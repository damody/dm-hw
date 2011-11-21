// digital_mesh.cpp : DLL �ץX����@�C


#include "stdafx.h"
#include "resource.h"
#include "digital_mesh_i.h"
#include "dllmain.h"

// �ΨӧP�_ DLL �O�_�i�Q OLE ����
STDAPI DllCanUnloadNow(void)
{
    return _AtlModule.DllCanUnloadNow();
}


// �Ǧ^ Class Factory �H�إߩҭn�D���O������
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}


// DllRegisterServer - �N���إ[�J��t�εn��
STDAPI DllRegisterServer(void)
{
    // �n������BTypelib �M�Ҧ� Typelib ��������
    HRESULT hr = _AtlModule.DllRegisterServer();
	return hr;
}


// DllUnregisterServer - �q�t�εn����������
STDAPI DllUnregisterServer(void)
{
	HRESULT hr = _AtlModule.DllUnregisterServer();
	return hr;
}

// DllInstall - �b�t�εn�����[�J/�������ءA�ӥB�O�w��ӧO�ϥΪ̤�
//              �ӧO�q���C	
STDAPI DllInstall(BOOL bInstall, LPCWSTR pszCmdLine)
{
    HRESULT hr = E_FAIL;
    static const wchar_t szUserSwitch[] = _T("user");

    if (pszCmdLine != NULL)
    {
    	if (_wcsnicmp(pszCmdLine, szUserSwitch, _countof(szUserSwitch)) == 0)
    	{
    		AtlSetPerUserRegistration(true);
    	}
    }

    if (bInstall)
    {	
    	hr = DllRegisterServer();
    	if (FAILED(hr))
    	{	
    		DllUnregisterServer();
    	}
    }
    else
    {
    	hr = DllUnregisterServer();
    }

    return hr;
}


