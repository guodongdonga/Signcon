// AddUserDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Signcon.h"
#include "AddUserDlg.h"
#include "afxdialogex.h"
#include "Operate.h"
#include "mysql.h"
extern MYSQL m_sqlCon;

// AddUserDlg �Ի���

IMPLEMENT_DYNAMIC(AddUserDlg, CDialogEx)

AddUserDlg::AddUserDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ADDUSER, pParent)
{

}

AddUserDlg::~AddUserDlg()
{
}

void AddUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_enno);
	DDX_Control(pDX, IDC_EDIT2, m_name);
}


BEGIN_MESSAGE_MAP(AddUserDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &AddUserDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// AddUserDlg ��Ϣ��������


void AddUserDlg::OnBnClickedOk()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	CString pStrenno, pStrname;
	m_enno.GetWindowTextA(pStrenno);
	m_name.GetWindowTextA(pStrname);
	Operate op;
	CString str;
	op.ConnectMySQL();
	str = "Insert into user values(\""+ pStrenno +"\",\""+pStrname+"\")";
	mysql_query(&m_sqlCon, str);
	AfxMessageBox("ִ����ɣ����´��û�����ҳ�漴�ɸ���");
	CDialogEx::OnOK();
}