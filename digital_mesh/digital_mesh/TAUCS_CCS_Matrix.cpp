#include "TAUCS_CCS_Matrix.h"

#pragma region Constructors


TAUCS_CCS_Matrix_Double::TAUCS_CCS_Matrix_Double():
m_Matrix(ZMatrix())
{

}

TAUCS_CCS_Matrix_Double::TAUCS_CCS_Matrix_Double( const MMatrix& mat ):
m_Matrix(mat)
{

}

TAUCS_CCS_Matrix_Double::TAUCS_CCS_Matrix_Double( int m, int n ):
m_Matrix(ZMatrix(m, n))
{

}

TAUCS_CCS_Matrix_Double::TAUCS_CCS_Matrix_Double( const taucs_ccs_matrix* mat )
{
	m_Matrix.resize(mat->m, mat->n);
	int nnz = mat->rowind[mat->n]-1;
	int index2=0;
	for (int index=0;index<nnz;++index)
	{
		if (mat->colptr[index2] >= index)
			++index2;
		m_Matrix(mat->rowind[index], index2) = mat->values.d[index];
	}
}

#pragma endregion Constructors

taucs_ccs_matrix* TAUCS_CCS_Matrix_Double::Get_taucs_ccs_matrix()
{
	int count = (int)m_Matrix.nnz();
	taucs_ccs_matrix* res_matrix = taucs_ccs_create(m_Matrix.size1(), m_Matrix.size2(), count, TAUCS_DOUBLE );
	int index = 0;
 	int index2 = 0;
	res_matrix->colptr[0] = 0;
#ifdef ROW_MAJOR
	// row major
	for (MMatrix::const_iterator1 it1 = m_Matrix.begin1();it1 != m_Matrix.end1();++it1)
	{
		for (MMatrix::const_iterator2 it2 = it1.begin(); it2 != it1.end();++it2)			
		{
			res_matrix->rowind[index] = it2.index2();
			res_matrix->values.d[index] = *it2;
			index++;
		}
		res_matrix->colptr[++index2] = index;
	}
#else //COL_MAJOR
	// column major
	for (MMatrix::const_iterator2 it1 = m_Matrix.begin2();it1 != m_Matrix.end2();++it1)
	{
		for (MMatrix::const_iterator1 it2 = it1.begin(); it2 != it1.end();++it2)			
		{
			res_matrix->rowind[index] = it2.index1();
			res_matrix->values.d[index] = *it2;
			index++;
		}
		res_matrix->colptr[++index2] = index;
	}
#endif
	return res_matrix;
}

MMatrix TAUCS_CCS_Matrix_Double::Get_ublas_Matrix()
{
	return m_Matrix;
}

void TAUCS_CCS_Matrix_Double::Resize( int m, int n )
{
	m_Matrix.resize(m, n);
}


MVector TAUCS_CCS_Matrix_Double::Compute_x_By_Slover_Ax_B( const MVector& B )
{
	Matrix mat = m_Matrix;
	Matrix inv_mat;
	GetInverseBySVD(inv_mat, mat);
	return prod(inv_mat, B);
}

MMatrix TAUCS_CCS_Matrix_Double::Compute_x_By_Slover_Ax_B( const MMatrix& B )
{
	Matrix mat = m_Matrix;
	Matrix inv_mat;
	GetInverseBySVD(inv_mat, mat);
	return prod(inv_mat, B);
}

TAUCS_CCS_Matrix_Double& TAUCS_CCS_Matrix_Double::operator=( const taucs_ccs_matrix* mat )
{
	m_Matrix.resize(mat->m, mat->n, false);

	int nnz = mat->colptr[mat->n];
	int index2=1;
	for (int index=0;index<nnz;++index)
	{
		if (mat->colptr[index2] <= index)
			++index2;
#ifdef ROW_MAJOR
		m_Matrix(index2-1, mat->rowind[index]) = mat->values.d[index];
#else //COL_MAJOR
		m_Matrix(mat->rowind[index], index2-1) = mat->values.d[index];
#endif
	}
	return *this;
}

TAUCS_CCS_Matrix_Double& TAUCS_CCS_Matrix_Double::operator=( const MMatrix& mat )
{
	m_Matrix = mat;
	return *this;
}

int_vector2d TAUCS_CCS_Matrix_Double::GetRowIndex()
{
	int_vector2d res(m_Matrix.size1());
#if defined(ROW_MAJOR)
	for (MMatrix::const_iterator1 it1 = m_Matrix.begin1();it1 != m_Matrix.end1();++it1)
	{
		for (MMatrix::const_iterator2 it2 = it1.begin(); it2 != it1.end();++it2)
		{
			res[it2.index1()].push_back(it2.index2());
		}
	}
#elif defined(COL_MAJOR)
	for (MMatrix::const_iterator2 it1 = m_Matrix.begin2();it1 != m_Matrix.end2();++it1)
	{
		for (MMatrix::const_iterator1 it2 = it1.begin(); it2 != it1.end();++it2)
		{
			res[it2.index1()].push_back(it2.index2());
		}
	}
#endif
	return res;
}

int_vector2d TAUCS_CCS_Matrix_Double::GetColIndex()
{
	int_vector2d res(m_Matrix.size2());
#if defined(ROW_MAJOR)
	for (MMatrix::const_iterator1 it1 = m_Matrix.begin1();it1 != m_Matrix.end1();++it1)
	{
		for (MMatrix::const_iterator2 it2 = it1.begin(); it2 != it1.end();++it2)
		{
			res[it2.index2()].push_back(it2.index1());
		}
	}
#elif defined(COL_MAJOR)
	for (MMatrix::const_iterator2 it1 = m_Matrix.begin2();it1 != m_Matrix.end2();++it1)
	{
		for (MMatrix::const_iterator1 it2 = it1.begin(); it2 != it1.end();++it2)
		{
			res[it2.index2()].push_back(it2.index1());
		}
	}
#endif
	return res;
}

taucs_ccs_matrix* Clone_taucs_ccs_matrix( taucs_ccs_matrix* src, size_t datatype_size )
{
	int nnz = src->colptr[src->n];
	taucs_ccs_matrix* res_matrix = taucs_ccs_create(src->m, src->n, nnz, src->flags);
	memcpy(res_matrix->colptr, src->colptr, (src->n+1) * sizeof(int));
	memcpy(res_matrix->rowind, src->rowind, nnz * sizeof(int));
	memcpy(res_matrix->values.v, src->values.v, nnz * datatype_size);
	return res_matrix;
}

taucs_ccs_matrix_sptr make_t_ccs_matrix_shared_ptr( taucs_ccs_matrix* src )
{
	return taucs_ccs_matrix_sptr(src, release_taucs_ccs_matrix);
}

taucs_ccs_matrix_sptr Clone_taucs_ccs_matrix_sptr( taucs_ccs_matrix* src, size_t datatype_size )
{
	return make_t_ccs_matrix_shared_ptr(Clone_taucs_ccs_matrix(src, datatype_size));
}

taucs_ccs_matrix* Clone_taucs_ccs_matrix_double( taucs_ccs_matrix* src )
{
	return Clone_taucs_ccs_matrix(src, sizeof(double));
}

taucs_ccs_matrix_sptr Clone_taucs_ccs_matrix_sptr_double( taucs_ccs_matrix* src )
{
	return make_t_ccs_matrix_shared_ptr(Clone_taucs_ccs_matrix_double(src));
}

