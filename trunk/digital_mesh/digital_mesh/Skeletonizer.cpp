#include <cstdlib>
#include <vector>
#include <cassert>
#include <iomanip>
#include <queue>
#include <boost/timer.hpp>

#include "Skeletonizer.h"

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
	mOriginalVolume = mMesh.GetVolume();
	mMesh.GetVertexs(&mOriginalVertexPos);
	this->mOriginalFaceArea.resize(fn);
	int f_count = 0;
	for (BasicMesh::FaceIter f_it = mMesh.faces_begin(); f_it != mMesh.faces_end(); ++f_it) 
	{
		mOriginalFaceArea[f_count++] = mMesh.ComputeFaceArea(f_it.handle());
	}
	for (uint i = 0; i < n; ++i)
	{
		mLapWeight[i] = mOptions.laplacianConstraintWeight;
		mPosWeight[i] = mOptions.positionalConstraintWeight;
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
	

	if(mOptions.useSymbolicSolver)
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
	}

	osg::Vec3d vmax, vmin;
	double* bound = mMesh.GetBound();
	vmin[0] = bound[0];
	vmin[1] = bound[2];
	vmin[2] = bound[4];
	vmax[0] = bound[1];
	vmax[1] = bound[3];
	vmax[2] = bound[5];
	mMeshDiagLen = (vmax-vmin).length();
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
		//if (i<100)LOG_TRACE << "areaRatio[" << i << "]: " << areaRatio[i];
		if (areaRatio[i] < mOptions.areaRatioThreshold)
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
			mMesh.mFlags[i] = 1;
			for (cells::iterator it = ce.begin();it != ce.end();++it)
			{
				(*it)->value /= (tot / 10000);
			}
		}
		for (cells::const_iterator it1 = ce.begin();it1 != ce.end();++it1)
			(*it1)->value *= mLapWeight[i];
		mLapWeight[i] *= mOptions.laplacianConstraintScale;
		if (mLapWeight[i] > 2048) mLapWeight[i] = 2048;
		double d = (1.0 / sqrt(totRatio)) * mOptions.positionalConstraintWeight;
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
		A.AddElement(i + n + n, i, mOptions.originalPositionalConstraintWeight);
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
		if (areaRatio[i] < mOptions.areaRatioThreshold)
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
			mMesh.mFlags[i] = 1;
			for (size_t w=0;w<rows[i].size();++w)
			{
				A(rows[i][w], i) /= (tot / 10000);
			}
		}
		for (unsigned w=0;w<rows[i].size();++w)
			A(rows[i][w], i) *= mLapWeight[i];
		mLapWeight[i] *= mOptions.laplacianConstraintScale;
		if (mLapWeight[i] > 2048) mLapWeight[i] = 2048;
		double d = (1.0 / sqrt(totRatio)) * mOptions.positionalConstraintWeight;
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
		A(i + n + n, i) = mOptions.originalPositionalConstraintWeight;
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
		if (areaRatio[i] < mOptions.areaRatioThreshold)
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
			b[j + n + n] = mOriginalVertexPos[k+i] * mOptions.originalPositionalConstraintWeight;
		}

		mCCSA.PreMultiply(&b[0], &ATb[0]);
		
		double* _x = &x[0];
		double* _ATb = &ATb[0];
		int ret;
		if (mOptions.useSymbolicSolver)
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

	if(mOptions.useSymbolicSolver)
	{
		if (mSymbolicSolver)
			FreeNumericFactor(mSymbolicSolver);
		int ret = NumericFactorization(mSymbolicSolver, mCCSATA);
		LOG_TRACE << "NumericFactorization: " << (ret == 0);
	}
	else
	{
		if (mSolver)
			FreeSolver(mSolver);
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
	mOptions.noiseRatio				= 0.02;

	// options for geometry collapsing
	mOptions.maxIterations				= 30;
	//m_Options.laplacianConstraintWeight		= 1.0;
	mOptions.laplacianConstraintWeight = 1.0 / (10 * sqrt(mMesh.AverageFaceArea()));
	mOptions.positionalConstraintWeight		= 1.0;
	mOptions.originalPositionalConstraintWeight	= 0.0;
	mOptions.laplacianConstraintScale		= 2.0;
	mOptions.positionalConstraintScale		= 1.5;
	mOptions.areaRatioThreshold			= 0.001;
	mOptions.useSymbolicSolver			= false ;
	mOptions.useIterativeSolver			= false ;
	mOptions.volumneRatioThreashold		= 0.001 ;
	// options for simplification
	mOptions.applySimplification			= true;
	mOptions.useShapeEnergy			= true;
	mOptions.useSamplingEnergy			= true;
	mOptions.shapeEnergyWeight			= 0.1;
	mOptions.targetVertexCount			= 500;
	// options for embedding
	mOptions.applyEmbedding			= true;
	mOptions.numOfImprovement			= 10;
	mOptions.postSimplify				= true;
	mOptions.postSimplifyErrorRatio		= 0.9;
	mOptions.useBoundaryVerticesOnly		= true;

	void * solver					= NULL;
	void * symbolicSolver				= NULL;
	mOriginalVolume;
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
	while (volume / mOriginalVolume > mOptions.volumneRatioThreashold && iter < maxIter);
}

