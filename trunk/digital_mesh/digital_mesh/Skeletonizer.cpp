
#include "Skeletonizer.h"
#include <cstdlib>
#include <vector>
#include <cassert>
#include <iomanip>
#include <boost/timer.hpp>
#include "imath.h"
#include "Tri_Mesh.h"
#include "log_define.h"

Skeletonizer::Skeletonizer(Matrix_Mesh& mesh, Options& )
:mMesh(mesh)
{
	Initialize();
	uint n  = mMesh.n_vertices();
	int fn = mMesh.n_faces();
	mLapWeight.resize(n);
	mPosWeight.resize(n);
	//opt = opt;
	//if (opt.AddNoise) AddNoise();
	m_originalVolume = mMesh.GetVolume();
	mMesh.GetVertexs(&mOriginalVertexPos);
	this->mOriginalFaceArea.resize(fn);
	int f_count = 0;
	for (BasicMesh::FaceIter f_it = mMesh.faces_begin(); f_it != mMesh.faces_end(); ++f_it) 
	{
		mOriginalFaceArea[f_count++] = mMesh.ComputeFaceArea(f_it.handle());
	}
	for (uint i = 0; i < n; ++i)
	{
		mLapWeight[i] = m_Options.laplacianConstraintWeight;
		mPosWeight[i] = m_Options.positionalConstraintWeight;
	}
	LOG_TRACE << "Skeletonizer Initialize ok";
	boost::timer timer;
	timer.restart();
	SparseMatrix tmp_A;
	BuildSMatrixA(tmp_A);
	LOG_TRACE << "SparseMatrix BuildMatrixA " << tmp_A.GetRowSize() << ", " << tmp_A.GetColSize() 
		<< " nnz:" << tmp_A.NumOfElements() << " elapsed: " << timer.elapsed();
	timer.restart();
	mCCSA = CCSMatrix(tmp_A);
	LOG_TRACE << "Convert to CCSMatrix finish!";
	mCCSATA = CCSMatrixATA(mCCSA);
	LOG_TRACE << "SparseMatrix MultiplyATA " << mCCSATA.GetRowSize() << ", " << mCCSATA.GetColSize() 
		<< " nnz:" << mCCSATA.GetNumNonZero() << " elapsed: " << timer.elapsed();
	

	if(m_Options.useSymbolicSolver)
	{
		LOG_TRACE << "Start Build SymbolicSolver!";
		mSymbolicSolver = SymbolicFactorization(mCCSATA);
		LOG_TRACE << "Build SymbolicSolver finish!";
		int ret = NumericFactorization(mSymbolicSolver, mCCSATA);
		LOG_TRACE << "Build NumericFactor result = " << ret;
	}
	else
	{
		LOG_TRACE << "Start Build Solver!";
		mSolver = Factorization(mCCSATA);
		if (mSolver == 0)
			LOG_FATAL << "Build Solver FATAL!";
		else
			LOG_TRACE << "Build Solver finish!";
		for (int k = 0;k<20;++k)
			LOG_TRACE << "m_Solver->matrix->values " << k << ", " << mSolver->matrix->values.d[k];
	}

	osg::Vec3d vmax, vmin;
	double* bound = mMesh.GetBound();
	vmin[0] = bound[0];
	vmin[1] = bound[2];
	vmin[2] = bound[4];
	vmax[0] = bound[1];
	vmax[1] = bound[3];
	vmax[2] = bound[5];
	m_Mesh_Diag_Len = (vmax-vmin).length();
}

