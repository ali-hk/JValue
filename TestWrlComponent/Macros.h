#pragma once

#define RETURN_IF_FAILED(hr) if(FAILED(hr)) { return hr; }
#define RETURN_HR(hr) return hr;
#define RETURN_HR_IF(hr, condition) if(condition) { return hr; }
#define RETURN_HR_IF_NULL(hr, pointer) if(pointer == nullptr) { return hr; }
#define RETURN_HR_IF_FALSE(hr, condition) if(condition == false) { return hr; }

#define RETURN_LAST_ERROR() return HRESULT_FROM_WIN32(GetLastError());
#define RETURN_HR_FROM_WIN32(dword) return HRESULT_FROM_WIN32(dword);


#define DEFINE_PROPERTY_STRING(propName, propNameLower) \
public: \
IFACEMETHOD(get_##propName)(_Outptr_ HSTRING *propNameLower)  { RETURN_HR(_hs##propNameLower.CopyTo(propNameLower)); } \
IFACEMETHOD(put_##propName)(_In_ HSTRING propNameLower) { RETURN_HR(WindowsDuplicateString(propNameLower, _hs##propNameLower.GetAddressOf())); } \
private: \
Microsoft::WRL::Wrappers::HString _hs##propNameLower;

#define DEFINE_PROPERTY_PTR(type, propName, propNameLower) \
public: \
IFACEMETHOD(get_##propName)(_Outptr_ type **propNameLower)  { RETURN_HR(_sp##propNameLower.CopyTo(propNameLower)); } \
IFACEMETHOD(put_##propName)(_In_ type *propNameLower) { _sp##propNameLower = propNameLower; return S_OK; } \
private: \
Microsoft::WRL::ComPtr<type> _sp##propNameLower;

#define DEFINE_PROPERTY_VALUE(type, propName, propNameLower) \
public: \
IFACEMETHOD(get_##propName)(_Out_ type *propNameLower)  { *propNameLower = _##propNameLower; return S_OK; } \
IFACEMETHOD(put_##propName)(_In_ type propNameLower) { _##propNameLower = propNameLower; return S_OK; } \
private: \
type _##propNameLower;