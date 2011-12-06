#pragma once


#include "DotNetUtilities.h"
#include "Mesh/GUA_OM.h"
#include "Mesh/DP.h"
#include "Mesh/GLCamera.h"
#include "Mesh/XForm.h"

Tri_Mesh *mesh;

DP_COM *dp_com ;

xform xf;
GLCamera camera;
float fov = 0.7f;

bool peeling_state ;


static const Mouse::button physical_to_logical_map[] = {
	Mouse::NONE, Mouse::ROTATE, Mouse::MOVEXY, Mouse::MOVEZ,
	Mouse::MOVEZ, Mouse::MOVEXY, Mouse::MOVEXY, Mouse::MOVEXY,
};

Mouse::button Mouse_State = Mouse::ROTATE;

#pragma comment(linker, "/subsystem:console /entry:WinMainCRTStartup")
namespace Depth_Peeling {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();

			point center;

			center[0] = 0.0 ;
			center[1] = 0.0 ;
			center[2] = 0.0 ;
			xf = xform::trans( 0, 0,  -3.5f / fov * 0.8 ) *
				xform::trans(center);

			mesh = NULL ;

			peeling_state = true ;
			dp_com = new DP_COM ;
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^  groupBox1;
	protected: 
	private: System::Windows::Forms::Button^  DepthPeel_button;
	private: System::Windows::Forms::Button^  OpenMesh_button;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: HKOGLPanel::HKOGLPanelControl^  hkoglPanelControl1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::Label^  outputL;
	private: System::Windows::Forms::Button^  clearBtn;
	private: System::Windows::Forms::CheckBox^  showModelBtn;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::CheckBox^  showSurfacePBtn;
	private: System::Windows::Forms::CheckBox^  showSkeletonPBtn;
	private: System::Windows::Forms::ContextMenuStrip^  layerMenu;
	private: System::Windows::Forms::ToolStripMenuItem^  plot1;
	private: System::Windows::Forms::ToolStripMenuItem^  plot2;




	private: System::Windows::Forms::Button^  testBtn;
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::ToolStripMenuItem^  plot3;
	private: System::Windows::Forms::ToolStripMenuItem^  plot4;
	private: System::Windows::Forms::ToolStripMenuItem^  plot5;
	private: System::Windows::Forms::CheckBox^  showSkeletonBtn;
	private: System::Windows::Forms::Label^  curShowLayerL;

	private: System::Windows::Forms::TrackBar^  trackBar1;





