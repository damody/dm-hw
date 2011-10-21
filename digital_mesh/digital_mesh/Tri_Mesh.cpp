
#include "Tri_Mesh.h"

bool IntersectLineTriangle( const osg::Vec3f& p, const osg::Vec3f& q, const osg::Vec3f& a, const osg::Vec3f& b, const osg::Vec3f& c, osg::Vec3f & point )
{
	osg::Vec3f pq = q - p;
	osg::Vec3f pa = a - p;
	osg::Vec3f pb = b - p;
	osg::Vec3f pc = c - p;
	float u, v, w;
	u = pq*(pc^pb);
	if (u < 0) return 0;
	v = pq*(pa^pc);
	if (v < 0) return 0;
	w = pq*(pb^pa);
	if (w < 0) return 0;
	float denom = 1.0f / (u+v+w);
	u*= denom;
	v*= denom;
	w*= denom;
	point = a*u+b*v+c*w;
	return 1;
}

bool Tri_Mesh::ReadFile( std::string _fileName ) /*讀取mesh資料 */
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

bool Tri_Mesh::SaveFile( std::string _fileName ) /*儲存mesh資料 */
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

bool Tri_Mesh::SelectPoint( osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& out )
{
	FIter f_it;
	FVIter	fv_it;
	osg::Vec3f face[3], result;
	for (f_it = faces_begin(); f_it != faces_end(); ++f_it) 
	{
		int i=0;
		for (fv_it = fv_iter( f_it ); fv_it; ++fv_it, ++i)
		{
			const Point& dp = point(fv_it.handle());
			face[i][0] = dp[0];
			face[i][1] = dp[1];
			face[i][2] = dp[2];
		}
		int ret = IntersectLineTriangle(p, q, face[0], face[1], face[2], result);
		if (ret == 1)
		{
			out = result;
			return true;
		}
	}
	return false;
}

bool Tri_Mesh::SelectVertex( osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& out )
{
	FIter f_it;
	FVIter	fv_it;
	osg::Vec3f face[3], result;
	for (f_it = faces_begin(); f_it != faces_end(); ++f_it) 
	{
		int i=0;
		for (fv_it = fv_iter( f_it ); fv_it; ++fv_it, ++i)
		{
			const Point& dp = point(fv_it.handle());
			face[i][0] = dp[0];
			face[i][1] = dp[1];
			face[i][2] = dp[2];
		}
		bool ret = IntersectLineTriangle(p, q, face[0], face[1], face[2], result);
		if (ret)
		{
			out = result;
			float min_dis = 99999999.0f;
			for(VIter v_itr = vertices_begin();v_itr != vertices_end(); ++v_itr)
			{
				const Point& dp = point(v_itr);
				osg::Vec3f pos;
				pos[0] = dp[0];
				pos[1] = dp[1];
				pos[2] = dp[2];
				float tmp = (pos-result).length2();
				if (tmp < min_dis)
				{
					min_dis = tmp;
					out = pos;
				}
			}
			return true;
		}
	}
	return false;
}

bool Tri_Mesh::SelectEdge( osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& out1, osg::Vec3f& out2 )
{
	FIter f_it;
	FVIter	fv_it;
	osg::Vec3f face[3], c;
	for (f_it = faces_begin(); f_it != faces_end(); ++f_it) 
	{
		int i=0;
		for (fv_it = fv_iter( f_it ); fv_it; ++fv_it, ++i)
		{
			const Point& dp = point(fv_it.handle());
			face[i][0] = dp[0];
			face[i][1] = dp[1];
			face[i][2] = dp[2];
		}
		bool ret = IntersectLineTriangle(p, q, face[0], face[1], face[2], c);
		if (ret)
		{
			float min_dis = 99999999.0f, tmp;
			BasicMesh::EdgeIter e_it;
			BasicMesh::HalfedgeHandle _hedge;
			for(e_it = edges_begin(); e_it != edges_end(); ++e_it)
			{
				_hedge = halfedge_handle(e_it.handle(),1);
				const Tri_Mesh::Point& p1 = point(from_vertex_handle(_hedge));
				const Tri_Mesh::Point& p2 = point(to_vertex_handle(_hedge));
				osg::Vec3f a, b, ab, ac, bc;
				for (int j=0;j<3;++j)
				{
					a[j] = p1[j];
					b[j] = p2[j];
				}
				ab = b-a;
				ac = c-a;
				bc = c-b;
				float e = ac*ab;
				if (e <= 0.0f) 
					tmp = ac*ac;
				else
				{
					float f = ab*ab;
					if (e >= f) 
						tmp = bc*bc;
					else
					{
						tmp = ac*ac - e * e / f;
					}
				}
				if (tmp < min_dis)
				{
					min_dis = tmp;
					out1 = a;
					out2 = b;
				}
			}
			return true;
		}
	}
	return false;
}

