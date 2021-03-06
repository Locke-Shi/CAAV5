// COPYRIGHT Dassault Systemes 2011
//===================================================================
//
// JDChangeFatherTestCmd.cpp
// The state chart based command: JDChangeFatherTestCmd
//
//===================================================================
//
// Usage notes:
//
//   测试更改一个对象的Father的方法
//
//===================================================================
//
//  Aug 2011  Creation: Code generated by the CAA wizard  THINKPAD
//===================================================================
#include "JDChangeFatherTestCmd.h"

#include "CATIAlias.h"
#include "CATUnicodeString.h"
#include "CATIDescendants.h"
#include "CATIModelEvents.h"
#include "CATModify.h"
#include "CATIGSMProceduralView.h"
#include "CATMmrInterPartCopy.h"
#include "CATICutAndPastable.h"
#include "CATIContainer.h"

#include "CATIPrtPart.h"
#include "CATIMechanicalFeature.h"

#include "CATIRedrawEvent.h"

#include "iostream.h"

#include "CATCreateExternalObject.h"
CATCreateClass( JDChangeFatherTestCmd);


//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
JDChangeFatherTestCmd::JDChangeFatherTestCmd() :
  CATStateCommand ("JDChangeFatherTestCmd", CATDlgEngOneShot, CATCommandModeExclusive) 
//  Valid states are CATDlgEngOneShot and CATDlgEngRepeat
,_pDlg(NULL),_pOkButtonAgent(NULL),_pCloseButtonAgent(NULL),_WinCloseAgent(NULL)
,_pObjectAgent(NULL),_pFatherAgent(NULL),_spiSpecOnObject(NULL_var),_spiSpecOnFather(NULL_var)
{
	//Create the dialog
	_pDlg = new JDChangeFatherTestDlg();
	_pDlg->Build();
	_pDlg->SetVisibility(CATDlgShow);
}

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
JDChangeFatherTestCmd::~JDChangeFatherTestCmd()
{
	if (_pOkButtonAgent != NULL) {
		_pOkButtonAgent->RequestDelayedDestruction();
		_pOkButtonAgent = NULL;
	}

	if( _pCloseButtonAgent != NULL ) {
		_pCloseButtonAgent->RequestDelayedDestruction();
		_pCloseButtonAgent = NULL;
	}

	if( _pObjectAgent != NULL ) {
		_pObjectAgent->RequestDelayedDestruction();
		_pObjectAgent = NULL;
	}

	if( _pFatherAgent != NULL ) {
		_pFatherAgent->RequestDelayedDestruction();
		_pFatherAgent = NULL;
	}

	if( _WinCloseAgent != NULL ) {
		_WinCloseAgent->RequestDelayedDestruction();
		_WinCloseAgent = NULL;
	}

	if( _pDlg != NULL ) {
		_pDlg->RequestDelayedDestruction();
		_pDlg = NULL;
	}
}


