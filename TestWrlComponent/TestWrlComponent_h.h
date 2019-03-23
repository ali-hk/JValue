/* Header file automatically generated from TestWrlComponent.idl */
/*
 * File built with Microsoft(R) MIDLRT Compiler Engine Version 10.00.0223 
 */

#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

/* verify that the <rpcsal.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCSAL_H_VERSION__
#define __REQUIRED_RPCSAL_H_VERSION__ 100
#endif

#include <rpc.h>
#include <rpcndr.h>

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include <windows.h>
#include <ole2.h>
#endif /*COM_NO_WINDOWS_H*/
#ifndef __TestWrlComponent_h_h__
#define __TestWrlComponent_h_h__
#ifndef __TestWrlComponent_h_p_h__
#define __TestWrlComponent_h_p_h__


#pragma once

// Ensure that the setting of the /ns_prefix command line switch is consistent for all headers.
// If you get an error from the compiler indicating "warning C4005: 'CHECK_NS_PREFIX_STATE': macro redefinition", this
// indicates that you have included two different headers with different settings for the /ns_prefix MIDL command line switch
#if !defined(DISABLE_NS_PREFIX_CHECKS)
#define CHECK_NS_PREFIX_STATE "always"
#endif // !defined(DISABLE_NS_PREFIX_CHECKS)


#pragma push_macro("MIDL_CONST_ID")
#undef MIDL_CONST_ID
#define MIDL_CONST_ID const __declspec(selectany)


//  API Contract Inclusion Definitions
#if !defined(SPECIFIC_API_CONTRACT_DEFINITIONS)
#if !defined(TESTWRLCOMPONENT_TESTCONTRACT_VERSION)
#define TESTWRLCOMPONENT_TESTCONTRACT_VERSION 0x10000
#endif // defined(TESTWRLCOMPONENT_TESTCONTRACT_VERSION)

#if !defined(WINDOWS_APPLICATIONMODEL_CALLS_CALLSPHONECONTRACT_VERSION)
#define WINDOWS_APPLICATIONMODEL_CALLS_CALLSPHONECONTRACT_VERSION 0x40000
#endif // defined(WINDOWS_APPLICATIONMODEL_CALLS_CALLSPHONECONTRACT_VERSION)

#if !defined(WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION)
#define WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION 0x30000
#endif // defined(WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION)

#if !defined(WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION)
#define WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION 0x70000
#endif // defined(WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION)

#if !defined(WINDOWS_NETWORKING_SOCKETS_CONTROLCHANNELTRIGGERCONTRACT_VERSION)
#define WINDOWS_NETWORKING_SOCKETS_CONTROLCHANNELTRIGGERCONTRACT_VERSION 0x30000
#endif // defined(WINDOWS_NETWORKING_SOCKETS_CONTROLCHANNELTRIGGERCONTRACT_VERSION)

#if !defined(WINDOWS_PHONE_PHONECONTRACT_VERSION)
#define WINDOWS_PHONE_PHONECONTRACT_VERSION 0x10000
#endif // defined(WINDOWS_PHONE_PHONECONTRACT_VERSION)

#if !defined(WINDOWS_PHONE_PHONEINTERNALCONTRACT_VERSION)
#define WINDOWS_PHONE_PHONEINTERNALCONTRACT_VERSION 0x10000
#endif // defined(WINDOWS_PHONE_PHONEINTERNALCONTRACT_VERSION)

#if !defined(WINDOWS_UI_WEBUI_CORE_WEBUICOMMANDBARCONTRACT_VERSION)
#define WINDOWS_UI_WEBUI_CORE_WEBUICOMMANDBARCONTRACT_VERSION 0x10000
#endif // defined(WINDOWS_UI_WEBUI_CORE_WEBUICOMMANDBARCONTRACT_VERSION)

#endif // defined(SPECIFIC_API_CONTRACT_DEFINITIONS)


// Header files for imported files
#include "oaidl.h"
#include "ocidl.h"
#include "Inspectable.h"
#include "Windows.Foundation.h"

