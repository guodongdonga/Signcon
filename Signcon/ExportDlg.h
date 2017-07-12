#pragma once
#include "afxwin.h"


// ExportDlg 对话框

class ExportDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ExportDlg)

public:
	ExportDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ExportDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXPORT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_year;
	CEdit m_month;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
