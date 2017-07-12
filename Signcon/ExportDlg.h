#pragma once
#include "afxwin.h"
/**************************************************************************
* Copyright (c) 2017 damaowo.cn
* File: ExportDlg.h
* Description : ExportDlg�Ի�����
*				����excel�Ի���
* modification history
* --------------------
* author: liang 2017-7-8
* --------------------
**************************************************************************/

// ExportDlg �Ի���

class ExportDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ExportDlg)

public:
	ExportDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ExportDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXPORT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_year;
	CEdit m_month;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
