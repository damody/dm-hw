
#include "osgImplementation.h"
#include <process.h>
#include <osg/Geometry>
#include <osg/Material>
#include <osg/Point>
#include <osg/LineWidth>
#include <osg/ref_ptr>
#include <osg/StateSet>
#include <osg/CullFace>
#include <osg/PolygonMode>

osgImplementation::osgImplementation( HWND hWnd )
:mhWnd(hWnd), mStatus(0), mMesh(0), mNeedUpdate(false)
{
	mDrawPoints = new osg::Geometry;
	mDrawSVertexs = new osg::Geometry;
	mDrawLines = new osg::Geometry;
	mDrawEdges = new osg::Geometry;
	mDrawVertexs = new osg::Geometry;
	mDrawFaces = new osg::Geometry;
	mDrawSFaces = new osg::Geometry;
	mDrawPoints->setUseDisplayList(false);
	mDrawSVertexs->setUseDisplayList(false);
	mDrawLines->setUseDisplayList(false);
	mDrawEdges->setUseDisplayList(false);
	mDrawVertexs->setUseDisplayList(false);
	mDrawFaces->setUseDisplayList(false);
	mDrawSFaces->setUseDisplayList(false);
}

osgImplementation::~osgImplementation(void)
{
	mViewer->setDone(true);
	Sleep(500);
	mViewer->stopThreading();
	delete mViewer;
}

void osgImplementation::Render( void* ptr )
{
	osgImplementation* osg = (osgImplementation*)ptr;
	osgViewer::Viewer* viewer = osg->getViewer();
	viewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);
	// You have two options for the main viewer loop
	//      viewer->run()   or
	//      while(!viewer->done()) { viewer->frame(); }
	//viewer->run();
	while(!viewer->done())
	{
		osg->PreFrameUpdate();
 		viewer->frame();
		//Sleep(10);
	}
	_endthread();
}

void osgImplementation::SetModel( Tri_Mesh* mesh )
{
	mMesh = mesh;
}

void osgImplementation::GetRay( float x, float y, osg::Vec3f& vPickRayOrig, osg::Vec3f& vPickRayDir )
{
	const osg::Matrixd& pmatProj = mViewer->getCamera()->getProjectionMatrix();
	osg::Viewport* viewport = mViewer->getCamera()->getViewport();
	// Compute the vector of the pick ray in screen space
	osg::Vec3f v;
	v[0] = ( ( ( 2.0f * x ) / viewport->width() ) - 1 ) / pmatProj.ptr()[0];
	v[1] = -( ( ( 2.0f * y ) / viewport->height() ) - 1 ) / pmatProj.ptr()[1*4+1];
	v[2] = 1.0f;

	// Get the inverse view matrix
	const osg::Matrixd& matView = mViewer->getCamera()->getViewMatrix();
	osg::Matrixd m;
	m.invert_4x4(matView);
	// Transform the screen space pick ray into 3D space
	vPickRayDir[0] = v[0] * m.ptr()[0*4+0] + v[1] * m.ptr()[1*4+0] + v[2] * m.ptr()[2*4+0];
	vPickRayDir[1] = v[0] * m.ptr()[0*4+1] + v[1] * m.ptr()[1*4+1] + v[2] * m.ptr()[2*4+1];
	vPickRayDir[2] = v[0] * m.ptr()[0*4+2] + v[1] * m.ptr()[1*4+2] + v[2] * m.ptr()[2*4+2];
	vPickRayOrig[0] = m.ptr()[3*4+0];
	vPickRayOrig[1] = m.ptr()[3*4+1];
	vPickRayOrig[2] = m.ptr()[3*4+2];
	vPickRayDir = vPickRayOrig-vPickRayDir*10;
}

void osgImplementation::AddPoint( const osg::Vec3f& p )
{
	mPoints.push_back(p);
	Show(mStatus);
}

