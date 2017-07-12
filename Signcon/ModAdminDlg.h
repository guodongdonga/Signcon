#pragma once
/**************************************************************************
* Copyright (c) 2017 damaowo.cn
* File: ModAdminDlg.h
* Description : 修改管理员信息对话框类
* modification history
* --------------------
* author: liang 2017-7-8
* --------------------
**************************************************************************/
#include "afxwin.h"


// ModAdminDlg 对话框

class ModAdminDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ModAdminDlg)

public:
	ModAdminDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ModAdminDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODADMIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_adminid;
	CEdit m_adminpassword;
	afx_msg void OnBnClickedOk();
};
