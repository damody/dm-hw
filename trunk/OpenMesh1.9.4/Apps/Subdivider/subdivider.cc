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
//   $Date: 2006-03-22 20:12:06 $
//                                                                            
//=============================================================================


#include <iostream>
#include <sstream>
// ---------------------------------------- OpenMesh Stuff
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Tools/Utils/Timer.hh>
#include <OpenMesh/Tools/Utils/getopt.h>
// ---------------------------------------- Subdivider
#include <OpenMesh/Tools/Subdivider/Uniform/Sqrt3T.hh>
#include <OpenMesh/Tools/Subdivider/Uniform/LoopT.hh>
#include <OpenMesh/Tools/Subdivider/Uniform/CompositeSqrt3T.hh>
#include <OpenMesh/Tools/Subdivider/Uniform/CompositeLoopT.hh>

// ----------------------------------------------------------------------------

using namespace OpenMesh::Subdivider;

typedef OpenMesh::Subdivider::Uniform::CompositeTraits       CTraits;
typedef OpenMesh::TriMesh_ArrayKernelT<CTraits>              CMesh;

typedef OpenMesh::TriMesh_ArrayKernelT<>                     Mesh;
typedef Uniform::Sqrt3T< Mesh >                              Sqrt3;
typedef Uniform::LoopT< Mesh >                               Loop;
typedef Uniform::CompositeSqrt3T< CMesh >                    CompositeSqrt3;
typedef Uniform::CompositeLoopT< CMesh >                     CompositeLoop;

using OpenMesh::Utils::Timer;

// ----------------------------------------------------------------------------

std::map< std::string, double > timings;

// ----------------------------------------------------------------------------

template < typename Subdivider >
bool subdivide( typename Subdivider::mesh_t& _m, size_t _n, 
                Timer::Format _fmt )
{
  bool       rc;
  Timer      t;
  Subdivider subdivide;

  std::cout << "Subdivide " << _n 
            << " times with '" << subdivide.name() << "'\n";

  subdivide.attach(_m);
  t.start();
  rc=subdivide( _n );
  t.stop();
  subdivide.detach();

  if (rc)
  {
    std::cout << "  Done [" << t.as_string(_fmt) << "]\n";
    timings[subdivide.name()] = t.seconds();
  }
  else
    std::cout << "  Failed!\n";
  return rc;
}

// ----------------------------------------------------------------------------

void usage_and_exit(int _xcode);

// ----------------------------------------------------------------------------

template < typename Subdivider >
int mainT( size_t _n, 
           const std::string& _ifname, 
           const std::string& _ofname, 
           const Timer::Format _fmt )
{
  // -------------------- read mesh
  std::cout << "Read mesh from file " << _ifname << std::endl;

  typename Subdivider::mesh_t mesh;

  if ( OpenMesh::IO::read_mesh( mesh, _ifname ) )
    std::cout << "  Ok\n";
  else
  {
    std::cout << "  Failed!\n";
    return 1;
  }

  std::cout << "  #V " << mesh.n_vertices() 
            << ", #F " << mesh.n_faces()
            << ", #E " << mesh.n_edges() << std::endl;

  // -------------------- subdividing
  try
  {
    if (!subdivide< Subdivider >( mesh, _n, _fmt ))
      return 1;
  }
  catch(std::bad_alloc& x)
  {
    std::cerr << "Out of memory: " << x.what() << std::endl;
    return 1;
  }
  catch(std::exception& x)
  {
    std::cerr << x.what() << std::endl;
    return 1;
  }
  catch(...)
  {
    std::cerr << "Unknown exception!\n";
    return 1;
  }

  // -------------------- write mesh

  std::cout << "  #V " << mesh.n_vertices() 
            << ", #F " << mesh.n_faces()
            << ", #E " << mesh.n_edges() << std::endl;

  if ( !_ofname.empty() )
  {
    std::cout << "Write resulting mesh to file " << _ofname << "..";
    if (OpenMesh::IO::write_mesh(mesh, _ofname, OpenMesh::IO::Options::Binary))
    {
      std::cout << "ok\n";
    }
    else
    {
      std::cerr << "Failed! Could not write file!\n";
      return 1;
    }
  }

  return 0;
}

