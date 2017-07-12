#pragma once
/**************************************************************************
* Copyright (c) 2017 damaowo.cn
* File: UserManage.h
* Description : ��Ա����Ի�����
* modification history
* --------------------
* author: liang 2017-7-10
* --------------------
**************************************************************************/
#include "afxcmn.h"


// UserManage �Ի���

class UserManage : public CDialogEx
{
	DECLARE_DYNAMIC(UserManage)

public:
	UserManage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~UserManage();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USERMANAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_userlist;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedDelanddeldata();
	afx_msg void OnBnClickedAdd();
};
