// COPYRIGHT Dassault Systemes 2009
//===================================================================
//
// JDAEPTContainerInit.h
// Provide implementation to interface
//    CATInit

//
//===================================================================
//
// Usage notes:
//
//===================================================================
//CAA2 Wizard Generation Report
//EXTENSION:	JDAPTContainer
//EXTENSIONTYPE:	DataExtension

//    TIE: CATInit

//End CAA2 Wizard Generation Report
//
//  Apr 2009  Creation: Code generated by the CAA wizard  LuJun
//===================================================================
#ifndef JDAEPTContainerInit_H
#define JDAEPTContainerInit_H

#include "CATBaseUnknown.h"
#include "CATISpecObject.h"
#include "CATUnicodeString.h"

#include "CATILinkableObject.h"
#include "CATIProduct.h"

//-----------------------------------------------------------------------

/**
* Class representing xxx.
*
* <br><b>Role</b>: Provide the basic class function...
* <p>
* It implements the interfaces :
*  <ol>
*  <li>@href CATInit
*  </ol>
*
* @href ClassReference, Class#MethodReference, #InternalMethod...
*/
class JDAEPTContainerInit: public CATBaseUnknown

{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     JDAEPTContainerInit ();
     virtual ~JDAEPTContainerInit ();

    /**
     * Implements a function from an interface.
     * @href CATInit#Init
     */
     void Init (CATBoolean  iDestroyExistingData ) ;

    /**
     * Implements a function from an interface.
     * @href CATInit#GetRootContainer
     */
     CATBaseUnknown* GetRootContainer (const CATIdent  iInterfaceID ) ;

	private:
		HRESULT GetLiteralParameter(CATISpecObject_var ispiObj,CATUnicodeString iParamName,CATBaseUnknown **oLiteralParam);
		HRESULT GetRootProduct(CATILinkableObject_var ispiLinkObject,CATIProduct_var &ospiRootProduct);


  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  JDAEPTContainerInit (JDAEPTContainerInit &);
  JDAEPTContainerInit& operator=(JDAEPTContainerInit&);

};

//-----------------------------------------------------------------------

#endif
