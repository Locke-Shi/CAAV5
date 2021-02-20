//----System framework
#include "CATUnicodeString.h"

//----ObjectModelerBase
#include "CATSessionServices.h"
#include "CATDocument.h"

//----ObjectSpecsModeler
#include "CATCatalogFactoryServices.h"
#include "CATICatalog.h"
#include "CATISpecObject.h"
#include "CATISpecAttribute.h"
#include "iostream.h"


//For feature name and attributes name definitions
//#include "TSTAnoFeatureNames.h"

//----Utility function 
static HRESULT CreateStartups( CATICatalog * pICatalog );
int main( int argc, char** argv )
{
	//----Create Session
	char         * pchSessionName = "JD Session";
	CATSession   * pSession       = NULL;
	cout<<"Step 1: Session Creation"<<endl;
	HRESULT rc = Create_Session(pchSessionName, pSession);
	if (FAILED(rc))
		return 1;
  //----

	//----Catalog creation
	CATUnicodeString   ustrFileName = "JDPrdAppFeature.CATfct";
	CATICatalog      * pICatalog    = NULL;
	
	cout<<"Step 2: Catalog Creation"<<endl;
	rc = CreateCatalog(&ustrFileName, &pICatalog);    
	if (pICatalog == NULL) {
		cout <<"ERROR: failed to generate catalog"<<endl;
		cout <<" if the file exists already, you must delete it"<<endl;
		return 2;
	}
	//----

	//----Set Client Id
	CATUnicodeString ustrClientID = "JDPrdAppClientId";
    rc = pICatalog->SetClientId(&ustrClientID);
    if (FAILED(rc)) {
		 return 3;
	}
	//----

	//----StartUps creation 
    cout<<"Step 3: StartUps Creation"<<endl;
    rc = CreateStartups( pICatalog );
    if (FAILED(rc)) {
		  return 4;
    }
  //----
	
  //----Save Catalog
    cout<<"Step 4: Catalog Save"<<endl;
    rc = SaveCatalog (&pICatalog, &ustrFileName);
  	pICatalog->Release();
    if (FAILED(rc)) {
		  return 5;
    }
  //----

	//----Delete Session
  
    cout<<"Step 5: Session destruction"<<endl;
	rc = Delete_Session(pchSessionName);
    if (FAILED(rc)) {
		  return 6;
    }
	//----

	return 0;
}


//-----------------------------------------------------------------------------
// CreateStartups() 
//-----------------------------------------------------------------------------
static HRESULT CreateStartups( CATICatalog *  piCatalog )
{
  //variables
	CATBaseUnknown    * piStartup = NULL;
	CATISpecObject    * piSpecStartup = NULL; 
	CATISpecAttribute * piAttribute = NULL;
	CATUnicodeString   uName;
	CATUnicodeString   uType;
	CATUnicodeString   uSuperType;
	HRESULT hr = S_OK; 

  //Define the base feature startup
  //----
	uName  = "JDAPTBase";
	uType  = "JDAPTBase";
	hr = piCatalog->CreateSUInCatalog(&piStartup, 
		                              &uName,
                                      &uType,
									  "CATISpecObject");
  if (SUCCEEDED(hr) && piStartup) {
  	hr = piStartup->QueryInterface(IID_CATISpecObject, (void **) &piSpecStartup);
    piStartup->Release();    piStartup = NULL;
  }
  if (SUCCEEDED(hr) && piSpecStartup) {
    CATUnicodeString AttNameBase="ListComponents";
    piAttribute = piSpecStartup->AddAttribute (AttNameBase, tk_list(tk_component), sp_IN );
    piAttribute->Release();    piAttribute = NULL;
    piSpecStartup->Release();    piSpecStartup = NULL;
  }


  //Define the root feature startup
  //----
	uName  = "JDAPTRoot";
	uType  = "JDAPTRoot";
	uSuperType  = "JDAPTBase";
	hr = piCatalog->CreateSUInCatalog(&piStartup, 
		                              &uName,
                                      &uType,
									  "CATISpecObject",
                                      &uSuperType );
	if (SUCCEEDED(hr) && piStartup) {
  		hr = piStartup->QueryInterface(IID_CATISpecObject, (void **) &piSpecStartup);
		piStartup->Release();    piStartup = NULL;
	}
	if (SUCCEEDED(hr) && piSpecStartup) {
		piSpecStartup->Release();    piSpecStartup = NULL;
	}


	///--- Solution for Exercise : Applicative Feature Definition

	//Define the memo feature startup
	uName  = "JDAPTMemo";
	uType  = "JDAPTMemo";
	uSuperType  = "JDAPTBase";
	hr = piCatalog->CreateSUInCatalog(&piStartup, 
		                              &uName,
                                      &uType,
									  "CATISpecObject",
                                      &uSuperType );
	if (SUCCEEDED(hr) && piStartup) {
  		hr = piStartup->QueryInterface(IID_CATISpecObject, (void **) &piSpecStartup);
		piStartup->Release();    piStartup = NULL;
	}
	if (SUCCEEDED(hr) && piSpecStartup) {
		CATUnicodeString AttNameX="X";
		piAttribute = piSpecStartup->AddAttribute (AttNameX, tk_specobject, sp_IN );
		piAttribute->Release();		piAttribute = NULL;
		CATUnicodeString AttNameY="Y";
		piAttribute = piSpecStartup->AddAttribute (AttNameY, tk_specobject, sp_IN );
		piAttribute->Release();		piAttribute = NULL;  
		CATUnicodeString AttNameZ="Z";
		piAttribute = piSpecStartup->AddAttribute (AttNameZ, tk_specobject, sp_IN );
		piAttribute->Release();		piAttribute = NULL;  
		piSpecStartup->Release();		piSpecStartup = NULL;
	}

  ///------- End Solution: Applicative Feature Definition
	return hr;
}
