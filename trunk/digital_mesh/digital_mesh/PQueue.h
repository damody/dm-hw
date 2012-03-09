#pragma once
#include "shared_ptr.h"

struct PQueueCell
{
	int PQIndex;
	virtual int CompareTo(PQueueCell*)=0;
	virtual ~PQueueCell(){}
};
SHARE_PTR(PQueueCell);

class PQueue //:  ICollection
{
public:
	PQueueCell_rawptrs mDatas;
	bool Empty()
	{return mDatas.empty();}
	void Clear()
	{mDatas.clear();}
	void Insert(PQueueCell* obj);
	//PQueueCell* Top() {return mDatas.front();}
	void Pop();
	PQueueCell* GetMin()
	{return mDatas.at(0);}
	void Update(const PQueueCell& obj);
	void PercolateUp(int hole);
	void PercolateDown(int hole);
	PQueueCell* DeleteMin()
	{
		PQueueCell* obj = mDatas[0];
		mDatas[0] = mDatas.back();
		mDatas.pop_back();
		if (mDatas.size() > 0)
		{
			mDatas[0]->PQIndex = 0;
			PercolateDown(0);
		}
		return obj;
	}
};
