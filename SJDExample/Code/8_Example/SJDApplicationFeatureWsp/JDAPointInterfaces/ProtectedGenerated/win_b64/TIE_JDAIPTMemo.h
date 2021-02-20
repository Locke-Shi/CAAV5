#ifndef __TIE_JDAIPTMemo
#define __TIE_JDAIPTMemo

#include <string.h>
#include "CATBaseUnknown.h"
#include "CATMetaClass.h"
#include "CATMacForTie.h"
#include "JDAIPTMemo.h"
#include "JS0DSPA.h"


#ifdef _WINDOWS_SOURCE
#define Exported __declspec(dllexport)
#define Imported __declspec(dllimport)
#else
#define Exported 
#define Imported 
#endif


/* To link an implementation with the interface JDAIPTMemo */
#define declare_TIE_JDAIPTMemo(classe) \
 \
 \
class TIEJDAIPTMemo##classe : public JDAIPTMemo \
{ \
   private: \
      CATDeclareCommonTIEMembers \
   public: \
      CATDeclareTIEMethods(JDAIPTMemo, classe) \
      CATDeclareIUnknownMethodsForCATBaseUnknownTIE \
      CATDeclareIDispatchMethodsForCATBaseUnknownTIE \
      CATDeclareCATBaseUnknownMethodsForTIE \
      virtual HRESULT GetX(double &oX) ; \
      virtual HRESULT SetX(double iX) ; \
      virtual HRESULT GetY(double &oY) ; \
      virtual HRESULT SetY(double iY) ; \
      virtual HRESULT GetZ(double &oZ) ; \
      virtual HRESULT SetZ(double iZ) ; \
};



#define ENVTIEdeclare_JDAIPTMemo(ENVTIEName,ENVTIETypeLetter,ENVTIELetter) \
virtual HRESULT GetX(double &oX) ; \
virtual HRESULT SetX(double iX) ; \
virtual HRESULT GetY(double &oY) ; \
virtual HRESULT SetY(double iY) ; \
virtual HRESULT GetZ(double &oZ) ; \
virtual HRESULT SetZ(double iZ) ; \


#define ENVTIEdefine_JDAIPTMemo(ENVTIEName,ENVTIETypeLetter,ENVTIELetter) \
HRESULT  ENVTIEName::GetX(double &oX)  \
{ \
return (ENVTIECALL(JDAIPTMemo,ENVTIETypeLetter,ENVTIELetter)GetX(oX)); \
} \
HRESULT  ENVTIEName::SetX(double iX)  \
{ \
return (ENVTIECALL(JDAIPTMemo,ENVTIETypeLetter,ENVTIELetter)SetX(iX)); \
} \
HRESULT  ENVTIEName::GetY(double &oY)  \
{ \
return (ENVTIECALL(JDAIPTMemo,ENVTIETypeLetter,ENVTIELetter)GetY(oY)); \
} \
HRESULT  ENVTIEName::SetY(double iY)  \
{ \
return (ENVTIECALL(JDAIPTMemo,ENVTIETypeLetter,ENVTIELetter)SetY(iY)); \
} \
HRESULT  ENVTIEName::GetZ(double &oZ)  \
{ \
return (ENVTIECALL(JDAIPTMemo,ENVTIETypeLetter,ENVTIELetter)GetZ(oZ)); \
} \
HRESULT  ENVTIEName::SetZ(double iZ)  \
{ \
return (ENVTIECALL(JDAIPTMemo,ENVTIETypeLetter,ENVTIELetter)SetZ(iZ)); \
} \


/* Name of the TIE class */
#define class_TIE_JDAIPTMemo(classe)    TIEJDAIPTMemo##classe


/* Common methods inside a TIE */
#define common_TIE_JDAIPTMemo(classe) \
 \
 \
/* Static initialization */ \
CATDefineCommonTIEMembers(JDAIPTMemo, classe) \
 \
 \