void Skeletonizer::UpdateVertexRecords( VertexRecord& rec1 )
{
	Vec3& p1 = rec1.mPos;
	if (rec1.mAdjV.size() > 1 && rec1.mAdjF.size() > 0) // Do not allow collapse at the end of skeleton
	{
		double totLength = 0;
		for (int_vector::iterator it = rec1.mAdjV.begin();it != rec1.mAdjV.end();++it)
		{
			VertexRecord& rec2 = *mVecRecords[*it];
			totLength += (p1 - rec2.mPos).length();
		}
		totLength /= rec1.mAdjV.size();
		
		for (int_vector::iterator it = rec1.mAdjV.begin();it != rec1.mAdjV.end();++it)
		{
			const int j = *it;
			bool found = false;
			for (int_vector::iterator it_idx = rec1.mAdjF.begin();it_idx != rec1.mAdjF.end();++it_idx)
			{
				int t = (*it_idx) * 3;
				int c1 = mFaceIndex[t];
				int c2 = mFaceIndex[t + 1];
				int c3 = mFaceIndex[t + 2];
				//LOG_TRACE << "i " << rec1.mVecIndex << " j " << j << " c1 " << c1 << " c2 " << c2 << " c3 " << c3;
				if (c1 == j || c2 == j || c3 == j)
				{
					found = true;
					//LOG_TRACE << "c1 " << c1 << " c2 " << c2 << " c3 " << c3;
					break;
				}
			}
			if (!found) continue;

			VertexRecord& rec2 = *mVecRecords[j];
			Vec3& p2 = rec2.mPos;
			if (rec2.mAdjF.size() == 0) continue;

			double err = 0;
			if (mOptions.useSamplingEnergy)
			{
				err = (p1 - p2).length() * totLength;
			}

			if (mOptions.useShapeEnergy)
			{
				Vec4 v1(p2);
				Vec4 v2((p1 + p2) / 2.0);
				Mat4 m = (rec1.mMatrix + rec2.mMatrix);
				double e1 = v1.dotProduct(m * v1) * mOptions.shapeEnergyWeight;
				double e2 = v2.dotProduct(m * v2) * mOptions.shapeEnergyWeight;
				if (e1 < e2)
					err += e1;
				else
				{
					err += e2;
					rec1.mCenter = true;
				}
			}

			if (err < rec1.mMinError)
			{
				rec1.mMinError = err;
				rec1.mMinIndex = j;
			}
		}
	}
}

