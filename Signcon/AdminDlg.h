#pragma once
#include "afxwin.h"


// AdminDlg 对话框

class AdminDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AdminDlg)

public:
	AdminDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AdminDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADMIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit m_dbaddress;
	CEdit m_dbuser;
	CEdit m_dbpassword;
	CEdit m_dbport;
	CEdit m_dbdb;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedUseredit();
	afx_msg void OnBnClickedPreprocess();
	CEdit m_tolerate;
	afx_msg void OnBnClickedModadmin();
};
