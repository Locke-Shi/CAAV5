// COPYRIGHT Dassault Systemes 2009
//===================================================================
//
// JDAEPTEditOnMemo.cpp
// Provide implementation to interface
//    CATIEdit
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//  Apr 2009  Creation: Code generated by the CAA wizard  LuJun
//===================================================================
#include "JDAEPTEditOnMemo.h"

#include "JDAPTProductCreateEditMemoCmd.h"
#include "CATDocument.h"
#include "CATILinkableObject.h"
#include "JDAIPTMemo.h"

#include "iostream.h"


 
CATImplementClass(JDAEPTEditOnMemo,
                  DataExtension,
                  CATExtIEdit,
                  JDAPTMemo );
 

//-----------------------------------------------------------------------------
// JDAEPTEditOnMemo : constructor
//-----------------------------------------------------------------------------
JDAEPTEditOnMemo::JDAEPTEditOnMemo():
    CATExtIEdit()
{
}

//-----------------------------------------------------------------------------
// JDAEPTEditOnMemo : destructor
//-----------------------------------------------------------------------------
JDAEPTEditOnMemo::~JDAEPTEditOnMemo()
{
}
 
// Link the implementation to its interface
// ---------------------------------------



//TIE or TIEchain definitions
#include "TIE_CATIEdit.h"
TIE_CATIEdit( JDAEPTEditOnMemo);


//Methods implementation

//-----------------------------------------------------------------------------
// Implements CATIEdit::Activate
//-----------------------------------------------------------------------------
CATCommand * JDAEPTEditOnMemo::Activate (CATPathElement *  iPath)
{
	//For an annotation created in a CATProduct the edition command is
	//  TSTAnoProductCreateEditMemoCmd
	HRESULT hr;

	//cout <<"==> Now we are in JDAEPTEditOnMemo::Activate !" << endl;
	  
	//Get annotation interface
	JDAIPTMemo *piMemo = NULL;
	hr = this->QueryInterface(IID_JDAIPTMemo, (void**)&piMemo);

	//Create the command
	CATCommand *pCom = NULL;
	if (SUCCEEDED(hr)) {
		pCom = new JDAPTProductCreateEditMemoCmd(piMemo);
		piMemo->Release(); piMemo = NULL;
	}
	else
		cout <<"  ==> Get JDAIPTMemo error !" << endl;

	//cout <<"==> Now end JDAEPTEditOnMemo::Activate !" << endl;

	return pCom;
}

//-----------------------------------------------------------------------------
// Implements CATIEdit::GetInPanelEditor
//-----------------------------------------------------------------------------
CATDlgFrame * JDAEPTEditOnMemo::GetInPanelEditor ()
{

   return NULL;
}

//-----------------------------------------------------------------------------
// Implements CATIEdit::GetPanelItem
//-----------------------------------------------------------------------------
CATDlgFrame * JDAEPTEditOnMemo::GetPanelItem (CATDialog *  iParent , const CATString &  iTitle)
{

   return NULL;
}
