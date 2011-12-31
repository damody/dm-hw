
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
#include <osgGA/TerrainManipulator>
#include <osgGA/FirstPersonManipulator>
#include <osgGA/OrbitManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>

// Initialization all variable
osgImplementation::osgImplementation( HWND hWnd )
:mhWnd(hWnd), mStatus(0), mMesh(0), mNeedUpdate(0), 
mNeedClearVertexes(0), mNeedClearEdges(0), mNeedClearFaces(0),
mNeedSimple(0), mFaceTransparency(1.0f), mHasLastSkeletonNode(false)
{
	mDrawPoints = new osg::Geometry;
	mDrawSVertices = new osg::Geometry;
	mDrawLines = new osg::Geometry;
	mDrawEdges = new osg::Geometry;
	mDrawVertexs = new osg::Geometry;
	mDrawFaces = new osg::Geometry;
	mDrawSFaces = new osg::Geometry;
	mVertices = new osg::Vec3Array;
	mVerticesColors = new osg::Vec4Array;
	mLinesColors = new osg::Vec4Array;
	mFacesColors= new osg::Vec4Array;
	mLines = new osg::Vec3Array;
	mFaces = new osg::Vec3Array;
}

osgImplementation::~osgImplementation(void)
{
	mViewer->setDone(true);
	mViewer->stopThreading();
	delete mViewer;
}

void osgImplementation::Render( void* ptr )
{
	osgImplementation* osg = (osgImplementation*)ptr;
	osgViewer::Viewer* viewer = osg->getViewer();
	
	while(!viewer->done())
	{
		osg->PreFrameUpdate();
 		viewer->frame();
		Sleep(10);

		osg::Vec3 eye, center, up;
		osg::Vec4 r;
		viewer->getCamera()->getViewMatrixAsLookAt(eye, center, up);
		up = center-eye;
		r[0]=eye[0];
		r[1]=eye[1];
		r[2]=eye[2];
		r[3]=1;
		osg->mModelLight->setPosition(r);
		osg->mModelLight->setDirection(center-eye); 
		osg->mModelLight->setSpotCutoff(25.f); 
	}
	_endthread();
}

void osgImplementation::SetModel( Tri_Mesh* mesh )
{
	mMesh = mesh;
	//init point
	BasicMesh::VertexIter v_it;
	mPointVertices = new osg::Vec3Array;
	mPointNormals = new osg::Vec3Array;
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
		mPointVertices->push_back(v_point);
		mPointNormals->push_back(v_normal);
	}
	// init edge
	BasicMesh::EdgeIter e_it;
	BasicMesh::HalfedgeHandle _hedge;
	mEdgeVertices = new osg::Vec3Array;
	mEdgeNormals = new osg::Vec3Array;
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
		mEdgeVertices->push_back(v_point);
		mEdgeNormals->push_back(v_normal);
		const Tri_Mesh::Normal& n2 = mMesh->normal(mMesh->to_vertex_handle(_hedge));
		const Tri_Mesh::Point& p2 = mMesh->point(mMesh->to_vertex_handle(_hedge));
		for (int i=0;i<3;++i)
		{
			v_point[i] = p2[i];
			v_normal[i] = n2[i];
		}
		mEdgeVertices->push_back(v_point);
		mEdgeNormals->push_back(v_normal);
	}
	//init face
	BasicMesh::FaceIter f_it;
	BasicMesh::FaceVertexIter fv_it;
	mFaceVertices = new osg::Vec3Array;
	mFaceNormals = new osg::Vec3Array;
	int count = 0;
	for (f_it = mMesh->faces_begin(); f_it != mMesh->faces_end(); ++f_it, ++count) 
	{
		osg::Vec3 v_normal, v_point;
		int i=0;
		for (fv_it = mMesh->fv_iter( f_it ); fv_it; ++fv_it, ++i)
		{
			if (i>=3) break;
			const Tri_Mesh::Normal& n = mMesh->normal(fv_it.handle());
			const Tri_Mesh::Point& p= mMesh->point(fv_it.handle());
			for (int i=0;i<3;++i)
			{
				v_normal[i] = n[i];
				v_point[i] = p[i];
			}
			mFaceVertices->push_back(v_point);
			mFaceNormals->push_back(v_normal);
		}
	}
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


