#ifndef __TIE_JDAIPTMemoParmEvents
#define __TIE_JDAIPTMemoParmEvents

#include <string.h>
#include "CATBaseUnknown.h"
#include "CATMetaClass.h"
#include "CATMacForTie.h"
#include "JDAIPTMemoParmEvents.h"
#include "JS0DSPA.h"


#ifdef _WINDOWS_SOURCE
#define Exported __declspec(dllexport)
#define Imported __declspec(dllimport)
#else
#define Exported 
#define Imported 
#endif


/* To link an implementation with the interface JDAIPTMemoParmEvents */
#define declare_TIE_JDAIPTMemoParmEvents(classe) \
 \
 \
class TIEJDAIPTMemoParmEvents##classe : public JDAIPTMemoParmEvents \
{ \
   private: \
      CATDeclareCommonTIEMembers \
   public: \
      CATDeclareTIEMethods(JDAIPTMemoParmEvents, classe) \
      CATDeclareIUnknownMethodsForCATBaseUnknownTIE \
      CATDeclareIDispatchMethodsForCATBaseUnknownTIE \
      CATDeclareCATBaseUnknownMethodsForTIE \
      virtual void AddSubscribe (CATICkeParm_var &iParameterToObserve); \
      virtual void RemoveSubscribe ( CATICkeParm_var &iParameterToObserve); \
      virtual void OnChangeValueEvent (CATCallbackEvent iEvent, void* iFrom, CATNotification* iNotification, CATSubscriberData iInfo, CATCallback iCallback); \
};



#define ENVTIEdeclare_JDAIPTMemoParmEvents(ENVTIEName,ENVTIETypeLetter,ENVTIELetter) \
virtual void AddSubscribe (CATICkeParm_var &iParameterToObserve); \
virtual void RemoveSubscribe ( CATICkeParm_var &iParameterToObserve); \
virtual void OnChangeValueEvent (CATCallbackEvent iEvent, void* iFrom, CATNotification* iNotification, CATSubscriberData iInfo, CATCallback iCallback); \


#define ENVTIEdefine_JDAIPTMemoParmEvents(ENVTIEName,ENVTIETypeLetter,ENVTIELetter) \
void  ENVTIEName::AddSubscribe (CATICkeParm_var &iParameterToObserve) \
{ \
 (ENVTIECALL(JDAIPTMemoParmEvents,ENVTIETypeLetter,ENVTIELetter)AddSubscribe (iParameterToObserve)); \
} \
void  ENVTIEName::RemoveSubscribe ( CATICkeParm_var &iParameterToObserve) \
{ \
 (ENVTIECALL(JDAIPTMemoParmEvents,ENVTIETypeLetter,ENVTIELetter)RemoveSubscribe (iParameterToObserve)); \
} \
void  ENVTIEName::OnChangeValueEvent (CATCallbackEvent iEvent, void* iFrom, CATNotification* iNotification, CATSubscriberData iInfo, CATCallback iCallback) \
{ \
 (ENVTIECALL(JDAIPTMemoParmEvents,ENVTIETypeLetter,ENVTIELetter)OnChangeValueEvent (iEvent,iFrom,iNotification,iInfo,iCallback)); \
} \


/* Name of the TIE class */
#define class_TIE_JDAIPTMemoParmEvents(classe)    TIEJDAIPTMemoParmEvents##classe


/* Common methods inside a TIE */
#define common_TIE_JDAIPTMemoParmEvents(classe) \
 \
 \
/* Static initialization */ \
CATDefineCommonTIEMembers(JDAIPTMemoParmEvents, classe) \
 \
 \
CATImplementTIEMethods(JDAIPTMemoParmEvents, classe) \
CATImplementIUnknownMethodsForCATBaseUnknownTIE(JDAIPTMemoParmEvents, classe, 1) \
CATImplementIDispatchMethodsForCATBaseUnknownTIE(JDAIPTMemoParmEvents, classe) \
CATImplementCATBaseUnknownMethodsForTIE(JDAIPTMemoParmEvents, classe) \
 \
