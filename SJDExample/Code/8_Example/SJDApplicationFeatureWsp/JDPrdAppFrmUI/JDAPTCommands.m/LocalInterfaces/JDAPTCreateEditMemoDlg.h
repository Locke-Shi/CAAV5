// COPYRIGHT Dassault Systemes 2009
//===================================================================
//
// JDAPTCreateEditMemoDlg.h
// The dialog : JDAPTCreateEditMemoDlg
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//CAA2 Wizard Generation Report
//   DIALOG
//End CAA2 Wizard Generation Report
//
//  Apr 2009  Creation: Code generated by the CAA wizard  LuJun
//===================================================================
#ifndef JDAPTCreateEditMemoDlg_H
#define JDAPTCreateEditMemoDlg_H

#include "CATDlgDialog.h"
#include "CATDlgInclude.h"

//----------------------------------------------------------------------

/**
 * Describe the purpose of your panel here.
 * <p>
 * Using this prefered syntax will enable mkdoc to document your class.
 * <p>
 * refer to programming resources of Dialog framework.
 * (consult base class description).
 */
class JDAPTCreateEditMemoDlg: public CATDlgDialog
{
  // Allows customization/internationalization of command's messages
  // ---------------------------------------------------------------
  DeclareResource( JDAPTCreateEditMemoDlg, CATDlgDialog )

  public:

  JDAPTCreateEditMemoDlg();
  virtual ~JDAPTCreateEditMemoDlg();

  void Build ();
  HRESULT GetX(double &oValue);
  HRESULT GetY(double &oValue);
  HRESULT GetZ(double &oValue);
  HRESULT SetX(double iValue);
  HRESULT SetY(double iValue);
  HRESULT SetZ(double iValue);


  protected:

  private:


//CAA2 WIZARD WIDGET DECLARATION SECTION
 CATDlgLabel*      _LabelX;
 CATDlgEditor*      _EditorX;
 CATDlgLabel*      _LabelY;
 CATDlgLabel*      _LabelZ;
 CATDlgEditor*      _EditorY;
 CATDlgEditor*      _EditorZ;
//END CAA2 WIZARD WIDGET DECLARATION SECTION
};

//----------------------------------------------------------------------

#endif
