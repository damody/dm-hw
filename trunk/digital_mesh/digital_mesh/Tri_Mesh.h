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

//指定特別畫出面的資料結構
struct sp_f 
{
	OpenMesh::FaceHandle fh;
	float r, g, b;
};
//指定特別畫出頂點的資料結構
struct sp_v 
{
	OpenMesh::EdgeHandle vh;
	float r, g, b;
};
//指定另外畫出位置的資料結構
struct sp_p
{
	BasicMesh::Point pt;
	float r, g, b;
};
bool IntersectLineTriangle( osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& a, osg::Vec3f& b, osg::Vec3f& c, osg::Vec3f & point );
class Tri_Mesh : public BasicMesh
{
public:
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
	bool SaveFile(std::string _fileName);//儲存mesh資料;
	bool SelectPoint(osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& out);
	bool SelectVertex(osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& out);
	bool SelectEdge(osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& out1, osg::Vec3f& out2);
	bool SelectFace(osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& out1, osg::Vec3f& out2, osg::Vec3f& out3);
};

