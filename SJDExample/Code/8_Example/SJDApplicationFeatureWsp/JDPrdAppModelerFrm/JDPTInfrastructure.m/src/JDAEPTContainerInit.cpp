// COPYRIGHT Dassault Systemes 2009
//===================================================================
//
// JDAEPTContainerInit.cpp
// Provide implementation to interface
//    CATInit
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//  Apr 2009  Creation: Code generated by the CAA wizard  LuJun
//===================================================================
#include "JDAEPTContainerInit.h"

//---------- Code generated by Jiangda CAAPlugin wizard

// ApplicationFrame
#include "CATFrmEditor.h"

// VisualizationBase
#include "CATPathElement.h"

// ProductStructure
#include "CATIProduct.h"

// ObjectModelerNavigator
#include "CATIRedrawEvent.h"

// System
#include "CATUnicodeString.h"
#include "CATBaseUnknown.h"

// Visualization
#include "CATCreate.h"

// ObjectSpecsModeler
#include "CATISpecObject.h"

//---------- End Code generated by Jiangda CAAPlugin wizard

#include "CATILinkableObject.h"
#include "CATIProviders.h"
#include "CATDocument.h"
#include "JDAPTNavigProvider.h"
#include "CATINavigateProvider.h"
#include "JDAPT3DVisuProvider.h"
#include "JDAPTParmProvider.h"
#include "CATI3DVisuProvider.h"
#include "CATIParmProvider.h"
#include "JDAPTUpdateProvider.h"
#include "CATIUpdateProvider.h"

#include "JDAIPTRoot.h"
#include "JDAIPTContainer.h"
#include "JDAIPTMemo.h"
#include "CATIDocRoots.h"
#include "CATIModelEvents.h"
#include "SpecBindNativeFormat.h"

#include "CATISpecAttrKey.h"
#include "CATISpecAttrAccess.h"
#include "CATICkeParm.h"

#include "JDAIPTMemoParmEvents.h"

//#include "CATCreate.h"


#include "iostream.h"


CATImplementClass(JDAEPTContainerInit,
                  DataExtension,
                  CATBaseUnknown,
                  JDAPTContainer );
 

//-----------------------------------------------------------------------------
// JDAEPTContainerInit : constructor
//-----------------------------------------------------------------------------
JDAEPTContainerInit::JDAEPTContainerInit():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// JDAEPTContainerInit : destructor
//-----------------------------------------------------------------------------
JDAEPTContainerInit::~JDAEPTContainerInit()
{
}
 
// Link the implementation to its interface
// ---------------------------------------



//TIE or TIEchain definitions
#include "TIE_CATInit.h"
TIE_CATInit( JDAEPTContainerInit);


//Methods implementation

