// dllmain.h : 模組類別的宣告。

class Cdigital_meshModule : public CAtlDllModuleT< Cdigital_meshModule >
{
public :
	DECLARE_LIBID(LIBID_digital_meshLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_DIGITAL_MESH, "{636067A7-4708-41D7-A6CC-13AE8A85F096}")
};

extern class Cdigital_meshModule _AtlModule;
