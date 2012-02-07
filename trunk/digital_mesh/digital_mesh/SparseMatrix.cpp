#include "SparseMatrix.h"

tag_RowComparer RowComparer;
tag_ColComparer ColComparer;

SparseMatrix::SparseMatrix( size_t m, size_t n ) :m_m(m), m_n(n)
{
	m_rows.resize(m);
	m_cols.resize(n);
}

SparseMatrix::SparseMatrix( int m, int n, int nElements ) :m_m(m), m_n(n)
{
	m_rows.resize(m);
	m_cols.resize(n);
	for (int i=0; i<m; i++)
		m_rows[i].resize(nElements);
	for (int i=0; i<n; i++)
		m_cols[i].resize(nElements);
}

int SparseMatrix::NumOfElements() const
{
	int count = 0;
	if (m_m < m_n)
	{
		for (cells_2d::const_iterator it = m_rows.begin();it != m_rows.end();++it)
		{
			count += it->size();
		}
	}
	else
	{
		for (cells_2d::const_iterator it = m_cols.begin();it != m_cols.end();++it)
		{
			count += it->size();
		}
	}
	return count;
}

cell* SparseMatrix::AddElement( const cell& _e )
{
	cells& r = m_rows[_e.i];
	cells& c = m_cols[_e.j];
	cell* e = new cell(_e.i, _e.j, _e.value);
	r.push_back(e);
	c.push_back(e);
	return e;
}

cell* SparseMatrix::AddElement( int i, int j, double value )
{
	if (value == 0) return 0;
	cells& r = m_rows[i];
	cells& c = m_cols[j];
	cell* e = new cell(i, j, value);
	r.push_back(e);
	c.push_back(e);
	return e;
}

cell* SparseMatrix::FindElement( int i, int j )
{
	cells& rr = m_rows[i];
	//TODO: Binary search acceleration
	for (cells::iterator it = rr.begin();it != rr.end(); ++it)
	{
		if ((*it)->j == j)
			return (*it);
	}
	return NULL;
}

cell* SparseMatrix::AddElementIfNotExist( int i, int j, double value )
{
	cell* e = FindElement(i, j);
	if (NULL == e)
	{
		return AddElement(i, j, value);
	}
	else
		return NULL;
}

cell* SparseMatrix::AddValueTo( int i, int j, double value )
{
	cell* e = FindElement(i, j);
	if (NULL == e) 
		return AddElement(i, j, value);
	else
		e->value += value;
	return e;
}

void SparseMatrix::SortElement()
{
	for (cells_2d::iterator it = m_rows.begin();it != m_rows.end();++it)
	{
		std::sort(it->begin(), it->end(), RowComparer);
	}
	for (cells_2d::iterator it = m_cols.begin();it != m_cols.end();++it)
	{
		std::sort(it->begin(), it->end(), ColComparer);
	}
}

void SparseMatrix::AddRow()
{
	m_rows.push_back(cells());
	m_m++;
}

void SparseMatrix::AddCol()
{
	m_cols.push_back(cells());
	m_n++;
}

void SparseMatrix::Multiply( double* xIn, double* xOut ) const
{
	for (int i=0; i<m_m; i++) 
	{
		const cells& r = m_rows[i];
		double sum = 0.0;
		for (size_t j=0;j < r.size();++j)
		{
			const cell& e = *r[j];
			sum += e.value * xIn[e.j];
		}
		xOut[i] = sum;
	}
}

void SparseMatrix::Multiply( double* xIn, int indexIn, double* xOut, int indexOut ) const
{
	for (int i=0; i<m_m; i++) 
	{
		const cells& r = m_rows[i];
		double sum = 0.0;
		for (size_t j=0;j < r.size();++j)
		{
			const cell& e = *r[j];
			sum += e.value * xIn[e.j+indexIn];
		}
		xOut[i+indexOut] = sum;
	}
}

