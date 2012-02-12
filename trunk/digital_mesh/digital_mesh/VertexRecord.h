#pragma once
#include <float.h>
#include "imath.h"
#include "Matrix_Mesh.h"


class VertexRecord
{
public:
	enum EnumJointType
	{
		NONE, ATTRACT_POINT, SADDLE_POINT, REGULAR_POINT, END_POINT, ATTRACT_INVALID, REGULAR_INVALID
	};

	Vec3	mPos;
	double	mRadius;
	int_vector	mAdjV;
	int_vector	mAdjF;
	int_vector	mCollapseFrom;
	int	mVecIndex;
	int	mMinIndex;
	int	mPQIndex;
	Matrix4	mMatrix;
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

	VertexRecord( Matrix_Mesh& mesh, int i ) 
		:mRadius(0), mVecIndex(-1), mMinIndex(-1), mPQIndex(-1),
		mCenter(false), mError(0), mColorIndex(-1),
		mMinError(DBL_MAX),

		mFacesArea(0),
		mMCNFlowError(DBL_MIN),	mMCNflowErrorNormalize(DBL_MIN),
		mHierarchyFlag(false), mFilterd(false),
		mBoneFlag(false), mJointFlag(false)
	{
		mVecIndex = i;
		mPos = Vec3(&(mesh.Vertexs()[i*3]));
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
	bool operator<(const VertexRecord& vr)
	{
		return mMinError < vr.mMinError;
	}
/*
#region added by hkchu        
	public EnumJointType joint_type;
	public int[] face_array;
	public double faces_area;            
	public double mcnflow_error = double.MinValue;
	public double mcnflow_error_normalize = double.MinValue;  
	public bool hierarchy_flag;            
	public bool filterd = false;
	public bool bone_flag = false;
	public bool joint_flag = false;

	public VertexRecord(VertexRecord _rec)
	{
		this.pos = new Vector3d(_rec.pos.x, _rec.pos.y, _rec.pos.z);
		this.radius = _rec.radius;
		this.vIndex = _rec.vIndex;
		this.minIndex = _rec.minIndex;
		this.minError = _rec.minError;
		this.colorIndex = _rec.colorIndex;
		this.center = _rec.center;
		this.err = _rec.err;

		if (_rec.adjV != null)
		{
			foreach (int index in _rec.adjV)
				this.adjV.Add(index);
		}

		if (_rec.collapseFrom != null)
		{
			foreach (int index in _rec.collapseFrom)
				this.collapseFrom.Add(index);
		}
	}
#endregion
*/
};
