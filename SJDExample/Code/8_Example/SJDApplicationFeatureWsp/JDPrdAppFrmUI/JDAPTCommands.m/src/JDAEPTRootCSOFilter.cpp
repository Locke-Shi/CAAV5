// COPYRIGHT Dassault Systemes 2009
//===================================================================
//
// JDAEPTRootCSOFilter.cpp
// Provide implementation to interface
//    CATICSOFilter
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//  Apr 2009  Creation: Code generated by the CAA wizard  LuJun
//===================================================================
#include "JDAEPTRootCSOFilter.h"

#include "iostream.h"

 
CATImplementClass(JDAEPTRootCSOFilter,
                  DataExtension,
                  CATBaseUnknown,
                  JDAPTRoot );
 

//-----------------------------------------------------------------------------
// JDAEPTRootCSOFilter : constructor
//-----------------------------------------------------------------------------
JDAEPTRootCSOFilter::JDAEPTRootCSOFilter():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// JDAEPTRootCSOFilter : destructor
//-----------------------------------------------------------------------------
JDAEPTRootCSOFilter::~JDAEPTRootCSOFilter()
{
}
 
// Link the implementation to its interface
// ---------------------------------------



//TIE or TIEchain definitions
#include "TIE_CATICSOFilter.h"
TIE_CATICSOFilter( JDAEPTRootCSOFilter);


//Methods implementation

//-----------------------------------------------------------------------------
// Implements CATICSOFilter::CommandIsAvailable
//-----------------------------------------------------------------------------
HRESULT JDAEPTRootCSOFilter::CommandIsAvailable (const char *  iHeaderID , const CATCSO *  iCSO )
{
	//cout <<"==> Now we are in JDAEPTRootCSOFilter::CommandIsAvailable !" << endl;
	HRESULT result;
	result = E_FAIL;
	if (!strcmp (iHeaderID, "Delete")) {
		result = S_OK;
	}
	//cout <<"==> Now end JDAEPTRootCSOFilter::CommandIsAvailable !" << endl;
	return result;
}

//-----------------------------------------------------------------------------
// Implements CATICSOFilter::AvailableElements
//-----------------------------------------------------------------------------
HRESULT JDAEPTRootCSOFilter::AvailableElements (const char *  iHeaderID , const CATCSO *  iCSO , CATListValCATBaseUnknown_var **  ioAvailableElements )
{

	//cout <<"==> Now we are in JDAEPTRootCSOFilter::AvailableElements !" << endl;
   return S_OK;
}

