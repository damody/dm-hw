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
	double_vector GetVectors();
	Vec3s GetVec3s();
	bool IsContainVertex(FaceHandle fh, int v_idx);
	typedef std::vector<char> chars;
	typedef std::vector<bool> bools;
	bools	m_isBoundary;
	chars	m_Flags;
private:
	int_vector2d m_adjVV, m_adjVF, m_adjFF;
	SparseMatrix m_SMVV, m_SMVF, m_SMFF;
	friend class Skeletonizer;
};

