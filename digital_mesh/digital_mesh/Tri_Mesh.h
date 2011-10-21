#pragma once
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#include <OpenMesh/Tools/Utils/getopt.h>
#include <vector>
#include <osg/Vec3f>
#include <string>

struct BasicTraits : public OpenMesh::DefaultTraits
{
	typedef OpenMesh::Vec3f Point;
	typedef OpenMesh::Vec3f Normal;
	// add normal property to vertices and faces
	VertexAttributes(OpenMesh::Attributes::Normal);
	FaceAttributes  (OpenMesh::Attributes::Normal);
};
typedef OpenMesh::TriMesh_ArrayKernelT<BasicTraits> BasicMesh;

struct sLine
{
	sLine(){}
	sLine(const osg::Vec3f& _a, const osg::Vec3f& _b)
		:a(_a), b(_b)
	{}
	osg::Vec3f a, b;
};
struct sFace
{
	sFace(){}
	sFace(const osg::Vec3f& _a, const osg::Vec3f& _b, const osg::Vec3f& _c)
		:a(_a), b(_b), c(_c)
	{}
	osg::Vec3f a, b, c;
};
typedef std::vector<sLine> sLines;
typedef std::vector<sFace> sFaces;
typedef std::vector<osg::Vec3f> sPoints;

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
	~Tri_Mesh()
	{
		release_vertex_status();
		release_edge_status();
		release_face_status();
	}
	bool ReadFile(std::string _fileName);//讀取mesh資料;
	bool SaveFile(std::string _fileName);//儲存mesh資料;`
	bool SelectPoint(osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& out);
	bool SelectVertex(osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& out);
	bool SelectEdge(osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& out1, osg::Vec3f& out2);
	bool SelectFace(osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& out1, osg::Vec3f& out2, osg::Vec3f& out3);

	bool SelectVertexRingVertex(osg::Vec3f& p, osg::Vec3f& q, sPoints& out);
	bool SelectVertexRingEdge(osg::Vec3f& p, osg::Vec3f& q, sLines& out);
	bool SelectVertexRingFace(osg::Vec3f& p, osg::Vec3f& q, sFaces& out);

	bool SelectEdgeRingVertex(osg::Vec3f& p, osg::Vec3f& q, sPoints& out);
	bool SelectEdgeRingEdge(osg::Vec3f& p, osg::Vec3f& q, sLines& out);
	bool SelectEdgeRingFace(osg::Vec3f& p, osg::Vec3f& q, sFaces& out);

	bool SelectFaceRingVertex(osg::Vec3f& p, osg::Vec3f& q, sPoints& out);
	bool SelectFaceRingEdge(osg::Vec3f& p, osg::Vec3f& q, sLines& out);
	bool SelectFaceRingFace(osg::Vec3f& p, osg::Vec3f& q, sFaces& out);

	bool GetVertexHandle(osg::Vec3f& p, osg::Vec3f& q, VIter& iter);
	bool GetEdgeHandle( osg::Vec3f& p, osg::Vec3f& q, EIter& iter );
	bool GetFaceHandle( osg::Vec3f& p, osg::Vec3f& q, FIter& iter );

	// mesh control
	BasicMesh::VertexHandle AddVertex(Point _p);
	VIter GetVIterFormIndex(int idx);
	int FindVertex(float x, float y, float z);
	int FindVertex(Point _p);
	//在model上增加新的面
	FHandle addFace(VHandle _v0, VHandle _v1, VHandle _v2, VHandle _v3);
	//在model上刪除面
	void deleteFace(FHandle _f);
	void deleteFace(VHandle _v0, VHandle _v1, VHandle _v2, VHandle _v3);
	//檢查兩頂點是否相鄰
	bool IsVertexVertex( VHandle _vj, VHandle _vi);
};

