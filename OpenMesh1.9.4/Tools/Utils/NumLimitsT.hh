//=============================================================================
//                                                                            
//                               OpenMesh                                     
//        Copyright (C) 2003 by Computer Graphics Group, RWTH Aachen          
//                           www.openmesh.org                                 
//                                                                            
//-----------------------------------------------------------------------------
//                                                                            
//                                License                                     
//                                                                            
//   This library is free software; you can redistribute it and/or modify it 
//   under the terms of the GNU Library General Public License as published  
//   by the Free Software Foundation, version 2.                             
//                                                                             
//   This library is distributed in the hope that it will be useful, but       
//   WITHOUT ANY WARRANTY; without even the implied warranty of                
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         
//   Library General Public License for more details.                          
//                                                                            
//   You should have received a copy of the GNU Library General Public         
//   License along with this library; if not, write to the Free Software       
//   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 
//                                                                            
//-----------------------------------------------------------------------------
//                                                                            
//   $Revision: 1.1.1.1 $
//   $Date: 2006-03-22 20:12:01 $
//                                                                            
//=============================================================================

/** \file NumLimits.hh
    Temporary solution until std::numeric_limits is standard.
 */

//=============================================================================
//
//  CLASS NumLimitsT
//
//=============================================================================

#ifndef OPENMESH_UTILS_NUMLIMITS_HH
#define OPENMESH_UTILS_NUMLIMITS_HH


//== INCLUDES =================================================================

#include "Config.hh"
#include <limits.h>
#include <float.h>


//== NAMESPEACES ==============================================================

namespace OpenMesh { // BEGIN_NS_OPENMESH
namespace Utils { // BEGIN_NS_UTILS


//== CLASS DEFINITION =========================================================


/** \class NumLimitsT NumLimitsT.hh <OpenMesh/Utils/NumLimitsT.hh

    This class provides the maximum and minimum values a certain
    scalar type (\cint, \c float, or \double) can store. You can
    use it like this:
    \code
    #include <OpenMesh/Utils/NumLimitsT.hh>

    int   float_min   = OpenMesh::NumLimitsT<float>::min();
    float double_max  = OpenMesh::NumLimitsT<double>::max();
    \endcode
    
    \note This functionality should be provided by
    std::numeric_limits.  This template does not exist on gcc <=
    2.95.3. The class template NumLimitsT is just a workaround.
**/
template <typename Scalar>
class NumLimitsT
{
public:
  /// Return the smallest \em absolte value a scalar type can store.
  static inline Scalar min() { return 0; }
  /// Return the maximum \em absolte value a scalar type can store.
  static inline Scalar max() { return 0; }

  static inline bool   is_float()   { return false; }
  static inline bool   is_integer() { return !NumLimitsT<Scalar>::is_float(); }
  static inline bool   is_signed()  { return true; }
};

  // is_float

template<> 
inline bool NumLimitsT<float>::is_float() { return true; }

template<> 
inline bool NumLimitsT<double>::is_float() { return true; }

template<> 
inline bool NumLimitsT<long double>::is_float() { return true; }

  // is_signed

template<> 
inline bool NumLimitsT<unsigned char>::is_signed() { return false; }

template<> 
inline bool NumLimitsT<unsigned short>::is_signed() { return false; }

template<> 
inline bool NumLimitsT<unsigned int>::is_signed() { return false; }

template<> 
inline bool NumLimitsT<unsigned long>::is_signed() { return false; }

template<> 
inline bool NumLimitsT<unsigned long long>::is_signed() { return false; }

  // min/max
template<> inline int  NumLimitsT<int>::min() { return INT_MIN; }
template<> inline int  NumLimitsT<int>::max() { return INT_MAX; }

template<> inline float NumLimitsT<float>::min() { return FLT_MIN; }
template<> inline float NumLimitsT<float>::max() { return FLT_MAX; }

template<> inline double NumLimitsT<double>::min() { return DBL_MIN; }
template<> inline double NumLimitsT<double>::max() { return DBL_MAX; }


//=============================================================================
} // END_NS_UTILS
} // END_NS_OPENMESH
//=============================================================================
#endif // OPENMESH_NUMLIMITS_HH defined
//=============================================================================

