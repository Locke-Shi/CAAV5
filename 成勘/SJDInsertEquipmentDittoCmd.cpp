﻿//===================================================================
// COPYRIGHT Company 2021/01/15
//===================================================================
// SJDInsertEquipmentDittoCmd.cpp
// Header definition of class SJDInsertEquipmentDittoCmd
//===================================================================
//
// Usage notes:
//
//===================================================================
//  2021/01/15 Creation: Code generated by the 3DS wizard
//===================================================================

//BUG1:当第一个没选，只选择第二个时候，程序崩溃

#include "SJDInsertEquipmentDittoCmd.h"
#include "CATIndicationAgent.h"
#include "CATMathPlane.h"

//ObjectModelerSystem
#include "CATIAlias.h"

//VisualizationInterfaces 
#include "CATIBuildPath.h"
#include "CATPathElement.h"

//ObjectModelerBase
#include "CATOmbLifeCycleRootsBag.h"

//PLMLibraryNavUseItf
#include "PLMICLGLibrary.h"
#include "PLMCLGPublicLibraryNavServices.h"

#include "CATIDftView.h"

#include "CATCreateExternalObject.h"
CATCreateClass(SJDInsertEquipmentDittoCmd);

// Constructor
SJDInsertEquipmentDittoCmd::SJDInsertEquipmentDittoCmd() :
	CATStateCommand("SJDInsertEquipmentDittoCmd", CATDlgEngOneShot, CATCommandModeShared)
	//  Valid states are CATDlgEngOneShot and CATDlgEngRepeat
	, _pDlg(NULL)
	, _pViewAgent(NULL)
	, _pEditor(NULL)
	, _pHSO(NULL)
	, _pISO(NULL)
	, _strNoSelection("")
	, _strCatalogName("")
	, _strChapterPartName("")
	, _strChapterFeatureName("")
	, _strChapterDittoName("")
	, _spBaseTopView(NULL_var)
	, _spBaseSectionView(NULL_var)
	, _bReadCatalog(FALSE)
{
	//=========================================================================
	//1，读取配置文件
	//读取设备配置信息	
	CATUnicodeString strXMLPath = SJDCHIGeneralServices::GetPathOfResource("CHIDIInvestDesign.xml");
	HRESULT rc = SJDCHIGeneralServices::readInvestDesignViewConfig(strXMLPath, _viewInfo);
	if (FAILED(rc))
	{
		RequestDelayedDestruction();
		CoutMsg("读取CHIDIInvestDesign.xml信息失败");
		return;
	}

	//读取设备配置信息
	rc = SJDCHIGeneralServices::readInvestDesignCatalogConfig(strXMLPath, _strCatalogName, _strChapterPartName, _strChapterFeatureName, _strChapterDittoName);
	if (FAILED(rc))
	{
		RequestDelayedDestruction();
		CoutMsg("读取catalog失败");
		return;
	}

	//SHIY 添加 - 添加函数读取ditto信息
	rc = GetCatalogDittoInfo();
	if (FAILED(rc))
	{
		RequestDelayedDestruction();
		CoutMsg("读取ditto失败");
		return;
	}
	//SHIY END

	//=========================================================================
	//2，对话框显示
	_pDlg = new SJDInsertEquipmentDittoDlg((CATApplicationFrame::GetApplicationFrame())->GetMainWindow(), "SJDInsertEquipmentDittoDlg");
	_pDlg->Build();
	_pDlg->SetVisibility(CATDlgShow);

	_pEditor = CATFrmEditor::GetCurrentEditor();
	_pHSO = _pEditor->GetHSO();

	this->CheckOKSensitivity();
}

// Destructor
SJDInsertEquipmentDittoCmd::~SJDInsertEquipmentDittoCmd()
{
	if (_pDlg != NULL)
		_pDlg->RequestDelayedDestruction();

	if (_pViewAgent != NULL) { _pViewAgent->RequestDelayedDestruction(); _pViewAgent = NULL; }
}

// BuildGraph()
void SJDInsertEquipmentDittoCmd::BuildGraph()
{
	//选择点
	_pViewAgent = new CATPathElementAgent("Select View");
	_pViewAgent->AddElementType(CATIDftView::ClassName());
	_pViewAgent->SetBehavior(CATDlgEngRepeat | CATDlgEngWithPrevaluation | CATDlgEngWithPSO);

	CATDialogState * initialState = GetInitialState("initialState");
	initialState->AddDialogAgent(_pViewAgent);

	AddTransition(initialState, initialState, IsOutputSetCondition(_pViewAgent), Action((ActionMethod)&SJDInsertEquipmentDittoCmd::ActionElementSelected, NULL, NULL, _pViewAgent));

	//OK CANCLE PREVIEW
	AddAnalyseNotificationCB(_pDlg, _pDlg->GetDiaOKNotification(), (CATCommandMethod)&SJDInsertEquipmentDittoCmd::ActionOK, NULL);
	AddAnalyseNotificationCB(_pDlg, _pDlg->GetWindCloseNotification(), (CATCommandMethod)&SJDInsertEquipmentDittoCmd::ActionCancel, NULL);

	//SelectorList选择
	AddAnalyseNotificationCB(_pDlg->GetSelectorList(SL_TopView), _pDlg->GetSelectorList(SL_TopView)->GetListSelectNotification(), (CATCommandMethod)&SJDInsertEquipmentDittoCmd::ActionSelectorListSelect, CATINT32ToPtr(SL_TopView));
	AddAnalyseNotificationCB(_pDlg->GetSelectorList(SL_SectionView), _pDlg->GetSelectorList(SL_SectionView)->GetListSelectNotification(), (CATCommandMethod)&SJDInsertEquipmentDittoCmd::ActionSelectorListSelect, CATINT32ToPtr(SL_SectionView));
	int iLine = 0;
	_pDlg->GetSelectorList(SL_TopView)->SetSelect(&iLine, 1);
}

