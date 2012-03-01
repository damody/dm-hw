#pragma once

#include <vector>
#include <list> 
#include "Matrix_Mesh.h"
#include "TAUCS_CCS_Matrix.h"
#include "imath.h"
#include "SparseMatrix.h"
#include "CCSMatrix.h"
#include "VertexRecord.h"
#include "taucs\my_solver.h"
#include "PQueue.h"

class Skeletonizer
{
public:
	class Options
	{
	public:
		// general options
		bool addNoise ;
		double noiseRatio;// = 0.02int_vector
		bool twoDimensionModel ;
		bool applyRootFinding ;
		// options for geometry collapsing
		int maxIterations;// = 30
		double laplacianConstraintWeight ;
		double positionalConstraintWeight ;
		double originalPositionalConstraintWeight ;
		double laplacianConstraintScale ;
		double positionalConstraintScale ;
		double areaRatioThreshold ;
		bool useSymbolicSolver ;
		bool useIterativeSolver ;
		double volumneRatioThreashold ;
		// options for simplification
		bool applySimplification ;
		bool useShapeEnergy ;
		bool useSamplingEnergy ;
		double shapeEnergyWeight ;
		int targetVertexCount ;
		// options for embedding
		bool applyEmbedding ;
		int numOfImprovement ;
		bool postSimplify ;
		double postSimplifyErrorRatio ;
		bool useBoundaryVerticesOnly ;
	};

private:
	Options		m_Options;
	Matrix_Mesh&	mMesh;
	void Initialize();
	MMatrix BuildMatrixA();
	void BuildSMatrixA(SparseMatrix& A);
	CCSMatrix CCSMatrixATA(const CCSMatrix& A);
	SparseMatrix Multiply1T(SparseMatrix& A1, SparseMatrix& A2);
	Solver_tag* Factorization(CCSMatrix& C)
	{
		int	*ri = &(C.RowIndex()[0]),
			*ci = &(C.ColIndex()[0]);
		double	*val = &(C.Values()[0]);
		return CreaterCholeskySolver(C.GetColSize(), C.GetNumNonZero(), ri, ci, val);
	}
	SymbolicSolver_tag* SymbolicFactorization(CCSMatrix& C)
	{
		int	*ri = &(C.RowIndex()[0]),
			*ci = &(C.ColIndex()[0]);
		double	*val = &(C.Values()[0]);
		return CreaterSymbolicSolver(C.GetColSize(), C.GetNumNonZero(), ri, ci, val);
	}
	int NumericFactorization(SymbolicSolver_tag* symoblicSolver, CCSMatrix& C)
	{
		int	*ri = &(C.RowIndex()[0]),
			*ci = &(C.ColIndex()[0]);
		double	*val = &(C.Values()[0]);
		return NumericFactor(symoblicSolver, C.GetColSize(), C.GetNumNonZero(), ri, ci, val);
	}
private:
	double_vector mOriginalVertexPos;
	double_vector mCollapsedVertexPos;
	double_vector mLapWeight;
	double_vector mPosWeight;
	double_vector mOriginalFaceArea;
	double_vector mOldAreaRatio;
	VertexRecord_sptrs mVecRecords;
	VertexRecord_sptrs mSimplifiedVertexRec;
	void* solver ;
	//SymbolicSolver	m_SymbolicSolver;
	SymbolicSolver_tag*	mSymbolicSolver;
	//Solver		m_Solver;
	Solver_tag*		mSolver;
	double	mMeshDiagLen;
	double	mOriginalVolume;
	int	iter;
	bool	displayBoneGeometry;
	bool	displayBoneSkeletonJoint;
	bool	useCompatibleColor;
	bool	displaySkeleton2;
	double	boneScale;
	double	jointScale;
	double	jointScale2;
	double	jointScale3;
	bool	draw_bone_influence;
	bool	draw_missed_faces;
	// display options
	bool	displaySkeleton;
	bool	displayOriginalMesh;
	bool	displayNodeSphere;
	CCSMatrix	mCCSA;
	CCSMatrix	mCCSATA;
	int_vector	mFaceIndex;
	
public:
	Skeletonizer(Matrix_Mesh& mesh, Options& opt);
	bool	ReadFile(std::string _fileName);
	Vector	Least_Square (Matrix_Mesh& mesh);
	void	ImplicitSmooth();
	void	GeometryCollapse(int maxIter);
	void	UpdateVertexRecords(VertexRecord& rec1);
	void	Simplification();
	void	AssignColorIndex();
 	void	MergeJoint2();
};