void Skeletonizer::BuildSMatrixA( SparseMatrix& A )
{
	int n = mMesh.n_vertices();
	int fn = mMesh.n_faces();
	LOG_TRACE  << "n:" << n << " fn: "<< fn;
	A = SparseMatrix(3*n, n);
	std::vector <double> areaRatio(fn) ;
	std::vector <bool >  collapsed(n) ;
	if (mOldAreaRatio.empty())
	{
		mOldAreaRatio.resize(fn);
		for(int i = 0; i < fn; i++)
			mOldAreaRatio[i]= 0.4;
	}
	Tri_Mesh::FIter		f_it;
	Tri_Mesh::FVIter	fv_it;
	Vec3 face[3], c;
	int i=0;
	for (f_it = mMesh.faces_begin(); f_it != mMesh.faces_end(); ++f_it, ++i)  {
		//取mesh的面
		int j=0;
		int c[3];
		for (fv_it = mMesh.fv_iter( f_it ); fv_it; ++fv_it, ++j) {
			//fviter找每個面 的handle

			const Tri_Mesh::Point& dp = mMesh.point(fv_it.handle());
			face[j][0] = dp[0];
			face[j][1] = dp[1];
			face[j][2] = dp[2];
			c[j] = fv_it.handle().idx();
		}
		const Vec3& v1 = face[0];
		const Vec3& v2 = face[1];
		const Vec3& v3 = face[2];
		areaRatio[i] = mMesh.ComputeFaceArea(f_it.handle()) / mOriginalFaceArea[i];
		if (i<100)LOG_TRACE << "areaRatio[" << i << "]: " << areaRatio[i];
		if (areaRatio[i] < m_Options.areaRatioThreshold)
		{
		}
		double cot1 = (v2 - v1).dotProduct(v3 - v1) / (v2 - v1).crossProduct(v3 - v1).length();
		double cot2 = (v3 - v2).dotProduct(v1 - v2) / (v3 - v2).crossProduct(v1 - v2).length();
		double cot3 = (v1 - v3).dotProduct(v2 - v3) / (v1 - v3).crossProduct(v2 - v3).length();
		if (_isnan(cot1) || _isnan(cot2) || _isnan(cot3))
		{
			LOG_FATAL << "nan: " << cot1 << " " << cot2 << "  " << cot3 << std::endl;
		}
		A.AddValueTo(c[1], c[1], -cot1); A.AddValueTo(c[1], c[2], cot1);
		A.AddValueTo(c[2], c[2], -cot1); A.AddValueTo(c[2], c[1], cot1);
		A.AddValueTo(c[2], c[2], -cot2); A.AddValueTo(c[2], c[0], cot2);
		A.AddValueTo(c[0], c[0], -cot2); A.AddValueTo(c[0], c[2], cot2);
		A.AddValueTo(c[0], c[0], -cot3); A.AddValueTo(c[0], c[1], cot3);
		A.AddValueTo(c[1], c[1], -cot3); A.AddValueTo(c[1], c[0], cot3);
	}
	LOG_TRACE << "face ok";
	LOG_TRACE << "SparseMatrix A's nnz: " << A.NumOfElements();
	double count = 0;
	const int_vector2d rows = A.GetRowIndex();
	for (int i = 0; i < n; i++)
	{
		double totRatio = 0;
		double oldTotRatio = 0;
		for (int_vector::iterator iit=mMesh.mAdjVF[i].begin();iit!=mMesh.mAdjVF[i].end();++iit)
		{
			totRatio += areaRatio[*iit];
			oldTotRatio += mOldAreaRatio[*iit];
		}
		totRatio /= mMesh.mAdjVF[i].size();
		//if (i<100)LOG_TRACE << "totRatio[" << i << "]: " << totRatio;
		oldTotRatio /= mMesh.mAdjVF[i].size();
		double tot = 0;
		cells& ce = A.GetRow(i);
		for (cells::const_iterator it = ce.begin();it != ce.end();++it)
		{
			if ((*it)->i != (*it)->j)
				tot += (*it)->value;
		}
		if (tot > 10000) 
		{
			collapsed[i] = true;
			mMesh.m_Flags[i] = 1;
			for (cells::iterator it = ce.begin();it != ce.end();++it)
			{
				(*it)->value /= (tot / 10000);
			}
		}
		for (cells::const_iterator it1 = ce.begin();it1 != ce.end();++it1)
			(*it1)->value *= mLapWeight[i];
		mLapWeight[i] *= m_Options.laplacianConstraintScale;
		if (mLapWeight[i] > 2048) mLapWeight[i] = 2048;
		double d = (1.0 / sqrt(totRatio)) * m_Options.positionalConstraintWeight;
		if (!(_isnan(d))) mPosWeight[i] = d;
		if (mPosWeight[i] > 10000) mPosWeight[i] = 10000;
		//if (i<100)LOG_TRACE << "m_posWeight[" << i << "]: " << m_posWeight[i];
		count++;
		bool ok = true;
		for (cells::const_iterator it = ce.begin();it != ce.end();++it)
		{
			if (_isnan((*it)->value))
			{
				ok = false;
				LOG_TRACE << "isnan test fail!";
				break;
			}
		}
		if (!ok)
		{
			for (cells::const_iterator it = ce.begin();it != ce.end();++it)
			{
				if ((*it)->i == (*it)->j)
					(*it)->value = -1;
				else
					(*it)->value = 1.0 / mMesh.mAdjVV[i].size();
			}
		}
	}
	LOG_TRACE << "weight ok";
	for (int i = 0; i < fn; i++)
		mOldAreaRatio[i] = areaRatio[i];
	for (int i = 0; i < n; i++)
		A.AddElement(i + n, i, mPosWeight[i]);
	for (int i = 0; i < n; i++)
		A.AddElement(i + n + n, i, m_Options.originalPositionalConstraintWeight);
	A.SortElement();
	LOG_TRACE << "SparseMatrix A's nnz: " << A.NumOfElements();
	//return A;
}

