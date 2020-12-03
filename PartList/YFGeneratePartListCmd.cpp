#include "YFGeneratePartListCmd.h"




CATCreateClass( YFGeneratePartListCmd);

YFGeneratePartListCmd::YFGeneratePartListCmd() :
CATStateCommand ("YFGeneratePartListCmd", CATDlgEngOneShot, CATCommandModeExclusive) 
{
	//about license
	//创建进程 - 初始化服务器
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
	//创建进程 - 验证服务器
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

	//记录信息
	//功能
	_strUserInfo = "YFPartList";

	//本机名称
		//初始化:如果不初始化，以下代码将无法执行
	WSAData data;
	if(WSAStartup(MAKEWORD(1,1),&data)!=0)
	{
		_strErrorTime = GetTimeFunc();
		cout<<_strErrorTime<<":初始化错误,无法获取主机信息..."<<endl;
	}
	
	char host[255];
		//获取主机名:也可以使用GetComputerName()这个函数
	if(gethostname(host,sizeof(host))==SOCKET_ERROR)
	{
		_strErrorTime = GetTimeFunc();
		cout<<_strErrorTime<<":无法获取主机名..."<<endl;
	}

	CATUnicodeString strPcName = host;
	_strUserInfo.Append("，");
	_strUserInfo.Append(strPcName);
	
	//开始时间
		//时间一
	CATUnicodeString strStartTime = GetTimeFunc();
	_strUserInfo.Append("，");
	_strUserInfo.Append(strStartTime);
	_strUserInfo.Append("，");
		//时间二(便于计算程序运行时间)
	CATTime currentTime = CATTime::GetCurrentLocalTime();
	_intStartHour = currentTime.GetHour();
	_intStartMinute = currentTime.GetMinute();
	_intStartSecond = currentTime.GetSecond();

	//获取程序变量
	char* docPath = "KBETracePath";															//保存模版的环境变量名
	char* docPathValue = NULL;																//保存莫班的环境变量对应的路
	CATLibStatus envState = CATGetEnvValue(docPath,&docPathValue);							//获得保存模版的环境变量的值
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

	//结束时间
	CATTime currentEndTime = CATTime::GetCurrentLocalTime();
	int intEndHour = currentEndTime.GetHour();
	int intEndMinute = currentEndTime.GetMinute();
	int intEndSecond = currentEndTime.GetSecond();
	_strUserInfo.Append("耗时：");
	if (intEndHour - _intStartHour)
	{
		CATUnicodeString strHour = NULL;
		strHour.BuildFromNum(intEndHour - _intStartHour);
		_strUserInfo.Append(strHour);
		_strUserInfo.Append("时");
	}

	if (intEndMinute - _intStartMinute)
	{
		CATUnicodeString strMin = NULL;
		strMin.BuildFromNum(intEndMinute - _intStartMinute);
		_strUserInfo.Append(strMin);
		_strUserInfo.Append("分");
	}

	if (intEndSecond - _intStartSecond)
	{
		CATUnicodeString strSec = NULL;
		strSec.BuildFromNum(intEndSecond - _intStartSecond);
		_strUserInfo.Append(strSec);
		_strUserInfo.Append("秒");
	}


	ofstream file(_strUserInfoDirection.ConvertToChar(),ios::app);
	file<<_strUserInfo<<"\n";
	file.close(); //使用完毕之后需要关闭
	
}
//描述：程序入口函数
//输入：void
//输出：void
//返回：void
void YFGeneratePartListCmd::BuildGraph()
{
	/*cout<<"开始"<<endl;
	cout<<_strUserInfoDirection<<endl;
	cout<<_strErrorPath<<endl;*/
	/*_strErrorTime = GetTimeFunc();
	ofstream errorFile(_strErrorPath.ConvertToChar(),ios::app);
	errorFile<<_strErrorTime<<_strErrorPath<<_strUserInfoDirection;
	errorFile.close(); */
	//软件窗口建立
	//----------------------------------
	_pDlg = new YFGeneratePartListDlg();
	_pDlg -> SetFather(this);
	_pDlg -> Build();
	_pDlg->SetOKSensitivity(CATDlgDisable);
	_pDlg->SetCANCELSensitivity(CATDlgDisable);

	_PreviewDlg = new YFPreviewPanelDlg;
	_PreviewDlg -> SetFather(_pDlg);
	_PreviewDlg->Build();

	
	//界面初始值设定
	//----------------------------------
	_BTSelectEBOM = _pDlg ->ReturnBTSelectEBOM();
	_EditorSelectEBOM = _pDlg ->ReturnEditorSelectEBOM();
	_ComboSelectAssembly = _pDlg ->ReturnComboSelectAssembly();
	_SelectorListSelectSUProduct = _pDlg ->ReturnSelectorListSelectSUProduct();
	_EditorSULevel = _pDlg ->ReturnEditorSULevel();
	_EditorExpDepth = _pDlg ->ReturnEditorExpDepth();
	_MultiListOfPreview = _PreviewDlg->ReturnPreviewMultiList();


	//界面初始化
	_pDlg -> SetVisibility(CATDlgShow);
	InitDataFunc();

	_SelectorListSelectSUProduct->ClearLine();
	_SelectorListSelectSUProduct->SetLine("Select A Product Node On Tree",0);
	_EditorSULevel->SetText(CATUnicodeString("Set The First Node Level On 2DTable")); 
	_EditorSelectEBOM->SetText(CATUnicodeString("Please Select A EBOM File")); 
	_EditorExpDepth->SetIntegerValue(2); 
	//_pDlg -> SetVisibility(CATDlgShow);

	//选择功能设定
	//----------------------------------
	//1选择代理
	_pElmAgtSelProduct = new CATOtherDocumentAgent("ElmAgtSelProductId","YFSelProductCmd","YFDrwToolsPartListM");
	CATLISTV(CATString) TypeListExpDir = NULL;
	TypeListExpDir.Append(CATString("CATIProduct"));
	_pElmAgtSelProduct->SetOrderedTypeList(TypeListExpDir);
	_pElmAgtSelProduct->SetBehavior(CATDlgEngWithPrevaluation|CATDlgEngWithPSOHSO|CATDlgEngWithTooltip|CATDlgEngOneShot) ;

	//1界面代理
	/*_pDlgAgtSelProduct = new CATDialogAgent("DlgAgtSelProductId");
	_pDlgAgtSelProduct->AcceptOnNotify(_SelectorListSelectSUProduct, _SelectorListSelectSUProduct->GetListSelectNotification());*/

	//0初始状态定义
	CATDialogState * pInitialState = GetInitialState("StInitialId");
	//pInitialState->AddDialogAgent(_pDlgAgtSelProduct);
	pInitialState->AddDialogAgent(_pElmAgtSelProduct);
   
	//1状态定义
	/*CATDialogState * pSelProductState = AddDialogState("StSelProduct");
	pSelProductState->AddDialogAgent(_pElmAgtSelProduct);
	pSelProductState->AddDialogAgent(_pDlgAgtSelProduct);*/

	//0初始状态切换
	//AddTransition( pInitialState,pInitialState, (IsOutputSetCondition(_pDlgAgtSelProduct)),Action ((ActionMethod) &YFGeneratePartListCmd::ChangeToModleWindow));

	//1状态切换
	AddTransition( pInitialState,pInitialState, (IsOutputSetCondition(_pElmAgtSelProduct)),Action ((ActionMethod) &YFGeneratePartListCmd::ShotElmAgtSelProductFunc));
 
	//事件设定
	//----------------------------------
	AddAnalyseNotificationCB (_pDlg, _pDlg -> GetDiaPREVIEWNotification(),(CATCommandMethod)&YFGeneratePartListCmd::ActionPreview,NULL);
	AddAnalyseNotificationCB (_pDlg, _pDlg -> GetDiaCANCELNotification(),(CATCommandMethod)&YFGeneratePartListCmd::ActionCancel,NULL);
	AddAnalyseNotificationCB (_pDlg, _pDlg -> GetDiaOKNotification(),(CATCommandMethod)&YFGeneratePartListCmd::ActionOk,NULL);
	AddAnalyseNotificationCB (_pDlg, _pDlg -> GetWindCloseNotification(),(CATCommandMethod)&YFGeneratePartListCmd::ActionClose,NULL);
	AddAnalyseNotificationCB (_SelectorListSelectSUProduct, _SelectorListSelectSUProduct -> GetListSelectNotification(),(CATCommandMethod)&YFGeneratePartListCmd::ChangeToModleWindowFunc,NULL);
	AddAnalyseNotificationCB (_BTSelectEBOM, _BTSelectEBOM -> GetPushBActivateNotification(),(CATCommandMethod)&YFGeneratePartListCmd::SelEBOMExcelFunc,NULL);

		//预览设定
	AddAnalyseNotificationCB (_PreviewDlg, _PreviewDlg -> GetDiaCANCELNotification(),(CATCommandMethod)&YFGeneratePartListCmd::ActionPreviewCancelFunc,NULL);
	AddAnalyseNotificationCB (_PreviewDlg, _PreviewDlg -> GetDiaOKNotification(),(CATCommandMethod)&YFGeneratePartListCmd::ActionPreviewOkFunc,NULL);
	AddAnalyseNotificationCB (_PreviewDlg, _PreviewDlg -> GetWindCloseNotification(),(CATCommandMethod)&YFGeneratePartListCmd::ActionPreviewCloseFunc,NULL);
		//预览点击响应
	AddAnalyseNotificationCB (_MultiListOfPreview, _MultiListOfPreview->GetListActivateNotification(),(CATCommandMethod)&YFGeneratePartListCmd::ActionChangeYesOrNoFunc,NULL);
	
}


