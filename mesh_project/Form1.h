#pragma once
#include "Tri_Mesh.h"
#include "osgControl.h"
#include <windows.h>
#include <process.h>
#include "DotNetUtilities.h"

osgControl* g_osgControl = NULL;
HANDLE g_ThreadHandle = NULL;
Tri_Mesh* g_Tri_Mesh = NULL;

namespace mesh_project {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Form1 的摘要
	///
	/// 警告: 如果您變更這個類別的名稱，就必須變更與這個類別所依據之所有 .resx 檔案關聯的
	///          Managed 資源編譯器工具的 'Resource File Name' 屬性。
	///          否則，這些設計工具
	///          將無法與這個表單關聯的當地語系化資源
	///          正確互動。
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: 在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::OpenFileDialog^  openMeshFileDialog;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	protected: 

	protected: 

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改這個方法的內容。
		///
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->openMeshFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(520, 465);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox1_MouseWheel);
			this->pictureBox1->Layout += gcnew System::Windows::Forms::LayoutEventHandler(this, &Form1::pictureBox1_Layout);
			this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox1_MouseMove);
			this->pictureBox1->LoadCompleted += gcnew System::ComponentModel::AsyncCompletedEventHandler(this, &Form1::pictureBox1_LoadCompleted);
			this->pictureBox1->Click += gcnew System::EventHandler(this, &Form1::pictureBox1_Click);
			this->pictureBox1->Resize += gcnew System::EventHandler(this, &Form1::pictureBox1_Resize);
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox1_MouseDown);
			this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::pictureBox1_Paint);
			this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox1_MouseUp);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 430);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Open obj";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::Open_obj_Click);
			// 
			// openMeshFileDialog
			// 
			this->openMeshFileDialog->FileName = L"openFileDialog1";
			this->openMeshFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::openMeshFileDialog_FileOk);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(520, 465);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Leave += gcnew System::EventHandler(this, &Form1::Form1_Leave);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void pictureBox1_Resize(System::Object^  sender, System::EventArgs^  e) {
		 }
	private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
			
		 }
	private: System::Void pictureBox1_LoadCompleted(System::Object^  sender, System::ComponentModel::AsyncCompletedEventArgs^  e) {

		 }
	private: System::Void Form1_Leave(System::Object^  sender, System::EventArgs^  e) {
			 WaitForSingleObject(g_ThreadHandle, 500);
		 }
	private: System::Void pictureBox1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		 }
	private: System::Void Open_obj_Click(System::Object^  sender, System::EventArgs^  e) {
			 openMeshFileDialog->ShowDialog();
		 }
	private: System::Void pictureBox1_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			 g_osgControl->getViewer()->getEventQueue()->mouseScroll2D(0, e->Delta);
			 if (e->Delta<0)
			 {
				 g_osgControl->getViewer()->getEventQueue()->mouseScroll(osgGA::GUIEventAdapter::SCROLL_DOWN);
			 }
			 else
			 {
				 g_osgControl->getViewer()->getEventQueue()->mouseScroll(osgGA::GUIEventAdapter::SCROLL_UP);
			 }
		 }
	private: System::Void pictureBox1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 switch (e->Button)
			 {
			 case System::Windows::Forms::MouseButtons::Left:
				 g_osgControl->getViewer()->getEventQueue()->mouseButtonPress(e->X, pictureBox1->Height - e->Y, 0);
				 break;
			 case System::Windows::Forms::MouseButtons::Middle:
				 g_osgControl->getViewer()->getEventQueue()->mouseButtonPress(e->X, pictureBox1->Height - e->Y, 1);
				 break;
			 case System::Windows::Forms::MouseButtons::Right:
				 g_osgControl->getViewer()->getEventQueue()->mouseButtonPress(e->X, pictureBox1->Height - e->Y, 2);
				 break;
			 }
			 osg::Vec3f p, q;
			 g_osgControl->GetRay(pictureBox1->Width - e->X, pictureBox1->Height - e->Y, p, q);
			 g_osgControl->AddLine(p, q);
		 }
	private: System::Void pictureBox1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 g_osgControl->getViewer()->getEventQueue()->mouseMotion(e->X, pictureBox1->Height - e->Y);
		 }
	private: System::Void pictureBox1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 switch (e->Button)
			 {
			 case System::Windows::Forms::MouseButtons::Left:
				 g_osgControl->getViewer()->getEventQueue()->mouseButtonRelease(e->X, pictureBox1->Height - e->Y, 0);
				 break;
			 case System::Windows::Forms::MouseButtons::Middle:
				 g_osgControl->getViewer()->getEventQueue()->mouseButtonRelease(e->X, pictureBox1->Height - e->Y, 1);
				 break;
			 case System::Windows::Forms::MouseButtons::Right:
				 g_osgControl->getViewer()->getEventQueue()->mouseButtonRelease(e->X, pictureBox1->Height - e->Y, 2);
				 break;
			 }
		 }
	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if (g_osgControl)
			 {
				 g_osgControl->getViewer()->getEventQueue()->keyPress(e->KeyValue);
			 }

		 }
	private: System::Void pictureBox1_Layout(System::Object^  sender, System::Windows::Forms::LayoutEventArgs^  e) {

		 }
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			 if (!g_osgControl)
			 {
				 g_osgControl = new osgControl((HWND)(pictureBox1->Handle.ToInt32()));
				 g_osgControl->InitOSG("");
				 g_ThreadHandle = (HANDLE)_beginthread(&osgControl::Render, 0, g_osgControl);
			 }
		 }
	private: System::Void openMeshFileDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 std::string filename;
			 MarshalString( openMeshFileDialog->FileName, filename );

			 if( g_Tri_Mesh != NULL )
				 delete g_Tri_Mesh;

			 g_Tri_Mesh = new Tri_Mesh;

			 if(g_Tri_Mesh->ReadFile(filename))
			 {
				 g_osgControl->SetModel(g_Tri_Mesh);
			 }
		 }

	};
}

