// Login.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Signcon.h"
#include "Login.h"
#include "afxdialogex.h"
#include "Operate.h"
#include "mysql.h"
// Login �Ի���

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


// Login ��Ϣ�������





void Login::OnBnClickedLogin()
{
	Operate op;
	int isafeflag = 0;
	op.ConnectMySQL();
	CString pStrsql, pStrusername, password;
	m_username.GetWindowTextA(pStrusername);
	m_password.GetWindowTextA(password);
	if (pStrusername == "root") //�����ݿ������޸Ĵ���ʱ���ᵼ���޷���½����ʹ��root��ʱ��½
	{
		if(!PathFileExists("C:\\Program Files\\DBSetting.ini"))
		{ 
		if (password == "SafePa$$Local")
		{
			AdminDlg admindlg;
			admindlg.DoModal();
			AfxMessageBox("������������ã��޸����ݿ����ú���ʹ�����������½���в���");
			return;
		}
		}
		else
		{
			AfxMessageBox("root�û�������");
			return;
		}
	}
	pStrsql = "select password from auth where user = \"" + pStrusername + "\"";
	if (mysql_real_query(&m_sqlCon, pStrsql, (unsigned long)strlen(pStrsql)))// ��ѯ���ݿ��е�""��  
	{
		return;
	}
	st_mysql_res *  res = mysql_store_result(&m_sqlCon);//�õ��洢����� 
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res)) //�����ݼ�Ϊrow
	{
		CString colname;
		CString pStrmyreaddata(row[0]);//��row rols��
		if (pStrmyreaddata == password) {
			AdminDlg admindlg;
			admindlg.DoModal();
			return;
		}
		else {
			AfxMessageBox("�������");
			return;
		}
	}
	AfxMessageBox("�����ڵ��û���");
	CDialogEx::OnOK();
}
