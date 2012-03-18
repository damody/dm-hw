#pragma once
#include "Matrix_Mesh.h"
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
#include <osg/Material>
#include <osg/ShapeDrawable>

#include "shared_ptr.h"
#include "Skeletonizer.h"


SHARE_PTR(Skeletonizer)

typedef osg::ref_ptr<osg::ShapeDrawable> ShapeDrawable_sptr;

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
	osg::ref_ptr<osg::Geode> mSkeleton;
	osg::ref_ptr<osg::Geode> mShape;
	osg::ref_ptr<osgGA::TrackballManipulator> mTrackball;
	osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> mKeyswitchManipulator;
	Matrix_Mesh*	mMesh;
	int		mStatus;
	osg::ref_ptr<sPoints>	mVertices;
	osg::ref_ptr<sColors>	mVerticesColors;
	osg::ref_ptr<sLines>	mLines;
	osg::ref_ptr<sColors>	mLinesColors;
	osg::ref_ptr<sFaces>	mFaces;
	osg::ref_ptr<sColors>	mFacesColors;
	osg::ref_ptr<osg::LightSource> mLightSource;
	osg::ref_ptr<osg::Light>    mModelLight;
	osg::ref_ptr<osg::Material> mModelMaterial;
	osg::ref_ptr<osg::Geometry> mDrawPoints;
	osg::ref_ptr<osg::Geometry> mDrawLines;
	osg::ref_ptr<osg::Geometry> mDrawSVertices;
	osg::ref_ptr<osg::Geometry> mDrawEdges;
	osg::ref_ptr<osg::Geometry> mDrawVertexs;
	osg::ref_ptr<osg::Geometry> mDrawSFaces;
	osg::ref_ptr<osg::Geometry> mDrawFaces;
	osg::ref_ptr<osg::Vec3Array> mPointVertices;
	osg::ref_ptr<osg::Vec3Array> mPointNormals;
	osg::ref_ptr<osg::Vec3Array> mEdgeVertices;
	osg::ref_ptr<osg::Vec3Array> mEdgeNormals;
	osg::ref_ptr<osg::Vec3Array> mFaceVertices;
	osg::ref_ptr<osg::Vec3Array> mFaceNormals;
	Vec3fs	mAllRayTraceNode;
	bool	mNeedUpdate;
	bool	mNeedClearVertexes;
	bool	mNeedClearEdges;
	bool	mNeedClearFaces;
	int	mNeedSimple;
	bool	mNeedSimpleConvex;
	float	mFaceTransparency;
	bool	mHasLastSkeletonNode;
	osg::Vec3f	mLastSkeletonNode;
	Vec3fs	mSkeletonNodes;
	Skeletonizer_sptr mMeshSkeletonizer;
	Skeletonizer::Options mMeshOptions;
public:
	static void Render(void* ptr);
	void MeshSimplification(int reduce_num, bool convex_check);
	// clear
	void ClearVertexes();
	void ClearEdges();
	void ClearFaces();

	//delete edge
	void DeleteEdge(const osg::Vec3f& a, const osg::Vec3f& b);
	// add single shape
	void AddVertex(const osg::Vec3f& p, float r, float g, float b);
	void AddLine(const osg::Vec3f& p, const osg::Vec3f& q, float r, float g, float b);
	void AddFace(const osg::Vec3f& fa, const osg::Vec3f& fb, const osg::Vec3f& fc, float r, float g, float b);
	void AddSkeletonNode(const osg::Vec3f& p);
	// add shapes
	void AddVertex(const sPoints& input, float r, float g, float b);
	void AddLine(const sLines& input, float r, float g, float b);
	void AddFace(const sFaces& input, float r, float g, float b);
	// select basic shape
	bool SelectPoint(const osg::Vec3f& p, const osg::Vec3f& q, osg::Vec3f& out);
	bool SelectVertex(const osg::Vec3f& p, const osg::Vec3f& q, osg::Vec3f& out);
	bool SelectEdge(const osg::Vec3f& p, const osg::Vec3f& q, osg::Vec3f& out1, osg::Vec3f& out2);
	bool SelectFace(const osg::Vec3f& p, const osg::Vec3f& q, osg::Vec3f& out1, osg::Vec3f& out2, osg::Vec3f& out3);
	// select Vertex Ring
	bool SelectVertexRingVertex(const osg::Vec3f& p, const osg::Vec3f& q, sPoints& out);
	bool SelectVertexRingEdge(const osg::Vec3f& p, const osg::Vec3f& q, sLines& out);
	bool SelectVertexRingFace(const osg::Vec3f& p, const osg::Vec3f& q, sFaces& out);
	// select Edge Ring
	bool SelectEdgeRingVertex(const osg::Vec3f& p, const osg::Vec3f& q, sPoints& out);
	bool SelectEdgeRingEdge(const osg::Vec3f& p, const osg::Vec3f& q, sLines& out);
	bool SelectEdgeRingFace(const osg::Vec3f& p, const osg::Vec3f& q, sFaces& out);
	// select Face Ring
	bool SelectFaceRingVertex(const osg::Vec3f& p, const osg::Vec3f& q, sPoints& out);
	bool SelectFaceRingEdge(const osg::Vec3f& p, const osg::Vec3f& q, sLines& out);
	bool SelectDontMoveFace(const osg::Vec3f& p, const osg::Vec3f& q, sLines& out);
	bool SelectFaceRingFace(const osg::Vec3f& p, const osg::Vec3f& q, sFaces& out);
	int  GetNumOfAllRayTraceNodes(const osg::Vec3f& p, const osg::Vec3f& q);
	void GetLastAllRayTraceNodes(Vec3fs& res);
	bool GetLastTraceNodeByIndex(int index, osg::Vec3f& res);
	void SelectSkeletonNode(const osg::Vec3f& p, const osg::Vec3f& q);
	void ShowSmoothSkeleton();
	Tri_Mesh* ExportSkeleton();

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
	void SetFaceTransparency(int percent);
	void SetModel(Matrix_Mesh* mesh);
	void SetViewer(bool run);
	void ResetCamera();
	void Done(bool value) { mDone = value; }
	bool Done(void) { return mDone; }
		
	osgViewer::Viewer* GetViewer() { return mViewer; }
	void GetRay(float x, float y, osg::Vec3f& vPickRayOrig, osg::Vec3f& vPickRayDir);
	void InitOSG();
	void InitCameraConfig();
	void InitSceneGraph(void);
	void InitManipulators(void);
	void ImplicitSmooth();
	void PreFrameUpdate();
private:
	ShapeDrawable_sptr AddCylinderBetweenPoints(osg::Vec3 StartPoint, osg::Vec3 EndPoint, float radius); 
	void InternalSimplification();
	void InternalUpdateMesh();
	void InternalClearVertexes();
	void InternalClearEdges();
	void InternalClearFaces();
};
