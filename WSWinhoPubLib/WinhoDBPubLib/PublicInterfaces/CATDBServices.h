// COPYRIGHT �Ϻ������Ϣ�������޹�˾ 2017
//===================================================================
//
// CATDBServices.h
// Header definition of CATDBServices
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
//  Jun 2017  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#ifndef CATDBServices_H
#define CATDBServices_H

#include "WinhoDBServices.h"
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"


//-----------------------------------------------------------------------

/**
* Class representing xxx.
*
* <br><b>Role</b>: Provide the basic class function...
* <p>
* Do not use the @href CATDBServices constructor to
* do such and such but instead...
*
* @example
*  // example is optional
*  pObject = new CATDBServices;
*  pObject->SetXXX(...);
*
* @href ClassReference, Class#MethodReference, #InternalMethod...
*/
class ExportedByWinhoDBServices CATDBServices: public CATBaseUnknown
{
  CATDeclareClass;

  public:

	  // Standard constructors and destructors
	  // -------------------------------------
      CATDBServices ();
      virtual ~CATDBServices ();

	  // Copy constructor and equal operator
	  // -----------------------------------
	  CATDBServices (CATDBServices &);
	  CATDBServices& operator=(CATDBServices&);

	  static HRESULT RunDBService(CATUnicodeString istrSysIdentifier,
								  CATUnicodeString istrServerAlias,
								  CATUnicodeString istrFuncName,
								  CATUnicodeString istrParams,
								  CATUnicodeString &ostrRunInfo,
								  CATUnicodeString &ostrResult,
								  CATBoolean iNeedWriteLog = CATBoolean(FALSE));

  private:

	  static HRESULT CreateParamsTxt(CATUnicodeString istrSysIdentifier,
								     CATUnicodeString istrFuncName,
								     CATUnicodeString istrParams,
								     CATUnicodeString &ostrRunInfo,
								     CATUnicodeString &ostrTxtPath);

	  static HRESULT RetrieveDBServiceResult(CATUnicodeString istrResultTxtPath,
											 CATUnicodeString &ostrRunInfo,
											 CATUnicodeString &ostrResult);

 
  
};

//-----------------------------------------------------------------------

#endif