MMatrix Skeletonizer::BuildMatrixA()
{
	int n = mMesh.n_vertices();
	int fn =mMesh.n_faces();
	LOG_TRACE  << "n:" << n << " fn: "<< fn;
	MMatrix A( 3* n , n);
	std::vector <double> areaRatio(fn) ;
	std::vector <bool >  collapsed(n) ;
	if ( mOldAreaRatio.empty())
	{
		mOldAreaRatio.resize(fn);
		for(int i = 0; i < fn; i++)
		mOldAreaRatio[i]= 0.4;
	}
	Tri_Mesh::FIter		 f_it;
	Tri_Mesh::FVIter	fv_it;
	osg::Vec3d face[3], c;
	int i=0;
	for (f_it = mMesh.faces_begin(); f_it != mMesh.faces_end(); ++f_it)  {
		//取mesh的面
		int j=0;
		int c[3];
		for (fv_it = mMesh.fv_iter( f_it ); fv_it; ++fv_it, ++j) {
			//fviter找每個面 的handle

			const Tri_Mesh::Point& dp = mMesh.point(fv_it.handle());
			face[j][0] = dp[0];
			face[j][1] = dp[1];
			face[j][2] = dp[2];
			c[j] = fv_it.handle().idx();
		}
		Vec3 v1(face[0].ptr());
		Vec3 v2(face[1].ptr());
		Vec3 v3(face[2].ptr());
		
		areaRatio[i] = mMesh.ComputeFaceArea(f_it.handle()) / mOriginalFaceArea[i];
		if (areaRatio[i] < m_Options.areaRatioThreshold)
		{
		}

		double cot1 = (v2 - v1).dotProduct(v3 - v1) / (v2 - v1).crossProduct(v3 - v1).length();
		double cot2 = (v3 - v2).dotProduct(v1 - v2) / (v3 - v2).crossProduct(v1 - v2).length();
		double cot3 = (v1 - v3).dotProduct(v2 - v3) / (v1 - v3).crossProduct(v2 - v3).length();
		if (_isnan(cot1) || _isnan(cot2) || _isnan(cot3))
		{
			LOG_FATAL << "nan: " << cot1 << " " << cot2 << "  " << cot3 << std::endl;
		}
  
		A(c[1], c[1]) += -cot1; A(c[1], c[2]) += cot1;
		A(c[2], c[2]) += -cot1; A(c[2], c[1]) += cot1;
		A(c[2], c[2]) += -cot2; A(c[2], c[0]) += cot2;
		A(c[0], c[0]) += -cot2; A(c[0], c[2]) += cot2;
		A(c[0], c[0]) += -cot3; A(c[0], c[1]) += cot3;
		A(c[1], c[1]) += -cot3; A(c[1], c[0]) += cot3;  
	}
	LOG_TRACE << "face ok";
	LOG_TRACE << "Matrix A's nnz: " << A.nnz();
	double count = 0;
	TAUCS_CCS_Matrix_Double A_proxy(A);
	const int_vector2d rows = A_proxy.GetRowIndex();
	for (int i = 0; i < n; i++)
	{
		double totRatio = 0;
		double oldTotRatio = 0;
		for (int_vector::iterator it=mMesh.mAdjVF[i].begin();it!=mMesh.mAdjVF[i].end();++it)
		{
			totRatio += areaRatio[*it];
			oldTotRatio += mOldAreaRatio[*it];
		}
		totRatio /= mMesh.mAdjVF[i].size();
		oldTotRatio /= mMesh.mAdjVF[i].size();

		double tot = 0;
		for (unsigned w=0;w<rows[i].size();++w)
		{
			if (w != i) tot += A(rows[i][w], i);
		}
		if (tot > 10000) 
		{
			collapsed[i] = true;
			mMesh.m_Flags[i] = 1;
			for (size_t w=0;w<rows[i].size();++w)
			{
				A(rows[i][w], i) /= (tot / 10000);
			}
		}
		for (unsigned w=0;w<rows[i].size();++w)
			A(rows[i][w], i) *= mLapWeight[i];
		mLapWeight[i] *= m_Options.laplacianConstraintScale;
		if (mLapWeight[i] > 2048) mLapWeight[i] = 2048;
		double d = (1.0 / sqrt(totRatio)) * m_Options.positionalConstraintWeight;
		if (!(_isnan(d))) mPosWeight[i] = d;
		if (mPosWeight[i] > 10000) mPosWeight[i] = 10000;
		count++;
		bool ok = true;
		for (unsigned w=0;w<rows[i].size();++w)
		{
			if (_isnan(A(rows[i][w], i)))
			{
				ok = false;
			}
		}
		if (!ok)
		{
			for (unsigned w=0;w<rows[i].size();++w)
			{
				if (i == rows[i][w])
					A(rows[i][w], i) = -1;
				else
					A(rows[i][w], i) = 1.0 / mMesh.mAdjVV[i].size();
			}
		}
	}
	LOG_TRACE << "weight ok";
	for (int i = 0; i < fn; i++)
		mOldAreaRatio[i] = areaRatio[i];
	for (int i = 0; i < n; i++)
		A(i + n, i) = mPosWeight[i];
	for (int i = 0; i < n; i++)
		A(i + n + n, i) = m_Options.originalPositionalConstraintWeight;
	LOG_TRACE << "Matrix A's nnz: " << A.nnz();
	return A;
}