bool Tri_Mesh::SelectFace( osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& out1, osg::Vec3f& out2, osg::Vec3f& out3 )
{
	FIter f_it;
	FVIter	fv_it;
	osg::Vec3f face[3], c;
	for (f_it = faces_begin(); f_it != faces_end(); ++f_it) 
	{
		int i=0;
		for (fv_it = fv_iter( f_it ); fv_it; ++fv_it, ++i)
		{
			const Point& dp = point(fv_it.handle());
			face[i][0] = dp[0];
			face[i][1] = dp[1];
			face[i][2] = dp[2];
		}
		int ret = IntersectLineTriangle(p, q, face[0], face[1], face[2], c);
		if (ret)
		{
			out1 = face[0];
			out2 = face[1];
			out3 = face[2];
			return true;
		}
	}
	return false;
}

bool Tri_Mesh::SelectVertexRingVertex( osg::Vec3f& p, osg::Vec3f& q, sPoints& out )
{
	VIter f_it;
	if (GetVertexHandle(p, q, f_it))
	{
		for(BasicMesh::VertexVertexIter vv_it = vv_iter(f_it); vv_it ; ++vv_it )
		{
			osg::Vec3f tmp;
			const Point& p = point(vv_it.handle());
			for (int j=0;j<3;++j)
			{
				tmp[j] = p[j];
			}
			out.push_back(tmp);
		}
		return true;
	}
	return false;
}

bool Tri_Mesh::SelectVertexRingEdge( osg::Vec3f& p, osg::Vec3f& q, sLines& out )
{
	VIter v_it;
	if (GetVertexHandle(p, q, v_it))
	{
		for(BasicMesh::VertexEdgeIter ve_itr = ve_iter(v_it); ve_itr ; ++ve_itr )
		{
			BasicMesh::HalfedgeHandle _hedge = halfedge_handle(ve_itr.handle(),1);
			osg::Vec3f tmp1, tmp2;
			const Point& p1 = point(from_vertex_handle(_hedge));
			const Point& p2 = point(to_vertex_handle(_hedge));
			for (int j=0;j<3;++j)
			{
				tmp1[j] = p1[j];
				tmp2[j] = p2[j];
			}
			out.push_back(tmp1);
			out.push_back(tmp2);
		}
		return true;
	}
	return false;
}

bool Tri_Mesh::SelectVertexRingFace( osg::Vec3f& p, osg::Vec3f& q, sFaces& out )
{
	VIter f_it;
	if (GetVertexHandle(p, q, f_it))
	{
		for(BasicMesh::VertexFaceIter vf_itr = vf_iter(f_it); vf_itr ; ++vf_itr )
		{
			osg::Vec3f t[3];
			int j=0;
			for (FVIter fv_it = fv_iter( vf_itr ); fv_it; ++fv_it, ++j)
			{
				const Point& p = point(fv_it.handle());
				t[j][0] = p[0];
				t[j][1] = p[1];
				t[j][2] = p[2];
				out.push_back(t[j]);
			}
		}
		return true;
	}
	return false;
}

