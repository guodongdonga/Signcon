#pragma once
#include "afxwin.h"


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
