#pragma once
#include "afxwin.h"
#include "AdminDlg.h"

// Login 对话框

class Login : public CDialogEx
{
	DECLARE_DYNAMIC(Login)

public:
	Login(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Login();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_username;
	CEdit m_password;
	afx_msg void OnBnClickedLogin();
};
