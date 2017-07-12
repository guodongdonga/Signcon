// UserManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Signcon.h"
#include "UserManage.h"
#include "afxdialogex.h"
#include "Operate.h"
#include "mysql.h"
#include "AddUserDlg.h"
extern MYSQL m_sqlCon;
// UserManage �Ի���

IMPLEMENT_DYNAMIC(UserManage, CDialogEx)

UserManage::UserManage(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_USERMANAGE, pParent)
{

}

UserManage::~UserManage()
{
}

void UserManage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USERLIST, m_userlist);
}


BEGIN_MESSAGE_MAP(UserManage, CDialogEx)
	ON_BN_CLICKED(IDC_DEL, &UserManage::OnBnClickedDel)
	ON_BN_CLICKED(IDC_DELANDDELDATA, &UserManage::OnBnClickedDelanddeldata)
	ON_BN_CLICKED(IDC_ADD, &UserManage::OnBnClickedAdd)
END_MESSAGE_MAP()


// UserManage ��Ϣ�������


BOOL UserManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_userlist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);      // ����ѡ��������  
	m_userlist.InsertColumn(0, _T("EnNo"), LVCFMT_LEFT, 70);
	m_userlist.InsertColumn(1, _T("����"), LVCFMT_LEFT, 100);        // �����2�е�����  
	CString pStrSerchdate;
	//ori���ݿ��в�ѯ��Ӧ���ڵ���������
	Operate op;
	CString pStrsql;
	op.ConnectMySQL();
	pStrsql = "select * FROM user";
	if (mysql_real_query(&m_sqlCon, pStrsql, (unsigned long)strlen(pStrsql)))// ��ѯ���ݿ��е�""��  
	{
		return 0;
	}
	st_mysql_res *  res = mysql_store_result(&m_sqlCon);//�õ��洢����� 

	if (NULL == res)//���Ϊ���򷵻�
	{
		return 0;
	}
	UpdateData(TRUE);
	MYSQL_ROW row;
	int iIndex = 0;
	m_userlist.DeleteAllItems();//����б�����
	while (row = mysql_fetch_row(res)) //�����ݼ�Ϊrow
	{
		m_userlist.InsertItem(iIndex, NULL);
		int rols;
		CString colname;
		for (rols = 0; rols < 2; rols++)
		{
			CString myreaddata(row[rols]);//��row rols��
			if (rols == 0)
			{
				m_userlist.SetItemText(iIndex, 0, myreaddata);
			}
			if (rols == 1)
			{
				m_userlist.SetItemText(iIndex, 1, myreaddata);
			}
		}
		iIndex++;
	}
	UpdateData(false);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void UserManage::OnBnClickedDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iPosition = m_userlist.GetSelectionMark();
	CString pStritem = m_userlist.GetItemText(iPosition,0);
	//AfxMessageBox(pStritem);
	m_userlist.DeleteItem(iPosition);
	Operate op;
	CString pStrsql;
	op.ConnectMySQL();
	pStrsql = "DELETE FROM USER where EnNo =\""+pStritem+"\"";
	mysql_query(&m_sqlCon, pStrsql);
	mysql_close(&m_sqlCon);//�ر�Mysql����
}


void UserManage::OnBnClickedDelanddeldata()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iPosition = m_userlist.GetSelectionMark();
	CString pStritem = m_userlist.GetItemText(iPosition, 0);
	//AfxMessageBox(pStritem);
	m_userlist.DeleteItem(iPosition);
	Operate op;
	CString pStrsql;
	op.ConnectMySQL();
	pStrsql = "DELETE FROM USER where EnNo =\"" + pStritem + "\"";
	mysql_query(&m_sqlCon, pStrsql);
	pStrsql = "DELETE FROM signoridata where EnNo =\"" + pStritem + "\"";
	mysql_query(&m_sqlCon, pStrsql);
	pStrsql = "DELETE FROM preprocess where EnNo =\"" + pStritem + "\"";
	mysql_query(&m_sqlCon, pStrsql);
}


void UserManage::OnBnClickedAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AddUserDlg adduserdlg;
	adduserdlg.DoModal();
}