void osgImplementation::AddVertex(const osg::Vec3f& p )
{
	mSVertexs.push_back(p);
	Show(mStatus);
}

void osgImplementation::AddVertex( const sPoints& input )
{
	for (int i=0;i<input.size();++i)
		AddVertex(input[i]);
}

void osgImplementation::AddLine(const osg::Vec3f& p, const osg::Vec3f& q )
{
	mLines.push_back(sLine(p, q));
	Show(mStatus);
}

void osgImplementation::AddLine( const sLines& input )
{
	for (int i=0;i<input.size();++i)
		AddLine(input[i].a, input[i].b);
}

void osgImplementation::AddFace( const osg::Vec3f& a, const osg::Vec3f& b, const osg::Vec3f& c )
{  
	mFaces.push_back(sFace(a, b, c));
	Show(mStatus);
}

void osgImplementation::AddFace( const sFaces& input )
{
	for (int i=0;i<input.size();++i)
		AddFace(input[i].a, input[i].b, input[i].c);
}


void osgImplementation::Show( int status /*= MODEL*/ )
{
	mStatus = status;
	mNeedUpdate = true;
}

void osgImplementation::InitSceneGraph( void )
{
	// Init the main Root Node/Group
	mRoot  = new osg::Group;
	mModel = new osg::Geode;
	mShape = new osg::Geode;
	mRoot->addChild(mShape.get());
	mRoot->addChild(mModel.get());
	mShape->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	//mShape->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	mShape->getOrCreateStateSet()->setRenderBinDetails( -1, "RenderBin");
 
 	mModel->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);
 	//mModel->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);

}

void osgImplementation::InitManipulators( void )
{
	// Create a trackball manipulator
	mTrackball = new osgGA::TrackballManipulator();
	// Create a Manipulator Switcher
	mKeyswitchManipulator = new osgGA::KeySwitchMatrixManipulator;
	// Add our trackball manipulator to the switcher
	mKeyswitchManipulator->addMatrixManipulator( '1', "Trackball", mTrackball.get());
	// Init the switcher to the first manipulator (in this case the only manipulator)
	mKeyswitchManipulator->selectMatrixManipulator(0);  // Zero based index Value
}

void osgImplementation::InitCameraConfig()
{
	// Local Variable to hold window size data
	RECT rect;
	// Create the viewer for this window
	mViewer = new osgViewer::Viewer();
	// add the thread model handler
	//mViewer->addEventHandler(new osgViewer::ThreadingHandler);
	// add the window size toggle handler
	mViewer->addEventHandler(new osgViewer::WindowSizeHandler);
	// add the stats handler
	mViewer->addEventHandler(new osgViewer::StatsHandler);
	// add the LOD Scale handler
	mViewer->addEventHandler(new osgViewer::LODScaleHandler);
	// add the screen capture handler
	mViewer->addEventHandler(new osgViewer::ScreenCaptureHandler);
	// Get the current window size
	::GetWindowRect(mhWnd, &rect);
	// Init the GraphicsContext Traits
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	// Init the Windata Variable that holds the handle for the Window to display OSG in.
	osg::ref_ptr<osg::Referenced> windata = new osgViewer::GraphicsWindowWin32::WindowData(mhWnd);
	// Setup the traits parameters
	traits->x = 0;
	traits->y = 0;
	traits->width = rect.right - rect.left;
	traits->height = rect.bottom - rect.top;
	traits->windowDecoration = false;
	traits->doubleBuffer = true;
	traits->sharedContext = 0;
	traits->setInheritedWindowPixelFormat = true;
	traits->inheritedWindowData = windata;
	// Create the Graphics Context
	osg::GraphicsContext* gc = osg::GraphicsContext::createGraphicsContext(traits.get());
	// Init a new Camera (Master for this View)
	mCamera = new osg::Camera;
	// Assign Graphics Context to the Camera
	mCamera->setGraphicsContext(gc);
	// Set the viewport for the Camera
	mCamera->setViewport(new osg::Viewport(traits->x, traits->y, traits->width, traits->height));
	// Set projection matrix and camera attribtues
	mCamera->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	mCamera->setClearColor(osg::Vec4f(0.2f, 0.2f, 0.4f, 1.0f));
	mCamera->setProjectionMatrixAsPerspective(
		30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0, 1000.0);
	// Add the Camera to the Viewer
	//mViewer->addSlave(camera.get());
	mViewer->setCamera(mCamera.get());
	// Add the Camera Manipulator to the Viewer
	mViewer->setCameraManipulator(mKeyswitchManipulator.get());
	// Set the Scene Data
	mViewer->setSceneData(mRoot.get());
	// Realize the Viewer
	mViewer->realize();
	// Correct aspect ratio
	/*double fovy,aspectRatio,z1,z2;
	mViewer->getCamera()->getProjectionMatrixAsPerspective(fovy,aspectRatio,z1,z2);
	aspectRatio=double(traits->width)/double(traits->height);
	mViewer->getCamera()->setProjectionMatrixAsPerspective(fovy,aspectRatio,z1,z2);*/
}

