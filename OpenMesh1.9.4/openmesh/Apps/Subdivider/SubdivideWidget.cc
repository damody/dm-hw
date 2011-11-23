//=============================================================================
//
//  CLASS SubdivideWidget - IMPLEMENTATION
//
//=============================================================================

#ifndef SUBDIVIDEWIDGET_CC
#define SUBDIVIDEWIDGET_CC

//== INCLUDES =================================================================


// Qt
#include <qapplication.h>
#include <qfiledialog.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qvbox.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qstring.h>
#include <qmessagebox.h>

// OpenMesh
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyConnectivity.hh>
#include <OpenMesh/Tools/Subdivider/Uniform/CompositeLoopT.hh>
#include <OpenMesh/Tools/Subdivider/Uniform/CompositeSqrt3T.hh>
#include <OpenMesh/Tools/Subdivider/Uniform/LoopT.hh>
#include <OpenMesh/Tools/Subdivider/Uniform/Sqrt3T.hh>

// My stuff
#include <OpenMesh/Apps/Subdivider/SubdivideWidget.hh>

//

using namespace OpenMesh::Subdivider;

//== IMPLEMENTATION ==========================================================


SubdivideWidget::
SubdivideWidget(QWidget* _parent, const char* _name)
  : QMainWindow(_parent, _name),
    timer_(NULL), animate_step_(0), max_animate_steps_(4), msecs_(0)
{
  QVBox* vbox = new QVBox( this );

  cur_topo_type = SOP_Undefined;
  // sel_topo_type will be set when adding the radio button.;

  // examiner widget
  viewer_widget_ = new MeshViewerWidget  (vbox, "Viewer Widget");

  setCentralWidget(vbox);

  QHBox* hbox = new QHBox(vbox);
  hbox->setFixedSize(400, 30);

  // insert subdivision pushbutton
  QPushButton* subdiv_button = new QPushButton( "Subdivide", hbox );
  subdiv_button->setMinimumWidth(50);
  QObject::connect( subdiv_button, SIGNAL( clicked() ),
                    this, SLOT( subdiv_slot() ) );


  // insert load pushbutton
  QPushButton* load_button = new QPushButton( "Load Mesh", hbox );
  load_button->setMinimumWidth(50);
  QObject::connect( load_button, SIGNAL( clicked() ),
                    this, SLOT( load_slot() ) );


  // insert save pushbutton
  QPushButton* save_button = new QPushButton( "Save Mesh", hbox );
  save_button->setMinimumWidth(50);
  QObject::connect( save_button, SIGNAL( clicked() ),
                    this, SLOT( save_slot() ) );


  // insert reset pushbutton
  QPushButton* reset_button = new QPushButton( "Reset", hbox );
  reset_button->setMinimumWidth(50);
  QObject::connect( reset_button, SIGNAL( clicked() ),
                    this, SLOT( reset_slot() ) );


  // Create an exclusive button group: Topology Operators
  QButtonGroup *bgrp1 = new QButtonGroup( 1, QGroupBox::Vertical,
                                          "Subdivision Operators:", vbox);
  bgrp1->setExclusive( TRUE );
  bgrp1->setFixedSize(400, 50);

  // insert 2 radiobuttons
  new QRadioButton( "Comp. Loop", bgrp1 );
  new QRadioButton( "Comp. SQRT(3)", bgrp1 );

  (new QRadioButton( "Loop", bgrp1 ))->setChecked( TRUE );
  sel_topo_type = SOP_UniformLoop;

  new QRadioButton( "Sqrt(3)", bgrp1 );

  QObject::connect( bgrp1, SIGNAL( pressed(int) ),
                    this, SLOT( slot_select_sop(int) ) );



  status_bar = new QStatusBar(vbox);
  status_bar->setFixedHeight(20);
  status_bar->message("0 Faces, 0 Edges, 0 Vertices");

  // animation
  timer_ = new QTimer(this);
  connect( timer_, SIGNAL( timeout() ), this, SLOT( animate_slot() ) );

  // --------------------

  subdivider_[SOP_UniformCompositeLoop]  = new Uniform::CompositeLoopT<Mesh>;
  subdivider_[SOP_UniformCompositeSqrt3] = new Uniform::CompositeSqrt3T<Mesh>;
  subdivider_[SOP_UniformLoop]           = new Uniform::LoopT<Mesh>;
  subdivider_[SOP_UniformSqrt3]          = new Uniform::Sqrt3T<Mesh>;

}


//-----------------------------------------------------------------------------

void SubdivideWidget::slot_select_sop(int i)
{
  switch(i)
  {
    case SOP_UniformCompositeLoop:
    case SOP_UniformCompositeSqrt3:
    case SOP_UniformLoop:
    case SOP_UniformSqrt3:          sel_topo_type = (SOPType)i; break;
    default:                        sel_topo_type = SOP_Undefined;
  }
  std::cout << "Selected SOP: " << i << std::endl;
}