	private: System::Windows::Forms::ContextMenuStrip^ noRightMenu;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			HKOGLPanel::HKCOGLPanelCameraSetting^  hkcoglPanelCameraSetting1 = (gcnew HKOGLPanel::HKCOGLPanelCameraSetting());
			HKOGLPanel::HKCOGLPanelPixelFormat^  hkcoglPanelPixelFormat1 = (gcnew HKOGLPanel::HKCOGLPanelPixelFormat());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->curShowLayerL = (gcnew System::Windows::Forms::Label());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->testBtn = (gcnew System::Windows::Forms::Button());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->showSkeletonBtn = (gcnew System::Windows::Forms::CheckBox());
			this->showModelBtn = (gcnew System::Windows::Forms::CheckBox());
			this->showSurfacePBtn = (gcnew System::Windows::Forms::CheckBox());
			this->showSkeletonPBtn = (gcnew System::Windows::Forms::CheckBox());
			this->clearBtn = (gcnew System::Windows::Forms::Button());
			this->outputL = (gcnew System::Windows::Forms::Label());
			this->DepthPeel_button = (gcnew System::Windows::Forms::Button());
			this->OpenMesh_button = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->hkoglPanelControl1 = (gcnew HKOGLPanel::HKOGLPanelControl());
			this->layerMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->plot1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->plot2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->plot3 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->plot4 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->plot5 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->BeginInit();
			this->groupBox3->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->layerMenu->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->curShowLayerL);
			this->groupBox1->Controls->Add(this->trackBar1);
			this->groupBox1->Controls->Add(this->testBtn);
			this->groupBox1->Controls->Add(this->groupBox3);
			this->groupBox1->Controls->Add(this->clearBtn);
			this->groupBox1->Controls->Add(this->outputL);
			this->groupBox1->Controls->Add(this->DepthPeel_button);
			this->groupBox1->Controls->Add(this->OpenMesh_button);
			this->groupBox1->Dock = System::Windows::Forms::DockStyle::Right;
			this->groupBox1->Location = System::Drawing::Point(715, 0);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(150, 720);
			this->groupBox1->TabIndex = 1;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Mesh_OP";
			// 
			// curShowLayerL
			// 
			this->curShowLayerL->AutoSize = true;
			this->curShowLayerL->Location = System::Drawing::Point(119, 505);
			this->curShowLayerL->Name = L"curShowLayerL";
			this->curShowLayerL->Size = System::Drawing::Size(30, 12);
			this->curShowLayerL->TabIndex = 10;
			this->curShowLayerL->Text = L"None";
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(3, 501);
			this->trackBar1->Maximum = 11;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(117, 45);
			this->trackBar1->TabIndex = 9;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &Form1::trackBar1_Scroll);
			// 
			// testBtn
			// 
			this->testBtn->Location = System::Drawing::Point(20, 455);
			this->testBtn->Name = L"testBtn";
			this->testBtn->Size = System::Drawing::Size(75, 23);
			this->testBtn->TabIndex = 8;
			this->testBtn->Text = L"testBtn";
			this->testBtn->UseVisualStyleBackColor = true;
			this->testBtn->Click += gcnew System::EventHandler(this, &Form1::testBtn_Click);
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->showSkeletonBtn);
			this->groupBox3->Controls->Add(this->showModelBtn);
			this->groupBox3->Controls->Add(this->showSurfacePBtn);
			this->groupBox3->Controls->Add(this->showSkeletonPBtn);
			this->groupBox3->Location = System::Drawing::Point(6, 291);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(113, 116);
			this->groupBox3->TabIndex = 7;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Show";
			// 
			// showSkeletonBtn
			// 
			this->showSkeletonBtn->AutoSize = true;
			this->showSkeletonBtn->Checked = true;
			this->showSkeletonBtn->CheckState = System::Windows::Forms::CheckState::Checked;
			this->showSkeletonBtn->Location = System::Drawing::Point(6, 87);
			this->showSkeletonBtn->Name = L"showSkeletonBtn";
			this->showSkeletonBtn->Size = System::Drawing::Size(105, 16);
			this->showSkeletonBtn->TabIndex = 7;
			this->showSkeletonBtn->Text = L"Skeleton segment";
			this->showSkeletonBtn->UseVisualStyleBackColor = true;
			this->showSkeletonBtn->CheckedChanged += gcnew System::EventHandler(this, &Form1::showSkeleton_CheckedChanged);
			// 
			// showModelBtn
			// 
			this->showModelBtn->AutoSize = true;
			this->showModelBtn->Checked = true;
			this->showModelBtn->CheckState = System::Windows::Forms::CheckState::Checked;
			this->showModelBtn->Location = System::Drawing::Point(6, 21);
			this->showModelBtn->Name = L"showModelBtn";
			this->showModelBtn->Size = System::Drawing::Size(54, 16);
			this->showModelBtn->TabIndex = 4;
			this->showModelBtn->Text = L"Model";
			this->showModelBtn->UseVisualStyleBackColor = true;
			this->showModelBtn->CheckedChanged += gcnew System::EventHandler(this, &Form1::showModelBtn_CheckedChanged);
			// 
			// showSurfacePBtn
			// 
			this->showSurfacePBtn->AutoSize = true;
			this->showSurfacePBtn->Checked = true;
			this->showSurfacePBtn->CheckState = System::Windows::Forms::CheckState::Checked;
			this->showSurfacePBtn->Location = System::Drawing::Point(6, 65);
			this->showSurfacePBtn->Name = L"showSurfacePBtn";
			this->showSurfacePBtn->Size = System::Drawing::Size(90, 16);
			this->showSurfacePBtn->TabIndex = 6;
			this->showSurfacePBtn->Text = L"Surface points";
			this->showSurfacePBtn->UseVisualStyleBackColor = true;
			this->showSurfacePBtn->CheckedChanged += gcnew System::EventHandler(this, &Form1::showSurfacePBtn_CheckedChanged);
			// 
			// showSkeletonPBtn
			// 
			this->showSkeletonPBtn->AutoSize = true;
			this->showSkeletonPBtn->Checked = true;
			this->showSkeletonPBtn->CheckState = System::Windows::Forms::CheckState::Checked;
			this->showSkeletonPBtn->Location = System::Drawing::Point(6, 43);
			this->showSkeletonPBtn->Name = L"showSkeletonPBtn";
			this->showSkeletonPBtn->Size = System::Drawing::Size(95, 16);
			this->showSkeletonPBtn->TabIndex = 5;
			this->showSkeletonPBtn->Text = L"Skeleton points";
			this->showSkeletonPBtn->UseVisualStyleBackColor = true;
			this->showSkeletonPBtn->CheckedChanged += gcnew System::EventHandler(this, &Form1::showSkeletonPBtn_CheckedChanged);
			// 
			// clearBtn
			// 
			this->clearBtn->Location = System::Drawing::Point(3, 110);
			this->clearBtn->Name = L"clearBtn";
			this->clearBtn->Size = System::Drawing::Size(144, 48);
			this->clearBtn->TabIndex = 3;
			this->clearBtn->Text = L"Clear All";
			this->clearBtn->UseVisualStyleBackColor = true;
			this->clearBtn->Click += gcnew System::EventHandler(this, &Form1::resetBtn_Click);
			// 
			// outputL
			// 
			this->outputL->AutoSize = true;
			this->outputL->Location = System::Drawing::Point(18, 186);
			this->outputL->Name = L"outputL";
			this->outputL->Size = System::Drawing::Size(33, 12);
			this->outputL->TabIndex = 2;
			this->outputL->Text = L"label1";
			// 
			// DepthPeel_button
			// 
			this->DepthPeel_button->Dock = System::Windows::Forms::DockStyle::Top;
			this->DepthPeel_button->Location = System::Drawing::Point(3, 61);
			this->DepthPeel_button->Name = L"DepthPeel_button";
			this->DepthPeel_button->Size = System::Drawing::Size(144, 43);
			this->DepthPeel_button->TabIndex = 1;
			this->DepthPeel_button->Text = L"Depth Peeling";
			this->DepthPeel_button->UseVisualStyleBackColor = true;
			this->DepthPeel_button->Click += gcnew System::EventHandler(this, &Form1::DepthPeel_button_Click);
			// 
			// OpenMesh_button
			// 
			this->OpenMesh_button->Dock = System::Windows::Forms::DockStyle::Top;
			this->OpenMesh_button->Location = System::Drawing::Point(3, 18);
			this->OpenMesh_button->Name = L"OpenMesh_button";
			this->OpenMesh_button->Size = System::Drawing::Size(144, 43);
			this->OpenMesh_button->TabIndex = 0;
			this->OpenMesh_button->Text = L"OpenMesh";
			this->OpenMesh_button->UseVisualStyleBackColor = true;
			this->OpenMesh_button->Click += gcnew System::EventHandler(this, &Form1::OpenMesh_button_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->hkoglPanelControl1);
			this->groupBox2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox2->Location = System::Drawing::Point(0, 0);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(715, 720);
			this->groupBox2->TabIndex = 2;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"OpenGL_Panel";
			// 
			// hkoglPanelControl1
			// 
			hkcoglPanelCameraSetting1->Far = 1000;
			hkcoglPanelCameraSetting1->Fov = 45;
			hkcoglPanelCameraSetting1->Near = -1000;
			hkcoglPanelCameraSetting1->Type = HKOGLPanel::HKCOGLPanelCameraSetting::CAMERATYPE::ORTHOGRAPHIC;
			this->hkoglPanelControl1->Camera_Setting = hkcoglPanelCameraSetting1;
			this->hkoglPanelControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->hkoglPanelControl1->Location = System::Drawing::Point(3, 18);
			this->hkoglPanelControl1->Name = L"hkoglPanelControl1";
			hkcoglPanelPixelFormat1->Accumu_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat1->Alpha_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_32;
			hkcoglPanelPixelFormat1->Stencil_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			this->hkoglPanelControl1->Pixel_Format = hkcoglPanelPixelFormat1;
			this->hkoglPanelControl1->Size = System::Drawing::Size(709, 699);
			this->hkoglPanelControl1->TabIndex = 0;
			this->hkoglPanelControl1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::hkoglPanelControl1_Paint);
			this->hkoglPanelControl1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::hkoglPanelControl1_KeyPress);
			this->hkoglPanelControl1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::hkoglPanelControl1_MouseDown);
			this->hkoglPanelControl1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::hkoglPanelControl1_MouseMove);
			this->hkoglPanelControl1->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::hkoglPanelControl1_MouseWheel);
			// 
			// layerMenu
			// 
			this->layerMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->plot1, this->plot2, 
				this->plot3, this->plot4, this->plot5});
			this->layerMenu->Name = L"layerMenu";
			this->layerMenu->Size = System::Drawing::Size(153, 136);
			// 
			// plot1
			// 
			this->plot1->Name = L"plot1";
			this->plot1->Size = System::Drawing::Size(152, 22);
			this->plot1->Text = L"Layer 1";
			this->plot1->Click += gcnew System::EventHandler(this, &Form1::plot1_Click);
			// 
			// plot2
			// 
			this->plot2->Name = L"plot2";
			this->plot2->Size = System::Drawing::Size(152, 22);
			this->plot2->Text = L"Layer 2";
			this->plot2->Click += gcnew System::EventHandler(this, &Form1::plot2_Click);
			// 
			// plot3
			// 
			this->plot3->Name = L"plot3";
			this->plot3->Size = System::Drawing::Size(152, 22);
			this->plot3->Text = L"Layer 3";
			this->plot3->Click += gcnew System::EventHandler(this, &Form1::plot3_Click);
			// 
			// plot4
			// 
			this->plot4->Name = L"plot4";
			this->plot4->Size = System::Drawing::Size(152, 22);
			this->plot4->Text = L"Layer 4";
			this->plot4->Click += gcnew System::EventHandler(this, &Form1::plot4_Click);
			// 
			// plot5
			// 
			this->plot5->Name = L"plot5";
			this->plot5->Size = System::Drawing::Size(152, 22);
			this->plot5->Text = L"Layer 5";
			this->plot5->Click += gcnew System::EventHandler(this, &Form1::plot5_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::openFileDialog1_FileOk);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(865, 720);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->EndInit();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->layerMenu->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void hkoglPanelControl1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			 glEnable(GL_COLOR_MATERIAL);
			 glClearColor( 1.0, 1.0, 1.0, 1.0);
			 glClear( GL_COLOR_BUFFER_BIT  );

			 point center;
			 center[0] = 0.0 ;
			 center[1] = 0.0 ;
			 center[2] = 0.0 ;
			 camera.setupGL( xf * center, 1.0 ) ;


			 glPushMatrix();
			 glMatrixMode(GL_MODELVIEW);
			 glMultMatrixd((double *)xf);

			 if ( mesh != NULL )
			 {
				 if( showModelBtn->Checked )
				 {
					//if(peeling_state==false)
					//{
					//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					//	glEnable(GL_BLEND);
					//}
					mesh->Render_Solid();
					//if(peeling_state==false)
					//{
					//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					//	glDisable(GL_BLEND);
					//}
					
				 }
				 
				 mesh->RenderSpecifiedPoint(OMT::Model::spList);
				 
				 if( showSkeletonPBtn->Checked )
				 {
					mesh->RenderSpecifiedPoint(OMT::Model::skeletonList);
				 }
				 if( showSurfacePBtn->Checked )
				 {
					mesh->RenderSpecifiedPoint(OMT::Model::surfaceList);
				 }
				 if( showSkeletonBtn->Checked )
				 {
					 dp_com->RenderSkeleton( (mesh->skeleton_p_list) );
				 }
				 if( trackBar1->Value != 0 )
				 {
					 this->RenderDepthPoints();
				 }

			 }


			 glPopMatrix();
		 }
