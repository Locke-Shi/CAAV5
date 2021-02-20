// COPYRIGHT Dassault Systemes 2009
//===================================================================
//
// JDAPTUpdateProvider.h
// Provide implementation to interface
//    CATIUpdateProvider

//
//===================================================================
//
// Usage notes:
//
//===================================================================
//CAA2 Wizard Generation Report
//IMPLEMENTATION
//    TIE: CATIUpdateProvider

//End CAA2 Wizard Generation Report
//
//  Apr 2009  Creation: Code generated by the CAA wizard  LuJun
//===================================================================
#ifndef JDAPTUpdateProvider_H
#define JDAPTUpdateProvider_H

#include "CATBaseUnknown.h"
#include "CATIDomain.h"

//-----------------------------------------------------------------------

/**
* Class representing xxx.
*
* <br><b>Role</b>: Provide the basic class function...
* <p>
* It implements the interfaces :
*  <ol>
*  <li>@href CATIUpdateProvider
*  </ol>
*
* @href ClassReference, Class#MethodReference, #InternalMethod...
*/
class JDAPTUpdateProvider: public CATBaseUnknown

{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     JDAPTUpdateProvider ();
     virtual ~JDAPTUpdateProvider ();

     /**
     * Implements a function from an interface.
     * @href CATIUpdateProvider#Update
     */
     int Update (CATBaseUnknown*  iWorkingObj  , CATIDomain_var  iDomain  = NULL_var) ;

     /**
     * Implements a function from an interface.
     * @href CATIUpdateProvider#IsUpToDate
     */
     CATBoolean IsUpToDate (CATBaseUnknown*  iWorkingObj  , CATIDomain_var  iDomain =NULL_var) const ;

     /**
     * Implements a function from an interface.
     * @href CATIUpdateProvider#SetUpToDate
     */
     void SetUpToDate (CATBaseUnknown*  iWorkingObj  , boolean  iFlag  ) ;

     /**
     * Implements a function from an interface.
     * @href CATIUpdateProvider#IsInactive
     */
     int IsInactive (CATBaseUnknown*  iWorkingObj ) const ;


  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  JDAPTUpdateProvider (JDAPTUpdateProvider &);
  JDAPTUpdateProvider& operator=(JDAPTUpdateProvider&);

};

//-----------------------------------------------------------------------

#endif