//-------------------------------------------------------------------------
// BuildGraph()
//-------------------------------------------------------------------------
void JDChangeFatherTestCmd::BuildGraph()
{
	//The agent of select a object
	_pObjectAgent= new CATPathElementAgent("Select a object");
	_pObjectAgent->SetOrderedElementType("CATIGSMLine");
	_pObjectAgent->SetBehavior(CATDlgEngWithPrevaluation|CATDlgEngWithCSO|CATDlgEngOneShot);

	//The agent of select father object
	_pFatherAgent= new CATPathElementAgent("Select a father");
	_pFatherAgent->SetOrderedElementType("CATIMmiNonOrderedGeometricalSet");
	_pFatherAgent->SetBehavior(CATDlgEngWithPrevaluation|CATDlgEngWithCSO|CATDlgEngOneShot);

	_pOkButtonAgent = new CATDialogAgent ("OkAgent");
	_pOkButtonAgent->AcceptOnNotify(_pDlg, _pDlg->GetDiaOKNotification());

	_pCloseButtonAgent = new CATDialogAgent ("CloseAgent");
	_pCloseButtonAgent->AcceptOnNotify(_pDlg, _pDlg->GetDiaCANCELNotification());

	_WinCloseAgent = new CATDialogAgent ("CloseAgent");
	_WinCloseAgent->AcceptOnNotify(_pDlg, _pDlg->GetWindCloseNotification());

	//Define the state
	//The line select state
	CATDialogState * initialState = GetInitialState("initialState");
	initialState -> AddDialogAgent (_pObjectAgent);
	initialState -> AddDialogAgent (_pFatherAgent);
	initialState -> AddDialogAgent (_pOkButtonAgent);
	initialState -> AddDialogAgent (_pCloseButtonAgent);
	initialState -> AddDialogAgent (_WinCloseAgent);

	//Define the transition
	AddTransition( initialState, initialState,
		IsOutputSetCondition (_pFatherAgent),
		Action ((ActionMethod) &JDChangeFatherTestCmd::ActionFatherObjectSelected));
	AddTransition( initialState, initialState,
		IsOutputSetCondition (_pObjectAgent),
		Action ((ActionMethod) &JDChangeFatherTestCmd::ActionObjectSelected));
	AddTransition( initialState, NULL, 
		IsOutputSetCondition (_pOkButtonAgent),
		Action ((ActionMethod) &JDChangeFatherTestCmd::ActionOkButton));
	AddTransition( initialState, NULL, 
		IsOutputSetCondition (_pCloseButtonAgent),
		Action ((ActionMethod) &JDChangeFatherTestCmd::ActionCloseButton));
	AddTransition( initialState, NULL, 
		IsOutputSetCondition (_WinCloseAgent),
		Action ((ActionMethod) &JDChangeFatherTestCmd::ActionCloseButton));
}

CATBoolean JDChangeFatherTestCmd::ActionObjectSelected(void *data)
{
	//Get the selected object
	CATBaseUnknown *piUnSurface = _pObjectAgent->GetElementValue();
	
	CATISpecObject *piSpecObj=NULL;
	HRESULT rc=piUnSurface->QueryInterface(IID_CATISpecObject,(void **)&piSpecObj);
	CATISpecObject_var spiSpecSurface=piSpecObj;
	if( !!piSpecObj ) {
		piSpecObj->Release();  piSpecObj = NULL;
	}
	
	//Get the name of the selected object, and set name into the dialog
	CATIAlias *piAlias=NULL;
	if( !!spiSpecSurface )
		rc=spiSpecSurface->QueryInterface(IID_CATIAlias,(void **)&piAlias);

	if( piAlias != NULL ) {
		CATUnicodeString Name=piAlias->GetAlias();
		_pDlg->SetObjectName(Name);

		_spiSpecOnObject = spiSpecSurface;

		piAlias->Release();  piAlias = NULL;

		//cout << "==> ObjectType: " << (_spiSpecOnObject->GetType()).ConvertToChar() << endl;
		//cout << "==> ObjectSupperType: " << (_spiSpecOnObject->GetSu/perType()).ConvertToChar() << endl;
	}

	_pObjectAgent->InitializeAcquisition();

	return TRUE;
}

CATBoolean JDChangeFatherTestCmd::ActionFatherObjectSelected(void *data)
{
	//Get the selected new father object
	CATBaseUnknown *piUnSurface = _pFatherAgent->GetElementValue();
	
	CATISpecObject *piSpecObj=NULL;
	HRESULT rc=piUnSurface->QueryInterface(IID_CATISpecObject,(void **)&piSpecObj);
	CATISpecObject_var spiSpecSurface=piSpecObj;
	if( !!piSpecObj ) {
		piSpecObj->Release();  piSpecObj = NULL;
	}

	//Set the new father object name into the dialog
	CATIAlias *piAlias=NULL;
	if( !!spiSpecSurface )
		rc=spiSpecSurface->QueryInterface(IID_CATIAlias,(void **)&piAlias);

	if( piAlias != NULL ) {
		CATUnicodeString Name=piAlias->GetAlias();
		_pDlg->SetFatherName(Name);

		_spiSpecOnFather = spiSpecSurface;

		piAlias->Release();  piAlias = NULL;

		//cout << "==> FatherType: " << (_spiSpecOnFather->GetType()).ConvertToChar() << endl;
	}

	_pFatherAgent->InitializeAcquisition();

	return TRUE;
}

