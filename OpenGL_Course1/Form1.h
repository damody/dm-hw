#pragma once

#include "DotNetUtilities.h"
#include "Mesh/GUA_OM.h"
#include "Mesh/GLCamera.h"
#include "Mesh/XForm.h"
#include <vector>



Tri_Mesh *mesh;

xform xf;
GLCamera camera;
float fov = 0.7f;

static const Mouse::button physical_to_logical_map[] = {
	Mouse::NONE, Mouse::ROTATE, Mouse::MOVEXY, Mouse::MOVEZ,
	Mouse::MOVEZ, Mouse::MOVEXY, Mouse::MOVEXY, Mouse::MOVEXY,
};
Mouse::button Mouse_State = Mouse::ROTATE;

#pragma comment(linker, "/subsystem:console /entry:WinMainCRTStartup")

namespace OpenGL_Course1 {

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
			xf = xform::trans(0, 0, -3.5f / fov * 0.8) *
				xform::trans(center);

			mesh = NULL ;
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
	private: HKOGLPanel::HKOGLPanelControl^  hkoglPanelControl1;

	private: System::Windows::Forms::OpenFileDialog^  openMeshFileDialog;


	private: System::Windows::Forms::CheckBox^  wireframeBox;
	private: System::Windows::Forms::RadioButton^  selFBtn;


	private: System::Windows::Forms::RadioButton^  selEBtn;

	private: System::Windows::Forms::RadioButton^  selVBtn;


	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::RadioButton^  neiFBtn;

	private: System::Windows::Forms::RadioButton^  neiEBtn;

	private: System::Windows::Forms::RadioButton^  neiVBtn;
	private: System::Windows::Forms::Label^  outputL;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::CheckBox^  modelBox;
	private: System::Windows::Forms::CheckBox^  axisBtn;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::Label^  pathLable;









	protected: 