void  TIEJDAIPTMemoParmEvents##classe::AddSubscribe (CATICkeParm_var &iParameterToObserve) \
{ \
   ((classe *)Tie_Method(NecessaryData.ForTIE,ptstat))->AddSubscribe (iParameterToObserve); \
} \
void  TIEJDAIPTMemoParmEvents##classe::RemoveSubscribe ( CATICkeParm_var &iParameterToObserve) \
{ \
   ((classe *)Tie_Method(NecessaryData.ForTIE,ptstat))->RemoveSubscribe (iParameterToObserve); \
} \
void  TIEJDAIPTMemoParmEvents##classe::OnChangeValueEvent (CATCallbackEvent iEvent, void* iFrom, CATNotification* iNotification, CATSubscriberData iInfo, CATCallback iCallback) \
{ \
   ((classe *)Tie_Method(NecessaryData.ForTIE,ptstat))->OnChangeValueEvent (iEvent,iFrom,iNotification,iInfo,iCallback); \
} \



/* Macro used to link an implementation with an interface */
#define TIE_JDAIPTMemoParmEvents(classe) \
 \
 \
declare_TIE_JDAIPTMemoParmEvents(classe) \
 \
 \
CATMetaClass * __stdcall TIEJDAIPTMemoParmEvents##classe::MetaObject() \
{ \
   if (!meta_object) \
   { \
      meta_object=new CATMetaClass(&IID_JDAIPTMemoParmEvents,"JDAIPTMemoParmEvents",JDAIPTMemoParmEvents::MetaObject(),classe::MetaObject(),TIE); \
   } \
   return(meta_object); \
} \
 \
 \
common_TIE_JDAIPTMemoParmEvents(classe) \
 \
 \
/* creator function of the interface */ \
/* encapsulate the new */ \
CATImplementTIECreation(JDAIPTMemoParmEvents, classe) \
 \
/* to put information into the dictionary */ \
static CATFillDictionary DicJDAIPTMemoParmEvents##classe(classe::MetaObject(),JDAIPTMemoParmEvents::MetaObject(),(void *)CreateTIEJDAIPTMemoParmEvents##classe)



/* Macro used to link an implementation with an interface */
/* This TIE is chained on the implementation object */
#define TIEchain_JDAIPTMemoParmEvents(classe) \
 \
 \
declare_TIE_JDAIPTMemoParmEvents(classe) \
 \
 \
CATMetaClass * __stdcall TIEJDAIPTMemoParmEvents##classe::MetaObject() \
{ \
   if (!meta_object) \
   { \
      meta_object=new CATMetaClass(&IID_JDAIPTMemoParmEvents,"JDAIPTMemoParmEvents",JDAIPTMemoParmEvents::MetaObject(),classe::MetaObject(),TIEchain); \
   } \
   return(meta_object); \
} \
 \
 \
common_TIE_JDAIPTMemoParmEvents(classe) \
 \
 \
/* creator function of the interface */ \
/* encapsulate the new */ \
CATImplementTIEchainCreation(JDAIPTMemoParmEvents, classe) \
 \
/* to put information into the dictionary */ \
static CATFillDictionary DicJDAIPTMemoParmEvents##classe(classe::MetaObject(),JDAIPTMemoParmEvents::MetaObject(),(void *)CreateTIEJDAIPTMemoParmEvents##classe)


/* Macro to switch between BOA and TIE at build time */ 
#ifdef CATSYS_BOA_IS_TIE
#define BOA_JDAIPTMemoParmEvents(classe) TIE_JDAIPTMemoParmEvents(classe)
#else
#define BOA_JDAIPTMemoParmEvents(classe) CATImplementBOA(JDAIPTMemoParmEvents, classe)
#endif

#endif
