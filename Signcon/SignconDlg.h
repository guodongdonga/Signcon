
// SignconDlg.h : ͷ�ļ�
//

#pragma once

class CSignconDlgAutoProxy;


// CSignconDlg �Ի���
class CSignconDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSignconDlg);
	friend class CSignconDlgAutoProxy;

// ����
public:
	CSignconDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CSignconDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SIGNCON_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	CSignconDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// ���ɵ���Ϣӳ�亯��
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
