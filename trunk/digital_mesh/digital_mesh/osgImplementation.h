#pragma once
#include "Tri_Mesh.h"
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/api/win32/GraphicsWindowWin32>
#include <osgGA/TrackballManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgDB/DatabasePager>
#include <osgDB/Registry>
#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <string>

struct sLine
{
	sLine(){}
	sLine(osg::Vec3f& _a, osg::Vec3f& _b)
		:a(_a), b(_b)
	{}
	osg::Vec3f a, b;
};
struct sFace
{
	sFace(){}
	sFace(osg::Vec3f& _a, osg::Vec3f& _b, osg::Vec3f& _c)
		:a(_a), b(_b), c(_c)
	{}
	osg::Vec3f a, b, c;
};

class osgImplementation
{
public:
	enum Choose_Show_Type
	{
		POINT	= 1,
		VERTEX	= 2,
		FACE	= 8,
		EDGE = 16,
		MODEL	= 32,
		RAY	= 64
	};
	osgImplementation(HWND hWnd);
	~osgImplementation(void);
	osg::ref_ptr<osg::Camera> mCamera;
private:
	
	bool mDone;
	HWND mhWnd;
	osgViewer::Viewer* mViewer;
	osg::ref_ptr<osg::Group> mRoot;
	osg::ref_ptr<osg::Geode> mModel;
	osg::ref_ptr<osg::Geode> mShape;
	osg::ref_ptr<osgGA::TrackballManipulator> mTrackball;
	osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> mKeyswitchManipulator;
	Tri_Mesh*	mMesh;
	int		mStatus;
	std::vector<osg::Vec3f> mPoints;
	std::vector<osg::Vec3f> mSVertexs;
	typedef std::vector<sLine> sLines;
	typedef std::vector<sLine> sFaces;
	sLines	mLines;
	sFaces	mFaces;
	osg::ref_ptr<osg::Geometry> mDrawPoints;
	osg::ref_ptr<osg::Geometry> mDrawLines;
	osg::ref_ptr<osg::Geometry> mDrawSVertexs;
	osg::ref_ptr<osg::Geometry> mDrawEdges;
	osg::ref_ptr<osg::Geometry> mDrawVertexs;
	osg::ref_ptr<osg::Geometry> mDrawSFaces;
	osg::ref_ptr<osg::Geometry> mDrawFaces;
	bool	mNeedUpdate;
public:
	static void Render(void* ptr);
	void AddLine(osg::Vec3f& p, osg::Vec3f& q);
	void AddPoint(osg::Vec3f& p);
	void AddVertex(osg::Vec3f& p);
	void AddFace(osg::Vec3f& a, osg::Vec3f& b, osg::Vec3f& c);
	bool SelectPoint(osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& out);
	bool SelectVertex(osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& out);
	bool SelectEdge(osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& out1, osg::Vec3f& out2);
	bool SelectFace(osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& out1, osg::Vec3f& out2, osg::Vec3f& out3);
	void Show(int status);
	int  GetShowStatus() {return mStatus;}
	void ShowModel(){Show(mStatus | MODEL);}
	void ShowVertex(){Show(mStatus | VERTEX);}
	void ShowEdge(){Show(mStatus | EDGE);}
	void ShowFace(){Show(mStatus | FACE);}
	void HideModel(){Show(mStatus & ~MODEL);}
	void HideVertex(){Show(mStatus & ~VERTEX);}
	void HideEdge(){Show(mStatus & ~EDGE);}
	void HideFace(){Show(mStatus & ~FACE);}
	void SetModel(Tri_Mesh* mesh);
	void Done(bool value) { mDone = value; }
	bool Done(void) { return mDone; }
		
	osgViewer::Viewer* getViewer() { return mViewer; }
	void GetRay(float x, float y, osg::Vec3f& vPickRayOrig, osg::Vec3f& vPickRayDir);
	void InitOSG()
	{
		// Init different parts of OSG
		InitManipulators();
		InitSceneGraph();
		InitCameraConfig();
	}
	void PreFrameUpdate();
	void InitCameraConfig();
	void InitSceneGraph(void);
	void InitManipulators(void);
};