private: System::Void RenderDepthPoints()
		 {
			glDisable(GL_LIGHTING);
			glPointSize ( 8.0 ) ;				  
			glColor3f( 0.0, 0.0, 1.0 ) ;
			glBegin(GL_POINTS);
			if( trackBar1->Value != 11 )	// ==0的狀況在paint時過濾掉了，只要考慮all
			{
				glVertex3dv( dp_com->tmpSurP[trackBar1->Value - 1] );
			}
			else
			{	//all
				for(int curD = 0 ; curD<MAX_LAYERS ; curD++)
				{
					glVertex3dv( dp_com->tmpSurP[curD] );
				}
			}
			glEnd();
			glEnable(GL_LIGHTING);
		 }
private: System::Windows::Forms::MouseEventArgs^ lastMouseE;
private: System::Void hkoglPanelControl1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 lastMouseE = e;
			 if (e->Button == System::Windows::Forms::MouseButtons::Left ||
				 e->Button == System::Windows::Forms::MouseButtons::Middle)
			 {
				 point center;
				 Mouse_State = Mouse::NONE;
				 center[0] = 0.0 ;
				 center[1] = 0.0 ;
				 center[2] = 0.0 ;				    
				 camera.mouse(e->X,e->Y, Mouse_State,
					 xf * center,
					 1.0, xf);
			 }
			 else if(e->Button == System::Windows::Forms::MouseButtons::Right)
			 {
				
				//System::Windows::Forms::ContextMenuStrip^ QQ= this->ContextMenuStrip;
				//this->ContextMenuStrip = layerMenu;
				//this->ContextMenuStrip = QQ;
				//this->ContextMenuStrip = NULL;
				this->ContextMenuStrip = layerMenu;	//預設為有右鍵選單狀態
				GLint viewport[4];
				GLdouble modelview[16];
				GLdouble projection[16];
				GLfloat winX, winY, winZ;
				//GLdouble objX, objY, objZ;
				glPushMatrix();

				glMatrixMode(GL_MODELVIEW);	glMultMatrixd((double *)xf);
				glGetDoublev( GL_MODELVIEW_MATRIX, modelview );

				glMatrixMode(GL_PROJECTION_MATRIX);	glMultMatrixd((double *)xf);
				glGetDoublev( GL_PROJECTION_MATRIX, projection );

				glMatrixMode(GL_VIEWPORT); glMultMatrixd((double *)xf);
				glGetIntegerv( GL_VIEWPORT, viewport );

				winX = (float)e->X;
				winY = (float)viewport[3] - (float)e->Y;

				glEnable(GL_DEPTH_TEST);
				glReadPixels( int(winX), int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
				glDisable(GL_DEPTH_TEST);

				outputL->Text = "mouseX= " + (e->X).ToString() + "\nmouseY= " + (e->Y).ToString();
				outputL->Text += "\nmouseZ= " + winZ +"\n" ;
				
				//if(winZ>=0.99999f)
				//{
				//	std::cerr << "Click on background (z= " << winZ << ")" << std::endl;
				//}
				//else
				//{
				//	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &objX, &objY, &objZ);
				//	outputL->Text += "\nObjectX: "+objX+"\nObjectY: "+objY+"\nObjectZ: "+(objZ);
				//	//加入目前的滑鼠點
				//	mesh->clear_sp_p();
				//	mesh->clear_surface_p();
				//	mesh->clear_skeleton_p();
				//	mesh->add_sp_p( OMT::MyMesh::Point(objX,objY,objZ), 1.0f, 0.0f, 1.0f);
				//}

				if(peeling_state==false)
				{	//該點的總層數
					int totalLayers = dp_com->m_ValidBuffer[ (int)winY*(hkoglPanelControl1->Width) + (int)winX ];

					//抓出Z值 並顯示在console
					for(int i=0 ; i<totalLayers ; i++)
					{
						int theIndex = (i*(hkoglPanelControl1->Width)*(hkoglPanelControl1->Height)) + (int)winY*(hkoglPanelControl1->Width) + (int)winX;
						float zValue = (dp_com->m_pZBuffer)[ theIndex ];
						//std::cout << (dp_com->m_pZBuffer)[ (int)( (i*(hkoglPanelControl1->Width)*(hkoglPanelControl1->Height)) + winY*(hkoglPanelControl1->Width)+winX) ] << " ";
						//if(zValue >= 1.f)
						//{	//深度大於1為背景，直接跳開
						//	break;
						//}
						std::cout << zValue << " ";
						
						//GLdouble drawX, drawY, drawZ;
						//gluUnProject( winX, winY, zValue, modelview, projection, viewport, &drawX, &drawY, &drawZ);
						
						/*
						glPushAttrib(GL_LIGHTING_BIT);
						glDisable(GL_LIGHTING);
						glEnable(GL_DEPTH_TEST);
						glPointSize(5.0f);
						glBegin(GL_POINTS);

							glColor3f(1.f, 0.f, 0.f);
							glVertex3d(drawX, drawY, drawZ);

						glEnd();
						glEnable(GL_LIGHTING);
						glDisable(GL_POLYGON_OFFSET_FILL);
						this->Refresh();
						*/
						//std::cout << "drawZ =" << drawZ << std::endl;
						
						//mesh->add_surface_p( OMT::MyMesh::Point(drawX,drawY,drawZ), 1.0f, 0.0f, 0.0f);
					}
					std::cout << " :" << dp_com->m_ValidBuffer[ (int)winY*(hkoglPanelControl1->Width) + (int)winX ] << std::endl;
					this->ContextMenuStrip = layerMenu;
					layerMenu->Visible = true;
					if( totalLayers/2 > 1 )
					{	//如果大於一層
						
						//OMT::Point tmpSurP[MAX_LAYERS];
						//OMT::Point preP(-100,-100,-100);
						const float minThreshold = 0.000005f;
						int theIndex = 0;
						float zValue = 0.f;
						//int totalSurfaceLayers = 0;	//總共經過的面層數
						//for(int surLayer = 0 ; surLayer<MAX_LAYERS ; surLayer++)
						for(int surLayer = 0 ; surLayer<totalLayers ; surLayer++)
						{	//先算出每層的實際座標點，以及實際的面層數(totalSurfaceLayers)
							theIndex = (surLayer*(hkoglPanelControl1->Width)*(hkoglPanelControl1->Height)) + (int)winY*(hkoglPanelControl1->Width) + (int)winX;
							zValue = (dp_com->m_pZBuffer)[ theIndex ];
							if(zValue >= 1.f)break;	//到尾端，跳開(early jump
							gluUnProject( winX, winY, zValue, modelview, projection, viewport, &(dp_com->tmpSurP[surLayer][0]), &(dp_com->tmpSurP[surLayer][1]), &(dp_com->tmpSurP[surLayer][2]));
							//totalSurfaceLayers++;
						}
						for(int surLayer = 0 ; surLayer < totalLayers ; surLayer++)
						{	//檢查是否有太近的點
							
							float diffDist = 0.f;
							if( surLayer>0)
							{
								OMT::Point diffP = dp_com->tmpSurP[surLayer] - dp_com->tmpSurP[surLayer-1];
								diffDist = diffP[0]*diffP[0] + diffP[1]*diffP[1] + diffP[2]*diffP[2];
								if(diffDist < minThreshold)
								{	//兩層太過接近，視為誤差，捨去目前這層
									int curShiftLayer;
									for(curShiftLayer = surLayer ; curShiftLayer < totalLayers-1 ; curShiftLayer++)
									{	//將後面的深度往前移
										dp_com->tmpSurP[curShiftLayer] = dp_com->tmpSurP[curShiftLayer+1];
									}
									dp_com->tmpSurP[curShiftLayer] = OMT::Point(-100.f,-100.f,-100.f);	//最後尾巴會有無用數值，填1以讓下次跳開
									//std::cout<< curLayer << " ";
									surLayer--;	//檢查的層數-1
									totalLayers--;	//總層數-1
								}
							}
						}
						totalLayers = totalLayers / 2;
						//totalSurfaceLayers = 3;
						//int a = totalSurfaceLayers / 2;
						//totalLayers = a;

						plot1->Visible = false;
						plot2->Visible = false;
						plot3->Visible = false;
						plot4->Visible = false;
						plot5->Visible = false;
						
						switch (totalLayers)
						{
							case 5:
								plot5->Visible = true;
								std::cout << "4-2: (" << dp_com->tmpSurP[9][0] << ", " << dp_com->tmpSurP[9][1] << ", " << dp_com->tmpSurP[9][2] << ") \n";
								std::cout << "4-1: (" << dp_com->tmpSurP[8][0] << ", " << dp_com->tmpSurP[8][1] << ", " << dp_com->tmpSurP[8][2] << ") \n";
							case 4:
								plot4->Visible = true;
								std::cout << "3-2: (" << dp_com->tmpSurP[7][0] << ", " << dp_com->tmpSurP[7][1] << ", " << dp_com->tmpSurP[7][2] << ") \n";
								std::cout << "3-1: (" << dp_com->tmpSurP[6][0] << ", " << dp_com->tmpSurP[6][1] << ", " << dp_com->tmpSurP[6][2] << ") \n";
							case 3:
								plot3->Visible = true;
								std::cout << "2-2: (" << dp_com->tmpSurP[5][0] << ", " << dp_com->tmpSurP[5][1] << ", " << dp_com->tmpSurP[5][2] << ") \n";
								std::cout << "2-1: (" << dp_com->tmpSurP[4][0] << ", " << dp_com->tmpSurP[4][1] << ", " << dp_com->tmpSurP[4][2] << ") \n";
							case 2:
								plot2->Visible = true;
								std::cout << "1-2: (" << dp_com->tmpSurP[3][0] << ", " << dp_com->tmpSurP[3][1] << ", " << dp_com->tmpSurP[3][2] << ") \n";
								std::cout << "1-1: (" << dp_com->tmpSurP[2][0] << ", " << dp_com->tmpSurP[2][1] << ", " << dp_com->tmpSurP[2][2] << ") \n";
							case 1:
								plot1->Visible = true;
								std::cout << "0-2: (" << dp_com->tmpSurP[1][0] << ", " << dp_com->tmpSurP[1][1] << ", " << dp_com->tmpSurP[1][2] << ") \n";
								std::cout << "0-1: (" << dp_com->tmpSurP[0][0] << ", " << dp_com->tmpSurP[0][1] << ", " << dp_com->tmpSurP[0][2] << ") \n";
								if(totalLayers==1)
								{
									std::cout << "only one layer after refining\n";
								}
							default:
								break;
						}
						layerMenu->Visible = true;
						std::cout << totalLayers << "layers after refining checked \n";
						//交由右鍵選單按鈕作後續動作
					}
					else
					{
						this->ContextMenuStrip->Visible = false;
						this->ContextMenuStrip = noRightMenu;	//取消右鍵選單
						//this->ContextMenuStrip->Visible = false;
						//畫出最表層的表面和骨架點
						GLdouble drawX, drawY, drawZ;
						int theIndex = 0;
						float zValue = 0.f;
						theIndex = 0 + ( winY )*(hkoglPanelControl1->Width) + (winX);
						zValue = (dp_com->m_pZBuffer)[ theIndex ];

						gluUnProject( winX, winY, zValue, modelview, projection, viewport, &drawX, &drawY, &drawZ);
						OMT::MyMesh::Point frontPoint(drawX, drawY, drawZ); 
						mesh->add_surface_p( frontPoint, 0.0f, 1.0f, 0.0f);	//畫表面點

						theIndex = ( (0+1) *(hkoglPanelControl1->Width)*(hkoglPanelControl1->Height)) + ((int)winY) * (hkoglPanelControl1->Width) + ((int)winX);
						zValue = (dp_com->m_pZBuffer)[ theIndex ];
						gluUnProject( winX, winY, zValue, modelview, projection, viewport, &drawX, &drawY, &drawZ);
						OMT::MyMesh::Point backPoint(drawX, drawY, drawZ);
						mesh->add_surface_p( backPoint, 0.0f, 1.0f, 0.0f);	//畫表面點

						if( dp_com->newLine )
						{	//為線段起點
							dp_com->lineSegIndex.push_back(mesh->skeleton_p_list.size());
							dp_com->newLine  = false;
						}
						else
						{	//不為線段起點
									glDisable(GL_LIGHTING);
									glLineWidth(3.0);
									glBegin(GL_LINES);
									glColor3f( 0.f, 0.f, 1.f);
									glVertex3dv( dp_com->previousP );
									glVertex3dv( ((frontPoint+backPoint)/2) );
									glEnd();
									glLineWidth(1.0);
									glEnable(GL_LIGHTING);
						}
						dp_com->previousP = (frontPoint+backPoint)/2 ;
						mesh->add_skeleton_p( (frontPoint+backPoint)/2 , 1.0f, 0.0f, 0.0f);	//畫骨架點
						this->Refresh();
						////畫出所有層的表面和骨架點
						//for(int curMid = 0, curLayer = 0 ; curMid < totalLayers ; curMid++, curLayer+=2)
						//{
						//	int theIndex = (curLayer*(hkoglPanelControl1->Width)*(hkoglPanelControl1->Height)) + (int)winY*(hkoglPanelControl1->Width) + (int)winX;
						//	float zValue = (dp_com->m_pZBuffer)[ theIndex ];
						//	
						//	
						//	GLdouble drawX, drawY, drawZ;
						//	gluUnProject( winX, winY, zValue, modelview, projection, viewport, &drawX, &drawY, &drawZ);
						//	OMT::MyMesh::Point frontPoint(drawX, drawY, drawZ); 
						//	mesh->add_surface_p( frontPoint, 1.0f, 0.0f, 0.0f);	//畫表面點
						//
						//	theIndex = ( (curLayer+1) *(hkoglPanelControl1->Width)*(hkoglPanelControl1->Height)) + (int)winY*(hkoglPanelControl1->Width) + (int)winX;
						//	zValue = (dp_com->m_pZBuffer)[ theIndex ];
						//	gluUnProject( winX, winY, zValue, modelview, projection, viewport, &drawX, &drawY, &drawZ);
						//	OMT::MyMesh::Point backPoint(drawX, drawY, drawZ);
						//	mesh->add_surface_p( backPoint, 1.0f, 0.0f, 0.0f);	//畫表面點
						//
						//	mesh->add_skeleton_p( (frontPoint+backPoint)/2 , 0.0f, 1.0f, 0.0f);	//畫骨架點
						//
						//}
						//
					}
				}
				glPopMatrix();
				this->Refresh();
				return;
			 }
		 }