HRESULT SJDInsertEquipmentDittoCmd::GetRootOccurrence(CATIPLMNavOccurrence_var & ospRootOccurrence)
{
	//获得Root装配
	CATFrmLayout*pFrmLayout = CATFrmLayout::GetCurrentLayout();
	CATFrmWindow*pCurrentWindow = pFrmLayout->GetCurrentWindow();
	CATFrmEditor*pEditor = pCurrentWindow->GetEditor();

	//获取当前根对象
	CATPathElement currUIActiveObjPath = pEditor->GetUIActiveObject();
	currUIActiveObjPath.InitToTopElement();
	CATBaseUnknown* piRoot = currUIActiveObjPath.NextChildElement();

	ospRootOccurrence = piRoot;
	if (ospRootOccurrence == NULL_var)
	{
		return E_FAIL;
	}

	return S_OK;
}

// ActionOK ()
CATBoolean SJDInsertEquipmentDittoCmd::ActionOK(CATCommand* iPublishingCommand, CATNotification * iNotification, CATCommandClientData iData)
{
	// TODO: Define the action associated with the transition
	// ------------------------------------------------------

	CATListValCATBaseUnknown_var listAllRepInst;

	HRESULT rc = S_OK;

	//创建TopView三维Ditto
	CATIDftView_var spDftTopView = _spBaseTopView;
	if (spDftTopView != NULL_var)
	{
		//1，获得图纸对应的三维	
		rc = this->GetAllLinkRefOfView(spDftTopView, listAllRepInst);
		if (FAILED(rc) || listAllRepInst.Size() == 0)
		{
			return FALSE;
		}

		//2, 获得所有标注
		CATListOfInt listLegendID;
		CATLISTV(CATMathPoint) listMathPt;
		for (int i = 1; i <= listAllRepInst.Size(); i++)
		{
			CATListOfInt listLegendIDCurrent;
			CATLISTV(CATMathPoint) listMathPtCurrent;

			CATIPLMNavRepInstance_var spRepInst = listAllRepInst[i];
			if (spRepInst == NULL_var)
			{
				CoutMsg("spRepInst == NULL_var");
				continue;
			}

			rc = this->GetAllDittoPt(spRepInst, listLegendIDCurrent, listMathPtCurrent);
			if (FAILED(rc) || listLegendIDCurrent.Size() == 0)
			{
				continue;
			}

			listLegendID.Append(listLegendIDCurrent);
			listMathPt.Append(listMathPtCurrent);
			listLegendIDCurrent.RemoveAll();
			listMathPtCurrent.RemoveAll();
		}

		//3，在当前View中创建Ditto
		rc = this->CreateDittoInView(spDftTopView, 0, listLegendID, listMathPt);

		listLegendID.RemoveAll();
		listMathPt.RemoveAll();
		listAllRepInst.RemoveAll();
	}

	CATIDftView_var spDftSectionView = _spBaseSectionView;
	if (spDftSectionView != NULL_var)
	{
		//1，获得图纸对应的三维	
		this->GetAllLinkRefOfView(spDftTopView, listAllRepInst);

		//2, 获得所有标注
		CATListOfInt listLegendID;
		CATLISTV(CATMathPoint) listMathPt;
		for (int i = 1; i <= listAllRepInst.Size(); i++)
		{
			CATListOfInt listLegendIDCurrent;
			CATLISTV(CATMathPoint) listMathPtCurrent;

			CATIPLMNavRepInstance_var spRepInst = listAllRepInst[i];
			if (spRepInst == NULL_var)
			{
				CoutMsg("spRepInst == NULL_var");
				continue;
			}

			rc = this->GetAllDittoPt(spRepInst, listLegendIDCurrent, listMathPtCurrent);
			if (FAILED(rc) || listLegendIDCurrent.Size() == 0)
			{
				continue;
			}

			listLegendID.Append(listLegendIDCurrent);
			listMathPt.Append(listMathPtCurrent);
			listLegendIDCurrent.RemoveAll();
			listMathPtCurrent.RemoveAll();
		}

		//3，在当前View中创建Ditto
		rc = this->CreateDittoInView(spDftSectionView, 1, listLegendID, listMathPt);

		listLegendID.RemoveAll();
		listMathPt.RemoveAll();
		listAllRepInst.RemoveAll();
	}

	this->RequestDelayedDestruction();

	return TRUE;
}

//取消
CATBoolean  SJDInsertEquipmentDittoCmd::ActionCancel(CATCommand* iPublishingCommand, CATNotification * iNotification, CATCommandClientData iData)
{
	std::cout << __FUNCTION__ << " start" << std::endl;

	this->RequestDelayedDestruction();

	return TRUE;
}

//选择框选择
CATBoolean  SJDInsertEquipmentDittoCmd::ActionSelectorListSelect(CATCommand* iPublishingCommand, CATNotification * iNotification, CATCommandClientData iData)
{
	_iCurrentSLIndex = (SelectorListType)CATPtrToINT32(iData);

	//清除所有sl的选择状态，设置当前选择
	_pDlg->GetSelectorList(SL_TopView)->ClearSelect();
	_pDlg->GetSelectorList(SL_SectionView)->ClearSelect();

	//选择第一行
	int iLine = 0;
	_pDlg->GetSelectorList(_iCurrentSLIndex)->SetSelect(&iLine, 1, 0);

	HighLightSelectObject();

	return TRUE;
}

//选择点
CATBoolean SJDInsertEquipmentDittoCmd::ActionElementSelected(void * iData)
{
	//CATPathElementAgent * pCurrentAgent = (CATPathElementAgent*)iData;
	_pHSO->Empty();

	CATBaseUnknown * pSelection = _pViewAgent->GetElementValue();

	_pViewAgent->InitializeAcquisition();

	CATIAlias_var  spiAlias = pSelection;
	CATUnicodeString strAlias;
	if (!!spiAlias)
		strAlias = spiAlias->GetAlias();
	else
		return FALSE;

	if (_iCurrentSLIndex == SL_TopView)
	{
		_spBaseTopView = pSelection;
	}
	else if (_iCurrentSLIndex == SL_SectionView)
	{
		_spBaseSectionView = pSelection;
	}

	_pDlg->GetSelectorList(_iCurrentSLIndex)->SetLine(strAlias, 0, CATDlgDataModify);

	this->HighLightSelectObject();
	this->CheckOKSensitivity();

	return TRUE;
}