#if defined(__cplusplus) && !defined(CINTERFACE)
#if defined(__MIDL_USE_C_ENUM)
#define MIDL_ENUM enum
#else
#define MIDL_ENUM enum class
#endif
/* Forward Declarations */
#ifndef ____x_ABI_CTestWrlComponent_CITestClass_FWD_DEFINED__
#define ____x_ABI_CTestWrlComponent_CITestClass_FWD_DEFINED__
namespace ABI {
    namespace TestWrlComponent {
        interface ITestClass;
    } /* TestWrlComponent */} /* ABI */
#define __x_ABI_CTestWrlComponent_CITestClass ABI::TestWrlComponent::ITestClass

#endif // ____x_ABI_CTestWrlComponent_CITestClass_FWD_DEFINED__




/*
 *
 * Interface TestWrlComponent.ITestClass
 *
 * Introduced to TestWrlComponent.TestContract in version 1.0
 *
 *
 */
#if TESTWRLCOMPONENT_TESTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CTestWrlComponent_CITestClass_INTERFACE_DEFINED__)
#define ____x_ABI_CTestWrlComponent_CITestClass_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_TestWrlComponent_ITestClass[] = L"TestWrlComponent.ITestClass";
namespace ABI {
    namespace TestWrlComponent {
        /* [object, contract, uuid("a7bf2f2b-115b-4fbf-9b40-0fb434779668")] */
        MIDL_INTERFACE("a7bf2f2b-115b-4fbf-9b40-0fb434779668")
        ITestClass : public IInspectable
        {
        public:
            virtual HRESULT STDMETHODCALLTYPE TestMethod(void) = 0;
            
        };

        extern MIDL_CONST_ID IID & IID_ITestClass=_uuidof(ITestClass);
        
    } /* TestWrlComponent */} /* ABI */

EXTERN_C const IID IID___x_ABI_CTestWrlComponent_CITestClass;
#endif /* !defined(____x_ABI_CTestWrlComponent_CITestClass_INTERFACE_DEFINED__) */
#endif // TESTWRLCOMPONENT_TESTCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace TestWrlComponent {
        class TestClass;
    } /* TestWrlComponent */} /* ABI */



/*
 *
 * Class TestWrlComponent.TestClass
 *
 * Introduced to TestWrlComponent.TestContract in version 1.0
 *
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the TestWrlComponent.TestContract API contract
 *
 * Class implements the following interfaces:
 *    TestWrlComponent.ITestClass ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if TESTWRLCOMPONENT_TESTCONTRACT_VERSION >= 0x10000

#ifndef RUNTIMECLASS_TestWrlComponent_TestClass_DEFINED
#define RUNTIMECLASS_TestWrlComponent_TestClass_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_TestWrlComponent_TestClass[] = L"TestWrlComponent.TestClass";
#endif
#endif // TESTWRLCOMPONENT_TESTCONTRACT_VERSION >= 0x10000


#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CTestWrlComponent_CITestClass_FWD_DEFINED__
#define ____x_ABI_CTestWrlComponent_CITestClass_FWD_DEFINED__
typedef interface __x_ABI_CTestWrlComponent_CITestClass __x_ABI_CTestWrlComponent_CITestClass;

#endif // ____x_ABI_CTestWrlComponent_CITestClass_FWD_DEFINED__



/*
 *
 * Interface TestWrlComponent.ITestClass
 *
 * Introduced to TestWrlComponent.TestContract in version 1.0
 *
 *
 */
