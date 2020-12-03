// COPYRIGHT �Ϻ������Ϣ�������޹�˾ 2018
//===================================================================
//
// SACDBServices.h
// Header definition of SACDBServices
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
//  Apr 2018  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#ifndef SACDBServices_H
#define SACDBServices_H

#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"

class DPInfo;
class ProductInfo;

#include <vector>
using std::vector;

//-----------------------------------------------------------------------

/**
* Class representing xxx.
*
* <br><b>Role</b>: Provide the basic class function...
* <p>
* Do not use the @href SACDBServices constructor to
* do such and such but instead...
*
* @example
*  // example is optional
*  pObject = new SACDBServices;
*  pObject->SetXXX(...);
*
* @href ClassReference, Class#MethodReference, #InternalMethod...
*/
class SACDBServices: public CATBaseUnknown
{
  CATDeclareClass;

  public:

	  // Standard constructors and destructors
	  // -------------------------------------
		 SACDBServices ();
		 virtual ~SACDBServices ();

	  // Copy constructor and equal operator
	  // -----------------------------------
	  SACDBServices (SACDBServices &);
	  SACDBServices& operator=(SACDBServices&);

	  static HRESULT RetrieveDPInfoByDPID(CATUnicodeString istrDPID,
										  DPInfo &oDPInfo);

	  static HRESULT RetrieveVCIInfoByID(CATUnicodeString istrVCIID,
										 CATUnicodeString istrBOMID,
										 vector<ProductInfo> &oProductInfoVector);

	  static HRESULT SaveSACNoteInfo(CATUnicodeString istrDOCID, 
									 vector<ProductInfo> iProductInfoVector);

	  static HRESULT RetrievePBOMInfo(CATUnicodeString istrInputParam, 
									  vector<ProductInfo> &oProductInfoVector);
};

//-----------------------------------------------------------------------

#endif