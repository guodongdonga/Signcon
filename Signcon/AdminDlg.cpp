// AdminDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Signcon.h"
#include "AdminDlg.h"
#include "afxdialogex.h"
#include "UserManage.h"
#include "Operate.h"
#include "ModAdminDlg.h"
// AdminDlg 对话框

IMPLEMENT_DYNAMIC(AdminDlg, CDialogEx)

AdminDlg::AdminDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ADMIN, pParent)
{
}

AdminDlg::~AdminDlg()
{
}

void AdminDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DBADDRESS, m_dbaddress);
	DDX_Control(pDX, IDC_DBUSER, m_dbuser);
	DDX_Control(pDX, IDC_DBPASSWORD, m_dbpassword);
	DDX_Control(pDX, IDC_DBPORT, m_dbport);
	DDX_Control(pDX, IDC_DBDATABASE, m_dbdb);
	DDX_Control(pDX, IDC_TOLERATE, m_tolerate);
}


BEGIN_MESSAGE_MAP(AdminDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &AdminDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_USEREDIT, &AdminDlg::OnBnClickedUseredit)
	ON_BN_CLICKED(IDC_PREPROCESS, &AdminDlg::OnBnClickedPreprocess)
	ON_BN_CLICKED(IDC_MODADMIN, &AdminDlg::OnBnClickedModadmin)
END_MESSAGE_MAP()


// AdminDlg 消息处理程序


void AdminDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString pStrip, pStrdatabase, pStruser, pStrpassword,pStrport,pStrtolerate;
	m_dbaddress.GetWindowTextA(pStrip);
	m_dbdb.GetWindowTextA(pStrdatabase);
	m_dbuser.GetWindowTextA(pStruser);
	m_dbpassword.GetWindowTextA(pStrpassword);
	m_dbport.GetWindowTextA(pStrport);
	m_tolerate.GetWindowTextA(pStrtolerate);
	int itolerate = atoi(pStrtolerate);
	if (itolerate < 1 || itolerate >59)
	{
		AfxMessageBox("数据不合法，请重新输入"); //限制时间在1-59之间
		return;
	}
	::WritePrivateProfileString(_T("Database connection Info"), _T("IP"), _T(pStrip), _T("C:\\Program Files\\DBSetting.ini"));
	::WritePrivateProfileString(_T("Database connection Info"), _T("database"), _T(pStrdatabase), _T("C:\\Program Files\\DBSetting.ini"));
	::WritePrivateProfileString(_T("Database connection Info"), _T("user"), _T(pStruser), _T("C:\\Program Files\\DBSetting.ini"));
	::WritePrivateProfileString(_T("Database connection Info"), _T("password"), _T(pStrpassword), _T("C:\\Program Files\\DBSetting.ini"));
	::WritePrivateProfileString(_T("Database connection Info"), _T("port"), _T(pStrport), _T("C:\\Program Files\\DBSetting.ini"));
	::WritePrivateProfileString(_T("Setting"), _T("tolerate"), _T(pStrtolerate), _T("C:\\Program Files\\DBSetting.ini"));
	CDialogEx::OnOK();
}


BOOL AdminDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString pStrip, pStrdatabase, pStruser, pStrpassword, pStrport,pStrtolerate;
	int nSize = 254;
	GetPrivateProfileString("Database connection Info", "IP", NULL, pStrip.GetBuffer(254), nSize, "C:\\Program Files\\DBSetting.ini");
	GetPrivateProfileString("Database connection Info", "user", NULL, pStruser.GetBuffer(254), nSize, "C:\\Program Files\\DBSetting.ini");
	GetPrivateProfileString("Database connection Info", "password", NULL, pStrpassword.GetBuffer(254), nSize, "C:\\Program Files\\DBSetting.ini");
	GetPrivateProfileString("Database connection Info", "port", NULL, pStrport.GetBuffer(254), nSize, "C:\\Program Files\\DBSetting.ini");
	GetPrivateProfileString("Database connection Info", "database", NULL, pStrdatabase.GetBuffer(254), nSize, "C:\\Program Files\\DBSetting.ini");
	GetPrivateProfileString("Setting", "tolerate", NULL, pStrtolerate.GetBuffer(254), nSize, "C:\\Program Files\\DBSetting.ini");
	m_dbaddress.SetWindowTextA(pStrip);
	m_dbuser.SetWindowTextA(pStruser);
	m_dbpassword.SetWindowTextA(pStrpassword);
	m_dbport.SetWindowTextA(pStrport);
	m_dbdb.SetWindowTextA(pStrdatabase);
	m_tolerate.SetWindowTextA(pStrtolerate);
	return TRUE;  // return TRUE unless you set the focus to a control
}


void AdminDlg::OnBnClickedUseredit()
{
	// TODO: 在此添加控件通知处理程序代码
	UserManage usermanage;
	usermanage.DoModal();
}


void AdminDlg::OnBnClickedPreprocess()
{
	// TODO: 在此添加控件通知处理程序代码
	Operate op;
	op.Exec(0);
}


void AdminDlg::OnBnClickedModadmin()
{
	// TODO: 在此添加控件通知处理程序代码
	ModAdminDlg modadmindlg;
	modadmindlg.DoModal();
	AfxMessageBox("配置已变更，下次登录生效。");
	return;
}