bool Tri_Mesh::SelectEdgeRingVertex( osg::Vec3f& p, osg::Vec3f& q, sPoints& out )
{
	EIter iter;
	if (GetEdgeHandle(p, q, iter))
	{
		BasicMesh::HalfedgeHandle _hedge = halfedge_handle(iter.handle(),1);
		for(BasicMesh::VertexVertexIter vv_it = vv_iter(from_vertex_handle(_hedge)); vv_it ; ++vv_it )
		{
			osg::Vec3f tmp;
			const Point& p = point(vv_it.handle());
			for (int j=0;j<3;++j)
			{
				tmp[j] = p[j];
			}
			out.push_back(tmp);
		}
		for(BasicMesh::VertexVertexIter vv_it = vv_iter(to_vertex_handle(_hedge)); vv_it ; ++vv_it )
		{
			osg::Vec3f tmp;
			const Point& p = point(vv_it.handle());
			for (int j=0;j<3;++j)
			{
				tmp[j] = p[j];
			}
			out.push_back(tmp);
		}
		return true;
	}
	return false;
}

bool Tri_Mesh::SelectEdgeRingEdge( osg::Vec3f& p, osg::Vec3f& q, sLines& out )
{
	EIter iter;
	if (GetEdgeHandle(p, q, iter))
	{
		BasicMesh::HalfedgeHandle _hedge = halfedge_handle(iter.handle(),1);
		for(BasicMesh::VertexEdgeIter ve_itr = ve_iter(from_vertex_handle(_hedge)); ve_itr ; ++ve_itr )
		{
			BasicMesh::HalfedgeHandle _hedge2 = halfedge_handle(ve_itr.handle(),1);
			osg::Vec3f tmp1, tmp2;
			const Point& p1 = point(from_vertex_handle(_hedge2));
			const Point& p2 = point(to_vertex_handle(_hedge2));
			for (int j=0;j<3;++j)
			{
				tmp1[j] = p1[j];
				tmp2[j] = p2[j];
			}
			out.push_back(tmp1);
			out.push_back(tmp2);
		}
		for(BasicMesh::VertexEdgeIter ve_itr = ve_iter(to_vertex_handle(_hedge)); ve_itr ; ++ve_itr )
		{
			BasicMesh::HalfedgeHandle _hedge2 = halfedge_handle(ve_itr.handle(),1);
			osg::Vec3f tmp1, tmp2;
			const Point& p1 = point(from_vertex_handle(_hedge2));
			const Point& p2 = point(to_vertex_handle(_hedge2));
			for (int j=0;j<3;++j)
			{
				tmp1[j] = p1[j];
				tmp2[j] = p2[j];
			}
			out.push_back(tmp1);
			out.push_back(tmp2);
		}
		return true;
	}
	return false;
}

bool Tri_Mesh::SelectEdgeRingFace( osg::Vec3f& p, osg::Vec3f& q, sFaces& out )
{
	EIter iter;
	if (GetEdgeHandle(p, q, iter))
	{
		BasicMesh::HalfedgeHandle _hedge = halfedge_handle(iter.handle(),1);
		for(BasicMesh::VertexFaceIter vf_itr = vf_iter(from_vertex_handle(_hedge)); vf_itr ; ++vf_itr )
		{
			osg::Vec3f t[3];
			int j=0;
			for (FVIter fv_it = fv_iter( vf_itr ); fv_it; ++fv_it, ++j)
			{
				const Point& p = point(fv_it.handle());
				t[j][0] = p[0];
				t[j][1] = p[1];
				t[j][2] = p[2];
				out.push_back(t[j]);
			}
		}
		for(BasicMesh::VertexFaceIter vf_itr = vf_iter(to_vertex_handle(_hedge)); vf_itr ; ++vf_itr )
		{
			osg::Vec3f t[3];
			int j=0;
			for (FVIter fv_it = fv_iter( vf_itr ); fv_it; ++fv_it, ++j)
			{
				const Point& p = point(fv_it.handle());
				t[j][0] = p[0];
				t[j][1] = p[1];
				t[j][2] = p[2];
				out.push_back(t[j]);
			}
		}
		return true;
	}
	return false;
}