void Skeletonizer::AssignColorIndex()
{
	LOG_TRACE << "[AssignColorIndex]" ;
	return;
	if (mSimplifiedVertexRec.empty()) return;
	const int COLOR_NUM = 3;
	bool used[COLOR_NUM]; // total 3 colors
	VertexRecord_queue q;

	for (VertexRecord_rawptrs::iterator it = mSimplifiedVertexRec.begin();
		it != mSimplifiedVertexRec.end(); ++it)
	{
		(*it)->mColorIndex = -1;
	}
	for (VertexRecord_rawptrs::iterator it = mSimplifiedVertexRec.begin();
		it != mSimplifiedVertexRec.end(); ++it)
	{
		VertexRecord* rec = *it;
		if (rec->mColorIndex != -1) 
			continue;
		q.push(rec);
		while (!q.empty())
		{
			VertexRecord* rec1 = q.front();
			q.pop();
			for (int i = 0; i < COLOR_NUM; i++)
				used[i] = false;
			for (int_vector::iterator it = rec1->mAdjV.begin();it != rec1->mAdjV.end();++it)
			{
				int adj = *it;
				VertexRecord* rec2 = mVecRecords[adj];
				if (rec2->mColorIndex != -1)
					used[mVecRecords[adj]->mColorIndex] = true;
				else
					q.push(rec2);
			}
			for (int i = 0; i < COLOR_NUM; i++)
				if (!used[i])
					rec1->mColorIndex = i;
			LOG_TRACE << "q.size() " << q.size();
		}
	}

	for (VertexRecord_rawptrs::iterator it = mSimplifiedVertexRec.begin();
		it != mSimplifiedVertexRec.end(); ++it)
	{
		VertexRecord& rec = **it;
		mMesh.mFlags[rec.mVecIndex] = (char)(rec.mColorIndex + 1);
		for (int_vector::iterator collapseFrom_it = rec.mCollapseFrom.begin();
			collapseFrom_it != rec.mCollapseFrom.end(); ++collapseFrom_it)
		{
			mMesh.mFlags[*collapseFrom_it] = (char)(rec.mColorIndex + 1);
		}	
	}
}

