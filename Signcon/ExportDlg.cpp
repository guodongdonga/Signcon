// ExportDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Signcon.h"
#include "ExportDlg.h"
#include "afxdialogex.h"
#include "Operate.h"


// ExportDlg �Ի���

IMPLEMENT_DYNAMIC(ExportDlg, CDialogEx)

ExportDlg::ExportDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EXPORT, pParent)
{

}

ExportDlg::~ExportDlg()
{
}

void ExportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_year);
	DDX_Control(pDX, IDC_EDIT2, m_month);
}


BEGIN_MESSAGE_MAP(ExportDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ExportDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ExportDlg ��Ϣ�������


void ExportDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Operate op;
	int iYear, iMonth;
	CString str;
	m_year.GetWindowTextA(str);
	iYear = atoi(str);
	m_month.GetWindowTextA(str);
	iMonth = atoi(str);
	op.layoutxlsx(iYear, iMonth);
	CDialogEx::OnOK();
}


BOOL ExportDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	UpdateData(TRUE);
	GetDlgItem(IDC_EDIT1)->SetWindowTextA("2016");//Ϊ�ı�������Ĭ��ֵ��
	GetDlgItem(IDC_EDIT2)->SetWindowTextA("1");
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