	private: System::ComponentModel::IContainer^  components;
	protected: 

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
			HKOGLPanel::HKCOGLPanelCameraSetting^  hkcoglPanelCameraSetting1 = (gcnew HKOGLPanel::HKCOGLPanelCameraSetting());
			HKOGLPanel::HKCOGLPanelPixelFormat^  hkcoglPanelPixelFormat1 = (gcnew HKOGLPanel::HKCOGLPanelPixelFormat());
			this->hkoglPanelControl1 = (gcnew HKOGLPanel::HKOGLPanelControl());
			this->openMeshFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->wireframeBox = (gcnew System::Windows::Forms::CheckBox());
			this->selVBtn = (gcnew System::Windows::Forms::RadioButton());
			this->selEBtn = (gcnew System::Windows::Forms::RadioButton());
			this->selFBtn = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->neiFBtn = (gcnew System::Windows::Forms::RadioButton());
			this->neiEBtn = (gcnew System::Windows::Forms::RadioButton());
			this->neiVBtn = (gcnew System::Windows::Forms::RadioButton());
			this->outputL = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->modelBox = (gcnew System::Windows::Forms::CheckBox());
			this->axisBtn = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->pathLable = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->SuspendLayout();
			// 
			// hkoglPanelControl1
			// 
			hkcoglPanelCameraSetting1->Far = 1000;
			hkcoglPanelCameraSetting1->Fov = 45;
			hkcoglPanelCameraSetting1->Near = -1000;
			hkcoglPanelCameraSetting1->Type = HKOGLPanel::HKCOGLPanelCameraSetting::CAMERATYPE::ORTHOGRAPHIC;
			this->hkoglPanelControl1->Camera_Setting = hkcoglPanelCameraSetting1;
			this->hkoglPanelControl1->Dock = System::Windows::Forms::DockStyle::Top;
			this->hkoglPanelControl1->Location = System::Drawing::Point(0, 0);
			this->hkoglPanelControl1->Name = L"hkoglPanelControl1";
			hkcoglPanelPixelFormat1->Accumu_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat1->Alpha_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat1->Stencil_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			this->hkoglPanelControl1->Pixel_Format = hkcoglPanelPixelFormat1;
			this->hkoglPanelControl1->Size = System::Drawing::Size(791, 497);
			this->hkoglPanelControl1->TabIndex = 0;
			this->hkoglPanelControl1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::hkoglPanelControl1_Paint);
			this->hkoglPanelControl1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::hkoglPanelControl1_MouseDown);
			this->hkoglPanelControl1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::hkoglPanelControl1_MouseMove);
			this->hkoglPanelControl1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::hkoglPanelControl1_MouseUp);
			this->hkoglPanelControl1->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::hkoglPanelControl1_MouseWheel);
			// 
			// openMeshFileDialog
			// 
			this->openMeshFileDialog->FileName = L"text";
			this->openMeshFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::openMeshFileDialog_FileOk);
			// 
			// wireframeBox
			// 
			this->wireframeBox->AutoSize = true;
			this->wireframeBox->Location = System::Drawing::Point(6, 41);
			this->wireframeBox->Name = L"wireframeBox";
			this->wireframeBox->Size = System::Drawing::Size(74, 16);
			this->wireframeBox->TabIndex = 2;
			this->wireframeBox->Text = L"Wireframe";
			this->wireframeBox->UseVisualStyleBackColor = true;
			this->wireframeBox->Click += gcnew System::EventHandler(this, &Form1::wireframeBox_Click);
			// 
			// selVBtn
			// 
			this->selVBtn->AutoSize = true;
			this->selVBtn->Location = System::Drawing::Point(6, 19);
			this->selVBtn->Name = L"selVBtn";
			this->selVBtn->Size = System::Drawing::Size(54, 16);
			this->selVBtn->TabIndex = 0;
			this->selVBtn->TabStop = true;
			this->selVBtn->Text = L"Vertex";
			this->selVBtn->UseVisualStyleBackColor = true;
			// 
			// selEBtn
			// 
			this->selEBtn->AutoSize = true;
			this->selEBtn->Location = System::Drawing::Point(6, 41);
			this->selEBtn->Name = L"selEBtn";
			this->selEBtn->Size = System::Drawing::Size(47, 16);
			this->selEBtn->TabIndex = 1;
			this->selEBtn->TabStop = true;
			this->selEBtn->Text = L"Edge";
			this->selEBtn->UseVisualStyleBackColor = true;
			// 
			// selFBtn
			// 
			this->selFBtn->AutoSize = true;
			this->selFBtn->Location = System::Drawing::Point(6, 63);
			this->selFBtn->Name = L"selFBtn";
			this->selFBtn->Size = System::Drawing::Size(44, 16);
			this->selFBtn->TabIndex = 2;
			this->selFBtn->TabStop = true;
			this->selFBtn->Text = L"Face";
			this->selFBtn->UseVisualStyleBackColor = true;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->selEBtn);
			this->groupBox1->Controls->Add(this->selFBtn);
			this->groupBox1->Controls->Add(this->selVBtn);
			this->groupBox1->Location = System::Drawing::Point(269, 503);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(69, 91);
			this->groupBox1->TabIndex = 4;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Select";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->neiFBtn);
			this->groupBox2->Controls->Add(this->neiEBtn);
			this->groupBox2->Controls->Add(this->neiVBtn);
			this->groupBox2->Location = System::Drawing::Point(344, 503);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(69, 91);
			this->groupBox2->TabIndex = 5;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"One Ring";
			// 
			// neiFBtn
			// 
			this->neiFBtn->AutoSize = true;
			this->neiFBtn->Location = System::Drawing::Point(6, 65);
			this->neiFBtn->Name = L"neiFBtn";
			this->neiFBtn->Size = System::Drawing::Size(44, 16);
			this->neiFBtn->TabIndex = 2;
			this->neiFBtn->TabStop = true;
			this->neiFBtn->Text = L"Face";
			this->neiFBtn->UseVisualStyleBackColor = true;
			// 
			// neiEBtn
			// 
			this->neiEBtn->AutoSize = true;
			this->neiEBtn->Location = System::Drawing::Point(6, 43);
			this->neiEBtn->Name = L"neiEBtn";
			this->neiEBtn->Size = System::Drawing::Size(47, 16);
			this->neiEBtn->TabIndex = 1;
			this->neiEBtn->TabStop = true;
			this->neiEBtn->Text = L"Edge";
			this->neiEBtn->UseVisualStyleBackColor = true;
			// 
			// neiVBtn
			// 
			this->neiVBtn->AutoSize = true;
			this->neiVBtn->Location = System::Drawing::Point(6, 21);
			this->neiVBtn->Name = L"neiVBtn";
			this->neiVBtn->Size = System::Drawing::Size(54, 16);
			this->neiVBtn->TabIndex = 0;
			this->neiVBtn->TabStop = true;
			this->neiVBtn->Text = L"Vertex";
			this->neiVBtn->UseVisualStyleBackColor = true;
			// 
			// outputL
			// 
			this->outputL->AutoSize = true;
			this->outputL->Location = System::Drawing::Point(498, 516);
			this->outputL->Name = L"outputL";
			this->outputL->Size = System::Drawing::Size(33, 12);
			this->outputL->TabIndex = 6;
			this->outputL->Text = L"label1";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 503);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(153, 111);
			this->button1->TabIndex = 7;
			this->button1->Text = L"Open Mesh";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// modelBox
			// 
			this->modelBox->AutoSize = true;
			this->modelBox->Checked = true;
			this->modelBox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->modelBox->Location = System::Drawing::Point(6, 19);
			this->modelBox->Name = L"modelBox";
			this->modelBox->Size = System::Drawing::Size(54, 16);
			this->modelBox->TabIndex = 8;
			this->modelBox->Text = L"Model";
			this->modelBox->UseVisualStyleBackColor = true;
			this->modelBox->CheckedChanged += gcnew System::EventHandler(this, &Form1::modelBox_CheckedChanged);
			// 
			// axisBtn
			// 
			this->axisBtn->AutoSize = true;
			this->axisBtn->Checked = true;
			this->axisBtn->CheckState = System::Windows::Forms::CheckState::Checked;
			this->axisBtn->Location = System::Drawing::Point(6, 63);
			this->axisBtn->Name = L"axisBtn";
			this->axisBtn->Size = System::Drawing::Size(45, 16);
			this->axisBtn->TabIndex = 9;
			this->axisBtn->Text = L"Axis";
			this->axisBtn->UseVisualStyleBackColor = true;
			this->axisBtn->CheckedChanged += gcnew System::EventHandler(this, &Form1::axisBtn_CheckedChanged);
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->modelBox);
			this->groupBox3->Controls->Add(this->axisBtn);
			this->groupBox3->Controls->Add(this->wireframeBox);
			this->groupBox3->Location = System::Drawing::Point(171, 503);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(92, 91);
			this->groupBox3->TabIndex = 10;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Show";
			// 
			// pathLable
			// 
			this->pathLable->AutoSize = true;
			this->pathLable->Location = System::Drawing::Point(174, 600);
			this->pathLable->Name = L"pathLable";
			this->pathLable->Size = System::Drawing::Size(51, 12);
			this->pathLable->TabIndex = 11;
			this->pathLable->Text = L"No model";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(791, 626);
			this->Controls->Add(this->pathLable);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->outputL);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->hkoglPanelControl1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void openMeshFileDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
				 std::string filename;
				 MarshalString( openMeshFileDialog->FileName, filename );

				 if( mesh != NULL )
					 delete mesh ;

				 mesh = new Tri_Mesh;
				  
				 
				 if(ReadFile(  filename, mesh  ) )
				 {
			          std::cout<<filename<<std::endl;
					  pathLable->Text = openMeshFileDialog->FileName;
				 }

				hkoglPanelControl1->Invalidate();
			 }
	private: System::Void OpenMesh_button_Click(System::Object^  sender, System::EventArgs^  e) {
				 
				 openMeshFileDialog->ShowDialog();
			 
			 }
