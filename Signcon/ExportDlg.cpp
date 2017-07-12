// ExportDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Signcon.h"
#include "ExportDlg.h"
#include "afxdialogex.h"
#include "Operate.h"


// ExportDlg 对话框

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


// ExportDlg 消息处理程序


void ExportDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	Operate op;
	int iYear, iMonth;
	CString pStrstr;
	m_year.GetWindowTextA(pStrstr);
	iYear = atoi(pStrstr);
	m_month.GetWindowTextA(pStrstr);
	iMonth = atoi(pStrstr);
	op.layoutxlsx(iYear, iMonth);
	CDialogEx::OnOK();
}


BOOL ExportDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdateData(TRUE);
	GetDlgItem(IDC_EDIT1)->SetWindowTextA("2016");//为文本框填上默认值。
	GetDlgItem(IDC_EDIT2)->SetWindowTextA("1");
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
