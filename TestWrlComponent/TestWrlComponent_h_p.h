

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Mon Jan 18 19:14:07 2038
 */
/* Compiler settings for C:\Users\alkhayat\AppData\Local\Temp\TestWrlComponent.idl-bac3a043:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __TestWrlComponent_h_p_h__
#define __TestWrlComponent_h_p_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#if defined(__cplusplus)
#if defined(__MIDL_USE_C_ENUM)
#define MIDL_ENUM enum
#else
#define MIDL_ENUM enum class
#endif
#endif


/* Forward Declarations */ 

#ifndef ____x_ABI_CTestWrlComponent_CITestClass_FWD_DEFINED__
#define ____x_ABI_CTestWrlComponent_CITestClass_FWD_DEFINED__
typedef interface __x_ABI_CTestWrlComponent_CITestClass __x_ABI_CTestWrlComponent_CITestClass;

#endif 	/* ____x_ABI_CTestWrlComponent_CITestClass_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "Inspectable.h"
#include "Windows.Foundation.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_TestWrlComponent_0000_0000 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_TestWrlComponent_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_TestWrlComponent_0000_0000_v0_0_s_ifspec;

#ifndef ____x_ABI_CTestWrlComponent_CITestClass_INTERFACE_DEFINED__
#define ____x_ABI_CTestWrlComponent_CITestClass_INTERFACE_DEFINED__

/* interface __x_ABI_CTestWrlComponent_CITestClass */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CTestWrlComponent_CITestClass;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a7bf2f2b-115b-4fbf-9b40-0fb434779668")
    __x_ABI_CTestWrlComponent_CITestClass : public IInspectable
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE TestMethod( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct __x_ABI_CTestWrlComponent_CITestClassVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CTestWrlComponent_CITestClass * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CTestWrlComponent_CITestClass * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CTestWrlComponent_CITestClass * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CTestWrlComponent_CITestClass * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CTestWrlComponent_CITestClass * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CTestWrlComponent_CITestClass * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *TestMethod )( 
            __x_ABI_CTestWrlComponent_CITestClass * This);
        
        END_INTERFACE
    } __x_ABI_CTestWrlComponent_CITestClassVtbl;

    interface __x_ABI_CTestWrlComponent_CITestClass
    {
        CONST_VTBL struct __x_ABI_CTestWrlComponent_CITestClassVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CTestWrlComponent_CITestClass_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CTestWrlComponent_CITestClass_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CTestWrlComponent_CITestClass_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CTestWrlComponent_CITestClass_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CTestWrlComponent_CITestClass_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CTestWrlComponent_CITestClass_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CTestWrlComponent_CITestClass_TestMethod(This)	\
    ( (This)->lpVtbl -> TestMethod(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CTestWrlComponent_CITestClass_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_TestWrlComponent_0000_0001 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_TestWrlComponent_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_TestWrlComponent_0000_0001_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