void osgImplementation::AddVertex(const osg::Vec3f& p, float r, float g, float b )
{
	mVertices->push_back(p);
	mVerticesColors->push_back(osg::Vec4f(r, g, b, 1.0f));
	Show(mStatus);
}

void osgImplementation::AddVertex( const sPoints& input, float r, float g, float b )
{
	for (size_t i=0;i<input.size();++i)
		AddVertex(input[i], r, g, b);
}

void osgImplementation::AddLine(const osg::Vec3f& p, const osg::Vec3f& q, float r, float g, float b )
{
	mLines->push_back(p);
	mLines->push_back(q);
	mLinesColors->push_back(osg::Vec4f(r, g, b, 1.0f));
	Show(mStatus);
}

void osgImplementation::AddLine( const sLines& input, float r, float g, float b )
{
	for (size_t i=0;i<input.size();i+=2)
	{
		mLines->push_back(input[i]);
		mLines->push_back(input[i+1]);
		mLinesColors->push_back(osg::Vec4f(r, g, b, 1.0f));
	}
	Show(mStatus);
}

void osgImplementation::AddFace( const osg::Vec3f& fa, const osg::Vec3f& fb, const osg::Vec3f& fc, float r, float g, float b )
{  
	mFaces->push_back(fa);
	mFaces->push_back(fb);
	mFaces->push_back(fc);
	mFacesColors->push_back(osg::Vec4f(r, g, b, 0.9f));
	Show(mStatus);
}

void osgImplementation::AddFace( const sFaces& input, float r, float g, float b )
{
	for (size_t i=0;i<input.size();i+=3)
	{
		mFaces->push_back(input[i]);
		mFaces->push_back(input[i+1]);
		mFaces->push_back(input[i+2]);
		mFacesColors->push_back(osg::Vec4f(r, g, b, 0.9f));
	}
	Show(mStatus);
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
	mShape->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
	mShape->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
	mShape->getOrCreateStateSet()->setRenderBinDetails( -1, "RenderBin");
 
 	mModel->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);
	osg::CullFace* cf = new osg::CullFace(osg::CullFace::FRONT); 
	mModel->getOrCreateStateSet()->setAttribute( cf ); 
	//mModel->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	mModel->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
	mModelMaterial = new osg::Material; 
	mModelMaterial->setDiffuse( osg::Material::FRONT, 
		osg::Vec4( 1.0f,1.0f,0.0f, 1.f ) ); 
	mModelMaterial->setSpecular( osg::Material::FRONT, 
		osg::Vec4( .3f, .3f, .3f, .3f ) ); 
	mModelMaterial->setShininess( osg::Material::FRONT, 96.f ); 
	mModel->getOrCreateStateSet()->setAttribute(mModelMaterial.get()); 
	mModelLight = new osg::Light;
	mModelLight->setAmbient( osg::Vec4( .1f, .1f, .1f, 1.f )); 
	mModelLight->setDiffuse( osg::Vec4( .8f, .8f, .8f, 1.f )); 
	mModelLight->setSpecular( osg::Vec4( .8f, .8f, .8f, 1.f )); 
	// Add the Light to a LightSource. Add the LightSource and 
	//   MatrixTransform to the scene graph. 
	osg::ref_ptr<osg::LightSource> ls = new osg::LightSource; 
	mRoot->addChild( ls );
	ls->setLight( mModelLight.get() ); 
}

void osgImplementation::SetFaceTransparency( int percent )
{
	mFaceTransparency = percent*0.01f;
	//mModelMaterial->setDiffuse( osg::Material::FRONT, osg::Vec4( 1.0f,1.0f,0.0f, mFaceTransparency) ); 
	mModelMaterial->setAlpha(osg::Material::Face::FRONT, mFaceTransparency);
	// 	osg::ref_ptr<osg::Vec4Array> shared_colors = new osg::Vec4Array;
	// 	shared_colors->push_back(osg::Vec4(1.0f,1.0f,0.0f,mFaceTransparency));
	//	mDrawFaces->setColorArray(shared_colors);
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
	osg::ref_ptr<osgGA::CameraManipulator> mani = new osgGA::DriveManipulator;
	mKeyswitchManipulator->addMatrixManipulator( '2', "Drive", mani);
	mani = new osgGA::FlightManipulator;
	mKeyswitchManipulator->addMatrixManipulator( '3', "Flight", mani);
	mani = new osgGA::TerrainManipulator;
	mKeyswitchManipulator->addMatrixManipulator( '4', "Terrain", mani);
	mani = new osgGA::FirstPersonManipulator;
	mKeyswitchManipulator->addMatrixManipulator( '5', "FirstPersonMan", mani);
	mani = new osgGA::OrbitManipulator;
	mKeyswitchManipulator->addMatrixManipulator( '6', "Orbit", mani);
}