//高亮
void SJDInsertEquipmentDittoCmd::HighLightSelectObject()
{
	_pHSO->Empty();

	switch (_iCurrentSLIndex)
	{
	case SL_TopView:
		UpdateHSO(_spBaseTopView, _pHSO, _pEditor);
		break;
	case SL_SectionView:
		UpdateHSO(_spBaseSectionView, _pHSO, _pEditor);
	}
}

//高亮
void SJDInsertEquipmentDittoCmd::UpdateHSO(CATBaseUnknown_var ispiBUObj, CATHSO * pHSO, CATFrmEditor * pEditor)
{
	HRESULT rc;

	if (ispiBUObj != NULL_var)
	{
		CATIBuildPath *pBuildPath = NULL;
		rc = ispiBUObj->QueryInterface(IID_CATIBuildPath, (void**)&pBuildPath);
		if (SUCCEEDED(rc) && pBuildPath != NULL)
		{
			CATPathElement context = pEditor->GetUIActiveObject();
			CATPathElement *pPathElement = NULL;
			rc = pBuildPath->ExtractPathElement(&context, &pPathElement);

			if (pPathElement != NULL)
			{   // the geometrical element corresponding to the active field is now highlighted
				pHSO->AddElement(pPathElement);
				pPathElement->Release();
				pPathElement = NULL;
			}
			pBuildPath->Release();
			pBuildPath = NULL;
		}
	}
}

//获得Catalog下Ditto信息
HRESULT SJDInsertEquipmentDittoCmd::GetCatalogDittoInfo()
{
	HRESULT hr = S_OK;

	//=========================================================================
	//1, 搜索catalog
	CATIAdpPLMIdentificator_var spiPLMIdentification = NULL_var;
	SJDCHIGeneralServices::GetCatalogFromName(_strCatalogName, spiPLMIdentification);
	if (spiPLMIdentification == NULL_var)
	{
		CoutMsg("获得catalog失败，请检查配置文件！");
		return FALSE;
	}

	//2，打开catalog			
	PLMICLGLibrary * piLibrary = NULL;
	CATOmbLifeCycleRootsBag bag;
	PLMCLGPublicLibraryNavServices::GetLibrary(spiPLMIdentification, piLibrary, bag);
	if (NULL == piLibrary)
	{
		CoutMsg("获得catalog失败，请检查配置文件！");
		return FALSE;
	}

	//3，获得chapter下对象列表
	//详图章节 
	//SHIY 修改 - 输入值_strChapterPartName改为_strChapterDittoName
	//SJDCHIGeneralServices::GetChapterItemsInCatalog(piLibrary, _strChapterPartName, _spBUDittoChapterItemList, _strDittoChapterItemNameList);
	SJDCHIGeneralServices::GetChapterItemsInCatalog(piLibrary, _strChapterDittoName, _spBUDittoChapterItemList, _strDittoChapterItemNameList);

	_bReadCatalog = TRUE;

	return hr;
}

//获取视图关联的所有Ref
HRESULT SJDInsertEquipmentDittoCmd::GetAllLinkRefOfView(CATIDftView_var ispDftView, CATListValCATBaseUnknown_var & listAllRepOcc)
{
	HRESULT rc = S_OK;

	//1获得投影视图里面所有的元素
	IUnknown* pUnknown = NULL;
	ispDftView->GetApplicativeExtension(IID_CATIDftGenGeomAccess, &pUnknown);
	if (pUnknown == NULL)
	{
		CoutMsg("pUnknown == NULL");
		return E_FAIL;
	}

	CATIDftGenGeomAccess* piGeomAccess = NULL;
	rc = pUnknown->QueryInterface(IID_CATIDftGenGeomAccess, (void**)&piGeomAccess);
	pUnknown->Release(); pUnknown = NULL;
	if (FAILED(rc) || piGeomAccess == NULL)
	{
		CoutMsg("piGeomAccess == NULL");
		return E_FAIL;
	}

	CATIUnknownList* olistElementInView = NULL;
	piGeomAccess->GetAllGeneratedItems(IID_CATIDftGenGeom, &olistElementInView);
	if (olistElementInView == NULL)
	{
		CoutMsg("olistElementInView == NULL");
		return E_FAIL;
	}

	unsigned int iSizeOfAllElem = 0;
	olistElementInView->Count(&iSizeOfAllElem);

	//2获取所有OIC
	CATLISTP(CATOmbObjectInContext) listOICOnIns;
	for (unsigned int i = 0; i < iSizeOfAllElem; i++)
	{
		IUnknown* piUnknownTemp = NULL;
		olistElementInView->Item(i, &piUnknownTemp);
		if (piUnknownTemp == NULL)
		{
			continue;
		}

		CATIDftGenGeom_var spGenGeom = NULL_var;
		piUnknownTemp->QueryInterface(IID_CATIDftGenGeom, (void**)&spGenGeom);
		if (NULL_var == spGenGeom)	continue;

		CATOmbObjectInContext*  piRepInstanceContext = NULL;
		spGenGeom->GetRepInstance(&piRepInstanceContext);
		if (piRepInstanceContext == NULL)	continue;


		if (listOICOnIns.Locate(piRepInstanceContext) == 0)
		{
			listOICOnIns.Append(piRepInstanceContext);
		}
	}

	//3获取每个OIC对应的Ref
	CATOmbObjectInContext * piOmbObjectInContext = NULL;
	int iSizeOfOIC = listOICOnIns.Size();
	for (int i = 1; i <= iSizeOfOIC; i++)
	{
		piOmbObjectInContext = listOICOnIns[i];

		//暂定场景为part下放二维图纸，不考虑多层级或有装配坐标变换的场景
		CATIPLMComponent * piRepresentationInstance = NULL;
		if (SUCCEEDED(piOmbObjectInContext->GetInstanceOfRepresentation(piRepresentationInstance)) && piRepresentationInstance)
		{
			CATIAlias_var spAlias = piRepresentationInstance;
			if (NULL_var != spAlias)
			{
				CATUnicodeString usAlias = spAlias->GetAlias();
				printf(" piRepresentationInstance =%s\n", usAlias.ConvertToChar());
			}

			CATIPLMNavRepInstance_var spRepInstance = piRepresentationInstance;

			piRepresentationInstance->Release();
			piRepresentationInstance = NULL;


			listAllRepOcc.Append(spRepInstance);
		}
	}

	return S_OK;
}

