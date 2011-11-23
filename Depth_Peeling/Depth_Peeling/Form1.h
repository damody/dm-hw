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
	private: System::Windows::Forms::Label^  testL;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			HKOGLPanel::HKCOGLPanelCameraSetting^  hkcoglPanelCameraSetting1 = (gcnew HKOGLPanel::HKCOGLPanelCameraSetting());
			HKOGLPanel::HKCOGLPanelPixelFormat^  hkcoglPanelPixelFormat1 = (gcnew HKOGLPanel::HKCOGLPanelPixelFormat());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->DepthPeel_button = (gcnew System::Windows::Forms::Button());
			this->OpenMesh_button = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->hkoglPanelControl1 = (gcnew HKOGLPanel::HKOGLPanelControl());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->testL = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->testL);
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
			this->hkoglPanelControl1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::hkoglPanelControl1_MouseDown);
			this->hkoglPanelControl1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::hkoglPanelControl1_MouseMove);
			this->hkoglPanelControl1->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::hkoglPanelControl1_MouseWheel);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::openFileDialog1_FileOk);
			// 
			// testL
			// 
			this->testL->AutoSize = true;
			this->testL->Location = System::Drawing::Point(18, 186);
			this->testL->Name = L"testL";
			this->testL->Size = System::Drawing::Size(33, 12);
			this->testL->TabIndex = 2;
			this->testL->Text = L"label1";
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
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
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
				 mesh->Render_Solid();

			 glPopMatrix();
		 }
private: System::Void hkoglPanelControl1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
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
				 
				 testL->Text = "mouseX= " + (e->X).ToString() + "\nmouseY= " + (e->Y).ToString();
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
			   if ( peeling_state )
			   {
				   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				   glEnable(GL_BLEND);
				   glDisable( GL_DEPTH_TEST ) ;
				   peeling_state = false ;
				   if(  dp_com->Scene_Init() )
				   {
					   dp_com->Set_BufferObj(hkoglPanelControl1->Width, hkoglPanelControl1->Height);
					    //��for�j��N�C�@�hDepth Layer ��X��
					    
					   //  DP_COM::Peeling_layer

					   //Set_ValidRegion();
					 
					   std::cout<<"Peeling Success.....";
				   }
				   else
				   {
				       std::cout<<"Peeling Fail.............WTX..............";
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
};
}