Vector Skeletonizer::Least_Square(Matrix_Mesh& m_mesh)
{
	int n = mMesh.n_vertices();
	int fn = mMesh.n_faces();
	MVector LSsol;
	MMatrix LSMat(3*n , n);
	std::vector <double> areaRatio(fn) ;
	Tri_Mesh::FIter		f_it;
	Tri_Mesh::FVIter	fv_it;
	osg::Vec3d face[3], c;
	int i=0;
	for (f_it = mMesh.faces_begin(); f_it != mMesh.faces_end(); ++f_it)  {
		int j=0;
		int c[3];
		for (fv_it = mMesh.fv_iter( f_it ); fv_it; ++fv_it, ++j) {
			const Tri_Mesh::Point& dp = mMesh.point(fv_it.handle());
			face[j][0] = dp[0];
			face[j][1] = dp[1];
			face[j][2] = dp[2];
			c[j] = fv_it.handle().idx();
		}
		Vec3 v1(face[0].ptr());
		Vec3 v2(face[1].ptr());
		Vec3 v3(face[2].ptr());

		areaRatio[i] = mMesh.ComputeFaceArea(f_it.handle()) / mOriginalFaceArea[i];
		if (areaRatio[i] < m_Options.areaRatioThreshold)
		{
		}

		double cot1 = (v2 - v1).dotProduct(v3 - v1) / (v2 - v1).crossProduct(v3 - v1).length();
		double cot2 = (v3 - v2).dotProduct(v1 - v2) / (v3 - v2).crossProduct(v1 - v2).length();
		double cot3 = (v1 - v3).dotProduct(v2 - v3) / (v1 - v3).crossProduct(v2 - v3).length();
		if (_isnan(cot1) || _isnan(cot2) || _isnan(cot3))
		{
			std::cerr << "nan: " << cot1 << " " << cot2 << "  " << cot3 << std::endl;
		}

		LSMat(c[1], c[1]) += -cot1; LSMat(c[1], c[2]) += cot1;
		LSMat(c[2], c[2]) += -cot1; LSMat(c[2], c[1]) += cot1;
		LSMat(c[2], c[2]) += -cot2; LSMat(c[2], c[0]) += cot2;
		LSMat(c[0], c[0]) += -cot2; LSMat(c[0], c[2]) += cot2;
		LSMat(c[0], c[0]) += -cot3; LSMat(c[0], c[1]) += cot3;
		LSMat(c[1], c[1]) += -cot3; LSMat(c[1], c[0]) += cot3;  
	}
	
	for (int a =0 ; a< n ; a++)
	{
		LSMat(a ,a) = 1 ; 
	}
	//LSMat = BuildMatrixA() ;
	Vector LSlap(3* n , 1 );
	for (int i=0 ; i< n; i++)
	{
		LSlap[i]=1;
	}

	LSsol = TAUCS_CCS_Matrix_Double(LSMat).Compute_x_By_Slover_Ax_B(LSlap);
	
	//std::cout<<"LSsol:" <<LSsol << std::endl ;
	//std::cout<<"LSMat:" <<LSMat << std::endl ;
	return LSsol;
}