//判断OK按钮是否可用
void SJDInsertEquipmentDittoCmd::CheckOKSensitivity()
{
	if (_spBaseTopView == NULL_var && _spBaseSectionView == NULL_var)
		_pDlg->SetOKSensitivity(CATDlgDisable);
	else
		_pDlg->SetOKSensitivity(CATDlgEnable);
}

//获得当前参考下的所有三维点
HRESULT SJDInsertEquipmentDittoCmd::GetAllDittoPt(CATIPLMNavRepInstance_var ispRepInst, CATListOfInt & oListLegendID, CATLISTV(CATMathPoint) & oListMathPt)
{
	HRESULT rc = S_OK;

	CATIPLMNavRepReference * piRepReference = NULL;
	ispRepInst->GetRepReferenceInstanceOf(piRepReference);
	if (piRepReference == NULL)
	{
		CoutMsg("piRepReference == NULL");
		return E_FAIL;
	}

	//获得RepReference下的所有点对象
	CATIPsiRepresentationLoadMode *piRepLoadMode = NULL;
	rc = piRepReference->QueryInterface(IID_CATIPsiRepresentationLoadMode, (void **)&piRepLoadMode);
	if (SUCCEEDED(rc) && NULL != piRepLoadMode)
	{
		rc = piRepLoadMode->ChangeLoadingMode(CATIPsiRepresentationLoadMode::EditMode);
		piRepLoadMode->Release();
		piRepLoadMode = NULL;
	}
	else
	{
		CoutMsg("Failed ChangeLoadingMode: EditMode");
		return E_FAIL;
	}

	//Retrieve the applicative container
	CATIMmiPrtContainer * pContainer = NULL;
	rc = piRepReference->RetrieveApplicativeContainer("CATPrtCont", IID_CATIMmiPrtContainer, (void **)&pContainer);
	if (FAILED(rc) || pContainer == NULL)
	{
		CoutMsg("Failed RetriveApplicativeContainer!");
		return E_FAIL;
	}

	CATIMmiMechanicalFeature_var spMechFeatOnPart = NULL_var;
	rc = pContainer->GetMechanicalPart(spMechFeatOnPart);
	pContainer->Release();	pContainer = NULL;
	if (FAILED(rc) || spMechFeatOnPart == NULL_var)
	{
		CoutMsg("FAILED to Get Mechanical Part.");
		return E_FAIL;
	}

	CATIPartRequest_var spPartRequestOnPart = spMechFeatOnPart;
	if (NULL_var == spPartRequestOnPart)
	{
		CoutMsg("spPartRequestOnPart==NULL_var");
		return E_FAIL;
	}

	//查找指定名称的几何集，看是否存在
	CATIAlias_var spAlias = NULL_var;
	CATListValCATBaseUnknown_var  oAllGsBodies;
	spPartRequestOnPart->GetAllBodies(" ", oAllGsBodies);
	if (oAllGsBodies != NULL && oAllGsBodies.Size() > 0)
	{
		for (int iBodyNum = 1; iBodyNum <= oAllGsBodies.Size(); iBodyNum++)
		{
			spAlias = oAllGsBodies[iBodyNum];
			CATUnicodeString gsmToolName = spAlias->GetAlias();
			std::cout << gsmToolName << std::endl;

			CATIGSMTool * piGSMTool = NULL;
			rc = oAllGsBodies[iBodyNum]->QueryInterface(IID_CATIGSMTool, (void**)&piGSMTool);
			if (FAILED(rc) || piGSMTool == NULL)
			{
				std::cout << "Failed QI piGSMTool" << std::endl;
				continue;
			}

			CATIGSMTool_var spiGSMTool = piGSMTool;
			piGSMTool->Release();
			piGSMTool = NULL;

			CATIBodyRequest_var spiSetRequest = spiGSMTool;

			CATListValCATBaseUnknown_var listGeoElements;
			rc = spiSetRequest->GetResults("", listGeoElements);
			if (FAILED(rc))
			{
				CoutMsg("Failed GetResults: listGeoElements");
				continue;
			}

			SJDICHIDIInvestDesignLegend * piInvestDesignLegend = NULL;
			for (int iGeoEleNum = 1; iGeoEleNum <= listGeoElements.Size(); iGeoEleNum++)
			{
				piInvestDesignLegend = NULL;
				rc = listGeoElements[iGeoEleNum]->QueryInterface(IID_SJDICHIDIInvestDesignLegend, (void**)&piInvestDesignLegend);
				if (FAILED(rc) || piInvestDesignLegend == NULL)
				{
					continue;
				}

				int iLegendID;
				CATMathPoint mathPtLegend;
				rc = this->GetLegendInfo(piInvestDesignLegend, iLegendID, mathPtLegend);
				if (SUCCEEDED(rc))
				{
					spAlias = piInvestDesignLegend;
					std::cout << spAlias->GetAlias() << std::endl;
					oListLegendID.Append(iLegendID);
					oListMathPt.Append(mathPtLegend);
				}
			}
		}
	}

	return rc;
}

