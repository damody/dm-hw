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
//=============================================================================
#ifdef _MSC_VER
#  pragma warning(disable: 4267 4311)
#endif

#include <iostream>
#include <fstream>

#include <qapplication.h>
#include <qmessagebox.h>
#include "SubdivideWidget.hh"



int main(int argc, char **argv)
{
  // OpenGL check
  QApplication::setColorSpec( QApplication::CustomColor );
  QApplication app(argc,argv);

  if ( !QGLFormat::hasOpenGL() ) {
    QString msg = "System has no OpenGL support!";
    QMessageBox::critical( NULL, "OpenGL", msg + argv[1], 0 );
    return -1;
  }

    
  // create widget
  SubdivideWidget* w = new SubdivideWidget(0, "Subdivider");  

  w->setCaption( "Subdivider" );
  w->resize(400, 400);
  app.setMainWidget(w);
  w->show();

  // load scene
  if (argc > 1)  
  {
     if ( ! w->open_mesh(argv[1]) )
     {
        QString msg = "Cannot read mesh from file ";
        QMessageBox::critical( NULL, argv[1], msg + argv[1], 0 );
        return -1;
     }
  }


  return app.exec();
}
