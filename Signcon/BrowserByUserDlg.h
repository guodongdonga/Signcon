#pragma once
#include "afxcmn.h"


// BrowserByUserDlg �Ի���

class BrowserByUserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(BrowserByUserDlg)

public:
	BrowserByUserDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~BrowserByUserDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BROWSERBYUSER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_userlist;
	CListCtrl m_detaillist;
	afx_msg void OnBnClickedOk();
};
