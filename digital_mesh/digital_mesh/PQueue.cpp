#include "PQueue.h"
#include "log_define.h"
#include "VertexRecord.h"

void PQueue::Insert( PQueueCell* obj )
{
	int hole = mDatas.size();
	mDatas.push_back(obj);
	while (hole>0 && obj->CompareTo(mDatas[(hole-1)/2])<0)
	{
		mDatas[hole] = mDatas[(hole-1)/2];
		mDatas[hole]->PQIndex = hole;
		hole = (hole-1) / 2;
	}
	mDatas[hole] = obj;
	obj->PQIndex = hole;
}

void PQueue::Pop()
{
	mDatas.at(0) = mDatas.back();
	mDatas.erase(mDatas.end()-1);
	if (!mDatas.empty())
	{
		mDatas.at(0)->PQIndex = 0;
		PercolateDown(0);
	}
}

void PQueue::Update( const PQueueCell& obj )
{
	PercolateUp(obj.PQIndex);
	PercolateDown(obj.PQIndex);
}

void PQueue::PercolateUp( int hole )
{
	PQueueCell* obj = mDatas[hole];
	while (hole > 0 && obj->CompareTo(mDatas[(hole - 1) / 2]) < 0)
	{
		int parent = (hole - 1) / 2;
		PQueueCell* parentObj = mDatas[parent];
		mDatas[hole] = mDatas[parent];
		parentObj->PQIndex = hole;
		hole = parent;
	}
	mDatas[hole] = obj;
	obj->PQIndex = hole;
}

void PQueue::PercolateDown( int hole )
{
	PQueueCell* obj = mDatas[hole];
	while ((hole*2+1) < (int)mDatas.size())
	{
		int child = hole*2 + 1;
		if (child != (int)mDatas.size()-1)
		{
			if (mDatas[child+1]->CompareTo(mDatas[child])<0)
				child++;
		}
		PQueueCell* childObj = mDatas[child];
		if (childObj->CompareTo(obj) < 0)
		{
			mDatas[hole] = childObj;
			childObj->PQIndex = hole;
			hole = child;
		}
		else break;
	}
	mDatas[hole] = obj;
	obj->PQIndex = hole;
}