//描述：主界面关闭函数
//输入：cmd-按钮指针，evt-事件指针，data-数据
//输出：void
//返回：void
void YFGeneratePartListCmd::ActionClose(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	//关闭
	RequestDelayedDestruction();
}

//描述：主界面取消函数
//输入：cmd-按钮指针，evt-事件指针，data-数据
//输出：void
//返回：void
void YFGeneratePartListCmd::ActionCancel(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	//cout<<"Enter Function:ActionCancel()..."<<endl;
	//删除生成的明细表
	DeleteTabelBomFunc();
	_pDlg->SetVisibility (CATDlgHide);
	RequestDelayedDestruction();
}

//描述：主界面确定函数
//输入：cmd-按钮指针，evt-事件指针，data-数据
//输出：void
//返回：void
void YFGeneratePartListCmd::ActionOk(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	//确定
	RequestDelayedDestruction();
	
}

//描述：主界面预览函数
//输入：cmd-按钮指针，evt-事件指针，data-数据
//输出：void
//返回：void
void YFGeneratePartListCmd::ActionPreview(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	//跳转至预览界面
	_MultiListOfPreview->ClearLine();
	_vecPreviewBomList.clear();
	_vecModelInfoList.clear();

	//判断所有输入值是否已经输入
	CATUnicodeString strEBOMPath = _EditorSelectEBOM->GetText();//EBOM路径
	CATUnicodeString strDepth = _EditorExpDepth->GetText();//深度
	CATUnicodeString strLevel = _EditorSULevel->GetText();//层级
	CATUnicodeString strProduct = NULL;
	_SelectorListSelectSUProduct->GetLine(strProduct,0);
	if (strEBOMPath == "Please Select A EBOM File" || strDepth == NULL || strLevel == "Set The First Node Level On 2DTable"|| strLevel == NULL || strProduct == "Select A Product Node On Tree")
	{
		CAAMessageBox("Error input !","Notice");
		return ;
	}
	
	//判断输入的等级和细分深度
	int intNumDepth = 0;
	int intNumLevel = 0;
	int intCovertIsOk = 0;
	intCovertIsOk = strDepth.ConvertToNum(&intNumDepth);
	if (intCovertIsOk == 0 && strDepth != "bottom" && strDepth != NULL) {CAAMessageBox("Please input correct value !","Notice");return ;}//判断：如果随便输入

	intCovertIsOk = strLevel.ConvertToNum(&intNumLevel);
	if (intCovertIsOk == 0) {CAAMessageBox("Please input correct value !","Notice");return ;}//判断：如果随意输入

	if (strDepth == "bottom" || strDepth == NULL) intNumDepth = 1024;//判断：输入为bottom以及为空

	if (intNumDepth<2) {CAAMessageBox("Error : Depth less than 2 !","Notice");return ;}//判断：细分深度如果小于2

	CATUnicodeString error = NULL;
	//判断以及定位所选节点和以及其父节点	
	CATBoolean rc = CheckSelectNodeFunc(_spSelProduct,error);
	if(rc == FALSE) CAAMessageBox(error,"Notice");

	//遍历数模所选节点下所有节点实例名和对应数量
	rc = GetPartListInfoFunc(_spSelProduct,intNumDepth,1,error);
	if (rc == FALSE) {CAAMessageBox(error,"Notice");return ;}
	
	//获取EBOM中的信息
	GetPreviewBomInfoFunc(intNumLevel,intNumDepth);

	//判断EBOM中子级和数模中的子级是否匹配
	CheckChildNodeFunc();


	//输出错误信息并选择是否继续
	if (_vecModelNotInEBOM.size() || _vecEBOMNotInModel.size())
	{
		
		CATUnicodeString strModelNotInEBOM = NULL;//EBOM中不存在这些
		CATUnicodeString strEBOMNotInModel = NULL;//零件中不存在这些
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


//描述：选择Excel成功响应函数
//输入：cmd-按钮指针，evt-事件指针，data-数据
//输出：void
//返回：void
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
//描述：取消选择Excel响应函数
//输入：cmd-按钮指针，evt-事件指针，data-数据
//输出：void
//返回：void
void YFGeneratePartListCmd::ChooseFileCancelFunc( CATCommand *, CATNotification* , CATCommandClientData data )
{
	if(_FileSelectEBOM != NULL)
	{
		_FileSelectEBOM->SetVisibility(CATDlgHide);
	}
}

//描述：设置选择excel弹框属性
//输入：cmd-按钮指针，evt-事件指针，data-数据
//输出：void
//返回：void
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


//描述：跳转窗口到模型窗口
//输入：cmd-按钮指针，evt-事件指针，data-数据
//输出：void
//返回：void
void YFGeneratePartListCmd::ChangeToModleWindowFunc(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	//cout<<"窗口跳转"<<endl;
	CATUnicodeString pCurrentSelectProdName = NULL;
	int intSeletLine = _ComboSelectAssembly -> GetSelect();
	_ComboSelectAssembly -> GetLine(pCurrentSelectProdName,intSeletLine);
	CATLISTP(CATFrmWindow) listOfCurWindows = _pLayout->GetWindowList() ;
	int intFlag = 0;
	//遍历当前打开数模窗口中有无当前选择的数模
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

//描述：选择起始总成，窗体响应
//输入：data-数据
//输出：void
//返回：void
void YFGeneratePartListCmd::ShotDlgAgtSelProductFunc( void * data )
{
	//cout<<"选择节点"<<endl;
	_pDlgAgtSelProduct->InitializeAcquisition();
}

//描述：选择起始总成，获取变量值
//输入：data-数据
//输出：void
//返回：void
void YFGeneratePartListCmd::ShotElmAgtSelProductFunc( void * data )
{
	//cout<<"获取节点"<<endl;
	_spSelProduct = GetSelectObjectFromAgent(_pElmAgtSelProduct);
	if (  _spSelProduct !=  NULL_var)
	{
		_SelectorListSelectSUProduct->ClearLine();
		CATIProduct_var spiProduct = _spSelProduct;
		_SelectorListSelectSUProduct->SetLine(spiProduct->GetPartNumber(),0);
		
		//设置默认等级
		CATUnicodeString strLevel = GetLevelNumberFunc(_spSelProduct);
		_EditorSULevel->SetText(strLevel);

	}
	_pElmAgtSelProduct->InitializeAcquisition();
}


/************************************************************************/
/*								ADD FUNCTION							*/
/************************************************************************/

//描述：读取Excel中数据
//输入：void
//输出：oError-错误信息
//返回：TRUE or FALSE
CATBoolean YFGeneratePartListCmd::ReadEBOMInfoFunc(CATUnicodeString& oError)
{
	//cout<<"Start ReadEBOMInfo()..."<<endl;
	//获取程序打开excel前存在的excel进程
	_oldPid = GetIdFunc();
	//读取EBOM内容
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
		//判断是否是选取的excel 格式
		if (pBomPath.SubString(pBomPath.GetLengthInChar()-5,5 )==CATUnicodeString(".xlsx")||pBomPath.SubString(pBomPath.GetLengthInChar()-4,4 )==CATUnicodeString(".xls"))
		{
			
			hr = CoInitialize(NULL);//没加之前创建EXCEL服务失败
			//打开excel进程
	
			if (!ExcelApp.CreateDispatch( _T( "Excel.Application" ), NULL ))
			{
				::MessageBox( NULL, _T( "创建Excel服务失败！" ), _T( "错误提示！" ), MB_OK | MB_ICONERROR);	
				_strErrorTime = GetTimeFunc();
				ofstream errorFile(_strErrorPath.ConvertToChar(),ios::app);
				errorFile<<_strErrorTime<<":创建Excel服务失败!\n";
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

			//读取数据
			int intRowNum = 10;
			int intColumnNum = 1;
			while (1)
			{

				PartListInfo* temoInfoList=new PartListInfo();
				temoInfoList->InitialDataFunc();

				//EBOM行数（为方便后面比较连续相同序号）
				temoInfoList->intEBOMRow = intRowNum - 10;

				//序号(第一列)
				_variant_t vNoValue = ExlRag.GetItem(_variant_t(RowNum),_variant_t(1));
				CATUnicodeString strNo = NULL;
				strNo.BuildFromBSTR(_bstr_t(vNoValue));
				if (strNo == NULL) break;
				temoInfoList->No = strNo;

				//层级(2-13列，有*号列即为层级)
				int intLevel = 1;
				CATUnicodeString strLevel = NULL;
				if(strNo == "0")
					strLevel = "0";
				else{
					FindPointsGetLevelFunc(strNo,intLevel);
					strLevel.BuildFromNum(intLevel);
				}
				temoInfoList->Level = strLevel;

				//数量
				_variant_t vNumberValue = ExlRag.GetItem(_variant_t(RowNum),_variant_t(14));
				CATUnicodeString strNumber = NULL;
				strNumber.BuildFromBSTR(_bstr_t(vNumberValue));
				temoInfoList->Quantity = strNumber;

				//零件号
				intColumnNum = GetColumnNumFunc(ExlRag,"延锋零件号"); 
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
				

				//版本
				intColumnNum = GetColumnNumFunc(ExlRag,"版本号\n（延锋）"); 
				if (intColumnNum == 0) {oError = "I/O error:Please ensure that the Excel field meets the standard!";_newPid = GetIdFunc();RemoveExcelProcessFunc(_oldPid,_newPid);return FALSE;}
				_variant_t vVersionValue = ExlRag.GetItem(_variant_t(intRowNum),_variant_t(intColumnNum));
				CATUnicodeString strVersion = NULL;
				strVersion.BuildFromBSTR(_bstr_t(vVersionValue));
				temoInfoList->VersionNo = strVersion;

				//零件名
				intColumnNum = GetColumnNumFunc(ExlRag,"零件名/描述"); 
				if (intColumnNum == 0) {oError = "I/O error:Please ensure that the Excel field meets the standard!";_newPid = GetIdFunc();RemoveExcelProcessFunc(_oldPid,_newPid);return FALSE;}
				_variant_t vPartNumberValue = ExlRag.GetItem(_variant_t(intRowNum),_variant_t(intColumnNum));
				CATUnicodeString strPartNumber = NULL;;	
				strPartNumber.BuildFromBSTR(_bstr_t(vPartNumberValue));
				temoInfoList->PartName = strPartNumber;

				//材料
				intColumnNum = GetColumnNumFunc(ExlRag,"材料名称"); 
				if (intColumnNum == 0) {oError = "I/O error:Please ensure that the Excel field meets the standard!";_newPid = GetIdFunc();RemoveExcelProcessFunc(_oldPid,_newPid);return FALSE;}
				_variant_t vMaterialValue = ExlRag.GetItem(_variant_t(intRowNum),_variant_t(intColumnNum));
				CATUnicodeString strMaterial = NULL;
				strMaterial.BuildFromBSTR(_bstr_t(vMaterialValue));
				temoInfoList->Material = strMaterial;

				//备注
				intColumnNum = GetColumnNumFunc(ExlRag,"备注"); 
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

//描述：根据字段判断所在列数
//输入：iExlRag-Excel变量,iColumnText-要查找的文本内容
//输出：void
//返回：int - 文本内容所在函数
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
		//if (strText == NULL) return 0;//如果没有遍历到
		if (intColumn > 75)  return 0;//如果没有遍历到

		if (strText == iColumnText)	return intColumn;//如果找到则返回对应列数

		intColumn++; 
	}
}

//描述：关闭后台excel进程
//输入：iOldPid-程序运行前进程号,iNewPid-程序运行后进程号
//输出：void
//返回：void
void YFGeneratePartListCmd::RemoveExcelProcessFunc(vector<int> iOldPid,vector<int> iNewPid)
{
	//定义需要关闭的excel的新容器
	vector<int> excelNeedClose;

	//遍历不同pid，单独放入一个这个新容器
	//case 1:2个容器都不为空
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
	//case 2:程序运行excel前，并没有excel运行
	if (iOldPid.size() == 0 && iNewPid.size() != 0) excelNeedClose.assign(iNewPid.begin(),iNewPid.end());

	//case 3:并没有运行excel
	if (iOldPid.size() == 0 && iNewPid.size() == 0) return ;

	//关闭excel
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

//描述:获取进程ID
//输入:void
//输出:void
//返回:vector<int>-进程号容器
vector<int> YFGeneratePartListCmd::GetIdFunc()
{
	vector<int> pIDVec;
	setlocale(LC_ALL, "");
	HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);    //建立进程快照

	if (INVALID_HANDLE_VALUE == hProcess)
	{
		_strErrorTime = GetTimeFunc();
		ofstream errorFile(_strErrorPath.ConvertToChar(),ios::app);
		errorFile<<_strErrorTime<<":获取进程信息失败!\n";
		errorFile.close(); 
		//printf("获取进程信息失败！！！\n");
		//return FALSE;
	}

	//成功获取进程信息
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	BOOL moreProc = Process32First(hProcess, &pe32);

	while (moreProc)   //枚举所有进程
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
			//_tprintf(_T("进程名称：%s\n"), pe32.szExeFile);
			//_tprintf(_T("进程ID号：%u\n"), pe32.th32ProcessID);
			pIDVec.push_back(IdNum);
		}

		moreProc = Process32Next(hProcess, &pe32);
	}

	CloseHandle(hProcess);        //释放进程快照
	return pIDVec;
}

//描述：测试打印
//输入：iVecTest - 类容器
//输出：void
//返回：void
void YFGeneratePartListCmd::printInfoFunc(vector< PartListInfo* > iVecTest)
{
	//cout<<"容器元素个数 = "<<iVecTest.size()<<endl;
	if (iVecTest.size()>0)
	{
		for (vector<PartListInfo*>::iterator it = iVecTest.begin();it!=iVecTest.end();it++)
		{
			cout<<endl;
			cout<<(*it)->TableNo<<")("<<(*it)->Level<<")("<<(*it)->YFPartNumber<<")("<<(*it)->VersionNo<<")("<<(*it)->PartName<<")("<<(*it)->Quantity<<")("<<(*it)->Material<<")("<<(*it)->Notes<<endl;

		}
	}
	
}

//描述：判断选中节点是否符合标准(所选节点以及其父级子级的名称是否和EBOM中的一致)
//输入：ispiSelectNode - 所选节点
//输出：oError-错误信息
//返回：TRUE or FALSE
CATBoolean YFGeneratePartListCmd::CheckSelectNodeFunc(CATISpecObject_var ispiSelectNode,CATUnicodeString& oError)
{
	//cout<<"Enter Function: CheckSelectNode（判断所选节点是否符合要求）..."<<endl;
	if (!ispiSelectNode) {oError = "Select Error!"; return FALSE;}

	CATUnicodeString strPartName = NULL;
	CATUnicodeString strYFPartNumber = NULL;

	//找出EBOM中所有对应的零件号
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
				vecTempList.push_back(*it);//找出在EBOM表中与当前节点零件号所有一样的零件号
		}
	}
	if (vecTempList.size()!=0)//判断父级是否一致
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
				
				for (int i = (*it)->intEBOMRow;i>=0;i--)//从当前节点序号往上寻找第一个父级
				{
					_vecEBOMInfos[i]->Level.ConvertToNum(&fatherLevel);	
					if (intLevel == fatherLevel + 1)
					{
						if (strYFPartNumber == _vecEBOMInfos[i]->YFPartNumber)
						{
							intFlag = 1;
							_intSelectRow = (*it)->intEBOMRow;
							//cout<<"当前选择行号 = "<<_intSelectRow<<endl;
						}
							
						break;
					}
				}
			}

			if (intFlag == 0) {oError = "The selected father node :"+ strPartName + " does not match the EBOM table !";_SelectorListSelectSUProduct->SetLine("Select A Product Node On Tree",0);return FALSE;}
		}else{//如果零件模型上级没有父亲
			
			for (vector<PartListInfo*>::iterator it = _vecEBOMInfos.begin();it!=_vecEBOMInfos.end();it++)
			{
				if (strYFPartNumber == (*it)->YFPartNumber)
				{
					_intSelectRow = (*it)->intEBOMRow;
					//cout<<"当前选择行号 = "<<_intSelectRow<<endl;
					break;
				}
			}
		}

	}else{//如果本身没有

		oError = "The selected node :"+ strPartName + " does not match the EBOM table !";_SelectorListSelectSUProduct->SetLine("Select A Product Node On Tree",0);return FALSE;
	}

	return TRUE;
}
//描述：判断子级是否匹配
//输入：void
//输出：void
//返回：void
void YFGeneratePartListCmd::CheckChildNodeFunc()
{
	//cout<<"Enter Function: CheckChildNode"<<endl;
	_vecModelNotInEBOM.clear();
	_vecEBOMNotInModel.clear();
	//判断数模里面的数据是否在EBOM中存在
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

		if (intFlag_1 == 0)	_vecModelNotInEBOM.push_back(it_map_1->first);	//EBOM中不存在这些
	}


	//判断EBOM里面的数据是否在数模中存在
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

		if (intFlag_2 == 0)	_vecEBOMNotInModel.push_back((*it_vec_2)->YFPartNumber);	//零件中不存在这些
	}
}