void Skeletonizer::Simplification()
{
	LOG_TRACE << "[Mesh Simplification]";
	int n = mMesh.n_vertices();
	mMesh.GetFaceVertexs(0, &mFaceIndex);
	for (int i = 0; i < n; i++)
		mVecRecords.push_back(new VertexRecord(mMesh, i));
	// init weights
	for (int i = 0; i < n; i++)
	{
		VertexRecord& rec1 = *mVecRecords[i];
		Vec3 p1 = rec1.mPos;

		if (mOptions.useShapeEnergy)
		{
			for (int_vector::iterator it = rec1.mAdjV.begin();it != rec1.mAdjV.end();++it)
			{
				Vec3& p2 = mVecRecords[*it]->mPos;
				Vec3 u = (p2 - p1).normalisedCopy();
				Vec3 w = u.crossProduct(p1);
				Mat4 m;
				m[0][1] = -u.z; m[0][2] =  u.y; m[0][3] = -w.x;
				m[1][0] =  u.z; m[1][2] = -u.x; m[1][3] = -w.y;
				m[2][0] = -u.y; m[2][1] =  u.x; m[2][3] = -w.z;
				rec1.mMatrix = rec1.mMatrix + m.transpose() * m;
			}
		}
		UpdateVertexRecords(rec1);
	}

	// put record into priority queue
	PQueue queue;
	for (int i = 0; i < n; i++)
		queue.Insert(mVecRecords[i]);

	int facesLeft = mMesh.n_faces();
	int vertexLeft = mMesh.n_vertices();
	int edgeLeft = 0;
	for (int i = 0; i < n; i++)
	{
		edgeLeft += (*mVecRecords[i]).mAdjV.size();
	}
	edgeLeft /= 2;
	while (facesLeft > 0 && vertexLeft > mOptions.targetVertexCount && !queue.Empty())
	{
		VertexRecord& rec1 = *((VertexRecord*)queue.Top());
		queue.Pop();
		VertexRecord& rec2 = *mVecRecords[rec1.mMinIndex];
		rec2.mMatrix = (rec1.mMatrix + rec2.mMatrix);
		if (rec1.mCenter)
			rec2.mPos = (rec1.mPos + rec2.mPos) / 2.0;
		rec2.mCollapseFrom.push_back(rec1.mVecIndex);
		for (int_vector::iterator it = rec1.mCollapseFrom.begin();it != rec1.mCollapseFrom.end();++it)
		{
			rec2.mCollapseFrom.push_back(*it);
		}
		rec1.mCollapseFrom.clear();
		int r1 = rec1.mVecIndex;
		int r2 = rec2.mVecIndex;
		int count = 0;

		for (int_vector::iterator it = rec1.mAdjF.begin();it != rec1.mAdjF.end();++it)
		{
			int index = *it;
			int t = index * 3;
			int c1 = mFaceIndex[t];
			int c2 = mFaceIndex[t + 1];
			int c3 = mFaceIndex[t + 2];

			if ((c1 == r2 || c2 == r2 || c3 == r2) ||
				(c1 == c2 || c2 == c3 || c3 == c1))
			{
				// remove adj faces
				for (int_vector::iterator it2 = rec1.mAdjV.begin();it2 != rec1.mAdjV.end();++it2)
				{
					int index2 = *it2;
					int_vector::iterator res = find(mVecRecords[index2]->mAdjF.begin(), mVecRecords[index2]->mAdjF.end(), index);
					if (res != mVecRecords[index2]->mAdjF.end())
					{
						mVecRecords[index2]->mAdjF.erase(res);
					}
				}
				// decrease face count
				facesLeft--;
				count++;
			}
			else
			{
				// update face index
				if (c1 == r1) mFaceIndex[t] = r2;
				if (c2 == r1) mFaceIndex[t + 1] = r2;
				if (c3 == r1) mFaceIndex[t + 2] = r2;
				// add adj faces
				rec2.mAdjF.push_back(index);
			}
		}

		// fix adj vertices
		for (int_vector::iterator it = rec1.mAdjV.begin();it != rec1.mAdjV.end();++it)
		{
			int index = *it;
			VertexRecord& recAdj = *mVecRecords[index];
			int_vector::iterator res = std::find(recAdj.mAdjV.begin(), recAdj.mAdjV.end(), r1);
			if (res != recAdj.mAdjV.end())
			{
				recAdj.mAdjV.erase(res);
				edgeLeft--;
			}
			if (index != r2)
			{
				recAdj.mAdjV.push_back(r2);
				rec2.mAdjV.push_back(index);
			}
		}

		// update records
		for (int_vector::iterator it = rec2.mAdjV.begin();it != rec2.mAdjV.end();++it)
		{
			int index = *it;
			UpdateVertexRecords(*mVecRecords[index]);
			queue.Update(*mVecRecords[index]);
		}
		UpdateVertexRecords(rec2);
		queue.Update(rec2);

		for (int_vector::iterator it = rec2.mAdjF.begin();it != rec2.mAdjF.end();++it)
		{
			int index = *it;
			int t = index * 3;
			int c1 = mFaceIndex[t];
			int c2 = mFaceIndex[t + 1];
			int c3 = mFaceIndex[t + 2];
			if (c1 == c2 || c2 == c3 || c3 == c1)
			{
				int_vector::iterator res = std::find(rec2.mAdjF.begin(), rec2.mAdjF.end(), index);
				if (res != rec2.mAdjF.end())
				{
					rec2.mAdjF.erase(res);
				}
				for (int_vector::iterator it = rec2.mAdjV.begin();it != rec2.mAdjV.end();++it)
				{
					int index2 = *it;
					int_vector& adjF = mVecRecords[index2]->mAdjF;
					int_vector::iterator res = std::find(adjF.begin(), adjF.end(), index);
					if (res != adjF.end())
					{
						adjF.erase(res);
					}
					// decrease face count
					facesLeft--;
				}
			}
		}
		if (count == 0)
		{
			//LOG_DEBUG << "!";
		}
		// decrease vertex count
		vertexLeft--;
	}

	// copy remaining vertices to resulting list
	while (!queue.Empty())
	{
		VertexRecord* rec = (VertexRecord*)queue.Top();
		queue.Pop();
		mSimplifiedVertexRec.push_back(rec);
	}

	AssignColorIndex();

	LOG_TRACE << "Nodes:" << mSimplifiedVertexRec.size();
}

