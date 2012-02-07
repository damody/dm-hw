#include "CCSMatrix.h"

int CCSMatrix::NumOfElements() const
{
	int count = 0;
	if (m_m < m_n)
	{
		for (int_vector::const_iterator it = m_rowIndex.begin();it != m_rowIndex.end();++it)
		{
			count += *it;
		}
	}
	else
	{
		for (int_vector::const_iterator it = m_colIndex.begin();it != m_colIndex.end();++it)
		{
			count += *it;
		}
	}
	return count;
}

CCSMatrix::CCSMatrix( const SparseMatrix& matrix )
{
	// get number of non-zero elements
	m_m = matrix.GetRowSize();
	m_n = matrix.GetColSize();
	int nnz = matrix.NumOfElements();

	// create temp arrays
	m_rowIndex.resize(nnz);
	m_colIndex.resize(m_n+1);
	m_values.resize(nnz);

	// copy values to arrays
	int index = 0;
	int index2 = 0;
	m_colIndex[0] = 0;
	for (cells_2d::const_iterator itcol = matrix.m_cols.begin();
		itcol != matrix.m_cols.end(); ++itcol)
	{
		for (cells::const_iterator it = itcol->begin();
			it != itcol->end(); ++it)
		{
			m_rowIndex[index] = (*it)->i;
			m_values[index] = (*it)->value;
			index++;
		}
		m_colIndex[++index2] = index;
	}
}

CCSMatrix::CCSMatrix( int m, int n )
{
	m_m = m;
	m_n = n;
	m_colIndex.resize(n + 1);
	m_colIndex[0] = 0;
}

void CCSMatrix::Multiply( double* xIn, double* xOut )
{
	memset(xOut, 0, sizeof(double) * m_m);
	for (int i=0; i<m_n; i++) 
	{
		for (int j=m_colIndex[i]; j<m_colIndex[i+1]; j++) 
		{
			int r = m_rowIndex[j];
			xOut[r] += m_values[j] * xIn[i];
		}
	}
}

void CCSMatrix::PreMultiply( double* xIn, double* xOut )
{
	memset(xOut, 0, sizeof(double) * m_n);
	for (int i = 0; i < m_n; i++)
	{
		double sum = 0.0;
		for (int j = m_colIndex[i]; j < m_colIndex[i + 1]; j++)
		{
			int r = m_rowIndex[j];
			sum += m_values[j] * xIn[r];
		}
		xOut[i] = sum;
	}
}

void CCSMatrix::PreMultiply( double* xIn, double* xOut, int startIndex, bool init )
{
	if (init) memset(xOut, 0, sizeof(double) * m_n);
	for (int i = 0; i < m_n; i++)
	{
		double sum = 0.0;
		for (int j = m_colIndex[i]; j < m_colIndex[i + 1]; j++)
		{
			int r = m_rowIndex[j];
			sum += m_values[j] * xIn[r + startIndex];
		}
		xOut[i] += sum;
	}
}

void CCSMatrix::PreMultiply( double* xIn, double* xOut, int inStart, int outStart, bool init )
{
	if (init) memset(xOut + inStart, 0, sizeof(double) * m_n);
	for (int i = 0; i < m_n; i++)
	{
		double sum = 0.0;
		for (int j = m_colIndex[i]; j < m_colIndex[i + 1]; j++)
		{
			int r = m_rowIndex[j];
			sum += m_values[j] * xIn[r + inStart];
		}
		xOut[i + outStart] += sum;
	}
}

void CCSMatrix::PreMultiply( double* xIn, double* xOut, int* index, int n )
{
	memset(xOut, 0, sizeof(double) * n);
	for (int i=0;i < n;++i)
	{
		double sum = 0.0;
		for (int j = m_colIndex[i]; j < m_colIndex[i + 1]; j++)
		{
			int r = m_rowIndex[j];
			sum += m_values[j] * xIn[r];
		}
		xOut[i] = sum;
	}
}

void CCSMatrix::PreMultiplyOffset( double* xIn, double* xOut, int startOut, int offsetOut )
{
	for (int i = startOut; i < m_n + offsetOut; i += offsetOut) 
		xOut[i] = 0;

	for (int i = 0, k = startOut; i < m_n; i++, k += offsetOut)
	{
		double sum = 0.0;
		for (int j = m_colIndex[i]; j < m_colIndex[i + 1]; j++)
		{
			int r = m_rowIndex[j];
			sum += m_values[j] * xIn[r];
		}
		xOut[k] = sum;
	}
}
