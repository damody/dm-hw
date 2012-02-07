
#include "Tri_Mesh.h"
#include <algorithm>
#include <osg\Matrixf>

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

float SqDistPointSegment( const osg::Vec3f& a, const osg::Vec3f& b, const osg::Vec3f& c )
{
	const osg::Vec3f ab = b-a, ac = c-a, bc = c-b;
	float e = ac*ab;
	if (e<=0) return ac*ac;
	float f=ab*ab;
	if (e>=f) return bc*bc;
	return ac*ac-e*e/f;
}

bool Tri_Mesh::ReadFile( std::string _fileName ) /*讀取mesh資料 */
{
	bool isRead = false;
	OpenMesh::IO::Options opt;
	if ( OpenMesh::IO::read_mesh(*this, _fileName, opt) )
	{
		//read mesh from filename OK!
		isRead = true;
		/*
		for (VertexIter v_it=vertices_begin(); v_it!=vertices_end(); ++v_it) 
		{
			const Normal& n = normal(v_it);
			const Point&  p = point(v_it);
			float a = n[0], b = n[1], c = n[2];
			float x = p[0], y = p[1], z = p[2];
			float d = -(a*x+b*y+c*z);
			osg::Matrixf  m(
				a*a,	a*b,	a*c,	a*d,
				a*b,	b*b,	b*c,	b*d,
				a*c,	a*b,	c*c,	c*d,
				a*d,	b*d,	c*d,	d*d,
				);
			mQMatrixs.push_back(QMatrix(v_it.handle(), m));
		}
		*/
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

bool Tri_Mesh::SelectPoint( const osg::Vec3f& p, const osg::Vec3f& q, osg::Vec3f& out )
{
	FIter f_it;
	FVIter	fv_it;
	osg::Vec3f face[3], result;
	float distance_from_p_to_face = -1;
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
			float tmp_dis = (p-result).length2();
			if (tmp_dis<distance_from_p_to_face || distance_from_p_to_face == -1)
			{
				distance_from_p_to_face = tmp_dis;
				out = result;
			}
		}
	}
	if (distance_from_p_to_face != -1)
		return true;
	return false;
}

bool Tri_Mesh::SelectVertex( const osg::Vec3f& p, const osg::Vec3f& q, osg::Vec3f& out )
{
	FIter f_it;
	FVIter	fv_it;
	osg::Vec3f face[3], result;
	float distance_from_p_to_face = -1;
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
			float tmp_dis = (p-result).length2();
			if (tmp_dis<distance_from_p_to_face || distance_from_p_to_face == -1)
			{
				distance_from_p_to_face = tmp_dis;
				float min_dis = -1;
				for (int j=0;j<3;++j)
				{
					float tmp = (face[j]-result).length2();
					if (tmp < min_dis || min_dis == -1)
					{
						min_dis = tmp;
						out = face[j];
					}
				}
			}
		}
	}
	if (distance_from_p_to_face != -1)
		return true;
	return false;
}

bool Tri_Mesh::SelectEdge( const osg::Vec3f& p, const osg::Vec3f& q, osg::Vec3f& out1, osg::Vec3f& out2 )
{
	FIter f_it;
	FVIter	fv_it;
	osg::Vec3f face[3], c;
	float distance_from_p_to_face = -1;
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
			float tmp_dis = (p-c).length2();
			if (tmp_dis<distance_from_p_to_face || distance_from_p_to_face == -1)
			{
				distance_from_p_to_face = tmp_dis;
				float tmp, min_dis=999999.0f;
				for(int j=0;j<3;++j)
				{
					osg::Vec3f a, b, ab, ac, bc;
					a = face[j];
					b = face[(j+1)%3];
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
			}
		}
	}
	if (distance_from_p_to_face != -1)
		return true;
	return false;
}

bool Tri_Mesh::SelectFace( const osg::Vec3f& p, const osg::Vec3f& q, osg::Vec3f& out1, osg::Vec3f& out2, osg::Vec3f& out3 )
{
	FIter f_it;
	FVIter	fv_it;
	osg::Vec3f face[3], c;
	float distance_from_p_to_face = -1;
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
			float tmp_dis = (p-c).length2();
			if (tmp_dis<distance_from_p_to_face || distance_from_p_to_face == -1)
			{
				distance_from_p_to_face = tmp_dis;
				out1 = face[0];
				out2 = face[1];
				out3 = face[2];
			}
		}
	}
	if (distance_from_p_to_face != -1)
		return true;
	return false;
}

