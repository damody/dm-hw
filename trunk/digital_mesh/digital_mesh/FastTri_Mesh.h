#pragma once
#include "Tri_Mesh.h"
#include "ANN/ANN.h"

class FastTri_Mesh : public Tri_Mesh
{
public:
	ANNpointArray	mPointAry;
	FastTri_Mesh(void);
	~FastTri_Mesh(void);
	bool ReadFile(std::string _fileName)
	{
		if (Tri_Mesh::ReadFile(_fileName))
		{
			
			return true;
		}
		else
			return false;
	}
};
