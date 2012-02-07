#include "Matrix_Mesh.h"
#include "log_define.h"
#include <boost/timer.hpp>

Matrix_Mesh::Matrix_Mesh(void):Tri_Mesh()
{
	LOG_DEBUG << "Matrix_Mesh()";
}

Matrix_Mesh::~Matrix_Mesh(void)
{
}

TAUCS_CCS_Matrix_Double Matrix_Mesh::BuildAdjacentMatrixVV()
{
	MMatrix m(n_vertices(), n_vertices());
	FIter	f_it;
	for (f_it = faces_begin(); f_it != faces_end(); ++f_it) 
	{
		int c[3];
		int idxc = 0;
		for(FVIter fv_it = fv_iter(f_it); fv_it ; ++fv_it )
		{
			c[idxc++] = fv_it.handle().idx();
		}
		// if (m(c[X], c[Y])==0)
#define Add_1_If_0(X, Y) m(c[X], c[Y]) = 1.0;
		Add_1_If_0(0,1);
		Add_1_If_0(1,2);
		Add_1_If_0(2,0);
		Add_1_If_0(1,0);
		Add_1_If_0(2,1);
		Add_1_If_0(0,2);
	}
	return TAUCS_CCS_Matrix_Double(m);
}

TAUCS_CCS_Matrix_Double Matrix_Mesh::BuildAdjacentMatrixFV()
{
	MMatrix m(n_faces(), n_vertices());
	FIter	f_it;
	int	f_count = 0;
	for (f_it = faces_begin(); f_it != faces_end(); ++f_it, ++f_count) 
	{
		int c[3];
		int idxc = 0;
		for(FVIter fv_it = fv_iter(f_it); fv_it ; ++fv_it )
		{
			c[idxc++] = fv_it.handle().idx();
		}
		m(f_count, c[0]) = 1.0;
		m(f_count, c[1]) = 1.0;
		m(f_count, c[2]) = 1.0;
	}
	return TAUCS_CCS_Matrix_Double(m);
}

TAUCS_CCS_Matrix_Double Matrix_Mesh::BuildAdjacentMatrixFF()
{
	MMatrix m(n_faces(), n_faces());

	FIter	f_it;
	int	f_count = 0;
	for (f_it = faces_begin(); f_it != faces_end(); ++f_it, ++f_count) 
	{
		int c[3];
		int idxc = 0;
		for(FVIter fv_it = fv_iter(f_it); fv_it ; ++fv_it )
		{
			c[idxc++] = fv_it.handle().idx();
		}
		for (size_t j=0;j < m_adjVF[c[0]].size();++j)
		{
			if (j != f_count && IsContainVertex(f_it, c[1]))
			{
				if (m(f_count, j)==0) m(f_count, j) = 1.0;
			}
		}
		for (size_t j=0;j < m_adjVF[c[1]].size();++j)
		{
			if (j != f_count && IsContainVertex(f_it, c[2]))
			{
				if (m(f_count, j)==0) m(f_count, j) = 1.0;
			}
		}
		for (size_t j=0;j < m_adjVF[c[2]].size();++j)
		{
			if (j != f_count && IsContainVertex(f_it, c[0]))
			{
				if (m(f_count, j)==0) m(f_count, j) = 1.0;
			}
		}
	}
	return TAUCS_CCS_Matrix_Double(m);
}

bool Matrix_Mesh::ReadFile( std::string _fileName )
{
	bool res = Tri_Mesh::ReadFile(_fileName);
	LOG_TRACE	 << "Tri_Mesh ReadFile finish";
	if (res)
	{
		boost::timer timer;
#ifndef _DEBUG
		timer.restart();
		TAUCS_CCS_Matrix_Double adjVV = BuildAdjacentMatrixVV();
		m_adjVV = adjVV.GetRowIndex();
		TAUCS_CCS_Matrix_Double adjVF = BuildAdjacentMatrixFV();
		m_adjVF = adjVF.GetColIndex();
		TAUCS_CCS_Matrix_Double adjFF = BuildAdjacentMatrixFF();
		m_adjFF = adjFF.GetRowIndex();
		LOG_TRACE	<< "TAUCS_CCS_Matrix_Double use time: " << timer.elapsed();
#endif
		timer.restart();
		m_SMVV = BuildAdjacentSMatrixVV();
		m_adjVV = m_SMVV.GetRowIndex();
		m_SMVF = BuildAdjacentSMatrixVV();
		m_adjVF = m_SMVF.GetColIndex();
		m_SMFF = BuildAdjacentSMatrixVV();
		m_adjFF = m_SMFF.GetRowIndex();
		LOG_TRACE	<< "SparseMatrix use time: " << timer.elapsed();
		m_Flags.resize(n_vertices());
		m_isBoundary.resize(n_vertices());
	}
	return res;
}

