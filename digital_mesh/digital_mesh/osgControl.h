// osgControl.h : CosgControl 的宣告

#pragma once
#include "resource.h"       // 主要符號

#include "digital_mesh_i.h"

class osgImplementation;
extern osgImplementation* s_osg;

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台上未正確支援單一執行緒 COM 物件，例如 Windows Mobile 平台沒有包含完整的 DCOM 支援。請定義 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 來強制 ATL 支援建立單一執行緒 COM 物件的實作，以及允許使用其單一執行緒 COM 物件實作。您的 rgs 檔中的執行緒模型已設定為 'Free'，因為這是非 DCOM Windows CE 平台中唯一支援的執行緒模型。"
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
