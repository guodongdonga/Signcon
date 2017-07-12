

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Wed Jul 12 21:42:45 2017
 */
/* Compiler settings for Signcon.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
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


#ifndef __Signcon_h_h__
#define __Signcon_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISigncon_FWD_DEFINED__
#define __ISigncon_FWD_DEFINED__
typedef interface ISigncon ISigncon;

#endif 	/* __ISigncon_FWD_DEFINED__ */


#ifndef __Signcon_FWD_DEFINED__
#define __Signcon_FWD_DEFINED__

#ifdef __cplusplus
typedef class Signcon Signcon;
#else
typedef struct Signcon Signcon;
#endif /* __cplusplus */

#endif 	/* __Signcon_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __Signcon_LIBRARY_DEFINED__
#define __Signcon_LIBRARY_DEFINED__

/* library Signcon */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_Signcon;

#ifndef __ISigncon_DISPINTERFACE_DEFINED__
#define __ISigncon_DISPINTERFACE_DEFINED__

/* dispinterface ISigncon */
/* [uuid] */ 


EXTERN_C const IID DIID_ISigncon;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("F0E1103C-2440-4CB2-92B6-21473992F8FF")
    ISigncon : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ISignconVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISigncon * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISigncon * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISigncon * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISigncon * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISigncon * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISigncon * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISigncon * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } ISignconVtbl;

    interface ISigncon
    {
        CONST_VTBL struct ISignconVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISigncon_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISigncon_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISigncon_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISigncon_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ISigncon_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ISigncon_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ISigncon_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ISigncon_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Signcon;

#ifdef __cplusplus

class DECLSPEC_UUID("66649C91-23BC-4858-9F53-13527F73FB22")
Signcon;
#endif
#endif /* __Signcon_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


