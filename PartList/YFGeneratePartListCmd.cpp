#include "YFGeneratePartListCmd.h"




CATCreateClass( YFGeneratePartListCmd);

YFGeneratePartListCmd::YFGeneratePartListCmd() :
CATStateCommand ("YFGeneratePartListCmd", CATDlgEngOneShot, CATCommandModeExclusive) 
{
	//about license
	//�������� - ��ʼ��������
	char * pubKey = "<DSAKeyValue><P>neI7nZPv+DQ+yZ/ZCntD7nrK4UY/iM1jAa/HqWTrqmHPEvy7SCUk2dh6PwW825hm3jVtI+Sz8mr3n/P4mVHA4cQKwhg8g7sex/SOedYz3LHT9jqfPMDMNSJm5QZKqQs+FZ/Qfr77JAIMyA9t6WWhSGaqMWv25Lygj0zKAzDJcRE=</P><Q>t5t0R22tOntHivrDco6enAATZK0=</Q><G>GnnAV0QQdMXLWMpaBVnCaoBJRaCF+KK4KHuP+eWBUagkEYwIPfL/kCAP2LS7ATijwKghorpO28mL2+xKw9msQFGzbi4mTIEHO5rO06xGtl/xrskiTli1S7/OtLC1dDaufEx04L8OkWf0ZQdTQT+nB09nB1EA3isQHV9jW8HGnGc=</G><Y>md9FuUYIBrLNCT8Jm+cYDHih1WwFp0cLHqwnUV0pXU3rCaG71Ft4aRIGlmIR40vqhbyDdLaIms6+c3AiaVdqfGawAnWtdSJgOEsdPIWWdg/MygoKI8msfNSjJwtNbvQJhP6M97vXo44YRIIOGne7PZSJxSMuBzTr9je7/gzM72w=</Y><Seed>/sbM1BbHzBPxW/nWDgTElXztVGs=</Seed><PgenCounter>Lw==</PgenCounter><X>mqTbw51X8QRPw1uwVpEyaXNpdSc=</X></DSAKeyValue>";
	_pAuthorizedService = (SotosAuthorizedService *)CreateSotosAuthorizedServiceObj("127.0.0.1", 8090, pubKey);//"127.0.0.1"
	string errMsg = _pAuthorizedService->InitiateService();
	if(errMsg!="")
	{
		delete _pAuthorizedService;
		_pAuthorizedService = NULL;
		::MessageBox( NULL, _T( "The Server Is Not Opened!" ), _T( "Note" ), MB_OK | MB_ICONERROR);
		RequestDelayedDestruction() ;
	}
	//about license
	//�������� - ��֤������
	try
	{
		if(!_pAuthorizedService->VerifyModuleIdAndName("YFAI2011", "2D_Partlist"))	throw "False";

	}catch (char* strError)
	{
		cout<<strError<<endl;
		delete _pAuthorizedService;
		_pAuthorizedService = NULL;
		::MessageBox( NULL, _T( "License Is Illegal!" ), _T( "Note" ), MB_OK | MB_ICONERROR);	
		RequestDelayedDestruction() ;

	}catch(...)
	{
		delete _pAuthorizedService;
		_pAuthorizedService = NULL;
		::MessageBox( NULL, _T( "License Is Wrong!" ), _T( "Note" ), MB_OK | MB_ICONERROR);	
		RequestDelayedDestruction() ;
	}
	//about license
	if (_pAuthorizedService == NULL)
	{
		::MessageBox( NULL, _T( "License Is Null!" ), _T( "Note" ), MB_OK | MB_ICONERROR);	
		RequestDelayedDestruction();
	}

	CmdInIt();
}

YFGeneratePartListCmd::YFGeneratePartListCmd(CATUnicodeString strFatherName):
CATStateCommand ("YFGeneratePartListCmd", NULL , CATCommandModeShared)   
{
	_strFatherName = strFatherName;
	CmdInIt();
	_pCmdNoteCls = new YFPartListCmdNote();
	_pCmdNoteObjCls = new YFPartListCmdNoteObj();
}
void YFGeneratePartListCmd::CmdInIt()
{

	_PreviewDlg = NULL;
	_pDlg = NULL;
	_EditorSelectEBOM = NULL;
	_SelectorListSelectSUProduct = NULL;
	_ComboSelectAssembly = NULL;
	_EditorSULevel = NULL;
	_EditorExpDepth = NULL;
	_BTSelectEBOM = NULL;
	_strTestDirection= "C:\\ToolTestData";
	_pElmAgtSelProduct  = NULL;
	_pDlgAgtSelProduct = NULL;
	 _spSelProduct = NULL;
	_FileSelectEBOM= NULL;
	_intSelectRow = 0;
	_pCmdNoteCls = NULL;
	_pCmdNoteObjCls = NULL;

	//��¼��Ϣ
	//����
	_strUserInfo = "YFPartList";

	//��������
		//��ʼ��:�������ʼ�������´��뽫�޷�ִ��
	WSAData data;
	if(WSAStartup(MAKEWORD(1,1),&data)!=0)
	{
		_strErrorTime = GetTimeFunc();
		cout<<_strErrorTime<<":��ʼ������,�޷���ȡ������Ϣ..."<<endl;
	}
	
	char host[255];
		//��ȡ������:Ҳ����ʹ��GetComputerName()�������
	if(gethostname(host,sizeof(host))==SOCKET_ERROR)
	{
		_strErrorTime = GetTimeFunc();
		cout<<_strErrorTime<<":�޷���ȡ������..."<<endl;
	}

	CATUnicodeString strPcName = host;
	_strUserInfo.Append("��");
	_strUserInfo.Append(strPcName);
	
	//��ʼʱ��
		//ʱ��һ
	CATUnicodeString strStartTime = GetTimeFunc();
	_strUserInfo.Append("��");
	_strUserInfo.Append(strStartTime);
	_strUserInfo.Append("��");
		//ʱ���(���ڼ����������ʱ��)
	CATTime currentTime = CATTime::GetCurrentLocalTime();
	_intStartHour = currentTime.GetHour();
	_intStartMinute = currentTime.GetMinute();
	_intStartSecond = currentTime.GetSecond();

	//��ȡ�������
	char* docPath = "KBETracePath";															//����ģ��Ļ���������
	char* docPathValue = NULL;																//����Ī��Ļ���������Ӧ��·
	CATLibStatus envState = CATGetEnvValue(docPath,&docPathValue);							//��ñ���ģ��Ļ���������ֵ
	_strUserInfoDirection = docPathValue;
	_strUserInfoDirection.Append("KBETracePath\\KBE_Traces\\CATIA");
	if(DirExists(_strUserInfoDirection.ConvertToChar()))
	{
		_strUserInfoDirection.Append("\\2DTools.txt");
	}
	else
	{
		_strUserInfoDirection = _strTestDirection;
		CreateDirectory(_strUserInfoDirection,NULL) ;
		_strUserInfoDirection.Append("\\2DTools.txt");
	}

	CATUnicodeString strErrorDir = "C:\\cattmp";
	if(!DirExists(strErrorDir.ConvertToChar()))
	{
		CreateDirectory(strErrorDir,NULL) ;
	}
	_strErrorPath = "C:\\cattmp\\KBEErrorLog_PartList.txt";
}
   
YFGeneratePartListCmd::~YFGeneratePartListCmd()
{
	//about license
	if (_pAuthorizedService)
	{
		// getchar();
		_pAuthorizedService->LicenceReturn("YFAI2011", "2D_Partlist");	

		// getchar();
		delete _pAuthorizedService;
		_pAuthorizedService = NULL;
	}

	if (_pDlg != NULL)
	{
		_pDlg -> RequestDelayedDestruction();
	}

	_EditorSelectEBOM = NULL;
	_SelectorListSelectSUProduct = NULL;
	_ComboSelectAssembly = NULL;
	_EditorSULevel = NULL;
	_EditorExpDepth = NULL;
	_BTSelectEBOM = NULL;
	_pElmAgtSelProduct  = NULL;
	_pDlgAgtSelProduct = NULL;
	_spSelProduct = NULL;
	_FileSelectEBOM= NULL;
	if (_pCmdNoteCls != NULL)
	{
		_pCmdNoteCls->Release(); 
		_pCmdNoteCls=NULL;
	}
	if (_pCmdNoteObjCls != NULL)
	{
		_pCmdNoteObjCls->Release(); 
		_pCmdNoteObjCls=NULL;
	}

	if (_PreviewDlg != NULL)
		_PreviewDlg -> RequestDelayedDestruction();	
	if (_pDlg != NULL)
		_pDlg -> RequestDelayedDestruction();

	//����ʱ��
	CATTime currentEndTime = CATTime::GetCurrentLocalTime();
	int intEndHour = currentEndTime.GetHour();
	int intEndMinute = currentEndTime.GetMinute();
	int intEndSecond = currentEndTime.GetSecond();
	_strUserInfo.Append("��ʱ��");
	if (intEndHour - _intStartHour)
	{
		CATUnicodeString strHour = NULL;
		strHour.BuildFromNum(intEndHour - _intStartHour);
		_strUserInfo.Append(strHour);
		_strUserInfo.Append("ʱ");
	}

	if (intEndMinute - _intStartMinute)
	{
		CATUnicodeString strMin = NULL;
		strMin.BuildFromNum(intEndMinute - _intStartMinute);
		_strUserInfo.Append(strMin);
		_strUserInfo.Append("��");
	}

	if (intEndSecond - _intStartSecond)
	{
		CATUnicodeString strSec = NULL;
		strSec.BuildFromNum(intEndSecond - _intStartSecond);
		_strUserInfo.Append(strSec);
		_strUserInfo.Append("��");
	}


	ofstream file(_strUserInfoDirection.ConvertToChar(),ios::app);
	file<<_strUserInfo<<"\n";
	file.close(); //ʹ�����֮����Ҫ�ر�
	
}
//������������ں���
//���룺void
//�����void
//���أ�void
void YFGeneratePartListCmd::BuildGraph()
{
	/*cout<<"��ʼ"<<endl;
	cout<<_strUserInfoDirection<<endl;
	cout<<_strErrorPath<<endl;*/
	/*_strErrorTime = GetTimeFunc();
	ofstream errorFile(_strErrorPath.ConvertToChar(),ios::app);
	errorFile<<_strErrorTime<<_strErrorPath<<_strUserInfoDirection;
	errorFile.close(); */
	//������ڽ���
	//----------------------------------
	_pDlg = new YFGeneratePartListDlg();
	_pDlg -> SetFather(this);
	_pDlg -> Build();
	_pDlg->SetOKSensitivity(CATDlgDisable);
	_pDlg->SetCANCELSensitivity(CATDlgDisable);

	_PreviewDlg = new YFPreviewPanelDlg;
	_PreviewDlg -> SetFather(_pDlg);
	_PreviewDlg->Build();

	
	//�����ʼֵ�趨
	//----------------------------------
	_BTSelectEBOM = _pDlg ->ReturnBTSelectEBOM();
	_EditorSelectEBOM = _pDlg ->ReturnEditorSelectEBOM();
	_ComboSelectAssembly = _pDlg ->ReturnComboSelectAssembly();
	_SelectorListSelectSUProduct = _pDlg ->ReturnSelectorListSelectSUProduct();
	_EditorSULevel = _pDlg ->ReturnEditorSULevel();
	_EditorExpDepth = _pDlg ->ReturnEditorExpDepth();
	_MultiListOfPreview = _PreviewDlg->ReturnPreviewMultiList();


	//�����ʼ��
	_pDlg -> SetVisibility(CATDlgShow);
	InitDataFunc();

	_SelectorListSelectSUProduct->ClearLine();
	_SelectorListSelectSUProduct->SetLine("Select A Product Node On Tree",0);
	_EditorSULevel->SetText(CATUnicodeString("Set The First Node Level On 2DTable")); 
	_EditorSelectEBOM->SetText(CATUnicodeString("Please Select A EBOM File")); 
	_EditorExpDepth->SetIntegerValue(2); 
	//_pDlg -> SetVisibility(CATDlgShow);

	//ѡ�����趨
	//----------------------------------
	//1ѡ�����
	_pElmAgtSelProduct = new CATOtherDocumentAgent("ElmAgtSelProductId","YFSelProductCmd","YFDrwToolsPartListM");
	CATLISTV(CATString) TypeListExpDir = NULL;
	TypeListExpDir.Append(CATString("CATIProduct"));
	_pElmAgtSelProduct->SetOrderedTypeList(TypeListExpDir);
	_pElmAgtSelProduct->SetBehavior(CATDlgEngWithPrevaluation|CATDlgEngWithPSOHSO|CATDlgEngWithTooltip|CATDlgEngOneShot) ;

	//1�������
	/*_pDlgAgtSelProduct = new CATDialogAgent("DlgAgtSelProductId");
	_pDlgAgtSelProduct->AcceptOnNotify(_SelectorListSelectSUProduct, _SelectorListSelectSUProduct->GetListSelectNotification());*/

	//0��ʼ״̬����
	CATDialogState * pInitialState = GetInitialState("StInitialId");
	//pInitialState->AddDialogAgent(_pDlgAgtSelProduct);
	pInitialState->AddDialogAgent(_pElmAgtSelProduct);
   
	//1״̬����
	/*CATDialogState * pSelProductState = AddDialogState("StSelProduct");
	pSelProductState->AddDialogAgent(_pElmAgtSelProduct);
	pSelProductState->AddDialogAgent(_pDlgAgtSelProduct);*/

	//0��ʼ״̬�л�
	//AddTransition( pInitialState,pInitialState, (IsOutputSetCondition(_pDlgAgtSelProduct)),Action ((ActionMethod) &YFGeneratePartListCmd::ChangeToModleWindow));

	//1״̬�л�
	AddTransition( pInitialState,pInitialState, (IsOutputSetCondition(_pElmAgtSelProduct)),Action ((ActionMethod) &YFGeneratePartListCmd::ShotElmAgtSelProductFunc));
 
	//�¼��趨
	//----------------------------------
	AddAnalyseNotificationCB (_pDlg, _pDlg -> GetDiaPREVIEWNotification(),(CATCommandMethod)&YFGeneratePartListCmd::ActionPreview,NULL);
	AddAnalyseNotificationCB (_pDlg, _pDlg -> GetDiaCANCELNotification(),(CATCommandMethod)&YFGeneratePartListCmd::ActionCancel,NULL);
	AddAnalyseNotificationCB (_pDlg, _pDlg -> GetDiaOKNotification(),(CATCommandMethod)&YFGeneratePartListCmd::ActionOk,NULL);
	AddAnalyseNotificationCB (_pDlg, _pDlg -> GetWindCloseNotification(),(CATCommandMethod)&YFGeneratePartListCmd::ActionClose,NULL);
	AddAnalyseNotificationCB (_SelectorListSelectSUProduct, _SelectorListSelectSUProduct -> GetListSelectNotification(),(CATCommandMethod)&YFGeneratePartListCmd::ChangeToModleWindowFunc,NULL);
	AddAnalyseNotificationCB (_BTSelectEBOM, _BTSelectEBOM -> GetPushBActivateNotification(),(CATCommandMethod)&YFGeneratePartListCmd::SelEBOMExcelFunc,NULL);

		//Ԥ���趨
	AddAnalyseNotificationCB (_PreviewDlg, _PreviewDlg -> GetDiaCANCELNotification(),(CATCommandMethod)&YFGeneratePartListCmd::ActionPreviewCancelFunc,NULL);
	AddAnalyseNotificationCB (_PreviewDlg, _PreviewDlg -> GetDiaOKNotification(),(CATCommandMethod)&YFGeneratePartListCmd::ActionPreviewOkFunc,NULL);
	AddAnalyseNotificationCB (_PreviewDlg, _PreviewDlg -> GetWindCloseNotification(),(CATCommandMethod)&YFGeneratePartListCmd::ActionPreviewCloseFunc,NULL);
		//Ԥ�������Ӧ
	AddAnalyseNotificationCB (_MultiListOfPreview, _MultiListOfPreview->GetListActivateNotification(),(CATCommandMethod)&YFGeneratePartListCmd::ActionChangeYesOrNoFunc,NULL);
	
}