//描述：获取对应等级
//输入：ispiSelectNode - 所选节点
//输出：void
//返回：CATUnicodeString - 所对应等级
CATUnicodeString YFGeneratePartListCmd::GetLevelNumberFunc(CATIProduct_var ispiSelectNode)
{
	//cout<<"Enter Function : GetLevelNumber()"<<endl;

	//通过零件号对比，获取相应等级
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
				//cout<<"Excel中零件号 = "<<(*it_BomInfo)->YFPartNumber<<endl;
				return (*it_BomInfo)->Level;
			}		
		}	
	}

	return -1;
}
//描述：判断小数点,获取等级
//输入：iStr - 序号字符串,iNum - 递归序号
//输出：void
//返回：void
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

//描述：获取所选节点下所有的节点名称
//输入：ispiRootProduct - 所选节点,iUserDepth - 用户定义深度,iDepth-默认深度
//输出：oError - 错误信息
//返回：TRUE or FALSE
CATBoolean YFGeneratePartListCmd::GetPartListInfoFunc(CATIProduct_var ispiRootProduct,int iUserDepth,int iDepth,CATUnicodeString& oError)
{
	//cout<<"Enter Function:GetPartListInfo ..."<<endl;
	CATBoolean rc  = TRUE;
	if (!ispiRootProduct) { oError = "Select node is NULL ！";return FALSE;}

	//将实例名存入容器
	CATUnicodeString strPartName = ispiRootProduct->GetPartNumber();
	int intPos = strPartName.SearchSubString("_");
	if (intPos!=-1)
	{
		CATUnicodeString strYFPartNumber = strPartName.SubString(0,intPos);
		_mapProducts[(CATIProduct*)ispiRootProduct] = strYFPartNumber;//把对应的product类型存入容器
		if (_vecModelInfoList.size()!=0)
		{
			int intFlag = 0;
			for (map<CATUnicodeString,int>::iterator it = _vecModelInfoList.begin();it!=_vecModelInfoList.end();it++)
			{
				if (it->first == strYFPartNumber)
				{
					it->second++;//相同零件号，数量加1
					intFlag = 1;
					break;
				}
			}
			if (intFlag!=1)
				_vecModelInfoList[strYFPartNumber] = 1;

		}else //如果容器为空则加入
			_vecModelInfoList[strYFPartNumber] = 1;
	}
	
	//当达到指定层级后跳出递归，返回获取的信息
	if (iDepth == iUserDepth) return TRUE;

	//递归
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
//描述：根据获取节点的第一个和最后一个，找出EBOM中所在位置(Useless)
//输入：iStartNumber - 开始序号,iEndNumber - 结束序号,iDepth-默认深度
//输出：oStartRow - 开始行数,oEndRow - 结束行数
//返回：void
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
//描述：获取需要预览的信息
//输入：iUserDefineLevel - 用户自定义起始等级,iUserDefineDepth - 默认起始等级
//输出：void
//返回：void
void YFGeneratePartListCmd::GetPreviewBomInfoFunc(int iUserDefineLevel,int iUserDefineDepth)
{
	//起始等级
	int intStartLevel = 0;
	CATUnicodeString strStartLevel = _vecEBOMInfos[_intSelectRow]->Level;
	strStartLevel.ConvertToNum(&intStartLevel);

	
	for (int i = _intSelectRow;i<_vecEBOMInfos.size();i++)
	{		
		int intLevel = 0;
		CATUnicodeString strLevel = _vecEBOMInfos[i]->Level;
		strLevel.ConvertToNum(&intLevel);

		//处理所选节点下面有相同序号节点
		int intFlag = 0;
		if (_vecEBOMInfos[i]->No == _vecEBOMInfos[_intSelectRow]->No)
		{
			int intEBOMRow = _vecEBOMInfos[i]->intEBOMRow;
			if (intEBOMRow - _intSelectRow < 2) //判断2行相同
				intFlag = 1;					//不需要跳出
		}
	
		//判断何时跳出遍历
		if(intLevel == intStartLevel && i!=_intSelectRow && intStartLevel != 0 && !intFlag) break;
			
		//cout<<"下一等级 = "<<level<<endl;
		if (intLevel <= intStartLevel + iUserDefineDepth - 1)
		{
			//cout<<level<<"<="<<startLevel<<"+"<<iUserDefineDepth<<"-1"<<endl;
			//等级
			CATUnicodeString strUserDefineLevel = NULL;
			strUserDefineLevel.BuildFromNum(iUserDefineLevel + intLevel - intStartLevel);
			_vecEBOMInfos[i]->userDefineLevel = strUserDefineLevel;

			//加入容器
			_vecPreviewBomList.push_back(_vecEBOMInfos[i]);
		}
		
	}
	return ;
}

//描述：判断数模中是否存在EBOM中节点(Useless)
//输入：iYFPartNumber - YF零件号
//输出：void
//返回：int 1-有，0-无
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
//描述：判断是否存在Part
//输入：ispiProduct - 需要判断的节点
//输出：void
//返回：int 1-有，0-无
void YFGeneratePartListCmd::HavePartOrNotFunc(CATIProduct_var ispiProduct,int& oFlag)
{
	if (!ispiProduct) 
	{
		oFlag =  -1;
		return;
	}


	//cout<<"child num = "<<ispiProduct->GetChildrenCount()<<endl;
	//递归
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

	}else{//遍历到最后一级

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
						int intFlag = CheckPartIsNullFunc(spiPrtPart);//判断part是否为空

						if (intFlag ==1) oFlag = 1;
						else oFlag =0;
					}
				}
				else oFlag = 0;
			}
		}

	}

}

