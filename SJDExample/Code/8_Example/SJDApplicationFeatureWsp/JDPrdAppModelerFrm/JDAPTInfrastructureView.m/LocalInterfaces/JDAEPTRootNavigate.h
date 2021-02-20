// COPYRIGHT Dassault Systemes 2009
//===================================================================
//
// JDAEPTRootNavigate.h
// Provide implementation to interface
//    CATINavigateObject

//
//===================================================================
//
// Usage notes:
//
//===================================================================
//CAA2 Wizard Generation Report
//EXTENSION:	JDAPTRoot
//EXTENSIONTYPE:	DataExtension

//    TIE: CATINavigateObject

//End CAA2 Wizard Generation Report
//
//  Apr 2009  Creation: Code generated by the CAA wizard  LuJun
//===================================================================
#ifndef JDAEPTRootNavigate_H
#define JDAEPTRootNavigate_H

#include "CATBaseUnknown.h"
class CATListValCATBaseUnknown_var;
#include "CATListOfCATUnicodeString.h"


//-----------------------------------------------------------------------

/**
* Class representing xxx.
*
* <br><b>Role</b>: Provide the basic class function...
* <p>
* It implements the interfaces :
*  <ol>
*  <li>@href CATINavigateObject
*  </ol>
*
* @href ClassReference, Class#MethodReference, #InternalMethod...
*/
class JDAEPTRootNavigate: public CATBaseUnknown

{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     JDAEPTRootNavigate ();
     virtual ~JDAEPTRootNavigate ();

    /**
     * Implements a function from an interface.
     * @href CATINavigateObject#GetIdentificators
     */
     CATListValCATUnicodeString* GetIdentificators () ;

    /**
     * Implements a function from an interface.
     * @href CATINavigateObject#GetChildren
     */
     CATListValCATBaseUnknown_var* GetChildren () ;


  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  JDAEPTRootNavigate (JDAEPTRootNavigate &);
  JDAEPTRootNavigate& operator=(JDAEPTRootNavigate&);

};

//-----------------------------------------------------------------------

#endif
