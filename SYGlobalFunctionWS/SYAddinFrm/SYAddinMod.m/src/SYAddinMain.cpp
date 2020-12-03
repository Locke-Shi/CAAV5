// COPYRIGHT Dassault Systemes 2019
//===================================================================
//
// SYAddinMain.cpp
// Provide implementation to interface
//    CATIAfrGeneralWksAddin
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//  Mar 2019  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#include "SYAddinMain.h"
 
CATImplementClass(SYAddinMain,
                  DataExtension,
                  CATBaseUnknown,
                  CATnull );
 
MacDeclareHeader(MyAddin);
//-----------------------------------------------------------------------------
// SYAddinMain : constructor
//-----------------------------------------------------------------------------
SYAddinMain::SYAddinMain():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// SYAddinMain : destructor
//-----------------------------------------------------------------------------
SYAddinMain::~SYAddinMain()
{
}
 
// Link the implementation to its interface
// ---------------------------------------



//TIE or TIEchain definitions
#include "TIE_CATIAfrGeneralWksAddin.h"
TIE_CATIAfrGeneralWksAddin( SYAddinMain);


//Methods implementation

void SYAddinMain::CreateCommands()
{
	new MyAddin("MyTest1","ModTestSelect","SYTest2Cmd",(void *) NULL);
}

CATCmdContainer *SYAddinMain::CreateToolbars()
{
	NewAccess(CATCmdContainer, pMyToolbar, MyTlb);

	NewAccess(CATCmdStarter, pMyTest, MyTest_1);
	SetAccessCommand(pMyTest, "MyTest1");
	SetAccessChild(pMyToolbar, pMyTest);

	AddToolbarView(pMyToolbar, 1, UnDock);

	return pMyToolbar;
}