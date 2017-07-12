#pragma once
#include "afxwin.h"
/**************************************************************************
* Copyright (c) 2017 damaowo.cn
* File: ExportDlg.h
* Description : ExportDlg对话框类
*				导出excel对话框
* modification history
* --------------------
* author: liang 2017-7-8
* --------------------
**************************************************************************/

// ExportDlg 对话框

class ExportDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ExportDlg)

public:
	ExportDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ExportDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXPORT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_year;
	CEdit m_month;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
