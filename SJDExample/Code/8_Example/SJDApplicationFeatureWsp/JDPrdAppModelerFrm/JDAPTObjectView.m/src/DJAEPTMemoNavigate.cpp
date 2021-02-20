// COPYRIGHT Dassault Systemes 2009
//===================================================================
//
// DJAEPTMemoNavigate.cpp
// Provide implementation to interface
//    CATINavigateObject
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//  May 2009  Creation: Code generated by the CAA wizard  LuJun
//===================================================================
#include "DJAEPTMemoNavigate.h"
#include "CATIAlias.h"
#include "CATLISTV_CATISpecObject.h"
#include "CATIDescendants.h"
#include "CATICkeParm.h"
#include "CATUnicodeString.h"
#include "CATListOfCATUnicodeString.h"

#include "iostream.h"


CATImplementClass(DJAEPTMemoNavigate,
                  DataExtension,
                  CATBaseUnknown,
                  JDAPTMemo );
 

//-----------------------------------------------------------------------------
// DJAEPTMemoNavigate : constructor
//-----------------------------------------------------------------------------
DJAEPTMemoNavigate::DJAEPTMemoNavigate():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// DJAEPTMemoNavigate : destructor
//-----------------------------------------------------------------------------
DJAEPTMemoNavigate::~DJAEPTMemoNavigate()
{
}
 
// Link the implementation to its interface
// ---------------------------------------



//TIE or TIEchain definitions
#include "TIE_CATINavigateObject.h"
TIE_CATINavigateObject( DJAEPTMemoNavigate);


//Methods implementation

//-----------------------------------------------------------------------------
// Implements CATINavigateObject::GetIdentificators
//-----------------------------------------------------------------------------
CATListValCATUnicodeString* DJAEPTMemoNavigate::GetIdentificators ()
{
	//cout <<"==> Now we are in DJAEPTMemoNavigate::GetIdentificators  !" << endl;
	//We use the alias name
	CATUnicodeString name = "";
	CATListValCATUnicodeString * pList = new CATListValCATUnicodeString();
	CATIAlias_var spAlias = this;
	if (spAlias != NULL_var) {
		name = spAlias->GetAlias();
		pList->Append(name);
	}
	else
		cout <<"  ==> Get CATIAlias error !" << endl;

	//cout <<"==> Now end DJAEPTMemoNavigate::GetIdentificators  !" << endl;

	return pList;
}

//-----------------------------------------------------------------------------
// Implements CATINavigateObject::GetChildren
//-----------------------------------------------------------------------------
CATListValCATBaseUnknown_var* DJAEPTMemoNavigate::GetChildren ()
{
	//cout <<"==> Now we are in DJAEPTMemoNavigate::GetChildren  !" << endl;

	//No object displayed under the base feature except literal added by the
	// user
	CATListValCATBaseUnknown_var *pListOfChild = new CATListValCATBaseUnknown_var();

	//Get list of parameter objects
	HRESULT hr;
	CATListValCATISpecObject_var listOfParm;
	CATIDescendants *piDescendant = NULL;
	hr = this->QueryInterface(IID_CATIDescendants, (void**)&piDescendant);
	if (SUCCEEDED(hr) && piDescendant) {
		piDescendant->GetDirectChildren (CATICkeParm::ClassName(), listOfParm);
		piDescendant->Release();
		piDescendant = NULL;
	}
	else
		cout << "  ==> Get CATIDescendants error !" << endl;

	//Keep only user defined objects
	for (int i=1; i<= listOfParm.Size(); i++) {
		CATICkeParm *piParm = NULL;
		hr = listOfParm[i]->QueryInterface(IID_CATICkeParm, (void**) &piParm);

		if (SUCCEEDED(hr) && piParm) {
			//CATICkeParm::UserAccessMode mode = piParm->UserAccess();
			//if (mode == CATICkeParm::User) {
			pListOfChild->Append(piParm);
			//}
			piParm->Release();
			piParm = NULL;
		}
		else
			cout << "  ==> Get CATICkeParm error !" << endl;
	}
	//cout << "  ==> The number of parm: " << pListOfChild->Size() << endl;
	//Clear the list if it is empty
	if (pListOfChild->Size() == 0) {
		delete pListOfChild;
		pListOfChild = NULL;
	}

	//cout <<"==> Now end DJAEPTMemoNavigate::GetChildren  !" << endl;

	return pListOfChild;
}

