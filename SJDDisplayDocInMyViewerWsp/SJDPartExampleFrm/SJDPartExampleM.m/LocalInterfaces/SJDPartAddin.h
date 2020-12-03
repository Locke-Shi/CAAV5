// COPYRIGHT Dassault Systemes 2015
//===================================================================
//
// SJDPartAddin.h
// Provide implementation to interface
//    CATIShapeDesignWorkshopAddin

//
//===================================================================
//
// Usage notes:
//
//===================================================================
//CAA2 Wizard Generation Report
//EXTENSION:	SJDPartAddinLT
//EXTENSIONTYPE:	DataExtension

//    TIE: CATIShapeDesignWorkshopAddin

//End CAA2 Wizard Generation Report
//
//  Jan 2015  Creation: Code generated by the CAA wizard  LuJunHome
//===================================================================
#ifndef SJDPartAddin_H
#define SJDPartAddin_H

#include "CATBaseUnknown.h"
class CATCmdContainer;

//-----------------------------------------------------------------------

/**
* Class representing xxx.
*
* <br><b>Role</b>: Provide the basic class function...
* <p>
* It implements the interfaces :
*  <ol>
*  <li>@href CATIShapeDesignWorkshopAddin
*  </ol>
*
* @href ClassReference, Class#MethodReference, #InternalMethod...
*/
class SJDPartAddin: public CATBaseUnknown

{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     SJDPartAddin ();
     virtual ~SJDPartAddin ();

	 void CreateCommands();
	 CATCmdContainer *CreateToolbars();


  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  SJDPartAddin (SJDPartAddin &);
  SJDPartAddin& operator=(SJDPartAddin&);

};

//-----------------------------------------------------------------------

#endif