//获得Legend类型和坐标
HRESULT SJDInsertEquipmentDittoCmd::GetLegendInfo(SJDICHIDIInvestDesignLegend * ipiLegend, int & oLegendID, CATMathPoint & oMathPt)
{
	HRESULT rc = S_OK;

	ipiLegend->GetLegendID(oLegendID);

	//获得创建方式
	LegendCreateMethod eLegendCreateMethod;
	ipiLegend->GetCreateMethod(eLegendCreateMethod);
	if (eLegendCreateMethod == LegendReferencePt)
	{
		//获得定位点
		CATBaseUnknown_var spBaseRefPt = NULL_var;
		rc = ipiLegend->GetLegendRefPt(spBaseRefPt);
		if (FAILED(rc) || spBaseRefPt == NULL_var)
		{
			CoutMsg("FAILED GetLegendRefPt");
			return NULL;
		}

		if (!!spBaseRefPt)
		{
			CATPoint * piPoint = NULL;
			rc = spBaseRefPt->QueryInterface(IID_CATPoint, (void **)&piPoint);
			if (SUCCEEDED(rc) && !!piPoint) {
				piPoint->GetMathPoint(oMathPt);

				piPoint->Release();  piPoint = NULL;
			}
			else
				return E_FAIL;
		}
	}
	else if (eLegendCreateMethod == LegendCoordParm)
	{
		//获得点坐标：X
		CATBaseUnknown_var spBaseParmX = NULL_var;
		rc = ipiLegend->GetParamCoordX(spBaseParmX);
		CATICkeParm_var spParmX = spBaseParmX;
		if (FAILED(rc) || spParmX == NULL_var)
		{
			CoutMsg("FAILED GetParamCoordX");
			return E_FAIL;
		}

		//获得点坐标：Y
		CATBaseUnknown_var spBaseParmY = NULL_var;
		rc = ipiLegend->GetParamCoordY(spBaseParmY);
		CATICkeParm_var spParmY = spBaseParmY;
		if (FAILED(rc) || spParmY == NULL_var)
		{
			CoutMsg("FAILED GetParamCoordY");
			return E_FAIL;
		}

		//获得点坐标：Z
		CATBaseUnknown_var spBaseParmZ = NULL_var;
		rc = ipiLegend->GetParamCoordZ(spBaseParmZ);
		CATICkeParm_var spParmZ = spBaseParmZ;
		if (FAILED(rc) || spParmZ == NULL_var)
		{
			CoutMsg("FAILED GetParamCoordZ");
			return E_FAIL;
		}

		double xCoord = 1000.*spParmX->Value()->AsReal();
		double yCoord = 1000.*spParmY->Value()->AsReal();
		double zCoord = 1000.*spParmZ->Value()->AsReal();

		oMathPt.SetCoord(xCoord, yCoord, zCoord);
	}

	return S_OK;
}

//在View中创建Ditto
HRESULT SJDInsertEquipmentDittoCmd::CreateDittoInView(CATIDftView_var ispDftView, int iViewType, CATListOfInt iListLegendID, CATLISTV(CATMathPoint) iListMathPt)
{
	HRESULT hr = S_OK;
	cout << "CreateDittoInView" << endl;

	
	CATUnicodeString strViewType = "";

	if (iViewType == 0)
		strViewType = "俯视图";
	else if (iViewType == 1)
		strViewType = "剖视图";	
	
	CATUnicodeString strDittoName;
	int iLocation;
	CATMathPoint mathPtCurrent;
	CATBaseUnknown_var spBUOnDitto = NULL_var;
	for (int iNum = 1; iNum <= iListLegendID.Size(); iNum++)
	{
		//获得Ditto名称
		strDittoName = "";
		strDittoName = this->getDittoName(strViewType, iListLegendID[iNum]); 

		//获取对应的Ditto
		iLocation = _strDittoChapterItemNameList.Locate(strDittoName);//namelist 是从catalog里面得出  -1
		if (iLocation > 0)
		{
			//当前三维坐标
			//SHIY 修改 - iLocation 改 iNum
			mathPtCurrent = iListMathPt[iNum];//pt 位置是从对象模型中得出 -2

			// -1 -2 问题：如果catalog中图例个数不等于对象模型中图例个数

			//SHIY 添加
			//需要根据名称从catalog中找到view对象
			spBUOnDitto = _spBUDittoChapterItemList[iLocation];
			CATIDftView_var spiDftDetailView = spBUOnDitto;
			if (!spiDftDetailView)
			{
				cout << "error detail" << endl;
				break;
			}

			//三维坐标转二维
			double d2DPoint[2] = {0.,0.};
			Transform3DPtTo2D(ispDftView, mathPtCurrent, d2DPoint);
			cout << "(" << d2DPoint[0] << "," << d2DPoint[1] << ")"<<endl;

			//当前View中创建Ditto
			CATIDftView_var spiNewDftDittoView = NULL_var;
			if (FAILED(CreateDitto(ispDftView, spiDftDetailView, d2DPoint, spiNewDftDittoView))||!spiNewDftDittoView)
			{
				cout << "error" << endl;
				continue;
			}

			//添加后期可以查找的标识符
			
			/*CATListValCATBaseUnknown_var listvBUObject;
			GetAllLinkRefOfView(spiNewDftDittoView, listvBUObject);
			if (listvBUObject.Size() != 0)
			{
				CATIPLMNavRepInstance_var spRepInst = listvBUObject[1];
				if (!!spRepInst)
				{
					CATICkeObject_var spiCkeObject = spRepInst;
					if (!!spiCkeObject)
					{
						cout << "yes" << endl;
						AddDeleteId(spiCkeObject);
						PrintAttrs(spiCkeObject);
					}
				}

			}*/
			
			//SHIY END
		
		}
	}

	return hr;
}

