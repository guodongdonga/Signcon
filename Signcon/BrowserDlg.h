#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// BrowserDlg �Ի���

class BrowserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(BrowserDlg)

public:
	BrowserDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~BrowserDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BROWSER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_listbrowser;
	afx_msg void OnBnClickedOk();
	CEdit m_browserdate;
};