bool Tri_Mesh::SelectFaceRingVertex( osg::Vec3f& p, osg::Vec3f& q, sPoints& out )
{
	FIter iter;
	if (GetFaceHandle(p, q, iter))
	{
		for(FVIter fv_it = fv_iter(iter); fv_it ; ++fv_it )
		{
			osg::Vec3f tmp;
			const Point& p = point(fv_it.handle());
			for (int j=0;j<3;++j)
			{
				tmp[j] = p[j];
			}
			out.push_back(tmp);
		}
		return true;
	}
	return false;
}

bool Tri_Mesh::SelectFaceRingEdge( osg::Vec3f& p, osg::Vec3f& q, sLines& out )
{
	FIter iter;
	if (GetFaceHandle(p, q, iter))
	{
		for(FEIter fe_itr = fe_iter(iter) ; fe_itr; ++fe_itr)
		{
			BasicMesh::HalfedgeHandle _hedge = halfedge_handle(fe_itr.handle(),1);
			osg::Vec3f tmp1, tmp2;
			const Point& p1 = point(from_vertex_handle(_hedge));
			const Point& p2 = point(to_vertex_handle(_hedge));
			for (int j=0;j<3;++j)
			{
				tmp1[j] = p1[j];
				tmp2[j] = p2[j];
			}
			out.push_back(tmp1);
			out.push_back(tmp2);
		}
		return true;
	}
	return false;
}

bool Tri_Mesh::SelectFaceRingFace( osg::Vec3f& p, osg::Vec3f& q, sFaces& out )
{
	FIter iter;
	if (GetFaceHandle(p, q, iter))
	{
		for(FFIter ff_it = ff_iter(iter); ff_it ; ++ff_it )
		{
			osg::Vec3f t[3];
			int j=0;
			for (FVIter fv_it = fv_iter( ff_it ); fv_it; ++fv_it, ++j)
			{
				const Point& dp = point(fv_it.handle());
				t[j][0] = dp[0];
				t[j][1] = dp[1];
				t[j][2] = dp[2];
				out.push_back(t[j]);
			}
		}
		return true;
	}
	return false;
}

bool Tri_Mesh::GetVertexHandle( osg::Vec3f& p, osg::Vec3f& q, VIter& iter )
{
	FIter f_it;
	FVIter	fv_it;
	osg::Vec3f face[3], result;
	for (f_it = faces_begin(); f_it != faces_end(); ++f_it) 
	{
		int i=0;
		for (fv_it = fv_iter( f_it ); fv_it; ++fv_it, ++i)
		{
			const Point& dp = point(fv_it.handle());
			face[i][0] = dp[0];
			face[i][1] = dp[1];
			face[i][2] = dp[2];
		}
		bool ret = IntersectLineTriangle(p, q, face[0], face[1], face[2], result);
		if (ret)
		{
			float min_dis = 99999999.0f;
			for(VIter v_itr = vertices_begin();v_itr != vertices_end(); ++v_itr)
			{
				const Point& dp = point(v_itr);
				osg::Vec3f pos;
				pos[0] = dp[0];
				pos[1] = dp[1];
				pos[2] = dp[2];
				float tmp = (pos-result).length2();
				if (tmp < min_dis)
				{
					min_dis = tmp;
					iter = v_itr;
				}
			}
			return true;
		}
	}
	return false;
}


bool Tri_Mesh::GetEdgeHandle( osg::Vec3f& p, osg::Vec3f& q, EIter& iter )
{
	FIter f_it;
	FVIter	fv_it;
	osg::Vec3f face[3], c;
	for (f_it = faces_begin(); f_it != faces_end(); ++f_it) 
	{
		int i=0;
		for (fv_it = fv_iter( f_it ); fv_it; ++fv_it, ++i)
		{
			const Point& dp = point(fv_it.handle());
			face[i][0] = dp[0];
			face[i][1] = dp[1];
			face[i][2] = dp[2];
		}
		bool ret = IntersectLineTriangle(p, q, face[0], face[1], face[2], c);
		if (ret)
		{
			float min_dis = 99999999.0f, tmp;
			BasicMesh::EdgeIter e_it;
			BasicMesh::HalfedgeHandle _hedge;
			for(e_it = edges_begin(); e_it != edges_end(); ++e_it)
			{
				_hedge = halfedge_handle(e_it.handle(),1);
				const Tri_Mesh::Point& p1 = point(from_vertex_handle(_hedge));
				const Tri_Mesh::Point& p2 = point(to_vertex_handle(_hedge));
				osg::Vec3f a, b, ab, ac, bc;
				for (int j=0;j<3;++j)
				{
					a[j] = p1[j];
					b[j] = p2[j];
				}
				ab = b-a;
				ac = c-a;
				bc = c-b;
				float e = ac*ab;
				if (e <= 0.0f) 
					tmp = ac*ac;
				else
				{
					float f = ab*ab;
					if (e >= f) 
						tmp = bc*bc;
					else
					{
						tmp = ac*ac - e * e / f;
					}
				}
				if (tmp < min_dis)
				{
					min_dis = tmp;
					iter = e_it;
				}
			}
			return true;
		}
	}
	return false;
}


