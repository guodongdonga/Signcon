#pragma once
#include "afxcmn.h"


// BrowserByUserDlg 对话框

class BrowserByUserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(BrowserByUserDlg)

public:
	BrowserByUserDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~BrowserByUserDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BROWSERBYUSER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_userlist;
	CListCtrl m_detaillist;
	afx_msg void OnBnClickedOk();
};
