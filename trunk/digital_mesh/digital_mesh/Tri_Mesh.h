#pragma once
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#include <OpenMesh/Tools/Utils/getopt.h>
#include <vector>
#include <osg/Vec3f>
#include <osg/Vec3d>
#include <string>
#include <osg/Array>
#include <osg/Matrixf>

struct BasicTraits : public OpenMesh::DefaultTraits
{
	typedef OpenMesh::Vec3d Point;
	typedef OpenMesh::Vec3d Normal;
	// add normal property to vertices and faces
	VertexAttributes(OpenMesh::Attributes::Normal);
	FaceAttributes  (OpenMesh::Attributes::Normal);
};
typedef OpenMesh::TriMesh_ArrayKernelT<BasicTraits> BasicMesh;

typedef osg::Vec3Array sLines;
typedef osg::Vec3Array sFaces;
typedef osg::Vec3Array sPoints;
typedef osg::Vec4Array sColors;
typedef std::vector<osg::Vec3f> Vec3fs;

struct QMatrix
{
	QMatrix(){}
	QMatrix(const BasicMesh::VHandle& _handle, const osg::Matrixf& _mat)
		:handle(_handle), mat(_mat)
	{}
	BasicMesh::VHandle	handle;
	osg::Matrixf		mat;
};
typedef std::vector<QMatrix> QMatrixs;
struct QEdge
{
	QEdge(){}
	QEdge(BasicMesh::EHandle& _handle, float _qv)
		:handle(_handle), qv(_qv)
	{}
	BasicMesh::EHandle	handle;
	float			qv;
};
typedef std::vector<QEdge> QEdges;
typedef std::vector<BasicMesh::Point> BMPoints;

bool IntersectLineTriangle( const osg::Vec3f& p, const osg::Vec3f& q, const osg::Vec3f& a, const osg::Vec3f& b, const osg::Vec3f& c, osg::Vec3f & point );
float SqDistPointSegment( const osg::Vec3f& a, const osg::Vec3f& b, const osg::Vec3f& c );

class Tri_Mesh : public BasicMesh
{
public:
	QMatrixs	mQMatrixs;
	QEdges		mQEdges;
	BMPoints	mDontMove;
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
	virtual bool ReadFile(std::string _fileName);//Ū��mesh���;
	virtual bool SaveFile(std::string _fileName);//�x�smesh���;`
	virtual bool SelectPoint(const osg::Vec3f& p, const osg::Vec3f& q, osg::Vec3f& out);
	virtual bool SelectVertex(const osg::Vec3f& p, const osg::Vec3f& q, osg::Vec3f& out);
	virtual bool SelectEdge(const osg::Vec3f& p, const osg::Vec3f& q, osg::Vec3f& out1, osg::Vec3f& out2);
	virtual bool SelectFace(const osg::Vec3f& p, const osg::Vec3f& q, osg::Vec3f& out1, osg::Vec3f& out2, osg::Vec3f& out3);

	virtual bool SelectVertexRingVertex(const osg::Vec3f& p, const osg::Vec3f& q, sPoints& out);
	virtual bool SelectVertexRingEdge(const osg::Vec3f& p, const osg::Vec3f& q, sLines& out);
	virtual bool SelectVertexRingFace(const osg::Vec3f& p, const osg::Vec3f& q, sFaces& out);
	typedef std::vector<VertexHandle> VertexHandles;
	virtual bool SelectVertexRingVertex( VertexHandle f_it, VertexHandles& out );

	virtual bool SelectEdgeRingVertex(const osg::Vec3f& p, const osg::Vec3f& q, sPoints& out);
	virtual bool SelectEdgeRingEdge(const osg::Vec3f& p, const osg::Vec3f& q, sLines& out);
	virtual bool SelectEdgeRingFace(const osg::Vec3f& p, const osg::Vec3f& q, sFaces& out);
	virtual bool SelectEdgeRingVertex(BasicMesh::EHandle eh, sPoints& out);

	virtual bool SelectFaceRingVertex(const osg::Vec3f& p, const osg::Vec3f& q, sPoints& out);
	virtual bool SelectFaceRingEdge(const osg::Vec3f& p, const osg::Vec3f& q, sLines& out);
	virtual bool SelectDontMoveFace(const osg::Vec3f& p, const osg::Vec3f& q, sFaces& out);
	virtual bool SelectFaceRingFace(const osg::Vec3f& p, const osg::Vec3f& q, sFaces& out);

	virtual bool GetVertexHandle(const osg::Vec3f& p, const osg::Vec3f& q, VertexHandle& iter);
	virtual bool GetEdgeHandle( const osg::Vec3f& p, const osg::Vec3f& q, EdgeHandle& iter );
	virtual bool GetFaceHandle( const osg::Vec3f& p, const osg::Vec3f& q, FaceHandle& iter );

	double	ComputeFaceArea(FaceHandle& iter);
	double	AverageFaceArea();
	double	TotalFaceArea();

	virtual bool GetAllRayTracePoints(const osg::Vec3f& p, const osg::Vec3f& q, Vec3fs& positive, Vec3fs& negative);
	virtual bool GetAllRayTraceNode(const osg::Vec3f& p, const osg::Vec3f& q, Vec3fs& nodes);
	
	bool IsConvexQuad(osg::Vec3f& a, osg::Vec3f& b, osg::Vec3f& c, osg::Vec3f& d);
	bool IsConvexPolygon(sPoints& pts);
	void MeshSimplification( int level, bool convex_check );
	// mesh control
	VHandle AddVertex(Point _p);
	VIter GetVIterFormIndex(int idx);
	int FindVertex(float x, float y, float z);
	int FindVertex(Point _p);
	//�bmodel�W�W�[�s����
	FHandle AddFace(VHandle _v0, VHandle _v1, VHandle _v2, VHandle _v3);
	//�bmodel�W�R����
	void DeleteFace(FHandle _f);
	void DeleteFace(VHandle _v0, VHandle _v1, VHandle _v2, VHandle _v3);
	bool GetEdgeHandleFromPoints(const osg::Vec3f& p, const osg::Vec3f& q, BasicMesh::HalfedgeHandle& iter );
	void DeleteEdge(HalfedgeHandle _e0);
	//�ˬd�⳻�I�O�_�۾F
	bool IsVertexVertex( VHandle _vj, VHandle _vi);
};