bool Tri_Mesh::GetFaceHandle( osg::Vec3f& p, osg::Vec3f& q, FIter& iter )
{
	FIter f_it;
	FVIter	fv_it;
	osg::Vec3f face[3], result;
	for (f_it = faces_begin(); f_it != faces_end(); ++f_it) 
	{
		int i=0;
		for (fv_it = fv_iter( f_it ); fv_it; ++fv_it, ++i)
		{
			const Point& dp = point(fv_it.handle());
			face[i][0] = dp[0];
			face[i][1] = dp[1];
			face[i][2] = dp[2];
		}
		bool ret = IntersectLineTriangle(p, q, face[0], face[1], face[2], result);
		if (ret)
		{
			iter = f_it;
			return true;
		}
	}
	return false;
}

BasicMesh::VertexHandle Tri_Mesh::AddVertex( Point _p )
{
	int find_result = FindVertex(_p);
	if (find_result != -1)
	{
		return vertex_handle(find_result);
	}
	else
	{
		return add_vertex(_p);
	}
}

BasicMesh::VertexIter Tri_Mesh::GetVIterFormIndex( int idx )
{
	VIter it = vertices_begin();
	for (int i=0;i<idx && it!=vertices_end();++it, ++i);
	return it;
}

int Tri_Mesh::FindVertex( float x, float y, float z )
{
	return FindVertex(Point(x, y, z));
}

int Tri_Mesh::FindVertex( Point _p )
{
	for( VIter v_itr = vertices_begin(); v_itr != vertices_end(); ++v_itr)
		if( point(v_itr) == _p )
			return v_itr.handle().idx();
	return -1;
}

BasicMesh::FaceHandle Tri_Mesh::addFace( BasicMesh::VHandle _v0, BasicMesh::VHandle _v1, BasicMesh::VHandle _v2, BasicMesh::VHandle _v3 )
{
	std::vector<BasicMesh::VHandle> face_vhandles;

	face_vhandles.clear();
	face_vhandles.push_back(_v0);
	face_vhandles.push_back(_v1);
	face_vhandles.push_back(_v2);
	face_vhandles.push_back(_v3);
	return add_face(face_vhandles);
}

void Tri_Mesh::deleteFace( BasicMesh::FaceHandle _f )
{
	delete_face(_f);
	garbage_collection();
}

void Tri_Mesh::deleteFace( VHandle _v0, VHandle _v1, VHandle _v2, VHandle _v3 )
{
	/* 
	v1				v0
	*<--------------*
	|				|
	|				|
	|				|
	|		f		|
	|				|
	|				|
	|				|
	* --------------*
	v2				v3
	*/
	HalfedgeHandle v0v1 = find_halfedge(_v0, _v1);
	if (v0v1.is_valid())
	{
		FHandle fh = face_handle(v0v1);
		if (fh.is_valid())
		{
			delete_face(fh);
			garbage_collection();
		}
	}
}

bool Tri_Mesh::IsVertexVertex( VHandle _vj, VHandle _vi )
{
	for( VVIter vvit = vv_iter(_vi) ; vvit ; ++vvit )
		if( vvit.handle() == _vj )
			return true;
	return false;
}
