#pragma once
#include "afxwin.h"


// AddUserDlg �Ի���

class AddUserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddUserDlg)

public:
	AddUserDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AddUserDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDUSER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_enno;
	CEdit m_name;
	afx_msg void OnBnClickedOk();
};
