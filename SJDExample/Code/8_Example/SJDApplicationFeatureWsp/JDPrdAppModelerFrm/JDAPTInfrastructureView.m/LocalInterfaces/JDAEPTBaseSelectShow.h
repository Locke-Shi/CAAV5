// COPYRIGHT Dassault Systemes 2009
//===================================================================
//
// JDAEPTBaseSelectShow.h
// Provide implementation to interface
//    CATISelectShow

//
//===================================================================
//
// Usage notes:
//
//===================================================================
//CAA2 Wizard Generation Report
//EXTENSION:	JDAPTBase
//EXTENSIONTYPE:	DataExtension

//    TIE: CATISelectShow

//End CAA2 Wizard Generation Report
//
//  Apr 2009  Creation: Code generated by the CAA wizard  LuJun
//===================================================================
#ifndef JDAEPTBaseSelectShow_H
#define JDAEPTBaseSelectShow_H

#include "CATExtISelectShow.h"

//-----------------------------------------------------------------------

/**
* Class representing xxx.
*
* <br><b>Role</b>: Provide the basic class function...
* <p>
* It implements the interfaces :
*  <ol>
*  <li>@href CATISelectShow
*  </ol>
*
* @href ClassReference, Class#MethodReference, #InternalMethod...
*/
class JDAEPTBaseSelectShow: public CATExtISelectShow

{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     JDAEPTBaseSelectShow ();
     virtual ~JDAEPTBaseSelectShow ();

    /**
     * Implements a function from an interface.
     * @href CATISelectShow#GetSelectShowInterface
     */
     //const IID & GetSelectShowInterface () ;

    /**
     * Implements a function from an interface.
     * @href CATISelectShow#GetElement
     */
     CATBaseUnknown * GetElement (CATPathElement * iPathElt ) ;

    /**
     * Implements a function from an interface.
     * @href CATISelectShow#GetElementForHideShow
     */
     HRESULT GetElementForHideShow (CATPathElement * iPathElt  , CATBaseUnknown *&  oSelectedObject  , int&  oPostProcess ) ;

    /**
     * Implements a function from an interface.
     * @href CATISelectShow#SelectShowPostProcess
     */
     //HRESULT SelectShowPostProcess (CATPathElement * iPathElt  , CATShowAttribut  iShowAttr ) ;


  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  JDAEPTBaseSelectShow (JDAEPTBaseSelectShow &);
  JDAEPTBaseSelectShow& operator=(JDAEPTBaseSelectShow&);

};

//-----------------------------------------------------------------------

#endif
