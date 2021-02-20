//ObjectModelerBase
#include "CATSession.h"
#include "CATDocument.h"
#include "CATIDocRoots.h"
#include "CATIContainer.h"
#include "CATDocumentServices.h"
#include "CATSessionServices.h"
#include "CATILinkableObject.h"
#include "CATIAlias.h"

//ObjectSpecsModeler 
#include "CATISpecObject.h"
//#include "CATISpecAttrAccess.h"
//#include "CATISpecAttrKey.h"

//DraftingInterfaces 
#include "CATIDftDocumentServices.h"
#include "CATIDftDrawing.h"
#include "CATIDftView.h"
#include "CATIView.h"
#include "CATIADrawingView.h"
#include "CATIDftGenView.h"

#include "CATIAGenerativeViewLinks.h"

//ProductStructure 
#include "CATIProduct.h"


////CATxPDMInterfaces 
//#include "CATxPDMSessionServices.h"
//#include "CATIxPDMItem.h"
//#include "CATListOfCATIxPDMItem.h"

////Mathematics 
//#include "CATLISTP_CATMathTransformation.h"
//#include "CATMathPlane.h"

//SJDGeneralClassFrm
//#include "SJDGeneralClass.h"

//System
#include "CATIUnknownList.h"
#include "iostream.h"

////////////////////////////////////////////////////////
//用于：连接关系（CATDrawing与CATPart或CATProduct）
//存在，需将CATPart或CATProduct文件改名的情况
////////////////////////////////////////////////////////
HRESULT SJDReplaceLinkedDocument(CATUnicodeString iFullPathOfDrawingDoc,CATUnicodeString iFullPathOfPartDoc);

///////////////////////////////////////////////////////
//用于：连接关系已断开，
//////////////////////////////////////////////////////
HRESULT SJDReCreateLinkDocument(CATUnicodeString iFullPathOfDrawingDoc,CATUnicodeString iFullPathOfPartDoc);

HRESULT SJDGetPartDoc(CATUnicodeString iFileFullPath,CATDocument *&oPartDoc,CATILinkableObject_var &oLinkedDoc);

void main(int argc,char *argv[])
{
	HRESULT rc=E_FAIL;

	//Check the input parameter
	if( argc < 3 ) {
		cout << "==> Missing input parameter !" << endl;
		return;
	}

	//Ge the file name
	char *fileName=argv[1];
	char *partFileName=argv[2];

	//Create a session
	CATSession* pSession = NULL;
	rc = ::Create_Session("RelinkDrawingPart_Session",pSession);
	if( FAILED(rc) || !pSession ) {
		cout << "==> Create Session error !" << endl;
		return;
	}

	//Method1: Link exist and using SaveAs to modify the document link
	CATUnicodeString strFullPathOfDrawingDoc(fileName);
	CATUnicodeString strFullPathOfPartDoc(partFileName);
	//rc = SJDReplaceLinkedDocument(strFullPathOfDrawingDoc,strFullPathOfPartDoc);

	//Method2: Link no exist,Remove the old link and create a new document link
	rc = SJDReCreateLinkDocument(strFullPathOfDrawingDoc,strFullPathOfPartDoc);

	//Delete the session
	rc = ::Delete_Session("RelinkDrawingPart_Session");
}