//-----------------------------------------------------------------------------
// Implements CATInit::Init
//-----------------------------------------------------------------------------
void JDAEPTContainerInit::Init (CATBoolean  iDestroyExistingData)
{
	//cout <<"==> Now we are in JDAEPTContainerInit::Init  !" << endl;
	HRESULT hr=E_FAIL;

	//1. Retrieve the document
	// (Done in exercise navigation)
	// Use interface CATILinkableObject
	CATILinkableObject_var spiLinkOnDocument = this;
	CATDocument *pDocument = NULL;
	if( !!spiLinkOnDocument ) {
		pDocument = spiLinkOnDocument->GetDocument();
	}

	//2. Declare the providers
	// (Done in exercise navigation)
	// Retrieve the interface CATIProviders on the document
	CATIProviders *piProvidersOnDocument = NULL;
	if( !!pDocument ) {
		hr = pDocument -> QueryInterface(IID_CATIProviders, (void**) &piProvidersOnDocument);
	}

	//Check the document have my provider ?
	CATBoolean isFoundMyProvider=FALSE;
	if( SUCCEEDED(hr) && !!piProvidersOnDocument ) {
		CATLISTP(CATBaseUnknown) *pListProvider = new CATLISTP(CATBaseUnknown);

		// The my NavigProvider
		hr = piProvidersOnDocument->ListProviders(JDAPTNavigProvider::ClassId(),&pListProvider);
		if( SUCCEEDED(hr) && !!pListProvider && pListProvider->Size() > 0 ) {
			isFoundMyProvider = TRUE;
			piProvidersOnDocument->Release(); piProvidersOnDocument = NULL; 
		}

		if( !!pListProvider ) { delete pListProvider; pListProvider = NULL; }
	}

	if( !!piProvidersOnDocument && !isFoundMyProvider ) {
		//2.1 Declare a navigation provider
		// (Done in exercise navigation)
		// Create an instance of TSTAnoNavigProvider
		// Add it to the providers
		JDAPTNavigProvider *pNavigProvider = new JDAPTNavigProvider();
		hr = piProvidersOnDocument -> AddProvider (CATINavigateProvider::ClassId(), pNavigProvider);
		pNavigProvider->Release();  pNavigProvider = NULL;

		//2.2 Declare a visualization provider
		// (Done in exercise 3D Visualization)
		// Create an instance of TSTAno3DVisuProvider
		// Add it to the providers
		JDAPT3DVisuProvider *p3DVisuProvider = new JDAPT3DVisuProvider();
		hr = piProvidersOnDocument -> AddProvider (CATI3DVisuProvider::ClassId(), p3DVisuProvider);
		p3DVisuProvider->Release();  p3DVisuProvider = NULL;

		//2.3 Declare a parameter provider
		// (Done in exercise parameters)
		// Create an instance of TSTAnoParmProvider
		// Add it to the providers
		JDAPTParmProvider *pParmProvider = new JDAPTParmProvider();
		hr = piProvidersOnDocument -> AddProvider (CATIParmProvider::ClassId(), pParmProvider);
		pParmProvider->Release();  pParmProvider = NULL;

		//2.4 Declare an update provider
		// (Done in exercise parameters)
		// Create an instance of TSTAnoUpdateProvider
		// Add it to the providers
		JDAPTUpdateProvider *pUpdateProvider = new JDAPTUpdateProvider();
		hr = piProvidersOnDocument -> AddProvider (CATIUpdateProvider::ClassId(), pUpdateProvider);
		pUpdateProvider->Release();  pUpdateProvider = NULL;

		piProvidersOnDocument->Release();		piProvidersOnDocument = NULL;
	}
	
	//3. Connect the root product to the JDAPT root
	// (Done in exercise 3D Visualization)

	//Retrieve the root object for annotations
	// use interface TSTIAnoContainer on the container
	JDAIPTRoot *piAnoRoot = NULL;
	JDAIPTContainer *piAnoContainer = NULL;
	hr = this->QueryInterface(IID_JDAIPTContainer, (void**)&piAnoContainer);
	if (SUCCEEDED(hr)) {
		hr = piAnoContainer->GetRoot(&piAnoRoot);
		piAnoContainer->Release();		piAnoContainer = NULL;
	}

	//////////////////////////////////////////////////////////////////////////
	//As the applicative root has been created, we must send a visu
	// event and refresh the graph
	//////////////////////////////////////////////////////////////////////////
	// Get current active node
	CATIProduct_var spiCurrentProduct=NULL_var;
	CATFrmEditor *pEditor = CATFrmEditor::GetCurrentEditor();
	if( !!pEditor ) {
		CATPathElement activePath = pEditor->GetUIActiveObject();
		spiCurrentProduct=activePath.FindElement(IID_CATIProduct);
	}
	else {
		hr = GetRootProduct(spiLinkOnDocument,spiCurrentProduct);
	}
	
	//////////////////////////////////////////////////////////////////////////
	// For Navigation
	//////////////////////////////////////////////////////////////////////////
	CATIRedrawEvent_var spRedraw = spiCurrentProduct;
	  //Refresh the graph -> will call the provider
	if( !!spRedraw ) { spRedraw->Redraw(); }

	//////////////////////////////////////////////////////////////////////////
	// For 3D Visualization
	//////////////////////////////////////////////////////////////////////////
	// Check the active node is the root node or child node
	CATIModelEvents_var spiEventsOnAppRoot=piAnoRoot;
	CATIModelEvents_var spiEventsOnDocRoot = NULL_var;

	hr = spiCurrentProduct->IsReference();
	if( SUCCEEDED(hr) ) {
		// The active node is the root node.
		// Connect AnoRoot to the root product reference
		spiEventsOnDocRoot = spiCurrentProduct;
		if( !!spiEventsOnDocRoot ) { spiEventsOnDocRoot->ConnectTo((CATBaseUnknown *)piAnoRoot); }

		if( !!spiEventsOnDocRoot && !!spiEventsOnAppRoot ) {
			CATCreate create((CATBaseUnknown*)spiEventsOnAppRoot, (CATBaseUnknown*)spiEventsOnDocRoot);
			spiEventsOnDocRoot->Dispatch(create);
		}
	}
	else {
		// The active node is a child node.
		// Connect AnoRoot to the product instance which is same reference of activate product
		CATIProduct_var spiCurrentProductRef=spiCurrentProduct->GetReferenceProduct();

		CATIProduct_var spiRootProduct=NULL_var;
		spiLinkOnDocument = spiCurrentProduct;
		hr = GetRootProduct(spiLinkOnDocument,spiRootProduct);
		CATListValCATBaseUnknown_var *pListChildProduct=NULL;
		if( !!spiRootProduct ) {
			pListChildProduct = spiRootProduct->GetAllChildren();
		}
		
		int numChildProduct=0;
		if( !!pListChildProduct ) { numChildProduct = pListChildProduct->Size(); }

		CATIProduct_var spiChildProductInst=NULL_var;
		CATIProduct_var spiChildProductRef=NULL_var;
		for(int i=1;i<=numChildProduct;i++) {
			spiChildProductInst = (*pListChildProduct)[i];
			spiChildProductRef = spiChildProductInst->GetReferenceProduct();

			if( spiChildProductRef != spiCurrentProductRef ) continue;

			spiEventsOnDocRoot = spiChildProductInst;
			if( !!spiEventsOnDocRoot ) { spiEventsOnDocRoot->ConnectTo((CATBaseUnknown *)piAnoRoot); }

			if( !!spiEventsOnDocRoot && !!spiEventsOnAppRoot ) {
				CATCreate create((CATBaseUnknown*)spiEventsOnAppRoot, (CATBaseUnknown*)spiEventsOnDocRoot);
				spiEventsOnDocRoot->Dispatch(create);
			}
		}
		if( !!pListChildProduct ) { delete pListChildProduct; pListChildProduct = NULL; }
	}

	//Connect the child of AnoRoot to the AnoRoot.
	CATListValCATBaseUnknown_var * pList = NULL;
	if( !!piAnoRoot ) {
		piAnoRoot->GetChildren(IID_JDAIPTMemo, pList);
	}
	
	//connect the root to its children
	if( !!pList ) {
		JDAIPTMemoParmEvents_var spParmEvent=NULL_var;
		CATISpecObject_var spiXCoord,spiYCoord,spiZCoord;
		CATBaseUnknown *pBaseUnknown;
		CATICkeParm_var spiCkeParmX,spiCkeParmY,spiCkeParmZ;
		JDAIPTMemo_var spMyFeature=NULL_var;
		HRESULT rc;
		for (int i=1; i <= pList->Size(); i++) {
			spiEventsOnAppRoot->ConnectTo((*pList)[i]);
			
			spMyFeature = (*pList)[i];
			rc = GetLiteralParameter(spMyFeature,"X",&pBaseUnknown);  spiCkeParmX = pBaseUnknown;
			rc = GetLiteralParameter(spMyFeature,"Y",&pBaseUnknown);  spiCkeParmY = pBaseUnknown;
			rc = GetLiteralParameter(spMyFeature,"Z",&pBaseUnknown);  spiCkeParmZ = pBaseUnknown;

			if( !!spiCkeParmX && !!spiCkeParmY && !!spiCkeParmZ) {
				spParmEvent = (*pList)[i];
				if( !!spParmEvent ) {
					spParmEvent->AddSubscribe(spiCkeParmX);
					spParmEvent->AddSubscribe(spiCkeParmY);
					spParmEvent->AddSubscribe(spiCkeParmZ);
				}
			}
		}

		delete pList;			pList = NULL;
	}

	if( !!piAnoRoot ) { piAnoRoot->Release(); piAnoRoot = NULL; }

	//4. Declaration of the CCP Format
	// (Done in exercise Copy Paste)
	// use global method SpecBindNativeFormat
	::SpecBindNativeFormat("JDAPTContainer");

	//cout <<"==> Now end JDAEPTContainerInit::Init  !" << endl;

   return;
}