CATImplementTIEMethods(JDAIPTMemo, classe) \
CATImplementIUnknownMethodsForCATBaseUnknownTIE(JDAIPTMemo, classe, 1) \
CATImplementIDispatchMethodsForCATBaseUnknownTIE(JDAIPTMemo, classe) \
CATImplementCATBaseUnknownMethodsForTIE(JDAIPTMemo, classe) \
 \
HRESULT  TIEJDAIPTMemo##classe::GetX(double &oX)  \
{ \
   return(((classe *)Tie_Method(NecessaryData.ForTIE,ptstat))->GetX(oX)); \
} \
HRESULT  TIEJDAIPTMemo##classe::SetX(double iX)  \
{ \
   return(((classe *)Tie_Method(NecessaryData.ForTIE,ptstat))->SetX(iX)); \
} \
HRESULT  TIEJDAIPTMemo##classe::GetY(double &oY)  \
{ \
   return(((classe *)Tie_Method(NecessaryData.ForTIE,ptstat))->GetY(oY)); \
} \
HRESULT  TIEJDAIPTMemo##classe::SetY(double iY)  \
{ \
   return(((classe *)Tie_Method(NecessaryData.ForTIE,ptstat))->SetY(iY)); \
} \
HRESULT  TIEJDAIPTMemo##classe::GetZ(double &oZ)  \
{ \
   return(((classe *)Tie_Method(NecessaryData.ForTIE,ptstat))->GetZ(oZ)); \
} \
HRESULT  TIEJDAIPTMemo##classe::SetZ(double iZ)  \
{ \
   return(((classe *)Tie_Method(NecessaryData.ForTIE,ptstat))->SetZ(iZ)); \
} \



/* Macro used to link an implementation with an interface */
#define TIE_JDAIPTMemo(classe) \
 \
 \
declare_TIE_JDAIPTMemo(classe) \
 \
 \
CATMetaClass * __stdcall TIEJDAIPTMemo##classe::MetaObject() \
{ \
   if (!meta_object) \
   { \
      meta_object=new CATMetaClass(&IID_JDAIPTMemo,"JDAIPTMemo",JDAIPTMemo::MetaObject(),classe::MetaObject(),TIE); \
   } \
   return(meta_object); \
} \
 \
 \
common_TIE_JDAIPTMemo(classe) \
 \
 \
/* creator function of the interface */ \
/* encapsulate the new */ \
CATImplementTIECreation(JDAIPTMemo, classe) \
 \
/* to put information into the dictionary */ \
static CATFillDictionary DicJDAIPTMemo##classe(classe::MetaObject(),JDAIPTMemo::MetaObject(),(void *)CreateTIEJDAIPTMemo##classe)



/* Macro used to link an implementation with an interface */
/* This TIE is chained on the implementation object */
#define TIEchain_JDAIPTMemo(classe) \
 \
 \
declare_TIE_JDAIPTMemo(classe) \
 \
 \
CATMetaClass * __stdcall TIEJDAIPTMemo##classe::MetaObject() \
{ \
   if (!meta_object) \
   { \
      meta_object=new CATMetaClass(&IID_JDAIPTMemo,"JDAIPTMemo",JDAIPTMemo::MetaObject(),classe::MetaObject(),TIEchain); \
   } \
   return(meta_object); \
} \
 \
 \
common_TIE_JDAIPTMemo(classe) \
 \
 \
/* creator function of the interface */ \
/* encapsulate the new */ \
CATImplementTIEchainCreation(JDAIPTMemo, classe) \
 \
/* to put information into the dictionary */ \
static CATFillDictionary DicJDAIPTMemo##classe(classe::MetaObject(),JDAIPTMemo::MetaObject(),(void *)CreateTIEJDAIPTMemo##classe)


/* Macro to switch between BOA and TIE at build time */ 
#ifdef CATSYS_BOA_IS_TIE
#define BOA_JDAIPTMemo(classe) TIE_JDAIPTMemo(classe)
#else
#define BOA_JDAIPTMemo(classe) CATImplementBOA(JDAIPTMemo, classe)
#endif

#endif
