// COPYRIGHT Dassault Systemes 2015
//===================================================================
//
// SJDPartExampleCmd.cpp
// The state chart based command: SJDPartExampleCmd
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
//  Jan 2015  Creation: Code generated by the CAA wizard  LuJunHome
//===================================================================
#include "SJDPartExampleCmd.h"

//---------- Code generated by Jiangda CAAPlugin wizard

// DialogEngine
#include "CATDialogState.h"

// VisualizationBase
#include "CATRep.h"
#include "CATPathElement.h"
#include "CAT3DViewpoint.h"

//---------- End Code generated by Jiangda CAAPlugin wizard

//ObjectModelerBase 
#include "CATInit.h"
#include "CATDocument.h"
#include "CATDocumentServices.h"

//MecModInterfaces 
#include "CATIPrtContainer.h"

//ObjectSpecsModeler
#include "CATISpecObject.h"

//Visualization 
#include "CATI3DGeoVisu.h"
#include "CATVisManager.h"


//System
#include "iostream.h"

#include "CATCreateExternalObject.h"
CATCreateClass( SJDPartExampleCmd);


//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
SJDPartExampleCmd::SJDPartExampleCmd() :
  CATStateCommand ("SJDPartExampleCmd", CATDlgEngOneShot, CATCommandModeExclusive) 
//  Valid states are CATDlgEngOneShot and CATDlgEngRepeat
  ,_pMyDlg(NULL),_pOkAgent(NULL),_pCloseAgent(NULL),_pApplyAgent(NULL)
  ,_pWinCloseAgent(NULL),_pComboSelectAgent(NULL),_p3DRep(NULL),_p3DRep1(NULL)
  ,_p3DRep2(NULL),_p3DRep3(NULL),_p3DRep4(NULL)
{
	_pMyDlg = new SJDPartExampleDlg();
	_pMyDlg->Build();
	_pMyDlg->SetVisibility(CATDlgShow);
}

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
SJDPartExampleCmd::~SJDPartExampleCmd()
{
   if (_pMyDlg != NULL) 
      _pMyDlg->RequestDelayedDestruction();
   if (_pOkAgent != NULL) 
	   _pOkAgent->RequestDelayedDestruction();
   if (_pCloseAgent != NULL) 
	   _pCloseAgent->RequestDelayedDestruction();
   if (_pApplyAgent != NULL) 
	   _pApplyAgent->RequestDelayedDestruction();
   if (_pWinCloseAgent != NULL) 
	   _pWinCloseAgent->RequestDelayedDestruction();
   if (_pComboSelectAgent != NULL) 
	   _pComboSelectAgent->RequestDelayedDestruction();
}