#if TESTWRLCOMPONENT_TESTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CTestWrlComponent_CITestClass_INTERFACE_DEFINED__)
#define ____x_ABI_CTestWrlComponent_CITestClass_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_TestWrlComponent_ITestClass[] = L"TestWrlComponent.ITestClass";
/* [object, contract, uuid("a7bf2f2b-115b-4fbf-9b40-0fb434779668")] */
typedef struct __x_ABI_CTestWrlComponent_CITestClassVtbl
{
    BEGIN_INTERFACE
    HRESULT ( STDMETHODCALLTYPE *QueryInterface)(
    __RPC__in __x_ABI_CTestWrlComponent_CITestClass * This,
    /* [in] */ __RPC__in REFIID riid,
    /* [annotation][iid_is][out] */
    _COM_Outptr_  void **ppvObject
    );

ULONG ( STDMETHODCALLTYPE *AddRef )(
    __RPC__in __x_ABI_CTestWrlComponent_CITestClass * This
    );

ULONG ( STDMETHODCALLTYPE *Release )(
    __RPC__in __x_ABI_CTestWrlComponent_CITestClass * This
    );

HRESULT ( STDMETHODCALLTYPE *GetIids )(
    __RPC__in __x_ABI_CTestWrlComponent_CITestClass * This,
    /* [out] */ __RPC__out ULONG *iidCount,
    /* [size_is][size_is][out] */ __RPC__deref_out_ecount_full_opt(*iidCount) IID **iids
    );

HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )(
    __RPC__in __x_ABI_CTestWrlComponent_CITestClass * This,
    /* [out] */ __RPC__deref_out_opt HSTRING *className
    );

HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )(
    __RPC__in __x_ABI_CTestWrlComponent_CITestClass * This,
    /* [OUT ] */ __RPC__out TrustLevel *trustLevel
    );
HRESULT ( STDMETHODCALLTYPE *TestMethod )(
        __x_ABI_CTestWrlComponent_CITestClass * This
        );
    END_INTERFACE
    
} __x_ABI_CTestWrlComponent_CITestClassVtbl;

interface __x_ABI_CTestWrlComponent_CITestClass
{
    CONST_VTBL struct __x_ABI_CTestWrlComponent_CITestClassVtbl *lpVtbl;
};

#ifdef COBJMACROS
#define __x_ABI_CTestWrlComponent_CITestClass_QueryInterface(This,riid,ppvObject) \
( (This)->lpVtbl->QueryInterface(This,riid,ppvObject) )

#define __x_ABI_CTestWrlComponent_CITestClass_AddRef(This) \
        ( (This)->lpVtbl->AddRef(This) )

#define __x_ABI_CTestWrlComponent_CITestClass_Release(This) \
        ( (This)->lpVtbl->Release(This) )

#define __x_ABI_CTestWrlComponent_CITestClass_GetIids(This,iidCount,iids) \
        ( (This)->lpVtbl->GetIids(This,iidCount,iids) )

#define __x_ABI_CTestWrlComponent_CITestClass_GetRuntimeClassName(This,className) \
        ( (This)->lpVtbl->GetRuntimeClassName(This,className) )

#define __x_ABI_CTestWrlComponent_CITestClass_GetTrustLevel(This,trustLevel) \
        ( (This)->lpVtbl->GetTrustLevel(This,trustLevel) )

#define __x_ABI_CTestWrlComponent_CITestClass_TestMethod(This) \
    ( (This)->lpVtbl->TestMethod(This) )


#endif /* COBJMACROS */


EXTERN_C const IID IID___x_ABI_CTestWrlComponent_CITestClass;
#endif /* !defined(____x_ABI_CTestWrlComponent_CITestClass_INTERFACE_DEFINED__) */
#endif // TESTWRLCOMPONENT_TESTCONTRACT_VERSION >= 0x10000



/*
 *
 * Class TestWrlComponent.TestClass
 *
 * Introduced to TestWrlComponent.TestContract in version 1.0
 *
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the TestWrlComponent.TestContract API contract
 *
 * Class implements the following interfaces:
 *    TestWrlComponent.ITestClass ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if TESTWRLCOMPONENT_TESTCONTRACT_VERSION >= 0x10000

#ifndef RUNTIMECLASS_TestWrlComponent_TestClass_DEFINED
#define RUNTIMECLASS_TestWrlComponent_TestClass_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_TestWrlComponent_TestClass[] = L"TestWrlComponent.TestClass";
#endif
#endif // TESTWRLCOMPONENT_TESTCONTRACT_VERSION >= 0x10000


#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __TestWrlComponent_h_p_h__

#endif // __TestWrlComponent_h_h__