//获得当前对象对应的catalog ditto名称
CATUnicodeString SJDInsertEquipmentDittoCmd::getDittoName(CATUnicodeString istrViewType, int iLegendID)
{
	CATUnicodeString strDittoName;
	CATUnicodeString strTemp;
	int iId;
	for (int i = 1; i <= _viewInfo.strListViewName.Size(); i++)
	{
		strTemp = _viewInfo.strListID[i];
		strTemp.ConvertToNum(&iId, "%d");
		if (istrViewType == _viewInfo.strListViewName[i] && iLegendID == iId)
		{
			strDittoName = _viewInfo.strListDittoName[i];
			break;
		}
	}

	return strDittoName;
}

//SHIY Add
//三维点转化二维点
HRESULT SJDInsertEquipmentDittoCmd::Transform3DPtTo2D(CATIDftView_var ispiDftView,
													  CATMathPoint  i3DPositin,
													  double* op2DPt)
{
	HRESULT hr = S_OK;
	if (!ispiDftView)
	{
		return E_FAIL;
	}

	CATIDftGenerSpec* piDftGenerSpec = NULL;
	if (FAILED(ispiDftView->GetGenerSpec(&piDftGenerSpec)) || !piDftGenerSpec)
	{
		return E_FAIL;
	}

	CATMathPlane* mathPrjPlane = NULL;
	piDftGenerSpec->GetProjectionPlane(&mathPrjPlane);
	mathPrjPlane->Project(i3DPositin, op2DPt[0], op2DPt[1]);

	return S_OK;
}
//创建Ditto
HRESULT SJDInsertEquipmentDittoCmd::CreateDitto(CATIDftView_var ispDftView, 
												CATIDftView_var ispiDftDetailView,
												double* ip2DPt,
												CATIDftView_var& ospiNewDftDittoView)
{
	if (!ispDftView || !ispiDftDetailView)
	{
		return E_FAIL;
	}
	HRESULT hr = S_OK;
	ospiNewDftDittoView = NULL;
	CATIADrawingView* piANewDftDittoView = NULL;
	//CATIADrawingView* piANewRefDftDittoView = NULL;
	CATIADrawingView* piADftDitto = NULL;
	if ((FAILED(ispiDftDetailView->QueryInterface(IID_CATIADrawingView, (void**)&piADftDitto)) || !piADftDitto))
	{
		cout << "	Error : CATIADrawingView is NULL ! " << endl;
		return E_FAIL;
	}

	CATIADrawingView_var spiADrawingVIew = ispDftView;
	if (spiADrawingVIew != NULL_var)
	{
		CATIADrawingComponents* piDrawingComponent = NULL;
		if (SUCCEEDED(spiADrawingVIew->get_Components(piDrawingComponent)))
		{
			CATIADrawingComponent* piAOComponent = NULL;
			if (SUCCEEDED(piDrawingComponent->Add(piADftDitto, ip2DPt[0], ip2DPt[1], piAOComponent)) && piAOComponent)
			{
				//test
				//1
				CATIDftDitto_var spiDftDitto = piAOComponent;
				if (!!spiDftDitto)
				{

					CATIAlias_var spiAlias = spiDftDitto;
					if (!!spiAlias)
					{
						cout << spiAlias->GetAlias() << endl;

						spiAlias->SetAlias("111");
					}
					//PrintAttrs(spiDftDitto);
					//IUnknown* pUnknown = NULL;
					//spiDftDitto->GetDetail(IID_CATIPLMNavRepInstance, &pUnknown);
					//if (pUnknown)
					//{
					//	//CATIPLMNavRepReference CATIPLMNavInstance
					//	CATIPLMNavRepReference* piRepRef = NULL;
					//	CATIPLMNavRepInstance* piRepInst =NULL;
					//	if (SUCCEEDED(pUnknown->QueryInterface(IID_CATIPLMNavRepInstance, (void**)&piRepInst)) && piRepRef)
					//	{
					//		cout << "111" << endl;
					//	}
					//	
					//}
					
				}
				//2
				CATIPLMComponent_var spiPLMComponent = piAOComponent;
				if (!!spiPLMComponent)
				{
					CATIAdpType* piAdpType = NULL;
					spiPLMComponent->GetAdpType(piAdpType);

					if (piAdpType)
					{
						CATUnicodeString ustrTypeName;
						piAdpType->GetAlias(ustrTypeName);
						cout << ustrTypeName << endl;

						CATIType * TypeKnowledgeOfComp = NULL;
						hr = CATPLMTypeServices::GetKweTypeFromAdpType(piAdpType, TypeKnowledgeOfComp);
						cout << TypeKnowledgeOfComp->Name() << endl;

					}
					
				}

				


				/*CATIDftSheet* piDftSheet = NULL;
				ispDftView->GetSheet(&piDftSheet);
				if (piDftSheet)
				{
					CATIADrawingSheet* piADrawingSheet = NULL;

					if (SUCCEEDED(piDftSheet->QueryInterface(IID_CATIADrawingSheet, (void**)&piADrawingSheet)) && piADrawingSheet)
					{
						piAOComponent->ExposeCompRefInSheet(piADrawingSheet);
					}
				}*/
				//
				if (SUCCEEDED(piAOComponent->get_CompRef(piANewDftDittoView)) && piANewDftDittoView)
				{
					ospiNewDftDittoView = piANewDftDittoView;
					/*if (SUCCEEDED(piANewDftDittoView->get_ReferenceView(piANewRefDftDittoView)) && piANewRefDftDittoView)
					{
						ospiNewDftDittoView = piANewRefDftDittoView;

						piANewRefDftDittoView->Release();
						piANewRefDftDittoView = NULL;
					}*/

					piANewDftDittoView->Release();
					piANewDftDittoView = NULL;
				}
				

				piAOComponent->Release(); 
				piAOComponent = NULL;
			}
			else {
				hr = E_FAIL;
				cout << "	Error : Add Failed ! " << endl;
				
			}
		}
		else {
			hr = E_FAIL;
			cout << "	Error : get_Components Failed ! " << endl;
			
		}
	}
	else {
		hr = E_FAIL;
		cout << "	Error : CATIADrawingView is NULL ! " << endl;
		
	}

	CATIModelEvents_var spiEvent(ispDftView);
	if (!!spiEvent)
	{
		CATModify info((CATBaseUnknown *)ispDftView);
		spiEvent->Dispatch(info);
	}

	return hr;
}

