#ifndef __TIE_JDAIPTRootFactory
#define __TIE_JDAIPTRootFactory

#include <string.h>
#include "CATBaseUnknown.h"
#include "CATMetaClass.h"
#include "CATMacForTie.h"
#include "JDAIPTRootFactory.h"
#include "JS0DSPA.h"


#ifdef _WINDOWS_SOURCE
#define Exported __declspec(dllexport)
#define Imported __declspec(dllimport)
#else
#define Exported 
#define Imported 
#endif


/* To link an implementation with the interface JDAIPTRootFactory */
#define declare_TIE_JDAIPTRootFactory(classe) \
 \
 \
class TIEJDAIPTRootFactory##classe : public JDAIPTRootFactory \
{ \
   private: \
      CATDeclareCommonTIEMembers \
   public: \
      CATDeclareTIEMethods(JDAIPTRootFactory, classe) \
      CATDeclareIUnknownMethodsForCATBaseUnknownTIE \
      CATDeclareIDispatchMethodsForCATBaseUnknownTIE \
      CATDeclareCATBaseUnknownMethodsForTIE \
      virtual HRESULT CreateRoot (JDAIPTRoot **opiRoot) ; \
};



#define ENVTIEdeclare_JDAIPTRootFactory(ENVTIEName,ENVTIETypeLetter,ENVTIELetter) \
virtual HRESULT CreateRoot (JDAIPTRoot **opiRoot) ; \


#define ENVTIEdefine_JDAIPTRootFactory(ENVTIEName,ENVTIETypeLetter,ENVTIELetter) \
HRESULT  ENVTIEName::CreateRoot (JDAIPTRoot **opiRoot)  \
{ \
return (ENVTIECALL(JDAIPTRootFactory,ENVTIETypeLetter,ENVTIELetter)CreateRoot (opiRoot)); \
} \


/* Name of the TIE class */
#define class_TIE_JDAIPTRootFactory(classe)    TIEJDAIPTRootFactory##classe


/* Common methods inside a TIE */
#define common_TIE_JDAIPTRootFactory(classe) \
 \
 \
/* Static initialization */ \
CATDefineCommonTIEMembers(JDAIPTRootFactory, classe) \
 \
 \
CATImplementTIEMethods(JDAIPTRootFactory, classe) \
CATImplementIUnknownMethodsForCATBaseUnknownTIE(JDAIPTRootFactory, classe, 1) \
CATImplementIDispatchMethodsForCATBaseUnknownTIE(JDAIPTRootFactory, classe) \
CATImplementCATBaseUnknownMethodsForTIE(JDAIPTRootFactory, classe) \
 \
HRESULT  TIEJDAIPTRootFactory##classe::CreateRoot (JDAIPTRoot **opiRoot)  \
{ \
   return(((classe *)Tie_Method(NecessaryData.ForTIE,ptstat))->CreateRoot (opiRoot)); \
} \



/* Macro used to link an implementation with an interface */
#define TIE_JDAIPTRootFactory(classe) \
 \
 \
declare_TIE_JDAIPTRootFactory(classe) \
 \
 \
CATMetaClass * __stdcall TIEJDAIPTRootFactory##classe::MetaObject() \
{ \
   if (!meta_object) \
   { \
      meta_object=new CATMetaClass(&IID_JDAIPTRootFactory,"JDAIPTRootFactory",JDAIPTRootFactory::MetaObject(),classe::MetaObject(),TIE); \
   } \
   return(meta_object); \
} \
 \
 \
common_TIE_JDAIPTRootFactory(classe) \
 \
 \
/* creator function of the interface */ \
/* encapsulate the new */ \
CATImplementTIECreation(JDAIPTRootFactory, classe) \
 \
/* to put information into the dictionary */ \
static CATFillDictionary DicJDAIPTRootFactory##classe(classe::MetaObject(),JDAIPTRootFactory::MetaObject(),(void *)CreateTIEJDAIPTRootFactory##classe)



/* Macro used to link an implementation with an interface */
/* This TIE is chained on the implementation object */
#define TIEchain_JDAIPTRootFactory(classe) \
 \
 \
declare_TIE_JDAIPTRootFactory(classe) \
 \
 \
CATMetaClass * __stdcall TIEJDAIPTRootFactory##classe::MetaObject() \
{ \
   if (!meta_object) \
   { \
      meta_object=new CATMetaClass(&IID_JDAIPTRootFactory,"JDAIPTRootFactory",JDAIPTRootFactory::MetaObject(),classe::MetaObject(),TIEchain); \
   } \
   return(meta_object); \
} \
 \
 \
common_TIE_JDAIPTRootFactory(classe) \
 \
 \
/* creator function of the interface */ \
/* encapsulate the new */ \
CATImplementTIEchainCreation(JDAIPTRootFactory, classe) \
 \
/* to put information into the dictionary */ \
static CATFillDictionary DicJDAIPTRootFactory##classe(classe::MetaObject(),JDAIPTRootFactory::MetaObject(),(void *)CreateTIEJDAIPTRootFactory##classe)


/* Macro to switch between BOA and TIE at build time */ 
#ifdef CATSYS_BOA_IS_TIE
#define BOA_JDAIPTRootFactory(classe) TIE_JDAIPTRootFactory(classe)
#else
#define BOA_JDAIPTRootFactory(classe) CATImplementBOA(JDAIPTRootFactory, classe)
#endif

#endif
