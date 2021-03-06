// COPYRIGHT Dassault Systemes 2015
//===================================================================
//
// JDAEActivateWorkbench.cpp
// Provide implementation to interface
//    CATIAfrActivateWorkbench
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//  May 2015  Creation: Code generated by the CAA wizard  LuJunHome
//===================================================================
#include "JDAEActivateWorkbench.h"

//---------- Code generated by Jiangda CAAPlugin wizard

// System
#include "CATString.h"

// ProductStructure
#include "CATIProduct.h"

// ObjectModelerBase
#include "CATIContainer.h"
#include "CATIParmProvider.h"
#include "CATI3DVisuProvider.h"
#include "CATDocument.h"
#include "CATILinkableObject.h"

// ObjectSpecsModeler
#include "CATIUpdateProvider.h"
#include "CATIProviders.h"

// ObjectModelerNavigator
#include "CATINavigateProvider.h"

// Visualization
#include "CATIModelEvents.h"

//---------- End Code generated by Jiangda CAAPlugin wizard

#include "JDAIPTDocument.h"
#include "JDAIPTRoot.h"
#include "JDAIPTMemo.h"
#include "JDAIPTContainer.h"

#include "CATModify.h"
#include "CATCreate.h"

#include "JDAPTNavigProvider.h"
#include "JDAPT3DVisuProvider.h"
#include "JDAPTParmProvider.h"
#include "JDAPTUpdateProvider.h"

#include "iostream.h"
 
CATImplementClass(JDAEActivateWorkbench,
                  DataExtension,
                  CATBaseUnknown,
                  ASMPRODUCT );
 

//-----------------------------------------------------------------------------
// JDAEActivateWorkbench : constructor
//-----------------------------------------------------------------------------
JDAEActivateWorkbench::JDAEActivateWorkbench():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// JDAEActivateWorkbench : destructor
//-----------------------------------------------------------------------------
JDAEActivateWorkbench::~JDAEActivateWorkbench()
{
}
 
// Link the implementation to its interface
// ---------------------------------------



//TIE or TIEchain definitions
#include "TIE_CATIAfrActivateWorkbench.h"
TIE_CATIAfrActivateWorkbench( JDAEActivateWorkbench);


//Methods implementation