//������������رպ���
//���룺cmd-��ťָ�룬evt-�¼�ָ�룬data-����
//�����void
//���أ�void
void YFGeneratePartListCmd::ActionClose(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	//�ر�
	RequestDelayedDestruction();
}

//������������ȡ������
//���룺cmd-��ťָ�룬evt-�¼�ָ�룬data-����
//�����void
//���أ�void
void YFGeneratePartListCmd::ActionCancel(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	//cout<<"Enter Function:ActionCancel()..."<<endl;
	//ɾ�����ɵ���ϸ��
	DeleteTabelBomFunc();
	_pDlg->SetVisibility (CATDlgHide);
	RequestDelayedDestruction();
}

//������������ȷ������
//���룺cmd-��ťָ�룬evt-�¼�ָ�룬data-����
//�����void
//���أ�void
void YFGeneratePartListCmd::ActionOk(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	//ȷ��
	RequestDelayedDestruction();
	
}

//������������Ԥ������
//���룺cmd-��ťָ�룬evt-�¼�ָ�룬data-����
//�����void
//���أ�void
void YFGeneratePartListCmd::ActionPreview(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	//��ת��Ԥ������
	_MultiListOfPreview->ClearLine();
	_vecPreviewBomList.clear();
	_vecModelInfoList.clear();

	//�ж���������ֵ�Ƿ��Ѿ�����
	CATUnicodeString strEBOMPath = _EditorSelectEBOM->GetText();//EBOM·��
	CATUnicodeString strDepth = _EditorExpDepth->GetText();//���
	CATUnicodeString strLevel = _EditorSULevel->GetText();//�㼶
	CATUnicodeString strProduct = NULL;
	_SelectorListSelectSUProduct->GetLine(strProduct,0);
	if (strEBOMPath == "Please Select A EBOM File" || strDepth == NULL || strLevel == "Set The First Node Level On 2DTable"|| strLevel == NULL || strProduct == "Select A Product Node On Tree")
	{
		CAAMessageBox("Error input !","Notice");
		return ;
	}
	
	//�ж�����ĵȼ���ϸ�����
	int intNumDepth = 0;
	int intNumLevel = 0;
	int intCovertIsOk = 0;
	intCovertIsOk = strDepth.ConvertToNum(&intNumDepth);
	if (intCovertIsOk == 0 && strDepth != "bottom" && strDepth != NULL) {CAAMessageBox("Please input correct value !","Notice");return ;}//�жϣ�����������

	intCovertIsOk = strLevel.ConvertToNum(&intNumLevel);
	if (intCovertIsOk == 0) {CAAMessageBox("Please input correct value !","Notice");return ;}//�жϣ������������

	if (strDepth == "bottom" || strDepth == NULL) intNumDepth = 1024;//�жϣ�����Ϊbottom�Լ�Ϊ��

	if (intNumDepth<2) {CAAMessageBox("Error : Depth less than 2 !","Notice");return ;}//�жϣ�ϸ��������С��2

	CATUnicodeString error = NULL;
	//�ж��Լ���λ��ѡ�ڵ���Լ��丸�ڵ�	
	CATBoolean rc = CheckSelectNodeFunc(_spSelProduct,error);
	if(rc == FALSE) CAAMessageBox(error,"Notice");

	//������ģ��ѡ�ڵ������нڵ�ʵ�����Ͷ�Ӧ����
	rc = GetPartListInfoFunc(_spSelProduct,intNumDepth,1,error);
	if (rc == FALSE) {CAAMessageBox(error,"Notice");return ;}
	
	//��ȡEBOM�е���Ϣ
	GetPreviewBomInfoFunc(intNumLevel,intNumDepth);

	//�ж�EBOM���Ӽ�����ģ�е��Ӽ��Ƿ�ƥ��
	CheckChildNodeFunc();


	//���������Ϣ��ѡ���Ƿ����
	if (_vecModelNotInEBOM.size() || _vecEBOMNotInModel.size())
	{
		
		CATUnicodeString strModelNotInEBOM = NULL;//EBOM�в�������Щ
		CATUnicodeString strEBOMNotInModel = NULL;//����в�������Щ
		if (_vecModelNotInEBOM.size())
		{
			for (int i = 0;i<_vecModelNotInEBOM.size();i++)
				strModelNotInEBOM.Append(_vecModelNotInEBOM[i]+"\n");
		}

		if (_vecEBOMNotInModel.size())
		{
			for (int j = 0;j<_vecEBOMNotInModel.size();j++)
				strEBOMNotInModel.Append(_vecEBOMNotInModel[j]+"\n");
		}

		CATDlgNotify* notify = new CATDlgNotify(_pDlg,"Waring!",CATDlgNfyOKCancel);
		notify->SetText("The following PartNumber in EBOM not found in the Model or have wrong in the quantity:\n" + strEBOMNotInModel + "And The following PartNumber in Model not found in the EBOM or have wrong in the quantity:\n" + strModelNotInEBOM + "\nPlease click OK to continue generate Table based on EBOM And Cancel to stop !");
		notify->SetVisibility(CATDlgShow);
		AddAnalyseNotificationCB (notify, notify -> GetNfyOKNotification(),(CATCommandMethod)&YFGeneratePartListCmd::ContinueToGengerateFunc,NULL);
		AddAnalyseNotificationCB (notify, notify -> GetNfyCancelNotification(),(CATCommandMethod)&YFGeneratePartListCmd::ActionDlgCancelFunc,notify);

	}

	if (_vecModelNotInEBOM.size() == 0 && _vecEBOMNotInModel.size() == 0)
	{
		int intRow=0;
		for(vector<PartListInfo*>::iterator it  = _vecPreviewBomList.begin();it!=_vecPreviewBomList.end();it++)
		{
			_MultiListOfPreview->SetColumnItem(1,(*it)->userDefineLevel,intRow,CATDlgDataModify);
			_MultiListOfPreview->SetColumnItem(2,(*it)->YFPartNumber,intRow,CATDlgDataModify);
			_MultiListOfPreview->SetColumnItem(3,(*it)->VersionNo,intRow,CATDlgDataModify);
			_MultiListOfPreview->SetColumnItem(4,(*it)->PartName,intRow,CATDlgDataModify);
			_MultiListOfPreview->SetColumnItem(5,(*it)->Quantity,intRow,CATDlgDataModify);
			_MultiListOfPreview->SetColumnItem(6,(*it)->Material,intRow,CATDlgDataModify);
			_MultiListOfPreview->SetColumnItem(7,(*it)->Notes,intRow,CATDlgDataModify);
			_MultiListOfPreview->SetColumnItem(8,"Y",intRow,CATDlgDataModify);
			intRow++;
		}

		_PreviewDlg->SetVisibility(CATDlgShow);
		_pDlg->SetVisibility(CATDlgHide);
	}

	
	return ;
}


//������ѡ��Excel�ɹ���Ӧ����
//���룺cmd-��ťָ�룬evt-�¼�ָ�룬data-����
//�����void
//���أ�void
void YFGeneratePartListCmd::ChooseFileOKFunc( CATCommand *, CATNotification* , CATCommandClientData data )
{
	if(_FileSelectEBOM != NULL)
	{		
		CATUnicodeString oCurrentDirectory("");
		_FileSelectEBOM->GetSelection (oCurrentDirectory);
		_EditorSelectEBOM->SetText(oCurrentDirectory);
		_FileSelectEBOM->SetVisibility(CATDlgHide);

		CATUnicodeString error = NULL;
		CATBoolean rc = ReadEBOMInfoFunc(error);
		if (rc == FALSE) {CAAMessageBox(error,"Notice");RequestDelayedDestruction() ;}
	}

}
//������ȡ��ѡ��Excel��Ӧ����
//���룺cmd-��ťָ�룬evt-�¼�ָ�룬data-����
//�����void
//���أ�void
void YFGeneratePartListCmd::ChooseFileCancelFunc( CATCommand *, CATNotification* , CATCommandClientData data )
{
	if(_FileSelectEBOM != NULL)
	{
		_FileSelectEBOM->SetVisibility(CATDlgHide);
	}
}

//����������ѡ��excel��������
//���룺cmd-��ťָ�룬evt-�¼�ָ�룬data-����
//�����void
//���أ�void
void YFGeneratePartListCmd::SelEBOMExcelFunc(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	if (_FileSelectEBOM == NULL)
	{
		_FileSelectEBOM = new CATDlgFile(_pDlg, "Choose Open Path");
		CATUnicodeString nameExtension[3]={"Excel File (*.xlsx)","Excel File (*.xl)","Excel File (*.xls)"};
		CATString filterExtension[3]={"*.xlsx","*.xl","*.xls"};
		_FileSelectEBOM->SetFilterStrings(nameExtension, filterExtension, 3);
		AddAnalyseNotificationCB (_FileSelectEBOM,_FileSelectEBOM->GetDiaOKNotification(),(CATCommandMethod)& YFGeneratePartListCmd::ChooseFileOKFunc,NULL);
		AddAnalyseNotificationCB (_FileSelectEBOM,_FileSelectEBOM->GetDiaCANCELNotification(),(CATCommandMethod)& YFGeneratePartListCmd::ChooseFileCancelFunc,NULL);
	}
	_FileSelectEBOM->SetVisibility(CATDlgShow);
}


//��������ת���ڵ�ģ�ʹ���
//���룺cmd-��ťָ�룬evt-�¼�ָ�룬data-����
//�����void
//���أ�void
void YFGeneratePartListCmd::ChangeToModleWindowFunc(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	//cout<<"������ת"<<endl;
	CATUnicodeString pCurrentSelectProdName = NULL;
	int intSeletLine = _ComboSelectAssembly -> GetSelect();
	_ComboSelectAssembly -> GetLine(pCurrentSelectProdName,intSeletLine);
	CATLISTP(CATFrmWindow) listOfCurWindows = _pLayout->GetWindowList() ;
	int intFlag = 0;
	//������ǰ����ģ���������޵�ǰѡ�����ģ
	if (listOfCurWindows.Size())
	{
		for (int i =1;i<=listOfCurWindows.Size();i++)
		{
			CATFrmEditor* pEditor= listOfCurWindows[i]->GetEditor();
			if (pEditor)
			{
				CATDocument* pUNITDoc = pEditor->GetDocument();

				CATIDocId* oDocId= NULL;
				CATUnicodeString oType = NULL;
				pUNITDoc->GetDocId(&oDocId);
				if (oDocId)
				{
					oDocId->GetType(oType); 
					if(oType == "CATProduct")
					{
						CATUnicodeString pWindName = listOfCurWindows[i]->GetBaseName();
						if(pWindName == pCurrentSelectProdName)
						{
							intFlag = 1;
							_pLayout->SetCurrentWindow(listOfCurWindows[i]);
							break;
						}
					}
				}
			}
		}
		if (intFlag == 0) CAAMessageBox("The Window may be closed ! ","Notice");
	}
}

