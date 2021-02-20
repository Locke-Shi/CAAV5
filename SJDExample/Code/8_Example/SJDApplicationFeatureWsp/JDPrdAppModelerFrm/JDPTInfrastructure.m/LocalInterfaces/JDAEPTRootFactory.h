// COPYRIGHT Dassault Systemes 2009
//===================================================================
//
// JDAEPTRootFactory.h
// Provide implementation to interface
//    JDAIPTRootFactory

//
//===================================================================
//
// Usage notes:
//
//===================================================================
//CAA2 Wizard Generation Report
//EXTENSION:	JDAPTContainer
//EXTENSIONTYPE:	DataExtension

//    TIE: JDAIPTRootFactory

//End CAA2 Wizard Generation Report
//
//  Apr 2009  Creation: Code generated by the CAA wizard  LuJun
//===================================================================
#ifndef JDAEPTRootFactory_H
#define JDAEPTRootFactory_H

#include "CATBaseUnknown.h"
#include "JDAIPTRoot.h"

//-----------------------------------------------------------------------

/**
* Class representing xxx.
*
* <br><b>Role</b>: Provide the basic class function...
* <p>
* It implements the interfaces :
*  <ol>
*  <li>@href JDAIPTRootFactory
*  </ol>
*
* @href ClassReference, Class#MethodReference, #InternalMethod...
*/
class JDAEPTRootFactory: public CATBaseUnknown

{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     JDAEPTRootFactory ();
     virtual ~JDAEPTRootFactory ();

    /**
     * Implements a function from an interface.
     * @href JDAIPTRootFactory#CreateRoot
     */
     HRESULT CreateRoot (JDAIPTRoot ** opiRoot ) ;


  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  JDAEPTRootFactory (JDAEPTRootFactory &);
  JDAEPTRootFactory& operator=(JDAEPTRootFactory&);

};

//-----------------------------------------------------------------------

#endif
