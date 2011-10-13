#pragma once
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#include <OpenMesh/Tools/Utils/getopt.h>
#include <vector>

struct BasicTraits : public OpenMesh::DefaultTraits
{
	typedef OpenMesh::Vec3f Point;
	typedef OpenMesh::Vec3f Normal;
	// add normal property to vertices and faces
	VertexAttributes(OpenMesh::Attributes::Normal);
	FaceAttributes  (OpenMesh::Attributes::Normal);
};
typedef OpenMesh::TriMesh_ArrayKernelT<BasicTraits> BasicMesh;

//���w�S�O�e�X������Ƶ��c
struct sp_f 
{
	OpenMesh::FaceHandle fh;
	float r, g, b;
};
//���w�S�O�e�X���I����Ƶ��c
struct sp_v 
{
	OpenMesh::EdgeHandle vh;
	float r, g, b;
};
//���w�t�~�e�X��m����Ƶ��c
struct sp_p
{
	BasicMesh::Point pt;
	float r, g, b;
};

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
	bool ReadFile(std::string _fileName)//Ū��mesh���
	{
		bool isRead = false;
		OpenMesh::IO::Options opt;
		if ( OpenMesh::IO::read_mesh(*this, _fileName, opt) )
		{
			//read mesh from filename OK!
			isRead = true;
		}
		if(isRead)
		{
			// If the file did not provide vertex normals and mesh has vertex normal ,then calculate them
			if (!opt.check( OpenMesh::IO::Options::VertexNormal ) && has_vertex_normals())
			{
				update_normals();
			}
		}
		return isRead;
	}
	bool SaveFile(std::string _fileName)//�x�smesh���
	{
		bool isSave = false;
		OpenMesh::IO::Options opt;
		if ( OpenMesh::IO::write_mesh(*this, _fileName, opt) )
		{
			//read mesh from filename OK!
			isSave = true;
		}
		return isSave;
	}
};