//������ѡ����ʼ�ܳɣ�������Ӧ
//���룺data-����
//�����void
//���أ�void
void YFGeneratePartListCmd::ShotDlgAgtSelProductFunc( void * data )
{
	//cout<<"ѡ��ڵ�"<<endl;
	_pDlgAgtSelProduct->InitializeAcquisition();
}

//������ѡ����ʼ�ܳɣ���ȡ����ֵ
//���룺data-����
//�����void
//���أ�void
void YFGeneratePartListCmd::ShotElmAgtSelProductFunc( void * data )
{
	//cout<<"��ȡ�ڵ�"<<endl;
	_spSelProduct = GetSelectObjectFromAgent(_pElmAgtSelProduct);
	if (  _spSelProduct !=  NULL_var)
	{
		_SelectorListSelectSUProduct->ClearLine();
		CATIProduct_var spiProduct = _spSelProduct;
		_SelectorListSelectSUProduct->SetLine(spiProduct->GetPartNumber(),0);
		
		//����Ĭ�ϵȼ�
		CATUnicodeString strLevel = GetLevelNumberFunc(_spSelProduct);
		_EditorSULevel->SetText(strLevel);

	}
	_pElmAgtSelProduct->InitializeAcquisition();
}


/************************************************************************/
/*								ADD FUNCTION							*/
/************************************************************************/

//��������ȡExcel������
//���룺void
//�����oError-������Ϣ
//���أ�TRUE or FALSE
CATBoolean YFGeneratePartListCmd::ReadEBOMInfoFunc(CATUnicodeString& oError)
{
	//cout<<"Start ReadEBOMInfo()..."<<endl;
	//��ȡ�����excelǰ���ڵ�excel����
	_oldPid = GetIdFunc();
	//��ȡEBOM����
	HRESULT hr = S_OK;
	
	_Application			ExcelApp;
	_Worksheet				WorkSheet;
	_Workbook				WorkBook;
	Workbooks				WorkBooks;
	Worksheets				WorkSheets;
	Range					ExlRag;
	CATTry
	{
		CATUnicodeString pBomPath= NULL;
		_EditorSelectEBOM->GetLine(pBomPath,0);
		//cout<<"pBomPath="<<pBomPath.ConvertToChar() <<endl;
		//�ж��Ƿ���ѡȡ��excel ��ʽ
		if (pBomPath.SubString(pBomPath.GetLengthInChar()-5,5 )==CATUnicodeString(".xlsx")||pBomPath.SubString(pBomPath.GetLengthInChar()-4,4 )==CATUnicodeString(".xls"))
		{
			
			hr = CoInitialize(NULL);//û��֮ǰ����EXCEL����ʧ��
			//��excel����
	
			if (!ExcelApp.CreateDispatch( _T( "Excel.Application" ), NULL ))
			{
				::MessageBox( NULL, _T( "����Excel����ʧ�ܣ�" ), _T( "������ʾ��" ), MB_OK | MB_ICONERROR);	
				_strErrorTime = GetTimeFunc();
				ofstream errorFile(_strErrorPath.ConvertToChar(),ios::app);
				errorFile<<_strErrorTime<<":����Excel����ʧ��!\n";
				errorFile.close(); 
				return FALSE;
				//exit(-1);
			}
		
			COleVariant	covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
			ExcelApp.SetDisplayAlerts(FALSE);
			
			if((_access(pBomPath.ConvertToChar(), 0))== -1)
			{
				_strErrorTime = GetTimeFunc();
				ofstream errorFile(_strErrorPath.ConvertToChar(),ios::app);
				errorFile<<_strErrorTime<<":The EBom doesn't exist!\n";
				errorFile.close(); 
				return FALSE;
				/*oWorkBooks.AttachDispatch(oExcelApp.GetWorkbooks(), TRUE);
				oWorkBook.AttachDispatch(oWorkBooks.Add(covOptional));*/
			}else{

				WorkBooks.AttachDispatch(ExcelApp.GetWorkbooks(), TRUE);
				CString strFileName=pBomPath.ConvertToChar();
				LPDISPATCH lpDisp = WorkBooks.Open(strFileName,
					_variant_t(vtMissing),_variant_t(vtMissing),_variant_t(vtMissing),_variant_t(vtMissing),_variant_t(vtMissing),
					_variant_t(vtMissing),_variant_t(vtMissing),_variant_t(vtMissing),_variant_t(vtMissing),_variant_t(vtMissing),
					_variant_t(vtMissing),_variant_t(vtMissing),_variant_t(vtMissing),_variant_t(vtMissing));

				WorkBook.AttachDispatch(lpDisp,TRUE);
			}

			CATUnicodeString usSheetName;
			if(usSheetName!="")
			{
				WorkSheets.AttachDispatch(WorkBook.GetSheets(),true);
				WorkSheet.AttachDispatch(WorkSheets.GetItem(_variant_t(usSheetName.ConvertToChar())),TRUE);
			}
			else
			{
				WorkSheet.AttachDispatch( WorkBook.GetActiveSheet(), TRUE);
				WorkSheet.Activate();
			}
			
			ExlRag.AttachDispatch(WorkSheet.GetRange(_variant_t("A1"),_variant_t(vtMissing)));

			//��ȡ����
			int intRowNum = 10;
			int intColumnNum = 1;
			while (1)
			{

				PartListInfo* temoInfoList=new PartListInfo();
				temoInfoList->InitialDataFunc();

				//EBOM������Ϊ�������Ƚ�������ͬ��ţ�
				temoInfoList->intEBOMRow = intRowNum - 10;

				//���(��һ��)
				_variant_t vNoValue = ExlRag.GetItem(_variant_t(RowNum),_variant_t(1));
				CATUnicodeString strNo = NULL;
				strNo.BuildFromBSTR(_bstr_t(vNoValue));
				if (strNo == NULL) break;
				temoInfoList->No = strNo;

				//�㼶(2-13�У���*���м�Ϊ�㼶)
				int intLevel = 1;
				CATUnicodeString strLevel = NULL;
				if(strNo == "0")
					strLevel = "0";
				else{
					FindPointsGetLevelFunc(strNo,intLevel);
					strLevel.BuildFromNum(intLevel);
				}
				temoInfoList->Level = strLevel;

				//����
				_variant_t vNumberValue = ExlRag.GetItem(_variant_t(RowNum),_variant_t(14));
				CATUnicodeString strNumber = NULL;
				strNumber.BuildFromBSTR(_bstr_t(vNumberValue));
				temoInfoList->Quantity = strNumber;

				//�����
				intColumnNum = GetColumnNumFunc(ExlRag,"�ӷ������"); 
				if (intColumnNum == 0) { oError = "I/O error:Please ensure that the Excel field meets the standard!";_newPid = GetIdFunc();RemoveExcelProcessFunc(_oldPid,_newPid);return FALSE;}
				_variant_t vPartNoValue = ExlRag.GetItem(_variant_t(intRowNum),_variant_t(intColumnNum));
				CATUnicodeString strPartNo = NULL;
				strPartNo.BuildFromBSTR(_bstr_t(vPartNoValue));
				if (strPartNo.SearchSubString("\n")!=-1)
				{
					int pos = strPartNo.SearchSubString("\n");
					strPartNo = strPartNo.SubString(pos+1,strPartNo.GetLengthInChar()-pos-1);
				}
				temoInfoList->YFPartNumber = strPartNo;	
				

				//�汾
				intColumnNum = GetColumnNumFunc(ExlRag,"�汾��\n���ӷ棩"); 
				if (intColumnNum == 0) {oError = "I/O error:Please ensure that the Excel field meets the standard!";_newPid = GetIdFunc();RemoveExcelProcessFunc(_oldPid,_newPid);return FALSE;}
				_variant_t vVersionValue = ExlRag.GetItem(_variant_t(intRowNum),_variant_t(intColumnNum));
				CATUnicodeString strVersion = NULL;
				strVersion.BuildFromBSTR(_bstr_t(vVersionValue));
				temoInfoList->VersionNo = strVersion;

				//�����
				intColumnNum = GetColumnNumFunc(ExlRag,"�����/����"); 
				if (intColumnNum == 0) {oError = "I/O error:Please ensure that the Excel field meets the standard!";_newPid = GetIdFunc();RemoveExcelProcessFunc(_oldPid,_newPid);return FALSE;}
				_variant_t vPartNumberValue = ExlRag.GetItem(_variant_t(intRowNum),_variant_t(intColumnNum));
				CATUnicodeString strPartNumber = NULL;;	
				strPartNumber.BuildFromBSTR(_bstr_t(vPartNumberValue));
				temoInfoList->PartName = strPartNumber;

				//����
				intColumnNum = GetColumnNumFunc(ExlRag,"��������"); 
				if (intColumnNum == 0) {oError = "I/O error:Please ensure that the Excel field meets the standard!";_newPid = GetIdFunc();RemoveExcelProcessFunc(_oldPid,_newPid);return FALSE;}
				_variant_t vMaterialValue = ExlRag.GetItem(_variant_t(intRowNum),_variant_t(intColumnNum));
				CATUnicodeString strMaterial = NULL;
				strMaterial.BuildFromBSTR(_bstr_t(vMaterialValue));
				temoInfoList->Material = strMaterial;

				//��ע
				intColumnNum = GetColumnNumFunc(ExlRag,"��ע"); 
				if (intColumnNum == 0) {oError = "I/O error:Please ensure that the Excel field meets the standard!";_newPid = GetIdFunc();RemoveExcelProcessFunc(_oldPid,_newPid);return FALSE;}
				_variant_t vNoteValue = ExlRag.GetItem(_variant_t(intRowNum),_variant_t(intColumnNum));
				CATUnicodeString strNote = NULL;
				strNote.BuildFromBSTR(_bstr_t(vNoteValue));
				temoInfoList->Notes = strNote;

				_vecEBOMInfos.push_back(temoInfoList);
				intRowNum++;
			}
			
			_newPid = GetIdFunc();
			RemoveExcelProcessFunc(_oldPid,_newPid);
			
		}else{

			oError = "Please choose the correct Excel format!";
			return FALSE;
		}
	}CATCatch(CATError,er)
	{
		_strErrorTime = GetTimeFunc();
		ofstream errorFile(_strErrorPath.ConvertToChar(),ios::app);
		errorFile<<_strErrorTime<<":Open Excel error!\n";
		errorFile.close(); 
		return FALSE;
	}CATEndTry

		return TRUE;
}

//�����������ֶ��ж���������
//���룺iExlRag-Excel����,iColumnText-Ҫ���ҵ��ı�����
//�����void
//���أ�int - �ı��������ں���
int YFGeneratePartListCmd::GetColumnNumFunc(Range iExlRag,const CATUnicodeString& iColumnText)
{
	//cout<<"Enter Function: GetColumnNum() ..."<<endl;

	int intColumn = 1;
	while (1)
	{
		_variant_t vValue = iExlRag.GetItem(_variant_t(8),_variant_t(intColumn));
		char cValue[1024] ={0};
		strcpy(cValue,(LPCSTR)_bstr_t(vValue));
		CATUnicodeString strText = cValue;
		//if(strText != NULL) cout<<strText<<endl;
		//if (strText == NULL) return 0;//���û�б�����
		if (intColumn > 75)  return 0;//���û�б�����

		if (strText == iColumnText)	return intColumn;//����ҵ��򷵻ض�Ӧ����

		intColumn++; 
	}
}

//�������رպ�̨excel����
//���룺iOldPid-��������ǰ���̺�,iNewPid-�������к���̺�
//�����void
//���أ�void
void YFGeneratePartListCmd::RemoveExcelProcessFunc(vector<int> iOldPid,vector<int> iNewPid)
{
	//������Ҫ�رյ�excel��������
	vector<int> excelNeedClose;

	//������ͬpid����������һ�����������
	//case 1:2����������Ϊ��
	if (iOldPid.size() != 0 && iNewPid.size() != 0)
	{
		for (int i = 0;i<iNewPid.size();i++)
		{
			int flag = 0;
			for (int j = 0;j<iOldPid.size();j++)
			{
				if (iNewPid[i] == iOldPid[j])
				{
					flag = 1;
					break;
				}
			}

			if (flag == 0)
			{
				excelNeedClose.push_back(iNewPid[i]);
			}
		}
	}
	//case 2:��������excelǰ����û��excel����
	if (iOldPid.size() == 0 && iNewPid.size() != 0) excelNeedClose.assign(iNewPid.begin(),iNewPid.end());

	//case 3:��û������excel
	if (iOldPid.size() == 0 && iNewPid.size() == 0) return ;

	//�ر�excel
	if (excelNeedClose.size()!=0)
	{
		for (int i = 0;i<excelNeedClose.size();i++)
		{
			//cout<<excelNeedClose[i]<<endl;
			HANDLE hprocess=::OpenProcess(PROCESS_ALL_ACCESS,FALSE,excelNeedClose[i]);
			if(hprocess!=NULL)
			{
				::TerminateProcess(hprocess,0);
				::CloseHandle(hprocess);
			}
		}
	}

	return ;
}