//添加删除属性MadeInSJD
HRESULT SJDInsertEquipmentDittoCmd::AddDeleteId(CATICkeObject_var ispiCkeObject)
{
	if (!ispiCkeObject)
	{
		return E_FAIL;
	}
	//先获取原有，再添加标识符
	CATUnicodeString ustrValue;
	CATCkeObjectAttrReadServices::GetValueAsString(ispiCkeObject, "V_description", ustrValue);
	if (ustrValue.SearchSubString("MadeInSJD") == -1)
	{
		CATCkeObjectAttrWriteServices::SetValueWithString(ispiCkeObject, "V_description", "MadeInSJD");
	}
	
	return S_OK;
}

HRESULT SJDInsertEquipmentDittoCmd::PrintAttrs(CATICkeObject_var ispiCkeObject)
{
	HRESULT hr = S_OK;
	//类型
	CATUnicodeString ustrPLMType = "Drawing";
	CATUnicodeString strNLSName;
	CATIType_var spCATType;
	hr = CATCkePLMNavPublicServices::RetrieveKnowledgeType(ustrPLMType, spCATType);
	if (NULL_var == spCATType)
	{
		hr = CATCkePLMNavCustoAccessPublicServices::RetrieveCustoType(ustrPLMType, spCATType);
	}
	//创建
	CATUnicodeString ustrUserAttr = "MadeInSJD";
	CATUnicodeString ustrUserValue = "123";
	CATIValue_var spiValue = NULL_var;
	CATCkeObjectAttrWriteServices::CreateValueFromString(spCATType, ustrUserAttr, ustrUserValue, spiValue);
	//1-
	CATListValCATAttributeInfos ListOfAttributes;
	hr = CATCkePLMNavPublicServices::ListAttributesFromObject(CATCkePLMTypeAttrServices::All,ispiCkeObject,ListOfAttributes);

	for (int i = 1;i<=ListOfAttributes.Size();i++)
	{
		cout << "attr name 1= " << ListOfAttributes[i].Name() << endl;
	}

	//1-1
	ListOfAttributes.RemoveAll();
	CATCkePLMNavPublicServices::ListAttributesFromType(CATCkePLMTypeAttrServices::All, spCATType, NULL, ListOfAttributes);
	for (int i = 1; i <= ListOfAttributes.Size(); i++)
	{
		cout << "ListAttributesFromType 1= " << ListOfAttributes[i].Name() << endl;
	}

	//2-
	CATUnicodeString ustrValue;
	CATCkeObjectAttrReadServices::GetValueAsString(ispiCkeObject,"MadeInSJD",ustrValue);

	cout << "ustrValue = " << ustrValue << endl;

	//3-
	//ListOfAttributes.RemoveAll();
	//CAAAdpRetrieveListOfFilteredAttributesFromMask(ListOfAttributes, "MaskCreate", spCATType);
	//for (int i = 1; i <= ListOfAttributes.Size(); i++)
	//{
	//	cout << "MaskCreate= " << ListOfAttributes[i].Name() << endl;
	//	CATICkeParm_var spCkeParmWithDefaultValue;
	//	hr = ListOfAttributes[i].GetDefaultValue(spCkeParmWithDefaultValue);
	//	if (SUCCEEDED(hr))
	//	{
	//		CATICkeInst_var spiCkeInst = spCkeParmWithDefaultValue->Value();
	//		if (!!spiCkeInst)
	//		{
	//			cout << "Value = " << spiCkeInst->AsString() << endl;
	//		}	
	//	}
	//}
	//ListOfAttributes.RemoveAll();
	//CAAAdpRetrieveListOfFilteredAttributesFromMask(ListOfAttributes, "MaskWrite", spCATType);
	//for (int i = 1; i <= ListOfAttributes.Size(); i++)
	//{
	//	cout << "MaskWrite= " << ListOfAttributes[i].Name() << endl;
	//	CATICkeParm_var spCkeParmWithDefaultValue;
	//	hr = ListOfAttributes[i].GetDefaultValue(spCkeParmWithDefaultValue);
	//	if (SUCCEEDED(hr))
	//	{
	//		CATICkeInst_var spiCkeInst = spCkeParmWithDefaultValue->Value();
	//		if (!!spiCkeInst)
	//		{
	//			cout << "Value = " << spiCkeInst->AsString() << endl;
	//		}
	//	}
	//}
	//ListOfAttributes.RemoveAll();
	//CAAAdpRetrieveListOfFilteredAttributesFromMask(ListOfAttributes, "MaskQuery", spCATType);
	//for (int i = 1; i <= ListOfAttributes.Size(); i++)
	//{
	//	cout << "MaskQuery= " << ListOfAttributes[i].Name() << endl;
	//	CATICkeParm_var spCkeParmWithDefaultValue;
	//	hr = ListOfAttributes[i].GetDefaultValue(spCkeParmWithDefaultValue);
	//	if (SUCCEEDED(hr))
	//	{
	//		CATICkeInst_var spiCkeInst = spCkeParmWithDefaultValue->Value();
	//		if (!!spiCkeInst)
	//		{
	//			cout << "Value = " << spiCkeInst->AsString() << endl;
	//		}
	//	}
	//}
	//ListOfAttributes.RemoveAll();
	//CAAAdpRetrieveListOfFilteredAttributesFromMask(ListOfAttributes, "MaskEZQuery", spCATType);
	//for (int i = 1; i <= ListOfAttributes.Size(); i++)
	//{
	//	cout << "MaskEZQuery= " << ListOfAttributes[i].Name() << endl;
	//	CATICkeParm_var spCkeParmWithDefaultValue;
	//	hr = ListOfAttributes[i].GetDefaultValue(spCkeParmWithDefaultValue);
	//	if (SUCCEEDED(hr))
	//	{
	//		CATICkeInst_var spiCkeInst = spCkeParmWithDefaultValue->Value();
	//		if (!!spiCkeInst)
	//		{
	//			cout << "Value = " << spiCkeInst->AsString() << endl;
	//		}
	//	}
	//}
	//ListOfAttributes.RemoveAll();
	//CAAAdpRetrieveListOfFilteredAttributesFromMask(ListOfAttributes, "MaskRead", spCATType);
	//for (int i = 1; i <= ListOfAttributes.Size(); i++)
	//{
	//	cout << "MaskRead= " << ListOfAttributes[i].Name() << endl;
	//	CATICkeParm_var spCkeParmWithDefaultValue;
	//	hr = ListOfAttributes[i].GetDefaultValue(spCkeParmWithDefaultValue);
	//	if (SUCCEEDED(hr))
	//	{
	//		CATICkeInst_var spiCkeInst = spCkeParmWithDefaultValue->Value();
	//		if (!!spiCkeInst)
	//		{
	//			cout << "Value = " << spiCkeInst->AsString() << endl;
	//		}
	//	}
	//}
	//ListOfAttributes.RemoveAll();
	//CAAAdpRetrieveListOfFilteredAttributesFromMask(ListOfAttributes, "MaskTree", spCATType);
	//for (int i = 1; i <= ListOfAttributes.Size(); i++)
	//{
	//	cout << "MaskTree= " << ListOfAttributes[i].Name() << endl;
	//	CATICkeParm_var spCkeParmWithDefaultValue;
	//	hr = ListOfAttributes[i].GetDefaultValue(spCkeParmWithDefaultValue);
	//	if (SUCCEEDED(hr))
	//	{
	//		CATICkeInst_var spiCkeInst = spCkeParmWithDefaultValue->Value();
	//		if (!!spiCkeInst)
	//		{
	//			cout << "Value = " << spiCkeInst->AsString() << endl;
	//		}
	//	}
	//}
	////4-
	//ListOfAttributes.RemoveAll();
	//hr = CATCkePLMNavCustoAccessPublicServices::ListAttributesFromCustoType(CATCkePLMTypeAttrServices::All,spCATType,ListOfAttributes, FALSE);
	//for (int i = 1; i <= ListOfAttributes.Size(); i++)
	//{
	//	cout << "ListAttributesFromCustoType 1= " << ListOfAttributes[i].Name() << endl;
	//}
	//5-
	CATTime CurrentValueTime;
	hr = CATCkeObjectAttrReadServices::GetValueAsTime(ispiCkeObject, "V_ApplicabilityDate", CurrentValueTime);
	CATUnicodeString strCurrentTime = CurrentValueTime.ConvertToString("%d %B %Y %H:%M:%S.");
	cout << " V_ApplicabilityDate  " << " attribute Current value  " << strCurrentTime.ConvertToChar() << endl;

	//6-
	CATICkeParmFactory_var parmFactory = ispiCkeObject;
	if (!!parmFactory)
	{
		cout << "yes QI" << endl;
	}

	
	return S_OK;
}

