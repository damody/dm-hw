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
	private: System::Windows::Forms::RadioButton^  orFBtn;

	private: System::Windows::Forms::RadioButton^  orEBtn;


	private: System::Windows::Forms::RadioButton^  orVBtn;


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
			HKOGLPanel::HKCOGLPanelCameraSetting^  hkcoglPanelCameraSetting2 = (gcnew HKOGLPanel::HKCOGLPanelCameraSetting());
			HKOGLPanel::HKCOGLPanelPixelFormat^  hkcoglPanelPixelFormat2 = (gcnew HKOGLPanel::HKCOGLPanelPixelFormat());
			this->hkoglPanelControl1 = (gcnew HKOGLPanel::HKOGLPanelControl());
			this->openMeshFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->wireframeBox = (gcnew System::Windows::Forms::CheckBox());
			this->selVBtn = (gcnew System::Windows::Forms::RadioButton());
			this->selEBtn = (gcnew System::Windows::Forms::RadioButton());
			this->selFBtn = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->orFBtn = (gcnew System::Windows::Forms::RadioButton());
			this->orEBtn = (gcnew System::Windows::Forms::RadioButton());
			this->orVBtn = (gcnew System::Windows::Forms::RadioButton());
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
			hkcoglPanelCameraSetting2->Far = 1000;
			hkcoglPanelCameraSetting2->Fov = 45;
			hkcoglPanelCameraSetting2->Near = -1000;
			hkcoglPanelCameraSetting2->Type = HKOGLPanel::HKCOGLPanelCameraSetting::CAMERATYPE::ORTHOGRAPHIC;
			this->hkoglPanelControl1->Camera_Setting = hkcoglPanelCameraSetting2;
			this->hkoglPanelControl1->Dock = System::Windows::Forms::DockStyle::Top;
			this->hkoglPanelControl1->Location = System::Drawing::Point(0, 0);
			this->hkoglPanelControl1->Name = L"hkoglPanelControl1";
			hkcoglPanelPixelFormat2->Accumu_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat2->Alpha_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat2->Stencil_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			this->hkoglPanelControl1->Pixel_Format = hkcoglPanelPixelFormat2;
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
			this->selVBtn->Checked = true;
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
			this->groupBox2->Controls->Add(this->orFBtn);
			this->groupBox2->Controls->Add(this->orEBtn);
			this->groupBox2->Controls->Add(this->orVBtn);
			this->groupBox2->Location = System::Drawing::Point(344, 503);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(69, 91);
			this->groupBox2->TabIndex = 5;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"One Ring";
			// 
			// orFBtn
			// 
			this->orFBtn->AutoSize = true;
			this->orFBtn->Location = System::Drawing::Point(6, 65);
			this->orFBtn->Name = L"orFBtn";
			this->orFBtn->Size = System::Drawing::Size(44, 16);
			this->orFBtn->TabIndex = 2;
			this->orFBtn->Text = L"Face";
			this->orFBtn->UseVisualStyleBackColor = true;
			this->orFBtn->CheckedChanged += gcnew System::EventHandler(this, &Form1::orFBtn_CheckedChanged);
			// 
			// orEBtn
			// 
			this->orEBtn->AutoSize = true;
			this->orEBtn->Location = System::Drawing::Point(6, 43);
			this->orEBtn->Name = L"orEBtn";
			this->orEBtn->Size = System::Drawing::Size(47, 16);
			this->orEBtn->TabIndex = 1;
			this->orEBtn->Text = L"Edge";
			this->orEBtn->UseVisualStyleBackColor = true;
			this->orEBtn->CheckedChanged += gcnew System::EventHandler(this, &Form1::orEBtn_CheckedChanged);
			// 
			// orVBtn
			// 
			this->orVBtn->AutoSize = true;
			this->orVBtn->Checked = true;
			this->orVBtn->Location = System::Drawing::Point(6, 21);
			this->orVBtn->Name = L"orVBtn";
			this->orVBtn->Size = System::Drawing::Size(54, 16);
			this->orVBtn->TabIndex = 0;
			this->orVBtn->TabStop = true;
			this->orVBtn->Text = L"Vertex";
			this->orVBtn->UseVisualStyleBackColor = true;
			this->orVBtn->CheckedChanged += gcnew System::EventHandler(this, &Form1::orVBtn_CheckedChanged);
			// 
			// outputL
			// 
			this->outputL->AutoSize = true;
			this->outputL->Location = System::Drawing::Point(419, 524);
			this->outputL->Name = L"outputL";
			this->outputL->Size = System::Drawing::Size(0, 12);
			this->outputL->TabIndex = 6;
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
			this->pathLable->Size = System::Drawing::Size(0, 12);
			this->pathLable->TabIndex = 11;
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
				 glColor3f(1.f, 0.f, 0.f);	//X軸: R
				 for(float i=0; i<=1.01f ; i+=0.1f)
				 {
					 glVertex3f(i,0.f,0.f);
				 }
				 glColor3f(0.f, 1.f, 0.f);	//Y軸:G
				 for(float i=0; i<=1.01f ; i+=0.1f)
				 {
					 glVertex3f(0.f,i,0.f);
				 }
				 glColor3f(0.f, 0.f, 1.f);	//Z軸:B
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
				 mesh->RenderSpecifiedVertex();
				 mesh->RenderSpecifiedFace();
				 mesh->RenderSpecifiedEdge();
			}
			 
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
		if(mesh)
		{
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
			
			if(winZ>=0.99999f)
			{
				std::cerr << "Click on background (z= " << winZ << ")" << std::endl;
				glPopMatrix();
				return;
			}
			gluUnProject( winX, winY, winZ, modelview, projection, viewport, &objX, &objY, &objZ);

			outputL->Text = "ObjectX: "+objX+"\nObjectY: "+objY+"\nObjectZ: "+(objZ);
			glPopMatrix();
			
			
			mesh->clear_sp_p();
			mesh->clear_sp_v();
			mesh->clear_sp_f();
			mesh->clear_sp_e();
			//加入目前的滑鼠點
			mesh->add_sp_p( OMT::MyMesh::Point(objX,objY,objZ), 1.0f, 0.0f, 1.0f);

			if(selVBtn->Checked)
			{	//Select Vertex
				float mDist=99999.f;
				float dist;
				OMT::VIter mV;
				OMT::VHandle mvH;
				for (OMT::VIter v_it = mesh->vertices_begin() ; v_it != mesh->vertices_end() ; ++v_it)
				{	//找到目前的vertex
					dist =	(mesh->point( v_it.handle() )[0] - objX) * (mesh->point( v_it.handle() )[0] - objX) +
							(mesh->point( v_it.handle() )[1] - objY) * (mesh->point( v_it.handle() )[1] - objY) +
							(mesh->point( v_it.handle() )[2] - objZ) * (mesh->point( v_it.handle() )[2] - objZ);
					//glVertex3dv(OMT::Point(v_it));
					if( dist < mDist )
					{
						mvH = v_it.handle();
						mDist = dist;
					}
					//std::cerr << mesh->point(v_it.handle())[0] << " "<< mesh->point(v_it.handle())[1] <<" "<< mesh->point(v_it.handle())[2] << " " << dist<<std::endl; 
				}
				//std::cerr <<"N: "<< mesh->point(mvH)[0] << " "<< mesh->point(mvH)[1] <<" "<< mesh->point(mvH)[2]<< " dist: "<< mDist <<std::endl; 
				mesh->add_sp_v(mvH, 1.f,0.f,0.f);

				if(orVBtn->Checked)
				{	// One Ring Vertex
					for(OMT::VVIter vv_it = mesh->vv_iter(mvH); vv_it ; ++vv_it )
					{
						mesh->add_sp_v( vv_it.handle(), 0.f,1.0f,0.f);
					}
				}
				else if(orFBtn->Checked)
				{	// One Ring Face
					for(OMT::VFIter vf_it = mesh->vf_iter(mvH); vf_it ; ++vf_it )
					{
						mesh->add_sp_f( vf_it.handle(), 0.f,1.0f,0.f);
					}
				}
				else
				{	// One Ring Edge
					for(OMT::VEIter ve_itr = mesh->ve_iter(mvH) ; ve_itr; ++ve_itr)
					{
						OMT::HEHandle _hedge = mesh->halfedge_handle(ve_itr.handle(),1);
						mesh->add_sp_e( (mesh->from_vertex_handle(_hedge)), 
										(mesh->to_vertex_handle(_hedge)), 
										0.f, 1.f, 1.f );
					}
				}

			}
			else if(selEBtn->Checked)
			{	//select Edge, 但先找面，再從面的三個邊中找邊
				float mDist=99999.f;
				float dist;
				OMT::FIter mF;
				OMT::FHandle mfH;
				OMT::Point mEdgeN[3];	//選到的面的邊法線向量
				double mParaD[3];		//選到的面的平面方程式參數d
				for (OMT::FIter f_it = mesh->faces_begin() ; f_it != mesh->faces_end() ; ++f_it)
				{	//找到目前的face
					OMT::Point com, fv[3];	//重心位置, face vertex
					com[0]=com[1]=com[2]=0.f;

					//float curPos[3]; curPos[0]=0.f;curPos[1]=0.f;curPos[2]=0.f;
					int i = 0;
					for(OMT::FVIter fv_it = mesh->fv_iter(f_it.handle()); fv_it ; ++fv_it, ++i) 
					{
						com += mesh->point(fv_it.handle());
						memcpy(	fv[i], mesh->point( fv_it.handle() ), sizeof(OMT::Point) ) ;
					}
					com /= 3.f;

					//算重心位置
					dist =	( com[0] - objX) * ( com[0] - objX ) +
						( com[1] - objY) * ( com[1] - objY ) +
						( com[2] - objZ) * ( com[2] - objZ );

					OMT::Point v[2], normalV, edgeN[3];//兩條邊向量,邊法向量,通過邊且垂直平面的平面法向量
					v[0] = fv[2] - fv[0];
					v[1] = fv[1] - fv[0];
					normalV = v[0] CROSS v[1];
					edgeN[0] = normalV CROSS (fv[1]-fv[0]);	//算出通過三角形三個邊且垂直於三角形的平面的法線向量
					edgeN[1] = normalV CROSS (fv[2]-fv[1]);
					edgeN[2] = normalV CROSS (fv[2]-fv[0]);
					double paraD[3];//通過三個邊的平面的d (ax+by+cz-d=0)
					paraD[0] = edgeN[0][0]*fv[0][0] + edgeN[0][1]*fv[0][1] + edgeN[0][2]*fv[0][2];
					paraD[1] = edgeN[1][0]*fv[1][0] + edgeN[1][1]*fv[1][1] + edgeN[1][2]*fv[1][2];
					paraD[2] = edgeN[2][0]*fv[2][0] + edgeN[2][1]*fv[2][1] + edgeN[2][2]*fv[2][2];
					if( dist < mDist )
					{	//若找到的三角形重心更靠近
						bool inside = true;
						double s[2];	//紀錄點帶入邊的平面方程式的結果
						for(int j=0 ; j<3 ; j++)
						{	//分別將滑鼠點和重心帶入平面方程式
							s[0] = edgeN[j][0]*	objX	+ edgeN[j][1]*objY	+	edgeN[j][2]*objZ -	paraD[j];
							s[1] = edgeN[j][0]*com[0]	+ edgeN[j][1]*com[1] +	edgeN[j][2]*com[2] - paraD[j];
							if( s[0]*s[1]<0.f )	//異號，表示滑鼠點和重心不在平面的同一邊
							{					//表示滑鼠點不在該三角形內
								inside = false;
								break;
							}
						}
						if(inside==false)
						{	//如果不在三角形內則繼續找下一個三角形
							continue;
						}
						mfH = f_it.handle();
						mDist = dist;
						memcpy(mEdgeN,edgeN, 3*sizeof(OMT::Point));
						memcpy(mParaD,paraD, 3*sizeof(double));

					}
					//std::cerr << mesh->point(v_it.handle())[0] << " "<< mesh->point(v_it.handle())[1] <<" "<< mesh->point(v_it.handle())[2] << " " << dist<<std::endl; 
				}
				//找到面了，接下來在面的三個邊中找最近的線, 從one ring edge開始找
				float curEDist, mEDist=99999.f;
				int theEdgeNum=0;
				for(int j=0 ; j<3 ; j++)	//找出和滑鼠最接近的邊向量
				{	//算出滑鼠點和邊的距離
					curEDist = abs(mEdgeN[j][0]*	objX	+ mEdgeN[j][1]*objY	+	mEdgeN[j][2]*objZ -	mParaD[j]) / sqrtf( mEdgeN[j][0]*mEdgeN[j][0] + mEdgeN[j][1]*mEdgeN[j][1] + mEdgeN[j][2]*mEdgeN[j][2]);
					
					if( curEDist < mEDist )	
					{					
						mEDist = curEDist;
						theEdgeNum = j;
					}
				}
				OMT::FEIter e_it = mesh->fe_iter(mfH);
				for(int q=0; q<=theEdgeNum; ++q, ++e_it);	//巡到目前的Edge iterator
				OMT::HEHandle _hedge = mesh->halfedge_handle(e_it.handle(),1);
				mesh->add_sp_e( (mesh->from_vertex_handle(_hedge)), 
					(mesh->to_vertex_handle(_hedge)), 
					1.f, 0.f, 0.f );
				if(orVBtn->Checked)
				{	// One Ring Vertex
					for(OMT::VVIter vv_it = mesh->vv_iter( (mesh->from_vertex_handle(_hedge) )); vv_it ; ++vv_it ) 
					{
						mesh->add_sp_v( vv_it.handle(), 0.f,1.0f,0.f);
					}
					for(OMT::VVIter vv_it = mesh->vv_iter( (mesh->to_vertex_handle(_hedge) )); vv_it ; ++vv_it ) 
					{
						mesh->add_sp_v( vv_it.handle(), 0.f,1.0f,0.f);
					}
				}
				else if(orFBtn->Checked)
				{	// One Ring Face
					for(OMT::VFIter vf_it = mesh->vf_iter( (mesh->from_vertex_handle(_hedge) ) ); vf_it ; ++vf_it )
					{
						mesh->add_sp_f( vf_it.handle(), 0.f,1.0f,0.f);
					}
					for(OMT::VFIter vf_it = mesh->vf_iter( (mesh->to_vertex_handle(_hedge) ) ); vf_it ; ++vf_it )
					{
						mesh->add_sp_f( vf_it.handle(), 0.f,1.0f,0.f);
					}
				}
				else
				{	// One Ring Edge
					for(OMT::VEIter ve_itr = mesh->ve_iter( (mesh->from_vertex_handle(_hedge) ))  ; ve_itr; ++ve_itr)
					{
						OMT::HEHandle _hedge = mesh->halfedge_handle(ve_itr.handle(),1);
						mesh->add_sp_e( (mesh->from_vertex_handle(_hedge)), 
							(mesh->to_vertex_handle(_hedge)), 
							0.f, 1.f, 1.f );
					}
					for(OMT::VEIter ve_itr = mesh->ve_iter( (mesh->to_vertex_handle(_hedge) ))  ; ve_itr; ++ve_itr)
					{
						OMT::HEHandle _hedge = mesh->halfedge_handle(ve_itr.handle(),1);
						mesh->add_sp_e( (mesh->from_vertex_handle(_hedge)), 
							(mesh->to_vertex_handle(_hedge)), 
							0.f, 1.f, 1.f );
					}
				}

			}
			else
			{	//select face
				float mDist=99999.f;
				float dist;
				OMT::FIter mF;
				OMT::FHandle mfH;
				for (OMT::FIter f_it = mesh->faces_begin() ; f_it != mesh->faces_end() ; ++f_it)
				{	//找到目前的face
					OMT::Point com, fv[3];	//重心位置, face vertex
					com[0]=com[1]=com[2]=0.f;
					
					//float curPos[3]; curPos[0]=0.f;curPos[1]=0.f;curPos[2]=0.f;
					int i = 0;
					for(OMT::FVIter fv_it = mesh->fv_iter(f_it.handle()); fv_it ; ++fv_it, ++i) 
					{
						com += mesh->point(fv_it.handle());
						memcpy(	fv[i], mesh->point( fv_it.handle() ), sizeof(OMT::Point) ) ;
					}
					com /= 3.f;

					//算重心位置
					dist =	( com[0] - objX) * ( com[0] - objX ) +
							( com[1] - objY) * ( com[1] - objY ) +
							( com[2] - objZ) * ( com[2] - objZ );
					
					OMT::Point v[2], normalV, edgeN[3];//兩條邊向量,邊法向量,通過邊且垂直平面的平面法向量
					v[0] = fv[2] - fv[0];
					v[1] = fv[1] - fv[0];
					normalV = v[0] CROSS v[1];
					edgeN[0] = normalV CROSS (fv[1]-fv[0]);	//算出通過三角形三個邊且垂直於三角形的平面的法線向量
					edgeN[1] = normalV CROSS (fv[2]-fv[1]);
					edgeN[2] = normalV CROSS (fv[2]-fv[0]);
					double paraD[3];//通過三個邊的平面的d (ax+by+cz-d=0)
					paraD[0] = edgeN[0][0]*fv[0][0] + edgeN[0][1]*fv[0][1] + edgeN[0][2]*fv[0][2];
					paraD[1] = edgeN[1][0]*fv[1][0] + edgeN[1][1]*fv[1][1] + edgeN[1][2]*fv[1][2];
					paraD[2] = edgeN[2][0]*fv[2][0] + edgeN[2][1]*fv[2][1] + edgeN[2][2]*fv[2][2];
					if( dist < mDist )
					{	//若找到的三角形重心更靠近
						bool inside = true;
						double s[2];	//紀錄點帶入邊的平面方程式的結果
						for(int j=0 ; j<3 ; j++)
						{	//分別將滑鼠點和重心帶入平面方程式
							s[0] = edgeN[j][0]*	objX	+ edgeN[j][1]*objY	+	edgeN[j][2]*objZ -	paraD[j];
							s[1] = edgeN[j][0]*com[0]	+ edgeN[j][1]*com[1] +	edgeN[j][2]*com[2] - paraD[j];
							if( s[0]*s[1]<0.f )	//異號，表示滑鼠點和重心不在平面的同一邊
							{					//表示滑鼠點不在該三角形內
								inside = false;
								break;
							}
						}
						if(inside==false)
						{	//如果不在三角形內則繼續找下一個三角形
							continue;
						}
						mfH = f_it.handle();
						mDist = dist;

					}
					//std::cerr << mesh->point(v_it.handle())[0] << " "<< mesh->point(v_it.handle())[1] <<" "<< mesh->point(v_it.handle())[2] << " " << dist<<std::endl; 
				}
				//std::cerr <<"N: "<< mesh->point(mvH)[0] << " "<< mesh->point(mvH)[1] <<" "<< mesh->point(mvH)[2]<< " dist: "<< mDist <<std::endl; 
				mesh->add_sp_f(mfH, 1.f,0.f,0.f);	//加入要畫的面
				if(orVBtn->Checked)
				{	// One Ring Vertex
					for(OMT::FVIter fv_it = mesh->fv_iter(mfH); fv_it ; ++fv_it )
					{
						mesh->add_sp_v( fv_it.handle(), 0.f,1.0f,0.f);
					}
				}
				else if(orFBtn->Checked)
				{	// One Ring Face
					for(OMT::FFIter ff_it = mesh->ff_iter(mfH); ff_it ; ++ff_it )
					{
						mesh->add_sp_f( ff_it.handle(), 0.f,1.0f,0.f);
					}
				}
				else
				{	//One Ring Edge
					for(OMT::FEIter fe_itr = mesh->fe_iter(mfH) ; fe_itr; ++fe_itr)
					{
						OMT::HEHandle _hedge = mesh->halfedge_handle(fe_itr.handle(),1);
						mesh->add_sp_e( (mesh->from_vertex_handle(_hedge)), 
										(mesh->to_vertex_handle(_hedge)), 
										0.f, 1.f, 1.f );
					}
				}

				
			}

			this->Refresh();
		} 
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
private: System::Void orVBtn_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			hkoglPanelControl1->Refresh();
		 }
private: System::Void orEBtn_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			hkoglPanelControl1->Refresh();
		 }
private: System::Void orFBtn_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			if(mesh)
			{
				mesh->clear_sp_f();
				mesh->clear_sp_v();
				mesh->clear_sp_p();
				mesh->clear_sp_e();
				hkoglPanelControl1->Refresh();
			}
			
		 }
};
}