//����:��ȡ����ID
//����:void
//���:void
//����:vector<int>-���̺�����
vector<int> YFGeneratePartListCmd::GetIdFunc()
{
	vector<int> pIDVec;
	setlocale(LC_ALL, "");
	HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);    //�������̿���

	if (INVALID_HANDLE_VALUE == hProcess)
	{
		_strErrorTime = GetTimeFunc();
		ofstream errorFile(_strErrorPath.ConvertToChar(),ios::app);
		errorFile<<_strErrorTime<<":��ȡ������Ϣʧ��!\n";
		errorFile.close(); 
		//printf("��ȡ������Ϣʧ�ܣ�����\n");
		//return FALSE;
	}

	//�ɹ���ȡ������Ϣ
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	BOOL moreProc = Process32First(hProcess, &pe32);

	while (moreProc)   //ö�����н���
	{
		WCHAR* pName = pe32.szExeFile;
		char pID[20] = "";

		_ultoa(pe32.th32ProcessID, pID, 10);  

		int nLen = WideCharToMultiByte( CP_ACP, 0,pName, -1, NULL, 0, NULL, NULL );   
		char* pResult = new char[nLen];  
		WideCharToMultiByte( CP_ACP, 0, pName, -1, pResult, nLen, NULL, NULL );  

		CATUnicodeString pIdNum(pID);
		CATUnicodeString pExeName(pResult);
		int IdNum = 0;
		pIdNum.ConvertToNum(&IdNum);
		if (pExeName == "EXCEL.EXE")
		{
			//_tprintf(_T("�������ƣ�%s\n"), pe32.szExeFile);
			//_tprintf(_T("����ID�ţ�%u\n"), pe32.th32ProcessID);
			pIDVec.push_back(IdNum);
		}

		moreProc = Process32Next(hProcess, &pe32);
	}

	CloseHandle(hProcess);        //�ͷŽ��̿���
	return pIDVec;
}

//���������Դ�ӡ
//���룺iVecTest - ������
//�����void
//���أ�void
void YFGeneratePartListCmd::printInfoFunc(vector< PartListInfo* > iVecTest)
{
	//cout<<"����Ԫ�ظ��� = "<<iVecTest.size()<<endl;
	if (iVecTest.size()>0)
	{
		for (vector<PartListInfo*>::iterator it = iVecTest.begin();it!=iVecTest.end();it++)
		{
			cout<<endl;
			cout<<(*it)->TableNo<<")("<<(*it)->Level<<")("<<(*it)->YFPartNumber<<")("<<(*it)->VersionNo<<")("<<(*it)->PartName<<")("<<(*it)->Quantity<<")("<<(*it)->Material<<")("<<(*it)->Notes<<endl;

		}
	}
	
}

//�������ж�ѡ�нڵ��Ƿ���ϱ�׼(��ѡ�ڵ��Լ��丸���Ӽ��������Ƿ��EBOM�е�һ��)
//���룺ispiSelectNode - ��ѡ�ڵ�
//�����oError-������Ϣ
//���أ�TRUE or FALSE
CATBoolean YFGeneratePartListCmd::CheckSelectNodeFunc(CATISpecObject_var ispiSelectNode,CATUnicodeString& oError)
{
	//cout<<"Enter Function: CheckSelectNode���ж���ѡ�ڵ��Ƿ����Ҫ��..."<<endl;
	if (!ispiSelectNode) {oError = "Select Error!"; return FALSE;}

	CATUnicodeString strPartName = NULL;
	CATUnicodeString strYFPartNumber = NULL;

	//�ҳ�EBOM�����ж�Ӧ�������
	vector<PartListInfo*>	vecTempList;
	CATIProduct_var spiSelectPro = ispiSelectNode;
	if (!spiSelectPro) {oError = "Select Error!"; return FALSE;}
	strPartName = spiSelectPro->GetPartNumber();
	int intPos = strPartName.SearchSubString("_");
	strYFPartNumber = strPartName.SubString(0,intPos);
	if (_vecEBOMInfos.size()>0)
	{
		for (vector<PartListInfo*>::iterator it = _vecEBOMInfos.begin();it!=_vecEBOMInfos.end();it++)
		{
			if ((*it)->YFPartNumber == strYFPartNumber)
				vecTempList.push_back(*it);//�ҳ���EBOM�����뵱ǰ�ڵ����������һ���������
		}
	}
	if (vecTempList.size()!=0)//�жϸ����Ƿ�һ��
	{
		CATIProduct_var spiFatherPro = spiSelectPro->GetFatherProduct();
		if (!!spiFatherPro)
		{
			int intFlag = 0;
			strPartName = spiFatherPro->GetPartNumber();
			int intPos = strPartName.SearchSubString("_");
			strYFPartNumber = strPartName.SubString(0,intPos);
			for (vector<PartListInfo*>::iterator it = vecTempList.begin();it!=vecTempList.end();it++)
			{
				int intLevel = 0,fatherLevel = 0;
				(*it)->Level.ConvertToNum(&intLevel);
				
				for (int i = (*it)->intEBOMRow;i>=0;i--)//�ӵ�ǰ�ڵ��������Ѱ�ҵ�һ������
				{
					_vecEBOMInfos[i]->Level.ConvertToNum(&fatherLevel);	
					if (intLevel == fatherLevel + 1)
					{
						if (strYFPartNumber == _vecEBOMInfos[i]->YFPartNumber)
						{
							intFlag = 1;
							_intSelectRow = (*it)->intEBOMRow;
							//cout<<"��ǰѡ���к� = "<<_intSelectRow<<endl;
						}
							
						break;
					}
				}
			}

			if (intFlag == 0) {oError = "The selected father node :"+ strPartName + " does not match the EBOM table !";_SelectorListSelectSUProduct->SetLine("Select A Product Node On Tree",0);return FALSE;}
		}else{//������ģ���ϼ�û�и���
			
			for (vector<PartListInfo*>::iterator it = _vecEBOMInfos.begin();it!=_vecEBOMInfos.end();it++)
			{
				if (strYFPartNumber == (*it)->YFPartNumber)
				{
					_intSelectRow = (*it)->intEBOMRow;
					//cout<<"��ǰѡ���к� = "<<_intSelectRow<<endl;
					break;
				}
			}
		}

	}else{//�������û��

		oError = "The selected node :"+ strPartName + " does not match the EBOM table !";_SelectorListSelectSUProduct->SetLine("Select A Product Node On Tree",0);return FALSE;
	}

	return TRUE;
}
//�������ж��Ӽ��Ƿ�ƥ��
//���룺void
//�����void
//���أ�void
void YFGeneratePartListCmd::CheckChildNodeFunc()
{
	//cout<<"Enter Function: CheckChildNode"<<endl;
	_vecModelNotInEBOM.clear();
	_vecEBOMNotInModel.clear();
	//�ж���ģ����������Ƿ���EBOM�д���
	for (map<CATUnicodeString,int>::iterator it_map_1 = _vecModelInfoList.begin();it_map_1!=_vecModelInfoList.end();it_map_1++)
	{
		int intFlag_1 = 0;	
		for (vector<PartListInfo*>::iterator it_vec_1 = _vecPreviewBomList.begin();it_vec_1!=_vecPreviewBomList.end();it_vec_1++)
		{
			int intQuantity = 0;
			(*it_vec_1)->Quantity.ConvertToNum(&intQuantity);

			if (it_map_1->first == (*it_vec_1)->YFPartNumber && it_map_1->second == intQuantity)
			{

				intFlag_1 = 1;
				break;
			}
		}

		if (intFlag_1 == 0)	_vecModelNotInEBOM.push_back(it_map_1->first);	//EBOM�в�������Щ
	}


	//�ж�EBOM����������Ƿ�����ģ�д���
	for (vector<PartListInfo*>::iterator it_vec_2 = _vecPreviewBomList.begin();it_vec_2!=_vecPreviewBomList.end();it_vec_2++)
	{
		int intFlag_2 = 0;
		int intQuantity = 0;
		(*it_vec_2)->Quantity.ConvertToNum(&intQuantity);
		
		for (map<CATUnicodeString,int>::iterator it_map_2 = _vecModelInfoList.begin();it_map_2!=_vecModelInfoList.end();it_map_2++)
		{	
			if (it_map_2->first == (*it_vec_2)->YFPartNumber && it_map_2->second == intQuantity)
			{
				intFlag_2 = 1;
				break;
			}
		}

		if (intFlag_2 == 0)	_vecEBOMNotInModel.push_back((*it_vec_2)->YFPartNumber);	//����в�������Щ
	}
}

//��������ȡ��Ӧ�ȼ�
//���룺ispiSelectNode - ��ѡ�ڵ�
//�����void
//���أ�CATUnicodeString - ����Ӧ�ȼ�
CATUnicodeString YFGeneratePartListCmd::GetLevelNumberFunc(CATIProduct_var ispiSelectNode)
{
	//cout<<"Enter Function : GetLevelNumber()"<<endl;

	//ͨ������ŶԱȣ���ȡ��Ӧ�ȼ�
	CATUnicodeString strNodeName = ispiSelectNode->GetPartNumber();
	int intPos = strNodeName.SearchSubString("_");
	CATUnicodeString strYFPartNumber = strNodeName.SubString(0,intPos);
	if (_vecEBOMInfos.size()!=0)
	{
		vector<PartListInfo*>::iterator it_BomInfo;
		for(it_BomInfo = _vecEBOMInfos.begin();it_BomInfo != _vecEBOMInfos.end();it_BomInfo++)
		{	
			if((*it_BomInfo)->YFPartNumber == strYFPartNumber)
			{
				//cout<<"Excel������� = "<<(*it_BomInfo)->YFPartNumber<<endl;
				return (*it_BomInfo)->Level;
			}		
		}	
	}

	return -1;
}
//�������ж�С����,��ȡ�ȼ�
//���룺iStr - ����ַ���,iNum - �ݹ����
//�����void
//���أ�void
void YFGeneratePartListCmd::FindPointsGetLevelFunc(CATUnicodeString iStr,int& iNum)
{
	if (iStr != "0" || iStr!= NULL)
	{
		if (iStr.SearchSubString(".")!=-1)
		{
			iStr.Remove(0,iStr.SearchSubString(".")+1);
			iNum++;
			FindPointsGetLevelFunc(iStr,iNum);
		}
	}
}

//��������ȡ��ѡ�ڵ������еĽڵ�����
//���룺ispiRootProduct - ��ѡ�ڵ�,iUserDepth - �û��������,iDepth-Ĭ�����
//�����oError - ������Ϣ
//���أ�TRUE or FALSE
CATBoolean YFGeneratePartListCmd::GetPartListInfoFunc(CATIProduct_var ispiRootProduct,int iUserDepth,int iDepth,CATUnicodeString& oError)
{
	//cout<<"Enter Function:GetPartListInfo ..."<<endl;
	CATBoolean rc  = TRUE;
	if (!ispiRootProduct) { oError = "Select node is NULL ��";return FALSE;}

	//��ʵ������������
	CATUnicodeString strPartName = ispiRootProduct->GetPartNumber();
	int intPos = strPartName.SearchSubString("_");
	if (intPos!=-1)
	{
		CATUnicodeString strYFPartNumber = strPartName.SubString(0,intPos);
		_mapProducts[(CATIProduct*)ispiRootProduct] = strYFPartNumber;//�Ѷ�Ӧ��product���ʹ�������
		if (_vecModelInfoList.size()!=0)
		{
			int intFlag = 0;
			for (map<CATUnicodeString,int>::iterator it = _vecModelInfoList.begin();it!=_vecModelInfoList.end();it++)
			{
				if (it->first == strYFPartNumber)
				{
					it->second++;//��ͬ����ţ�������1
					intFlag = 1;
					break;
				}
			}
			if (intFlag!=1)
				_vecModelInfoList[strYFPartNumber] = 1;

		}else //�������Ϊ�������
			_vecModelInfoList[strYFPartNumber] = 1;
	}
	
	//���ﵽָ���㼶�������ݹ飬���ػ�ȡ����Ϣ
	if (iDepth == iUserDepth) return TRUE;

	//�ݹ�
	if (ispiRootProduct->GetChildrenCount())
	{
		CATListValCATBaseUnknown_var* listOfChildren = ispiRootProduct->GetChildren("CATIProduct");
		for (int i = 1;i<=listOfChildren->Size();i++)
		{
			CATIProduct_var spiChildProduct = (*listOfChildren)[i];
			if (!!spiChildProduct)
			{
				rc = GetPartListInfoFunc(spiChildProduct,iUserDepth,iDepth+1,oError);
				if (rc == FALSE) {oError = "Internal error !";return FALSE;}
			}	
		}
	}

	return TRUE;
}
//���������ݻ�ȡ�ڵ�ĵ�һ�������һ�����ҳ�EBOM������λ��(Useless)
//���룺iStartNumber - ��ʼ���,iEndNumber - �������,iDepth-Ĭ�����
//�����oStartRow - ��ʼ����,oEndRow - ��������
//���أ�void
void YFGeneratePartListCmd::GetEBOMPositionFunc(CATUnicodeString iStartNumber,CATUnicodeString iEndNumber,int& oStartRow,int& oEndRow)
{
	for (vector<PartListInfo*>::iterator it = _vecEBOMInfos.begin();it!=_vecEBOMInfos.end();it++)
	{
		if((*it)->YFPartNumber == iStartNumber && oStartRow > (*it)->intEBOMRow)
			oStartRow = (*it)->intEBOMRow;
		

		if((*it)->YFPartNumber == iEndNumber && oEndRow < (*it)->intEBOMRow)
			oEndRow = (*it)->intEBOMRow;
	}
	return;
}
//��������ȡ��ҪԤ������Ϣ
//���룺iUserDefineLevel - �û��Զ�����ʼ�ȼ�,iUserDefineDepth - Ĭ����ʼ�ȼ�
//�����void
//���أ�void
void YFGeneratePartListCmd::GetPreviewBomInfoFunc(int iUserDefineLevel,int iUserDefineDepth)
{
	//��ʼ�ȼ�
	int intStartLevel = 0;
	CATUnicodeString strStartLevel = _vecEBOMInfos[_intSelectRow]->Level;
	strStartLevel.ConvertToNum(&intStartLevel);

	
	for (int i = _intSelectRow;i<_vecEBOMInfos.size();i++)
	{		
		int intLevel = 0;
		CATUnicodeString strLevel = _vecEBOMInfos[i]->Level;
		strLevel.ConvertToNum(&intLevel);

		//������ѡ�ڵ���������ͬ��Žڵ�
		int intFlag = 0;
		if (_vecEBOMInfos[i]->No == _vecEBOMInfos[_intSelectRow]->No)
		{
			int intEBOMRow = _vecEBOMInfos[i]->intEBOMRow;
			if (intEBOMRow - _intSelectRow < 2) //�ж�2����ͬ
				intFlag = 1;					//����Ҫ����
		}
	
		//�жϺ�ʱ��������
		if(intLevel == intStartLevel && i!=_intSelectRow && intStartLevel != 0 && !intFlag) break;
			
		//cout<<"��һ�ȼ� = "<<level<<endl;
		if (intLevel <= intStartLevel + iUserDefineDepth - 1)
		{
			//cout<<level<<"<="<<startLevel<<"+"<<iUserDefineDepth<<"-1"<<endl;
			//�ȼ�
			CATUnicodeString strUserDefineLevel = NULL;
			strUserDefineLevel.BuildFromNum(iUserDefineLevel + intLevel - intStartLevel);
			_vecEBOMInfos[i]->userDefineLevel = strUserDefineLevel;

			//��������
			_vecPreviewBomList.push_back(_vecEBOMInfos[i]);
		}
		
	}
	return ;
}

