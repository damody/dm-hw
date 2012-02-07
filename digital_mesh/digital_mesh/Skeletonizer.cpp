
#include "Skeletonizer.h"
#include <cstdlib>
#include <vector>
#include <cassert>
#include <boost/timer.hpp>
#include "imath.h"
#include "Tri_Mesh.h"
#include "log_define.h"

Skeletonizer::Skeletonizer(Matrix_Mesh& mesh, Options& )
:m_Mesh(mesh)
{
	Initialize();
	int n  = m_Mesh.n_vertices();
	int fn = m_Mesh.n_faces();
	m_lapWeight.resize(n);
	m_posWeight.resize(n);
	//opt = opt;
	//if (opt.AddNoise) AddNoise();
	m_originalVolume = m_Mesh.GetVolume();
	m_originalVertexPos = m_Mesh.GetVectors();
	this->m_originalFaceArea.resize(fn);
	int f_count = 0;
	for (BasicMesh::FaceIter f_it = m_Mesh.faces_begin(); f_it != m_Mesh.faces_end(); ++f_it) 
	{
		m_originalFaceArea[f_count] = m_Mesh.ComputeFaceArea(f_it.handle());
		++f_count;
	}
	for (std::vector <int>::size_type i = 0; i != n; ++i)
	{
		m_lapWeight.push_back( m_Options.laplacianConstraintWeight );
		m_posWeight.push_back( m_Options.positionalConstraintWeight );
	}
	LOG_TRACE << "Skeletonizer Initialize ok";
	boost::timer timer;
#ifndef _DEBUG
	timer.restart();
	MMatrix A = BuildMatrixA();
	LOG_TRACE << "TAUCS_CCS_Matrix_Double BuildMatrixA " << A.size1() << ", " << A.size2() << " elapsed: " << timer.elapsed();
	MMatrix ATA(A.size1(), A.size1());
	timer.restart();
	ATA = MultiplyATA(A);
	LOG_TRACE << "TAUCS_CCS_Matrix_Double MultiplyATA " << ATA.size1() << ", " << ATA.size2() << " elapsed: " << timer.elapsed();
#endif // _DEBUG
	
	timer.restart();
	SparseMatrix tmp_A = BuildSMatrixA();
	LOG_TRACE << "SparseMatrix BuildMatrixA " << tmp_A.GetRowSize() << ", " << tmp_A.GetColSize() 
		<< " nnz:" << tmp_A.NumOfElements() << " elapsed: " << timer.elapsed();
	timer.restart();
	m_ccsA = CCSMatrix(tmp_A);
	LOG_TRACE << "Convert to CCSMatrix finish!";
	m_ccsATA = CCSMatrixATA(m_ccsA);
	LOG_TRACE << "SparseMatrix MultiplyATA " << m_ccsATA.GetRowSize() << ", " << m_ccsATA.GetColSize() 
		<< " nnz:" << m_ccsATA.GetNumNonZero() << " elapsed: " << timer.elapsed();
	
	if(m_Options.useSymbolicSolver)
	{
		LOG_TRACE << "Start Build SymbolicSolver!";
		m_SymbolicSolver = SymbolicFactorization(m_ccsATA);
		LOG_TRACE << "Build SymbolicSolver finish!";
		int ret = NumericFactorization(m_SymbolicSolver, m_ccsATA);
		LOG_TRACE << "Build NumericFactor result = " << ret;
	}
	else
	{
		LOG_TRACE << "Start Build Solver!";
		m_Solver = Factorization(m_ccsATA);
		if (m_Solver == 0)
			LOG_FATAL << "Build Solver FATAL!";
		else
			LOG_TRACE << "Build Solver finish!";
	}
	osg::Vec3f vmax, vmin;
	double* bound = m_Mesh.GetBound();
	vmin[0] = bound[0];
	vmin[1] = bound[2];
	vmin[2] = bound[4];
	vmax[0] = bound[1];
	vmax[1] = bound[3];
	vmax[2] = bound[5];
	m_Mesh_Diag_Len = (vmax-vmin).length();
}

