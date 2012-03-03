#include "AdditionalFunction.h"

Vec3 PointToVec3( const BasicMesh::Point& p )
{
	Vec3 v;
	v[0] = p[0];
	v[1] = p[1];
	v[2] = p[2];
	return v;
}

