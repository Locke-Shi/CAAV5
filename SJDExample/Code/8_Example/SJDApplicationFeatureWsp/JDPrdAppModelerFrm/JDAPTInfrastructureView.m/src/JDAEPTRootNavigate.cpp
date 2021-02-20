// COPYRIGHT Dassault Systemes 2009
//===================================================================
//
// JDAEPTRootNavigate.cpp
// Provide implementation to interface
//    CATINavigateObject
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//  Apr 2009  Creation: Code generated by the CAA wizard  LuJun
//===================================================================
#include "JDAEPTRootNavigate.h"
#include "CATUnicodeString.h"
#include "JDAIPTRoot.h"
#include "CATISpecObject.h"

#include "iostream.h"


 
CATImplementClass(JDAEPTRootNavigate,
                  DataExtension,
                  CATBaseUnknown,
                  JDAPTRoot );
 

//-----------------------------------------------------------------------------
// JDAEPTRootNavigate : constructor
//-----------------------------------------------------------------------------
JDAEPTRootNavigate::JDAEPTRootNavigate():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// JDAEPTRootNavigate : destructor
//-----------------------------------------------------------------------------
JDAEPTRootNavigate::~JDAEPTRootNavigate()
{
}
 
// Link the implementation to its interface
// ---------------------------------------



//TIE or TIEchain definitions
#include "TIE_CATINavigateObject.h"
TIE_CATINavigateObject( JDAEPTRootNavigate);


//Methods implementation

//-----------------------------------------------------------------------------
// Implements CATINavigateObject::GetIdentificators
//-----------------------------------------------------------------------------
CATListValCATUnicodeString* JDAEPTRootNavigate::GetIdentificators ()
{
	//cout <<"==> Now we are in JDAEPTRootNavigate::GetIdentificators  !" << endl;

	CATListValCATUnicodeString *lstId = new CATListValCATUnicodeString();

	/*CATUnicodeString ustrId = "JDAPTs";
	lstId->Append(ustrId);  */
	CATISpecObject *piSpecObjectOnRoot = NULL;
	HRESULT rc = this -> QueryInterface(IID_CATISpecObject,
		(void**)&piSpecObjectOnRoot);
	if (SUCCEEDED(rc))
	{
		// Retrieve the root's name
		CATUnicodeString rootId = piSpecObjectOnRoot -> GetDisplayName();
		piSpecObjectOnRoot -> Release();
		piSpecObjectOnRoot = NULL;

		// String added to the list 
		lstId -> Append(rootId);
	}



	//cout <<"==> Now end JDAEPTRootNavigate::GetIdentificators  !" << endl;

	return lstId;

}

//-----------------------------------------------------------------------------
// Implements CATINavigateObject::GetChildren
//-----------------------------------------------------------------------------
CATListValCATBaseUnknown_var* JDAEPTRootNavigate::GetChildren ()
{

	//cout <<"==> Now we are in JDAEPTRootNavigate::GetChildren  !" << endl;

	JDAIPTRoot *piRoot = NULL;
	HRESULT hr;
	hr = this->QueryInterface(IID_JDAIPTRoot, (void**)&piRoot);

	CATListValCATBaseUnknown_var * pList = NULL;
	if (SUCCEEDED(hr) && (piRoot != NULL)) {
		hr = piRoot->GetChildren (IID_CATINavigateObject, pList);
		piRoot->Release();		piRoot = NULL;
	}
	else
		cout << "  ==> Get JDAIPTRoot error !" << endl;

	/*if( pList == NULL )  return pList;

	cout << "  ==> The number of children: " << pList->Size() << endl;

	CATBaseUnknown_var spObj=(*pList)[1];
	CATISpecObject *piSpecObj=NULL;
	hr = spObj->QueryInterface(IID_CATISpecObject,(void **)&piSpecObj);
	cout <<"  ==> Child name: " << piSpecObj->GetDisplayName() << endl;
	if( piSpecObj)
		piSpecObj->Release();
	piSpecObj = NULL;*/

	//cout <<"==> Now end JDAEPTRootNavigate::GetChildren  !" << endl;

	return pList;

}
