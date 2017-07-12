// Login.cpp : 实现文件
//

#include "stdafx.h"
#include "Signcon.h"
#include "Login.h"
#include "afxdialogex.h"
#include "Operate.h"
#include "mysql.h"
// Login 对话框

extern MYSQL m_sqlCon;

IMPLEMENT_DYNAMIC(Login, CDialogEx)

Login::Login(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOGIN, pParent)
{

}

Login::~Login()
{
}

void Login::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_username);
	DDX_Control(pDX, IDC_EDIT2, m_password);
}


BEGIN_MESSAGE_MAP(Login, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Login::OnBnClickedLogin)
END_MESSAGE_MAP()


// Login 消息处理程序





void Login::OnBnClickedLogin()
{
	Operate op;
	int isafeflag = 0;
	op.ConnectMySQL();
	CString pStrsql, pStrusername, password;
	m_username.GetWindowTextA(pStrusername);
	m_password.GetWindowTextA(password);
	if (pStrusername == "root") //当数据库配置修改错误时，会导致无法登陆，可使用root临时登陆
	{
		if(!PathFileExists("C:\\Program Files\\DBSetting.ini"))//当配置文件不存在的时候，可以使用root账户进行登录
		{ 
		if (password == "SafePa$$Local")
		{
			AdminDlg admindlg;
			admindlg.DoModal();
			AfxMessageBox("此密码仅供备用，修改数据库配置后，请使用其他密码登陆进行操作");
			return;
		}
		}
		else
		{
			AfxMessageBox("root用户不可用");
			return;
		}
	}
	pStrsql = "select password from auth where user = \"" + pStrusername + "\"";
	if (mysql_real_query(&m_sqlCon, pStrsql, (unsigned long)strlen(pStrsql)))// 查询数据库中的""表  
	{
		return;
	}
	st_mysql_res *  res = mysql_store_result(&m_sqlCon);//得到存储结果集 
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res)) //行数据集为row
	{
		CString pStrmyreaddata(row[0]);//读row rols列
		if (pStrmyreaddata == password) {
			AdminDlg admindlg;
			admindlg.DoModal();
			return;
		}
		else {
			AfxMessageBox("密码错误");
			return;
		}
	}
	AfxMessageBox("不存在的用户名");
	CDialogEx::OnOK();
}
