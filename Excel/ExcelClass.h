// COPYRIGHT Dassault Systemes 2014
//===================================================================
//
// ExcelClass.h
// Header definition of ExcelClass
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
//  Apr 2014  Creation: Code generated by the CAA wizard  ZhangYong
//===================================================================
#ifndef ExcelClass_H
#define ExcelClass_H

#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"
#include "excel.h"
//#include "StdAfx.h"
#include "comdef.h"
#include "comutil.h"
#include "io.h"
#include "iostream.h"

#include <cstring>
#include <cstringt.h>

#include "CAxis.h"
#include "CAxisTitle.h"

#include "CATListOfCATUnicodeString.h"


#undef DeleteObject
//#include <afxwin.h>         // MFC core and standard components
//#include <afxext.h>         // MFC extensions

#ifdef _WINDOWS_
#undef  _WINDOWS_ 
#endif
#include <afxdisp.h>   

//-----------------------------------------------------------------------

/**
* Class representing xxx.
*
* <br><b>Role</b>: Provide the basic class function...
* <p>
* Do not use the @href ExcelClass constructor to
* do such and such but instead...
*
* @example
*  // example is optional
*  pObject = new ExcelClass;
*  pObject->SetXXX(...);
*
* @href ClassReference, Class#MethodReference, #InternalMethod...
*/
class ExcelClass: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors
  // -------------------------------------
     ExcelClass (/*CATUnicodeString fileFullPath*/);
     virtual ~ExcelClass ();

  // Copy constructor and equal operator
  // -----------------------------------
  ExcelClass (ExcelClass &);
  ExcelClass& operator=(ExcelClass&);

private:
  Range m_ExlRge; 

  _Worksheet m_ExlSheet; 
  Worksheets m_ExlSheets; 

  _Workbook m_ExlBook; 
  Workbooks m_ExlBooks; 

  _Application m_ExlApp;

/*  Pictures pt;*/

//   CellFormat cf; 
//   Font ft; 
  
  int iSheetIndex;

private:
	CATBoolean bSheet;

