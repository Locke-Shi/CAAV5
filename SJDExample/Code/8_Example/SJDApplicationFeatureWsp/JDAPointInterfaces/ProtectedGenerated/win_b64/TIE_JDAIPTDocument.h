#ifndef __TIE_JDAIPTDocument
#define __TIE_JDAIPTDocument

#include <string.h>
#include "CATBaseUnknown.h"
#include "CATMetaClass.h"
#include "CATMacForTie.h"
#include "JDAIPTDocument.h"
#include "JS0DSPA.h"


#ifdef _WINDOWS_SOURCE
#define Exported __declspec(dllexport)
#define Imported __declspec(dllimport)
#else
#define Exported 
#define Imported 
#endif


/* To link an implementation with the interface JDAIPTDocument */
#define declare_TIE_JDAIPTDocument(classe) \
 \
 \
class TIEJDAIPTDocument##classe : public JDAIPTDocument \
{ \
   private: \
      CATDeclareCommonTIEMembers \
   public: \
      CATDeclareTIEMethods(JDAIPTDocument, classe) \
      CATDeclareIUnknownMethodsForCATBaseUnknownTIE \
      CATDeclareIDispatchMethodsForCATBaseUnknownTIE \
      CATDeclareCATBaseUnknownMethodsForTIE \
      virtual HRESULT GetContainer ( CATIContainer **opiContainer, CATBoolean iCreateIfNeeded = false); \
};



#define ENVTIEdeclare_JDAIPTDocument(ENVTIEName,ENVTIETypeLetter,ENVTIELetter) \
virtual HRESULT GetContainer ( CATIContainer **opiContainer, CATBoolean iCreateIfNeeded = false); \


#define ENVTIEdefine_JDAIPTDocument(ENVTIEName,ENVTIETypeLetter,ENVTIELetter) \
HRESULT  ENVTIEName::GetContainer ( CATIContainer **opiContainer, CATBoolean iCreateIfNeeded ) \
{ \
return (ENVTIECALL(JDAIPTDocument,ENVTIETypeLetter,ENVTIELetter)GetContainer (opiContainer,iCreateIfNeeded )); \
} \


/* Name of the TIE class */
#define class_TIE_JDAIPTDocument(classe)    TIEJDAIPTDocument##classe


/* Common methods inside a TIE */
#define common_TIE_JDAIPTDocument(classe) \
 \
 \
/* Static initialization */ \
CATDefineCommonTIEMembers(JDAIPTDocument, classe) \
 \
 \
CATImplementTIEMethods(JDAIPTDocument, classe) \
CATImplementIUnknownMethodsForCATBaseUnknownTIE(JDAIPTDocument, classe, 1) \
CATImplementIDispatchMethodsForCATBaseUnknownTIE(JDAIPTDocument, classe) \
CATImplementCATBaseUnknownMethodsForTIE(JDAIPTDocument, classe) \
 \
HRESULT  TIEJDAIPTDocument##classe::GetContainer ( CATIContainer **opiContainer, CATBoolean iCreateIfNeeded ) \
{ \
   return(((classe *)Tie_Method(NecessaryData.ForTIE,ptstat))->GetContainer (opiContainer,iCreateIfNeeded )); \
} \



/* Macro used to link an implementation with an interface */
#define TIE_JDAIPTDocument(classe) \
 \
 \
declare_TIE_JDAIPTDocument(classe) \
 \
 \
CATMetaClass * __stdcall TIEJDAIPTDocument##classe::MetaObject() \
{ \
   if (!meta_object) \
   { \
      meta_object=new CATMetaClass(&IID_JDAIPTDocument,"JDAIPTDocument",JDAIPTDocument::MetaObject(),classe::MetaObject(),TIE); \
   } \
   return(meta_object); \
} \
 \
 \
common_TIE_JDAIPTDocument(classe) \
 \
 \
/* creator function of the interface */ \
/* encapsulate the new */ \
CATImplementTIECreation(JDAIPTDocument, classe) \
 \
/* to put information into the dictionary */ \
static CATFillDictionary DicJDAIPTDocument##classe(classe::MetaObject(),JDAIPTDocument::MetaObject(),(void *)CreateTIEJDAIPTDocument##classe)



/* Macro used to link an implementation with an interface */
/* This TIE is chained on the implementation object */
#define TIEchain_JDAIPTDocument(classe) \
 \
 \
declare_TIE_JDAIPTDocument(classe) \
 \
 \
CATMetaClass * __stdcall TIEJDAIPTDocument##classe::MetaObject() \
{ \
   if (!meta_object) \
   { \
      meta_object=new CATMetaClass(&IID_JDAIPTDocument,"JDAIPTDocument",JDAIPTDocument::MetaObject(),classe::MetaObject(),TIEchain); \
   } \
   return(meta_object); \
} \
 \
 \
common_TIE_JDAIPTDocument(classe) \
 \
 \
/* creator function of the interface */ \
/* encapsulate the new */ \
CATImplementTIEchainCreation(JDAIPTDocument, classe) \
 \
/* to put information into the dictionary */ \
static CATFillDictionary DicJDAIPTDocument##classe(classe::MetaObject(),JDAIPTDocument::MetaObject(),(void *)CreateTIEJDAIPTDocument##classe)


/* Macro to switch between BOA and TIE at build time */ 
#ifdef CATSYS_BOA_IS_TIE
#define BOA_JDAIPTDocument(classe) TIE_JDAIPTDocument(classe)
#else
#define BOA_JDAIPTDocument(classe) CATImplementBOA(JDAIPTDocument, classe)
#endif

#endif
