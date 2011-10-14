
#include "osgControl.h"
#include <process.h>
#include <osg/Geometry>
#include <osg/Material>


osgControl::osgControl( HWND hWnd ) :mhWnd(hWnd)
{
	
}

osgControl::~osgControl(void)
{
	mViewer->setDone(true);
	Sleep(500);
	mViewer->stopThreading();
	delete mViewer;
}

void osgControl::Render( void* ptr )
{
	osgControl* osg = (osgControl*)ptr;

	osgViewer::Viewer* viewer = osg->getViewer();

	// You have two options for the main viewer loop
	//      viewer->run()   or
	//      while(!viewer->done()) { viewer->frame(); }
	//viewer->run();
	while(!viewer->done())
	{
		osg->PreFrameUpdate();
		viewer->frame();
		osg->PostFrameUpdate();
		Sleep(10);         // Use this command if you need to allow other processes to have cpu time
	}
	// For some reason this has to be here to avoid issue: 
	// if you have multiple OSG windows up 
	// and you exit one then all stop rendering
	_endthread();
}

void osgControl::SetModel( Tri_Mesh* mesh )
{
	mMesh = mesh;
}

void osgControl::GetRay( float x, float y, osg::Vec3f& vPickRayOrig, osg::Vec3f& vPickRayDir )
{
	osg::Vec3f eye, center, up;
	mViewer->getCamera()->getViewMatrixAsLookAt(eye, center, up);
	const osg::Matrixd& pmatProj = mViewer->getCamera()->getProjectionMatrix();
	osg::Viewport* viewport = mViewer->getCamera()->getViewport();
	// Compute the vector of the pick ray in screen space
	osg::Vec3f v;
	v[0] = ( ( ( 2.0f * x ) / viewport->width() ) - 1 ) / pmatProj.ptr()[0];
	v[1] = -( ( ( 2.0f * y ) / viewport->height() ) - 1 ) / pmatProj.ptr()[1*4+1];
	v[2] = 1.0f;

	// Get the inverse view matrix
	const osg::Matrixd& matView = mViewer->getCamera()->getViewMatrix();
	const osg::Matrixd& matWorld = mViewer->getCamera()->getWorldMatrices().front();
	// 		const D3DXMATRIX matView = *g_Camera.GetViewMatrix();
	// 		const D3DXMATRIX matWorld = *g_Camera.GetWorldMatrix();
	osg::Matrixd mWorldView = matView, m;
	// 		D3DXMATRIX m;
	// 		D3DXMatrixInverse( &m, NULL, &mWorldView );
	m.invert_4x4(mWorldView);
	// Transform the screen space pick ray into 3D space
	vPickRayDir[0] = v[0] * m.ptr()[0*4+0] + v[1] * m.ptr()[1*4+0] + v[2] * m.ptr()[2*4+0];
	vPickRayDir[1] = v[0] * m.ptr()[0*4+1] + v[1] * m.ptr()[1*4+1] + v[2] * m.ptr()[2*4+1];
	vPickRayDir[2] = v[0] * m.ptr()[0*4+2] + v[1] * m.ptr()[1*4+2] + v[2] * m.ptr()[2*4+2];
	vPickRayOrig[0] = m.ptr()[3*4+0];
	vPickRayOrig[1] = m.ptr()[3*4+1];
	vPickRayOrig[2] = m.ptr()[3*4+2];
	vPickRayDir = vPickRayOrig-vPickRayDir*10;
}

void osgControl::AddLine( osg::Vec3f& p, osg::Vec3f& q )
{
	osg::Geometry* polyGeom = new osg::Geometry();
	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
	vertices->push_back(p);
	vertices->push_back(q);
	polyGeom->setVertexArray(vertices);
	osg::ref_ptr<osg::Vec4Array> shared_colors = new osg::Vec4Array;
	shared_colors->push_back(osg::Vec4(1.0f,1.0f,0.0f,1.0f));
	// use the shared color array.
	polyGeom->setColorArray(shared_colors.get());
	polyGeom->setColorBinding(osg::Geometry::BIND_OVERALL);
	polyGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 2));
	mModel->addDrawable(polyGeom);
}

void osgControl::Show( int status /*= MODEL*/ )
{
	osg::ref_ptr<osg::Geometry> polyGeom = new osg::Geometry;
	if (status & MODEL)
	{
		
	}
	if (status & EDGE)
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
		polyGeom->setVertexArray(vertices);
		osg::ref_ptr<osg::Vec4Array> shared_colors = new osg::Vec4Array;
		shared_colors->push_back(osg::Vec4(0.0f,1.0f,0.0f,1.0f));
		// use the shared color array.
		polyGeom->setColorArray(shared_colors.get());
		polyGeom->setColorBinding(osg::Geometry::BIND_OVERALL);
		// use the normal array.
// 		polyGeom->setNormalArray(normals.get());
// 		polyGeom->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
		// This time we simply use primitive, and hardwire the number of coords to use 
		// since we know up front,
		polyGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, vertices->getNumElements()));
		// add the points geometry to the geode.
		mModel->addDrawable(polyGeom);
	}
	if (status & VERTEX)
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
		polyGeom->setVertexArray(vertices);
		osg::ref_ptr<osg::Vec4Array> shared_colors = new osg::Vec4Array;
		shared_colors->push_back(osg::Vec4(1.0f,0.0f,0.0f,1.0f));
		// use the shared color array.
// 		polyGeom->setColorArray(shared_colors.get());
// 		polyGeom->setColorBinding(osg::Geometry::BIND_OVERALL);
		// use the normal array.
		polyGeom->setNormalArray(normals.get());
		polyGeom->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
		// This time we simply use primitive, and hardwire the number of coords to use 
		// since we know up front,
		polyGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, vertices->getNumElements()));
		// add the points geometry to the geode.
		mModel->addDrawable(polyGeom);
	}
	if (status & FACE)
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
		polyGeom->setVertexArray(vertices);
		osg::ref_ptr<osg::Vec4Array> shared_colors = new osg::Vec4Array;
		shared_colors->push_back(osg::Vec4(1.0f,1.0f,0.0f,1.0f));
		// use the shared color array.
		polyGeom->setColorArray(shared_colors.get());
		polyGeom->setColorBinding(osg::Geometry::BIND_OVERALL);
		// use the normal array.
 		polyGeom->setNormalArray(normals.get());
 		polyGeom->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
		// This time we simply use primitive, and hardwire the number of coords to use 
		// since we know up front,
		polyGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, vertices->getNumElements()));
		// add the points geometry to the geode.
		mModel->addDrawable(polyGeom);
	}
}

void osgControl::InitSceneGraph( void )
{
	// Init the main Root Node/Group
	mRoot  = new osg::Group;
	mModel = new osg::Geode();
	mRoot->addChild(mModel.get());
}

void osgControl::InitManipulators( void )
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

void osgControl::InitCameraConfig()
{
	// Local Variable to hold window size data
	RECT rect;

	// Create the viewer for this window
	mViewer = new osgViewer::Viewer();

	// add the thread model handler
	mViewer->addEventHandler(new osgViewer::ThreadingHandler);

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