SparseMatrix Skeletonizer::BuildSMatrixA()
{
	int n = m_Mesh.n_vertices();
	int fn = m_Mesh.n_faces();
	LOG_TRACE  << "n:" << n << " fn: "<< fn;
	SparseMatrix A(3*n, n);
	std::vector <double> areaRatio(fn) ;
	std::vector <bool >  collapsed(n) ;
	if (m_oldAreaRatio.empty())
	{
		m_oldAreaRatio.resize(fn);
		for(int i = 0; i < fn; i++)
			m_oldAreaRatio[i]= 0.4;
	}
	Tri_Mesh::FIter		f_it;
	Tri_Mesh::FVIter	fv_it;
	Vec3 face[3], c;
	float distance_from_p_to_face = -1;
	int i=0;
	for (f_it = m_Mesh.faces_begin(); f_it != m_Mesh.faces_end(); ++f_it)  {
		//取mesh的面
		int j=0;
		int c[3];
		for (fv_it = m_Mesh.fv_iter( f_it ); fv_it; ++fv_it, ++j) {
			//fviter找每個面 的handle

			const Tri_Mesh::Point& dp = m_Mesh.point(fv_it.handle());
			face[j][0] = dp[0];
			face[j][1] = dp[1];
			face[j][2] = dp[2];
			c[j] = fv_it.handle().idx();
		}
		const Vec3& v1 = face[0];
		const Vec3& v2 = face[1];
		const Vec3& v3 = face[2];
		areaRatio[i] = m_Mesh.ComputeFaceArea(f_it.handle()) / m_originalFaceArea[i];
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
		for (unsigned j=0;j < m_Mesh.m_adjVF[i].size();++j)
		{
			totRatio += areaRatio[m_Mesh.m_adjVF[i][j]];
			oldTotRatio += m_oldAreaRatio[m_Mesh.m_adjVF[i][j]];
		}
		totRatio /= m_Mesh.m_adjVF[i].size();
		oldTotRatio /= m_Mesh.m_adjVF[i].size();
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
			m_Mesh.m_Flags[i] = 1;
			for (cells::iterator it = ce.begin();it != ce.end();++it)
			{
				(*it)->value /= (tot / 10000);
			}
		}
		for (cells::const_iterator it1 = ce.begin();it1 != ce.end();++it1)
		{
			(*it1)->value *= m_lapWeight[i];
			m_lapWeight[i] *= m_Options.laplacianConstraintScale;
			if (m_lapWeight[i] > 2048) m_lapWeight[i] = 2048;
			double d = (1.0 / sqrt(totRatio)) * m_Options.positionalConstraintWeight;
			if (!(_isnan(d))) m_posWeight[i] = d;
			if (m_posWeight[i] > 10000) m_posWeight[i] = 10000;
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
						(*it)->value = 1.0 / m_Mesh.m_adjVV[i].size();
				}
			}
		}
	}
	LOG_TRACE << "weight ok";
	for (int i = 0; i < fn; i++)
		m_oldAreaRatio[i] = areaRatio[i];
	for (int i = 0; i < n; i++)
		A.AddElement(i + n, i, m_posWeight[i]);
	for (int i = 0; i < n; i++)
		A.AddElement(i + n + n, i, m_Options.originalPositionalConstraintWeight);
	LOG_TRACE << "SparseMatrix A's nnz: " << A.NumOfElements();
	return A;
}

MMatrix Skeletonizer::BuildMatrixA()
{
	int n = m_Mesh.n_vertices();
	int fn =m_Mesh.n_faces();
	LOG_TRACE  << "n:" << n << " fn: "<< fn;
	MMatrix A( 3* n , n);
	std::vector <double> areaRatio(fn) ;
	std::vector <bool >  collapsed(n) ;
	if ( m_oldAreaRatio.empty())
	{
		m_oldAreaRatio.resize(fn);
		for(int i = 0; i < fn; i++)
		m_oldAreaRatio[i]= 0.4;
	}
	Tri_Mesh::FIter		 f_it;
	Tri_Mesh::FVIter	fv_it;
	osg::Vec3f face[3], c;
	float distance_from_p_to_face = -1;
	int i=0;
	for (f_it = m_Mesh.faces_begin(); f_it != m_Mesh.faces_end(); ++f_it)  {
		//取mesh的面
		int j=0;
		int c[3];
		for (fv_it = m_Mesh.fv_iter( f_it ); fv_it; ++fv_it, ++j) {
			//fviter找每個面 的handle

			const Tri_Mesh::Point& dp = m_Mesh.point(fv_it.handle());
			face[j][0] = dp[0];
			face[j][1] = dp[1];
			face[j][2] = dp[2];
			c[j] = fv_it.handle().idx();
		}
		Vec3 v1(face[0].ptr());
		Vec3 v2(face[1].ptr());
		Vec3 v3(face[2].ptr());
		
		areaRatio[i] = m_Mesh.ComputeFaceArea(f_it.handle()) / m_originalFaceArea[i];
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
		for (unsigned j=0;j < m_Mesh.m_adjVF[i].size();++j)
		{
			totRatio += areaRatio[m_Mesh.m_adjVF[i][j]];
			oldTotRatio += m_oldAreaRatio[m_Mesh.m_adjVF[i][j]];
		}
		totRatio /= m_Mesh.m_adjVF[i].size();
		oldTotRatio /= m_Mesh.m_adjVF[i].size();

		double tot = 0;
		
		tot = 0;
		for (unsigned w=0;w<rows[i].size();++w)
		{
			if (w != i) tot += A(rows[i][w], i);
		}
		if (tot > 10000) 
		{
			collapsed[i] = true;
			m_Mesh.m_Flags[i] = 1;
			for (size_t w=0;w<rows[i].size();++w)
			{
				A(rows[i][w], i) /= (tot / 10000);
			}
		}
		for (unsigned w=0;w<rows[i].size();++w)
		{
			A(rows[i][w], i) *= m_lapWeight[i];
			m_lapWeight[i] *= m_Options.laplacianConstraintScale;
			if (m_lapWeight[i] > 2048) m_lapWeight[i] = 2048;
			double d = (1.0 / sqrt(totRatio)) * m_Options.positionalConstraintWeight;
			if (!(_isnan(d))) m_posWeight[i] = d;
			if (m_posWeight[i] > 10000) m_posWeight[i] = 10000;
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
						A(rows[i][w], i) = 1.0 / m_Mesh.m_adjVV[i].size();
				}
			}
		}
	}
	LOG_TRACE << "weight ok";
	for (int i = 0; i < fn; i++)
		m_oldAreaRatio[i] = areaRatio[i];
	for (int i = 0; i < n; i++)
		A(i + n, i) = m_posWeight[i];
	for (int i = 0; i < n; i++)
		A(i + n + n, i) = m_Options.originalPositionalConstraintWeight;
	LOG_TRACE << "Matrix A's nnz: " << A.nnz();
	return A;
}