// ----------------------------------------------------------------------------

int main(int argc, char **argv)
{
  int    c;

  bool        compare_all = false;
  size_t      n;
  std::string ifname;
  std::string ofname;

  enum {
    TypeSqrt3,
    TypeLoop,
    TypeCompSqrt3,
    TypeCompLoop
  } st = TypeSqrt3;

  Timer::Format fmt = Timer::Automatic;

  while ( (c=getopt(argc, argv, "csSlLhf:"))!=-1 )
  {
    switch(c)
    {
      case 'c': compare_all=true; break;
      case 's': st = TypeSqrt3; break;
      case 'S': st = TypeCompSqrt3; break;
      case 'l': st = TypeLoop; break;
      case 'L': st = TypeCompLoop; break;
      case 'f': 
      {
        switch(*optarg)
        {          
          case 'm': fmt = Timer::MSeconds; break;
          case 'c': fmt = Timer::HSeconds; break;
          case 's': fmt = Timer::Seconds;  break;
          case 'a':
          default:  fmt = Timer::Automatic; break;
        }
        break;
      }
      case 'h': usage_and_exit(0);
      case '?':
      default:  usage_and_exit(1);
    }
  }
  
  if (argc-optind < 2)
    usage_and_exit(1);

  // # iterations
  {
    std::stringstream str; str << argv[optind]; str >> n;
  }

  // input file
  ifname = argv[++optind];

  // output file, if provided
  if ( ++optind < argc )
    ofname = argv[optind];


  // --------------------
  if ( compare_all )
  {
    int rc;
    rc  = mainT<Sqrt3>         ( n, ifname, "", fmt );
    rc += mainT<Loop>          ( n, ifname, "", fmt );
    rc += mainT<CompositeSqrt3>( n, ifname, "", fmt );
    rc += mainT<CompositeLoop> ( n, ifname, "", fmt );
    
    if (rc)
      return rc;

    std::cout << std::endl;

    std::map< std::string, double >::iterator it;
    
    std::cout << "Timings:\n";
    for(it = timings.begin();it!=timings.end();++it)
      std::cout << it->first << ": " << Timer::as_string(it->second)
                << std::endl;
    std::cout << std::endl;
    std::cout << "Ratio composite/native algorithm:\n";
    std::cout << "sqrt(3): " 
              << timings["Uniform Composite Sqrt3"]/timings["Uniform Sqrt3"]
              << std::endl
              << "loop   : "
              << timings["Uniform Composite Loop"]/timings["Uniform Loop"]
              << std::endl;
    return 0;
  }
  else switch(st)
  {
    case TypeSqrt3: 
      return mainT<Sqrt3>( n, ifname, ofname, fmt );
    case TypeLoop:  
      return mainT<Loop>( n, ifname, ofname, fmt );
    case TypeCompSqrt3: 
      return mainT<CompositeSqrt3>( n, ifname, ofname, fmt );
    case TypeCompLoop:  
      return mainT<CompositeLoop> ( n, ifname, ofname, fmt );
  }
  return 1;
}

// ----------------------------------------------------------------------------

void usage_and_exit(int _xcode)
{
  std::cout << "Usage: subdivide [Subdivider Type] #Iterations Input [Output].\n";
  std::cout << std::endl;
  std::cout << "Subdivider Type\n"
            << std::endl
            << "  -l\tLoop\n"
            << "  -L\tComposite Loop\n"
            << "  -s\tSqrt3\n"
            << "  -S\tComposite Sqrt3\n"
            << std::endl;
  exit(_xcode);
}