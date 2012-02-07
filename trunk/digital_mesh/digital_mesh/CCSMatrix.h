#pragma once
#include "imath.h"
#include "SparseMatrix.h"

class CCSMatrix
{
private:
	int m_m;
	int m_n;
	int_vector m_rowIndex;
	int_vector m_colIndex;
	double_vector m_values;
public:
	CCSMatrix():m_m(0), m_n(0) {}
	CCSMatrix(const SparseMatrix& matrix);
	CCSMatrix(int m, int n);

	int GetRowSize() const
	{return m_m;}
	int GetColSize() const
	{return m_n;}
	const int_vector& GetRowIndex() const
		{return m_rowIndex;}
	int_vector& RowIndex()
		{return m_rowIndex;}
	const int_vector& GetColIndex() const
		{return m_colIndex;}
	int_vector& ColIndex()
		{return m_colIndex;}
	const double_vector& GetValues() const
		{return m_values;}
	double_vector& Values()
		{return m_values;}
	int GetNumNonZero() const
	{return m_values.size();}
	int NumOfElements() const;

	// TODO: Need Implemented
	CCSMatrix FastMultiply(const CCSMatrix& B) const;
	// TODO: Need Implemented
	void Transpose();
	void Multiply(double* xIn, double* xOut);
	void PreMultiply(double* xIn, double* xOut);
	void PreMultiply(double* xIn, double* xOut, int startIndex, bool init);
	void PreMultiply(double* xIn, double* xOut, int inStart, int outStart, bool init);
	void PreMultiply(double* xIn, double* xOut, int* index, int n);
	void PreMultiplyOffset(double* xIn, double* xOut, int startOut, int offsetOut);
	// TODO: Need Implemented
	bool Check(CCSMatrix B);
	// TODO: Need Implemented
	void CG(double* x, double* b, double eps, int maxIter);
	// TODO: Need Implemented
	void PCG(double* x, double* b, double* inv, double eps, int maxIter);
};