//�������ж���ģ���Ƿ����EBOM�нڵ�(Useless)
//���룺iYFPartNumber - YF�����
//�����void
//���أ�int 1-�У�0-��
int YFGeneratePartListCmd::ProIsExistInModelFunc(CATUnicodeString iYFPartNumber)
{
	//cout<<"Enter Function:HavePartOrNot ..."<<endl;
	
	int intFlag = 0;
	for (map<CATUnicodeString,int>::iterator it=_vecModelInfoList.begin();it!=_vecModelInfoList.end();it++)
	{
		if (iYFPartNumber == it->first)
		{
			intFlag = 1;
			break;
		}
	}
	
	
	return intFlag;
}
//�������ж��Ƿ����Part
//���룺ispiProduct - ��Ҫ�жϵĽڵ�
//�����void
//���أ�int 1-�У�0-��
void YFGeneratePartListCmd::HavePartOrNotFunc(CATIProduct_var ispiProduct,int& oFlag)
{
	if (!ispiProduct) 
	{
		oFlag =  -1;
		return;
	}


	//cout<<"child num = "<<ispiProduct->GetChildrenCount()<<endl;
	//�ݹ�
	if (ispiProduct->GetChildrenCount())
	{
		CATListValCATBaseUnknown_var* listOfChildren = ispiProduct->GetChildren("CATIProduct");
		for (int i = 1;i<=listOfChildren->Size();i++)
		{
			CATIProduct_var spiChildProduct = (*listOfChildren)[i];
			if (!!spiChildProduct)
			{
				HavePartOrNotFunc(spiChildProduct,oFlag);	
				return ;
			}	
		}

	}else{//���������һ��

		CATIProduct_var spiRefProduct = ispiProduct->GetReferenceProduct();
		if(spiRefProduct != NULL_var)
		{
			CATILinkableObject_var spiLinkObject = spiRefProduct;
			CATDocument *pPartDoc = spiLinkObject->GetDocument();
			if (pPartDoc)
			{
				CATIDocId* oDocID=NULL;
				CATUnicodeString oType = NULL;
				pPartDoc->GetDocId(&oDocID);
				oDocID->GetType(oType);

				if ( oType == "CATPart") 
				{
					CATIContainer* piSpecCont = NULL;
					CATIContainerOfDocument_var spiContOfDoc(pPartDoc);
					if(SUCCEEDED(spiContOfDoc->GetSpecContainer(piSpecCont)) && piSpecCont)
					{
						CATIPrtContainer_var spiPrtContainer(piSpecCont);
						CATIPrtPart_var spiPrtPart = spiPrtContainer->GetPart();
						int intFlag = CheckPartIsNullFunc(spiPrtPart);//�ж�part�Ƿ�Ϊ��

						if (intFlag ==1) oFlag = 1;
						else oFlag =0;
					}
				}
				else oFlag = 0;
			}
		}

	}

}

//�������ж��Ƿ�Ϊ��Part
//���룺ispiPrtPart - ��ǰPart
//�����void
//���أ�int 1-�У�0-��
int YFGeneratePartListCmd::CheckPartIsNullFunc(CATIPrtPart_var ispiPrtPart)
{

	HRESULT hr = S_OK;
	CATIPartRequest_var spiPartRequest = ispiPrtPart;
	int flag = 0;
	if (!!spiPartRequest)
	{
		CATListValCATBaseUnknown_var listOfBUPartObjs;
		hr = spiPartRequest->GetAllBodies("MfDefault3DView",listOfBUPartObjs);//��ȡ�����壬��ͼ�μ��ڵ�

		if (listOfBUPartObjs.Size())
		{
			
			for (int i = 1;i<=listOfBUPartObjs.Size();i++)
			{

				//==��ȡ�������ͼ�μ����������
				CATIBodyRequest_var spiBodyRequest = listOfBUPartObjs[i];
				if (!!spiBodyRequest)
				{
					CATListValCATBaseUnknown_var listOfBUBodyObjs;
					hr = spiBodyRequest->GetResults("MfDefault3DView",listOfBUBodyObjs);
				
					if (listOfBUBodyObjs.Size()) flag = 1;

				}
				//==
			}

		}
	}

	return flag;
}
//�������ж��Ƿ���������ͬ���
//���룺iCurrentFlag - YF��ǰ�к�,iVecTableBom-Ԥ����������
//�����void
//���أ�int 1-ǰ����ͬ,�м����,2-��ǰһ����һ��������һ������ͷ��� 3-�ͺ��治һ����ǰ��һ������β���
int YFGeneratePartListCmd::ContinuousSameNoOrNotFunc(int iCurrentFlag,vector<PartListInfo*> iVecTableBom)
{
	//cout<<"Enter Function:()..."<<endl;
	//�Ƚ���Ҫ������ϸ�������е����
	int intFlag = 0;
	int intPreviousFlag = 0;
	int intNextFlag = 0;
	
	if(iCurrentFlag!=0 && iVecTableBom[iCurrentFlag]->No == iVecTableBom[iCurrentFlag-1]->No )//��ǰһ�жԱ�
		intPreviousFlag = 1;

	if (iCurrentFlag!=iVecTableBom.size()-1 && iVecTableBom[iCurrentFlag]->No == iVecTableBom[iCurrentFlag+1]->No)//�ͺ�һ�жԱ�
		intNextFlag = 1;

	
	if (intPreviousFlag && intNextFlag)//ǰ����ͬ,�м����
		intFlag = 1;
	else if(!intPreviousFlag && intNextFlag)//��ǰһ����һ��������һ������ͷ���
		intFlag = 2;
	else if(intPreviousFlag && !intNextFlag)//�ͺ��治һ����ǰ��һ������β���
		intFlag = 3;


	return intFlag;
}

