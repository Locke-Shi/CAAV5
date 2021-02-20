#ifndef __TIE_JDAIPTRoot
#define __TIE_JDAIPTRoot

#include <string.h>
#include "CATBaseUnknown.h"
#include "CATMetaClass.h"
#include "CATMacForTie.h"
#include "JDAIPTRoot.h"
#include "JS0DSPA.h"


#ifdef _WINDOWS_SOURCE
#define Exported __declspec(dllexport)
#define Imported __declspec(dllimport)
#else
#define Exported 
#define Imported 
#endif


/* To link an implementation with the interface JDAIPTRoot */
#define declare_TIE_JDAIPTRoot(classe) \
 \
 \
class TIEJDAIPTRoot##classe : public JDAIPTRoot \
{ \
   private: \
      CATDeclareCommonTIEMembers \
   public: \
      CATDeclareTIEMethods(JDAIPTRoot, classe) \
      CATDeclareIUnknownMethodsForCATBaseUnknownTIE \
      CATDeclareIDispatchMethodsForCATBaseUnknownTIE \
      CATDeclareCATBaseUnknownMethodsForTIE \
      virtual HRESULT AddChild (CATISpecObject *ipiFeature); \
      virtual HRESULT RemoveChild (CATISpecObject *ipiFeature); \
      virtual HRESULT GetChildren (const IID &iItfIID, CATListValCATBaseUnknown_var *& oList); \
};



#define ENVTIEdeclare_JDAIPTRoot(ENVTIEName,ENVTIETypeLetter,ENVTIELetter) \
virtual HRESULT AddChild (CATISpecObject *ipiFeature); \
virtual HRESULT RemoveChild (CATISpecObject *ipiFeature); \
virtual HRESULT GetChildren (const IID &iItfIID, CATListValCATBaseUnknown_var *& oList); \


#define ENVTIEdefine_JDAIPTRoot(ENVTIEName,ENVTIETypeLetter,ENVTIELetter) \
HRESULT  ENVTIEName::AddChild (CATISpecObject *ipiFeature) \
{ \
return (ENVTIECALL(JDAIPTRoot,ENVTIETypeLetter,ENVTIELetter)AddChild (ipiFeature)); \
} \
HRESULT  ENVTIEName::RemoveChild (CATISpecObject *ipiFeature) \
{ \
return (ENVTIECALL(JDAIPTRoot,ENVTIETypeLetter,ENVTIELetter)RemoveChild (ipiFeature)); \
} \
HRESULT  ENVTIEName::GetChildren (const IID &iItfIID, CATListValCATBaseUnknown_var *& oList) \
{ \
return (ENVTIECALL(JDAIPTRoot,ENVTIETypeLetter,ENVTIELetter)GetChildren (iItfIID,oList)); \
} \


/* Name of the TIE class */
#define class_TIE_JDAIPTRoot(classe)    TIEJDAIPTRoot##classe


/* Common methods inside a TIE */
#define common_TIE_JDAIPTRoot(classe) \
 \
 \
/* Static initialization */ \
CATDefineCommonTIEMembers(JDAIPTRoot, classe) \
 \
 \
CATImplementTIEMethods(JDAIPTRoot, classe) \
CATImplementIUnknownMethodsForCATBaseUnknownTIE(JDAIPTRoot, classe, 1) \
CATImplementIDispatchMethodsForCATBaseUnknownTIE(JDAIPTRoot, classe) \
CATImplementCATBaseUnknownMethodsForTIE(JDAIPTRoot, classe) \
 \
HRESULT  TIEJDAIPTRoot##classe::AddChild (CATISpecObject *ipiFeature) \
{ \
   return(((classe *)Tie_Method(NecessaryData.ForTIE,ptstat))->AddChild (ipiFeature)); \
} \
HRESULT  TIEJDAIPTRoot##classe::RemoveChild (CATISpecObject *ipiFeature) \
{ \
   return(((classe *)Tie_Method(NecessaryData.ForTIE,ptstat))->RemoveChild (ipiFeature)); \
} \
HRESULT  TIEJDAIPTRoot##classe::GetChildren (const IID &iItfIID, CATListValCATBaseUnknown_var *& oList) \
{ \
   return(((classe *)Tie_Method(NecessaryData.ForTIE,ptstat))->GetChildren (iItfIID,oList)); \
} \



/* Macro used to link an implementation with an interface */
#define TIE_JDAIPTRoot(classe) \
 \
 \
declare_TIE_JDAIPTRoot(classe) \
 \
 \
CATMetaClass * __stdcall TIEJDAIPTRoot##classe::MetaObject() \
{ \
   if (!meta_object) \
   { \
      meta_object=new CATMetaClass(&IID_JDAIPTRoot,"JDAIPTRoot",JDAIPTRoot::MetaObject(),classe::MetaObject(),TIE); \
   } \
   return(meta_object); \
} \
 \
 \
common_TIE_JDAIPTRoot(classe) \
 \
 \
/* creator function of the interface */ \
/* encapsulate the new */ \
CATImplementTIECreation(JDAIPTRoot, classe) \
 \
/* to put information into the dictionary */ \
static CATFillDictionary DicJDAIPTRoot##classe(classe::MetaObject(),JDAIPTRoot::MetaObject(),(void *)CreateTIEJDAIPTRoot##classe)



/* Macro used to link an implementation with an interface */
/* This TIE is chained on the implementation object */
#define TIEchain_JDAIPTRoot(classe) \
 \
 \
declare_TIE_JDAIPTRoot(classe) \
 \
 \
CATMetaClass * __stdcall TIEJDAIPTRoot##classe::MetaObject() \
{ \
   if (!meta_object) \
   { \
      meta_object=new CATMetaClass(&IID_JDAIPTRoot,"JDAIPTRoot",JDAIPTRoot::MetaObject(),classe::MetaObject(),TIEchain); \
   } \
   return(meta_object); \
} \
 \
 \
common_TIE_JDAIPTRoot(classe) \
 \
 \
/* creator function of the interface */ \
/* encapsulate the new */ \
CATImplementTIEchainCreation(JDAIPTRoot, classe) \
 \
/* to put information into the dictionary */ \
static CATFillDictionary DicJDAIPTRoot##classe(classe::MetaObject(),JDAIPTRoot::MetaObject(),(void *)CreateTIEJDAIPTRoot##classe)


/* Macro to switch between BOA and TIE at build time */ 
#ifdef CATSYS_BOA_IS_TIE
#define BOA_JDAIPTRoot(classe) TIE_JDAIPTRoot(classe)
#else
#define BOA_JDAIPTRoot(classe) CATImplementBOA(JDAIPTRoot, classe)
#endif

#endif