private: System::Void hkoglPanelControl1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			 glEnable(GL_COLOR_MATERIAL);
			 glClearColor( 1.0, 1.0, 1.0, 0.0);
			 glClear(GL_COLOR_BUFFER_BIT);

			 point center;
			 center[0] = 0.0 ;
			 center[1] = 0.0 ;
			 center[2] = 0.0 ;
			 camera.setupGL( xf * center, 1.0 ) ;


			 glPushMatrix();
			 glMatrixMode(GL_MODELVIEW);
			 glMultMatrixd((double *)xf);

			 if ( mesh != NULL && modelBox->Checked)
			 {
				 mesh->Render_Solid();
			 }
			 if( mesh!=NULL && wireframeBox->Checked)
			 {
				 mesh->Render_Wireframe();			 
			 }
			 if( axisBtn->Checked )
			 {
				 glPointSize(3.f);
				 glDisable(GL_LIGHTING);
				 glBegin(GL_POINTS);
				 glColor3f(1.f, 0.f, 0.f);	//X¶b: R
				 for(float i=0; i<=1.01f ; i+=0.1f)
				 {
					 glVertex3f(i,0.f,0.f);
				 }
				 glColor3f(0.f, 1.f, 0.f);	//Y¶b:G
				 for(float i=0; i<=1.01f ; i+=0.1f)
				 {
					 glVertex3f(0.f,i,0.f);
				 }
				 glColor3f(0.f, 0.f, 1.f);	//Z¶b:B
				 for(float i=0; i<=1.01f ; i+=0.1f)
				 {
					 glVertex3f(0.f,0.f,i);
				 }
				 glPointSize(1.f);
			 }
			 glEnd();

			 if(mesh)
			 {
				 mesh->RenderSpecifiedPoint();
			 }
			 
			 

			 //mesh->RenderSpecifiedPoint();
			 //std::vector<OMT::sp_p>::iterator p_itr = mesh->sp_p_list.begin();
			 //for (p_itr; p_itr != mesh->sp_p_list.end(); ++p_itr)
			 //{
			//	 glColor3f(p_itr->r, p_itr->g, p_itr->b);
			//	 glVertex3dv(p_itr->pt);
			 //}

			
			glPopMatrix();

		   }
		 