void Skeletonizer::ImplicitSmooth()
{
	LOG_TRACE << "Start ImplicitSmooth";
	const int n = mMesh.n_vertices();
	double_vector x(n);
	double_vector b(3*n);
	double_vector ATb(n);
	for (int i = 0; i < 3; i++)
	{
		double_vector VertexPos;
		mMesh.GetVertexs(&VertexPos);
		assert(mOriginalVertexPos.size() == 3*n);
		int j=0, k=0;
		double tsum = 0;
		for (;j < n; ++j, k+=3) 
		{
			b[j] = 0;
			b[j + n] = VertexPos[k+i] * mPosWeight[j];
			tsum += b[j + n];
			b[j + n + n] = mOriginalVertexPos[k+i] * m_Options.originalPositionalConstraintWeight;
		}

		mCCSA.PreMultiply(&b[0], &ATb[0]);
		
		double* _x = &x[0];
		double* _ATb = &ATb[0];
		int ret;
		if (m_Options.useSymbolicSolver)
			ret = NumericSolve(mSymbolicSolver, _x, _ATb);
		else
			ret = Solve(mSolver, _x, _ATb);
		tsum = 0;
		LOG_TRACE << "Numeric solver: " << (ret == 0);
 		j=0;k=0;
		for (;j < n; ++j, k+=3)
		{
			mOriginalVertexPos[k+i] = x[j];
		}
 		k=0;
		LOG_DEBUG << i << " TotalFaceArea: " << mMesh.TotalFaceArea();
		for (BasicMesh::VertexIter v_it=mMesh.vertices_begin();
			v_it!=mMesh.vertices_end(); ++v_it, k+=3)
		{
			Tri_Mesh::Point& p = mMesh.point(v_it);
			p[i] = mOriginalVertexPos[k+i];
		}
		LOG_DEBUG << i << " TotalFaceArea: " << mMesh.TotalFaceArea();
	}
	iter++;
	SparseMatrix A;
	BuildSMatrixA(A);
	mCCSA = CCSMatrix(A);
	mCCSATA = CCSMatrixATA(mCCSA);

	if(m_Options.useSymbolicSolver)
	{
		FreeNumericFactor(mSymbolicSolver);
		int ret = NumericFactorization(mSymbolicSolver, mCCSATA);
		LOG_TRACE << "NumericFactorization: " << (ret == 0);
	}
	else
	{
		if (mSolver != NULL) FreeSolver(mSolver);
		mSolver = Factorization(mCCSATA);
		if (mSolver == NULL) 
		{
			LOG_FATAL << "m_Solver = Factorization(m_ccsATA);";
		}
		else
		{
			LOG_TRACE << "Build Solver finish!";
		}
	}
}

void Skeletonizer::Initialize()
{
	m_Options.noiseRatio				= 0.02;

	// options for geometry collapsing
	m_Options.maxIterations				= 30;
	//m_Options.laplacianConstraintWeight		= 1.0;
	m_Options.laplacianConstraintWeight = 1.0 / (10 * sqrt(mMesh.AverageFaceArea()));
	m_Options.positionalConstraintWeight		= 1.0;
	m_Options.originalPositionalConstraintWeight	= 0.0;
	m_Options.laplacianConstraintScale		= 2.0;
	m_Options.positionalConstraintScale		= 1.5;
	m_Options.areaRatioThreshold			= 0.001;
	m_Options.useSymbolicSolver			= false ;
	m_Options.useIterativeSolver			= false ;
	m_Options.volumneRatioThreashold		= 0.001 ;
	// options for simplification
	m_Options.applySimplification			= true;
	m_Options.useShapeEnergy			= true;
	m_Options.useSamplingEnergy			= true;
	m_Options.shapeEnergyWeight			= 0.1;
	m_Options.targetVertexCount			= 10;
	// options for embedding
	m_Options.applyEmbedding			= true;
	m_Options.numOfImprovement			= 100;
	m_Options.postSimplify				= true;
	m_Options.postSimplifyErrorRatio		= 0.9;
	m_Options.useBoundaryVerticesOnly		= true;

	void * solver					= NULL;
	void * symbolicSolver				= NULL;
	m_originalVolume;
	iter						= 0;
	displayBoneGeometry				= true ;
	displayBoneSkeletonJoint			= true ;
	useCompatibleColor				= false ;
	displaySkeleton2				= false ;
	boneScale					= 0.0035 ;
	jointScale					= 0.0035 ;
	jointScale2					= 0.0035 ;
	jointScale3					= 0.01 ;
	draw_bone_influence				= false;
	draw_missed_faces				= false;
	// display options
	displaySkeleton					= false;
	displayOriginalMesh				= false;
	displayNodeSphere				= false;
}

