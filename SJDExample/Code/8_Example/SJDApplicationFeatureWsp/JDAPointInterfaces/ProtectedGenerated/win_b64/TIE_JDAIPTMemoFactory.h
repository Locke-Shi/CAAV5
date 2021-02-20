#ifndef __TIE_JDAIPTMemoFactory
#define __TIE_JDAIPTMemoFactory

#include <string.h>
#include "CATBaseUnknown.h"
#include "CATMetaClass.h"
#include "CATMacForTie.h"
#include "JDAIPTMemoFactory.h"
#include "JS0DSPA.h"


#ifdef _WINDOWS_SOURCE
#define Exported __declspec(dllexport)
#define Imported __declspec(dllimport)
#else
#define Exported 
#define Imported 
#endif


/* To link an implementation with the interface JDAIPTMemoFactory */
#define declare_TIE_JDAIPTMemoFactory(classe) \
 \
 \
class TIEJDAIPTMemoFactory##classe : public JDAIPTMemoFactory \
{ \
   private: \
      CATDeclareCommonTIEMembers \
   public: \
      CATDeclareTIEMethods(JDAIPTMemoFactory, classe) \
      CATDeclareIUnknownMethodsForCATBaseUnknownTIE \
      CATDeclareIDispatchMethodsForCATBaseUnknownTIE \
      CATDeclareCATBaseUnknownMethodsForTIE \
      virtual HRESULT CreateJDAPoint(double iX,double iY,double iZ,JDAIPTMemo  **oPT) ; \
};



#define ENVTIEdeclare_JDAIPTMemoFactory(ENVTIEName,ENVTIETypeLetter,ENVTIELetter) \
virtual HRESULT CreateJDAPoint(double iX,double iY,double iZ,JDAIPTMemo  **oPT) ; \


#define ENVTIEdefine_JDAIPTMemoFactory(ENVTIEName,ENVTIETypeLetter,ENVTIELetter) \
HRESULT  ENVTIEName::CreateJDAPoint(double iX,double iY,double iZ,JDAIPTMemo  **oPT)  \
{ \
return (ENVTIECALL(JDAIPTMemoFactory,ENVTIETypeLetter,ENVTIELetter)CreateJDAPoint(iX,iY,iZ,oPT)); \
} \


/* Name of the TIE class */
#define class_TIE_JDAIPTMemoFactory(classe)    TIEJDAIPTMemoFactory##classe


/* Common methods inside a TIE */
#define common_TIE_JDAIPTMemoFactory(classe) \
 \
 \
/* Static initialization */ \
CATDefineCommonTIEMembers(JDAIPTMemoFactory, classe) \
 \
 \
CATImplementTIEMethods(JDAIPTMemoFactory, classe) \
CATImplementIUnknownMethodsForCATBaseUnknownTIE(JDAIPTMemoFactory, classe, 1) \
CATImplementIDispatchMethodsForCATBaseUnknownTIE(JDAIPTMemoFactory, classe) \
CATImplementCATBaseUnknownMethodsForTIE(JDAIPTMemoFactory, classe) \
 \
HRESULT  TIEJDAIPTMemoFactory##classe::CreateJDAPoint(double iX,double iY,double iZ,JDAIPTMemo  **oPT)  \
{ \
   return(((classe *)Tie_Method(NecessaryData.ForTIE,ptstat))->CreateJDAPoint(iX,iY,iZ,oPT)); \
} \



/* Macro used to link an implementation with an interface */
#define TIE_JDAIPTMemoFactory(classe) \
 \
 \
declare_TIE_JDAIPTMemoFactory(classe) \
 \
 \
CATMetaClass * __stdcall TIEJDAIPTMemoFactory##classe::MetaObject() \
{ \
   if (!meta_object) \
   { \
      meta_object=new CATMetaClass(&IID_JDAIPTMemoFactory,"JDAIPTMemoFactory",JDAIPTMemoFactory::MetaObject(),classe::MetaObject(),TIE); \
   } \
   return(meta_object); \
} \
 \
 \
common_TIE_JDAIPTMemoFactory(classe) \
 \
 \
/* creator function of the interface */ \
/* encapsulate the new */ \
CATImplementTIECreation(JDAIPTMemoFactory, classe) \
 \
/* to put information into the dictionary */ \
static CATFillDictionary DicJDAIPTMemoFactory##classe(classe::MetaObject(),JDAIPTMemoFactory::MetaObject(),(void *)CreateTIEJDAIPTMemoFactory##classe)



/* Macro used to link an implementation with an interface */
/* This TIE is chained on the implementation object */
#define TIEchain_JDAIPTMemoFactory(classe) \
 \
 \
declare_TIE_JDAIPTMemoFactory(classe) \
 \
 \
CATMetaClass * __stdcall TIEJDAIPTMemoFactory##classe::MetaObject() \
{ \
   if (!meta_object) \
   { \
      meta_object=new CATMetaClass(&IID_JDAIPTMemoFactory,"JDAIPTMemoFactory",JDAIPTMemoFactory::MetaObject(),classe::MetaObject(),TIEchain); \
   } \
   return(meta_object); \
} \
 \
 \
common_TIE_JDAIPTMemoFactory(classe) \
 \
 \
/* creator function of the interface */ \
/* encapsulate the new */ \
CATImplementTIEchainCreation(JDAIPTMemoFactory, classe) \
 \
/* to put information into the dictionary */ \
static CATFillDictionary DicJDAIPTMemoFactory##classe(classe::MetaObject(),JDAIPTMemoFactory::MetaObject(),(void *)CreateTIEJDAIPTMemoFactory##classe)


/* Macro to switch between BOA and TIE at build time */ 
#ifdef CATSYS_BOA_IS_TIE
#define BOA_JDAIPTMemoFactory(classe) TIE_JDAIPTMemoFactory(classe)
#else
#define BOA_JDAIPTMemoFactory(classe) CATImplementBOA(JDAIPTMemoFactory, classe)
#endif

#endif
