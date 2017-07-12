#pragma once
/**************************************************************************
* Copyright (c) 2017 damaowo.cn
* File: UserManage.h
* Description : 成员管理对话框类
* modification history
* --------------------
* author: liang 2017-7-10
* --------------------
**************************************************************************/
#include "afxcmn.h"


// UserManage 对话框

class UserManage : public CDialogEx
{
	DECLARE_DYNAMIC(UserManage)

public:
	UserManage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~UserManage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USERMANAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_userlist;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedDelanddeldata();
	afx_msg void OnBnClickedAdd();
};
