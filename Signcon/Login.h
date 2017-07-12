#pragma once
/**************************************************************************
* Copyright (c) 2017 damaowo.cn
* File: Login.h
* Description : ��¼�Ի�����
* modification history
* --------------------
* author: liang 2017-7-8
* --------------------
**************************************************************************/
#include "afxwin.h"
#include "AdminDlg.h"

// Login �Ի���

class Login : public CDialogEx
{
	DECLARE_DYNAMIC(Login)

public:
	Login(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Login();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_username;
	CEdit m_password;
	afx_msg void OnBnClickedLogin();
};