CCSMatrix Skeletonizer::CCSMatrixATA( const CCSMatrix& A )
{
	int_vector last(A.GetRowSize(), -1);
	int_vector next(A.GetNumNonZero(), -1);
	int_vector colIndex(A.GetNumNonZero());
	for (int i = 0; i < A.GetColSize(); i++)
	{
		for (int j = A.GetColIndex()[i]; j < A.GetColIndex()[i + 1]; j++)
		{
			int k = A.GetRowIndex()[j];
			if (last[k] != -1) next[last[k]] = j;
			last[k] = j;
			colIndex[j] = i;
		}
	}

	CCSMatrix ATA(A.GetColSize(), A.GetColSize());
	int_vector set;
	double_vector tmp(A.GetColSize(), 0);
	int_vector ATA_RowIndex;
	double_vector ATA_Value;

	for (int j = 0; j < A.GetColSize(); j++)
	{
		for (int col = A.GetColIndex()[j]; col < A.GetColIndex()[j + 1]; col++)
		{
			int k = A.GetRowIndex()[col];
			double val = A.GetValues()[col];
			int curr = col;
			while (true)
			{
				int i = colIndex[curr];
				set.push_back(i);
				tmp[i] += val * A.GetValues()[curr];
				if (next[curr] != -1)
					curr = next[curr];
				else
					break;
			}
		}
		std::sort(set.begin(), set.end());
		int count = 0;
		for (int_vector::iterator it = set.begin();it != set.end();++it)
		{
			if (tmp[*it] == 0) continue;
			ATA_RowIndex.push_back(*it);
			ATA_Value.push_back(tmp[*it]);
			tmp[*it] = 0;
			count++;
		}
		ATA.ColIndex()[j + 1] = ATA.GetColIndex()[j] + count;
		set.clear();
	}

	ATA.RowIndex() = ATA_RowIndex;
	ATA.Values() = ATA_Value;
	return ATA;
}

SparseMatrix Skeletonizer::Multiply1T( SparseMatrix& A1, SparseMatrix& A2 )
{
	SparseMatrix M(A1.GetColSize(), A2.GetColSize());
	double_vector tmp(A2.GetColSize(), 0);
	int_vector marked;

	for (int i = 0; i < A1.GetColSize(); i++)
	{
		marked.clear();
		cells& rr = A1.GetCol(i);
		for (cells::iterator it1 = rr.begin();it1 != rr.end();++it1)
		{
			cells& rr2 = A2.GetRow((*it1)->i);
			for (cells::iterator it2 = rr2.begin();it2 != rr2.end();++it2)
			{
				tmp[(*it2)->j] += (*it1)->value * (*it2)->value;
				marked.push_back((*it2)->j);   
			}
		}
		for (int_vector::iterator it = marked.begin();it != marked.end();++it)
		{
			if (tmp[*it] != 0)
			{
				M.AddElement(i, *it, tmp[*it]);
				tmp[*it] = 0;
			}
		}
	}
	M.SortElement();
	return M;
}

void Skeletonizer::GeometryCollapse( int maxIter )
{
	LOG_TRACE << "[GeometryCollapse]";
	//if (m_collapsedVertexPos.empty()) return ;
	iter = 0;
	double volume;
	do
	{
		ImplicitSmooth();
		volume = mMesh.GetVolume();
	}
	while (volume / m_originalVolume > m_Options.volumneRatioThreashold && iter < maxIter);
}