void osgImplementation::PreFrameUpdate()
{
	// Due any preframe updates in this routine
	if (mNeedUpdate && mMesh)
	{
		mNeedUpdate = false;
		if (!mPoints.empty())
		{// add all points
			osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
			for (size_t i=0;i<mPoints.size();++i)
				vertices->push_back(mPoints[i]);
			mDrawPoints->setVertexArray(vertices);
			osg::ref_ptr<osg::Vec4Array> shared_colors = new osg::Vec4Array;
			shared_colors->push_back(osg::Vec4(1.0f,0.0f,1.0f,1.0f));
			mDrawPoints->setColorArray(shared_colors);
			mDrawPoints->setColorBinding(osg::Geometry::BIND_OVERALL);
			mDrawPoints->setNormalBinding(osg::Geometry::BIND_OFF);
			mDrawPoints->removePrimitiveSet(0,999);
			mDrawPoints->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, vertices->getNumElements()));
			mDrawPoints->getOrCreateStateSet()->setAttribute( new osg::Point( 5.0f ), osg::StateAttribute::ON );
			if (!mShape->containsDrawable(mDrawPoints))
				mShape->addDrawable(mDrawPoints);
		}
		else
			mShape->removeDrawable(mDrawPoints);
		if (!mSVertexs.empty())
		{// add all points
			osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
			for (size_t i=0;i<mSVertexs.size();++i)
				vertices->push_back(mSVertexs[i]);
			
			mDrawSVertexs->setVertexArray(vertices);
			osg::ref_ptr<osg::Vec4Array> shared_colors = new osg::Vec4Array;
			shared_colors->push_back(osg::Vec4(1.0f,1.0f,1.0f,1.0f));
			mDrawSVertexs->setColorArray(shared_colors);
			mDrawSVertexs->setColorBinding(osg::Geometry::BIND_OVERALL);
			mDrawSVertexs->setNormalBinding(osg::Geometry::BIND_OFF);
			mDrawSVertexs->removePrimitiveSet(0,999);
			mDrawSVertexs->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, vertices->getNumElements()));
			mDrawSVertexs->getOrCreateStateSet()->setAttribute( new osg::Point( 5.0f ), osg::StateAttribute::ON );
			if (!mShape->containsDrawable(mDrawSVertexs))
				mShape->addDrawable(mDrawSVertexs);
		}
		else
			mShape->removeDrawable(mDrawSVertexs);
		if (!mLines.empty())
		{// add all lines
			osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
			for (size_t i=0;i<mLines.size();++i)
			{
				vertices->push_back(mLines[i].a);
				vertices->push_back(mLines[i].b);
			}
			
			mDrawLines->setVertexArray(vertices);
			osg::ref_ptr<osg::Vec4Array> shared_colors = new osg::Vec4Array;
			shared_colors->push_back(osg::Vec4(0.0f,1.0f,1.0f,1.0f));
			// use the shared color array.
			mDrawLines->setColorArray(shared_colors);
			mDrawLines->setColorBinding(osg::Geometry::BIND_OVERALL);
			mDrawLines->setNormalBinding(osg::Geometry::BIND_OFF);
			mDrawLines->removePrimitiveSet(0,999);
			mDrawLines->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, vertices->getNumElements()));
			mDrawLines->getOrCreateStateSet()->setAttribute( new osg::LineWidth(3.0f), osg::StateAttribute::ON );
			if (!mShape->containsDrawable(mDrawLines))
				mShape->addDrawable(mDrawLines);
		}
		else
			mShape->removeDrawable(mDrawLines);
		if (!mFaces.empty())
		{// add all faces
			osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
			for (size_t i=0;i<mFaces.size();++i)
			{
				vertices->push_back(mFaces[i].a);
				vertices->push_back(mFaces[i].b);
				vertices->push_back(mFaces[i].c);
			}
			
			mDrawSFaces->setVertexArray(vertices);
			osg::ref_ptr<osg::Vec4Array> shared_colors = new osg::Vec4Array;
			shared_colors->push_back(osg::Vec4(0.5f,0.5f,0.2f,1.0f));
			// use the shared color array.
			mDrawSFaces->setColorArray(shared_colors);
			mDrawSFaces->setColorBinding(osg::Geometry::BIND_OVERALL);
			mDrawSFaces->setNormalBinding(osg::Geometry::BIND_OFF);
			mDrawSFaces->removePrimitiveSet(0,999);
			mDrawSFaces->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, vertices->getNumElements()));
			if (!mShape->containsDrawable(mDrawSFaces))
				mShape->addDrawable(mDrawSFaces);
		}
		else
			mShape->removeDrawable(mDrawSFaces);
		
		if (mStatus & VERTEX)
		{
			BasicMesh::VertexIter v_it;
			osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
			osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
			for (v_it = mMesh->vertices_begin(); v_it != mMesh->vertices_end(); ++v_it) 
			{
				osg::Vec3 v_normal, v_point;
				const Tri_Mesh::Normal& n = mMesh->normal(v_it.handle());
				const Tri_Mesh::Point& p = mMesh->point(v_it.handle());
				for (int i=0;i<3;++i)
				{
					v_normal[i] = n[i];
					v_point[i] = p[i];
				}
				vertices->push_back(v_point);
				normals->push_back(v_normal);
			}
			// pass the created vertex array to the points geometry object.
			
			mDrawVertexs->setVertexArray(vertices);
			osg::ref_ptr<osg::Vec4Array> shared_colors = new osg::Vec4Array;
			shared_colors->push_back(osg::Vec4(1.0f,0.0f,0.0f,1.0f));
			// use the shared color array.
			mDrawVertexs->setColorArray(shared_colors);
			mDrawVertexs->setColorBinding(osg::Geometry::BIND_OVERALL);
			// use the normal array.
			mDrawVertexs->setNormalArray(normals);
			mDrawVertexs->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
			// This time we simply use primitive, and hardwire the number of coords to use 
			// since we know up front,
			mDrawVertexs->removePrimitiveSet(0,999);
			mDrawVertexs->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, vertices->getNumElements()));
			// add the points geometry to the geode.
			mDrawVertexs->getOrCreateStateSet()->setAttribute( new osg::Point( 2.0f ), osg::StateAttribute::ON );
			if (!mModel->containsDrawable(mDrawVertexs))
				mModel->addDrawable(mDrawVertexs);
		}
		else
		{
			mModel->removeDrawable(mDrawVertexs);
		}
		if (mStatus & EDGE)
		{
			BasicMesh::EdgeIter e_it;
			BasicMesh::HalfedgeHandle _hedge;
			osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
			osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
			osg::Vec3 v_normal, v_point;
			for(e_it = mMesh->edges_begin(); e_it != mMesh->edges_end(); ++e_it)
			{
				_hedge = mMesh->halfedge_handle(e_it.handle(),1);
				const Tri_Mesh::Normal& n1 = mMesh->normal(mMesh->from_vertex_handle(_hedge));
				const Tri_Mesh::Point& p1 = mMesh->point(mMesh->from_vertex_handle(_hedge));
				for (int i=0;i<3;++i)
				{
					v_point[i] = p1[i];
					v_normal[i] = n1[i];
				}
				vertices->push_back(v_point);
				normals->push_back(v_normal);
				const Tri_Mesh::Normal& n2 = mMesh->normal(mMesh->to_vertex_handle(_hedge));
				const Tri_Mesh::Point& p2 = mMesh->point(mMesh->to_vertex_handle(_hedge));
				for (int i=0;i<3;++i)
				{
					v_point[i] = p2[i];
					v_normal[i] = n2[i];
				}
				vertices->push_back(v_point);
				normals->push_back(v_normal);
			}
			// pass the created vertex array to the points geometry object.
			
			mDrawEdges->setVertexArray(vertices);
			osg::ref_ptr<osg::Vec4Array> shared_colors = new osg::Vec4Array;
			shared_colors->push_back(osg::Vec4(0.0f,1.0f,0.0f,1.0f));
			// use the shared color array.
			mDrawEdges->setColorArray(shared_colors);
			mDrawEdges->setColorBinding(osg::Geometry::BIND_OVERALL);
			// use the normal array.
			mDrawEdges->setNormalArray(normals);
			mDrawEdges->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
			// This time we simply use primitive, and hardwire the number of coords to use 
			// since we know up front,
			mDrawEdges->removePrimitiveSet(0,999);
			mDrawEdges->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, vertices->getNumElements()));
			// add the points geometry to the geode.
			if (!mModel->containsDrawable(mDrawEdges))
				mModel->addDrawable(mDrawEdges);
		}
		else
		{
			mModel->removeDrawable(mDrawEdges);
		}
		if (mStatus & FACE)
		{
			BasicMesh::FaceIter f_it;
			BasicMesh::FaceVertexIter fv_it;
			osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
			osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
			int count = 0;
			for (f_it = mMesh->faces_begin(); f_it != mMesh->faces_end(); ++f_it, ++count) 
			{
				osg::Vec3 v_normal, v_point;
				for (fv_it = mMesh->fv_iter( f_it ); fv_it; ++fv_it)
				{
					const Tri_Mesh::Normal& n = mMesh->normal(fv_it.handle());
					const Tri_Mesh::Point& p= mMesh->point(fv_it.handle());
					for (int i=0;i<3;++i)
					{
						v_normal[i] = n[i];
						v_point[i] = p[i];
					}
					vertices->push_back(v_point);
					normals->push_back(v_normal);
				}
			}
			
			// pass the created vertex array to the points geometry object.
			mDrawFaces->setVertexArray(vertices);
			osg::ref_ptr<osg::Vec4Array> shared_colors = new osg::Vec4Array;
			shared_colors->push_back(osg::Vec4(1.0f,1.0f,0.0f,1.0f));
			// use the shared color array.
			mDrawFaces->setColorArray(shared_colors);
			mDrawFaces->setColorBinding(osg::Geometry::BIND_OVERALL);
			// use the normal array.
			mDrawFaces->setNormalArray(normals);
			mDrawFaces->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
			// This time we simply use primitive, and hardwire the number of coords to use 
			// since we know up front,
			mDrawFaces->removePrimitiveSet(0,999);
			mDrawFaces->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, vertices->getNumElements()));
			// add the points geometry to the geode.
			if (!mModel->containsDrawable(mDrawFaces))
				mModel->addDrawable(mDrawFaces);
		}
		else
		{
			mModel->removeDrawable(mDrawFaces);
		}
	}
}