void Skeletonizer::MergeJoint2()
{
	int vn = mMesh.n_vertices();
	int_vector segmentIndex(vn);
	//#region init segment index
	for (VertexRecord_rawptrs::iterator it = mSimplifiedVertexRec.begin();
		it != mSimplifiedVertexRec.end(); ++it)
	{
		VertexRecord& rec = **it;
		rec.mCollapseFrom.push_back(rec.mVecIndex);
		for (int_vector::iterator it2 = rec.mCollapseFrom.begin();
			it2 != rec.mCollapseFrom.end(); ++it2)
		{
			segmentIndex[*it2] = rec.mVecIndex;
		}
	}
	//#endregion
	bool updated = false;

	do
	{
		for (VertexRecord_rawptrs::iterator it = mSimplifiedVertexRec.begin();
			it != mSimplifiedVertexRec.end(); ++it)
		{
			VertexRecord& rec = **it;
			if (rec.mCollapseFrom.empty()) continue;
			if (rec.mAdjV.size() <= 2) continue;

			Vec3 p = rec.mPos;
			updated = false;
			//#region compute radius
			double radius = 0;
			for (int_vector::iterator collapseFrom_it = rec.mCollapseFrom.begin();
				collapseFrom_it != rec.mCollapseFrom.end(); ++collapseFrom_it)
			{
				int index = *collapseFrom_it;
				Vec3 q(&mOriginalVertexPos[index * 3]);
				radius += (p - q).length();
			}
			radius /= rec.mCollapseFrom.size();
			//#endregion

			//#region compute sd
			double sd = 0;
			for (int_vector::iterator collapseFrom_it = rec.mCollapseFrom.begin();
				collapseFrom_it != rec.mCollapseFrom.end(); ++collapseFrom_it)
			{
				int index = *collapseFrom_it;
				Vec3 q(&mOriginalVertexPos[index * 3]);
				double diff = (p - q).length() - radius;
				sd += diff * diff;
			}
			sd /= rec.mCollapseFrom.size();
			sd = sqrt(sd);
			sd /= radius;
			//#endregion

			Vec3 minCenter;
			double minSD = DBL_MAX;
			double minRadius = DBL_MAX;
			int minAdj = -1;
			for (int_vector::iterator adjV_it = rec.mAdjV.begin();
				adjV_it != rec.mAdjV.end(); ++adjV_it)
			{
				int adj = *adjV_it;
				VertexRecord& rec2 = *mVecRecords[adj];
				if (rec2.mAdjV.size() == 1) continue;
				Vec3 newCenter;
				double newRadius = 0;
				double newSD = 0;
				//#region compute new center
				Vec3 dis;
				double totLen = 0;
				int_vector marked;

				for (int_vector::iterator collapseFrom_it = rec.mCollapseFrom.begin();
					collapseFrom_it != rec.mCollapseFrom.end(); ++collapseFrom_it)
				{
					int i = *collapseFrom_it;
					int_vector& adjVVi = mMesh.mAdjVV[i];
					for (int_vector::iterator it4 = adjVVi.begin();
						it4 != adjVVi.end(); ++it4)
					{
						int j = *it4;
						if (segmentIndex[j] != rec.mVecIndex && segmentIndex[j] != adj)
							marked.push_back(i);
					}
				}
				for (int_vector::iterator marked_it = marked.begin();
					marked_it != marked.end(); ++marked_it)
				{
					int i = *marked_it;
					Vec3 p1(&mOriginalVertexPos[i * 3]);
					double len = 0;
					int_vector& adjVVi = mMesh.mAdjVV[i];
					for (int_vector::iterator it4 = adjVVi.begin();
						it4 != adjVVi.end(); ++it4)
					{
						int j = *it4;
						int_vector::iterator res = std::find(marked.begin(), marked.end(), j);
						if (res != marked.end())
						{
							Vec3 u(&mOriginalVertexPos[j * 3]);
							len += (p1 - u).length();
						}
					}
					dis += p1 * len;
					totLen += len;
				}

				marked.clear();
				for (int_vector::iterator collapseFrom_it = rec2.mCollapseFrom.begin();
					collapseFrom_it != rec2.mCollapseFrom.end(); ++collapseFrom_it)
				{
					int i = *collapseFrom_it;
					int_vector& adjVV = mMesh.mAdjVV[i];
					for (int_vector::iterator adjVV_it = adjVV.begin();
						adjVV_it != adjVV.end(); ++adjVV_it)
					{
						int j =  *adjVV_it;
						if (segmentIndex[j] != rec2.mVecIndex && segmentIndex[j] != rec.mVecIndex)
							marked.push_back(i);
					}
				}
				for (int_vector::iterator marked_it = marked.begin();
					marked_it != marked.end(); ++marked_it)
				{
					int i = *marked_it;
					Vec3 p1(&mOriginalVertexPos[i * 3]);
					double len = 0;
					int_vector& adjVV = mMesh.mAdjVV[i];
					for (int_vector::iterator adjVV_it = adjVV.begin();
						adjVV_it != adjVV.end(); ++adjVV_it)
					{
						int j =  *adjVV_it;
						int_vector::iterator res = std::find(marked.begin(), marked.end(), j);
						if (res != marked.end())
						{
							Vec3 u(&mOriginalVertexPos[j * 3]);
							len += (p1 - u).length();
						}
					}
					dis += p1 * len;
					totLen += len;
				}
				if (totLen > 0)
					newCenter = dis / totLen;
				//#endregion

				//#region compute new radius
				for (int_vector::iterator collapseFrom_it = rec.mCollapseFrom.begin();
					collapseFrom_it != rec.mCollapseFrom.end(); ++collapseFrom_it)
				{
					int index = *collapseFrom_it;
					Vec3 q(&mOriginalVertexPos[index * 3]);
					newRadius += (newCenter - q).length();
				}
				for (int_vector::iterator collapseFrom_it = rec2.mCollapseFrom.begin();
					collapseFrom_it != rec2.mCollapseFrom.end(); ++collapseFrom_it)
				{
					int index = *collapseFrom_it;
					Vec3 q(&mOriginalVertexPos[index * 3]);
					newRadius += (newCenter - q).length();
				}
				newRadius /= (rec.mCollapseFrom.size() + rec2.mCollapseFrom.size());
				//#endregion

				//#region compute sd
				for (int_vector::iterator collapseFrom_it = rec.mCollapseFrom.begin();
					collapseFrom_it != rec.mCollapseFrom.end(); ++collapseFrom_it)
				{
					Vec3 q(&mOriginalVertexPos[*collapseFrom_it * 3]);
					double diff = (newCenter - q).length() - newRadius;
					newSD += diff * diff;
				}
				for (int_vector::iterator collapseFrom_it = rec2.mCollapseFrom.begin();
					collapseFrom_it != rec2.mCollapseFrom.end(); ++collapseFrom_it)
				{
					Vec3 q(&mOriginalVertexPos[*collapseFrom_it * 3]);
					double diff = (newCenter - q).length() - newRadius;
					newSD += diff * diff;
				}
				newSD /= (rec.mCollapseFrom.size() + rec2.mCollapseFrom.size());
				newSD = sqrt(newSD);
				newSD /= newRadius;
				//#endregion

				if (newSD < minSD)
				{
					minSD = newSD;
					minRadius = newRadius;
					minCenter = newCenter;
					minAdj = adj;
				}
			}


			//#region merge node if new SD is smaller
			if (minAdj != -1 && minSD < mOptions.postSimplifyErrorRatio * sd)
			{
				LOG_TRACE << (rec.mVecIndex + "=>" + minAdj);
				int r1 = rec.mVecIndex;
				VertexRecord& rec2 = *mVecRecords[minAdj];
				rec2.mPos = minCenter;
				rec2.mCollapseFrom.push_back(rec.mVecIndex);
				for (int_vector::iterator collapseFrom_it = rec.mCollapseFrom.begin();
					collapseFrom_it != rec.mCollapseFrom.end(); ++collapseFrom_it)
				{
					rec2.mCollapseFrom.push_back(*collapseFrom_it);
				}
				rec.mCollapseFrom.clear();
				updated = true;

				for (int_vector::iterator adjV_it = rec.mAdjV.begin();
					adjV_it != rec.mAdjV.end(); ++adjV_it)
				{
					int index = *adjV_it;
					VertexRecord& recAdj = *mVecRecords[index];
					int_vector::iterator res = std::find(recAdj.mAdjV.begin(), recAdj.mAdjV.end(), r1);
					if (res != recAdj.mAdjV.end())
					{
						recAdj.mAdjV.erase(res);
					}
					if (index != minAdj)
					{
						recAdj.mAdjV.push_back(minAdj);
						rec2.mAdjV.push_back(index);
					}
				}
			}
			//#endregion
		}
	} while (updated);

	VertexRecord_rawptrs updatedVertexRec;
	for (VertexRecord_rawptrs::iterator it = mSimplifiedVertexRec.begin();
		it != mSimplifiedVertexRec.end(); ++it)
	{
		VertexRecord& rec = **it;
		if (!rec.mCollapseFrom.empty())
			updatedVertexRec.push_back(&rec);
	}
	mSimplifiedVertexRec = updatedVertexRec;
}