//������Ԥ������ȡ��
//���룺cmd-��ťָ�룬evt-�¼�ָ�룬data-����
//�����void
//���أ�void
void YFGeneratePartListCmd::ActionPreviewCancelFunc(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	//�ر�Ԥ������
	_PreviewDlg->SetVisibility(CATDlgHide);
	_pDlg->SetVisibility(CATDlgShow);
	SendNotification(GetFather(),_pCmdNoteCls);
	//_pCmdNoteCls->Release();
	//_pCmdNoteCls = NULL;
}
//������Ԥ������ȷ��
//���룺cmd-��ťָ�룬evt-�¼�ָ�룬data-����
//�����void
//���أ�void
void YFGeneratePartListCmd::ActionPreviewOkFunc(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	cout<<"Enter Function:ActionPreviewOk()..."<<endl;
	_pDlg->SetOKSensitivity(CATDlgEnable);
	_pDlg->SetCANCELSensitivity(CATDlgEnable);
	DeleteTabelBomFunc();
	
	vector<PartListInfo*> pTableBomList;//������������
	CATListValCATUnicodeString	listOfNOs;//��¼���
	CATListValCATUnicodeString	listOfYFPartNumber;//��¼�ӷ������
	CATListOfInt	ListOfFlag;//��¼��־λ


	//��ȡ������������Ϣ
	if (_vecPreviewBomList.size())
	{
		//��Ԥ����ʾ�д򹴵���Ϣ�����������
		for (int i = 0;i<_vecPreviewBomList.size();i++)
		{
			CATUnicodeString oString = NULL;
			_MultiListOfPreview->GetColumnItem(8,oString,i);
			if (oString == "��")//���ѡ���ˣ�������б�
				pTableBomList.push_back(_vecPreviewBomList[i]);
		}
		
		
		CATUnicodeString strTempNo = NULL;
		int intFlagNum = 0;
		//ȷ�����ɵ����
		for (int i = 0;i<pTableBomList.size();i++)
		{
			listOfNOs.Append(pTableBomList[i]->No);
			listOfYFPartNumber.Append(pTableBomList[i]->YFPartNumber);

			int intNoFlag = ContinuousSameNoOrNotFunc(i,pTableBomList);
			cout<<"int no flag "<<intNoFlag<<endl;
			
			CATIProduct* piProduct = NULL;
			for (map<CATIProduct*,CATUnicodeString>::iterator it = _mapProducts.begin();it!=_mapProducts.end();it++)
			{
				if (pTableBomList[i]->YFPartNumber == it->second)
				{
					piProduct = it->first;
					break;
				}
			}
			
			int intPartOrNotFlag = 0;
			if (piProduct) HavePartOrNotFunc(piProduct,intPartOrNotFlag);

			if (intNoFlag == 2)
			{
				intFlagNum++;

				if (intPartOrNotFlag) ListOfFlag.Append(intFlagNum*10+1);
				else ListOfFlag.Append(intFlagNum*10);
				
			}else if(intNoFlag == 1 || intNoFlag ==3){

				if (intPartOrNotFlag) ListOfFlag.Append(intFlagNum*10+1);
				else ListOfFlag.Append(intFlagNum*10);

			}else{//�Ƕ�����
				
				if (intPartOrNotFlag) ListOfFlag.Append(1);
				else ListOfFlag.Append(0);
			}

		}
	
	}


	//ceil ����ȡ��
	//��ȡ״̬
	int intPos = ((CATIProduct_var)_spSelProduct)->GetPartNumber().SearchSubString("_");
	CATUnicodeString strYFPartNumber = ((CATIProduct_var)_spSelProduct)->GetPartNumber().SubString(0,intPos);

	double dblTableNo = 0.;
	CATUnicodeString strTableNo = NULL;
	int intCheckFlag = 0;
	int intTempFlag = 1;//���
	int intStartIndex = 0;
	int intTempFlag_2 = 0;//�ж϶�����
	int intMembers = 1;
	for (int j =1 ;j<=listOfYFPartNumber.Size();j++)
	{
		if(listOfYFPartNumber[j] == strYFPartNumber) pTableBomList[j-1]->TableNo = NULL;//Ϊ��ѡ���ڵ�
		else{
			
			if( ListOfFlag[j]/10 == 0 && ListOfFlag[j]%10 == 1)//��Ϊ�������������part
			{
				dblTableNo = ceil(dblTableNo + 0.1);
				strTableNo.BuildFromNum((int)dblTableNo);
				pTableBomList[j-1]->TableNo = strTableNo;

			}else{//���������
				
				
				if ( ListOfFlag[j]/10 == intTempFlag && ListOfFlag[j]%10 == 1)//�����ƿ�ͷ,�ж϶����Ƹ������Լ����������������Part
				{
					intTempFlag_2 = 0;
					intStartIndex = j;//��¼�����������ͷ�±�
					intTempFlag++;
					for (int j_1 = j+1;j_1<=listOfYFPartNumber.Size();j_1++)
					{
						if ( ListOfFlag[intStartIndex]/10 == ListOfFlag[j_1]/10)
						{
							intMembers++;//��Ա����
							if (ListOfFlag[j_1]%10 == 1)
							{
								intTempFlag_2 = 1;
							}
						}
					}

					//if (ListOfFlag[intStartIndex]%10 == 1)//��Part
					//{
						if (intTempFlag_2 == 1)//�����������Part
						{
							dblTableNo = ceil(dblTableNo + 0.1) + 0.1;
							strTableNo.BuildFromNum(dblTableNo);
							pTableBomList[j-1]->TableNo = strTableNo;

						}else{//���������Part

							dblTableNo = ceil(dblTableNo + 0.1);
							strTableNo.BuildFromNum((int)dblTableNo);
							pTableBomList[j-1]->TableNo = strTableNo;

						}
					/*}*/
				}

				//if( j!=intStartIndex && ListOfFlag[j]/10 == ListOfFlag[intStartIndex]/10 && ListOfFlag[intStartIndex]%10 == 0) continue; //��ͷ�����Part


				if ( j!=intStartIndex && ListOfFlag[j]%10 == 1)
				{
					dblTableNo = dblTableNo + 0.1;
					strTableNo.BuildFromNum(dblTableNo);
					pTableBomList[j-1]->TableNo = strTableNo;
				}
	

			}
		}													//������					����part
		//cout<<listOfNOs[j]<<" = "<<listOfYFPartNumber[j]<<" = " << ListOfFlag[j]/10<<" = "<<ListOfFlag[j]%10<<endl;
		
	}//end for

	/*for (int i = 0;i<pTableBomList.size();i++)
	{
		cout<<pTableBomList[i]->TableNo<<" = "<<pTableBomList[i]->YFPartNumber<<endl;
	}*/

	
	//������ϸ��
	CATUnicodeString strFatherName(GetFather()->GetName().CastToCharPtr());
	if((strFatherName == ("YFGenerateExplosiveViewDlg")  ||  strFatherName == ("YFGenerateExplosiveViewCmd") ))
	{
		_pCmdNoteObjCls->_strTableNoList.clear();
		_pCmdNoteObjCls->_strPartNumberList.clear();
		if (pTableBomList.size())
		{

			if(pTableBomList.size()>=2)
			{
				_pCmdNoteObjCls->_strTopPartNumber = pTableBomList[0]->YFPartNumber;
			}
			for(int i = 0;i<pTableBomList.size();i++)
			{
				if (pTableBomList[i]->TableNo != "")
				{
					_pCmdNoteObjCls->_strTableNoList.push_back(pTableBomList[i]->TableNo);
					_pCmdNoteObjCls->_strPartNumberList.push_back(pTableBomList[i]->YFPartNumber);
				}
			}
		}
		else
		{
			CAAMessageBox("No data selected !","Notioce");
		}
		_PreviewDlg->SetVisibility(CATDlgHide);
		_pDlg->SetVisibility(CATDlgShow);
		SendNotification(GetFather(),_pCmdNoteCls);
		//_pCmdNoteCls->Release();
		//_pCmdNoteCls = NULL;
	}
	else
	{
		if (pTableBomList.size())
		{
			CreateTableFunc(pTableBomList);
		}
		else
		{
			CAAMessageBox("No data selected !","Notioce");
		}
		_PreviewDlg->SetVisibility(CATDlgHide);
		_pDlg->SetVisibility(CATDlgShow);
	}
}
//������Ԥ������ر�
//���룺cmd-��ťָ�룬evt-�¼�ָ�룬data-����
//�����void
//���أ�void
void YFGeneratePartListCmd::ActionPreviewCloseFunc(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	//�ر�Ԥ������
	_PreviewDlg->SetVisibility(CATDlgHide);
	_pDlg->SetVisibility(CATDlgShow);
	SendNotification(GetFather(),_pCmdNoteCls);
	//_pCmdNoteCls->Release();
	//_pCmdNoteCls = NULL;
}
//������˫��Ԥ����Ӧ
//���룺cmd-��ťָ�룬evt-�¼�ָ�룬data-����
//�����void
//���أ�void
void YFGeneratePartListCmd::ActionChangeYesOrNoFunc(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	int intIoTabRow = -1;
	_MultiListOfPreview->GetSelect(&intIoTabRow,1);
	CATUnicodeString oString = NULL;
	_MultiListOfPreview->GetColumnItem(8,oString,intIoTabRow);
	if(oString == NULL)
	{
		_MultiListOfPreview->SetColumnItem(8,"Y",intIoTabRow,CATDlgDataModify);
	}
	else if(oString.SearchSubString("Y")!=-1)
	{
		_MultiListOfPreview->SetColumnItem(8,NULL,intIoTabRow,CATDlgDataModify);
	}
}
//������������ϸ��
//���룺iVecTableBomList-�����ʾ����ϸ������
//�����void
//���أ�void
void YFGeneratePartListCmd::CreateTableFunc(vector<PartListInfo*> iVecTableBomList)
{
	//cout<<"Enter Function:()..."<<endl;
	HRESULT hr  = S_OK;
	CATBoolean rc = TRUE;
	/*CATUnicodeString strFontName = "SICH";
	CATBSTR bstrFontName;
	strFontName.ConvertToBSTR(&bstrFontName);*/
	//��õ�ǰ�ĵ�
	CATFrmEditor* pEditor=CATFrmEditor::GetCurrentEditor();
	CATDocument * pDoc = pEditor->GetDocument();
	CATIDrawing *piDrawing = NULL;
	CATIDftDrawing *piDftDrawing = NULL;
	CATIDftDocumentServices *piDftDocServices = NULL;
	if (SUCCEEDED(pDoc->QueryInterface(IID_CATIDftDocumentServices, (void **)&piDftDocServices)))
	{
		piDftDocServices->GetDrawing(IID_CATIDrawing, (void **)&piDrawing);
		piDftDocServices->GetDrawing(IID_CATIDftDrawing, (void **)&piDftDrawing);
		piDftDocServices->Release();
		piDftDocServices=NULL;

		if(piDrawing&&piDftDrawing)
		{
			CATISheet_var spCurSheet = piDrawing->GetCurrentSheet();//��ǰͼֽ
			CATIDftSheet* piDftCurrentSheet = NULL;
			hr = piDftDrawing->GetActiveSheet(&piDftCurrentSheet);
			boolean bRc = TRUE;
			hr = piDftCurrentSheet->IsDetail(&bRc);
			if (bRc) {CAAMessageBox("Error : Current Sheet Is Detail Sheet !","Notice");return;}

			CATIAlias_var spiAlias = spCurSheet;
			CATUnicodeString currentSheetName = spiAlias->GetAlias();
			CATLISTV(CATISpecObject_var) listOfFormerSheets = piDrawing->GetSheetList();
				
			CATIView_var spCurView = spCurSheet->GetMainView(); //��ǰ��ͼ
			//��ȡͼֽ��С
			double dblWidth,dblHeight;
			CATIDftSheetFormat *piDftSheetFormat=NULL;
			spCurSheet->QueryInterface(IID_CATIDftSheetFormat,(void**)&piDftSheetFormat);
			if(piDftSheetFormat==NULL) return;
			piDftSheetFormat->GetSheetSize(dblWidth,dblHeight);
			piDftSheetFormat->Release();
			piDftSheetFormat=NULL;
			double dblOx,dblOy;//���λ��
			double dblH;//�ɻ����ռ�߶�

			int intFlag=0;
			if (dblWidth==1189&&dblHeight==841)  //A0
			{
				dblOx=979;
				dblOy=83;
				dblH= dblHeight-16.0*2;
				intFlag=1;
			}else if (dblWidth==420&&dblHeight==297)//A3
			{
				dblOx=25.0;
				dblOy=287.;
				dblH= 257.;
				intFlag=2;
			}else
			{
				dblOx=0.0;
				dblOy=dblHeight;
				dblH = dblOy;
			}
			//�������
			CATIADrawingTable *piTable =NULL;
			CATIADrawingText* piText = NULL;
			CATIADrawingTextProperties* piTextProp = NULL;
			CATIDrwTextProperties_var spiDrwTestProp = NULL_var;
			int intTotalRow = iVecTableBomList.size();//����������
			//cout<<"�������� = "<<intTotalRow<<endl;
			if (intFlag == 1 || intFlag == 0) //A0��������
			{
				piTable = CreateDrawingTableFunc(spCurView,dblOx,dblOy,intTotalRow+1);

				//������
				CATIAlias_var spiAlias = piTable;
				CATUnicodeString tableName = "YFPartList";
				spiAlias->SetAlias(tableName);
				//�������
				for (int j_1=0;j_1<iVecTableBomList.size();j_1++)
				{
					//�����ֶ�
					piTable->SetCellString(j_1+2,1,CATUnicodeStringToCATBSTR(iVecTableBomList[j_1]->TableNo));
					piTable->SetCellAlignment(j_1+2,1,CatTableMiddleCenter);
					piTable->GetCellObject(j_1+2,1,piText);
					ChangeFontFunc(piText,iVecTableBomList[j_1]->TableNo,1);
					piText->get_TextProperties(piTextProp);
					spiDrwTestProp = piTextProp;
					spiDrwTestProp->SetCharacterSpacing(0.2);
					

					piTable->SetCellString(j_1+2,2,CATUnicodeStringToCATBSTR(iVecTableBomList[j_1] ->userDefineLevel));
					piTable->SetCellAlignment(j_1+2,2,CatTableMiddleCenter);
					piTable->GetCellObject(j_1+2,2,piText);
					ChangeFontFunc(piText,iVecTableBomList[j_1] ->Level,1);
					piText->get_TextProperties(piTextProp);
					spiDrwTestProp = piTextProp;
					spiDrwTestProp->SetCharacterSpacing(0.2);

					piTable->SetCellString(j_1+2,3,CATUnicodeStringToCATBSTR(iVecTableBomList[j_1]->YFPartNumber));
					piTable->SetCellAlignment(j_1+2,3,CatTableMiddleCenter);
					piTable->GetCellObject(j_1+2,3,piText);
					ChangeFontFunc(piText,iVecTableBomList[j_1]->YFPartNumber,1);
					//piText->SetFontName(0,100,bstrFontName);
					piText->get_TextProperties(piTextProp);
					spiDrwTestProp = piTextProp;
					spiDrwTestProp->SetCharacterSpacing(0.2);

					piTable->SetCellString(j_1+2,4,CATUnicodeStringToCATBSTR(iVecTableBomList[j_1] ->VersionNo));
					piTable->SetCellAlignment(j_1+2,4,CatTableMiddleCenter);
					piTable->GetCellObject(j_1+2,4,piText);
					ChangeFontFunc(piText,iVecTableBomList[j_1] ->VersionNo,1);
					//piText->SetFontName(0,100,bstrFontName);
					piText->get_TextProperties(piTextProp);
					spiDrwTestProp = piTextProp;
					spiDrwTestProp->SetCharacterSpacing(0.2);

					piTable->SetCellString(j_1+2,5,CATUnicodeStringToCATBSTR(iVecTableBomList[j_1] ->PartName));
					piTable->SetCellAlignment(j_1+2,5,CatTableMiddleCenter);
					piTable->GetCellObject(j_1+2,5,piText);
					ChangeFontFunc(piText,iVecTableBomList[j_1] ->PartName,1);
					//piText->SetFontName(0,100,bstrFontName);
					piText->get_TextProperties(piTextProp);
					spiDrwTestProp = piTextProp;
					spiDrwTestProp->SetCharacterSpacing(0.2);

					piTable->SetCellString(j_1+2,6,CATUnicodeStringToCATBSTR(iVecTableBomList[j_1] ->Quantity));
					piTable->SetCellAlignment(j_1+2,6,CatTableMiddleCenter);
					piTable->GetCellObject(j_1+2,6,piText);
					ChangeFontFunc(piText,iVecTableBomList[j_1] ->Quantity,1);
					//piText->SetFontName(0,100,bstrFontName);
					piText->get_TextProperties(piTextProp);
					spiDrwTestProp = piTextProp;
					spiDrwTestProp->SetCharacterSpacing(0.2);

					piTable->SetCellString(j_1+2,7,CATUnicodeStringToCATBSTR(iVecTableBomList[j_1] ->Material));
					piTable->SetCellAlignment(j_1+2,7,CatTableMiddleCenter);
					piTable->GetCellObject(j_1+2,7,piText);
					ChangeFontFunc(piText,iVecTableBomList[j_1] ->Material,1);
					//piText->SetFontName(0,100,bstrFontName);
					piText->get_TextProperties(piTextProp);
					spiDrwTestProp = piTextProp;
					spiDrwTestProp->SetCharacterSpacing(0.2);

					piTable->SetCellString(j_1+2,8,CATUnicodeStringToCATBSTR(iVecTableBomList[j_1] ->Notes));
					piTable->SetCellAlignment(j_1+2,8,CatTableMiddleCenter);
					piTable->GetCellObject(j_1+2,8,piText);
					ChangeFontFunc(piText,iVecTableBomList[j_1] ->Notes,1);
					//piText->SetFontName(0,100,bstrFontName);
					piText->get_TextProperties(piTextProp);
					spiDrwTestProp = piTextProp;
					spiDrwTestProp->SetCharacterSpacing(0.2);
				}

				piTable->InvertMode(CatInvertRow);
				piTable->put_AnchorPoint(CatTableBottomLeft);

				CATISpecObject_var spiTableObj = (CATISpecObject_var)piTable;
				_listOfObjNeedToDeleteLst.Append(spiTableObj);
				
			}else{//A3

				piTable = CreateDrawingTableFunc(spCurView,dblOx,dblOy,1);

				//�����б�
				CATISpecObject_var spiTableObj = (CATISpecObject_var)piTable;
				_listOfObjNeedToDeleteLst.Append(spiTableObj);

				int intNumFlag = 0;
				int intRowNum = 2;
				float minX = 0.;//�����ά����СX����
				float maxX = 0.;//�����ά�����X����
				float minY = 100.;//�����ά����СY����
				float maxY = 0.;//�����ά�����Y����
				while(1)
				{
					
					if (intNumFlag > iVecTableBomList.size()-1) break;
				
					piTable->AddRow(0);
				
					if (minY - 30. < 9.)
					{
						/*cout<<"��ʼ��ҳ"<<endl;
						cout<<"�Ƴ� = "<<intRowNum<<endl;*/
						piTable->RemoveRow(intRowNum);
						
						CATISheet_var spiNewSheet = CopySheetFunc(spCurSheet,piDrawing);
						
						if (!!spiNewSheet)
						{

							CATIView_var spiNewMainView = spiNewSheet->GetMainView();
							rc = DeleteTablesInViewFunc(spiNewMainView);
							if (rc == FALSE)
							{
								_strErrorTime = GetTimeFunc();
								ofstream errorFile(_strErrorPath.ConvertToChar(),ios::app);
								errorFile<<_strErrorTime<<":DeleteTablesInViewFunc error!\n";
								errorFile.close();
								return ;
							}
							intRowNum = 2;
						
							piTable = CreateDrawingTableFunc(spiNewMainView,dblOx,dblOy,1);
							//�����б�
							spiTableObj = (CATISpecObject_var)piTable;
							_listOfObjNeedToDeleteLst.Append(spiTableObj);

							piTable->AddRow(0);

						}else{

							_strErrorTime = GetTimeFunc();
							ofstream errorFile(_strErrorPath.ConvertToChar(),ios::app);
							errorFile<<_strErrorTime<<":Create New Sheet Fail !\n";
							errorFile.close();
							return;
	
						}
					}

					//cout<<"��ʼд��� = "<<intNumFlag+1<<"�����ݣ��ڵ� "<<intRowNum<<" ��"<<endl;
					//������
					CATIAlias_var spiAlias = piTable;
					CATUnicodeString tableName = "YFPartList";
					spiAlias->SetAlias(tableName);

					//�����ֶ�
					piTable->SetCellString(intRowNum,1,CATUnicodeStringToCATBSTR(iVecTableBomList[intNumFlag]->TableNo));
					piTable->SetCellAlignment(intRowNum,1,CatTableMiddleCenter);
					piTable->GetCellObject(intRowNum,1,piText);
					ChangeFontFunc(piText,iVecTableBomList[intNumFlag]->TableNo,1);
					//piText->SetFontName(0,100,bstrFontName);
					piText->get_TextProperties(piTextProp);
					spiDrwTestProp = piTextProp;
					spiDrwTestProp->SetCharacterSpacing(0.2);

					piTable->SetCellString(intRowNum,2,CATUnicodeStringToCATBSTR(iVecTableBomList[intNumFlag] ->userDefineLevel));
					piTable->SetCellAlignment(intRowNum,2,CatTableMiddleCenter);
					piTable->GetCellObject(intRowNum,2,piText);
					ChangeFontFunc(piText,iVecTableBomList[intNumFlag] ->Level,1);
					//piText->SetFontName(0,100,bstrFontName);
					piText->get_TextProperties(piTextProp);
					spiDrwTestProp = piTextProp;
					spiDrwTestProp->SetCharacterSpacing(0.2);

					piTable->SetCellString(intRowNum,3,CATUnicodeStringToCATBSTR(iVecTableBomList[intNumFlag]->YFPartNumber));
					piTable->SetCellAlignment(intRowNum,3,CatTableMiddleCenter);
					piTable->GetCellObject(intRowNum,3,piText);
					ChangeFontFunc(piText,iVecTableBomList[intNumFlag]->YFPartNumber,1);
					//piText->SetFontName(0,100,bstrFontName);
					piText->get_TextProperties(piTextProp);
					spiDrwTestProp = piTextProp;
					spiDrwTestProp->SetCharacterSpacing(0.2);

					piTable->SetCellString(intRowNum,4,CATUnicodeStringToCATBSTR(iVecTableBomList[intNumFlag] ->VersionNo));
					piTable->SetCellAlignment(intRowNum,4,CatTableMiddleCenter);
					piTable->GetCellObject(intRowNum,4,piText);
					ChangeFontFunc(piText,iVecTableBomList[intNumFlag] ->VersionNo,1);
					//piText->SetFontName(0,100,bstrFontName);
					piText->get_TextProperties(piTextProp);
					spiDrwTestProp = piTextProp;
					spiDrwTestProp->SetCharacterSpacing(0.2);

					piTable->SetCellString(intRowNum,5,CATUnicodeStringToCATBSTR(iVecTableBomList[intNumFlag] ->PartName));
					piTable->SetCellAlignment(intRowNum,5,CatTableMiddleCenter);
					piTable->GetCellObject(intRowNum,5,piText);
					ChangeFontFunc(piText,iVecTableBomList[intNumFlag] ->PartName,1);
					//piText->SetFontName(0,100,bstrFontName);
					piText->get_TextProperties(piTextProp);
					spiDrwTestProp = piTextProp;
					spiDrwTestProp->SetCharacterSpacing(0.2);
					//cout<<"�ֶ� = "<<iVecTableBomList[intNumFlag]->PartName<<endl;

					piTable->SetCellString(intRowNum,6,CATUnicodeStringToCATBSTR(iVecTableBomList[intNumFlag] ->Quantity));
					piTable->SetCellAlignment(intRowNum,6,CatTableMiddleCenter);
					piTable->GetCellObject(intRowNum,6,piText);
					ChangeFontFunc(piText,iVecTableBomList[intNumFlag] ->Quantity,1);
					//piText->SetFontName(0,100,bstrFontName);
					piText->get_TextProperties(piTextProp);
					spiDrwTestProp = piTextProp;
					spiDrwTestProp->SetCharacterSpacing(0.2);

					piTable->SetCellString(intRowNum,7,CATUnicodeStringToCATBSTR(iVecTableBomList[intNumFlag] ->Material));
					piTable->SetCellAlignment(intRowNum,7,CatTableMiddleCenter);
					piTable->GetCellObject(intRowNum,7,piText);
					ChangeFontFunc(piText,iVecTableBomList[intNumFlag] ->Material,1);
					//piText->SetFontName(0,100,bstrFontName);
					piText->get_TextProperties(piTextProp);
					spiDrwTestProp = piTextProp;
					spiDrwTestProp->SetCharacterSpacing(0.2);

					piTable->SetCellString(intRowNum,8,CATUnicodeStringToCATBSTR(iVecTableBomList[intNumFlag] ->Notes));
					piTable->SetCellAlignment(intRowNum,8,CatTableMiddleCenter);
					piTable->GetCellObject(intRowNum,8,piText);
					ChangeFontFunc(piText,iVecTableBomList[intNumFlag] ->Notes,1);
					//piText->SetFontName(0,100,bstrFontName);
					piText->get_TextProperties(piTextProp);
					spiDrwTestProp = piTextProp;
					spiDrwTestProp->SetCharacterSpacing(0.2);

					CATI2DGeoVisu* pi2DGeoVisu = NULL;
					if (SUCCEEDED(piTable->QueryInterface(IID_CATI2DGeoVisu,(void**)&pi2DGeoVisu)))//��ȡ�����ά���ӻ�����Ľӿ�ָ��
					{
						CATRep* pRep = pi2DGeoVisu->GiveRep();//��ȡͼ�α�ʾ��ָ��
						if (pRep)
						{
							CAT2DRep* p2DRep = (CAT2DRep*)pRep;//����ת��
							if (p2DRep)
							{
								CAT2DBoundingBox boundingBox = p2DRep->GetBoundingElement();//��ȡ��ά�еĶ�ά��ʾ��Ϣ

								boundingBox.GetParameter(&minX,&maxX,&minY,&maxY);//��ȡ��ά�б߽�����
							
								/*cout<<"minX = "<<minX<<",maxX = "<<maxX<<endl;
								cout<<"minY = "<<minY<<",maxY = "<<maxY<<endl;*/
								
							}
						}
						pi2DGeoVisu->Release();pi2DGeoVisu=NULL;
					}

					intRowNum++;
					intNumFlag++;

					//cout<<"д�����"<<endl;
				}

				//cout<<"break while"<<endl;
				//ͼֽ����
				CATLISTV(CATISpecObject_var) listOfSortSheets;
				CATLISTV(CATISpecObject_var) listOfSheets = piDrawing->GetSheetList();
				CATIAlias_var spiTestAlias = NULL_var;
				if (listOfSheets.Size()&&listOfFormerSheets.Size())
				{
					for (int i_sheet = 1;i_sheet<=listOfFormerSheets.Size();i_sheet++)
					{	
						spiTestAlias = listOfFormerSheets[i_sheet];
						//cout<<"���������� = "<<spiTestAlias->GetAlias()<<endl;
						listOfSortSheets.Append(listOfFormerSheets[i_sheet]);

						CATISheet_var spiSheet = listOfFormerSheets[i_sheet];
						if (spCurSheet == spiSheet)
						{
							for (int j_sheet = listOfFormerSheets.Size()+1;j_sheet<=listOfSheets.Size();j_sheet++)
							{
								spiTestAlias = listOfSheets[j_sheet];
								//cout<<"������¼ӵ����� = "<<spiTestAlias->GetAlias()<<endl;
								listOfSortSheets.Append(listOfSheets[j_sheet]);
							}
						}	
					}
				}

				if (FAILED(piDftDrawing->ValidateSheetOrder(listOfSortSheets)))
				{
					_strErrorTime = GetTimeFunc();
					ofstream errorFile(_strErrorPath.ConvertToChar(),ios::app);
					errorFile<<_strErrorTime<<":ValidateSheetOrder����ʧ��!\n";
					errorFile.close(); 
				}

				if (FAILED(piDftDrawing->ReorderSheets(listOfSortSheets)))
				{
					_strErrorTime = GetTimeFunc();
					ofstream errorFile(_strErrorPath.ConvertToChar(),ios::app);
					errorFile<<_strErrorTime<<"::ReorderSheets����ʧ��!\n";
					errorFile.close(); 
				}

			
			}//end else

			
			
			piDftDrawing->Release();piDftDrawing =NULL;
			piDrawing->Release();piDrawing = NULL;
			piDftCurrentSheet->Release();piDftCurrentSheet=NULL;
			
		}
	}


}
//������������ͷ
//���룺ispiCurView-��ǰ������ͼ,ox-��λX�㣬oy-��λY�㣬row-����
//�����void
//���أ�CATIADrawingTable - ��ϸ��ָ��
CATIADrawingTable* YFGeneratePartListCmd::CreateDrawingTableFunc(CATIView_var ispiCurView,double ox,double oy,int row)
{
	CATIADrawingTables* pTables = NULL;
	CATIADrawingTable  *piTable = NULL;
	CATIADrawingText* piText = NULL;
	CATIADrawingTextProperties* piTextProp = NULL;
	if (SUCCEEDED(ispiCurView->QueryInterface(IID_CATIADrawingTables,(void**)&pTables))&&pTables)
	{
		pTables->Add(ox,oy,row,8,9.88,8,piTable); //x/y/�С��С��иߣ��п�
		if (piTable!=NULL)
		{
			//cout<<"��ͷ�����ɹ�!"<<endl;
			CATUnicodeString arryTableNames[8]={"���\nNO","����\nLEVEL","�����\nPART NO","�汾\nREV","�������\nPART NAME","����\nQUANTITY","����\nMATERIAL","��ע\nNOTES"};
			piTable->SetRowSize(1,10);
			//�п�
			double arryColWidth[8]={11,14.0,25.0,9.0,70.0,21.0,27.0,18.0};
			for(int j =0;j<8;j++)
			{
				CATUnicodeString strText = NULL;
				piTable->SetColumnSize(j+1,arryColWidth[j]);
				piTable->SetCellString(1,j+1,_bstr_t(arryTableNames[j].ConvertToChar()));//���������ֶ�
				piTable->SetCellAlignment(1,j+1,CatTableMiddleCenter);//����
				piTable->GetCellObject(1,j+1,piText);
				
				strText.BuildFromBSTR(_bstr_t(arryTableNames[j].ConvertToChar()));
				ChangeFontFunc(piText,strText,1);
				piText->get_TextProperties(piTextProp);
				CATIDrwTextProperties_var spiDrwTestProp = piTextProp;
				spiDrwTestProp->SetCharacterSpacing(0.2);
			}

		}
	}
	return piTable;
}
//������charתwchar
//���룺cchar-const char* ���ַ���
//�����void
//���أ�wchar_t* - wchar_t* ���ַ���
wchar_t* YFGeneratePartListCmd::char2wcharFunc(const char* cchar) 
{     
	wchar_t *m_wchar;    
	int len = MultiByteToWideChar( CP_ACP ,0,cchar ,strlen( cchar), NULL,0);     
	m_wchar= new wchar_t[len+1];     
	MultiByteToWideChar( CP_ACP ,0,cchar,strlen( cchar),m_wchar,len);     
	m_wchar[len]= '\0' ;    
	return m_wchar; 
} 
//������ת��
//���룺str-CATUnicodeString ���ַ���
//�����void
//���أ�CATBSTR - CATBSTR ���ַ���
CATBSTR YFGeneratePartListCmd::CATUnicodeStringToCATBSTRFunc(CATUnicodeString str)
{
	CATBSTR pBSTR=NULL;
	str.CATUnicodeString::ConvertToBSTR(&pBSTR); 
	return pBSTR;
}
//��������ʼ������
//���룺void
//�����void
//���أ�void
void YFGeneratePartListCmd::InitDataFunc()
{
	//��ȡ�����б� 
	_pLayout=CATFrmLayout::GetCurrentLayout();
	CATLISTP(CATFrmWindow) listOfWindow=_pLayout->GetWindowList() ;
	int intProFlag = 0,intDraFlag = 0;
	if (listOfWindow.Size()!=0)
	{
		for (int i =1;i<=listOfWindow.Size();i++)
		{
			CATUnicodeString oType =GetDocumentTypeFunc(listOfWindow[i]);
			if(oType == "CATProduct")
			{
				CATUnicodeString pWindName = listOfWindow[i]->GetBaseName();
				if(pWindName.SearchSubString(".CATProduct")!=-1) 
					_ComboSelectAssembly->SetLine(pWindName);
				
				intProFlag = 1;
			}
			if (oType == "CATDrawing") intDraFlag = 1;	
		}
		//�ж�
		if (intProFlag == 0)
		{
			CAAMessageBox("Please Open A CATProduct File��","Notice");
			RequestDelayedDestruction();//��ֹ�������
			return ;
		}else if(intDraFlag == 0){
			CAAMessageBox("Please Open A 2D Drawing  Relating To Part or Product!","Notice");
			RequestDelayedDestruction();//��ֹ�������
			return ;
		}

	}else{
		CAAMessageBox("Please Open A CATProduct File And A 2D Drawing !","Notice");
		RequestDelayedDestruction();//��ֹ�������
		return ;
	}

	//��ȡ��ǰ����
	_pCurrentWindow = _pLayout->GetCurrentWindow();
	CATUnicodeString oCurType = GetDocumentTypeFunc(_pCurrentWindow);
	if(oCurType != "CATDrawing")
	{
		CAAMessageBox("Please switch to the Drawing module operation !","Notice");
		RequestDelayedDestruction();//��ֹ�������
		return ;
	}

	//_pDlg ->SetVisibility(CATDlgShow);
	return ;
}
//��������ȡ��������
//���룺ipWind - ��ǰ����
//�����void
//���أ�CATUnicodeString - ��������
CATUnicodeString YFGeneratePartListCmd::GetDocumentTypeFunc( CATFrmWindow * ipWind )
{
	//cout<<"Enter Function: GetDocumentType()..."<<endl;
	CATUnicodeString oType = NULL;
	if (ipWind!=NULL)
	{
		CATDocument * pDoc =NULL;
		CATFrmEditor * pEditor= ipWind->GetEditor();
		if (pEditor!=NULL)
		{
			pDoc=pEditor->GetDocument();
			CATIDocId* oDocId=NULL;
			pDoc->GetDocId(&oDocId);
			oDocId->GetType(oType); 
			return oType;
		}
		pEditor =NULL;
		pDoc =NULL;

	}
	return NULL;
}


