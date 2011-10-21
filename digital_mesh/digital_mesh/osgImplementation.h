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
#include <vector>


#include <windows.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>

void RedirectIOToConsole();

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
	sPoints mPoints;
	sPoints mSVertexs;
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
	// clear
	void ClearPoints();
	void ClearVertexes();
	void ClearEdges();
	void ClearFaces();

	// add single shape
	void AddPoint(const osg::Vec3f& p);
	void AddVertex(const osg::Vec3f& p);
	void AddLine(const osg::Vec3f& p, const osg::Vec3f& q);
	void AddFace(const osg::Vec3f& a, const osg::Vec3f& b, const osg::Vec3f& c);
	// add shapes
	void AddVertex(const sPoints& input);
	void AddLine(const sLines& input);
	void AddFace(const sFaces& input);
	// select basic shape
	bool SelectPoint(osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& out);
	bool SelectVertex(osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& out);
	bool SelectEdge(osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& out1, osg::Vec3f& out2);
	bool SelectFace(osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& out1, osg::Vec3f& out2, osg::Vec3f& out3);
	// select Vertex Ring
	bool SelectVertexRingVertex(osg::Vec3f& p, osg::Vec3f& q, sPoints& out);
	bool SelectVertexRingEdge(osg::Vec3f& p, osg::Vec3f& q, sLines& out);
	bool SelectVertexRingFace(osg::Vec3f& p, osg::Vec3f& q, sFaces& out);
	// select Edge Ring
	bool SelectEdgeRingVertex(osg::Vec3f& p, osg::Vec3f& q, sPoints& out);
	bool SelectEdgeRingEdge(osg::Vec3f& p, osg::Vec3f& q, sLines& out);
	bool SelectEdgeRingFace(osg::Vec3f& p, osg::Vec3f& q, sFaces& out);
	// select Face Ring
	bool SelectFaceRingVertex(osg::Vec3f& p, osg::Vec3f& q, sPoints& out);
	bool SelectFaceRingEdge(osg::Vec3f& p, osg::Vec3f& q, sLines& out);
	bool SelectFaceRingFace(osg::Vec3f& p, osg::Vec3f& q, sFaces& out);

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
		//RedirectIOToConsole();
		InitManipulators();
		InitSceneGraph();
		InitCameraConfig();
	}
	void PreFrameUpdate();
	void InitCameraConfig();
	void InitSceneGraph(void);
	void InitManipulators(void);
};
