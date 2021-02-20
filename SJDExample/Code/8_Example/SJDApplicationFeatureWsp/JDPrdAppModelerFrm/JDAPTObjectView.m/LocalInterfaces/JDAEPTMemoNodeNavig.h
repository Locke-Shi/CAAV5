// COPYRIGHT Dassault Systemes 2009
//===================================================================
//
// JDAEPTMemoNodeNavig.h
// Provide implementation to interface
//    CATINavigModify

//
//===================================================================
//
// Usage notes:
//
//===================================================================
//CAA2 Wizard Generation Report
//EXTENSION:	JDAPTMemo_node
//EXTENSIONTYPE:	DataExtension

//    TIE: CATINavigModify

//End CAA2 Wizard Generation Report
//
//  Apr 2009  Creation: Code generated by the CAA wizard  LuJun
//===================================================================
#ifndef JDAEPTMemoNodeNavig_H
#define JDAEPTMemoNodeNavig_H

#include "CATNodeExtension.h"

//-----------------------------------------------------------------------

/**
* Class representing xxx.
*
* <br><b>Role</b>: Provide the basic class function...
* <p>
* It implements the interfaces :
*  <ol>
*  <li>@href CATINavigModify
*  </ol>
*
* @href ClassReference, Class#MethodReference, #InternalMethod...
*/
class JDAEPTMemoNodeNavig: public CATNodeExtension

{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     JDAEPTMemoNodeNavig ();
     virtual ~JDAEPTMemoNodeNavig ();

    /**
     * Implements a function from an interface.
     * @href CATINavigModify#UpdateElem
     */
     void UpdateElem (CATNavigInstance*  iInst ) ;

    /**
     * Implements a function from an interface.
     * @href CATINavigModify#ModifyShortHelp
     */
     //HRESULT ModifyShortHelp (CATUnicodeString&  ioText ) ;

    /**
     * Implements a function from an interface.
     * @href CATINavigModify#Select
     */
     //void Select (int  iMode ) ;

    /**
     * Implements a function from an interface.
     * @href CATINavigModify#IsSelected
     */
     //int IsSelected () ;


  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  JDAEPTMemoNodeNavig (JDAEPTMemoNodeNavig &);
  JDAEPTMemoNodeNavig& operator=(JDAEPTMemoNodeNavig&);

};

//-----------------------------------------------------------------------

#endif
