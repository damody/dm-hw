#pragma once
#include "Tri_Mesh.h"
#include "ANN/ANN.h"
#include <memory>
#include <vector>

typedef std::vector<BasicMesh::VertexHandle> VertexHandles;
typedef std::vector<ANNidx> ANNidxs;
typedef std::vector<ANNdist> ANNdists;

typedef std::tr1::shared_ptr<ANNkd_tree> ANNkd_tree_Sptr;
class FastTri_Mesh : public Tri_Mesh
{
public:
	ANNpointArray	mPointAry;
	std::tr1::shared_ptr<ANNkd_tree> mANNkd_tree;
	VertexHandles		mVertexHandles;
	ANNidxs			mANNidxs;
	ANNdists		mANNdistss;
	int mNumOfPoints;
	FastTri_Mesh(void);
	~FastTri_Mesh(void);
	bool ReadFile(std::string _fileName)
	{
		if (Tri_Mesh::ReadFile(_fileName))
		{
			int maxPts = 0;
			for (VertexIter v_it=vertices_begin(); v_it!=vertices_end(); ++v_it, ++maxPts);
			mNumOfPoints = maxPts;
			mPointAry = annAllocPts(maxPts, 3);
			int i = 0;
			for (VertexIter v_it=vertices_begin(); v_it!=vertices_end(); ++v_it, ++i)
			{
				Point p = point(v_it);
				mVertexHandles.push_back(v_it.handle());
				mPointAry[i][0] = p[0];
				mPointAry[i][1] = p[1];
				mPointAry[i][2] = p[2];
			}
			mANNkd_tree = ANNkd_tree_Sptr(new ANNkd_tree(		// build search structure
				mPointAry,			// the data points
				maxPts,				// number of points
				3));				// dimension of space
			return true;
		}
		else
			return false;
	}
};
