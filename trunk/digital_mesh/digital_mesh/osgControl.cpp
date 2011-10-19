// osgControl.cpp : CosgControl 的實作

#include "stdafx.h"
#include "osgImplementation.h"
#include "osgControl.h"
#include "ConvStr.h"
#include <string>

// CosgControl
osgImplementation* s_osg = NULL;
Tri_Mesh*	s_Tri_Mesh = NULL;
HANDLE		s_ThreadHandle;

STDMETHODIMP CosgControl::LoadObjMesh(BSTR* filepath, LONG* status)
{
	std::string path = ConvStr::GetStr(*filepath);
	if(s_Tri_Mesh->ReadFile(path))
	{
		s_osg->SetModel(s_Tri_Mesh);
	}
	return S_OK;
}

STDMETHODIMP CosgControl::ShowVertex(void)
{
	s_osg->ShowVertex();
	return S_OK;
}

STDMETHODIMP CosgControl::ShowEdge(void)
{
	s_osg->ShowEdge();
	return S_OK;
}

STDMETHODIMP CosgControl::ShowFace(void)
{
	s_osg->ShowFace();
	return S_OK;
}

STDMETHODIMP CosgControl::InitOSG(LONG windowHandle)
{
	s_osg = new osgImplementation((HWND)windowHandle);
	s_osg->InitOSG();
	s_ThreadHandle = (HANDLE)_beginthread(&osgImplementation::Render, 0, s_osg);
	s_Tri_Mesh = new Tri_Mesh;
	return S_OK;
}

STDMETHODIMP CosgControl::MouseDown(LONG x, LONG y, CHAR button)
{
	s_osg->getViewer()->getEventQueue()->mouseButtonPress(x, y, button);
	return S_OK;
}

STDMETHODIMP CosgControl::MouseMove(LONG x, LONG y)
{
	s_osg->getViewer()->getEventQueue()->mouseMotion(x, y);
	return S_OK;
}

STDMETHODIMP CosgControl::MouseUp(LONG x, LONG y, CHAR button)
{
	s_osg->getViewer()->getEventQueue()->mouseButtonRelease(x, y, button);
	return S_OK;
}

STDMETHODIMP CosgControl::HideVertex(void)
{
	s_osg->HideVertex();
	return S_OK;
}

STDMETHODIMP CosgControl::HideEdge(void)
{
	s_osg->HideEdge();
	return S_OK;
}

STDMETHODIMP CosgControl::HideFace(void)
{
	s_osg->HideFace();
	return S_OK;
}

STDMETHODIMP CosgControl::SelectPoint(LONG x, LONG y)
{
	osg::Vec3f ori, dir, p;
	s_osg->GetRay(x, y, ori, dir);
	if (s_osg->SelectPoint(ori, dir, p))
		s_osg->AddPoint(p);
	return S_OK;
}

STDMETHODIMP CosgControl::SelectVertex(LONG x, LONG y)
{
	osg::Vec3f ori, dir, p;
	s_osg->GetRay(x, y, ori, dir);
	if (s_osg->SelectVertex(ori, dir, p))
		s_osg->AddVertex(p);
	return S_OK;
}

STDMETHODIMP CosgControl::SelectEdge(LONG x, LONG y)
{
	osg::Vec3f ori, dir, o1, o2;
	s_osg->GetRay(x, y, ori, dir);
	if (s_osg->SelectEdge(ori, dir, o1, o2))
		s_osg->AddLine(o1, o2);
	return S_OK;
}

STDMETHODIMP CosgControl::SetSelectColor(SHORT r, SHORT g, SHORT b)
{
	// TODO: 在這裡加入您的實作程式碼

	return S_OK;
}

STDMETHODIMP CosgControl::SelectFace(LONG x, LONG y)
{
	osg::Vec3f ori, dir, o1, o2, o3;
	s_osg->GetRay(x, y, ori, dir);
	if (s_osg->SelectFace(ori, dir, o1, o2, o3))
		s_osg->AddFace(o1, o2, o3);
	return S_OK;
}

