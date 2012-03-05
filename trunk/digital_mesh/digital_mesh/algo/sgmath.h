#pragma once
#include "math\OgreVector2.h"
#include "math\OgreVector3.h"
#include <cmath>

Ogre::Vector3d GetRotation( const Ogre::Vector3d& src, double angle, const Ogre::Vector3d& middle_up = Ogre::Vector3d::NEGATIVE_UNIT_Z );
Ogre::Vector2d GetRotation( const Ogre::Vector2d& src, double angle, const Ogre::Vector2d& middle = Ogre::Vector2d::ZERO);
Ogre::Degree GetAngle(double x, double y);
