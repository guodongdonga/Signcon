// HelpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Signcon.h"
#include "HelpDlg.h"
#include "afxdialogex.h"


// HelpDlg 对话框

IMPLEMENT_DYNAMIC(HelpDlg, CDialogEx)

HelpDlg::HelpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HELP, pParent)
{

}

HelpDlg::~HelpDlg()
{
}

void HelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(HelpDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &HelpDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// HelpDlg 消息处理程序


void HelpDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	if (DeleteFile("C:\\Program Files\\DBSetting.ini"))
	{
		AfxMessageBox("重置完成，重启后即可重新配置");
		PostMessage(WM_QUIT, 0, 0);
	}
}