bool osgImplementation::SelectPoint( osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& out )
{
	if (!mMesh) return false;
	return mMesh->SelectPoint(p, q, out);
}

bool osgImplementation::SelectVertex( osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& out )
{
	if (!mMesh) return false;
	return mMesh->SelectVertex(p, q, out);
}

bool osgImplementation::SelectEdge( osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& out1, osg::Vec3f& out2 )
{
	if (!mMesh) return false;
	return mMesh->SelectEdge(p, q, out1, out2);
	return true;
}

bool osgImplementation::SelectFace( osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& out1, osg::Vec3f& out2, osg::Vec3f& out3 )
{
	if (!mMesh) return false;
	return mMesh->SelectFace(p, q, out1, out2, out3);
}

bool osgImplementation::SelectVertexRingVertex( osg::Vec3f& p, osg::Vec3f& q, sPoints& out )
{
	return mMesh->SelectVertexRingVertex(p, q, out);
}

bool osgImplementation::SelectVertexRingEdge( osg::Vec3f& p, osg::Vec3f& q, sLines& out )
{
	return mMesh->SelectVertexRingEdge(p, q, out);
}

bool osgImplementation::SelectVertexRingFace( osg::Vec3f& p, osg::Vec3f& q, sFaces& out )
{
	return mMesh->SelectVertexRingFace(p, q, out);
}

