
#include "Tri_Mesh.h"

bool IntersectLineTriangle( osg::Vec3f& p, osg::Vec3f& q, osg::Vec3f& a, osg::Vec3f& b, osg::Vec3f& c, osg::Vec3f & point )
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
			float min_dis = 99999999.0;
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
			float min_dis = 99999999.0, tmp;
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
// 			osg::Vec3f fnormal = out1 ^ out2;
// 			fnormal.normalize();
// 			fnormal *= 0.001;
// 			out1 -= fnormal;
// 			out2 -= fnormal;
// 			out3 -= fnormal;
			return true;
		}
	}
	return false;
}

bool Tri_Mesh::SelectVertexRingVertex( osg::Vec3f& p, osg::Vec3f& q, sPoints& out )
{
	return false;
}

bool Tri_Mesh::SelectVertexRingEdge( osg::Vec3f& p, osg::Vec3f& q, sLines& out )
{
	return false;
}

bool Tri_Mesh::SelectVertexRingFace( osg::Vec3f& p, osg::Vec3f& q, sFaces& out )
{
	return false;
}

bool Tri_Mesh::SelectEdgeRingVertex( osg::Vec3f& p, osg::Vec3f& q, sPoints& out )
{
	return false;
}

bool Tri_Mesh::SelectEdgeRingEdge( osg::Vec3f& p, osg::Vec3f& q, sLines& out )
{
	return false;
}

bool Tri_Mesh::SelectEdgeRingFace( osg::Vec3f& p, osg::Vec3f& q, sFaces& out )
{
	return false;
}

bool Tri_Mesh::SelectFaceRingVertex( osg::Vec3f& p, osg::Vec3f& q, sPoints& out )
{
	return false;
}

bool Tri_Mesh::SelectFaceRingEdge( osg::Vec3f& p, osg::Vec3f& q, sLines& out )
{
	return false;
}

bool Tri_Mesh::SelectFaceRingFace( osg::Vec3f& p, osg::Vec3f& q, sFaces& out )
{
	return false;
}