double Matrix_Mesh::GetVolume()
{
	double totVolume = 0;
	FIter	f_it;
	int	f_count = 0;
	for (f_it = faces_begin(); f_it != faces_end(); ++f_it, ++f_count) 
	{
		osg::Vec3d pos[3];
		int i=0;
		for (FVIter fv_it = fv_iter(f_it); fv_it ; ++fv_it )
		{
			osg::Vec3d tmp;
			const Point& p = point(fv_it.handle());
			for (int j=0;j<3;++j)
			{
				tmp[j] = p[j];
			}
			pos[i++] = tmp;
		}
		totVolume += 
			pos[0][0] * pos[1][1] * pos[2][2] - 
			pos[0][0] * pos[1][2] * pos[2][1] - 
			pos[0][1] * pos[1][0] * pos[2][2] +
			pos[0][1] * pos[1][2] * pos[2][0] + 
			pos[0][2] * pos[1][0] * pos[2][1] - 
			pos[0][2] * pos[1][1] * pos[2][0];
	}
	return totVolume;
}

SparseMatrix Matrix_Mesh::BuildAdjacentSMatrixVV()
{
	SparseMatrix m(n_vertices(), n_vertices());
	FIter	f_it;
	for (f_it = faces_begin(); f_it != faces_end(); ++f_it) 
	{
		int c[3];
		int idxc = 0;
		for(FVIter fv_it = fv_iter(f_it); fv_it ; ++fv_it )
		{
			c[idxc++] = fv_it.handle().idx();
		}
		// if (m(c[X], c[Y])==0)
#define SAdd_1_If_0(X, Y) m.AddElementIfNotExist(c[X], c[Y], 1.0);
		SAdd_1_If_0(0,1);
		SAdd_1_If_0(1,2);
		SAdd_1_If_0(2,0);
		SAdd_1_If_0(1,0);
		SAdd_1_If_0(2,1);
		SAdd_1_If_0(0,2);
	}
	return m;
}

SparseMatrix Matrix_Mesh::BuildAdjacentSMatrixFV()
{
	SparseMatrix m(n_faces(), n_vertices());
	FIter	f_it;
	int	f_count = 0;
	for (f_it = faces_begin(); f_it != faces_end(); ++f_it, ++f_count) 
	{
		int c[3];
		int idxc = 0;
		for(FVIter fv_it = fv_iter(f_it); fv_it ; ++fv_it )
		{
			c[idxc++] = fv_it.handle().idx();
		}
		m.AddElementIfNotExist(f_count, c[0], 1.0);
		m.AddElementIfNotExist(f_count, c[1], 1.0);
		m.AddElementIfNotExist(f_count, c[2], 1.0);
	}
	return m;
}

SparseMatrix Matrix_Mesh::BuildAdjacentSMatrixFF()
{
	SparseMatrix m(n_faces(), n_faces());
	FIter	f_it;
	int	f_count = 0;
	for (f_it = faces_begin(); f_it != faces_end(); ++f_it, ++f_count) 
	{
		int c[3];
		int idxc = 0;
		for(FVIter fv_it = fv_iter(f_it); fv_it ; ++fv_it )
		{
			c[idxc++] = fv_it.handle().idx();
		}
		for (size_t j=0;j < m_adjVF[c[0]].size();++j)
		{
			if (j != f_count && IsContainVertex(f_it, c[1]))
				m.AddElementIfNotExist(f_count, j, 1.0);
		}
		for (size_t j=0;j < m_adjVF[c[1]].size();++j)
		{
			if (j != f_count && IsContainVertex(f_it, c[2]))
				m.AddElementIfNotExist(f_count, j, 1.0);
		}
		for (size_t j=0;j < m_adjVF[c[2]].size();++j)
		{
			if (j != f_count && IsContainVertex(f_it, c[0]))
				m.AddElementIfNotExist(f_count, j, 1.0);
		}
	}
	return m;
}

double* Matrix_Mesh::GetBound()
{
	VertexIter v_it=vertices_begin();
	const Point& start = point(v_it);
	m_bound[0] = m_bound[1] = start[0];
	m_bound[2] = m_bound[3] = start[1];
	m_bound[4] = m_bound[5] = start[2];
	for (;v_it!=vertices_end(); ++v_it) 
	{
		const Point&  p = point(v_it);
		if (m_bound[0] > p[0]) m_bound[0] = p[0];
		if (m_bound[1] < p[0]) m_bound[1] = p[0];
		if (m_bound[2] > p[1]) m_bound[2] = p[1];
		if (m_bound[3] < p[1]) m_bound[3] = p[1];
		if (m_bound[4] > p[2]) m_bound[4] = p[2];
		if (m_bound[5] < p[2]) m_bound[5] = p[2];
	}
	return m_bound;
}

double_vector Matrix_Mesh::GetVectors()
{
	double_vector res;
	for (VertexIter v_it=vertices_begin(); v_it!=vertices_end(); ++v_it) 
	{
		const Point&  p = point(v_it);
		for (int j=0;j<3;++j)
		{
			res.push_back(p[j]);
		}
	}
	return res;
}

Vec3s Matrix_Mesh::GetVec3s()
{
	Vec3s res;
	for (VertexIter v_it=vertices_begin(); v_it!=vertices_end(); ++v_it) 
	{
		Vec3 tmp;
		const Point&  p = point(v_it);
		for (int j=0;j<3;++j)
		{
			tmp[j] = p[j];
		}
		res.push_back(tmp);
	}
	return res;
}

bool Matrix_Mesh::IsContainVertex( FaceHandle fh, int v_idx )
{
	for(FVIter fv_it = fv_iter(fh); fv_it ; ++fv_it )
	{
		if(fv_it.handle().idx() == v_idx) return true;
	}
	return false;
}