bool osgImplementation::SelectEdgeRingVertex( osg::Vec3f& p, osg::Vec3f& q, sPoints& out )
{
	return mMesh->SelectEdgeRingVertex(p, q, out);
}

bool osgImplementation::SelectEdgeRingEdge( osg::Vec3f& p, osg::Vec3f& q, sLines& out )
{
	return mMesh->SelectEdgeRingEdge(p, q, out);
}

bool osgImplementation::SelectEdgeRingFace( osg::Vec3f& p, osg::Vec3f& q, sFaces& out )
{
	return mMesh->SelectEdgeRingFace(p, q, out);
}

bool osgImplementation::SelectFaceRingVertex( osg::Vec3f& p, osg::Vec3f& q, sPoints& out )
{
	return mMesh->SelectFaceRingVertex(p, q, out);
}

bool osgImplementation::SelectFaceRingEdge( osg::Vec3f& p, osg::Vec3f& q, sLines& out )
{
	return mMesh->SelectFaceRingEdge(p, q, out);
}

bool osgImplementation::SelectFaceRingFace( osg::Vec3f& p, osg::Vec3f& q, sFaces& out )
{
	return mMesh->SelectFaceRingFace(p, q, out);
}

void osgImplementation::ClearPoints()
{
	mPoints.clear();
	Show(mStatus);
}

void osgImplementation::ClearVertexes()
{
	mSVertexs.clear();
	Show(mStatus);
}

void osgImplementation::ClearEdges()
{
	mLines.clear();
	Show(mStatus);
}

void osgImplementation::ClearFaces()
{
	mFaces.clear();
	Show(mStatus);
}

void RedirectIOToConsole()
{
	using namespace std;
	int hConHandle;
	long lStdHandle;
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	FILE *fp;
	// allocate a console for this app
	AllocConsole();
	// set the screen buffer to be big enough to let us scroll text
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
	coninfo.dwSize.Y = 1024;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),
		coninfo.dwSize);
	// redirect unbuffered STDOUT to the console
	lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "w" );
	*stdout = *fp;
	setvbuf( stdout, NULL, _IONBF, 0 );
	// redirect unbuffered STDIN to the console
	lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "r" );
	*stdin = *fp;
	setvbuf( stdin, NULL, _IONBF, 0 );
	// redirect unbuffered STDERR to the console
	lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "w" );
	*stderr = *fp;
	setvbuf( stderr, NULL, _IONBF, 0 );
	// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
	// point to console as well
	ios::sync_with_stdio();
}
