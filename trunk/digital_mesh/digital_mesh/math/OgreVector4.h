/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2009 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#ifndef __Vector4_H__
#define __Vector4_H__

#include "OgreVector3.h"

namespace Ogre
{

	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Math
	*  @{
	*/
	/** 4-dimensional homogeneous vector.
    */
    class Vector4d
    {
    public:
        double x, y, z, w;

    public:
	    inline Vector4d():x(0), y(0), z(0), w(0)
        {
        }

        inline Vector4d( const double fX, const double fY, const double fZ, const double fW )
            : x( fX ), y( fY ), z( fZ ), w( fW)
        {
        }

        inline explicit Vector4d( const double afCoordinate[4] )
            : x( afCoordinate[0] ),
              y( afCoordinate[1] ),
              z( afCoordinate[2] ),
              w( afCoordinate[3] )
        {
        }

        inline explicit Vector4d( const int afCoordinate[4] )
        {
            x = (double)afCoordinate[0];
            y = (double)afCoordinate[1];
            z = (double)afCoordinate[2];
            w = (double)afCoordinate[3];
        }

        inline explicit Vector4d( double* const r )
            : x( r[0] ), y( r[1] ), z( r[2] ), w( r[3] )
        {
        }

        inline explicit Vector4d( const double scaler )
            : x( scaler )
            , y( scaler )
            , z( scaler )
            , w( scaler )
        {
        }

        inline explicit Vector4d(const Vector3d& rhs)
            : x(rhs.x), y(rhs.y), z(rhs.z), w(1.0f)
        {
        }

		/** Exchange the contents of this vector with another. 
		*/
		inline void swap(Vector4d& other)
		{
			std::swap(x, other.x);
			std::swap(y, other.y);
			std::swap(z, other.z);
			std::swap(w, other.w);
		}
	
		inline double operator [] ( const size_t i ) const
        {
            assert( i < 4 );

            return *(&x+i);
        }

		inline double& operator [] ( const size_t i )
        {
            assert( i < 4 );

            return *(&x+i);
        }

		/// Pointer accessor for direct copying
		inline double* ptr()
		{
			return &x;
		}
		/// Pointer accessor for direct copying
		inline const double* ptr() const
		{
			return &x;
		}

        /** Assigns the value of the other vector.
            @param
                rkVector The other vector
        */
        inline Vector4d& operator = ( const Vector4d& rkVector )
        {
            x = rkVector.x;
            y = rkVector.y;
            z = rkVector.z;
            w = rkVector.w;

            return *this;
        }

		inline Vector4d& operator = ( const double fScalar)
		{
			x = fScalar;
			y = fScalar;
			z = fScalar;
			w = fScalar;
			return *this;
		}

        inline bool operator == ( const Vector4d& rkVector ) const
        {
            return ( x == rkVector.x &&
                y == rkVector.y &&
                z == rkVector.z &&
                w == rkVector.w );
        }

        inline bool operator != ( const Vector4d& rkVector ) const
        {
            return ( x != rkVector.x ||
                y != rkVector.y ||
                z != rkVector.z ||
                w != rkVector.w );
        }

        inline Vector4d& operator = (const Vector3d& rhs)
        {
            x = rhs.x;
            y = rhs.y;
            z = rhs.z;
            w = 1.0f;
            return *this;
        }

        // arithmetic operations
        inline Vector4d operator + ( const Vector4d& rkVector ) const
        {
            return Vector4d(
                x + rkVector.x,
                y + rkVector.y,
                z + rkVector.z,
                w + rkVector.w);
        }

        inline Vector4d operator - ( const Vector4d& rkVector ) const
        {
            return Vector4d(
                x - rkVector.x,
                y - rkVector.y,
                z - rkVector.z,
                w - rkVector.w);
        }

        inline Vector4d operator * ( const double fScalar ) const
        {
            return Vector4d(
                x * fScalar,
                y * fScalar,
                z * fScalar,
                w * fScalar);
        }

        inline Vector4d operator * ( const Vector4d& rhs) const
        {
            return Vector4d(
                rhs.x * x,
                rhs.y * y,
                rhs.z * z,
                rhs.w * w);
        }

        inline Vector4d operator / ( const double fScalar ) const
        {
            assert( fScalar != 0.0 );

            double fInv = 1.0f / fScalar;

            return Vector4d(
                x * fInv,
                y * fInv,
                z * fInv,
                w * fInv);
        }

        inline Vector4d operator / ( const Vector4d& rhs) const
        {
            return Vector4d(
                x / rhs.x,
                y / rhs.y,
                z / rhs.z,
                w / rhs.w);
        }

        inline const Vector4d& operator + () const
        {
            return *this;
        }

        inline Vector4d operator - () const
        {
            return Vector4d(-x, -y, -z, -w);
        }

        inline friend Vector4d operator * ( const double fScalar, const Vector4d& rkVector )
        {
            return Vector4d(
                fScalar * rkVector.x,
                fScalar * rkVector.y,
                fScalar * rkVector.z,
                fScalar * rkVector.w);
        }

        inline friend Vector4d operator / ( const double fScalar, const Vector4d& rkVector )
        {
            return Vector4d(
                fScalar / rkVector.x,
                fScalar / rkVector.y,
                fScalar / rkVector.z,
                fScalar / rkVector.w);
        }

        inline friend Vector4d operator + (const Vector4d& lhs, const double rhs)
        {
            return Vector4d(
                lhs.x + rhs,
                lhs.y + rhs,
                lhs.z + rhs,
                lhs.w + rhs);
        }

        inline friend Vector4d operator + (const double lhs, const Vector4d& rhs)
        {
            return Vector4d(
                lhs + rhs.x,
                lhs + rhs.y,
                lhs + rhs.z,
                lhs + rhs.w);
        }

        inline friend Vector4d operator - (const Vector4d& lhs, double rhs)
        {
            return Vector4d(
                lhs.x - rhs,
                lhs.y - rhs,
                lhs.z - rhs,
                lhs.w - rhs);
        }

        inline friend Vector4d operator - (const double lhs, const Vector4d& rhs)
        {
            return Vector4d(
                lhs - rhs.x,
                lhs - rhs.y,
                lhs - rhs.z,
                lhs - rhs.w);
        }

        // arithmetic updates
        inline Vector4d& operator += ( const Vector4d& rkVector )
        {
            x += rkVector.x;
            y += rkVector.y;
            z += rkVector.z;
            w += rkVector.w;

            return *this;
        }

        inline Vector4d& operator -= ( const Vector4d& rkVector )
        {
            x -= rkVector.x;
            y -= rkVector.y;
            z -= rkVector.z;
            w -= rkVector.w;

            return *this;
        }

        inline Vector4d& operator *= ( const double fScalar )
        {
            x *= fScalar;
            y *= fScalar;
            z *= fScalar;
            w *= fScalar;
            return *this;
        }

        inline Vector4d& operator += ( const double fScalar )
        {
            x += fScalar;
            y += fScalar;
            z += fScalar;
            w += fScalar;
            return *this;
        }

        inline Vector4d& operator -= ( const double fScalar )
        {
            x -= fScalar;
            y -= fScalar;
            z -= fScalar;
            w -= fScalar;
            return *this;
        }

        inline Vector4d& operator *= ( const Vector4d& rkVector )
        {
            x *= rkVector.x;
            y *= rkVector.y;
            z *= rkVector.z;
            w *= rkVector.w;

            return *this;
        }

        inline Vector4d& operator /= ( const double fScalar )
        {
            assert( fScalar != 0.0 );

            double fInv = 1.0f / fScalar;

            x *= fInv;
            y *= fInv;
            z *= fInv;
            w *= fInv;

            return *this;
        }

        inline Vector4d& operator /= ( const Vector4d& rkVector )
        {
            x /= rkVector.x;
            y /= rkVector.y;
            z /= rkVector.z;
            w /= rkVector.w;

            return *this;
        }

        /** Calculates the dot (scalar) product of this vector with another.
            @param
                vec Vector with which to calculate the dot product (together
                with this one).
            @returns
                A double representing the dot product value.
        */
        inline double dotProduct(const Vector4d& vec) const
        {
            return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
        }
		/// Check whether this vector contains valid values
		inline bool isNaN() const
		{
			return Math::isNaN(x) || Math::isNaN(y) || Math::isNaN(z) || Math::isNaN(w);
		}
        /** Function for writing to a stream.
        */
        inline friend std::ostream& operator <<
            ( std::ostream& o, const Vector4d& v )
        {
            o << "Vector4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
            return o;
        }
        // special
        static const Vector4d ZERO;
    };
	/** @} */
	/** @} */

}
#endif