//-----------------------------------------------------------------------------
// Implements CATIAfrActivateWorkbench::GetInitialWorkbench
//-----------------------------------------------------------------------------
CATString & JDAEActivateWorkbench::GetInitialWorkbench ()
{
	HRESULT rc=E_FAIL;
	
	CATString *strName=new CATString();
	(*strName) = "";

	//////////////////////////////////////////////////////////////////////////
	//1. The current activate object is a Root Product ?
	//   为避免重复添加我们的Provider，所以我们仅在RootProduct时才添加
	//   我们的Provider
	//////////////////////////////////////////////////////////////////////////
	CATIProduct_var spiProductRoot=this;
	CATIProduct_var spiFatherProduct=NULL_var;
	if( !!spiProductRoot ) {
		spiFatherProduct = spiProductRoot->GetFatherProduct();
	}
	if( !!spiFatherProduct ) return (*strName);

	//////////////////////////////////////////////////////////////////////////
	//2. 检查当前Product文档，是否添加了我们的Provider
	//Get current document
	//////////////////////////////////////////////////////////////////////////
	CATILinkableObject_var spiLink=spiProductRoot;
	CATDocument *pDoc=NULL;
	if( !!spiLink ) {
		pDoc = spiLink->GetDocument();
	}
	
	CATIProviders *piProvidersOnDoc=NULL;
	if( !!pDoc ) {
		rc = pDoc->QueryInterface(IID_CATIProviders,(void **)&piProvidersOnDoc);
	}
	
	CATBoolean isFoundMyProvider=FALSE;
	if( SUCCEEDED(rc) && !!piProvidersOnDoc ) {
		CATLISTP(CATBaseUnknown) *pListProvider = new CATLISTP(CATBaseUnknown);

		// The NavigProvider
		rc = piProvidersOnDoc->ListProviders(JDAPTNavigProvider::ClassId(),&pListProvider);
		if( pListProvider->Size() > 0 ) {
			isFoundMyProvider = TRUE;
			piProvidersOnDoc->Release(); piProvidersOnDoc = NULL; 
		}

		delete pListProvider; pListProvider = NULL;
	}
	if( isFoundMyProvider ) return (*strName);

	//cout << "==> We will add my provider !!!!" << endl;

	//////////////////////////////////////////////////////////////////////////
	//3.In this product document, we can't found my provider,so we will add 
	//  my provider.
	//////////////////////////////////////////////////////////////////////////
	JDAPTNavigProvider *pJDANavigProvider=new JDAPTNavigProvider();
	rc = piProvidersOnDoc->AddProvider(CATINavigateProvider::ClassId(),pJDANavigProvider);

	JDAPT3DVisuProvider *pJDAVisuProvider=new JDAPT3DVisuProvider();
	rc = piProvidersOnDoc->AddProvider(CATI3DVisuProvider::ClassId(),pJDAVisuProvider);

	JDAPTParmProvider *pJDAParmProvider=new JDAPTParmProvider();
	rc = piProvidersOnDoc->AddProvider(CATIParmProvider::ClassId(),pJDAParmProvider);

	JDAPTUpdateProvider *pJDAUpdateProvider=new JDAPTUpdateProvider();
	rc = piProvidersOnDoc->AddProvider(CATIUpdateProvider::ClassId(),pJDAUpdateProvider);

	if( !!piProvidersOnDoc ) { piProvidersOnDoc->Release(); piProvidersOnDoc = NULL; }

	//////////////////////////////////////////////////////////////////////////
	//由于JDAPT3DVisuProvider视乎不起作用，所以才需要重新链接3DVisu Events
	//传递的链接层次,以下代码都是这个作用
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//4. Check which child have my container
	//////////////////////////////////////////////////////////////////////////
	CATListValCATBaseUnknown_var *pListChildProduct=spiProductRoot->GetAllChildren();
	int numChild=0;
	if( !pListChildProduct || (numChild=pListChildProduct->Size()) < 1 )  return (*strName);

	CATIProduct_var spiChildProductInst=NULL_var;
	CATIProduct_var spiChildProductRef=NULL_var;

	CATDocument *pDocChild=NULL;
	JDAIPTDocument *piMyDoc=NULL;
	CATIContainer *piMyContainer=NULL;
	JDAIPTContainer_var spiMyContainer=NULL_var;
	JDAIPTRoot *piMyRoot=NULL;
	CATIModelEvents_var spiEventsOnDocRoot=NULL_var;
	CATIModelEvents_var spiEventsOnMyRoot=NULL_var;

	CATListValCATBaseUnknown_var * pListChildMyRoot = NULL;

	for(int i=1;i<=numChild;i++) {
		spiChildProductInst = (*pListChildProduct)[i];
		spiChildProductRef = spiChildProductInst->GetReferenceProduct();

		spiLink = spiChildProductRef;
		pDocChild = spiLink->GetDocument();
		if( !(pDocChild->IsAKindOf("CATProduct")) ) continue;

		rc = pDocChild->QueryInterface(IID_JDAIPTDocument,(void **)&piMyDoc);
		if( FAILED(rc) || !piMyDoc ) continue;

		rc = piMyDoc->GetContainer(&piMyContainer);
		piMyDoc->Release(); piMyDoc = NULL;
		if( FAILED(rc) || !piMyContainer ) continue;

		spiMyContainer = piMyContainer;
		rc = spiMyContainer->GetRoot(&piMyRoot);
		if( SUCCEEDED(rc) && !!piMyRoot ) {
			spiEventsOnDocRoot = spiChildProductInst;
			spiEventsOnMyRoot = piMyRoot;
			spiEventsOnDocRoot->ConnectTo(spiEventsOnMyRoot);

			CATCreate myCreateEvent((CATBaseUnknown*)spiEventsOnMyRoot, (CATBaseUnknown*)spiEventsOnDocRoot);
			spiEventsOnDocRoot->Dispatch(myCreateEvent);

			//
			rc = piMyRoot->GetChildren(IID_JDAIPTMemo, pListChildMyRoot);
			if( !!pListChildMyRoot ) {
				int numChildMyRoot=pListChildMyRoot->Size();
				for(int j=1;j<=numChildMyRoot;j++) {
					spiEventsOnMyRoot->ConnectTo((*pListChildMyRoot)[j]);
				}

				delete pListChildMyRoot; pListChildMyRoot = NULL;
			}
			
			piMyRoot->Release(); piMyRoot = NULL;
		}
	}

	if( !!pListChildProduct ) { delete pListChildProduct; pListChildProduct = NULL; }

	return (*strName);
}

