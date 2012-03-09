#include "VertexRecord.h"

VertexRecord::VertexRecord( Matrix_Mesh& mesh, int i ) 
:mRadius(0), mVecIndex(-1), mMinIndex(-1), mPQIndex(-1), mMesh(&mesh),
mCenter(false), mError(0), mColorIndex(-1), mMinError(DBL_MAX),
mFacesArea(0), mMCNFlowError(DBL_MIN), mMCNflowErrorNormalize(DBL_MIN),
mHierarchyFlag(false), mFilterd(false),mBoneFlag(false), mJointFlag(false)
{
	mVecIndex = i;
	int_vector& VV = mesh.mAdjVV[i];
	for (int_vector::iterator it = VV.begin(); it != VV.end(); ++it)
	{
		mAdjV.push_back(*it);
	}
	int_vector& VF = mesh.mAdjVF[i];
	for (int_vector::iterator it = VF.begin(); it != VF.end(); ++it)
	{
		mAdjF.push_back(*it);
	}
}
