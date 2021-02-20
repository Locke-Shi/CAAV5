// COPYRIGHT Dassault Systemes 2009
//===================================================================
//
// JDAEPTRootFactory.cpp
// Provide implementation to interface
//    JDAIPTRootFactory
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//  Apr 2009  Creation: Code generated by the CAA wizard  LuJun
//===================================================================
#include "JDAEPTRootFactory.h"

//#include "JDAIPTRoot.h"
#include "CATISpecObject.h"
#include "CATICatalog.h"
#include "CATIContainer.h"
#include "CATUnicodeString.h"
#include "CATCatalogFactoryServices.h"

#include "iostream.h"


 
CATImplementClass(JDAEPTRootFactory,
                  DataExtension,
                  CATBaseUnknown,
                  JDAPTContainer );
 

//-----------------------------------------------------------------------------
// JDAEPTRootFactory : constructor
//-----------------------------------------------------------------------------
JDAEPTRootFactory::JDAEPTRootFactory():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// JDAEPTRootFactory : destructor
//-----------------------------------------------------------------------------
JDAEPTRootFactory::~JDAEPTRootFactory()
{
}
 
// Link the implementation to its interface
// ---------------------------------------



//TIE or TIEchain definitions
#include "TIE_JDAIPTRootFactory.h"
TIE_JDAIPTRootFactory( JDAEPTRootFactory);


//Methods implementation

//-----------------------------------------------------------------------------
// Implements JDAIPTRootFactory::CreateRoot
//-----------------------------------------------------------------------------
HRESULT JDAEPTRootFactory::CreateRoot (JDAIPTRoot ** opiRoot)
{
	//cout <<"==> Now we are in JDAEPTRootFactory::CreateRoot  !" << endl;

	//Open the catalog
	CATUnicodeString name = "JDPrdAppFeature.CATfct";
	CATUnicodeString id = "JDPrdAppClientId";
	CATIContainer_var spContainer = this;
	CATICatalog * piCatalog = NULL;

	HRESULT hr;
	hr = ::AccessCatalog(&name, &id, spContainer, &piCatalog);
	if( FAILED(hr) || piCatalog == NULL )  return hr;

	//Create the object
	CATISpecObject *piStartup = NULL;
	CATUnicodeString featureType = "JDAPTRoot";
	hr = piCatalog->RetrieveSU ((CATBaseUnknown**)&piStartup, &featureType, "CATISpecObject");
	piCatalog->Release();  piCatalog = NULL;
	if( FAILED(hr) || piStartup == NULL )  return hr;

	CATISpecObject *piInstance = NULL;
	piInstance = piStartup->Instanciate(NULL_string, spContainer);
	piStartup->Release();  piStartup = NULL;
	if( piInstance == NULL )  return E_FAIL;
	  
	hr = piInstance->QueryInterface(IID_JDAIPTRoot, (void**)opiRoot);
	piInstance->Release();  	piInstance = NULL;

	//cout <<"==> Now end JDAEPTRootFactory::CreateRoot  !" << endl;

	return hr;
}