HRESULT SJDReplaceLinkedDocument(CATUnicodeString iFullPathOfDrawingDoc,CATUnicodeString iFullPathOfPartDoc)
{
	HRESULT rc=E_FAIL;
	if( iFullPathOfDrawingDoc.GetLengthInChar() < 1 || iFullPathOfPartDoc.GetLengthInChar() < 1 )
		return rc;

	//Open the document
	CATDocument *pDoc=NULL;
	rc = CATDocumentServices::OpenDocument(iFullPathOfDrawingDoc,pDoc);
	if( FAILED(rc) || !pDoc ) {
		cout << "==> Open " << iFullPathOfDrawingDoc.ConvertToChar() << " error !" << endl;
		return rc;
	}

	CATIDftDocumentServices *piDftDocServices = NULL;
	rc = pDoc->QueryInterface(IID_CATIDftDocumentServices,(void **)&piDftDocServices);
	if( FAILED(rc) || !piDftDocServices ) {
		cout << "==> Get CATIDftDocumentServices error !" << endl;
		return rc;
	}

	CATIDftDrawing *piDftDrawing = NULL;
	rc = piDftDocServices->GetDrawing(IID_CATIDftDrawing,(void **)&piDftDrawing);
	piDftDocServices->Release(); piDftDocServices = NULL;
	if( FAILED(rc) || !piDftDrawing ) {
		cout << "==> Get CATIDftDrawing error !" << endl;
		return rc;
	}

	//Get all views
	CATIUnknownList *pListView=NULL;
	rc = piDftDrawing->GetViews(&pListView);
	piDftDrawing->Release();  piDftDrawing = NULL;
	if( FAILED(rc) || !pListView ) {
		cout << "==> Get ViewList error !" << endl;
		return rc;
	}

	IUnknown *itemView = NULL;
	CATIDftView *piCurrentView = NULL;
	CATIView_var spiCurrentView=NULL_var;


	CATILinkableObject_var spiLinkDoc=NULL_var;
	
	unsigned int numView=0;
	pListView->Count(&numView);
	for(unsigned int i=0;i<numView;i++) {
		rc = pListView->Item(i,&itemView);
		if( FAILED(rc) || !itemView ) continue;

		rc = itemView->QueryInterface(IID_CATIDftView,(void **)&piCurrentView);
		if( FAILED(rc) || !piCurrentView ) continue;

		spiCurrentView = piCurrentView;
		piCurrentView->Release(); piCurrentView = NULL;

		spiLinkDoc = spiCurrentView->GetDoc();
		if( !spiLinkDoc ) continue;

		break;
	}
	delete pListView;  pListView = NULL;

	if( !!spiLinkDoc ) {
		CATDocument *pLinkedDoc=spiLinkDoc->GetDocument();
		if( !!pLinkedDoc ) {
			rc = CATDocumentServices::SaveAs(*pLinkedDoc,iFullPathOfPartDoc);
		}
	}
	
	//Save the Drawing document
	rc = CATDocumentServices::SaveAs(*pDoc,CATUnicodeString("CCCC.CATDrawing"));
	if( FAILED(rc) ) {
		cout << "==> Save document error !" << endl;
	}

	//Remove the Drawing document from memory
	rc = CATDocumentServices::Remove(*pDoc);

	return rc;
}