Vector Skeletonizer::Least_Square(Matrix_Mesh& m_mesh)
{
	int n = m_Mesh.n_vertices();
	int fn = m_Mesh.n_faces();
	MVector LSsol;
	MMatrix LSMat(3*n , n);
	std::vector <double> areaRatio(fn) ;
	Tri_Mesh::FIter		f_it;
	Tri_Mesh::FVIter	fv_it;
	osg::Vec3f face[3], c;
	float distance_from_p_to_face = -1;
	int i=0;
	for (f_it = m_Mesh.faces_begin(); f_it != m_Mesh.faces_end(); ++f_it)  {
		int j=0;
		int c[3];
		for (fv_it = m_Mesh.fv_iter( f_it ); fv_it; ++fv_it, ++j) {
			const Tri_Mesh::Point& dp = m_Mesh.point(fv_it.handle());
			face[j][0] = dp[0];
			face[j][1] = dp[1];
			face[j][2] = dp[2];
			c[j] = fv_it.handle().idx();
		}
		Vec3 v1(face[0].ptr());
		Vec3 v2(face[1].ptr());
		Vec3 v3(face[2].ptr());

		areaRatio[i] = m_Mesh.ComputeFaceArea(f_it.handle()) / m_originalFaceArea[i];
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
	const int n = m_Mesh.n_vertices();
	double_vector x(n);
	double_vector b(3*n);
	double_vector ATb(n);
	m_originalVertexPos = m_Mesh.GetVectors();
	assert(m_originalVertexPos.size() == 3*n);
	for (int i = 0; i < 3; i++)
	{
		int j=0, k=0;
		double tsum = 0;
		for (;j < n; ++j, k+=3) 
		{
			b[j] = 0;
			b[j + n] = m_originalVertexPos[k+i] * m_posWeight[j];
			tsum += b[j + n];
			b[j + n + n] = m_originalVertexPos[k+i] * m_Options.originalPositionalConstraintWeight;
		}
		LOG_DEBUG << "sum: " << tsum;
		m_ccsA.PreMultiply(&b[0], &ATb[0]);
		double* _x = &x[0];
		double* _ATb = &ATb[0];
		int ret;
		if (m_Options.useSymbolicSolver)
			ret = NumericSolve(m_SymbolicSolver, _x, _ATb);
		else
			ret = Solve(m_Solver, _x, _ATb);
		LOG_TRACE << "Numeric solver: " << (ret == 0);
 		j=0;k=0;
		for (;j < n; ++j, k+=3)
		{
			m_originalVertexPos[k+i] = x[j];
		}
 		k=0;
		for (BasicMesh::VertexIter v_it=m_Mesh.vertices_begin();
			v_it!=m_Mesh.vertices_end(); ++v_it, k+=3)
		{
			Tri_Mesh::Point& p = m_Mesh.point(v_it);
			p[i] = m_originalVertexPos[k+i];
		}
	}
	iter++;
	SparseMatrix A = BuildSMatrixA();
	m_ccsA = CCSMatrix(A);
	m_ccsATA = CCSMatrixATA(m_ccsA);

	if(m_Options.useSymbolicSolver)
	{
		FreeNumericFactor(m_SymbolicSolver);
		int ret = NumericFactorization(m_SymbolicSolver, m_ccsATA);
		LOG_TRACE << "NumericFactorization: " << (ret == 0);
	}
	else
	{
		if (m_Solver != NULL) FreeSolver(m_Solver);
		m_Solver = Factorization(m_ccsATA);
		if (m_Solver == NULL) 
		{
			LOG_FATAL << "m_Solver = Factorization(m_ccsATA);";
		}
	}
}

void Skeletonizer::Initialize()
{
	m_Options.noiseRatio				= 0.02;

	// options for geometry collapsing
	m_Options.maxIterations				= 30;
	m_Options.laplacianConstraintWeight		= 1.0;
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
// 	if (m_collapsedVertexPos.empty())
// 		return ;
	iter = 0;
	double volume;
	do
	{
		ImplicitSmooth();
		volume = m_Mesh.GetVolume();
	}
	while (volume / m_originalVolume > m_Options.volumneRatioThreashold && iter < maxIter);
}


