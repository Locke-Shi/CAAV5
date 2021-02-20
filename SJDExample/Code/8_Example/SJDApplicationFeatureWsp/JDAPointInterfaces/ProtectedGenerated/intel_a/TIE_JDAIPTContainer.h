#ifndef __TIE_JDAIPTContainer
#define __TIE_JDAIPTContainer

#include <string.h>
#include "CATBaseUnknown.h"
#include "CATMetaClass.h"
#include "CATMacForTie.h"
#include "JDAIPTContainer.h"
#include "JS0DSPA.h"


#ifdef _WINDOWS_SOURCE
#define Exported __declspec(dllexport)
#define Imported __declspec(dllimport)
#else
#define Exported 
#define Imported 
#endif


/* To link an implementation with the interface JDAIPTContainer */
#define declare_TIE_JDAIPTContainer(classe) \
 \
 \
class TIEJDAIPTContainer##classe : public JDAIPTContainer \
{ \
   private: \
      CATDeclareCommonTIEMembers \
   public: \
      CATDeclareTIEMethods(JDAIPTContainer, classe) \
      CATDeclareIUnknownMethodsForCATBaseUnknownTIE \
      CATDeclareIDispatchMethodsForCATBaseUnknownTIE \
      CATDeclareCATBaseUnknownMethodsForTIE \
      virtual HRESULT GetRoot(JDAIPTRoot **opiRoot) ; \
};



#define ENVTIEdeclare_JDAIPTContainer(ENVTIEName,ENVTIETypeLetter,ENVTIELetter) \
virtual HRESULT GetRoot(JDAIPTRoot **opiRoot) ; \


#define ENVTIEdefine_JDAIPTContainer(ENVTIEName,ENVTIETypeLetter,ENVTIELetter) \
HRESULT  ENVTIEName::GetRoot(JDAIPTRoot **opiRoot)  \
{ \
return (ENVTIECALL(JDAIPTContainer,ENVTIETypeLetter,ENVTIELetter)GetRoot(opiRoot)); \
} \


/* Name of the TIE class */
#define class_TIE_JDAIPTContainer(classe)    TIEJDAIPTContainer##classe


/* Common methods inside a TIE */
#define common_TIE_JDAIPTContainer(classe) \
 \
 \
/* Static initialization */ \
CATDefineCommonTIEMembers(JDAIPTContainer, classe) \
 \
 \
CATImplementTIEMethods(JDAIPTContainer, classe) \
CATImplementIUnknownMethodsForCATBaseUnknownTIE(JDAIPTContainer, classe, 1) \
CATImplementIDispatchMethodsForCATBaseUnknownTIE(JDAIPTContainer, classe) \
CATImplementCATBaseUnknownMethodsForTIE(JDAIPTContainer, classe) \
 \
HRESULT  TIEJDAIPTContainer##classe::GetRoot(JDAIPTRoot **opiRoot)  \
{ \
   return(((classe *)Tie_Method(NecessaryData.ForTIE,ptstat))->GetRoot(opiRoot)); \
} \



/* Macro used to link an implementation with an interface */
#define TIE_JDAIPTContainer(classe) \
 \
 \
declare_TIE_JDAIPTContainer(classe) \
 \
 \
CATMetaClass * __stdcall TIEJDAIPTContainer##classe::MetaObject() \
{ \
   if (!meta_object) \
   { \
      meta_object=new CATMetaClass(&IID_JDAIPTContainer,"JDAIPTContainer",JDAIPTContainer::MetaObject(),classe::MetaObject(),TIE); \
   } \
   return(meta_object); \
} \
 \
 \
common_TIE_JDAIPTContainer(classe) \
 \
 \
/* creator function of the interface */ \
/* encapsulate the new */ \
CATImplementTIECreation(JDAIPTContainer, classe) \
 \
/* to put information into the dictionary */ \
static CATFillDictionary DicJDAIPTContainer##classe(classe::MetaObject(),JDAIPTContainer::MetaObject(),(void *)CreateTIEJDAIPTContainer##classe)



/* Macro used to link an implementation with an interface */
/* This TIE is chained on the implementation object */
#define TIEchain_JDAIPTContainer(classe) \
 \
 \
declare_TIE_JDAIPTContainer(classe) \
 \
 \
CATMetaClass * __stdcall TIEJDAIPTContainer##classe::MetaObject() \
{ \
   if (!meta_object) \
   { \
      meta_object=new CATMetaClass(&IID_JDAIPTContainer,"JDAIPTContainer",JDAIPTContainer::MetaObject(),classe::MetaObject(),TIEchain); \
   } \
   return(meta_object); \
} \
 \
 \
common_TIE_JDAIPTContainer(classe) \
 \
 \
/* creator function of the interface */ \
/* encapsulate the new */ \
CATImplementTIEchainCreation(JDAIPTContainer, classe) \
 \
/* to put information into the dictionary */ \
static CATFillDictionary DicJDAIPTContainer##classe(classe::MetaObject(),JDAIPTContainer::MetaObject(),(void *)CreateTIEJDAIPTContainer##classe)


/* Macro to switch between BOA and TIE at build time */ 
#ifdef CATSYS_BOA_IS_TIE
#define BOA_JDAIPTContainer(classe) TIE_JDAIPTContainer(classe)
#else
#define BOA_JDAIPTContainer(classe) CATImplementBOA(JDAIPTContainer, classe)
#endif

#endif
