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

class osgControl
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
	osgControl(HWND hWnd);
	~osgControl(void);
	osg::ref_ptr<osg::Camera> mCamera;
private:
	bool mDone;
	std::string mModelName;
	HWND mhWnd;
	osgViewer::Viewer* mViewer;
	osg::ref_ptr<osg::Group> mRoot;
	osg::ref_ptr<osg::Geode> mModel;
	osg::ref_ptr<osgGA::TrackballManipulator> mTrackball;
	osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> mKeyswitchManipulator;
	Tri_Mesh*	mMesh;
	int	mStatus;
public:
	void AddLine(osg::Vec3f& p, osg::Vec3f& q);
	void AddPoint(osg::Vec3f& p);
	void AddFace(osg::Vec3f& a, osg::Vec3f& b, osg::Vec3f& c);
	void Show(int status);
	int  GetShowStatus() {return mStatus;}
	void ShowModel(){Show(mStatus | MODEL);}
	void ShowVertex(){Show(mStatus | VERTEX);}
	void ShowEdge(){Show(mStatus | EDGE);}
	void ShowFace(){Show(mStatus | FACE);}
	void SetModel(Tri_Mesh* mesh);
	void Done(bool value) { mDone = value; }
	bool Done(void) { return mDone; }
	static void Render(void* ptr);
	osgViewer::Viewer* getViewer() { return mViewer; }
	void GetRay(float x, float y, osg::Vec3f& vPickRayOrig, osg::Vec3f& vPickRayDir);
	void InitOSG(std::string modelname)
	{
		// Store the name of the model to load
		mModelName = modelname;
		// Init different parts of OSG
		InitManipulators();
		InitSceneGraph();
		InitCameraConfig();
	}
	void PreFrameUpdate()
	{
		// Due any preframe updates in this routine
	}
	void PostFrameUpdate()
	{
		// Due any postframe updates in this routine
	}

	void InitCameraConfig();
	void InitSceneGraph(void);
	void InitManipulators(void);
};
