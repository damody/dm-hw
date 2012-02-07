#pragma once
#include <vector>
#include <algorithm>
#include "imath.h"
#include "shared_ptr.h"
#include "log_define.h"

struct cell
{
	int i, j;
	double value;
	cell(int _i, int _j, double _v)
	{
		i = _i;
		j = _j;
		value = _v;
	}
	cell():i(-1), j(-1), value(0)
	{}
	bool IsNull()
	{
		return i == -1 && j == -1;
	}
};
typedef std::vector<cell*> cells;
typedef std::vector<cells> cells_2d;

struct tag_RowComparer
{
	bool operator ()(const cell* lhs, const cell* rhs)
	{
		return lhs->j < rhs->j;
	}
};
struct tag_ColComparer
{
	bool operator ()(const cell* lhs, const cell* rhs)
	{
		return lhs->i < rhs->i;
	}
};
extern tag_RowComparer RowComparer;
extern tag_ColComparer ColComparer;

class SparseMatrix
{
private:
	friend class CCSMatrix;
	int m_m, m_n;
	cells_2d m_rows, m_cols;
public:
	SparseMatrix():m_m(0), m_n(0){}
	// just resize
	SparseMatrix(size_t m, size_t n);
	// add nElements in matrix each row and column
	SparseMatrix(int m, int n, int nElements);
	// free all elements
	void Release()
	{
		for (cells_2d::iterator it1 = m_rows.begin();it1 != m_rows.end();++it1)
		{
			for (cells::iterator it2 = it1->begin();it2 != it1->end();++it2)
			{
				delete *it2;
			}
		}
	}

	int GetRowSize() const {return m_m;}
	int GetColSize() const {return m_n;}
	int NumOfElements() const;
	const cells_2d& GetRows() const {return m_rows;}
	const cells_2d& GetCols() const {return m_cols;}
	cells& GetRow(size_t index)
	{return m_rows[index];}
	cells& GetCol(size_t index)
	{return m_cols[index];}
	// TODO: Need Implemented
	// SparseMatrix(const SparseMatrix& right);
	// TODO: Need Implemented
	bool operator == (const SparseMatrix& right) const;
	// TODO: Need Implemented
	int GetHashCode() const;
	// TODO: Need Implemented
	bool CheckElements() const;
	// TODO: Need Implemented
	bool IsSymmetric() const;

	cell*	AddElement(const cell& _e);
	cell*	AddElement(int i, int j, double value);
	cell*	FindElement(int i, int j);
	cell*	AddElementIfNotExist(int i, int j, double value);
	cell*	AddValueTo(int i, int j, double value);
	void	SortElement();
	void	AddRow();
	void	AddCol();
	void	Multiply(double* xIn, double* xOut) const;
	void	Multiply(double* xIn, int indexIn, double* xOut, int indexOut) const;
	void	PreMultiply(double* xIn, double* xOut) const;
	void	Scale(double s);
	SparseMatrix Multiply(const SparseMatrix& right) const;
	SparseMatrix Add(const SparseMatrix& right) const;
	// TODO: Need Implemented
	void	Transpose();
	// TODO: Need Implemented
	double* GetDiagonalPreconditionor();
	// TODO: Need Implemented
	SparseMatrix ConcatRows(const SparseMatrix& right);
	int_vector2d GetRowIndex() const;
	int_vector2d GetColIndex() const;
	// TODO: Need Implemented
	static void ConjugateGradientsMethod(const SparseMatrix& A, double* b, double* x, int iter, double tolerance);
	// TODO: Need Implemented
	static void ConjugateGradientsMethod2(const SparseMatrix& A, double* b, double* x, int iter, double tolerance);
	// TODO: Need Implemented
	static void ConjugateGradientsMethod3(const SparseMatrix& A, double* b, double* x, bool* boundary, int iter, double tolerance);
	// TODO: Need Implemented
	static void JacobiMethod(SparseMatrix A, double* b, double* x, int iter, double tolerance);
	//static void Assign(double* u, double* v); don't need
	// TODO: Need Implemented
	static void Subtract(double* w, double* u, double* v);
	// TODO: Need Implemented
	static void Add(double* w, double* u, double* v);
	// TODO: Need Implemented
	static void Scale(double* w, double* u, double s);
	// TODO: Need Implemented
	static double Dot(double* u, double* v);
};

