// COPYRIGHT Dassault Systemes 2009
//===================================================================
//
// JDAEPTContainer.cpp
// Provide implementation to interface
//    JDAIPTContainer
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//  Apr 2009  Creation: Code generated by the CAA wizard  LuJun
//===================================================================
#include "JDAEPTContainer.h"

#include "CATUnicodeString.h"
#include "JDAIPTRoot.h"
#include "CATIClientContainer.h"
#include "sequence_CATBaseUnknown_ptr.h"

#include "iostream.h"


 
CATImplementClass(JDAEPTContainer,
                  DataExtension,
                  CATBaseUnknown,
                  JDAPTContainer );
 

//-----------------------------------------------------------------------------
// JDAEPTContainer : constructor
//-----------------------------------------------------------------------------
JDAEPTContainer::JDAEPTContainer():
    CATBaseUnknown()
{
	_piRoot = NULL;
}

//-----------------------------------------------------------------------------
// JDAEPTContainer : destructor
//-----------------------------------------------------------------------------
JDAEPTContainer::~JDAEPTContainer()
{
	if (_piRoot) {
		_piRoot->Release();
		_piRoot = NULL;
	}

}
 
// Link the implementation to its interface
// ---------------------------------------



//TIE or TIEchain definitions
#include "TIE_JDAIPTContainer.h"
TIE_JDAIPTContainer( JDAEPTContainer);


//Methods implementation

//-----------------------------------------------------------------------------
// Implements JDAIPTContainer::GetRoot
//-----------------------------------------------------------------------------
HRESULT JDAEPTContainer::GetRoot (JDAIPTRoot ** opiRoot)
{
	//cout <<"==> Now we are in JDAEPTContainer::GetRoot  !" << endl;

	///--- Solution for Exercise : Container Management
	HRESULT hr;
	(*opiRoot) = NULL;

	if (!_piRoot) {
		//root variable not initialized yet, search in the container for an
		// object that implements TSTIAnoRoot
		CATListPtrCATBaseUnknown *pList = NULL;
		CATIClientContainer *piContainer = NULL;
		hr = this->QueryInterface(IID_CATIClientContainer, (void**) &piContainer);

		if (SUCCEEDED(hr)) {
			//cout <<"  ==> Get IID_CATIClientContainer OK !" << endl;
			hr = piContainer->ListMembers(IID_JDAIPTRoot, "JDPrdAppClientId", &pList);
			piContainer->Release();      piContainer = NULL;
		}
		else
			cout << "  ==> Get CATIClientContainer error !" << endl;
		if (SUCCEEDED(hr) && pList && pList->Size() > 0) {
			//cout <<"  ==> The number of IID_JDAIPTRoot: " << pList->Size() << endl;
			_piRoot = (JDAIPTRoot*)(*pList)[1];
		}
		else {
			_piRoot = NULL;
			//cout << "  ==> Get CATListPtrCATBaseUnknown error !" << endl;
		}
		if (pList) {
			delete pList;
			pList = NULL;
		}
	}
	  
	//Reference to be released by the calling code
	if (_piRoot) {
		_piRoot->AddRef();
		(*opiRoot) = _piRoot;
		hr = S_OK;
	} else {
		hr = E_FAIL;
	}
	///------- End Solution: Container Management

	//cout <<"==> Now end JDAEPTContainer::GetRoot  !" << endl;

	return hr;

}
