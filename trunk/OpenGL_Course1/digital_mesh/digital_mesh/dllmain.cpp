// dllmain.cpp : DllMain 的實作。

#include "stdafx.h"
#include "resource.h"
#include "digital_mesh_i.h"
#include "dllmain.h"

Cdigital_meshModule _AtlModule;

// DLL 進入點
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInstance;
	return _AtlModule.DllMain(dwReason, lpReserved); 
}
