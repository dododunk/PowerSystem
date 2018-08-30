

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Jun 26 13:23:57 2012
 */
/* Compiler settings for IFRM.odl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

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


#ifndef __IFRM_h_h__
#define __IFRM_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IIFRM_FWD_DEFINED__
#define __IIFRM_FWD_DEFINED__
typedef interface IIFRM IIFRM;
#endif 	/* __IIFRM_FWD_DEFINED__ */


#ifndef __Document_FWD_DEFINED__
#define __Document_FWD_DEFINED__

#ifdef __cplusplus
typedef class Document Document;
#else
typedef struct Document Document;
#endif /* __cplusplus */

#endif 	/* __Document_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __IFRM_LIBRARY_DEFINED__
#define __IFRM_LIBRARY_DEFINED__

/* library IFRM */
/* [version][uuid] */ 


DEFINE_GUID(LIBID_IFRM,0x2CD482BE,0x1805,0x42FF,0x91,0x55,0x10,0xAC,0x16,0x9D,0x6D,0xBE);

#ifndef __IIFRM_DISPINTERFACE_DEFINED__
#define __IIFRM_DISPINTERFACE_DEFINED__

/* dispinterface IIFRM */
/* [uuid] */ 


DEFINE_GUID(DIID_IIFRM,0x289B6134,0xD862,0x4066,0x9E,0x9C,0x7A,0x3A,0x16,0x3E,0xEE,0x8B);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("289B6134-D862-4066-9E9C-7A3A163EEE8B")
    IIFRM : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IIFRMVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIFRM * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIFRM * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIFRM * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IIFRM * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IIFRM * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IIFRM * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IIFRM * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IIFRMVtbl;

    interface IIFRM
    {
        CONST_VTBL struct IIFRMVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIFRM_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIFRM_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIFRM_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIFRM_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IIFRM_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IIFRM_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IIFRM_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IIFRM_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_Document,0x8B14B09D,0xD2CF,0x40AF,0x94,0xD3,0x9C,0xC1,0xF6,0x1B,0x0A,0xFE);

#ifdef __cplusplus

class DECLSPEC_UUID("8B14B09D-D2CF-40AF-94D3-9CC1F61B0AFE")
Document;
#endif
#endif /* __IFRM_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


