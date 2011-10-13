
#include "osgControl.h"
#include <process.h>
#include <osg/Geometry>
#include <osg/Material>


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
		//Sleep(10);         // Use this command if you need to allow other processes to have cpu time
	}
	// For some reason this has to be here to avoid issue: 
	// if you have multiple OSG windows up 
	// and you exit one then all stop rendering
	_endthread();
}

void osgControl::SetModel( Tri_Mesh* mesh )
{
	mModel = new osg::Geode();
	osg::Geometry* polyGeom = new osg::Geometry();

	BasicMesh::FaceIter f_it;
	BasicMesh::FaceVertexIter fv_it;
	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
	osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
	int count = 0;

	for (f_it = mesh->faces_begin(); f_it != mesh->faces_end(); ++f_it, ++count) 
	{
		osg::Vec3 v_normal, v_point;
		int cc=0;
		for (fv_it = mesh->fv_iter( f_it ); fv_it; ++fv_it, ++cc)
		{
			const Tri_Mesh::Normal& n = mesh->normal(fv_it.handle());
			const Tri_Mesh::Point& p= mesh->point(fv_it.handle());
			for (int i=0;i<3;++i)
			{
				v_normal[i] = n[i];
				v_point[i] = p[i];
			}
			vertices->push_back(v_point);
			normals->push_back(v_normal);
		}
		assert(cc==3);
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
	// Optimize the model
	osgUtil::Optimizer optimizer;
	optimizer.optimize(mModel.get());
	optimizer.reset();

	// Add the model to the scene
	mRoot->addChild(mModel.get());
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
