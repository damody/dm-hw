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
//   $Date: 2006-03-22 20:12:07 $
//                                                                            
//=============================================================================

#ifdef _MSC_VER
#  pragma warning(disable: 4267 4311)
#endif

#include <iostream>
#include <fstream>

#include <OpenMesh/Apps/ProgViewer/ProgViewerWidget.hh>
#include <qstring.h>
#include <qapplication.h>
#include <qgl.h>



int main(int argc, char **argv)
{
  // OpenGL check
  QApplication::setColorSpec( QApplication::CustomColor );
  QApplication app(argc,argv);

  if ( !QGLFormat::hasOpenGL() ) {
    std::cerr << "This system has no OpenGL support.\n";
    return -1;
  }

    
  // create widget
  ProgViewerWidget w(0, "Viewer");
  app.setMainWidget(&w);
  w.resize(400, 400);
  w.show();
  
  // load scene
  if (argc > 1)  w.open_prog_mesh(argv[1]);


  // print usage info
  std::cout << "\n\n"
	    << "Press  Minus : Coarsen mesh\n"
	    << "       Plus  : Refine mesh\n"
	    << "       Home  : Coarsen down to base mesh\n"
	    << "       End   : Refine up to finest mesh\n"
	    << "\n";

	    
  return app.exec();
}
