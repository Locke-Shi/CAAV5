// COPYRIGHT Dassault Systemes 2009
//===================================================================
//
// JDAEPTMemoCSOFilter.cpp
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
#include "JDAEPTMemoCSOFilter.h"

#include "iostream.h"

 
CATImplementClass(JDAEPTMemoCSOFilter,
                  DataExtension,
                  CATBaseUnknown,
                  JDAPTMemo );
 

//-----------------------------------------------------------------------------
// JDAEPTMemoCSOFilter : constructor
//-----------------------------------------------------------------------------
JDAEPTMemoCSOFilter::JDAEPTMemoCSOFilter():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// JDAEPTMemoCSOFilter : destructor
//-----------------------------------------------------------------------------
JDAEPTMemoCSOFilter::~JDAEPTMemoCSOFilter()
{
}
 
// Link the implementation to its interface
// ---------------------------------------



//TIE or TIEchain definitions
#include "TIE_CATICSOFilter.h"
TIE_CATICSOFilter( JDAEPTMemoCSOFilter);


//Methods implementation

//-----------------------------------------------------------------------------
// Implements CATICSOFilter::CommandIsAvailable
//-----------------------------------------------------------------------------
HRESULT JDAEPTMemoCSOFilter::CommandIsAvailable (const char *  iHeaderID , const CATCSO *  iCSO )
{
	//cout <<"==> Now we are in JDAEPTMemoCSOFilter::CommandIsAvailable !" << endl;
   return S_OK;
}

//-----------------------------------------------------------------------------
// Implements CATICSOFilter::AvailableElements
//-----------------------------------------------------------------------------
HRESULT JDAEPTMemoCSOFilter::AvailableElements (const char *  iHeaderID , const CATCSO *  iCSO , CATListValCATBaseUnknown_var **  ioAvailableElements )
{

	//cout <<"==> Now we are in JDAEPTMemoCSOFilter::AvailableElements !" << endl;
   return S_OK;
}

