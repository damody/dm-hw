#pragma once
#include "tri_mesh.h"
#include "TAUCS_CCS_Matrix.h"
#include "SparseMatrix.h"

class Matrix_Mesh :
	public Tri_Mesh
{
public:
	Matrix_Mesh(void);
	virtual ~Matrix_Mesh(void);
	virtual bool ReadFile(std::string _fileName);//Åª¨úmesh¸ê®Æ;
	TAUCS_CCS_Matrix_Double BuildAdjacentMatrixVV();
	TAUCS_CCS_Matrix_Double BuildAdjacentMatrixFV();
	TAUCS_CCS_Matrix_Double BuildAdjacentMatrixFF();
	SparseMatrix BuildAdjacentSMatrixVV();
	SparseMatrix BuildAdjacentSMatrixFV();
	SparseMatrix BuildAdjacentSMatrixFF();
	double GetVolume();
	double m_bound[6];
	// xmin xmax ymin ymax zmin zmax
	double* GetBound();
	const double_vector& Vertexs()
	{return mVertexs;}
	void GetVertexs(double_vector* vertexs, int_vector* indexs = NULL) const;
	void GetFaceVertexs(double_vector* vertexs, int_vector *indexs = NULL);
	Vec3s GetVec3s() const;
	bool IsContainVertex(FaceHandle fh, int v_idx);
	typedef std::vector<char> chars;
	typedef std::vector<bool> bools;
	bools	mIsBoundary;
	chars	mFlags;
public:
	int_vector2d mAdjVV, mAdjVF, mAdjFF;
	SparseMatrix mSMVV, mSMVF, mSMFF;
private:
	double_vector mVertexs;
	friend class Skeletonizer;
};

