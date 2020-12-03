#include "iostream.h"
#include "SYGlobalFunctionCls1.h"
#include "SYExcelCls.h"
#include "tlhelp32.h"
#include <string>
#include <vector>

//XMLParser 
#include "CATIXMLDOMDocumentBuilder.h"
#include "CATIDOMDocument.h"
#include "CATIDOMNodeList.h"
#include "CATIDOMNamedNodeMap.h"

//system
#include "CATUnicodeString.h"

using namespace std;

void TestXML(CATUnicodeString istrXMLPath)
{

	//�ļ��Ƿ����
	if((_access(istrXMLPath, 0)) == -1 )
	{
		cout<< "The File " <<istrXMLPath<<" doesn't exist"<<endl;
		return ;
	}

	CATIXMLDOMDocumentBuilder_var builder;
	HRESULT hr = ::CreateCATIXMLDOMDocumentBuilder(builder);
	if (FAILED(hr) || builder == NULL_var) 
	{
		cout<<"# Can't Create CATIXMLDOMDocument Builder"<<endl;
		return ;
	}

	//���DOM�ĵ�
	CATListOfCATUnicodeString readOptions;
	readOptions.Append("CATDoValidation");
	CATListOfCATUnicodeString readOptionValues;
	readOptionValues.Append("false");
	CATIDOMDocument_var document;
	if (FAILED(builder->Parse(istrXMLPath, document, readOptions, readOptionValues)) && document== NULL_var)
	{
		cout<<"# Can't Parse CATIXMLDOMDocument"<<endl;
		return ;
	}

	//
	CATIDOMNodeList_var oNodeList;
	document->GetElementsByTagName("*",oNodeList);//��ȡÿ�е�һ���ַ���ǩ
	if(oNodeList!=NULL_var)
	{
		unsigned int iSize=0;
		oNodeList->GetLength(iSize);
		//cout<<"# Get element: "<<iSize<<endl;
		for(unsigned int i=0;i<iSize;i++)
		{
			CATIDOMNode_var oItem=NULL_var;
			oNodeList->Item(i,oItem);
			if(oItem!=NULL_var)
			{
				CATUnicodeString oLocalName;
				oItem->GetNodeName(oLocalName);
				cout<<i<<"--Node Name is: "<<oLocalName<<endl;

				//�������
				CATIDOMNamedNodeMap_var spDOMNamedNodeMap=NULL_var;
				oItem->GetAttributes(spDOMNamedNodeMap);
				if(spDOMNamedNodeMap!=NULL_var)
				{
					int oLength;
					spDOMNamedNodeMap->GetLength(oLength);
					for(int j=0;j<oLength;j++)
					{
						CATIDOMNode_var oSubItem=NULL_var;
						spDOMNamedNodeMap->Item(j,oSubItem);
						if(oSubItem!=NULL_var)
						{
							CATUnicodeString oNodeName;
							CATUnicodeString oNodeValue;
							oSubItem->GetNodeName(oNodeName);
							oSubItem->GetNodeValue(oNodeValue);

							cout<<"oNodeName = "<<oNodeName<<endl;
							cout<<"oNodeValue = "<<oNodeValue<<endl;
							
							
						}
					}
				}
			}
			
		}
	}


	return ;
}

//void TestExcel(CATUnicodeString istrExcelPath)
//{
//
//	SYExcelCls excelClass;
//	
//	/*pExcelClass->CreateExcel();
//	pExcelClass->SaveExcelFile(strCxcelpath.ConvertToChar(),TRUE);*/
//	
//	excelClass.OpenExcel(istrExcelPath);
//
//	//��ȡ��ǰSheet�Ѿ�ʹ�õ�����������	
//	int iFormatRows = excelClass.GetUsedRowNum();
//	int iFormatColumns = excelClass.GetUsedColNum();
//	cout<<"Row = "<<iFormatRows<<endl;
//	cout<<"iFormatColumns = "<<iFormatColumns<<endl;
//
//	for (int i = 1;i<=iFormatRows;i++)
//	{
//		for (int j = 1;j<=iFormatRows;j++)
//		{
//			CATUnicodeString strValue = excelClass.GetSheetCellData(1,i,j);
//			cout<<strValue<<endl;
//		}
//	}
//
//	excelClass.DeleteRow(3);
//
//	excelClass.SaveExcelFile(istrExcelPath.ConvertToChar(),FALSE);
//	excelClass.CloseExcelFile(istrExcelPath.ConvertToChar());
//}