void Skeletonizer::EmbeddingImproving()
{
	const int vn = mMesh.n_vertices();
	int_vector segmentIndex(vn);
	bool_vector marked(vn, false);

	// init local variables
	for (VertexRecord_rawptrs::iterator it = mSimplifiedVertexRec.begin();
		it != mSimplifiedVertexRec.end(); ++it)
	{
		VertexRecord& rec = **it;
		rec.mCollapseFrom.push_back(rec.mVecIndex);
		for (int_vector::iterator collapseFrom_it = rec.mCollapseFrom.begin();
			collapseFrom_it != rec.mCollapseFrom.end(); ++collapseFrom_it)
		{
			segmentIndex[*collapseFrom_it] = rec.mVecIndex;
		}
	}

	// for each skeletal node
	for (VertexRecord_rawptrs::iterator it = mSimplifiedVertexRec.begin();
		it != mSimplifiedVertexRec.end(); ++it)
	{
		VertexRecord& rec = **it;
		Vec3 totDis;
		rec.mPos = Vec3(&mOriginalVertexPos[rec.mVecIndex * 3]);
		if (rec.mAdjV.size() == 2)
		{
			// for each adjacent node
			for (int_vector::iterator adjV_it = rec.mAdjV.begin();
				adjV_it != rec.mAdjV.end(); ++adjV_it)
			{
				int adj = *adjV_it;
				Vec3 dis;
				Vec3 q;
				int_vector boundaryVertices;
				double totLen = 0;
				for (int_vector::iterator collapseFrom_it = rec.mCollapseFrom.begin();
					collapseFrom_it != rec.mCollapseFrom.end(); ++collapseFrom_it)
				{
					const int i = *collapseFrom_it;
					int_vector& adjVVi = mMesh.mAdjVV[i];
					for (int_vector::iterator it4 = adjVVi.begin();
						it4 != adjVVi.end(); ++it4)
					{
						int j = *it4;
						if (segmentIndex[j] == adj)
						{
							marked[i] = true;
							boundaryVertices.push_back(i);
							break;
						}
					}
				}
				for (int_vector::iterator boundaryVert_it = boundaryVertices.begin();
					boundaryVert_it != boundaryVertices.end(); ++boundaryVert_it)
				{
					const int i = *boundaryVert_it;
					Vec3 p1 = Vec3(&mOriginalVertexPos[i * 3]);
					BasicMesh::Point p = mMesh.point(mMesh.vertex_handle(i));
					Vec3 p2 = PointToVec3(p);
					double len = 0;
					int_vector& adjVVi = mMesh.mAdjVV[i];
					for (int_vector::iterator it4 = adjVVi.begin();
						it4 != adjVVi.end(); ++it4)
					{
						int j = *it4;
						if (marked[j])
						{
							Vec3 u = Vec3(&mOriginalVertexPos[j * 3]);
							len = (p1 - u).length();
						}
					}
					q += p2 * len;
					dis += (p1 - p2) * len;
					totLen += len;
				}
				marked = bool_vector(vn, false);

				Vec3 center = (q + dis) / totLen;
				if (totLen > 0) totDis += center;
			}
			//rec.mPos += totDis / rec.mAdjV.size();
			rec.mPos = totDis / rec.mAdjV.size();
		}
		else
		{
			Vec3 dis;
			double totLen = 0;
			for (int_vector::iterator collapseFrom_it = rec.mCollapseFrom.begin();
				collapseFrom_it != rec.mCollapseFrom.end(); ++collapseFrom_it)
			{
				int i = *collapseFrom_it;
				int_vector& adjVVi = mMesh.mAdjVV[i];
				for (int_vector::iterator it4 = adjVVi.begin();
					it4 != adjVVi.end(); ++it4)
				{
					int j = *it4;
					if (segmentIndex[j] != rec.mVecIndex)
					{ marked[i] = true; }
				}
			}
			for (int_vector::iterator collapseFrom_it = rec.mCollapseFrom.begin();
				collapseFrom_it != rec.mCollapseFrom.end(); ++collapseFrom_it)
			{
				int i = *collapseFrom_it;
				if (!marked[i]) continue;

				Vec3 p1 = Vec3(&mOriginalVertexPos[i * 3]);
				BasicMesh::Point p = mMesh.point(mMesh.vertex_handle(i));
				Vec3 p2 = PointToVec3(p);
				double len = 0;
				int_vector& adjVVi = mMesh.mAdjVV[i];
				for (int_vector::iterator it4 = adjVVi.begin();
					it4 != adjVVi.end(); ++it4)
				{
					int j = *it4;
					if (marked[j])
					{
						Vec3 u = Vec3(&mOriginalVertexPos[j * 3]);
						len += (p1 - u).length();
					}
				}
				//dis += (p - p2);
				dis += (p1 - rec.mPos) * len;
				totLen += len;
			}
			if (totLen > 0) rec.mPos += dis / totLen;
		}
	}
}

