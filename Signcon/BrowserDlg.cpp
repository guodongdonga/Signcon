// BrowserDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Signcon.h"
#include "BrowserDlg.h"
#include "afxdialogex.h"
#include "Operate.h"
#include "mysql.h"
// BrowserDlg �Ի���
extern MYSQL m_sqlCon;

IMPLEMENT_DYNAMIC(BrowserDlg, CDialogEx)

BrowserDlg::BrowserDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BROWSER, pParent)
{

}

BrowserDlg::~BrowserDlg()
{
}

void BrowserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BROWSERLIST, m_listbrowser);
	DDX_Control(pDX, IDC_EDIT1, m_browserdate);
}


BEGIN_MESSAGE_MAP(BrowserDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &BrowserDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// BrowserDlg ��Ϣ�������


BOOL BrowserDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_listbrowser.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);      // ����ѡ��������  
	m_listbrowser.InsertColumn(0, _T("��ˮ��"), LVCFMT_LEFT, 50);
	m_listbrowser.InsertColumn(1, _T("������"), LVCFMT_LEFT, 50);        // �����2�е�����  
	m_listbrowser.InsertColumn(2, _T("EnNo"), LVCFMT_LEFT, 100);        // �����3�е�����  
	m_listbrowser.InsertColumn(3, _T("����"), LVCFMT_LEFT, 80);        // �����4�е�����  
	m_listbrowser.InsertColumn(4, _T("ǩ��ʱ��"), LVCFMT_LEFT, 150);        // �����5�е�����  

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void BrowserDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString pStrSerchdate;
	m_browserdate.GetWindowTextA(pStrSerchdate);
	//ori���ݿ��в�ѯ��Ӧ���ڵ���������
	Operate op;
	CString pStrsql;
	op.ConnectMySQL();

	pStrsql = "select * FROM signoridata where Date = \"" + pStrSerchdate + "\"";
	if (mysql_real_query(&m_sqlCon, pStrsql, (unsigned long)strlen(pStrsql)))// ��ѯ���ݿ��е�""��  
	{
		return ;
	}
	st_mysql_res *  res = mysql_store_result(&m_sqlCon);//�õ��洢����� 

	if (NULL == res)//���Ϊ���򷵻�
	{
		return ;
	}

	UpdateData(TRUE);//����
	MYSQL_ROW row;
	int iIndex = 0;
	m_listbrowser.DeleteAllItems();
	while (row = mysql_fetch_row(res)) //�����ݼ�Ϊrow
	{
		m_listbrowser.InsertItem(iIndex, NULL);
		int irols;
		CString colname;
		for (irols = 0; irols < 6; irols++)
		{
			CString pStrmyreaddata(row[irols]);//��row irols��
			if (irols == 0)
			{
				m_listbrowser.SetItemText(iIndex, 0, pStrmyreaddata);
			}
			if (irols == 1)
			{
				m_listbrowser.SetItemText(iIndex, 1, pStrmyreaddata);
			}
			if (irols == 2)
			{
				m_listbrowser.SetItemText(iIndex, 2, pStrmyreaddata);
			}
			if (irols == 3)
			{
				m_listbrowser.SetItemText(iIndex, 3, pStrmyreaddata);
			}
			if (irols == 5)
			{
				m_listbrowser.SetItemText(iIndex, 4, pStrmyreaddata);
			}
		}
		iIndex++;
	}
	UpdateData(false);//����
}