//-------------------------------------------------------------------------
// BuildGraph()
//-------------------------------------------------------------------------
void SJDPartExampleCmd::BuildGraph()
{
	//Set dialog filed agent 
	_pOkAgent      = new CATDialogAgent("Ok");
	_pApplyAgent   = new CATDialogAgent("Apply");
	_pCloseAgent   = new CATDialogAgent("Close");
	_pWinCloseAgent  = new CATDialogAgent("WinClose");
	_pComboSelectAgent  = new CATDialogAgent("ComboSelect");

	//Set the Notify on 
	_pOkAgent->AcceptOnNotify(_pMyDlg,_pMyDlg->GetDiaOKNotification());
	_pApplyAgent->AcceptOnNotify(_pMyDlg,_pMyDlg->GetDiaAPPLYNotification());
	_pCloseAgent->AcceptOnNotify(_pMyDlg,_pMyDlg->GetDiaCLOSENotification ());
	_pWinCloseAgent->AcceptOnNotify(_pMyDlg,_pMyDlg->GetWindCloseNotification());
	_pComboSelectAgent->AcceptOnNotify(_pMyDlg->GetCombo(),_pMyDlg->GetCombo()->GetComboSelectNotification());

	//Set stat
	CATDialogState *WaitForSelObjectState= GetInitialState("SelectType");
	WaitForSelObjectState -> AddDialogAgent ( _pOkAgent );
	WaitForSelObjectState -> AddDialogAgent ( _pApplyAgent );
	WaitForSelObjectState -> AddDialogAgent ( _pCloseAgent );
	WaitForSelObjectState -> AddDialogAgent ( _pWinCloseAgent );
	WaitForSelObjectState -> AddDialogAgent ( _pComboSelectAgent );

	// TODO: Define the StateChart 
	// From line to line 
	AddTransition ( WaitForSelObjectState , WaitForSelObjectState , 
		IsOutputSetCondition ( _pComboSelectAgent ) ,
		Action ( ( ActionMethod ) &SJDPartExampleCmd::ActionComboSelect ) );

	AddTransition ( WaitForSelObjectState , NULL , 
		IsOutputSetCondition ( _pOkAgent ) ,
		Action ( ( ActionMethod ) &SJDPartExampleCmd::ActionOkButton ) );
	//  ok
	AddTransition ( WaitForSelObjectState , WaitForSelObjectState , 
		IsOutputSetCondition ( _pApplyAgent ) ,
		Action ( (ActionMethod )& SJDPartExampleCmd::ActionApplyButton ) ); 

	// Apply
	AddTransition ( WaitForSelObjectState , NULL , 
		IsOutputSetCondition ( _pCloseAgent ) ,
		Action ( (ActionMethod )& SJDPartExampleCmd::ActionCloseButton ) );  

	// Close 
	AddTransition ( WaitForSelObjectState , NULL , 
		IsOutputSetCondition ( _pWinCloseAgent ) ,
		Action ( (ActionMethod )& SJDPartExampleCmd::ActionCloseButton ) );
}

