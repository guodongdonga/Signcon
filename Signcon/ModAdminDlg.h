#pragma once
/**************************************************************************
* Copyright (c) 2017 damaowo.cn
* File: ModAdminDlg.h
* Description : �޸Ĺ���Ա��Ϣ�Ի�����
* modification history
* --------------------
* author: liang 2017-7-8
* --------------------
**************************************************************************/
#include "afxwin.h"


// ModAdminDlg �Ի���

class ModAdminDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ModAdminDlg)

public:
	ModAdminDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ModAdminDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODADMIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_adminid;
	CEdit m_adminpassword;
	afx_msg void OnBnClickedOk();
};
