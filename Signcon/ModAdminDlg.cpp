// ModAdminDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Signcon.h"
#include "ModAdminDlg.h"
#include "afxdialogex.h"
#include "Operate.h"
#include "mysql.h"
extern MYSQL m_sqlCon;

// ModAdminDlg �Ի���

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


// ModAdminDlg ��Ϣ�������


void ModAdminDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Operate op;
	CString pStrsql,pStrusername,pStrpassword;
	op.ConnectMySQL();
	m_adminid.GetWindowText(pStrusername);
	m_adminpassword.GetWindowText(pStrpassword);
	pStrsql = "DELETE FROM auth";
	mysql_query(&m_sqlCon, pStrsql);
	pStrsql = "Insert into auth values(1,"+ pStrusername+","+ pStrpassword+",1)";
	mysql_query(&m_sqlCon, pStrsql);
	mysql_close(&m_sqlCon);//�ر�Mysql����
	CDialogEx::OnOK();
}