HRESULT SJDInsertEquipmentDittoCmd::CAAAdpRetrieveListOfFilteredAttributesFromMask(CATListValCATAttributeInfos &oListOfAttrInfo,
														 CATUnicodeString strMaskType,
														 const CATIType_var& iKweType)
{
	HRESULT hr = E_FAIL;

	cout << "   CAAAdpMaskedFilteredAttributesValueEditorDlg::RetrieveOfListFilteredAttributesFromMask" << endl;

	if (0 == strcmp("MaskCreate", strMaskType))
	{
		hr = CATCkePLMNavPublicServices::ListFilteredAttributesFromMaskAndType(iKweType, NULL,
			CATCkePLMTypeAttrServices::MaskCreate,
			oListOfAttrInfo);
	}
	else if (0 == strcmp("MaskWrite", strMaskType))
	{
		hr = CATCkePLMNavPublicServices::ListFilteredAttributesFromMaskAndType(iKweType, NULL,
			CATCkePLMTypeAttrServices::MaskWrite,
			oListOfAttrInfo);
	}
	else if (0 == strcmp("MaskQuery", strMaskType))
	{
		hr = CATCkePLMNavPublicServices::ListFilteredAttributesFromMaskAndType(iKweType, NULL,
			CATCkePLMTypeAttrServices::MaskQuery,
			oListOfAttrInfo);
	}
	else if (0 == strcmp("MaskEZQuery", strMaskType))
	{
		hr = CATCkePLMNavPublicServices::ListFilteredAttributesFromMaskAndType(iKweType, NULL,
			CATCkePLMTypeAttrServices::MaskEZQuery,
			oListOfAttrInfo);
	}
	else if (0 == strcmp("MaskRead", strMaskType))
	{
		hr = CATCkePLMNavPublicServices::ListFilteredAttributesFromMaskAndType(iKweType, NULL,
			CATCkePLMTypeAttrServices::MaskRead,
			oListOfAttrInfo);
	}
	else if (0 == strcmp("MaskTree", strMaskType))
	{
		hr = CATCkePLMNavPublicServices::ListFilteredAttributesFromMaskAndType(iKweType, NULL,
			CATCkePLMTypeAttrServices::MaskTree,
			oListOfAttrInfo);
	}

	return hr;
}
//
//删除对象
HRESULT SJDInsertEquipmentDittoCmd::DeleteObj(CATIDftView_var ispDftView)
{
	if (!ispDftView)
	{
		return E_FAIL;
	}
	CATIUseEntity* piAECClothoidEntity = NULL;
	if (FAILED(ispDftView->QueryInterface(IID_CATIUseEntity, (void**)&piAECClothoidEntity)) || !piAECClothoidEntity)
	{
		return E_FAIL;
	}
	DataCommonProtocolServices::Delete(piAECClothoidEntity);//Delete Import Feature
	piAECClothoidEntity->Release();
	piAECClothoidEntity = NULL;
	DataCommonProtocolServices::Update(piAECClothoidEntity);

	return S_OK;
}