bool Tri_Mesh::SelectVertexRingVertex( const osg::Vec3f& p, const osg::Vec3f& q, sPoints& out )
{
	VertexHandle f_it;
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

bool Tri_Mesh::SelectVertexRingVertex( VertexHandle f_it, VertexHandles& out )
{
	for(BasicMesh::VertexVertexIter vv_it = vv_iter(f_it); vv_it ; ++vv_it )
	{
		out.push_back(vv_it.handle());
	}
	return true;
}

bool Tri_Mesh::SelectVertexRingEdge( const osg::Vec3f& p, const osg::Vec3f& q, sLines& out )
{
	VertexHandle v_it;
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

bool Tri_Mesh::SelectVertexRingFace( const osg::Vec3f& p, const osg::Vec3f& q, sFaces& out )
{
	VertexHandle f_it;
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

bool Tri_Mesh::SelectEdgeRingVertex( const osg::Vec3f& p, const osg::Vec3f& q, sPoints& out )
{
	EdgeHandle iter;
	if (GetEdgeHandle(p, q, iter))
	{
		BasicMesh::HalfedgeHandle _hedge = halfedge_handle(iter,1);
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

bool Tri_Mesh::SelectEdgeRingVertex( BasicMesh::EHandle eh, sPoints& out )
{
	BasicMesh::HalfedgeHandle _hedge = halfedge_handle(eh,0);
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
// 	for(BasicMesh::VertexVertexIter vv_it = vv_iter(to_vertex_handle(_hedge)); vv_it ; ++vv_it )
// 	{
// 		osg::Vec3f tmp;
// 		const Point& p = point(vv_it.handle());
// 		for (int j=0;j<3;++j)
// 		{
// 			tmp[j] = p[j];
// 		}
// 		out.push_back(tmp);
// 	}
	return true;
}

bool Tri_Mesh::SelectEdgeRingEdge( const osg::Vec3f& p, const osg::Vec3f& q, sLines& out )
{
	EdgeHandle iter;
	if (GetEdgeHandle(p, q, iter))
	{
		BasicMesh::HalfedgeHandle _hedge = halfedge_handle(iter,1);
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

bool Tri_Mesh::SelectEdgeRingFace( const osg::Vec3f& p, const osg::Vec3f& q, sFaces& out )
{
	EdgeHandle iter;
	if (GetEdgeHandle(p, q, iter))
	{
		BasicMesh::HalfedgeHandle _hedge = halfedge_handle(iter,1);
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

bool Tri_Mesh::SelectFaceRingVertex( const osg::Vec3f& p, const osg::Vec3f& q, sPoints& out )
{
	FaceHandle iter;
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

bool Tri_Mesh::SelectFaceRingEdge( const osg::Vec3f& p, const osg::Vec3f& q, sLines& out )
{
	FaceHandle iter;
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

bool Tri_Mesh::SelectDontMoveFace( const osg::Vec3f& p, const osg::Vec3f& q, sFaces& out)
{
	FaceHandle iter;
	if (GetFaceHandle(p, q, iter))
	{
		osg::Vec3f t[3];
		int j=0;
		for (FVIter fv_it = fv_iter(iter); fv_it; ++fv_it, ++j)
		{
			const Point& dp = point(fv_it.handle());
			t[j][0] = dp[0];
			t[j][1] = dp[1];
			t[j][2] = dp[2];
			out.push_back(t[j]);
		}
		for(FEIter fe_itr = fe_iter(iter) ; fe_itr; ++fe_itr)
		{
			BasicMesh::HalfedgeHandle _hedge = halfedge_handle(fe_itr.handle(),1);
			const Point& p1 = point(from_vertex_handle(_hedge));
			const Point& p2 = point(to_vertex_handle(_hedge));
			mDontMove.push_back(p1);
			mDontMove.push_back(p2);
		}
		return true;
	}
	sort(mDontMove.begin(), mDontMove.end());
	return false;
}

bool Tri_Mesh::SelectFaceRingFace( const osg::Vec3f& p, const osg::Vec3f& q, sFaces& out )
{
	FaceHandle iter;
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

bool Tri_Mesh::GetVertexHandle( const osg::Vec3f& p, const osg::Vec3f& q, VertexHandle& iter )
{
	FIter f_it;
	FVIter	fv_it;
	osg::Vec3f face[3], result;
	float distance_from_p_to_face = -1;
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
			float tmp_dis = (p-result).length2();
			if (tmp_dis<distance_from_p_to_face || distance_from_p_to_face == -1)
			{
				distance_from_p_to_face = tmp_dis;
				float min_dis = -1;
				int j=0;
				for (fv_it = fv_iter( f_it ); fv_it; ++fv_it, ++j)
				{
					float tmp = (face[j]-result).length2();
					if (tmp < min_dis || min_dis == -1)
					{
						min_dis = tmp;
						iter = fv_it.handle();
					}
				}
			}
		}
	}
	if (distance_from_p_to_face != -1)
		return true;
	return false;
}


bool Tri_Mesh::GetEdgeHandle( const osg::Vec3f& p, const osg::Vec3f& q, EdgeHandle& iter )
{
	FIter f_it;
	FVIter	fv_it;
	osg::Vec3f face[3], c;
	float distance_from_p_to_face = -1;
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
			float tmp_dis = (p-c).length2();
			if (tmp_dis<distance_from_p_to_face || distance_from_p_to_face == -1)
			{
				distance_from_p_to_face = tmp_dis;
				float tmp, min_dis=-1;
				for(FEIter fe_itr = fe_iter(f_it) ; fe_itr; ++fe_itr)
				{
					BasicMesh::HalfedgeHandle _hedge = halfedge_handle(fe_itr.handle(),1);
					osg::Vec3f a, b, ab, ac, bc;
					const Point& p1 = point(from_vertex_handle(_hedge));
					const Point& p2 = point(to_vertex_handle(_hedge));
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
					if (tmp < min_dis || min_dis == -1)
					{
						min_dis = tmp;
						iter = fe_itr.handle();
					}
				}
			}
		}
	}
	if (distance_from_p_to_face != -1)
		return true;
	return false;
}


bool Tri_Mesh::GetFaceHandle( const osg::Vec3f& p, const osg::Vec3f& q, FaceHandle& iter )
{
	FIter f_it;
	FVIter	fv_it;
	osg::Vec3f face[3], result;
	float distance_from_p_to_face = -1;
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
			float tmp_dis = (p-result).length2();
			if (tmp_dis<distance_from_p_to_face || distance_from_p_to_face == -1)
			{
				distance_from_p_to_face = tmp_dis;
				iter = f_it;
			}
		}
	}
	if (distance_from_p_to_face != -1)
		return true;
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

BasicMesh::FaceHandle Tri_Mesh::AddFace( BasicMesh::VHandle _v0, BasicMesh::VHandle _v1, BasicMesh::VHandle _v2, BasicMesh::VHandle _v3 )
{
	std::vector<BasicMesh::VHandle> face_vhandles;

	face_vhandles.clear();
	face_vhandles.push_back(_v0);
	face_vhandles.push_back(_v1);
	face_vhandles.push_back(_v2);
	face_vhandles.push_back(_v3);
	return add_face(face_vhandles);
}


void Tri_Mesh::DeleteEdge( BasicMesh::HalfedgeHandle _hedge )
{
	Tri_Mesh::Point& p1 = point(from_vertex_handle(_hedge));
	Tri_Mesh::Point& p2 = point(to_vertex_handle(_hedge));
	Tri_Mesh::Point res = (p1+p2)*0.5f, tp1=p1, tp2=p2;
	p1=p2=res;
	collapse(_hedge);
}

void Tri_Mesh::DeleteFace( BasicMesh::FaceHandle _f )
{
	delete_face(_f);
	garbage_collection();
}

void Tri_Mesh::DeleteFace( VHandle _v0, VHandle _v1, VHandle _v2, VHandle _v3 )
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

bool Tri_Mesh::GetEdgeHandleFromPoints( const osg::Vec3f& a, const osg::Vec3f& b, HalfedgeHandle& iter )
{
	VIter p1 = GetVIterFormIndex(FindVertex(Point(a[0], a[1], a[2])));
	VIter p2 = GetVIterFormIndex(FindVertex(Point(b[0], b[1], b[2])));
	iter = find_halfedge(p1, p2);
	return iter.is_valid();
}

void Tri_Mesh::MeshSimplification( int level, bool convex_check )
{
	/*
	for (VertexIter v_it=vertices_begin(); v_it!=vertices_end(); ++v_it) 
	{
		const Normal& n = normal(v_it);
		const Point&  p = point(v_it);
		float a = n[0], b = n[1], c = n[2];
		float x = p[0], y = p[1], z = p[2];
		float d = -(a*x+b*y+c*z);
		osg::Matrixf  mat(
			a*a,	a*b,	a*c,	a*d,
			a*b,	b*b,	b*c,	b*d,
			a*c,	a*b,	c*c,	c*d,
			a*d,	b*d,	c*d,	d*d
			);
		mQMatrixs.push_back(QMatrix(v_it.handle(), mat));
	}
	*/
	mQEdges.clear();
	for (EdgeIter e_it=edges_begin(); e_it!=edges_end(); ++e_it) 
	{
		mQEdges.push_back(QEdge(e_it.handle(), 1));
	}
	if (((int)mQEdges.size())-level<10)
		return ;
	std::random_shuffle(mQEdges.begin(), mQEdges.end());
	
	osg::ref_ptr<sPoints> sp = new sPoints;
	for (int i=level-1;i >=0;--i)
	{
		HalfedgeHandle hf = halfedge_handle(mQEdges[i].handle, 0);
		if (is_valid_handle(hf) && is_collapse_ok(hf))
		{
			BMPoints::iterator it = find(mDontMove.begin(), mDontMove.end(), 
				point(from_vertex_handle(hf)));
			if (it != mDontMove.end())
				continue;
			it = find(mDontMove.begin(), mDontMove.end(), 
				point(to_vertex_handle(hf)));
			if (it != mDontMove.end())
				continue;
			if (convex_check)
			{
				sp->clear();
				SelectEdgeRingVertex(mQEdges[i].handle, *sp);
				if (IsConvexPolygon(*sp))
					DeleteEdge(hf);
			}
			else
				DeleteEdge(hf);
		}
	}
	garbage_collection();
}

bool Tri_Mesh::IsConvexQuad( osg::Vec3f& a, osg::Vec3f& b, osg::Vec3f& c, osg::Vec3f& d )
{
	osg::Vec3f aa = (d-b) ^ (a-b);
	osg::Vec3f bb = (d-b) ^ (c-b);
	if (aa*bb >= 0) return false;
	aa = (c-a) ^ (d-a);
	bb = (c-a) ^ (b-a);
	if (aa*bb < 0) return true;
	return false;
}

bool Tri_Mesh::IsConvexPolygon( sPoints& pts )
{
	if (pts.size() < 4)
		return true;
	if (pts.size() == 4)
		return IsConvexQuad(pts[0], pts[1], pts[2], pts[3]);
	else
	{
		for (size_t i=0;i+3<pts.size();i++)
		{
			if (false == IsConvexQuad(pts[i], pts[i+1], pts[i+2], pts[i+3]))
				return false;
		}
		return true;
	}
}

struct cmp_pos_dis
{
	osg::Vec3f v;
	bool operator ()(const osg::Vec3f& lhs, const osg::Vec3f& rhs)
	{
		return (v-lhs).length2() < (v-rhs).length2();
	}
};

bool Tri_Mesh::GetAllRayTracePoints( const osg::Vec3f& p, const osg::Vec3f& q, Vec3fs& positive, Vec3fs& negative )
{
	FIter f_it;
	FVIter	fv_it;
	osg::Vec3f face[3], result;
	float distance_from_p_to_face = -1;
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
		// Positive tracing
		bool ret = IntersectLineTriangle(p, q, face[0], face[1], face[2], result);
		if (ret) positive.push_back(result);
		// Negative tracing
		ret = IntersectLineTriangle(q, p, face[0], face[1], face[2], result);
		if (ret) negative.push_back(result);
	}
	if (positive.empty()) return false;
	cmp_pos_dis cmp;
	cmp.v = p;
	sort(positive.begin(), positive.end(), cmp);
	sort(negative.begin(), negative.end(), cmp);
	return true;
}

bool Tri_Mesh::GetAllRayTraceNode( const osg::Vec3f& p, const osg::Vec3f& q, Vec3fs& nodes )
{
	Vec3fs positive, negative;
	bool ret = GetAllRayTracePoints(p, q, positive, negative);
	if (false == ret) return false;
	nodes.clear();
	assert(positive.size() == negative.size());
	for (int i=0;i<positive.size();++i)
	{
		nodes.push_back((positive[i] + negative[i])*0.5);
	}
}


double Tri_Mesh::ComputeFaceArea( FaceHandle& iter )
{
	osg::Vec3f v[3];
	int i=0;
	for(FVIter fv_it = fv_iter(iter); fv_it ; ++fv_it )
	{
		const Point& p = point(fv_it.handle());
		for (int j=0;j<3;++j)
		{
			v[i][j] = p[j];
		}
		++i;
	}
	return ((v[1]-v[0])^(v[2]-v[0])).length() / 2.0;
}

double Tri_Mesh::AverageFaceArea()
{
	FIter	f_it;
	int	count = 0;
	double	sum = 0.0;
	for (f_it = faces_begin(); f_it != faces_end(); ++f_it) 
	{
		sum += ComputeFaceArea(f_it.handle());
		++count;
	}
	return sum/count;
}

double Tri_Mesh::TotalFaceArea()
{
	FIter	f_it;
	double	sum = 0.0;
	for (f_it = faces_begin(); f_it != faces_end(); ++f_it) 
	{
		sum += ComputeFaceArea(f_it.handle());
	}
	return sum;
}
