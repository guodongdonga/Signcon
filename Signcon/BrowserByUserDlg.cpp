// BrowserByUserDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Signcon.h"
#include "BrowserByUserDlg.h"
#include "afxdialogex.h"
#include "Operate.h"
#include "mysql.h"
// BrowserByUserDlg �Ի���
extern MYSQL m_sqlCon;
IMPLEMENT_DYNAMIC(BrowserByUserDlg, CDialogEx)

BrowserByUserDlg::BrowserByUserDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BROWSERBYUSER, pParent)
{

}

BrowserByUserDlg::~BrowserByUserDlg()
{
}

void BrowserByUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USER, m_userlist);
	DDX_Control(pDX, IDC_DETAIL, m_detaillist);
}


BEGIN_MESSAGE_MAP(BrowserByUserDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &BrowserByUserDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// BrowserByUserDlg ��Ϣ�������


BOOL BrowserByUserDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString pStrSerchdate;
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_userlist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);      
	m_userlist.InsertColumn(0, _T("EnNo"), LVCFMT_CENTER, 110);// ����ѡ��������  
	m_userlist.InsertColumn(1, _T("�û���"), LVCFMT_CENTER, 112);
	m_detaillist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);      // ����ѡ��������  
	m_detaillist.InsertColumn(0, _T("��ˮ��"), LVCFMT_CENTER, 70);	
	m_detaillist.InsertColumn(1, _T("����"), LVCFMT_CENTER, 80);
	m_detaillist.InsertColumn(2, _T("ʱ��"), LVCFMT_CENTER, 80);
	m_detaillist.InsertColumn(3, _T("������"), LVCFMT_CENTER, 70);
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
	m_userlist.DeleteAllItems();
	while (row = mysql_fetch_row(res)) //�����ݼ�Ϊrow
	{
		m_userlist.InsertItem(iIndex, NULL);
		int rols;
		CString colname;
		for (rols = 0; rols < 2; rols++)
		{
			CString pStrmyreaddata(row[rols]);//��row rols��
			if (rols == 0)
			{
				m_userlist.SetItemText(iIndex, 0, pStrmyreaddata);
			}
			if (rols == 1)
			{
				m_userlist.SetItemText(iIndex, 1, pStrmyreaddata);
			}
		}
		iIndex++;
	}
	UpdateData(false);
	mysql_close(&m_sqlCon);//�ر�Mysql����
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void BrowserByUserDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iPosition = m_userlist.GetSelectionMark();
	CString pStritem = m_userlist.GetItemText(iPosition, 0);
	//AfxMessageBox(pStritem);
	Operate op;
	CString pStrsql;
	op.ConnectMySQL();
	pStrsql = "select * from signoridata where enno = "+ pStritem;
	if (mysql_real_query(&m_sqlCon, pStrsql, (unsigned long)strlen(pStrsql)))// ��ѯ���ݿ��е�""��  
	{
		return ;
	}
	st_mysql_res *  res = mysql_store_result(&m_sqlCon);//�õ��洢����� 

	if (NULL == res)//���Ϊ���򷵻�
	{
		return ;
	}
	UpdateData(TRUE);
	MYSQL_ROW row;
	int iIndex = 0;
	m_detaillist.DeleteAllItems();
	while (row = mysql_fetch_row(res)) //�����ݼ�Ϊrow
	{
		m_detaillist.InsertItem(iIndex, NULL);
		int rols;
		CString colname;
		for (rols = 0; rols < 6; rols++)
		{
			CString pStrmyreaddata(row[rols]);//��row rols��
			if (rols == 0)
			{
				m_detaillist.SetItemText(iIndex, 0, pStrmyreaddata);
			}
			if (rols == 1)
			{
				m_detaillist.SetItemText(iIndex, 3, pStrmyreaddata);
			}
			if (rols == 4)
			{
				m_detaillist.SetItemText(iIndex, 1, pStrmyreaddata);
			}
			if (rols == 5)
			{
				m_detaillist.SetItemText(iIndex, 2, pStrmyreaddata);
			}
		}
		iIndex++;
	}
	UpdateData(false);
	mysql_close(&m_sqlCon);//�ر�Mysql����
	
	//CDialogEx::OnOK();
}
