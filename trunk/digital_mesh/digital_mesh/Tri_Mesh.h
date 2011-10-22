#pragma once
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#include <OpenMesh/Tools/Utils/getopt.h>
#include <vector>
#include <osg/Vec3f>
#include <string>
#include <osg/Array>

struct BasicTraits : public OpenMesh::DefaultTraits
{
	typedef OpenMesh::Vec3f Point;
	typedef OpenMesh::Vec3f Normal;
	// add normal property to vertices and faces
	VertexAttributes(OpenMesh::Attributes::Normal);
	FaceAttributes  (OpenMesh::Attributes::Normal);
};
typedef OpenMesh::TriMesh_ArrayKernelT<BasicTraits> BasicMesh;

typedef osg::Vec3Array sLines;
typedef osg::Vec3Array sFaces;
typedef osg::Vec3Array sPoints;
typedef osg::Vec4Array sColors;

bool IntersectLineTriangle( const osg::Vec3f& p, const osg::Vec3f& q, const osg::Vec3f& a, const osg::Vec3f& b, const osg::Vec3f& c, osg::Vec3f & point );

class Tri_Mesh : public BasicMesh
{
public:
	enum Type
	{
		POINT	= 1,
		VERTEX	= 2,
		FACE	= 8,
		EDGE = 16,
		RINGVERTEX	= 32,
		RINGFACE	= 64,
		RINGEDGE	= 128
	};
	Tri_Mesh()
	{
		request_vertex_status();
		request_edge_status();
		request_face_status();
	}
	virtual ~Tri_Mesh()
	{
		release_vertex_status();
		release_edge_status();
		release_face_status();
	}
	virtual bool ReadFile(std::string _fileName);//讀取mesh資料;
	virtual bool SaveFile(std::string _fileName);//儲存mesh資料;`
	virtual bool SelectPoint(osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& out);
	virtual bool SelectVertex(osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& out);
	virtual bool SelectEdge(osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& out1, osg::Vec3f& out2);
	virtual bool SelectFace(osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& out1, osg::Vec3f& out2, osg::Vec3f& out3);

	virtual bool SelectVertexRingVertex(osg::Vec3f& p, osg::Vec3f& q, sPoints& out);
	virtual bool SelectVertexRingEdge(osg::Vec3f& p, osg::Vec3f& q, sLines& out);
	virtual bool SelectVertexRingFace(osg::Vec3f& p, osg::Vec3f& q, sFaces& out);

	virtual bool SelectEdgeRingVertex(osg::Vec3f& p, osg::Vec3f& q, sPoints& out);
	virtual bool SelectEdgeRingEdge(osg::Vec3f& p, osg::Vec3f& q, sLines& out);
	virtual bool SelectEdgeRingFace(osg::Vec3f& p, osg::Vec3f& q, sFaces& out);

	virtual bool SelectFaceRingVertex(osg::Vec3f& p, osg::Vec3f& q, sPoints& out);
	virtual bool SelectFaceRingEdge(osg::Vec3f& p, osg::Vec3f& q, sLines& out);
	virtual bool SelectFaceRingFace(osg::Vec3f& p, osg::Vec3f& q, sFaces& out);

	virtual bool GetVertexHandle(osg::Vec3f& p, osg::Vec3f& q, VertexHandle& iter);
	virtual bool GetEdgeHandle( osg::Vec3f& p, osg::Vec3f& q, EdgeHandle& iter );
	virtual bool GetFaceHandle( osg::Vec3f& p, osg::Vec3f& q, FaceHandle& iter );
	
	// mesh control
	VHandle AddVertex(Point _p);
	VIter GetVIterFormIndex(int idx);
	int FindVertex(float x, float y, float z);
	int FindVertex(Point _p);
	//在model上增加新的面
	FHandle AddFace(VHandle _v0, VHandle _v1, VHandle _v2, VHandle _v3);
	//在model上刪除面
	void DeleteFace(FHandle _f);
	void DeleteFace(VHandle _v0, VHandle _v1, VHandle _v2, VHandle _v3);
	bool GetEdgeHandleFromPoints(const osg::Vec3f& p, const osg::Vec3f& q, BasicMesh::HalfedgeHandle& iter );
	void DeleteEdge(HalfedgeHandle _e0);
	//檢查兩頂點是否相鄰
	bool IsVertexVertex( VHandle _vj, VHandle _vi);
};

