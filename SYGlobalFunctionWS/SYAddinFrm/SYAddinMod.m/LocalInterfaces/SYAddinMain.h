// COPYRIGHT Dassault Systemes 2019
//===================================================================
//
// SYAddinMain.h
// Provide implementation to interface
//    CATIAfrGeneralWksAddin

//
//===================================================================
//
// Usage notes:
//
//===================================================================
//CAA2 Wizard Generation Report
//EXTENSION:	CATnull
//EXTENSIONTYPE:	DataExtension

//    TIE: CATIAfrGeneralWksAddin

//End CAA2 Wizard Generation Report
//
//  Mar 2019  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#ifndef SYAddinMain_H
#define SYAddinMain_H

#include "CATBaseUnknown.h"

//ApplicationFrame 
#include "CATCommandHeader.h"
#include "CATCreateWorkshop.h"
#include "CATCmdContainer.h"

//-----------------------------------------------------------------------

/**
* Class representing xxx.
*
* <br><b>Role</b>: Provide the basic class function...
* <p>
* It implements the interfaces :
*  <ol>
*  <li>@href CATIAfrGeneralWksAddin
*  </ol>
*
* @href ClassReference, Class#MethodReference, #InternalMethod...
*/
class SYAddinMain: public CATBaseUnknown

{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     SYAddinMain ();
     virtual ~SYAddinMain ();
	 void CreateCommands();
	 CATCmdContainer *CreateToolbars();


  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  SYAddinMain (SYAddinMain &);
  SYAddinMain& operator=(SYAddinMain&);

};

//-----------------------------------------------------------------------

#endif