Vec3s Skeletonizer::GetSkeletonNodes() const
{
	Vec3s res;
	for (VertexRecord_rawptrs::const_iterator it = mSimplifiedVertexRec.begin();
		it != mSimplifiedVertexRec.end(); ++it)
	{
		res.push_back((*it)->mPos);
	}
	return res;
}

Vec3Lines Skeletonizer::GetSkeletonLines() const
{
	Vec3Lines res;
	for (VertexRecord_rawptrs::const_iterator it = mSimplifiedVertexRec.begin();
		it != mSimplifiedVertexRec.end(); ++it)
	{
		const VertexRecord& rec = **it;
		for (int_vector::const_iterator it = rec.mAdjV.begin();
			it != rec.mAdjV.end(); ++it) 
		{
			const VertexRecord& rec2 = *mVecRecords[*it];
			res.push_back(Vec3Line(rec.mPos, rec2.mPos));
		}
	}
	return res;
}

void Skeletonizer::BuildSkeletonGraph()
{
	//Program.PrintText("build graph \n");

	if (mSimplifiedVertexRec.empty()) return;

	// 		if (skeletonGraph == null) skeletonGraph = new AdjacencyGraph<int, Edge<int>>(false);
	// 		skeletonGraph.Clear();
	// 		foreach (VertexRecord rec in simplifiedVertexRec)
	// 		{
	// 			skeletonGraph.push_backVertex(rec.mVecIndex);
	// 		}
	// 		foreach (VertexRecord rec in simplifiedVertexRec)
	// 		{
	// 			foreach (int adj in rec.mAdjV)
	// 			{
	// 				VertexRecord rec2 = vRec[adj];
	// 				Edge<int> edge = new Edge<int>(rec.mVecIndex, rec2.vIndex);
	// 				if (skeletonGraph.ContainsEdge(rec.mVecIndex, rec2.vIndex) == false && skeletonGraph.ContainsEdge(rec2.vIndex, rec.mVecIndex) == false)
	// 					skeletonGraph.push_backEdge(edge);
	// 			}
	// 		}
}


