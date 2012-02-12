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
	std::vector<VertexRecord> mVecRecord;
	std::list<VertexRecord> mSimplifiedVertexRec;
	void* solver ;
	//SymbolicSolver	m_SymbolicSolver;
	SymbolicSolver_tag*	mSymbolicSolver;
	//Solver		m_Solver;
	Solver_tag*		mSolver;
	double m_Mesh_Diag_Len;
	double m_originalVolume;
	int  iter;
	bool displayBoneGeometry;
	bool displayBoneSkeletonJoint;
	bool useCompatibleColor;
	bool displaySkeleton2;
	double boneScale;
	double jointScale;
	double jointScale2;
	double jointScale3;
	bool draw_bone_influence;
	bool draw_missed_faces;
	// display options
	bool displaySkeleton;
	bool displayOriginalMesh;
	bool displayNodeSphere;
	CCSMatrix	mCCSA;
	CCSMatrix	mCCSATA;
	int_vector	mFaceIndex;
public:
	Skeletonizer(Matrix_Mesh& mesh, Options& opt);
	bool	ReadFile(std::string _fileName);
	Vector	Least_Square (Matrix_Mesh& mesh);
	void	ImplicitSmooth();
	void	GeometryCollapse(int maxIter);
	
	void Simplification()
	{
		LOG_TRACE << "[Mesh Simplification]";

 		int n = mMesh.n_vertices();
		double_vector vertexs;
		mMesh.GetVertexs(&vertexs, &mFaceIndex);

// 		vRec = new VertexRecord[n];
// 		for (int i = 0; i < n; i++)
// 			vRec[i] = new VertexRecord(mesh, i);
// 
// 		//RemoveFaces();
// 
// 		// init weights
// 		for (int i = 0; i < n; i++)
// 		{
// 			VertexRecord rec1 = vRec[i];
// 			Vector3d p1 = rec1.pos;
// 			rec1.minError = double.MaxValue;
// 			rec1.minIndex = -1;
// 
// 			if (opt.UseShapeEnergy)
// 				foreach (int j in rec1.adjV)
// 			{
// 				Vector3d p2 = vRec[j].pos;
// 				Vector3d u = (p2 - p1).Normalize();
// 				Vector3d w = u.Cross(p1);
// 				Matrix4d m = new Matrix4d();
// 				m[0, 1] = -u.z; m[0, 2] = u.y; m[0, 3] = -w.x;
// 				m[1, 0] = u.z; m[1, 2] = -u.x; m[1, 3] = -w.y;
// 				m[2, 0] = -u.y; m[2, 1] = u.x; m[2, 3] = -w.z;
// 				rec1.matrix += m.Transpose() * m;
// 			}
// 			UpdateVertexRecords(rec1);
// 		}
// 
// 		// put record into priority queue
// 		PriorityQueue queue = new PriorityQueue(n);
// 		for (int i = 0; i < n; i++) queue.Insert(vRec[i]);
// 
// 		int facesLeft = mesh.FaceCount;
// 		int vertexLeft = mesh.VertexCount;
// 		int edgeLeft = 0;
// 		foreach (VertexRecord rec in vRec)
// 			foreach (int i in rec.adjV)
// 			edgeLeft++;
// 		edgeLeft /= 2;
// 		while (facesLeft > 0 && vertexLeft > opt.TargetVertexCount && !queue.IsEmpty())
// 		{
// 			VertexRecord rec1 = (VertexRecord)queue.DeleteMin();
// 			VertexRecord rec2 = vRec[rec1.minIndex];
// 			rec2.matrix = (rec1.matrix + rec2.matrix);
// 			if (rec1.center)
// 				rec2.pos = (rec1.pos + rec2.pos) / 2.0;
// 			rec2.collapseFrom.Add(rec1.vIndex);
// 			foreach (int index in rec1.collapseFrom) rec2.collapseFrom.Add(index);
// 			rec1.collapseFrom = null;
// 			int r1 = rec1.vIndex;
// 			int r2 = rec2.vIndex;
// 			int count = 0;
// 
// 			//if (facesLeft % 2 == 1) throw new Exception();
// 			//				Program.PrintText((facesLeft - edgeLeft + vertexLeft).ToString());
// 			// 				Program.PrintText(facesLeft + " " + vertexLeft);
// 
// 			foreach (int index in rec1.adjF)
// 			{
// 				int t = index * 3;
// 				int c1 = faceIndex[t];
// 				int c2 = faceIndex[t + 1];
// 				int c3 = faceIndex[t + 2];
// 
// 				if ((c1 == r2 || c2 == r2 || c3 == r2) ||
// 					(c1 == c2 || c2 == c3 || c3 == c1))
// 				{
// 					// remove adj faces
// 					foreach (int index2 in rec1.adjV)
// 						vRec[index2].adjF.Remove(index);
// 					// decrease face count
// 					facesLeft--;
// 					count++;
// 				}
// 				else
// 				{
// 					// update face index
// 					if (c1 == r1) faceIndex[t] = r2;
// 					if (c2 == r1) faceIndex[t + 1] = r2;
// 					if (c3 == r1) faceIndex[t + 2] = r2;
// 
// 					// add adj faces
// 					rec2.adjF.Add(index);
// 				}
// 			}
// 
// 			// fix adj vertices
// 			foreach (int index in rec1.adjV)
// 			{
// 				VertexRecord recAdj = vRec[index];
// 				if (recAdj.adjV.Contains(r1))
// 				{
// 					recAdj.adjV.Remove(r1);
// 					edgeLeft--;
// 				}
// 				if (index != r2)
// 				{
// 					recAdj.adjV.Add(r2);
// 					rec2.adjV.Add(index);
// 				}
// 			}
// 
// 			// update records
// 			foreach (int index in rec2.adjV)
// 			{
// 				UpdateVertexRecords(vRec[index]);
// 				queue.Update(vRec[index]);
// 			}
// 			UpdateVertexRecords(rec2);
// 			queue.Update(rec2);
// 
// 			foreach (int index in rec2.adjF)
// 			{
// 				int t = index * 3;
// 				int c1 = faceIndex[t];
// 				int c2 = faceIndex[t + 1];
// 				int c3 = faceIndex[t + 2];
// 
// 				if (c1 == c2 || c2 == c3 || c3 == c1)
// 				{
// 					rec2.adjF.Remove(index);
// 					foreach (int index2 in rec2.adjV)
// 						vRec[index2].adjF.Remove(index);
// 					// decrease face count
// 					facesLeft--;
// 				}
// 			}
// 
// 			if (count == 0) Program.PrintText("!");
// 
// 			// decrease vertex count
// 			vertexLeft--;
// 		}
// 
// 		// copy remaining vertices to resulting list
// 		simplifiedVertexRec = new List<VertexRecord>(512);
// 		while (!queue.IsEmpty())
// 		{
// 			VertexRecord rec = (VertexRecord)queue.DeleteMin();
// 			simplifiedVertexRec.Add(rec);
// 		}
// 
// 		// release set objects
// 		foreach (VertexRecord rec in vRec)
// 		{
// 			rec.adjF = null;
// 			if (rec.collapseFrom == null)
// 				rec.adjV = null;
// 		}
// 
// 		AssignColorIndex();
// 
// 		Program.PrintText("Nodes:" + simplifiedVertexRec.Count.ToString());
	}
	
};

