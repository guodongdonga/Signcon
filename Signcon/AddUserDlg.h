#pragma once
#include "afxwin.h"


// AddUserDlg 对话框

class AddUserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddUserDlg)

public:
	AddUserDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AddUserDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDUSER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_enno;
	CEdit m_name;
	afx_msg void OnBnClickedOk();
};