void SparseMatrix::PreMultiply( double* xIn, double* xOut ) const
{
	for (int j=0; j<m_n; j++) 
	{
		const cells& c = m_cols[j];
		double sum = 0.0;
		for (size_t i=0;i < c.size();++i)
		{
			const cell& e = *c[i];
			sum += e.value * xIn[e.i];
		}
		xOut[j] = sum;
	}
}

void SparseMatrix::Scale( double s )
{
	for (cells_2d::iterator it1 = m_rows.begin();it1 != m_rows.end();++it1)
	{
		for (cells::iterator it2 = it1->begin();it2 != it1->end();++it2)
		{
			(*it2)->value *= s;
		}
	}
}

SparseMatrix SparseMatrix::Multiply( const SparseMatrix& right ) const
{
	assert(m_n == right.m_m);
	if (!(m_n == right.m_m))
	{
		LOG_FATAL << "SparseMatrix(Multiply): m_n == right.m_m";
	}
	SparseMatrix ret(m_m, right.m_n);
	for (size_t i=0; i< m_rows.size(); i++)
	{
		const cells& rr = m_rows[i];
		for (size_t j=0;j < right.m_cols.size();++j)
		{
			const cells& cc = right.m_cols[j];
			size_t c1 = 0;
			size_t c2 = 0;
			double sum = 0;
			bool used = false;
			while (c1 < rr.size() && c2 < cc.size()) 
			{
				const cell& e1 = *rr[c1];
				const cell& e2 = *cc[c2];
				if (e1.j < e2.i) { c1++; continue; }
				if (e1.j > e2.i) { c2++; continue; }
				sum += e1.value * e2.value;
				c1++;
				c2++;
				used = true;
			}
			if (used) ret.AddElement(i, j, sum);
		}
	}
	return ret;
}

SparseMatrix SparseMatrix::Add( const SparseMatrix& right ) const
{
	assert(m_m == right.m_m && m_n == right.m_n);
	if (!(m_m == right.m_m && m_n == right.m_n))
	{
		LOG_FATAL << "SparseMatrix(Add): m_m == right.m_m && m_n == right.m_n";
	}
	SparseMatrix ret(m_m, m_m);

	for (int i=0; i < m_m; i++) 
	{
		const cells& r1 = m_rows[i];
		const cells& r2 = right.m_rows[i];
		size_t c1 = 0;
		size_t c2 = 0;
		while (c1 < r1.size() && c2 < r2.size()) 
		{
			const cell& e1 = *r1[c1];
			const cell& e2 = *r2[c2];
			if (e1.j < e2.j) {
				c1++; 
				ret.AddElement(i, e1.j, e1.value); 
				continue; 
			}
			if (e1.j > e2.j) 
			{
				c2++; 
				ret.AddElement(i, e2.j, e2.value); 
				continue; 
			}
			ret.AddElement(i, e1.j, e1.value + e2.value);
			c1++;
			c2++;
		}
		while (c1 < r1.size()) 
		{
			const cell& e = *r1[c1];
			ret.AddElement(e.i, e.j, e.value);
			c1++;
		}
		while (c2 < r2.size()) 
		{
			const cell& e = *r2[c2];
			ret.AddElement(e.i, e.j, e.value);
			c2++;
		}
	}
	return ret;
}

int_vector2d SparseMatrix::GetRowIndex() const
{
	int_vector2d arr(m_m);
	for (int i = 0; i < m_m; i++)
	{
		arr[i].resize(m_rows[i].size());
		int j = 0;
		for (cells::const_iterator it = m_rows[i].begin();it != m_rows[i].end();++it)
			arr[i][j++] = (*it)->j;
	}
	return arr;
}

int_vector2d SparseMatrix::GetColIndex() const
{
	int_vector2d arr(m_n);
	for (int i = 0; i < m_n; i++)
	{
		arr[i].resize(m_cols[i].size());
		int j = 0;
		for (cells::const_iterator it = m_cols[i].begin();it != m_cols[i].end();++it)
			arr[i][j++] = (*it)->i;
	}
	return arr;
}