STDMETHODIMP CosgControl::SelectVertexRingVertex(LONG x, LONG y)
{
	osg::Vec3f ori, dir, o1, o2, o3;
	s_osg->GetRay(x, y, ori, dir);
	sPoints out;
	if (s_osg->SelectVertexRingVertex(ori, dir, out))
		s_osg->AddVertex(out);
	return S_OK;
}

STDMETHODIMP CosgControl::SelectVertexRingEdge(LONG x, LONG y)
{
	osg::Vec3f ori, dir, o1, o2, o3;
	s_osg->GetRay(x, y, ori, dir);
	sLines out;
	if (s_osg->SelectVertexRingEdge(ori, dir, out))
		s_osg->AddLine(out);
	return S_OK;
}

STDMETHODIMP CosgControl::SelectVertexRingFace(LONG x, LONG y)
{
	osg::Vec3f ori, dir, o1, o2, o3;
	s_osg->GetRay(x, y, ori, dir);
	sFaces out;
	if (s_osg->SelectVertexRingFace(ori, dir, out))
		s_osg->AddFace(out);
	return S_OK;
}

STDMETHODIMP CosgControl::SelectEdgeRingVertex(LONG x, LONG y)
{
	osg::Vec3f ori, dir, o1, o2, o3;
	s_osg->GetRay(x, y, ori, dir);
	sPoints out;
	if (s_osg->SelectEdgeRingVertex(ori, dir, out))
		s_osg->AddVertex(out);
	return S_OK;
}

STDMETHODIMP CosgControl::SelectEdgeRingEdge(LONG x, LONG y)
{
	osg::Vec3f ori, dir, o1, o2, o3;
	s_osg->GetRay(x, y, ori, dir);
	sLines out;
	if (s_osg->SelectEdgeRingEdge(ori, dir, out))
		s_osg->AddLine(out);
	return S_OK;
}

STDMETHODIMP CosgControl::SelectEdgeRingFace(LONG x, LONG y)
{
	osg::Vec3f ori, dir, o1, o2, o3;
	s_osg->GetRay(x, y, ori, dir);
	sFaces out;
	if (s_osg->SelectEdgeRingFace(ori, dir, out))
		s_osg->AddFace(out);
	return S_OK;
}

STDMETHODIMP CosgControl::SelectFaceRingVertex(LONG x, LONG y)
{
	osg::Vec3f ori, dir, o1, o2, o3;
	s_osg->GetRay(x, y, ori, dir);
	sPoints out;
	if (s_osg->SelectFaceRingVertex(ori, dir, out))
		s_osg->AddVertex(out);
	return S_OK;
}

STDMETHODIMP CosgControl::SelectFaceRingEdge(LONG x, LONG y)
{
	osg::Vec3f ori, dir, o1, o2, o3;
	s_osg->GetRay(x, y, ori, dir);
	sLines out;
	if (s_osg->SelectFaceRingEdge(ori, dir, out))
		s_osg->AddLine(out);
	return S_OK;
}

STDMETHODIMP CosgControl::SelectFaceRingFace(LONG x, LONG y)
{
	osg::Vec3f ori, dir, o1, o2, o3;
	s_osg->GetRay(x, y, ori, dir);
	sFaces out;
	if (s_osg->SelectFaceRingFace(ori, dir, out))
		s_osg->AddFace(out);
	return S_OK;
}

STDMETHODIMP CosgControl::ClearPoints(void)
{
	s_osg->ClearPoints();
	return S_OK;
}

STDMETHODIMP CosgControl::ClearVertexes(void)
{
	s_osg->ClearVertexes();
	return S_OK;
}

STDMETHODIMP CosgControl::ClearEdges(void)
{
	s_osg->ClearEdges();
	return S_OK;
}

STDMETHODIMP CosgControl::ClearFaces(void)
{
	s_osg->ClearFaces();
	return S_OK;
}
