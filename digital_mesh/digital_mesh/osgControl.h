// osgControl.h : CosgControl ���ŧi

#pragma once
#include "resource.h"       // �D�n�Ÿ�

#include "digital_mesh_i.h"

class osgImplementation;
extern osgImplementation* s_osg;

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ���x�W�����T�䴩��@����� COM ����A�Ҧp Windows Mobile ���x�S���]�t���㪺 DCOM �䴩�C�Щw�q _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA �ӱj�� ATL �䴩�إ߳�@����� COM ���󪺹�@�A�H�Τ��\�ϥΨ��@����� COM �����@�C�z�� rgs �ɤ���������ҫ��w�]�w�� 'Free'�A�]���o�O�D DCOM Windows CE ���x���ߤ@�䴩��������ҫ��C"
#endif



// CosgControl

class ATL_NO_VTABLE CosgControl :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CosgControl, &CLSID_osgControl>,
	public IDispatchImpl<IosgControl, &IID_IosgControl, &LIBID_digital_meshLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CosgControl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_OSGCONTROL)


BEGIN_COM_MAP(CosgControl)
	COM_INTERFACE_ENTRY(IosgControl)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
		if (s_osg)
			delete s_osg;
		s_osg = NULL;
	}

public:
	STDMETHOD(LoadObjMesh)(BSTR filepath, LONG* status);
	STDMETHOD(SaveObjMesh)(BSTR filepath, LONG* status);
	STDMETHOD(ShowVertex)(void);
	STDMETHOD(ShowEdge)(void);
	STDMETHOD(ShowFace)(void);
	STDMETHOD(InitOSG)(LONG windowHandle);
	STDMETHOD(MouseDown)(LONG x, LONG y, CHAR button);
	STDMETHOD(MouseMove)(LONG x, LONG y);
	STDMETHOD(MouseUp)(LONG x, LONG y, CHAR button);
	STDMETHOD(HideVertex)(void);
	STDMETHOD(HideEdge)(void);
	STDMETHOD(HideFace)(void);
	STDMETHOD(SelectPoint)(LONG x, LONG y);
	STDMETHOD(SelectVertex)(LONG x, LONG y);
	STDMETHOD(SelectEdge)(LONG x, LONG y);
	STDMETHOD(SelectFace)(LONG x, LONG y);
	STDMETHOD(SelectVertexRingVertex)(LONG x, LONG y);
	STDMETHOD(SelectVertexRingEdge)(LONG x, LONG y);
	STDMETHOD(SelectVertexRingFace)(LONG x, LONG y);
	STDMETHOD(SelectEdgeRingVertex)(LONG x, LONG y);
	STDMETHOD(SelectEdgeRingEdge)(LONG x, LONG y);
	STDMETHOD(SelectEdgeRingFace)(LONG x, LONG y);
	STDMETHOD(SelectFaceRingVertex)(LONG x, LONG y);
	STDMETHOD(SelectFaceRingEdge)(LONG x, LONG y);
	STDMETHOD(SelectFaceRingFace)(LONG x, LONG y);
	STDMETHOD(ClearVertexes)(void);
	STDMETHOD(ClearEdges)(void);
	STDMETHOD(ClearFaces)(void);
	STDMETHOD(DeleteSelectEdge)(LONG x, LONG y);
	STDMETHOD(MeshSimplification)(LONG level, VARIANT_BOOL convex_check);
	STDMETHOD(SelectDontMoveFace)(LONG x, LONG y);
	STDMETHOD(SetViewer)(VARIANT_BOOL run);
	STDMETHOD(GetNumOfAllRayTraceNodes)(LONG x, LONG y, LONG* NumOfNodes);
	STDMETHOD(SetFaceTransparency)(LONG percent);
	STDMETHOD(AddLastTraceNodeByIndex)(LONG i);
	STDMETHOD(SelectSkeletonNode)(LONG x, LONG y);
	STDMETHOD(ResetCamera)(void);
	STDMETHOD(ImplicitSmooth)(void);
};

OBJECT_ENTRY_AUTO(__uuidof(osgControl), CosgControl)
