#pragma once
#include "algo/sgmath.h"

Ogre::Vector3d GetRotation( const Ogre::Vector3d& src, double angle, const Ogre::Vector3d& middle_up )
{
	Ogre::Quaternion q;
	q.FromAngleAxis( Ogre::Degree(angle), middle_up );
	return q * src;
}

Ogre::Vector2d GetRotation( const Ogre::Vector2d& src, double angle, const Ogre::Vector2d& middle )
{
	Ogre::Quaternion q;
	Ogre::Vector3d tmpsrc(src.x, src.y, 0);
	Ogre::Vector3d up(middle.x, middle.y, -1);
	q.FromAngleAxis( Ogre::Degree(angle), up );
	tmpsrc = q * tmpsrc;
	return Ogre::Vector2d(tmpsrc.x, tmpsrc.y);
}

Ogre::Degree GetAngle( double x, double y )
{
	return Ogre::Degree(Ogre::Radian(atan2f(x, y)));
}
