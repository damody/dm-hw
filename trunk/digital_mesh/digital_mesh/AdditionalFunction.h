#pragma once
#include "imath.h"
#include "Tri_Mesh.h"

Vec3 PointToVec3(const BasicMesh::Point& p);
osg::Vec3f OgreVec3ToOsgVec3(const Ogre::Vector3d& p);
Ogre::Vector3d OsgVec3ToOgreVec3(const osg::Vec3f& p);