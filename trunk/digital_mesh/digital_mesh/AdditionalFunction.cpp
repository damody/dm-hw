#include "AdditionalFunction.h"

Vec3 PointToVec3( const BasicMesh::Point& p )
{
	Vec3 v;
	v[0] = p[0];
	v[1] = p[1];
	v[2] = p[2];
	return v;
}

osg::Vec3f OgreVec3ToOsgVec3(const Ogre::Vector3d& p)
{
	osg::Vec3f v;
	v[0] = p[0];
	v[1] = p[1];
	v[2] = p[2];
	return v;
}

Ogre::Vector3d OsgVec3ToOgreVec3(const osg::Vec3f& p)
{
	Ogre::Vector3d v;
	v[0] = p[0];
	v[1] = p[1];
	v[2] = p[2];
	return v;
}