void osgImplementation::InitCameraConfig()
{
	// Local Variable to hold window size data
	RECT rect;
	// Create the viewer for this window
	mViewer = new osgViewer::Viewer();
	// add the thread model handler
	mViewer->addEventHandler(new osgViewer::ThreadingHandler);
	// add the window size toggle handler
	//mViewer->addEventHandler(new osgViewer::WindowSizeHandler);
	// add the stats handler
	mViewer->addEventHandler(new osgViewer::StatsHandler);
	// add the LOD Scale handler
	mViewer->addEventHandler(new osgViewer::LODScaleHandler);
	// add the screen capture handler
	//mViewer->addEventHandler(new osgViewer::ScreenCaptureHandler);
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
	mViewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);
}

void osgImplementation::PreFrameUpdate()
{
	// Due any preframe updates in this routine
	if (mNeedSimple>0)
	{
		mNeedUpdate = true;
		static int i=0;
		mMesh->MeshSimplification(mNeedSimple, mNeedSimpleConvex);
		SetModel(mMesh);
		mNeedSimple = 0;
	}
	if (mNeedClearFaces)
	{
		mNeedClearFaces = false;
		mNeedUpdate = true;
		mDrawSFaces->removePrimitiveSet(0,999);
		mFaces->clear();
		mFacesColors->clear();
		mMesh->mDontMove.clear();
	}
	if (mNeedClearEdges)
	{
		mNeedClearEdges = false;
		mNeedUpdate = true;
		mDrawLines->removePrimitiveSet(0,999);
		mLines->clear();
		mLinesColors->clear();
	}
	if (mNeedClearVertexes)
	{
		mNeedClearVertexes = false;
		mNeedUpdate = true;
		mDrawSVertices->removePrimitiveSet(0,999);
		mVertices->clear();
		mVerticesColors->clear();
	}
	if (mNeedUpdate && mMesh)
	{
		mNeedUpdate = false;
		if (!mVertices->empty())
		{// add all points
			if (mVertices->size() == 1)
			{
				mVertices->push_back(osg::Vec3f(0,0,0));
				mVerticesColors->push_back(osg::Vec4f(0,0,0,0));
			}
			mDrawSVertices->setVertexArray(mVertices);
			mDrawSVertices->setColorArray(mVerticesColors);
			mDrawSVertices->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE);
			mDrawSVertices->setNormalBinding(osg::Geometry::BIND_OFF);
			mDrawSVertices->removePrimitiveSet(0,999);
			mDrawSVertices->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, mVertices->size()));
			mDrawSVertices->getOrCreateStateSet()->setAttribute( new osg::Point( 5.0f ), osg::StateAttribute::ON );
			if (!mShape->containsDrawable(mDrawSVertices))
				mShape->addDrawable(mDrawSVertices);
		}
		else
			mShape->removeDrawable(mDrawSVertices);
		if (!mLines->empty())
		{// add all lines
			mDrawLines->setVertexArray(mLines);
			mDrawLines->setColorArray(mLinesColors);
			mDrawLines->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE);
			mDrawLines->setNormalBinding(osg::Geometry::BIND_OFF);
			mDrawLines->removePrimitiveSet(0,999);
			mDrawLines->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, mLines->size()));
			mDrawLines->getOrCreateStateSet()->setAttribute( new osg::LineWidth(3.0f), osg::StateAttribute::ON );
			if (!mShape->containsDrawable(mDrawLines))
				mShape->addDrawable(mDrawLines);
		}
		else
			mShape->removeDrawable(mDrawLines);
		if (!mFaces->empty())
		{// add all faces
			mDrawSFaces->setVertexArray(mFaces);
			mDrawSFaces->setColorArray(mFacesColors);
			mDrawSFaces->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE);
			mDrawSFaces->setNormalBinding(osg::Geometry::BIND_OFF);
			mDrawSFaces->removePrimitiveSet(0,999);
			mDrawSFaces->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, mFaces->size()));
			if (!mShape->containsDrawable(mDrawSFaces))
				mShape->addDrawable(mDrawSFaces);
		}
		else
			mShape->removeDrawable(mDrawSFaces);
		
		if (mStatus & VERTEX)
		{
			// pass the created vertex array to the points geometry object.
			mDrawVertexs->setVertexArray(mPointVertices);
			osg::ref_ptr<osg::Vec4Array> shared_colors = new osg::Vec4Array;
			shared_colors->push_back(osg::Vec4(1.0f,0.0f,0.0f,1.0f));
			// use the shared color array.
			mDrawVertexs->setColorArray(shared_colors);
			mDrawVertexs->setColorBinding(osg::Geometry::BIND_OVERALL);
			// use the normal array.
			mDrawVertexs->setNormalArray(mPointNormals);
			mDrawVertexs->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
			// This time we simply use primitive, and hardwire the number of coords to use 
			// since we know up front,
			mDrawVertexs->removePrimitiveSet(0,999);
			mDrawVertexs->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, mPointVertices->size()));
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
			// pass the created vertex array to the points geometry object.			
			mDrawEdges->setVertexArray(mEdgeVertices);
			osg::ref_ptr<osg::Vec4Array> shared_colors = new osg::Vec4Array;
			shared_colors->push_back(osg::Vec4(0.0f,1.0f,0.0f,1.0f));
			// use the shared color array.
			mDrawEdges->setColorArray(shared_colors);
			mDrawEdges->setColorBinding(osg::Geometry::BIND_OVERALL);
			// use the normal array.
			mDrawEdges->setNormalArray(mEdgeNormals);
			mDrawEdges->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
			// This time we simply use primitive, and hardwire the number of coords to use 
			// since we know up front,
			mDrawEdges->removePrimitiveSet(0,999);
			mDrawEdges->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, mEdgeVertices->size()));
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
			// pass the created vertex array to the points geometry object.
			mDrawFaces->setVertexArray(mFaceVertices);
			osg::ref_ptr<osg::Vec4Array> shared_colors = new osg::Vec4Array;
			shared_colors->push_back(osg::Vec4(1.0f,1.0f,0.0f,mFaceTransparency));
			// use the shared color array.
			mDrawFaces->setColorArray(shared_colors);
			mDrawFaces->setColorBinding(osg::Geometry::BIND_OVERALL);
			// use the normal array.
			mDrawFaces->setNormalArray(mFaceNormals);
			mDrawFaces->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
			// This time we simply use primitive, and hardwire the number of coords to use 
			// since we know up front,
			mDrawFaces->removePrimitiveSet(0,999);
			mDrawFaces->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, mFaceVertices->size()));
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