private: System::Void hkoglPanelControl1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if (e->Button == System::Windows::Forms::MouseButtons::Left)
			 { 
				 point center;
				 Mouse_State = Mouse::ROTATE;
				 center[0] = 0.0 ;
				 center[1] = 0.0 ;
				 center[2] = 0.0 ;				    
				 camera.mouse(e->X,e->Y, Mouse_State,
					 xf * center,
					 1.0, xf);
				 hkoglPanelControl1->Invalidate();
			}

			 if (e->Button == System::Windows::Forms::MouseButtons::Middle)
			 { 
				 point center;
				 Mouse_State = Mouse::MOVEXY;
				 center[0] = 0.0 ;
				 center[1] = 0.0 ;
				 center[2] = 0.0 ;				    
				 camera.mouse(e->X,e->Y, Mouse_State,
					 xf * center,
					 1.0, xf);
				 hkoglPanelControl1->Invalidate();
			 }
			 
		 }
private: System::Void OpenMesh_button_Click(System::Object^  sender, System::EventArgs^  e) {
			    openFileDialog1->ShowDialog();
		 }
private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 std::string filename;
			 MarshalString( openFileDialog1->FileName, filename );

			 if( mesh != NULL )
				 delete mesh ;

			 mesh = new Tri_Mesh;


			 if(ReadFile(  filename, mesh  ) )
				 std::cout<<filename<<std::endl;

			 hkoglPanelControl1->Invalidate();
		 }