CATBoolean SJDPartExampleCmd::ActionComboSelect(void * data)
{
	_pComboSelectAgent->InitializeAcquisition();

	//
	if( !!_p3DRep ) {
		_pMyDlg->GetViewer3D()->RemoveRep((CAT3DRep *)_p3DRep);
		_p3DRep = NULL;

		_pMyDlg->GetViewer3D()->Draw();
	}
	
	CATUnicodeString fileName;
	int indexSelect=_pMyDlg->GetCombo()->GetSelect();
	switch(indexSelect) {
		case 1:
			fileName = "Part1.CATPart";
			if( !_p3DRep1 ) {
				_p3DRep1 = GetRepFromDocument(fileName);
			}
			_p3DRep = _p3DRep1;
			break;
		case 2:
			fileName = "Part2.CATPart";
			if( !_p3DRep2 ) {
				_p3DRep2 = GetRepFromDocument(fileName);
			}
			_p3DRep = _p3DRep2;
			break;
		case 3:
			fileName = "Part3.CATPart";
			if( !_p3DRep3 ) {
				_p3DRep3 = GetRepFromDocument(fileName);
			}
			_p3DRep = _p3DRep3;
			break;
		case 4:
			fileName = "Part4.CATPart";
			if( !_p3DRep4 ) {
				_p3DRep4 = GetRepFromDocument(fileName);
			}
			_p3DRep = _p3DRep4;
			break;
		default:
			break;
	}

	if( !!_p3DRep ) {
		_pMyDlg->GetViewer3D()->AddRep(_p3DRep);
		_pMyDlg->GetViewer3D()->Draw();
		_pMyDlg->GetViewer3D()->Reframe();
	}

	return TRUE;
}
CATBoolean SJDPartExampleCmd::ActionOkButton(void * data)
{

	return TRUE;
}
CATBoolean SJDPartExampleCmd::ActionCloseButton(void * data)
{

	return TRUE;
}
CATBoolean SJDPartExampleCmd::ActionApplyButton(void * data)
{
	_pApplyAgent->InitializeAcquisition();

	return TRUE;
}
CAT3DRep *SJDPartExampleCmd::GetRepFromDocument(CATUnicodeString istrFileName)
{
	HRESULT rc=E_FAIL;
	CAT3DRep *pRep3D=NULL;

	//////////////////////////////////////////////////////////////////////////
	// ����ʵ�����������TestData·��
	//////////////////////////////////////////////////////////////////////////
	CATUnicodeString fullFilePath=CATUnicodeString("E:\\Program\\CAA\\CATIA\\tmpTest\\SJDDisplayDocInMyViewerWsp\\TestData\\") + istrFileName;
	CATDocument* pPartDocument = NULL;
	rc = CATDocumentServices::OpenDocument(fullFilePath, pPartDocument);

	CATInit * pInitOnDoc = NULL ;
	if( !!pPartDocument ) {
		rc = pPartDocument->QueryInterface(IID_CATInit,(void **) &pInitOnDoc);
	}
	
	CATIPrtContainer * pISpecContainer= NULL ;
	if( !!pInitOnDoc ) {
		pISpecContainer = (CATIPrtContainer*)pInitOnDoc->GetRootContainer("CATIPrtContainer");

		pInitOnDoc->Release();	pInitOnDoc = NULL ;
	}
	
	CATISpecObject_var spSpecObjectOnMechanicalPart = NULL_var;
	if( !!pISpecContainer ) {
		spSpecObjectOnMechanicalPart = pISpecContainer->GetPart();

		pISpecContainer->Release();  pISpecContainer = NULL ;
	}

	CATPathElement *pRootObjectPath = NULL;
	if( !!spSpecObjectOnMechanicalPart ) {
		pRootObjectPath = new CATPathElement(spSpecObjectOnMechanicalPart);
	}

	//------------------------------------------------------------------
	//6 - Attaches the Path to manage by the CATVisManager
	//------------------------------------------------------------------
	CATVisManager *pVisManager = CATVisManager::GetVisManager();
	// 6-1 List of CATIVisu interfaces used to display the model 
	
	list<IID> ListIVisu3d;
	IID * pIIDInf = new IID(IID_CATI3DGeoVisu) ;
	ListIVisu3d.fastadd(pIIDInf);

	// 6-2 Creating a default 3D viewpoint
	CAT3DViewpoint * pVP = new CAT3DViewpoint();
	//CAT3DViewpoint pVP = _pMyDlg->GetViewer3D()->GetMain3DViewpoint();  //���������

	// 6-3 Attaching the root to the CATVisManager: The graphic representations
	//     are created.
	//
	if( !!pVisManager ) {
		rc = pVisManager->AttachTo ( pRootObjectPath, pVP, ListIVisu3d);
	}

	delete pIIDInf; 	pIIDInf = NULL;
	ListIVisu3d.empty();
	pRootObjectPath->Release();	pRootObjectPath = NULL;

	//------------------------------------------------------------------
	//7 - Retrieves the Graphic Representation of the MechanicalPart feature
	//------------------------------------------------------------------
	CATI3DGeoVisu *pIVisuOnRoot =NULL;
	if( !!spSpecObjectOnMechanicalPart ) {
		rc = spSpecObjectOnMechanicalPart->QueryInterface(IID_CATI3DGeoVisu,(void **) &pIVisuOnRoot);
	}
	if ( SUCCEEDED(rc) && !!pIVisuOnRoot )
	{
		CATRep * pRep = pIVisuOnRoot->GiveRep();
		if ( NULL != pRep )
		{
			pRep3D = (CAT3DRep *) pRep;
		}

		pIVisuOnRoot->Release(); pIVisuOnRoot = NULL ;
	}

	////------------------------------------------------------------------
	////9 - Detach the VP, the root and the list of interfaces 
	////------------------------------------------------------------------
	//rc = pVisManager->DetachFrom(pVP,0) ;
	//pVP->Release();	pVP = NULL;

	////------------------------------------------------------------------
	////10 - Closes the Part Document 
	////------------------------------------------------------------------
	//rc = CATDocumentServices::Remove (*pPartDocument);
	//pPartDocument = NULL ;

	return pRep3D;
}