//��ȡ�������еĽ���ID
void retrieveActiveProcess(const CString& strProcessName,CArray<DWORD,DWORD>& aPid)
{
	aPid.RemoveAll();
	DWORD dwPid = 0;

	CString strExeFile;
	HANDLE hHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);

	DWORD dwid = ::GetCurrentProcessId();

	if(INVALID_HANDLE_VALUE!=hHandle)
	{

		PROCESSENTRY32 stEntry;//��Ž��̿��յ���Ϣ�ṹ��

		stEntry.dwSize = sizeof(PROCESSENTRY32);

		if(Process32First(hHandle,&stEntry))
		{
			cout<<"3"<<endl;
			do{


				/*char* pch = new char[strExeFile.GetLength()+1];
				pch = strExeFile.GetBuffer(strExeFile.GetLength()+1);
				strExeFile.ReleaseBuffer();
				cout<<pch<<endl;*/


				strExeFile.Format(_T("%s"),stEntry.szExeFile);


				wcout<<(LPCTSTR)strExeFile<<endl;
				
				if (strProcessName.CompareNoCase(strExeFile) == 0)
				{
					if (dwid!=stEntry.th32ProcessID)
					{
						cout<<"2"<<endl;
						aPid.Add(stEntry.th32ProcessID);
					}
				}

			}while(Process32Next(hHandle,&stEntry));

		}


		CloseHandle(hHandle);
	}


	return ;
}
//
void CheckFileOpenOrClose(const CString& strFileName)
{
	
	CFile file;
	file.Open(strFileName,CFile::modeReadWrite);

	if(!file.GetFileName().IsEmpty())
	{
		file.Close();
	}

	else{

		cout<<"�Ѿ���"<<endl;
	}
	
}
//��������ɾ����ɾ��λ�ú���������
void TestVectorDelete()
{
	vector<int> vecOnTest;
	vecOnTest.push_back(1);
	vecOnTest.push_back(2);
	vecOnTest.push_back(3);
	vecOnTest.push_back(4);
	vecOnTest.push_back(5);

	int flag = 0;
	vector<int>::iterator iter;
	for (iter = vecOnTest.begin();iter != vecOnTest.end();++iter)
	{
		if ((*iter) == 2)
		{
			cout<<"=="<<endl;
			flag = 1;
			vecOnTest.erase(iter);
			
		}

		if (flag == 1)
		{
		
			cout<<--(*iter)<<endl;

		}else cout<<*iter<<endl;
		
	}


}
int main(int argc,char** argv)
{
	TestVectorDelete();
	/*CATUnicodeString strExcelFilePath = NULL;
	CATUnicodeString strXMLFilePath = NULL;
	CATUnicodeString strBinPath = NULL;
	SYGlobalFunctionCls1::GetCurrentBinPath("SYGlobalFunctionMod.dll",strBinPath);

	strExcelFilePath = strBinPath+"\\Test.xlsx";	
	strXMLFilePath = strBinPath+"\\utf8test.xml";
	cout<<"strExcelFilePath  = "<<strExcelFilePath<<endl;
	cout<<"strXMLFilePath  = "<<strXMLFilePath<<endl;*/
		
	//TestExcel(strExcelFilePath);

	//TestXML(strXMLFilePath);
	
	
	/*CArray<DWORD,DWORD> pid;

	retrieveActiveProcess("EXCEL.EXE",pid);

	cout<<"1"<<endl;
	for (int i = 0;i<pid.GetSize();i++)
	{
		cout<<pid.GetAt(i)<<endl;

	}*/


	//CheckFileOpenOrClose("D:\\V5CAA\\V5Functions\\SYGlobalFunctionWS\\Test.xlsx");

	return 1;
}