#include <pch.h>

STDAPI DllGetActivationFactory(
    _In_ HSTRING activatibleClassId,
    _COM_Outptr_ IActivationFactory** factory
)
{
    auto &module = Microsoft::WRL::Module<Microsoft::WRL::InProc>::GetModule();
    return module.GetActivationFactory(activatibleClassId, factory);
}

HRESULT WINAPI DllCanUnloadNow()
{
    auto &module = Microsoft::WRL::Module<Microsoft::WRL::InProc>::GetModule();
    return module.GetObjectCount() == 0 ? S_OK : S_FALSE;
}

HRESULT WINAPI DllGetClassObject(
    _In_ REFCLSID rclsid,
    _In_ REFIID riid,
    _Outptr_ LPVOID FAR* ppv
)
{
    auto &module = Microsoft::WRL::Module<Microsoft::WRL::InProc>::GetModule();
    return module.GetClassObject(rclsid, riid, ppv);
}

BOOL WINAPI DllMain(
    _In_ HINSTANCE Module,
    _In_ DWORD Reason,
    _In_opt_ PVOID Reserved
)
{
    UNREFERENCED_PARAMETER(Reserved);

    if (Module == nullptr) {
        return FALSE;
    }

    switch (Reason) {
    case DLL_PROCESS_ATTACH:
        break;

    case DLL_PROCESS_DETACH:
        break;

    default:
        break;
    }

    return TRUE;
}