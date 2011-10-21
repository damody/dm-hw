

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Fri Oct 21 12:36:13 2011
 */
/* Compiler settings for .\digital_mesh.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __digital_mesh_i_h__
#define __digital_mesh_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IosgControl_FWD_DEFINED__
#define __IosgControl_FWD_DEFINED__
typedef interface IosgControl IosgControl;
#endif 	/* __IosgControl_FWD_DEFINED__ */


#ifndef __osgControl_FWD_DEFINED__
#define __osgControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class osgControl osgControl;
#else
typedef struct osgControl osgControl;
#endif /* __cplusplus */

#endif 	/* __osgControl_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IosgControl_INTERFACE_DEFINED__
#define __IosgControl_INTERFACE_DEFINED__

/* interface IosgControl */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IosgControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DD78AA03-FFA2-49C0-84ED-2FCA530FA736")
    IosgControl : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadObjMesh( 
            /* [in] */ BSTR *filepath,
            /* [retval][out] */ LONG *status) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowVertex( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowEdge( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowFace( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitOSG( 
            /* [in] */ LONG windowHandle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MouseDown( 
            /* [in] */ LONG x,
            /* [in] */ LONG y,
            /* [in] */ CHAR button) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MouseMove( 
            /* [in] */ LONG x,
            /* [in] */ LONG y) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MouseUp( 
            /* [in] */ LONG x,
            /* [in] */ LONG y,
            /* [in] */ CHAR button) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HideVertex( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HideEdge( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HideFace( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectPoint( 
            /* [in] */ LONG x,
            /* [in] */ LONG y) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectVertex( 
            /* [in] */ LONG x,
            /* [in] */ LONG y) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectEdge( 
            /* [in] */ LONG x,
            /* [in] */ LONG y) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectFace( 
            /* [in] */ LONG x,
            /* [in] */ LONG y) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSelectColor( 
            /* [in] */ SHORT r,
            /* [in] */ SHORT g,
            /* [in] */ SHORT b) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectVertexRingVertex( 
            /* [in] */ LONG x,
            /* [in] */ LONG y) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectVertexRingEdge( 
            /* [in] */ LONG x,
            /* [in] */ LONG y) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectVertexRingFace( 
            /* [in] */ LONG x,
            /* [in] */ LONG y) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectEdgeRingVertex( 
            /* [in] */ LONG x,
            /* [in] */ LONG y) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectEdgeRingEdge( 
            /* [in] */ LONG x,
            /* [in] */ LONG y) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectEdgeRingFace( 
            /* [in] */ LONG x,
            /* [in] */ LONG y) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectFaceRingVertex( 
            /* [in] */ LONG x,
            /* [in] */ LONG y) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectFaceRingEdge( 
            /* [in] */ LONG x,
            /* [in] */ LONG y) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectFaceRingFace( 
            /* [in] */ LONG x,
            /* [in] */ LONG y) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClearPoints( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClearVertexes( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClearEdges( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClearFaces( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IosgControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IosgControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IosgControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IosgControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IosgControl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IosgControl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IosgControl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IosgControl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadObjMesh )( 
            IosgControl * This,
            /* [in] */ BSTR *filepath,
            /* [retval][out] */ LONG *status);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ShowVertex )( 
            IosgControl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ShowEdge )( 
            IosgControl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ShowFace )( 
            IosgControl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InitOSG )( 
            IosgControl * This,
            /* [in] */ LONG windowHandle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MouseDown )( 
            IosgControl * This,
            /* [in] */ LONG x,
            /* [in] */ LONG y,
            /* [in] */ CHAR button);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MouseMove )( 
            IosgControl * This,
            /* [in] */ LONG x,
            /* [in] */ LONG y);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MouseUp )( 
            IosgControl * This,
            /* [in] */ LONG x,
            /* [in] */ LONG y,
            /* [in] */ CHAR button);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HideVertex )( 
            IosgControl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HideEdge )( 
            IosgControl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HideFace )( 
            IosgControl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectPoint )( 
            IosgControl * This,
            /* [in] */ LONG x,
            /* [in] */ LONG y);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectVertex )( 
            IosgControl * This,
            /* [in] */ LONG x,
            /* [in] */ LONG y);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectEdge )( 
            IosgControl * This,
            /* [in] */ LONG x,
            /* [in] */ LONG y);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectFace )( 
            IosgControl * This,
            /* [in] */ LONG x,
            /* [in] */ LONG y);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSelectColor )( 
            IosgControl * This,
            /* [in] */ SHORT r,
            /* [in] */ SHORT g,
            /* [in] */ SHORT b);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectVertexRingVertex )( 
            IosgControl * This,
            /* [in] */ LONG x,
            /* [in] */ LONG y);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectVertexRingEdge )( 
            IosgControl * This,
            /* [in] */ LONG x,
            /* [in] */ LONG y);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectVertexRingFace )( 
            IosgControl * This,
            /* [in] */ LONG x,
            /* [in] */ LONG y);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectEdgeRingVertex )( 
            IosgControl * This,
            /* [in] */ LONG x,
            /* [in] */ LONG y);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectEdgeRingEdge )( 
            IosgControl * This,
            /* [in] */ LONG x,
            /* [in] */ LONG y);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectEdgeRingFace )( 
            IosgControl * This,
            /* [in] */ LONG x,
            /* [in] */ LONG y);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectFaceRingVertex )( 
            IosgControl * This,
            /* [in] */ LONG x,
            /* [in] */ LONG y);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectFaceRingEdge )( 
            IosgControl * This,
            /* [in] */ LONG x,
            /* [in] */ LONG y);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectFaceRingFace )( 
            IosgControl * This,
            /* [in] */ LONG x,
            /* [in] */ LONG y);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ClearPoints )( 
            IosgControl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ClearVertexes )( 
            IosgControl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ClearEdges )( 
            IosgControl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ClearFaces )( 
            IosgControl * This);
        
        END_INTERFACE
    } IosgControlVtbl;

    interface IosgControl
    {
        CONST_VTBL struct IosgControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IosgControl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IosgControl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IosgControl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IosgControl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IosgControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IosgControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IosgControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IosgControl_LoadObjMesh(This,filepath,status)	\
    ( (This)->lpVtbl -> LoadObjMesh(This,filepath,status) ) 

#define IosgControl_ShowVertex(This)	\
    ( (This)->lpVtbl -> ShowVertex(This) ) 

#define IosgControl_ShowEdge(This)	\
    ( (This)->lpVtbl -> ShowEdge(This) ) 

#define IosgControl_ShowFace(This)	\
    ( (This)->lpVtbl -> ShowFace(This) ) 

#define IosgControl_InitOSG(This,windowHandle)	\
    ( (This)->lpVtbl -> InitOSG(This,windowHandle) ) 

#define IosgControl_MouseDown(This,x,y,button)	\
    ( (This)->lpVtbl -> MouseDown(This,x,y,button) ) 

#define IosgControl_MouseMove(This,x,y)	\
    ( (This)->lpVtbl -> MouseMove(This,x,y) ) 

#define IosgControl_MouseUp(This,x,y,button)	\
    ( (This)->lpVtbl -> MouseUp(This,x,y,button) ) 

#define IosgControl_HideVertex(This)	\
    ( (This)->lpVtbl -> HideVertex(This) ) 

#define IosgControl_HideEdge(This)	\
    ( (This)->lpVtbl -> HideEdge(This) ) 

#define IosgControl_HideFace(This)	\
    ( (This)->lpVtbl -> HideFace(This) ) 

#define IosgControl_SelectPoint(This,x,y)	\
    ( (This)->lpVtbl -> SelectPoint(This,x,y) ) 

#define IosgControl_SelectVertex(This,x,y)	\
    ( (This)->lpVtbl -> SelectVertex(This,x,y) ) 

#define IosgControl_SelectEdge(This,x,y)	\
    ( (This)->lpVtbl -> SelectEdge(This,x,y) ) 

#define IosgControl_SelectFace(This,x,y)	\
    ( (This)->lpVtbl -> SelectFace(This,x,y) ) 

#define IosgControl_SetSelectColor(This,r,g,b)	\
    ( (This)->lpVtbl -> SetSelectColor(This,r,g,b) ) 

#define IosgControl_SelectVertexRingVertex(This,x,y)	\
    ( (This)->lpVtbl -> SelectVertexRingVertex(This,x,y) ) 

#define IosgControl_SelectVertexRingEdge(This,x,y)	\
    ( (This)->lpVtbl -> SelectVertexRingEdge(This,x,y) ) 

#define IosgControl_SelectVertexRingFace(This,x,y)	\
    ( (This)->lpVtbl -> SelectVertexRingFace(This,x,y) ) 

#define IosgControl_SelectEdgeRingVertex(This,x,y)	\
    ( (This)->lpVtbl -> SelectEdgeRingVertex(This,x,y) ) 

#define IosgControl_SelectEdgeRingEdge(This,x,y)	\
    ( (This)->lpVtbl -> SelectEdgeRingEdge(This,x,y) ) 

#define IosgControl_SelectEdgeRingFace(This,x,y)	\
    ( (This)->lpVtbl -> SelectEdgeRingFace(This,x,y) ) 

#define IosgControl_SelectFaceRingVertex(This,x,y)	\
    ( (This)->lpVtbl -> SelectFaceRingVertex(This,x,y) ) 

#define IosgControl_SelectFaceRingEdge(This,x,y)	\
    ( (This)->lpVtbl -> SelectFaceRingEdge(This,x,y) ) 

#define IosgControl_SelectFaceRingFace(This,x,y)	\
    ( (This)->lpVtbl -> SelectFaceRingFace(This,x,y) ) 

#define IosgControl_ClearPoints(This)	\
    ( (This)->lpVtbl -> ClearPoints(This) ) 

#define IosgControl_ClearVertexes(This)	\
    ( (This)->lpVtbl -> ClearVertexes(This) ) 

#define IosgControl_ClearEdges(This)	\
    ( (This)->lpVtbl -> ClearEdges(This) ) 

#define IosgControl_ClearFaces(This)	\
    ( (This)->lpVtbl -> ClearFaces(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IosgControl_INTERFACE_DEFINED__ */



#ifndef __digital_meshLib_LIBRARY_DEFINED__
#define __digital_meshLib_LIBRARY_DEFINED__

/* library digital_meshLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_digital_meshLib;

EXTERN_C const CLSID CLSID_osgControl;

#ifdef __cplusplus

class DECLSPEC_UUID("7FA9490A-AD27-4787-8E98-EBCDCF28F6CE")
osgControl;
#endif
#endif /* __digital_meshLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