public:

	//创建excel文件
	CATBoolean CreateExcel();
	//打开excel文件
	CATBoolean OpenExcel(CATUnicodeString ExcelPath);
	//创建sheet
	void CreateSheet(CATUnicodeString sSheetName);
	//Copy sheet    拷贝模板  
	void CopySheet(int sheetIndex);
	//Delete sheet    删除sheet  
	void DeleteSheet(int sheetIndex);
	//执行宏命令
	void RunMacro(CATUnicodeString strMacroName);
	//设置sheet
	void SetSheet(int  iSheetIndex);
	//得到sheet表名
	CATUnicodeString GetSheetName(int index);
	//得到当前workbook中含有多少个sheet
	int GetSheetCount();
	//设置sheet为当前sheet  
	void SetCurrentSheet(CATUnicodeString strSheetName);
	//设置sheet表名
	void SetSheetName(int index,CATUnicodeString strName);
	//得到某一个sheet的索引值
	int GetSheetIndex(CATUnicodeString strSheetName);
	//移动某个sheet到指定位置
	void MoveSheetToPos(int SheetIndex,int MoveToPos);
	//写某一行的一些单元格的值
	void WriteRowData(long iRow, long iColIndex, CATListOfCATUnicodeString &LstValue);
	//得到某一sheet某单元格的值
	CATUnicodeString GetSheetCellData(int sheetIndex,long iRowIndex, long iColIndex);
	//得到某一个sheet使用的行数
	int ExcelClass::GetSheetUsedRows(int sheetIndex);
	//得到某一个sheet使用的列数
	int ExcelClass::GetSheetUsedCols(int sheetIndex);
	//设置某一个sheet表的某个单元格的值
	void UpdateSheetCellData(int sheetIndex,long iRowIndex, long iColIndex, CATUnicodeString Value);
	//写某一列的一些单元格的值
	void WriteColData(long iRowIndex, long iCol, CATListOfCATUnicodeString &LstValue);
	//写某个sheet的某些单元格的值
	void WriteSheetCellsData(int sheetIndex,long iRowStart, long iColStart,long iRowEnd, long iColEnd, CATListOfCATUnicodeString &LstValue,int Type);
	//从起始单元格到终止单元格连续写值。并指定写的方式
	void WriteData(long iRowStart, long iColStart,long iRowEnd, long iColEnd, CATListOfCATUnicodeString &LstValue,int Type);
	//得到某个sheet的某些单元格的值
	void GetSheetCellsData(int sheetIndex,long iRowStart, long iColStart,long iRowEnd, long iColEnd, CATListOfCATUnicodeString &LstValue,int Type);
	//向单元格写值
	void WriteCellData(long iRowIndex, long iColIndex, CATUnicodeString Value);
	//获得已经使用的行数
	int GetUsedRowNum();
	//获得已经使用的列数
	int GetUsedColNum();
	//获得已经使用的单元格起始行
	int GetUsedRowStart();
	//获得已经使用的单元格的起始列
	int GetUsedColStart();
	//读取某一个单元格的值
	CATUnicodeString ReadOneCellValue(long iRow,long iCol);
	//读取某一行的某一些值
	void ReadRowData(long iRow,long iColIndex,long iColNum,CATListOfCATUnicodeString &oLstValue);
	//读取某一列的某一些值
	//void ReadColData(long iRowIndex,long iRowNum,long iCol,CATListOfCATUnicodeString &oLstValue);
	void ReadColData(long iCol,long iRowIndex,long iRowNum,CATListOfCATUnicodeString &oLstValue);
	//设置单元格字体颜色
	void SetCellFontColor(long iRow,long iCol,COLORREF color);
	//设置单元格字体大小
	void SetCellFontSize(long iRow,long iCol,int iFontSize);
	//设置单元格字体是否为粗体
	void SetCellFontBold(long iRow,long iCol,bool bBold);
	//设置行字体颜色
	void SetRowFontColor(long iRow,COLORREF color);
	//设置列字体颜色
	void SetColFontColor(long iCol,COLORREF color);
	//设置行字体大小
	void SetRowFontSize(long iRow,int iFontSize);
	//设置列字体大小
	void SetColFontSize(long iCol,int iFontSize);
	//设置行是否为粗体
	void SetRowFontBold(long iRow,bool bBold);
	//设置列是否为粗体
	void SetColFontBold(long iCol,bool bBold);
	//设置使用过的单元格黑线框
	void SetCellBorderAround(long iStartRow,long iStartCol,long iEndRow,long iEndCol);
	//设置某个sheet的某些单元格黑线框
	void SetSheetCellBorderAround(int sheetIndex,long iStartRow,long iStartCol,long iEndRow,long iEndCol);
	//设置单元格的水平对齐方式
	void SetHCellAlignStye(long iRow,long iCol,long hResult);
	//设置列的水平对齐方式
	void SetHColAlignStye(long iCol,long hResult);
	//设置列的某些单元格水平对齐方式
	void SetHColCellsAlignStye(long iCol,long iStartRow,long iEndRow,long hResult);
	//设置列的某些单元格垂直对齐方式
	void SetVColCellsAlignStye(long iCol,long iStartRow,long iEndRow,long vResult);
	//设置行的水平对齐方式
	void SetHRowAlignStye(long iRow,long vResult);
	//设置行的某些单元格水平对齐方式
	void SetHRowCellsAlignStye(long iRow,long iStartCol,long iEndCol,long hResult);
	//设置行的某些单元格垂直对齐方式
	void SetVRowCellsAlignStye(long iRow,long iStartCol,long iEndCol,long vResult);
	//设置单元格的垂直对齐方式
	void SetVCellAlignStye(long iRow,long iCol,long vResult);
	//设置行的垂直对齐方式
	void SetVRowAlignStye(long iRow,long vResult);
	//设置列的垂直对齐方式
	void SetVColAlignStye(long iCol,long vResult);
	//设置单元格填充色
	void SetRangeFillColor(long iRow,long iCol,COLORREF color);
	//设置某些单元格的填充色
	void SetSomeRangeFillColor(long iStartRow,long iStartCol,long iEndRow,long iEndCol,COLORREF color);
	//设置行填充色
	void SetRowFillColor(long iRow,COLORREF color);
	//设置列填充色
	void SetColFillColor(long iCol,COLORREF color);
	//合并单元格
	void MergeCells(long iRowStart,long iColStart,long iRowEnd,long iColEnd);
	//合并单元格
	void MergeCell(CString iRowStart,CString iColStart,CString iRowEnd,CString iColEnd);
	//插入行
	void InsertRows(long iRow);
	//插入列
	void InsertCols(long iCol);
	//写公式
	void WriteFormula(long iRow,long iCol,CATUnicodeString formula );
	//设置某个单元格的高度宽度
	void SetCellHeightWidth(long iRow,long iCol,float iHeight,float iWidth);
	//设置行高
	void SetRowHeight(long iRow, float iHeight);
	//得到行高
	void GetRowHeight(long iRow, float &iHeight);
	//设置列宽
	void SetColWidth(long iColumn, float iWidth);
	//得到列宽
	void GetColWidth(long iColumn, float &iWidth);
	//设置某个单元格自动换行
	void SetAutoWrap(long iRow, long iColumn);
	//设置某些单元格格式
	void SetRangeFormatLocal(long iStartRow,long iStartCol,long iEndRow,long iEndCol,CATUnicodeString DecimalDigits);
	//设置设置某个Sheet某些单元格格式   
	void SetSheetRangeFormat(int sheetIndex,long iStartRow,long iStartCol,long iEndRow,long iEndCol,CATUnicodeString DecimalDigits);
	//设置所有单元格自动适应
	void AllCellAutoFit(int Fillstye);
	// 删除行   
	void DeleteRow(long iRow);
	// 删除列   
	void DeleteCol(long iCol);
	//设置边框
	void SetBorders(long iStartRow, long iStartColumn, long iEndRow, long iEndColumn,// 指定的单元格
		bool bLeft, bool bTop, bool bRight, bool bBottom,				// 指定的四个边
		bool bInsideVertical, bool bInsideHorizontal,					// 内部边框
		long Left_LineType, long Top_LineType, long Right_LineType, long Bottom_LineType, // 四个边的线类型
		long InsideVertical_LineType, long InsideHorizontal_LineType);	// 内部边框的线类型

	void SetBorders(long iStartRow, long iStartColumn, long iEndRow, long iEndColumn);

	//创建图表
	void CreatChartObjects(double dLeft, double dTop, double dWidth, double dHeight, // 图标的位置和大小
											CString strDataSourceRange,
											CString strTitle,
											CString strX,
											CString strY);
	//行冻结
	void LineFreezePanes(long iRow);
	//插入图片
	void InsertPictures(long iRow,long iCol,float iRowHeight,float iColWidth,CATUnicodeString iPicturePath, float iRowOffSet=0.0, float iColOffSet=0.0);

	//获得合并单元格信息
	void GetMergeAreaInfo(long iRow, long iColumn, long& MergeRowCount, long& MergeColumnCount, long& MergeStartRow, long& MergeStartColumn);
	//保存
	void SaveExcelFile(CString savePath,bool bOpenTemp);
	//关闭--TianHH-2016.3.1
	void CloseExcelFile(CString savePath);
	//保存为文本
	void SaveTextFile(CString savePath,bool bOpenTemp);

	void DownloadPicuture( int iSheetIndex, int iRow, int iCol, CATUnicodeString istrFileSavePath );


};

//-----------------------------------------------------------------------

#endif