CATBoolean JDChangeFatherTestCmd::ActionOkButton( void *data )
{
	HRESULT rc=E_FAIL;

	if( !_spiSpecOnObject || !_spiSpecOnFather ) return FALSE;

	//First method:
	// Using CATIGSMProceduralView interface to change the father of the selected object.
	// 成功
	rc = JDChangeFatherByDescendants();

	//Second method:
	//Test Copy and past method
	// 成功
	//rc = JDChangeFatherByCopyPaste();

	//Third method:
	//Test cut and past method
	// 成功
	//rc = JDChangeFatherByCutPaste();

	return TRUE;
}

CATBoolean JDChangeFatherTestCmd::ActionCloseButton(void *data)
{
	return TRUE;
}
HRESULT JDChangeFatherTestCmd::JDChangeFatherByDescendants()
{
	HRESULT rc=E_FAIL;

	//Remove the selected object from the old father
	//Get the old father of the selected object
	CATISpecObject *piSpecOnObjectCurrentFather=_spiSpecOnObject->GetFather();
	if( !!piSpecOnObjectCurrentFather ) {
		//Remove the selected object from old father
		piSpecOnObjectCurrentFather->RemoveComponent(_spiSpecOnObject);

		//Update the old father
		piSpecOnObjectCurrentFather->Update();

		//Refresh the specTree for the old father
		CATIRedrawEvent_var spiRedrawEvent(piSpecOnObjectCurrentFather);
		if( !!spiRedrawEvent )
			spiRedrawEvent->Redraw();

		//Release pointer
		piSpecOnObjectCurrentFather->Release();  piSpecOnObjectCurrentFather = NULL;
	}

	//Add the object under the new father
	//Get the CATIGSMProceduralView of the selected object
	CATIGSMProceduralView *piGsmProcedural=NULL;
	rc = _spiSpecOnObject->QueryInterface(IID_CATIGSMProceduralView,(void **)&piGsmProcedural);
	if( SUCCEEDED(rc) && !!piGsmProcedural ) {
		//Get the CATIDescendants of the new father
		CATIDescendants_var spiNewFatherDesc=_spiSpecOnFather;
		//Add the selected object into the new father
		rc = piGsmProcedural->InsertInProceduralView(spiNewFatherDesc,FALSE);

		//Update the selected object
		_spiSpecOnObject->Update();

		//Release the pointer
		piGsmProcedural->Release();  piGsmProcedural = NULL;
	}
	
	return S_OK;
}
HRESULT JDChangeFatherTestCmd::JDChangeFatherByCopyPaste()
{
	HRESULT rc=E_FAIL;

	//Get the CATMmrInterPartCopy class
	CATMmrInterPartCopy *actionCP=new CATMmrInterPartCopy(_spiSpecOnObject,_spiSpecOnFather);

	if( !!actionCP ) {
		//Copy BREP attributes and colors
		int iMode=3; 
		rc = actionCP->SetAttributeMode(iMode);
		//Without link
		rc = actionCP->SetLinkMode(FALSE);

		CATUnicodeString erroMessage;
		rc = actionCP->Run(&erroMessage);
		if( FAILED(rc) )
			cout << "==> Error in Run: " << erroMessage.ConvertToChar() << endl;

		//Get the result SpecObject
		CATISpecObject_var spiSpecResult=NULL_var;
		rc = actionCP->GetResult(spiSpecResult);

		//Get alias from old SpecObject
		//and Set alias to the new SpecObject
		CATIAlias_var spiSourceAlias=_spiSpecOnObject;
		CATIAlias_var spiTargetAlias=spiSpecResult;

		CATUnicodeString specAlias;
		if( !!spiSourceAlias )
			specAlias = spiSourceAlias->GetAlias();
		if( !!spiTargetAlias )
			spiTargetAlias->SetAlias(specAlias);

		//Update the SpecObject
		spiSpecResult->Update();
		_spiSpecOnFather->Update();

		delete actionCP;  actionCP = NULL;
	}

	return rc;
}