bool osgImplementation::SelectPoint( const osg::Vec3f& p, const osg::Vec3f& q, osg::Vec3f& out )
{
	if (!mMesh) return false;
	return mMesh->SelectPoint(p, q, out);
}

bool osgImplementation::SelectVertex( const osg::Vec3f& p, const osg::Vec3f& q, osg::Vec3f& out )
{
	if (!mMesh) return false;
	return mMesh->SelectVertex(p, q, out);
}

bool osgImplementation::SelectEdge( const osg::Vec3f& p, const osg::Vec3f& q, osg::Vec3f& out1, osg::Vec3f& out2 )
{
	if (!mMesh) return false;
	return mMesh->SelectEdge(p, q, out1, out2);
	return true;
}

bool osgImplementation::SelectFace( const osg::Vec3f& p, const osg::Vec3f& q, osg::Vec3f& out1, osg::Vec3f& out2, osg::Vec3f& out3 )
{
	if (!mMesh) return false;
	return mMesh->SelectFace(p, q, out1, out2, out3);
}

bool osgImplementation::SelectVertexRingVertex( const osg::Vec3f& p, const osg::Vec3f& q, sPoints& out )
{
	return mMesh->SelectVertexRingVertex(p, q, out);
}

bool osgImplementation::SelectVertexRingEdge( const osg::Vec3f& p, const osg::Vec3f& q, sLines& out )
{
	return mMesh->SelectVertexRingEdge(p, q, out);
}

bool osgImplementation::SelectVertexRingFace( const osg::Vec3f& p, const osg::Vec3f& q, sFaces& out )
{
	return mMesh->SelectVertexRingFace(p, q, out);
}