private: System::Void hkoglPanelControl1_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			 if (e->Delta<0)
			 {
				 point center;
				 Mouse_State = Mouse::WHEELDOWN;
				 center[0] = 0.0 ;
				 center[1] = 0.0 ;
				 center[2] = 0.0 ;				    
				 camera.mouse(e->X,e->Y, Mouse_State,
					 xf * center,
					 1.0, xf);
				 hkoglPanelControl1->Invalidate();
			 }
			 else
			 {
				 point center;
				 Mouse_State = Mouse::WHEELUP;
				 center[0] = 0.0 ;
				 center[1] = 0.0 ;
				 center[2] = 0.0 ;				    
				 camera.mouse(e->X,e->Y, Mouse_State,
					 xf * center,
					 1.0, xf);
				 hkoglPanelControl1->Invalidate();
			 }
		 }
private: System::Void DepthPeel_button_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(mesh==NULL)return;	//沒有載入model則直接關掉
			 if ( peeling_state )
			   {
				   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				   glEnable(GL_BLEND);
				   glDisable(GL_DEPTH_TEST);	//*******開了可能會抓不到深度
				   peeling_state = false ;
				   glMatrixMode(GL_VIEWPORT); glMultMatrixd((double *)xf);
				   if(  dp_com->Scene_Init() )
				   {
					   dp_com->Set_BufferObj(hkoglPanelControl1->Width, hkoglPanelControl1->Height);
					   //用for迴圈將每一層Depth Layer 抓出來
						for(int curLayer = 0 ; curLayer< MAX_LAYERS ; curLayer++ )
						{
							//  DP_COM::Peeling_layer
							dp_com->Peeling_layer( hkoglPanelControl1->Width, hkoglPanelControl1->Height, curLayer, mesh, xf );
						}
						dp_com->Set_ValidRegion( hkoglPanelControl1->Width, hkoglPanelControl1->Height );
					 
						std::cout<<"Peeling Success....." << std::endl;
				   }
				   else
				   {
				       std::cout<<"Peeling Fail.............WTX.............." << std::endl;
				   }
			   } 
			   else
			   {
				   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				   glDisable(GL_BLEND);
				   glEnable( GL_DEPTH_TEST ) ;
				   peeling_state = true ;
			   }
			   
			   glPolygonMode(  GL_FRONT, GL_FILL ) ;
			   glPolygonMode(  GL_BACK, GL_POINT ) ;
			   hkoglPanelControl1->Invalidate( );
		 }