HRESULT JDChangeFatherTestCmd::JDChangeFatherByCutPaste()
{
	HRESULT rc=E_FAIL;

	//Get current work object
	CATIMechanicalFeature_var spiMechanicalFeat=_spiSpecOnFather;

	CATISpecObject_var spiSpecOnOldCurrentObject=NULL_var;
	CATISpecObject_var spiSpecOnPrtPart=NULL_var;
	  //Get the root object
	if( !!spiMechanicalFeat )
		spiSpecOnPrtPart = spiMechanicalFeat->GetPart();
	CATIPrtPart_var spiPrtPart=spiSpecOnPrtPart;
	  //Get current feature
	if( !!spiPrtPart )
		spiSpecOnOldCurrentObject = spiPrtPart->GetCurrentFeature();

	//Get the source and target feature container
	CATIContainer_var spiTargetContainer=_spiSpecOnFather->GetFeatContainer();
	CATIContainer_var spiSourceContainer=_spiSpecOnObject->GetFeatContainer();
	if( !spiTargetContainer || !spiSourceContainer ) {
		cout << "==> Get container of CATFeature error !" << endl;
		return rc;
	}

	//Get the CATICutAndPastable of target
	CATICutAndPastable *piTargetCutPastable=NULL;
	rc = spiTargetContainer->QueryInterface(IID_CATICutAndPastable,(void **)&piTargetCutPastable);
	CATICutAndPastable_var spiTargetCutPastable=piTargetCutPastable;
	if( !!piTargetCutPastable ) { piTargetCutPastable->Release();  piTargetCutPastable = NULL; }
	if( !spiTargetCutPastable ) {
		cout << "==> Get target CATICutAndPastable error !" << endl;
		return rc;
	}

	//Get the CATICutAndPastable of source
	CATICutAndPastable *piSourceCutPastable=NULL;
	rc = spiSourceContainer->QueryInterface(IID_CATICutAndPastable,(void **)&piSourceCutPastable);
	CATICutAndPastable_var spiSourceCutPastable=piSourceCutPastable;
	if( !!piSourceCutPastable ) { piSourceCutPastable->Release();  piSourceCutPastable = NULL; }
	if( !spiSourceCutPastable ) {
		cout << "==> Get source CATICutAndPastable error !" << endl;
		return rc;
	}

	//The object to be copied and pasted
	ListOfVarBaseUnknown newListToCopy;
	ListOfVarBaseUnknown listFromCopy;
	listFromCopy.Append((CATBaseUnknown *)_spiSpecOnObject);

	//Copye the list object to the clipboard
	int RC;
	RC = spiSourceCutPastable->BoundaryExtract(newListToCopy,&listFromCopy,NULL);
	if( !RC ) {
		cout << "==> There no object copy to the clipboard !" << endl;
		return rc;
	}

	//Get the object of clipboard
	VarBaseUnknown pExtractedList;
	pExtractedList = spiSourceCutPastable->Extract(newListToCopy,NULL);

	CATICutAndPastable_var spiExtractCutPastable=pExtractedList;
	if( !spiExtractCutPastable ) {
		cout << "==> Get extract CATICutAndPastable error !" << endl;
		return rc;
	}

	//Get the object in the clipboard
	ListOfVarBaseUnknown extractedListToCopy;
	RC = spiExtractCutPastable->BoundaryExtract(extractedListToCopy,NULL,NULL);
	if( !RC ) {
		cout << "==> Can't get any object form the clipboard !" << endl;
		return rc;
	}

	//We are in the CATPart document,so we should set current feature
	if( !!spiPrtPart ) {
		spiPrtPart->SetCurrentFeature(_spiSpecOnFather);
	}

	//Do the past operation
	ListOfVarBaseUnknown listPastedObjects;
	listPastedObjects = spiTargetCutPastable->Paste(extractedListToCopy,NULL,NULL);
	if( listPastedObjects.Size() != extractedListToCopy.Size() ) {
		cout << "==> There may be have some errors when do the paste !" << endl;
	}

	//Restore the old current feature
	if( !!spiSpecOnOldCurrentObject && !!spiPrtPart ) {
		spiPrtPart->SetCurrentFeature(spiSpecOnOldCurrentObject);
	}

	//Remove objects from source
	spiSourceCutPastable->Remove(listFromCopy,NULL);

	//Update all object
	if( !!spiSpecOnPrtPart )
		spiSpecOnPrtPart->Update();

	return S_OK;
}