//�������������
//���룺ipiADrawingText - ��������ָ��,iStrText-�ı�����,iStartPos - ��ʼλ��
//�����void
//���أ�void
void YFGeneratePartListCmd::ChangeFontFunc(CATIADrawingText* ipiADrawingText,CATUnicodeString iStrText,int iStartPos)
{
	//�ж���Ӣ��
	
	string str = UnicodeToANSIFunc(iStrText);
	if(str[0]<255 && str[0]>0)//�����ASCII�ַ���ΧΪ0-255,����,����һ���ֽ�,Ӣ������
	{
		//cout<<str.substr(0,1)<<" Ӣ�� =  "<<iStrText.SearchSubString(str.substr(0,1).c_str())<<"λ�� = "<<iStartPos<<endl;
		CATUnicodeString strFontName = "SSS1";
		CATBSTR bstrFontName;
		strFontName.ConvertToBSTR(&bstrFontName);
		ipiADrawingText->SetFontSize(iStartPos,1,2.5);
		ipiADrawingText->SetFontName(iStartPos,1,bstrFontName);
		iStrText.Remove(iStrText.SearchSubString(str.substr(0,1).c_str()));
		if (iStrText!=NULL) ChangeFontFunc(ipiADrawingText,iStrText,iStartPos+1);
	}
	else//<0,>255���Ǻ���,���������ֽ�,����
	{	
		//cout<<str.substr(0,2)<<" ���� =  "<<iStrText.SearchSubString(str.substr(0,2).c_str())<<"λ�� = "<<iStartPos<<endl;
		CATUnicodeString strFontName = "SICH";
		CATBSTR bstrFontName;
		strFontName.ConvertToBSTR(&bstrFontName);
		ipiADrawingText->SetFontSize(iStartPos,1,3.5);
		ipiADrawingText->SetFontName(iStartPos,1,bstrFontName);
		iStrText.Remove(iStrText.SearchSubString(str.substr(0,2).c_str()));
		if (iStrText!=NULL) ChangeFontFunc(ipiADrawingText,iStrText,iStartPos+1);
	}
}
//������ɾ����ϸ��
//���룺void
//�����void
//���أ�void
void YFGeneratePartListCmd::DeleteTabelBomFunc()
{
	if (_listOfObjNeedToDeleteLst.Size())
	{
		for (int i=1;i<=_listOfObjNeedToDeleteLst.Size();i++)
		{
			CATIModelEvents_var IME(_listOfObjNeedToDeleteLst[i]);
			if(NULL_var != IME) {
				CATDelete info(_listOfObjNeedToDeleteLst[i]->GetImpl());
				IME->Dispatch(info);
			}
			CATISpecObject_var ispFather = _listOfObjNeedToDeleteLst[i]->GetFather();
			if (NULL_var != ispFather) {
				ispFather->Remove(_listOfObjNeedToDeleteLst[i]);
			}
			else {
				LifeCycleObject_var LCO = _listOfObjNeedToDeleteLst[i];
				LCO -> remove();
			} 
		}
		_listOfObjNeedToDeleteLst.RemoveAll();
	}
	return ;
}

