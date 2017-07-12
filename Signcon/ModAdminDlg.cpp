// ModAdminDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Signcon.h"
#include "ModAdminDlg.h"
#include "afxdialogex.h"
#include "Operate.h"
#include "mysql.h"
extern MYSQL m_sqlCon;

// ModAdminDlg 对话框

IMPLEMENT_DYNAMIC(ModAdminDlg, CDialogEx)

ModAdminDlg::ModAdminDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MODADMIN, pParent)
{

}

ModAdminDlg::~ModAdminDlg()
{
}

void ModAdminDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADMINID, m_adminid);
	DDX_Control(pDX, IDC_ADMINPASSWORD, m_adminpassword);
}


BEGIN_MESSAGE_MAP(ModAdminDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ModAdminDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ModAdminDlg 消息处理程序


void ModAdminDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	Operate op;
	CString str,pStrusername,pStrpassword;
	op.ConnectMySQL();
	m_adminid.GetWindowText(pStrusername);
	m_adminpassword.GetWindowText(pStrpassword);
	str = "DELETE FROM auth";
	mysql_query(&m_sqlCon, str);
	str = "Insert into auth values(1,"+ pStrusername+","+ pStrpassword+",1)";
	mysql_query(&m_sqlCon, str);
	mysql_close(&m_sqlCon);//关闭Mysql连接


	CDialogEx::OnOK();
}
