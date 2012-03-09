#pragma once
#include <float.h>
#include <queue>
#include "Matrix_Mesh.h"
#include "PQueue.h"
#include "imath.h"
#include "shared_ptr.h"

class VertexRecord : public PQueueCell
{
public:
	enum EnumJointType
	{
		NONE, ATTRACT_POINT, SADDLE_POINT, REGULAR_POINT, END_POINT, ATTRACT_INVALID, REGULAR_INVALID
	};

	double	mRadius;
	int_vector	mAdjV;
	int_vector	mAdjF;
	int_vector	mCollapseFrom;
	int	mVecIndex;
	int	mMinIndex;
	int	mPQIndex;
	Mat4	mMatrix;
	double	mMinError;
	int	mColorIndex;
	bool	mCenter;
	double	mError;
	EnumJointType	mJointType;
	int_vector	mFaceArray;
	double	mFacesArea;            
	double	mMCNFlowError;
	double	mMCNflowErrorNormalize; 
	bool	mHierarchyFlag;            
	bool	mFilterd;
	bool	mBoneFlag;
	bool	mJointFlag;
	Matrix_Mesh*	mMesh;

	VertexRecord( Matrix_Mesh& mesh, int i );
	~VertexRecord(){}
	bool operator<(const VertexRecord& vr)
	{
		return mMinError < vr.mMinError;
	}
	Vec3 Pos() const
	{
		Ogre::Vector3d res(
			&(mMesh->point(mMesh->vertex_handle(mVecIndex))[0])
			);
		return res;
	}
	void SetPos(Vec3& v)
	{
		BasicMesh::Point p = mMesh->point(mMesh->vertex_handle(mVecIndex));
		p[0] = v[0];
		p[1] = v[1];
		p[2] = v[2];
	}
	void AddPos(Vec3& v)
	{
		BasicMesh::Point p = mMesh->point(mMesh->vertex_handle(mVecIndex));
		p[0] += v[0];
		p[1] += v[1];
		p[2] += v[2];
	}
	virtual int CompareTo(PQueueCell* obj)
	{
		VertexRecord* rec = (VertexRecord*)obj;
		if (mMinError < rec->mMinError) return -1;
		if (mMinError > rec->mMinError) return 1;
		return 0;
	}
};
SHARE_PTR(VertexRecord)
typedef std::queue<VertexRecord*> VertexRecord_queue;