private: System::Void resetBtn_Click(System::Object^  sender, System::EventArgs^  e) {
			mesh->clear_sp_p();
			mesh->clear_surface_p();
			mesh->clear_skeleton_p();
			dp_com->clearLineSegIndex();
			this->Refresh();
		 }
private: System::Void showModelBtn_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 this->Refresh();
		 }
private: System::Void showSkeletonPBtn_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 this->Refresh();
		 }
private: System::Void showSurfacePBtn_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 this->Refresh();
		 }
private: System::Void testBtn_Click(System::Object^  sender, System::EventArgs^  e) {
			 
		 }
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			 this->noRightMenu = this->ContextMenuStrip;
		}

private: System::Void hkoglPanelControl1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
			 if(e->KeyChar == '\r')
			 {
				std::cout << "ENTER" << std::endl;
				dp_com->newLine = true;	//下一個點要畫新線段
				dp_com->lineSegIndex.push_back(mesh->skeleton_p_list.size());
				std::vector<int>::iterator it;
				this->Invalidate();
				//for( it = dp_com->lineSegIndex.begin() ; it != dp_com->lineSegIndex.end() ; it++)
				//{
				//	 //std::cout << it << " ";
				//}
			 }
		 }
private: System::Void showSkeleton_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			this->Refresh();
		 }