bool osgImplementation::SelectEdgeRingVertex( const osg::Vec3f& p, const osg::Vec3f& q, sPoints& out )
{
	return mMesh->SelectEdgeRingVertex(p, q, out);
}

bool osgImplementation::SelectEdgeRingEdge( const osg::Vec3f& p, const osg::Vec3f& q, sLines& out )
{
	return mMesh->SelectEdgeRingEdge(p, q, out);
}

bool osgImplementation::SelectEdgeRingFace( const osg::Vec3f& p, const osg::Vec3f& q, sFaces& out )
{
	return mMesh->SelectEdgeRingFace(p, q, out);
}

bool osgImplementation::SelectFaceRingVertex( const osg::Vec3f& p, const osg::Vec3f& q, sPoints& out )
{
	return mMesh->SelectFaceRingVertex(p, q, out);
}

bool osgImplementation::SelectFaceRingEdge( const osg::Vec3f& p, const osg::Vec3f& q, sLines& out )
{
	return mMesh->SelectFaceRingEdge(p, q, out);
}

bool osgImplementation::SelectDontMoveFace( const osg::Vec3f& p, const osg::Vec3f& q, sFaces& out )
{
	return mMesh->SelectDontMoveFace(p, q, out);
}

bool osgImplementation::SelectFaceRingFace( const osg::Vec3f& p, const osg::Vec3f& q, sFaces& out )
{
	return mMesh->SelectFaceRingFace(p, q, out);
}

void osgImplementation::ClearVertexes()
{
	mNeedClearVertexes = true;
}

void osgImplementation::ClearEdges()
{
	mHasLastSkeletonNode = false;
	mNeedClearEdges = true;
}

void osgImplementation::ClearFaces()
{
	mNeedClearFaces = true;
}

void osgImplementation::DeleteEdge( const osg::Vec3f& a, const osg::Vec3f& b )
{
	BasicMesh::HalfedgeHandle it;
	if (mMesh->GetEdgeHandleFromPoints(a, b, it))
	{
		if (mMesh->is_valid_handle(it) && mMesh->is_collapse_ok(it))
			mMesh->DeleteEdge(it);
	}
	Show(mStatus);
}

void osgImplementation::MeshSimplification( int reduce_num, bool convex_check )
{
	if (!mMesh) return ;
	mNeedSimple = reduce_num;
	mNeedSimpleConvex = convex_check;
	Show(mStatus);
}

void osgImplementation::SetViewer( bool run )
{
	if (run)
		mViewer->setCameraManipulator(mKeyswitchManipulator.get(), false);
	else
		mViewer->setCameraManipulator(NULL);
}

int osgImplementation::GetNumOfAllRayTraceNodes( const osg::Vec3f& p, const osg::Vec3f& q )
{
	if (!mMesh) return false;
	mAllRayTraceNode.clear();
	mMesh->GetAllRayTraceNode(p, q, mAllRayTraceNode);
	return mAllRayTraceNode.size();
}

void osgImplementation::GetLastAllRayTraceNodes( Vec3fs& res )
{
	if (!mMesh) return ;
	res = mAllRayTraceNode;
}

bool osgImplementation::GetLastTraceNodeByIndex(int index, osg::Vec3f& res)
{
	if (!mMesh) return false;
	assert(index >= 0 && index < mAllRayTraceNode.size());
	if (index >= 0 && index < mAllRayTraceNode.size())
	{
		res = mAllRayTraceNode[index];
		return true;
	}
	else
		return false;
}

void osgImplementation::AddSkeletonNode( const osg::Vec3f& p )
{
	mSkeletonNodes.push_back(p);
	AddVertex(p, 1.0f, 0.7f, 0.7f);
	if (mHasLastSkeletonNode)
		AddLine(mLastSkeletonNode, p, 1.0f, 0.4f, 0.4f);
	mHasLastSkeletonNode = true;
	mLastSkeletonNode = p;
}


void osgImplementation::SelectSkeletonNode( const osg::Vec3f& p, const osg::Vec3f& q )
{
	float dis;
	for (int i=0;i < mSkeletonNodes.size();++i)
	{
		dis = SqDistPointSegment(p, q, mSkeletonNodes[i]);
		if (dis < 0.01)
			mLastSkeletonNode = mSkeletonNodes[i];
	}
	
}

void osgImplementation::ResetCamera()
{
	mViewer->setCameraManipulator(mKeyswitchManipulator.get());
}