
// SignconDlg.h : 头文件
//

#pragma once

class CSignconDlgAutoProxy;


// CSignconDlg 对话框
class CSignconDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSignconDlg);
	friend class CSignconDlgAutoProxy;

// 构造
public:
	CSignconDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CSignconDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SIGNCON_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	CSignconDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnExportToExcel();
	afx_msg void OnImportData();
	afx_msg void OnViewOri();
	afx_msg void OnAdmin();
	afx_msg void OnBrowserByUser();
	afx_msg void OnHelp();
};