private: System::Void hkoglPanelControl1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			 if (e->Button == System::Windows::Forms::MouseButtons::Left || e->Button == System::Windows::Forms::MouseButtons::Middle)
			 {
				 point center;
				 Mouse_State = Mouse::NONE;
				 center[0] = 0.0 ;
				 center[1] = 0.0 ;
				 center[2] = 0.0 ;				    
				 camera.mouse(e->X,e->Y, Mouse_State, xf * center, 1.0, xf);
			 }
			 if(e->Button == System::Windows::Forms::MouseButtons::Right)
			 {	//retrieve the model coordinate
				GLint viewport[4];
				GLdouble modelview[16];
				GLdouble projection[16];
				GLfloat winX, winY, winZ;
				GLdouble objX, objY, objZ;
				glPushMatrix();

				glMatrixMode(GL_MODELVIEW);	glMultMatrixd((double *)xf);
				glGetDoublev( GL_MODELVIEW_MATRIX, modelview );

				glMatrixMode(GL_PROJECTION_MATRIX);	glMultMatrixd((double *)xf);
				glGetDoublev( GL_PROJECTION_MATRIX, projection );

				glMatrixMode(GL_VIEWPORT); glMultMatrixd((double *)xf);
				glGetIntegerv( GL_VIEWPORT, viewport );

				winX = (float)e->X;
				winY = (float)viewport[3] - (float)e->Y;

				glReadPixels( int(winX), int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

				gluUnProject( winX, winY, winZ, modelview, projection, viewport, &objX, &objY, &objZ);

				outputL->Text = "objX: "+objX+"\nobjY: "+objY+"\nobjZ: "+(objZ);
				glPopMatrix();
				
				if(mesh)
					mesh->add_sp_p( OMT::MyMesh::Point(objX,objY,objZ), 1.0f, 1.0f, 1.0f);
				this->Refresh();
				 
			 }
		 }
private: System::Void hkoglPanelControl1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		{
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
private: System::Void hkoglPanelControl1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		
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
private: System::Void wireframeBox_Click(System::Object^  sender, System::EventArgs^  e) {
			 hkoglPanelControl1->Refresh();
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			openMeshFileDialog->ShowDialog();
		 }
private: System::Void modelBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 hkoglPanelControl1->Refresh();
		 }
private: System::Void axisBtn_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			hkoglPanelControl1->Refresh();
		 }
};
}