private: System::Void plot1_Click(System::Object^  sender, System::EventArgs^  e) {
			this->drawLayerPoints(1);
		}
private: System::Void plot2_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->drawLayerPoints(2);
		 }
private: System::Void plot3_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->drawLayerPoints(3);
		 }
private: System::Void plot4_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->drawLayerPoints(4);
		 }
private: System::Void plot5_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->drawLayerPoints(5);
		 }
private: System::Void drawLayerPoints(int theLayer)
		 {
/*
			GLint viewport[4];
			GLdouble modelview[16];
			GLdouble projection[16];
			GLfloat winX, winY, winZ;
			glPushMatrix();
			glMatrixMode(GL_MODELVIEW);	glMultMatrixd((double *)xf);
			glGetDoublev( GL_MODELVIEW_MATRIX, modelview );

			glMatrixMode(GL_PROJECTION_MATRIX);	glMultMatrixd((double *)xf);
			glGetDoublev( GL_PROJECTION_MATRIX, projection );

			glMatrixMode(GL_VIEWPORT); glMultMatrixd((double *)xf);
			glGetIntegerv( GL_VIEWPORT, viewport );

			winX = (float)lastMouseE->X;
			winY = (float)viewport[3] - (float)lastMouseE->Y;

			glEnable(GL_DEPTH_TEST);
			glReadPixels( int(winX), int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
			glDisable(GL_DEPTH_TEST);

			//畫出最表層的表面和骨架點
			GLdouble drawX, drawY, drawZ;
			int theIndex = 0;
			float zValue = 0.f;

			theIndex = (theLayer*(hkoglPanelControl1->Width)*(hkoglPanelControl1->Height)) + (int)winY*(hkoglPanelControl1->Width) + (int)winX;
			zValue = (dp_com->m_pZBuffer)[ theIndex ];
			gluUnProject( winX, winY, zValue, modelview, projection, viewport, &drawX, &drawY, &drawZ);
			OMT::MyMesh::Point frontPoint(drawX, drawY, drawZ); 
			mesh->add_surface_p( frontPoint, 0.0f, 1.0f, 0.0f);	//畫表面點

			theIndex = ( (theLayer+1) *(hkoglPanelControl1->Width)*(hkoglPanelControl1->Height)) + (int)winY*(hkoglPanelControl1->Width) + (int)winX;
			zValue = (dp_com->m_pZBuffer)[ theIndex ];
			gluUnProject( winX, winY, zValue, modelview, projection, viewport, &drawX, &drawY, &drawZ);
			OMT::MyMesh::Point backPoint(drawX, drawY, drawZ);
			mesh->add_surface_p( backPoint, 0.0f, 1.0f, 0.0f);	//畫表面點
*/

			OMT::MyMesh::Point &frontPoint = dp_com->tmpSurP[theLayer*2]; 
			OMT::MyMesh::Point &backPoint = dp_com->tmpSurP[theLayer*2+1]; 
			if( dp_com->newLine )
			{	//為線段起點
				dp_com->lineSegIndex.push_back(mesh->skeleton_p_list.size());
				dp_com->newLine  = false;
			}
			else
			{	//不為線段起點
						glDisable(GL_LIGHTING);
						glLineWidth(3.0);
						glBegin(GL_LINES);
						glColor3f( 0.f, 0.f, 1.f);
						glVertex3dv( dp_com->previousP );
						glVertex3dv( ((frontPoint+backPoint)/2) );
						glEnd();
						glLineWidth(1.0);
						glEnable(GL_LIGHTING);
			}
			dp_com->previousP = (frontPoint+backPoint)/2 ;
			mesh->add_skeleton_p( (frontPoint+backPoint)/2 , 1.0f, 0.0f, 0.0f);	//畫骨架點
						
			
			//glPopMatrix();
			//this->Refresh();
			return;
		}
private: System::Void trackBar1_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 if(trackBar1->Value ==0)
			 {
				 curShowLayerL->Text = "None";
			 }
			 else if(trackBar1->Value == 11)
			 {
				 curShowLayerL->Text = "All";
			 }
			 else
			 {
				curShowLayerL->Text = (trackBar1->Value).ToString();
			 }
			 this->Refresh();
		 }
};
}

