#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// BrowserDlg 对话框

class BrowserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(BrowserDlg)

public:
	BrowserDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~BrowserDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BROWSER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_listbrowser;
	afx_msg void OnBnClickedOk();
	CEdit m_browserdate;
};