//-----------------------------------------------------------------------------
// Implements CATInit::GetRootContainer
//-----------------------------------------------------------------------------
CATBaseUnknown* JDAEPTContainerInit::GetRootContainer (const CATIdent  iInterfaceID)
{
	//cout <<"==> Now we are in JDAEPTContainerInit::GetRootContainer  !" << endl;

   return QueryInterface(iInterfaceID);
}

HRESULT JDAEPTContainerInit::GetLiteralParameter(CATISpecObject_var ispiObj,CATUnicodeString iParamName,CATBaseUnknown **oLiteralParam)
{

	//cout <<"==> Now we are in JDAEPTMemo::GetLiteralParameter  !" << endl;

	HRESULT rc=E_FAIL;

	(*oLiteralParam) = NULL;
	CATISpecAttrKey *pSpecKey=NULL;

	CATISpecAttrAccess_var spAccess = ispiObj;
	if (!!spAccess ) {
		pSpecKey = spAccess->GetAttrKey(iParamName);
	}

	if (!!spAccess && pSpecKey) {
		(*oLiteralParam) = spAccess->GetSpecObject(pSpecKey);
		if (*oLiteralParam) rc = S_OK;
		pSpecKey->Release();  pSpecKey = NULL;
	}

	//cout <<"==> Now end JDAEPTMemo::GetLiteralParameter  !" << endl;

	return rc;
}
HRESULT JDAEPTContainerInit::GetRootProduct(CATILinkableObject_var ispiLinkObject,CATIProduct_var &ospiRootProduct)
{
	HRESULT rc=E_FAIL;
	ospiRootProduct = NULL_var;
	if( !ispiLinkObject ) return rc;

	CATDocument *pDocument=ispiLinkObject->GetDocument();
	if( !(pDocument->IsAKindOf("CATProduct")) ) return rc;

	CATIDocRoots_var spiDocRoots = pDocument;
	CATListValCATBaseUnknown_var *pListRoots = spiDocRoots->GiveDocRoots();

	CATBaseUnknown_var spDocRoot=NULL_var;
	if( !!pListRoots && pListRoots->Size() > 0 ) {
		spDocRoot = (*pListRoots)[1];
	}
	if( !!pListRoots) { delete pListRoots; pListRoots = NULL; }

	CATIProduct *piRootProduct=NULL;
	if( !!spDocRoot ) {
		rc = spDocRoot->QueryInterface(IID_CATIProduct,(void **)&piRootProduct);
	}
	ospiRootProduct = piRootProduct;

	if( !!piRootProduct ) { piRootProduct->Release(); piRootProduct = NULL; }

	return rc;
}