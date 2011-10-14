#pragma once
#include "Tri_Mesh.h"
#include "osgControl.h"
#include <windows.h>
#include <process.h>
#include "DotNetUtilities.h"



osgControl*	g_osgControl = NULL;
HANDLE		g_ThreadHandle = NULL;
Tri_Mesh*	g_Tri_Mesh = NULL;
osgControl::Choose_Show_Type g_ChooseType = osgControl::POINT;
osgControl::Choose_Show_Type g_Showype = osgControl::MODEL;


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

	private: System::Windows::Forms::OpenFileDialog^  openMeshFileDialog;
	private: System::Windows::Forms::SaveFileDialog^  saveMeshFileDialog;


	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  chooseToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  faceToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  clearToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  pointToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  vertexToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  faceToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  modelToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  faceToolStripMenuItem2;
	private: System::Windows::Forms::ToolStripMenuItem^  faceToolStripMenuItem3;
	private: System::Windows::Forms::ToolStripMenuItem^  wireframeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  chooseRayToolStripMenuItem;
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
			this->openMeshFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveMeshFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->chooseToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->faceToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->faceToolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->faceToolStripMenuItem3 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pointToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->vertexToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->wireframeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->faceToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->modelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->chooseRayToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->Location = System::Drawing::Point(0, 25);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(882, 546);
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
			// openMeshFileDialog
			// 
			this->openMeshFileDialog->FileName = L"openFileDialog1";
			this->openMeshFileDialog->Filter = L"obj 模型|*.obj";
			this->openMeshFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::openMeshFileDialog_FileOk);
			// 
			// saveMeshFileDialog
			// 
			this->saveMeshFileDialog->Filter = L"obj 模型|*.obj";
			this->saveMeshFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::saveMeshFileDialog_FileOk);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->fileToolStripMenuItem, 
				this->chooseToolStripMenuItem, this->clearToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(882, 25);
			this->menuStrip1->TabIndex = 3;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->openToolStripMenuItem, 
				this->saveToolStripMenuItem});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(39, 21);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(108, 22);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::openToolStripMenuItem_Click);
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(108, 22);
			this->saveToolStripMenuItem->Text = L"Save";
			this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::saveToolStripMenuItem_Click);
			// 
			// chooseToolStripMenuItem
			// 
			this->chooseToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->faceToolStripMenuItem1, 
				this->faceToolStripMenuItem2, this->faceToolStripMenuItem3});
			this->chooseToolStripMenuItem->Name = L"chooseToolStripMenuItem";
			this->chooseToolStripMenuItem->Size = System::Drawing::Size(64, 21);
			this->chooseToolStripMenuItem->Text = L"Choose";
			// 
			// faceToolStripMenuItem1
			// 
			this->faceToolStripMenuItem1->Name = L"faceToolStripMenuItem1";
			this->faceToolStripMenuItem1->Size = System::Drawing::Size(113, 22);
			this->faceToolStripMenuItem1->Text = L"Point";
			this->faceToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::faceToolStripMenuItem1_Click);
			// 
			// faceToolStripMenuItem2
			// 
			this->faceToolStripMenuItem2->Name = L"faceToolStripMenuItem2";
			this->faceToolStripMenuItem2->Size = System::Drawing::Size(113, 22);
			this->faceToolStripMenuItem2->Text = L"Vertex";
			this->faceToolStripMenuItem2->Click += gcnew System::EventHandler(this, &Form1::faceToolStripMenuItem2_Click);
			// 
			// faceToolStripMenuItem3
			// 
			this->faceToolStripMenuItem3->Name = L"faceToolStripMenuItem3";
			this->faceToolStripMenuItem3->Size = System::Drawing::Size(113, 22);
			this->faceToolStripMenuItem3->Text = L"Face";
			this->faceToolStripMenuItem3->Click += gcnew System::EventHandler(this, &Form1::faceToolStripMenuItem3_Click);
			// 
			// clearToolStripMenuItem
			// 
			this->clearToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->pointToolStripMenuItem, 
				this->vertexToolStripMenuItem, this->wireframeToolStripMenuItem, this->faceToolStripMenuItem, this->modelToolStripMenuItem, this->chooseRayToolStripMenuItem});
			this->clearToolStripMenuItem->Name = L"clearToolStripMenuItem";
			this->clearToolStripMenuItem->Size = System::Drawing::Size(51, 21);
			this->clearToolStripMenuItem->Text = L"Show";
			// 
			// pointToolStripMenuItem
			// 
			this->pointToolStripMenuItem->Name = L"pointToolStripMenuItem";
			this->pointToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->pointToolStripMenuItem->Text = L"Point";
			this->pointToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::pointToolStripMenuItem_Click);
			// 
			// vertexToolStripMenuItem
			// 
			this->vertexToolStripMenuItem->Name = L"vertexToolStripMenuItem";
			this->vertexToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->vertexToolStripMenuItem->Text = L"Vertex";
			this->vertexToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::vertexToolStripMenuItem_Click);
			// 
			// wireframeToolStripMenuItem
			// 
			this->wireframeToolStripMenuItem->Name = L"wireframeToolStripMenuItem";
			this->wireframeToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->wireframeToolStripMenuItem->Text = L"Edge";
			this->wireframeToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::edgeToolStripMenuItem_Click);
			// 
			// faceToolStripMenuItem
			// 
			this->faceToolStripMenuItem->Name = L"faceToolStripMenuItem";
			this->faceToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->faceToolStripMenuItem->Text = L"Face";
			this->faceToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::faceToolStripMenuItem_Click);
			// 
			// modelToolStripMenuItem
			// 
			this->modelToolStripMenuItem->Name = L"modelToolStripMenuItem";
			this->modelToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->modelToolStripMenuItem->Text = L"Model";
			this->modelToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::modelToolStripMenuItem_Click);
			// 
			// chooseRayToolStripMenuItem
			// 
			this->chooseRayToolStripMenuItem->Name = L"chooseRayToolStripMenuItem";
			this->chooseRayToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->chooseRayToolStripMenuItem->Text = L"Choose Ray";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(882, 571);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Leave += gcnew System::EventHandler(this, &Form1::Form1_Leave);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

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
	private: System::Void saveMeshFileDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 std::string filename;
			 MarshalString( openMeshFileDialog->FileName, filename );
			 if( g_Tri_Mesh != NULL )
			 {
				 g_Tri_Mesh->SaveFile(filename);
			 }
		 }
	private: System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 openMeshFileDialog->ShowDialog();
		 }
	private: System::Void saveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 saveMeshFileDialog->ShowDialog();
		 }

	private: System::Void faceToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void faceToolStripMenuItem2_Click(System::Object^  sender, System::EventArgs^  e) {
	 }
private: System::Void faceToolStripMenuItem3_Click(System::Object^  sender, System::EventArgs^  e) {
	 }
private: System::Void edgeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		 g_osgControl->ShowEdge();
	 }
private: System::Void pointToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		 g_osgControl->ShowVertex();
	 }
private: System::Void vertexToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	 }
private: System::Void faceToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		 g_osgControl->ShowFace();
	 }
private: System::Void modelToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		 g_osgControl->ShowModel();
	 }
};
}

