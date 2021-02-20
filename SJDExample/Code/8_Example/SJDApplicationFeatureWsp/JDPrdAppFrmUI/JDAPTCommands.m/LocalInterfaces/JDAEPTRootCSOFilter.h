// COPYRIGHT Dassault Systemes 2009
//===================================================================
//
// JDAEPTRootCSOFilter.h
// Provide implementation to interface
//    CATICSOFilter

//
//===================================================================
//
// Usage notes:
//
//===================================================================
//CAA2 Wizard Generation Report
//EXTENSION:	JDAPTRoot
//EXTENSIONTYPE:	DataExtension

//    TIE: CATICSOFilter

//End CAA2 Wizard Generation Report
//
//  Apr 2009  Creation: Code generated by the CAA wizard  LuJun
//===================================================================
#ifndef JDAEPTRootCSOFilter_H
#define JDAEPTRootCSOFilter_H

#include "CATBaseUnknown.h"
#include "CATCSO.h"
#include "CATLISTV_CATBaseUnknown.h"

//-----------------------------------------------------------------------

/**
* Class representing xxx.
*
* <br><b>Role</b>: Provide the basic class function...
* <p>
* It implements the interfaces :
*  <ol>
*  <li>@href CATICSOFilter
*  </ol>
*
* @href ClassReference, Class#MethodReference, #InternalMethod...
*/
class JDAEPTRootCSOFilter: public CATBaseUnknown

{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     JDAEPTRootCSOFilter ();
     virtual ~JDAEPTRootCSOFilter ();

    /**
     * Implements a function from an interface.
     * @href CATICSOFilter#CommandIsAvailable
     */
     HRESULT CommandIsAvailable (const char *  iHeaderID  , const CATCSO *  iCSO  ) ;

    /**
     * Implements a function from an interface.
     * @href CATICSOFilter#AvailableElements
     */
     HRESULT AvailableElements (const char *  iHeaderID  , const CATCSO *  iCSO  , CATListValCATBaseUnknown_var **  ioAvailableElements  ) ;


  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  JDAEPTRootCSOFilter (JDAEPTRootCSOFilter &);
  JDAEPTRootCSOFilter& operator=(JDAEPTRootCSOFilter&);

};

//-----------------------------------------------------------------------

#endif