//-----------------------------------------------------------------------------

void SubdivideWidget::keyPressEvent( QKeyEvent *k )
{
   bool timerStopped = false;
   if ( timer_->isActive())
   {
      timer_->stop();
      timerStopped = true;
   }

   switch ( tolower(k->ascii()) )
   {
     case 'r':                               // reset
       reset_slot();
       break;
     case 's':                               // save
       save_slot();
       break;
     case 'l':                               // load
       load_slot();
       break;

     case 'a':

       if ( timerStopped )
         break;

       if (timer_->isActive())
       {
         timer_->stop();
       }
       else
       {
         reset_slot();
         timer_->start(0, true);
       }
       break;

     case ' ':                               // subdivide
       subdiv_slot();
   }
}



//-----------------------------------------------------------------------------


void SubdivideWidget::update()
{
  unsigned int n_faces = viewer_widget_->mesh().n_faces();
  unsigned int n_edges = viewer_widget_->mesh().n_edges();
  unsigned int n_vertices = viewer_widget_->mesh().n_vertices();
  QString message(""), temp;
  message.append(temp.setNum(n_faces));
  message.append(" Faces, ");
  message.append(temp.setNum(n_edges));
  message.append(" Edges, ");
  message.append(temp.setNum(n_vertices));
  message.append(" Vertices.  ");
  if (msecs_)
  {
    message.append(temp.setNum(msecs_/1000.0));
    message.append("s");
  }
  status_bar->message(message);
}


//-----------------------------------------------------------------------------


void SubdivideWidget::reset_slot()
{
  if (cur_topo_type != SOP_Undefined)
    subdivider_[cur_topo_type]->detach();

  viewer_widget_->mesh() = viewer_widget_->orig_mesh();
  viewer_widget_->mesh().update_face_normals();
  viewer_widget_->mesh().update_vertex_normals();
  viewer_widget_->updateGL();
  update();
  cur_topo_type = SOP_Undefined;
}



//-----------------------------------------------------------------------------


void SubdivideWidget::subdiv_slot()
{
  assert( sel_topo_type != SOP_Undefined );

  //QTime t;
  using namespace OpenMesh::Subdivider::Uniform;

  status_bar->message( "processing subdivision step...");

  if (cur_topo_type != sel_topo_type)
  {
    if (cur_topo_type!=SOP_Undefined)
      subdivider_[cur_topo_type]->detach();
    subdivider_[cur_topo_type=sel_topo_type]->attach(viewer_widget_->mesh());
  }

  std::clog << "subdiving...\n";
  (*subdivider_[sel_topo_type])(1);
  std::clog << "subdiving...done\n";

  // Update viewer
  viewer_widget_->mesh().update_normals();
  viewer_widget_->updateGL();

  // Update status bar information
  update();
}


//-----------------------------------------------------------------------------

bool
SubdivideWidget::open_mesh(const char* _filename)
{
  OpenMesh::IO::Options opt;

  if (viewer_widget_->open_mesh(_filename, opt))
  {
    update();
    return true;
  }

  return false;
}


//-----------------------------------------------------------------------------

void
SubdivideWidget::save_slot()
{
  using OpenMesh::IO::IOManager;

  QString write_filter(IOManager().qt_write_filters().c_str());
  QString filename =
    QFileDialog::getSaveFileName(QString::null, write_filter, this);

  if (!filename.isEmpty())
    if (OpenMesh::IO::write_mesh(viewer_widget_->mesh(),
         filename.ascii(),
         OpenMesh::IO::Options::Binary) )
      std::cerr << "ok\n";
    else
      std::cerr << "FAILED\n";
}


//-----------------------------------------------------------------------------

void
SubdivideWidget::load_slot()
{
  using OpenMesh::IO::IOManager;

  QString read_filter(IOManager().qt_read_filters().c_str());
  QString filename =
    QFileDialog::getOpenFileName(QString::null, read_filter, this);

  if (!filename.isNull())
  {

    if (cur_topo_type != SOP_Undefined)
      subdivider_[cur_topo_type]->detach();

    OpenMesh::IO::Options opt;

    if ( !viewer_widget_->open_mesh(filename, opt) )
    {
      QString msg = "Cannot read mesh from file ";
      QMessageBox::critical( NULL, filename, msg + filename, 0 );
    }

    update();
    cur_topo_type = SOP_Undefined;
  }
}


//-----------------------------------------------------------------------------

void
SubdivideWidget::animate_slot()
{
  if (++animate_step_ < max_animate_steps_)
  {
    subdiv_slot();
  }
  else
  {
    reset_slot();
    animate_step_ = 0;
  }
  timer_->start( 500 , true);
}

//=============================================================================
#endif //SUBDIVIDEWIDGET_CC deifined
//=============================================================================
