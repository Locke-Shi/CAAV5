// COPYRIGHT Dassault Systemes 2020
//===================================================================
//
// SYGlobalFunctionCls1.h
// Header definition of SYGlobalFunctionCls1
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
//  May 2020  Creation: Code generated by the CAA wizard  ShiYi
//===================================================================
#ifndef SYGlobalFunctionCls1_H
#define SYGlobalFunctionCls1_H

#include "SYGlobalFunctionMod.h"
#include "CATBaseUnknown.h"
#include "afx.h"
//System
#include "CATUnicodeString.h"
#include "CATTime.h"
#include "CATTimeSpan.h"

//-----------------------------------------------------------------------

/**
* Class representing xxx.
*
* <br><b>Role</b>: Provide the basic class function...
* <p>
* Do not use the @href SYGlobalFunctionCls1 constructor to
* do such and such but instead...
*
* @example
*  // example is optional
*  pObject = new SYGlobalFunctionCls1;
*  pObject->SetXXX(...);
*
* @href ClassReference, Class#MethodReference, #InternalMethod...
*/


bool ExportedBySYGlobalFunctionMod TestExistence(CATUnicodeString istrPathOrFile,double iovertime);



class ExportedBySYGlobalFunctionMod SYGlobalFunctionCls1: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors
  // -------------------------------------
     SYGlobalFunctionCls1 ();
     virtual ~SYGlobalFunctionCls1 ();

  // Copy constructor and equal operator
  // -----------------------------------
  SYGlobalFunctionCls1 (SYGlobalFunctionCls1 &);
  SYGlobalFunctionCls1& operator=(SYGlobalFunctionCls1&);

public:

	//测试文件是否存在
	static bool TestFileExistence(CATUnicodeString istrPathOrFile);

	//获取当前程序BIN目录
	static bool GetCurrentBinPath(CATUnicodeString istrDllPath,CATUnicodeString& oBinPath);

  

};

//-----------------------------------------------------------------------

#endif
