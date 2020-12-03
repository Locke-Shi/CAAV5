// COPYRIGHT Dassault Systemes 2020
//===================================================================
//
// SYGlobalFunctionCls1.cpp
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
#include "SYGlobalFunctionCls1.h"
 
CATImplementClass( SYGlobalFunctionCls1,
                   Implementation, 
                   CATBaseUnknown,
                   CATNull );
 
//-----------------------------------------------------------------------------
// SYGlobalFunctionCls1 : constructor
//-----------------------------------------------------------------------------
SYGlobalFunctionCls1::SYGlobalFunctionCls1():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// SYGlobalFunctionCls1 : destructor
//-----------------------------------------------------------------------------
SYGlobalFunctionCls1::~SYGlobalFunctionCls1()
{
}
 
//-----------------------------------------------------------------------------
// SYGlobalFunctionCls1 : copy constructor
//-----------------------------------------------------------------------------
SYGlobalFunctionCls1::SYGlobalFunctionCls1(SYGlobalFunctionCls1& original):
   CATBaseUnknown(original)
{
}
 
//-----------------------------------------------------------------------------
// SYGlobalFunctionCls1 : equal operator
//-----------------------------------------------------------------------------
SYGlobalFunctionCls1& SYGlobalFunctionCls1::operator=(SYGlobalFunctionCls1& original)
{
   CATBaseUnknown::operator=(original);
   return *this;
}
 
//�����ļ��Ƿ����_1
//���룺istrPathOrFile - �ļ�����·��+�ļ�����
//�����true - ���ڣ� false - ������
bool SYGlobalFunctionCls1::TestFileExistence(CATUnicodeString istrPathOrFile)
{
	bool bisCun=false;
	if(istrPathOrFile.GetLengthInChar() <=0)return bisCun;

	do 
	{
		if((_access(istrPathOrFile.ConvertToChar(),0)) != -1) 
		{
			//����
			bisCun=true;
			break;
		}

	} while (1);

	return bisCun;
}

//�����ļ��Ƿ����_2
//���룺istrPathOrFile - �ļ�����·��+�ļ���) ,iovertime - ʱ��
//�����true - ���ڣ� false - ������
bool TestExistence(CATUnicodeString istrPathOrFile,double iovertime)
{
	bool bisCun=false;
	if(istrPathOrFile.GetLengthInChar() <=0)return bisCun;

	CATTime time1;
	do 
	{
		if((_access(istrPathOrFile.ConvertToChar(),0)) != -1) 
		{
			//����
			bisCun=true;
			break;
		}

		CATTime time2;
		CATTimeSpan timespan=time2-time1;
		if(timespan.GetTotalSeconds() >= iovertime)
		{
			return bisCun;
		}
	} while (1);

	return bisCun;
}

//��ȡ����BinĿ¼
//���룺ģ��DLL����(ģ����+��׺)
//�����oBinPath - ����·��,bool - 
bool SYGlobalFunctionCls1::GetCurrentBinPath(CATUnicodeString istrDllPath,CATUnicodeString& oBinPath)
{
	//���dll���
	HINSTANCE hinstance = ::GetModuleHandle(istrDllPath);

	//���dll·��
	TCHAR szFilePath[MAX_PATH + 1]; 
	GetModuleFileName(hinstance, szFilePath, MAX_PATH); 
	CString sCurDir = szFilePath;

	//����·�����ļ���
	int nPos = sCurDir.ReverseFind('\\');
	CString sBinPath = sCurDir.Left(nPos);

	//����bin�ļ���·��
	BSTR path = sBinPath.AllocSysString();
	oBinPath.BuildFromBSTR(path);

	return true;
}