//��������ʾ��Ϣ���ȷ����������
//���룺cmd-��ťָ�룬evt-�¼�ָ�룬data-����
//�����void
//���أ�void
void YFGeneratePartListCmd::ContinueToGengerateFunc(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	//cout<<"Enter Function ;ContinueToGengerate()..."<<endl;
	int intRow=0;
	for(vector<PartListInfo*>::iterator it  = _vecPreviewBomList.begin();it!=_vecPreviewBomList.end();it++)
	{
		_MultiListOfPreview->SetColumnItem(1,(*it)->userDefineLevel,intRow,CATDlgDataModify);
		_MultiListOfPreview->SetColumnItem(2,(*it)->YFPartNumber,intRow,CATDlgDataModify);
		_MultiListOfPreview->SetColumnItem(3,(*it)->VersionNo,intRow,CATDlgDataModify);
		_MultiListOfPreview->SetColumnItem(4,(*it)->PartName,intRow,CATDlgDataModify);
		_MultiListOfPreview->SetColumnItem(5,(*it)->Quantity,intRow,CATDlgDataModify);
		_MultiListOfPreview->SetColumnItem(6,(*it)->Material,intRow,CATDlgDataModify);
		_MultiListOfPreview->SetColumnItem(7,(*it)->Notes,intRow,CATDlgDataModify);
		_MultiListOfPreview->SetColumnItem(8,"��",intRow,CATDlgDataModify);
		intRow++;
	}

	_PreviewDlg->SetVisibility(CATDlgShow);
	_pDlg->SetVisibility(CATDlgHide);
}
//��������ʾ��Ϣ���ȡ��
//���룺cmd-��ťָ�룬evt-�¼�ָ�룬data-����
//�����void
//���أ�void
void YFGeneratePartListCmd::ActionDlgCancelFunc(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	//cout<<"ActionDlgClose"<<endl;
	((CATDlgNotify*)data)->SetVisibility(CATDlgHide);
}


//����������ͼֽ
//���룺ispiSourceSheet - Ҫ������sheet,ispiTargetDrawing - ������Ŀ�ĵ�
//�����void
//���أ�CATISheet_var - ���ؽ������
CATISheet_var YFGeneratePartListCmd::CopySheetFunc(CATISheet_var ispiSourceSheet,CATIDrawing_var ispiTargetDrawing)
{
	
	if (!ispiSourceSheet || !ispiTargetDrawing)
	{
		_strErrorTime = GetTimeFunc();
		ofstream errorFile(_strErrorPath.ConvertToChar(),ios::app);
		errorFile<<_strErrorTime<<":����ͼֽ��������!\n";
		errorFile.close(); 
		return NULL_var;
	}

	//��ȡ :spiTargetCutAndPast
	CATISpecObject_var spiSpecOnTargetDrawing = ispiTargetDrawing;
	if (!spiSpecOnTargetDrawing)
	{
		_strErrorTime = GetTimeFunc();
		ofstream errorFile(_strErrorPath.ConvertToChar(),ios::app);
		errorFile<<_strErrorTime<<":QI error : spiSpecOnTargetDrawing!\n";
		errorFile.close();
		return NULL_var;
	}

	CATIContainer_var spiTargetCont = spiSpecOnTargetDrawing->GetFeatContainer();
	if (!spiTargetCont)
	{
		_strErrorTime = GetTimeFunc();
		ofstream errorFile(_strErrorPath.ConvertToChar(),ios::app);
		errorFile<<_strErrorTime<<":QI error : spiTargetCont!\n";
		errorFile.close();
		return NULL_var;
	}

	CATICutAndPastable_var spiTargetCutAndPast = spiTargetCont;
	if (!spiTargetCutAndPast)
	{
		_strErrorTime = GetTimeFunc();
		ofstream errorFile(_strErrorPath.ConvertToChar(),ios::app);
		errorFile<<_strErrorTime<<":QI error : spiTargetCutAndPast!\n";
		errorFile.close();
		return NULL_var;
	}

	//��ȡ :spiSourceCutAndPast
	CATISpecObject_var spiSpecOnSourceSheet = ispiSourceSheet;
	if (!spiSpecOnSourceSheet)
	{
		_strErrorTime = GetTimeFunc();
		ofstream errorFile(_strErrorPath.ConvertToChar(),ios::app);
		errorFile<<_strErrorTime<<":QI error : spiSpecOnSourceSheet!\n";
		errorFile.close();
		return NULL_var;
	}

	CATIContainer_var spiSourceCont = spiSpecOnSourceSheet->GetFeatContainer();
	if (!spiSourceCont)
	{
		_strErrorTime = GetTimeFunc();
		ofstream errorFile(_strErrorPath.ConvertToChar(),ios::app);
		errorFile<<_strErrorTime<<":QI error : spiSourceCont!\n";
		errorFile.close();
		return NULL_var;
	}

	CATICutAndPastable_var spiSourceCutAndPast = spiSourceCont;
	if (!spiSourceCutAndPast)
	{
		_strErrorTime = GetTimeFunc();
		ofstream errorFile(_strErrorPath.ConvertToChar(),ios::app);
		errorFile<<_strErrorTime<<":QI error : spiSourceCutAndPast!\n";
		errorFile.close();
		return NULL_var;
	}

	//����
	IdFormat iIdFmy = "CATDrwCont";
	const CATFormat* pFmt = CATFormat::GetRegisteredFormat(iIdFmy);

	ListOfVarBaseUnknown listFromCopy;
	listFromCopy.Append((CATBaseUnknown *)spiSpecOnSourceSheet);

	ListOfVarBaseUnknown lisTarget;
	lisTarget.Append(spiSpecOnTargetDrawing);

	ListOfVarBaseUnknown listPastedObjects = spiTargetCutAndPast -> Paste (listFromCopy,&lisTarget,pFmt);

	//��ȡ���
	CATISheet_var spiResultSheet = NULL_var;
	CATBaseUnknown *pBaseUnknown=NULL;
	CATPathElement *pPathOfResultElement=NULL;
	if( listPastedObjects.Size() > 0 ) 
	{
		pBaseUnknown = listPastedObjects[1];
		pPathOfResultElement = (CATPathElement *)pBaseUnknown;
		if( !!pPathOfResultElement ) 
		{
			spiResultSheet = (CATISpecObject_var)pPathOfResultElement->FindElement(IID_CATISpecObject);
		}
	}

	return spiResultSheet;
}
//������ɾ��ͼֽ�б��
//���룺ispiDftView - ��ǰ��ͼ
//�����void
//���أ�CATBoolean - true of false
CATBoolean YFGeneratePartListCmd::DeleteTablesInViewFunc(CATIView_var ispiDftView)
{
	HRESULT hr = S_OK;
	if (!ispiDftView)
	{
		_strErrorTime = GetTimeFunc();
		ofstream errorFile(_strErrorPath.ConvertToChar(),ios::app);
		errorFile<<_strErrorTime<<":DeleteTablesInViewFunc ������������!\n";
		errorFile.close();
		return FALSE;
	}

	CATIADrawingView_var spiADrawingView = ispiDftView;
	if (!spiADrawingView)
	{
		_strErrorTime = GetTimeFunc();
		ofstream errorFile(_strErrorPath.ConvertToChar(),ios::app);
		errorFile<<_strErrorTime<<":DeleteTablesInViewFunc QI error!\n";
		errorFile.close();
		return FALSE;
	}

	CATIADrawingTables* piADrawingTables = NULL;
	hr = spiADrawingView->get_Tables(piADrawingTables);
	if (FAILED(hr) || !piADrawingTables)
	{
		_strErrorTime = GetTimeFunc();
		ofstream errorFile(_strErrorPath.ConvertToChar(),ios::app);
		errorFile<<_strErrorTime<<":DeleteTablesInViewFunc get_Tables error!\n";
		errorFile.close();
		return FALSE;
	}

	//��ȡ����Ŀ
	CATLONG itableCount;
	piADrawingTables->get_Count(itableCount);

	for (CATLONG i = 1;i<=itableCount;i++)
		piADrawingTables->Remove(i);

	piADrawingTables->Release();piADrawingTables = NULL;

	return TRUE;

}
//�ַ�ת��
char* YFGeneratePartListCmd::UnicodeToANSIFunc(CATUnicodeString iStrText)
{
	int textlen = WideCharToMultiByte( CP_ACP, 0, iStrText, -1, NULL, 0, NULL, NULL );
	char* result =(char *)malloc((textlen+1)*sizeof(char));
	memset( result, 0, sizeof(char) * ( textlen + 1 ) );
	WideCharToMultiByte( CP_ACP, 0, iStrText, -1, result, textlen, NULL, NULL );

	return result;
}


void * YFGeneratePartListCmd::SendCommandSpecificObject(const char * ExpectedObject,CATNotification* ReceivedNotification)
{
	if ( _pCmdNoteObjCls->IsAKindOf(ExpectedObject) && (ReceivedNotification == _pCmdNoteCls) )
	{
		return ((void *) _pCmdNoteObjCls);
	}
	else
	{
		return (NULL);
	}
}