//描述：判断是否为空Part
//输入：ispiPrtPart - 当前Part
//输出：void
//返回：int 1-有，0-无
int YFGeneratePartListCmd::CheckPartIsNullFunc(CATIPrtPart_var ispiPrtPart)
{

	HRESULT hr = S_OK;
	CATIPartRequest_var spiPartRequest = ispiPrtPart;
	int flag = 0;
	if (!!spiPartRequest)
	{
		CATListValCATBaseUnknown_var listOfBUPartObjs;
		hr = spiPartRequest->GetAllBodies("MfDefault3DView",listOfBUPartObjs);//获取几何体，和图形集节点

		if (listOfBUPartObjs.Size())
		{
			
			for (int i = 1;i<=listOfBUPartObjs.Size();i++)
			{

				//==获取几何体和图形集下面的特征
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
//描述：判读是否是连续相同序号
//输入：iCurrentFlag - YF当前行号,iVecTableBom-预览数据容器
//输出：void
//返回：int 1-前后都相同,中间序号,2-和前一个不一样，后面一样，开头序号 3-和后面不一样，前面一样，结尾序号
int YFGeneratePartListCmd::ContinuousSameNoOrNotFunc(int iCurrentFlag,vector<PartListInfo*> iVecTableBom)
{
	//cout<<"Enter Function:()..."<<endl;
	//比较需要生成明细栏容器中的序号
	int intFlag = 0;
	int intPreviousFlag = 0;
	int intNextFlag = 0;
	
	if(iCurrentFlag!=0 && iVecTableBom[iCurrentFlag]->No == iVecTableBom[iCurrentFlag-1]->No )//和前一行对比
		intPreviousFlag = 1;

	if (iCurrentFlag!=iVecTableBom.size()-1 && iVecTableBom[iCurrentFlag]->No == iVecTableBom[iCurrentFlag+1]->No)//和后一行对比
		intNextFlag = 1;

	
	if (intPreviousFlag && intNextFlag)//前后都相同,中间序号
		intFlag = 1;
	else if(!intPreviousFlag && intNextFlag)//和前一个不一样，后面一样，开头序号
		intFlag = 2;
	else if(intPreviousFlag && !intNextFlag)//和后面不一样，前面一样，结尾序号
		intFlag = 3;


	return intFlag;
}

//描述：预览界面取消
//输入：cmd-按钮指针，evt-事件指针，data-数据
//输出：void
//返回：void
void YFGeneratePartListCmd::ActionPreviewCancelFunc(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	//关闭预览界面
	_PreviewDlg->SetVisibility(CATDlgHide);
	_pDlg->SetVisibility(CATDlgShow);
	SendNotification(GetFather(),_pCmdNoteCls);
	//_pCmdNoteCls->Release();
	//_pCmdNoteCls = NULL;
}
//描述：预览界面确定
//输入：cmd-按钮指针，evt-事件指针，data-数据
//输出：void
//返回：void
void YFGeneratePartListCmd::ActionPreviewOkFunc(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	cout<<"Enter Function:ActionPreviewOk()..."<<endl;
	_pDlg->SetOKSensitivity(CATDlgEnable);
	_pDlg->SetCANCELSensitivity(CATDlgEnable);
	DeleteTabelBomFunc();
	
	vector<PartListInfo*> pTableBomList;//最后输出的容器
	CATListValCATUnicodeString	listOfNOs;//记录序号
	CATListValCATUnicodeString	listOfYFPartNumber;//记录延锋零件号
	CATListOfInt	ListOfFlag;//记录标志位


	//获取最后所需输出信息
	if (_vecPreviewBomList.size())
	{
		//把预览显示中打勾的信息输出到容器中
		for (int i = 0;i<_vecPreviewBomList.size();i++)
		{
			CATUnicodeString oString = NULL;
			_MultiListOfPreview->GetColumnItem(8,oString,i);
			if (oString == "√")//如果选择了，则加入列表
				pTableBomList.push_back(_vecPreviewBomList[i]);
		}
		
		
		CATUnicodeString strTempNo = NULL;
		int intFlagNum = 0;
		//确定生成的序号
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

			}else{//非多配制
				
				if (intPartOrNotFlag) ListOfFlag.Append(1);
				else ListOfFlag.Append(0);
			}

		}
	
	}


	//ceil 向上取整
	//获取状态
	int intPos = ((CATIProduct_var)_spSelProduct)->GetPartNumber().SearchSubString("_");
	CATUnicodeString strYFPartNumber = ((CATIProduct_var)_spSelProduct)->GetPartNumber().SubString(0,intPos);

	double dblTableNo = 0.;
	CATUnicodeString strTableNo = NULL;
	int intCheckFlag = 0;
	int intTempFlag = 1;//组号
	int intStartIndex = 0;
	int intTempFlag_2 = 0;//判断多配制
	int intMembers = 1;
	for (int j =1 ;j<=listOfYFPartNumber.Size();j++)
	{
		if(listOfYFPartNumber[j] == strYFPartNumber) pTableBomList[j-1]->TableNo = NULL;//为所选根节点
		else{
			
			if( ListOfFlag[j]/10 == 0 && ListOfFlag[j]%10 == 1)//不为多配制零件，有part
			{
				dblTableNo = ceil(dblTableNo + 0.1);
				strTableNo.BuildFromNum((int)dblTableNo);
				pTableBomList[j-1]->TableNo = strTableNo;

			}else{//多配制零件
				
				
				if ( ListOfFlag[j]/10 == intTempFlag && ListOfFlag[j]%10 == 1)//多配制开头,判断多配制个数，以及下面各多配制有无Part
				{
					intTempFlag_2 = 0;
					intStartIndex = j;//记录多配制零件开头下标
					intTempFlag++;
					for (int j_1 = j+1;j_1<=listOfYFPartNumber.Size();j_1++)
					{
						if ( ListOfFlag[intStartIndex]/10 == ListOfFlag[j_1]/10)
						{
							intMembers++;//成员个数
							if (ListOfFlag[j_1]%10 == 1)
							{
								intTempFlag_2 = 1;
							}
						}
					}

					//if (ListOfFlag[intStartIndex]%10 == 1)//有Part
					//{
						if (intTempFlag_2 == 1)//下面零件中有Part
						{
							dblTableNo = ceil(dblTableNo + 0.1) + 0.1;
							strTableNo.BuildFromNum(dblTableNo);
							pTableBomList[j-1]->TableNo = strTableNo;

						}else{//下面零件无Part

							dblTableNo = ceil(dblTableNo + 0.1);
							strTableNo.BuildFromNum((int)dblTableNo);
							pTableBomList[j-1]->TableNo = strTableNo;

						}
					/*}*/
				}

				//if( j!=intStartIndex && ListOfFlag[j]/10 == ListOfFlag[intStartIndex]/10 && ListOfFlag[intStartIndex]%10 == 0) continue; //开头零件无Part


				if ( j!=intStartIndex && ListOfFlag[j]%10 == 1)
				{
					dblTableNo = dblTableNo + 0.1;
					strTableNo.BuildFromNum(dblTableNo);
					pTableBomList[j-1]->TableNo = strTableNo;
				}
	

			}
		}													//多配制					有无part
		//cout<<listOfNOs[j]<<" = "<<listOfYFPartNumber[j]<<" = " << ListOfFlag[j]/10<<" = "<<ListOfFlag[j]%10<<endl;
		
	}//end for

	/*for (int i = 0;i<pTableBomList.size();i++)
	{
		cout<<pTableBomList[i]->TableNo<<" = "<<pTableBomList[i]->YFPartNumber<<endl;
	}*/

	
	//创建明细表
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
//描述：预览界面关闭
//输入：cmd-按钮指针，evt-事件指针，data-数据
//输出：void
//返回：void
void YFGeneratePartListCmd::ActionPreviewCloseFunc(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	//关闭预览界面
	_PreviewDlg->SetVisibility(CATDlgHide);
	_pDlg->SetVisibility(CATDlgShow);
	SendNotification(GetFather(),_pCmdNoteCls);
	//_pCmdNoteCls->Release();
	//_pCmdNoteCls = NULL;
}
//描述：双击预览响应
//输入：cmd-按钮指针，evt-事件指针，data-数据
//输出：void
//返回：void
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
//描述：创建明细表
//输入：iVecTableBomList-序号显示的明细表容器
//输出：void
//返回：void
void YFGeneratePartListCmd::CreateTableFunc(vector<PartListInfo*> iVecTableBomList)
{
	//cout<<"Enter Function:()..."<<endl;
	HRESULT hr  = S_OK;
	CATBoolean rc = TRUE;
	/*CATUnicodeString strFontName = "SICH";
	CATBSTR bstrFontName;
	strFontName.ConvertToBSTR(&bstrFontName);*/
	//获得当前文档
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
			CATISheet_var spCurSheet = piDrawing->GetCurrentSheet();//当前图纸
			CATIDftSheet* piDftCurrentSheet = NULL;
			hr = piDftDrawing->GetActiveSheet(&piDftCurrentSheet);
			boolean bRc = TRUE;
			hr = piDftCurrentSheet->IsDetail(&bRc);
			if (bRc) {CAAMessageBox("Error : Current Sheet Is Detail Sheet !","Notice");return;}

			CATIAlias_var spiAlias = spCurSheet;
			CATUnicodeString currentSheetName = spiAlias->GetAlias();
			CATLISTV(CATISpecObject_var) listOfFormerSheets = piDrawing->GetSheetList();
				
			CATIView_var spCurView = spCurSheet->GetMainView(); //当前视图
			//获取图纸大小
			double dblWidth,dblHeight;
			CATIDftSheetFormat *piDftSheetFormat=NULL;
			spCurSheet->QueryInterface(IID_CATIDftSheetFormat,(void**)&piDftSheetFormat);
			if(piDftSheetFormat==NULL) return;
			piDftSheetFormat->GetSheetSize(dblWidth,dblHeight);
			piDftSheetFormat->Release();
			piDftSheetFormat=NULL;
			double dblOx,dblOy;//表格定位点
			double dblH;//可画表格空间高度

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
			//创建表格
			CATIADrawingTable *piTable =NULL;
			CATIADrawingText* piText = NULL;
			CATIADrawingTextProperties* piTextProp = NULL;
			CATIDrwTextProperties_var spiDrwTestProp = NULL_var;
			int intTotalRow = iVecTableBomList.size();//总数据数量
			//cout<<"总数据量 = "<<intTotalRow<<endl;
			if (intFlag == 1 || intFlag == 0) //A0或者其他
			{
				piTable = CreateDrawingTableFunc(spCurView,dblOx,dblOy,intTotalRow+1);

				//改名字
				CATIAlias_var spiAlias = piTable;
				CATUnicodeString tableName = "YFPartList";
				spiAlias->SetAlias(tableName);
				//填充数据
				for (int j_1=0;j_1<iVecTableBomList.size();j_1++)
				{
					//设置字段
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

				//加入列表
				CATISpecObject_var spiTableObj = (CATISpecObject_var)piTable;
				_listOfObjNeedToDeleteLst.Append(spiTableObj);

				int intNumFlag = 0;
				int intRowNum = 2;
				float minX = 0.;//定义包维盒最小X坐标
				float maxX = 0.;//定义包维盒最大X坐标
				float minY = 100.;//定义包维盒最小Y坐标
				float maxY = 0.;//定义包维盒最大Y坐标
				while(1)
				{
					
					if (intNumFlag > iVecTableBomList.size()-1) break;
				
					piTable->AddRow(0);
				
					if (minY - 30. < 9.)
					{
						/*cout<<"开始换页"<<endl;
						cout<<"移除 = "<<intRowNum<<endl;*/
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
							//加入列表
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

					//cout<<"开始写入第 = "<<intNumFlag+1<<"个数据，在第 "<<intRowNum<<" 行"<<endl;
					//改名字
					CATIAlias_var spiAlias = piTable;
					CATUnicodeString tableName = "YFPartList";
					spiAlias->SetAlias(tableName);

					//设置字段
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
					//cout<<"字段 = "<<iVecTableBomList[intNumFlag]->PartName<<endl;

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
					if (SUCCEEDED(piTable->QueryInterface(IID_CATI2DGeoVisu,(void**)&pi2DGeoVisu)))//获取管理二维可视化界面的接口指针
					{
						CATRep* pRep = pi2DGeoVisu->GiveRep();//获取图形表示的指针
						if (pRep)
						{
							CAT2DRep* p2DRep = (CAT2DRep*)pRep;//类型转化
							if (p2DRep)
							{
								CAT2DBoundingBox boundingBox = p2DRep->GetBoundingElement();//获取包维盒的二维表示信息

								boundingBox.GetParameter(&minX,&maxX,&minY,&maxY);//获取包维盒边界坐标
							
								/*cout<<"minX = "<<minX<<",maxX = "<<maxX<<endl;
								cout<<"minY = "<<minY<<",maxY = "<<maxY<<endl;*/
								
							}
						}
						pi2DGeoVisu->Release();pi2DGeoVisu=NULL;
					}

					intRowNum++;
					intNumFlag++;

					//cout<<"写入完毕"<<endl;
				}

				//cout<<"break while"<<endl;
				//图纸排序
				CATLISTV(CATISpecObject_var) listOfSortSheets;
				CATLISTV(CATISpecObject_var) listOfSheets = piDrawing->GetSheetList();
				CATIAlias_var spiTestAlias = NULL_var;
				if (listOfSheets.Size()&&listOfFormerSheets.Size())
				{
					for (int i_sheet = 1;i_sheet<=listOfFormerSheets.Size();i_sheet++)
					{	
						spiTestAlias = listOfFormerSheets[i_sheet];
						//cout<<"排序后的名称 = "<<spiTestAlias->GetAlias()<<endl;
						listOfSortSheets.Append(listOfFormerSheets[i_sheet]);

						CATISheet_var spiSheet = listOfFormerSheets[i_sheet];
						if (spCurSheet == spiSheet)
						{
							for (int j_sheet = listOfFormerSheets.Size()+1;j_sheet<=listOfSheets.Size();j_sheet++)
							{
								spiTestAlias = listOfSheets[j_sheet];
								//cout<<"排序后新加的名称 = "<<spiTestAlias->GetAlias()<<endl;
								listOfSortSheets.Append(listOfSheets[j_sheet]);
							}
						}	
					}
				}

				if (FAILED(piDftDrawing->ValidateSheetOrder(listOfSortSheets)))
				{
					_strErrorTime = GetTimeFunc();
					ofstream errorFile(_strErrorPath.ConvertToChar(),ios::app);
					errorFile<<_strErrorTime<<":ValidateSheetOrder排序失败!\n";
					errorFile.close(); 
				}

				if (FAILED(piDftDrawing->ReorderSheets(listOfSortSheets)))
				{
					_strErrorTime = GetTimeFunc();
					ofstream errorFile(_strErrorPath.ConvertToChar(),ios::app);
					errorFile<<_strErrorTime<<"::ReorderSheets排序失败!\n";
					errorFile.close(); 
				}

			
			}//end else

			
			
			piDftDrawing->Release();piDftDrawing =NULL;
			piDrawing->Release();piDrawing = NULL;
			piDftCurrentSheet->Release();piDftCurrentSheet=NULL;
			
		}
	}


}
//描述：创建表头
//输入：ispiCurView-当前所在视图,ox-定位X点，oy-定位Y点，row-行数
//输出：void
//返回：CATIADrawingTable - 明细表指针
CATIADrawingTable* YFGeneratePartListCmd::CreateDrawingTableFunc(CATIView_var ispiCurView,double ox,double oy,int row)
{
	CATIADrawingTables* pTables = NULL;
	CATIADrawingTable  *piTable = NULL;
	CATIADrawingText* piText = NULL;
	CATIADrawingTextProperties* piTextProp = NULL;
	if (SUCCEEDED(ispiCurView->QueryInterface(IID_CATIADrawingTables,(void**)&pTables))&&pTables)
	{
		pTables->Add(ox,oy,row,8,9.88,8,piTable); //x/y/行、列、行高，列宽
		if (piTable!=NULL)
		{
			//cout<<"表头创建成功!"<<endl;
			CATUnicodeString arryTableNames[8]={"序号\nNO","级别\nLEVEL","零件号\nPART NO","版本\nREV","零件名称\nPART NAME","数量\nQUANTITY","材料\nMATERIAL","备注\nNOTES"};
			piTable->SetRowSize(1,10);
			//列宽
			double arryColWidth[8]={11,14.0,25.0,9.0,70.0,21.0,27.0,18.0};
			for(int j =0;j<8;j++)
			{
				CATUnicodeString strText = NULL;
				piTable->SetColumnSize(j+1,arryColWidth[j]);
				piTable->SetCellString(1,j+1,_bstr_t(arryTableNames[j].ConvertToChar()));//设置首行字段
				piTable->SetCellAlignment(1,j+1,CatTableMiddleCenter);//居中
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
//描述：char转wchar
//输入：cchar-const char* 型字符串
//输出：void
//返回：wchar_t* - wchar_t* 型字符串
wchar_t* YFGeneratePartListCmd::char2wcharFunc(const char* cchar) 
{     
	wchar_t *m_wchar;    
	int len = MultiByteToWideChar( CP_ACP ,0,cchar ,strlen( cchar), NULL,0);     
	m_wchar= new wchar_t[len+1];     
	MultiByteToWideChar( CP_ACP ,0,cchar,strlen( cchar),m_wchar,len);     
	m_wchar[len]= '\0' ;    
	return m_wchar; 
} 
//描述：转换
//输入：str-CATUnicodeString 型字符串
//输出：void
//返回：CATBSTR - CATBSTR 型字符串
CATBSTR YFGeneratePartListCmd::CATUnicodeStringToCATBSTRFunc(CATUnicodeString str)
{
	CATBSTR pBSTR=NULL;
	str.CATUnicodeString::ConvertToBSTR(&pBSTR); 
	return pBSTR;
}
//描述：初始化界面
//输入：void
//输出：void
//返回：void
void YFGeneratePartListCmd::InitDataFunc()
{
	//获取窗口列表 
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
		//判断
		if (intProFlag == 0)
		{
			CAAMessageBox("Please Open A CATProduct File！","Notice");
			RequestDelayedDestruction();//防止命令不结束
			return ;
		}else if(intDraFlag == 0){
			CAAMessageBox("Please Open A 2D Drawing  Relating To Part or Product!","Notice");
			RequestDelayedDestruction();//防止命令不结束
			return ;
		}

	}else{
		CAAMessageBox("Please Open A CATProduct File And A 2D Drawing !","Notice");
		RequestDelayedDestruction();//防止命令不结束
		return ;
	}

	//获取当前窗口
	_pCurrentWindow = _pLayout->GetCurrentWindow();
	CATUnicodeString oCurType = GetDocumentTypeFunc(_pCurrentWindow);
	if(oCurType != "CATDrawing")
	{
		CAAMessageBox("Please switch to the Drawing module operation !","Notice");
		RequestDelayedDestruction();//防止命令不结束
		return ;
	}

	//_pDlg ->SetVisibility(CATDlgShow);
	return ;
}
//描述：获取窗口类型
//输入：ipWind - 当前窗口
//输出：void
//返回：CATUnicodeString - 窗口类型
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


//描述：字体更换
//输入：ipiADrawingText - 字体属性指针,iStrText-文本内容,iStartPos - 开始位置
//输出：void
//返回：void
void YFGeneratePartListCmd::ChangeFontFunc(CATIADrawingText* ipiADrawingText,CATUnicodeString iStrText,int iStartPos)
{
	//判断中英文
	
	string str = UnicodeToANSIFunc(iStrText);
	if(str[0]<255 && str[0]>0)//扩充的ASCII字符范围为0-255,如是,处理一个字节,英文数字
	{
		//cout<<str.substr(0,1)<<" 英文 =  "<<iStrText.SearchSubString(str.substr(0,1).c_str())<<"位置 = "<<iStartPos<<endl;
		CATUnicodeString strFontName = "SSS1";
		CATBSTR bstrFontName;
		strFontName.ConvertToBSTR(&bstrFontName);
		ipiADrawingText->SetFontSize(iStartPos,1,2.5);
		ipiADrawingText->SetFontName(iStartPos,1,bstrFontName);
		iStrText.Remove(iStrText.SearchSubString(str.substr(0,1).c_str()));
		if (iStrText!=NULL) ChangeFontFunc(ipiADrawingText,iStrText,iStartPos+1);
	}
	else//<0,>255的是汉字,处理两个字节,汉字
	{	
		//cout<<str.substr(0,2)<<" 中文 =  "<<iStrText.SearchSubString(str.substr(0,2).c_str())<<"位置 = "<<iStartPos<<endl;
		CATUnicodeString strFontName = "SICH";
		CATBSTR bstrFontName;
		strFontName.ConvertToBSTR(&bstrFontName);
		ipiADrawingText->SetFontSize(iStartPos,1,3.5);
		ipiADrawingText->SetFontName(iStartPos,1,bstrFontName);
		iStrText.Remove(iStrText.SearchSubString(str.substr(0,2).c_str()));
		if (iStrText!=NULL) ChangeFontFunc(ipiADrawingText,iStrText,iStartPos+1);
	}
}
//描述：删除明细表
//输入：void
//输出：void
//返回：void
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

//描述：提示消息点击确定继续生成
//输入：cmd-按钮指针，evt-事件指针，data-数据
//输出：void
//返回：void
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
		_MultiListOfPreview->SetColumnItem(8,"√",intRow,CATDlgDataModify);
		intRow++;
	}

	_PreviewDlg->SetVisibility(CATDlgShow);
	_pDlg->SetVisibility(CATDlgHide);
}
//描述：提示消息点击取消
//输入：cmd-按钮指针，evt-事件指针，data-数据
//输出：void
//返回：void
void YFGeneratePartListCmd::ActionDlgCancelFunc(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	//cout<<"ActionDlgClose"<<endl;
	((CATDlgNotify*)data)->SetVisibility(CATDlgHide);
}


//描述：复制图纸
//输入：ispiSourceSheet - 要拷贝的sheet,ispiTargetDrawing - 拷贝的目的地
//输出：void
//返回：CATISheet_var - 返回结果对象
CATISheet_var YFGeneratePartListCmd::CopySheetFunc(CATISheet_var ispiSourceSheet,CATIDrawing_var ispiTargetDrawing)
{
	
	if (!ispiSourceSheet || !ispiTargetDrawing)
	{
		_strErrorTime = GetTimeFunc();
		ofstream errorFile(_strErrorPath.ConvertToChar(),ios::app);
		errorFile<<_strErrorTime<<":拷贝图纸参数错误!\n";
		errorFile.close(); 
		return NULL_var;
	}

	//获取 :spiTargetCutAndPast
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

	//获取 :spiSourceCutAndPast
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

	//拷贝
	IdFormat iIdFmy = "CATDrwCont";
	const CATFormat* pFmt = CATFormat::GetRegisteredFormat(iIdFmy);

	ListOfVarBaseUnknown listFromCopy;
	listFromCopy.Append((CATBaseUnknown *)spiSpecOnSourceSheet);

	ListOfVarBaseUnknown lisTarget;
	lisTarget.Append(spiSpecOnTargetDrawing);

	ListOfVarBaseUnknown listPastedObjects = spiTargetCutAndPast -> Paste (listFromCopy,&lisTarget,pFmt);

	//获取结果
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
//描述：删除图纸中表格
//输入：ispiDftView - 当前视图
//输出：void
//返回：CATBoolean - true of false
CATBoolean YFGeneratePartListCmd::DeleteTablesInViewFunc(CATIView_var ispiDftView)
{
	HRESULT hr = S_OK;
	if (!ispiDftView)
	{
		_strErrorTime = GetTimeFunc();
		ofstream errorFile(_strErrorPath.ConvertToChar(),ios::app);
		errorFile<<_strErrorTime<<":DeleteTablesInViewFunc 函数参数错误!\n";
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

	//获取表数目
	CATLONG itableCount;
	piADrawingTables->get_Count(itableCount);

	for (CATLONG i = 1;i<=itableCount;i++)
		piADrawingTables->Remove(i);

	piADrawingTables->Release();piADrawingTables = NULL;

	return TRUE;

}
//字符转化
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