HRESULT SJDReCreateLinkDocument(CATUnicodeString iFullPathOfDrawingDoc,CATUnicodeString iFullPathOfPartDoc)
{
	HRESULT rc=E_FAIL;
	if( iFullPathOfDrawingDoc.GetLengthInChar() < 1 || iFullPathOfPartDoc.GetLengthInChar() < 1 )
		return rc;

	//Open the document
	CATDocument *pDoc=NULL;
	rc = CATDocumentServices::OpenDocument(iFullPathOfDrawingDoc,pDoc);
	if( FAILED(rc) || !pDoc ) {
		cout << "==> Open " << iFullPathOfDrawingDoc.ConvertToChar() << " error !" << endl;
		return rc;
	}

	CATIDftDocumentServices *piDftDocServices = NULL;
	rc = pDoc->QueryInterface(IID_CATIDftDocumentServices,(void **)&piDftDocServices);
	if( FAILED(rc) || !piDftDocServices ) {
		cout << "==> Get CATIDftDocumentServices error !" << endl;
		return rc;
	}

	CATIDftDrawing *piDftDrawing = NULL;
	rc = piDftDocServices->GetDrawing(IID_CATIDftDrawing,(void **)&piDftDrawing);
	piDftDocServices->Release(); piDftDocServices = NULL;
	if( FAILED(rc) || !piDftDrawing ) {
		cout << "==> Get CATIDftDrawing error !" << endl;
		return rc;
	}

	//Get the part doc
	CATDocument *pPartDoc=NULL;
	CATILinkableObject_var spiLinkOnPartDoc=NULL_var;
	rc = SJDGetPartDoc(iFullPathOfPartDoc,pPartDoc,spiLinkOnPartDoc);
	if( FAILED(rc) || !pPartDoc || !spiLinkOnPartDoc ) return rc;

	//Get all views
	CATIUnknownList *pListView=NULL;
	rc = piDftDrawing->GetViews(&pListView);
	piDftDrawing->Release();  piDftDrawing = NULL;
	if( FAILED(rc) || !pListView ) {
		cout << "==> Get ViewList error !" << endl;
		return rc;
	}

	IUnknown *itemView = NULL;
	CATIDftView *piCurrentView = NULL;
	CATIDftView_var spiDftView=NULL_var;
	CATIView_var spiCurrentView=NULL_var;
	CATIADrawingView *piDrawingView=NULL;

	//wchar_t *nameOfView;
	//CATUnicodeString viewName;

	IUnknown *pUnknownGenView=NULL;
	CATIDftGenView *piGenView=NULL;
	CATBoolean isGenView;

	CATIAGenerativeViewLinks *pGenViewLink=NULL;

	CATISpecObject_var spiSpecOnView=NULL_var;

	unsigned int numView=0;
	pListView->Count(&numView);
	for(unsigned int i=0;i<numView;i++) {
		rc = pListView->Item(i,&itemView);
		if( FAILED(rc) || !itemView ) continue;

		rc = itemView->QueryInterface(IID_CATIDftView,(void **)&piCurrentView);
		if( FAILED(rc) || !piCurrentView ) continue;

		spiDftView = piCurrentView;
		piCurrentView->Release(); piCurrentView = NULL;
		
		/*rc = spiDftView->GetViewName(&nameOfView);
		viewName.BuildFromWChar(nameOfView);
		cout << "==> View Name: " << viewName.ConvertToChar() << endl;*/

		//Check the view is GeneralView ?
		rc = spiDftView->GetApplicativeExtension(IID_CATIDftGenView,&pUnknownGenView);
		if( SUCCEEDED(rc) && !!pUnknownGenView ) {
			rc = pUnknownGenView->QueryInterface(IID_CATIDftGenView,(void **)&piGenView);
			pUnknownGenView->Release(); pUnknownGenView = NULL;
		}
		
		isGenView = FALSE;
		if( SUCCEEDED(rc) || !!piGenView ) {
			rc = piGenView->IsGenerative(&isGenView);
			piGenView->Release();  piGenView = NULL;
		}
		if( isGenView == FALSE ) continue;
		
		//Remove the old view link and create a new link
		spiCurrentView = spiDftView;
		rc = spiCurrentView->QueryInterface(IID_CATIADrawingView,(void **)&piDrawingView);
		if( SUCCEEDED(rc) && !!piDrawingView ) {
			rc = piDrawingView->get_GenerativeLinks(pGenViewLink);
			if( SUCCEEDED(rc) && !!pGenViewLink ) {
				rc = pGenViewLink->RemoveAllLinks();
				pGenViewLink->Release();  pGenViewLink = NULL;
			}
			piDrawingView->Release(); piDrawingView = NULL;
			//rc = piDrawingView->Isolate();
			//piDrawingView->Release();  piDrawingView = NULL;
			
			if( SUCCEEDED(rc) ) {
				spiCurrentView->SetDoc(spiLinkOnPartDoc);

				spiSpecOnView = spiCurrentView;
				if( !!spiSpecOnView )
					spiSpecOnView->Update();
			}
		}
	}
	delete pListView;  pListView = NULL;

	//Save the Drawing document
	rc = CATDocumentServices::SaveAs(*pDoc,CATUnicodeString("CCCC.CATDrawing"));
	if( FAILED(rc) ) {
		cout << "==> Save document error !" << endl;
	}

	//Remove the Drawing document from memory
	rc = CATDocumentServices::Remove(*pPartDoc);
	rc = CATDocumentServices::Remove(*pDoc);
	
	return rc;
}
HRESULT SJDGetPartDoc(CATUnicodeString iFileFullPath,CATDocument *&oPartDoc,CATILinkableObject_var &oLinkedDoc)
{
	HRESULT rc=E_FAIL;

	//Check the input parameters
	if( iFileFullPath.GetLengthInChar() <  1 )  return rc;

	//Open the document
	//CATDocument *pDoc=NULL;
	rc = CATDocumentServices::OpenDocument(iFileFullPath,oPartDoc);
	if( FAILED(rc) || !oPartDoc ) {
		cout << "==> Open " << iFileFullPath.ConvertToChar() << " error !" << endl;
		return rc;
	}

	CATIDocRoots *piDocRootOnDoc=NULL;
	rc = oPartDoc->QueryInterface(IID_CATIDocRoots,(void **)&piDocRootOnDoc);
	if( FAILED(rc) || !piDocRootOnDoc ) {
		cout << "==> Get CATIDocRoots error !" << endl;
		return rc;
	}

	//Get the root CATProduct
	CATListValCATBaseUnknown_var *pListRoot=piDocRootOnDoc->GiveDocRoots();
	CATIProduct_var spiRootProduct=NULL_var;
	if( !!pListRoot && pListRoot->Size() > 0 ) {
		spiRootProduct = (*pListRoot)[1];
		delete pListRoot;  pListRoot = NULL;
	}
	piDocRootOnDoc->Release();  piDocRootOnDoc = NULL;
	if( !spiRootProduct ) return rc;

	oLinkedDoc = spiRootProduct;

	return rc;
}