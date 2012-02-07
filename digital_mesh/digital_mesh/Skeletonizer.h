#pragma once

#include <vector>
#include <list> 
#include "Matrix_Mesh.h"
#include "TAUCS_CCS_Matrix.h"
#include "imath.h"
#include "SparseMatrix.h"
#include "CCSMatrix.h"
#include "taucs\my_solver.h"

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
	class VertexRecord
	{
		Ogre::Vector3 pos;
		double radius;
		int_vector adjV ;
		int_vector adjF ;
		int_vector collapseFrom ;
		int vIndex  ;
		int minIndex ;
		int pqIndex ;
		Ogre::Matrix4 matrix ;
		double minError ;
		int colorIndex ;
		bool center;
		double err ;
	};
public:
	double_vector m_originalVertexPos;
	double_vector m_collapsedVertexPos;
	double_vector m_lapWeight;
	double_vector m_posWeight;
	double_vector m_originalFaceArea;
	double_vector m_oldAreaRatio;
	std::vector<VertexRecord> m_vRec;
	std::list<VertexRecord> m_simplifiedVertexRec ;
	void* solver ;
	//SymbolicSolver	m_SymbolicSolver;
	SymbolicSolver_tag*	m_SymbolicSolver;
	//Solver		m_Solver;
	Solver_tag*		m_Solver;
	double m_Mesh_Diag_Len;
	double m_originalVolume;
	int iter ;
	int_vector  faceIndex ;
	bool displayBoneGeometry ;
	bool displayBoneSkeletonJoint ;
	bool useCompatibleColor ;
	bool displaySkeleton2 ;
	double boneScale ;
	double jointScale ;
	double jointScale2 ;
	double jointScale3 ;
	bool draw_bone_influence;
	bool draw_missed_faces;
	// display options
	bool displaySkeleton;
	bool displayOriginalMesh;
	bool displayNodeSphere;
private:
	Options		m_Options;
	Matrix_Mesh&	m_Mesh;
	void Initialize();
	MMatrix BuildMatrixA();
	SparseMatrix BuildSMatrixA();
	CCSMatrix CCSMatrixATA(const CCSMatrix& A);
	SparseMatrix Multiply1T(SparseMatrix& A1, SparseMatrix& A2);
	Solver_tag* Factorization(CCSMatrix C)
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
	Tri_Mesh readmesh;
	CCSMatrix m_ccsA;
	CCSMatrix m_ccsATA;
public:
	Skeletonizer(Matrix_Mesh& mesh, Options& opt);
	bool	ReadFile(std::string _fileName);
	Vector	Least_Square (Matrix_Mesh& mesh);
	void	ImplicitSmooth();
	void	GeometryCollapse(int maxIter);
};

