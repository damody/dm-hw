#pragma once
/************************************************************************/
/* design by liang-syuan huang                                          */
/* This file imath define all Matrix and Vector that we need            */
/* The first thing : you need to decide row major/column major          */
/* you can use #define ROW_MAJOR or COL_MAJOR to decide matrix major    */
/*                                                                      */
/* use ogre math for compute dot product and cross producct             */
/*                                                                      */
/*                                                                      */
/************************************************************************/

#include <vector>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <cassert>

typedef unsigned char	uchar;
typedef unsigned short	ushort;
typedef unsigned int	uint;
typedef __int64		int64;
typedef unsigned __int64	uint64;

typedef std::vector<bool>	bool_vector;
typedef std::vector<uchar>	uchar_vector;
typedef std::vector<ushort>	ushort_vector;
typedef std::vector<uint>	uint_vector;
typedef std::vector<double>	double_vector;
typedef std::vector<double_vector>	double_vector2d;
typedef std::vector<float>	float_vector;
typedef std::vector<float_vector>	float_vector2d;
typedef std::vector<int>	int_vector;
typedef std::vector<std::vector<int> >	int_vector2d;
typedef std::vector<int64>	int64_vector;
typedef std::vector<std::vector<int64> > int64_vector2d;

#pragma warning( push, 0 )
#include "math/OgreVector2.h"
#include "math/OgreVector3.h"
#include "math/OgreVector4.h"
#include "math/OgreMatrix3.h"
#include "math/OgreMatrix4.h"
#pragma warning( pop )

template <class VEC>
struct VLine
{
	union
	{
		struct
		{
			VEC begin, end;
		};
		struct
		{
			VEC from, to;
		};
	};
	VEC v[2];

	VLine(){}
	VLine(const VEC& v1, const VEC& v2)
	{
		begin = v1;
		end = v2;
	}
};

typedef Ogre::Vector2d Vec2;
typedef Ogre::Vector3d Vec3;
typedef Ogre::Vector4d Vec4;
typedef Ogre::Matrix3 Mat3;
typedef Ogre::Matrix4 Mat4;
typedef Ogre::Quaternion Quaternion;
typedef VLine<Vec2> Vec2Line;
typedef VLine<Vec3> Vec3Line;
typedef VLine<Vec4> Vec4Line;
typedef std::vector<Vec2Line> Vec2Lines;
typedef std::vector<Vec3Line> Vec3Lines;
typedef std::vector<Vec4Line> Vec4Lines;
typedef std::vector<Vec2> Vec2s;
typedef std::vector<Vec3> Vec3s;
typedef std::vector<Vec4> Vec4s;


#pragma warning( push, 0 )
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/banded.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/operation.hpp>
#pragma warning( pop ) 

namespace UBLAS = boost::numeric::ublas;
typedef double num;
// vector
typedef UBLAS::vector<num>		Vector;
typedef UBLAS::mapped_vector<num>	MVector;	//M stand for mapped
typedef UBLAS::compressed_vector<num>	SVector;	//S stand for small and slow
// generic matrix
typedef UBLAS::zero_matrix	<num>	ZMatrix;
typedef UBLAS::identity_matrix	<num>	IMatrix;
// matrix
typedef UBLAS::basic_row_major<int64, int64>		row_major_int64;
typedef UBLAS::basic_column_major<int64, int64>		col_major_int64;
typedef UBLAS::map_std<int64, num> map_std_int64;
typedef UBLAS::matrix		<num, col_major_int64>	Matrix_col;
typedef UBLAS::matrix		<num, row_major_int64>	Matrix_row;
typedef UBLAS::mapped_matrix	<num, col_major_int64, map_std_int64> MMatrix_col; //M stand for mapped
typedef UBLAS::mapped_matrix	<num, row_major_int64, map_std_int64> MMatrix_row;
typedef UBLAS::coordinate_matrix<num, col_major_int64>	CMatrix_col;	//C stand for coordinate
typedef UBLAS::coordinate_matrix<num, row_major_int64>	CMatrix_row;
typedef UBLAS::compressed_matrix<num, col_major_int64>	SMatrix_col;	//S stand for small and slow
typedef UBLAS::compressed_matrix<num, row_major_int64>	SMatrix_row;
typedef UBLAS::diagonal_matrix	<num, col_major_int64>	DMatrix_col;
typedef UBLAS::diagonal_matrix	<num, row_major_int64>	DMatrix_row;

//#define COL_MAJOR
#if !defined(ROW_MAJOR) && !defined(COL_MAJOR)
#pragma message( "if no define any major, default use ROW_MAJOR" )
#define ROW_MAJOR
#endif

#if defined(ROW_MAJOR)
typedef Matrix_row	Matrix;
typedef MMatrix_row	MMatrix;
typedef CMatrix_row	CMatrix;
typedef SMatrix_row	SMatrix;
typedef DMatrix_row	DMatrix;
#elif defined(COL_MAJOR)
typedef Matrix_col	Matrix;
typedef MMatrix_col	MMatrix;
typedef CMatrix_col	CMatrix;
typedef SMatrix_col	SMatrix;
typedef DMatrix_col	DMatrix;
#endif

#define USE_CLAPACK
#ifdef USE_CLAPACK
#define BOOST_NUMERIC_BINDINGS_USE_CLAPACK
#pragma warning( push, 0 )
#include <boost/numeric/bindings/lapack/gesvd.hpp>
#include <boost/numeric/bindings/lapack/gesdd.hpp>
#include <boost/numeric/bindings/traits/std_vector.hpp>
#include <boost/numeric/bindings/traits/ublas_matrix.hpp>
#pragma warning( pop ) 
// # pragma comment(lib, "libf2cd.lib")
// # pragma comment(lib, "BLASd.lib")
// # pragma comment(lib, "lapackd.lib")
#undef  BOOST_NUMERIC_BINDINGS_USE_CLAPACK
void svd(const Matrix& A, Matrix& U, DMatrix& D, Matrix& VT);
void GetInverseBySVD(Matrix &dst, Matrix &src);   //��matrix�������ϯx�}
#endif

// function declaration
void Transpose(MMatrix_col& m_out, const MMatrix_row& m_in);
void Transpose(MMatrix_row& m_out, const MMatrix_col& m_in);
MMatrix_row MultiplyATA( const MMatrix_row& A );
MMatrix_col MultiplyATA( const MMatrix_col& A );
template <class MATRIX_TYPE> 
void Sparse_Multiply(MATRIX_TYPE& out, const MMatrix_row& A, const MMatrix_col& B);
