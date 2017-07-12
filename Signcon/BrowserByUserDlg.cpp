// BrowserByUserDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Signcon.h"
#include "BrowserByUserDlg.h"
#include "afxdialogex.h"
#include "Operate.h"
#include "mysql.h"
// BrowserByUserDlg 对话框
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


// BrowserByUserDlg 消息处理程序


BOOL BrowserByUserDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_userlist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);      
	m_userlist.InsertColumn(0, _T("EnNo"), LVCFMT_CENTER, 110);// 整行选择、网格线  
	m_userlist.InsertColumn(1, _T("用户名"), LVCFMT_CENTER, 112);
	m_detaillist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);      // 整行选择、网格线  
	m_detaillist.InsertColumn(0, _T("流水号"), LVCFMT_CENTER, 70);	
	m_detaillist.InsertColumn(1, _T("日期"), LVCFMT_CENTER, 80);
	m_detaillist.InsertColumn(2, _T("时间"), LVCFMT_CENTER, 80);
	m_detaillist.InsertColumn(3, _T("机器号"), LVCFMT_CENTER, 70);
	
	CString pstrSerchdate;
	//ori数据库中查询对应日期的所有数据
	Operate op;
	CString str;
	op.ConnectMySQL();

	str = "select * FROM user";
	if (mysql_real_query(&m_sqlCon, str, (unsigned long)strlen(str)))// 查询数据库中的""表  
	{
		return 0;
	}
	st_mysql_res *  res = mysql_store_result(&m_sqlCon);//得到存储结果集 

	if (NULL == res)//如果为空则返回
	{
		return 0;
	}

	UpdateData(TRUE);//加上
	MYSQL_ROW row;
	int iIndex = 0;
	m_userlist.DeleteAllItems();
	while (row = mysql_fetch_row(res)) //行数据集为row
	{
		m_userlist.InsertItem(iIndex, NULL);
		int rols;
		CString colname;
		for (rols = 0; rols < 2; rols++)
		{
			CString myreaddata(row[rols]);//读row rols列
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
	UpdateData(false);//加上
	mysql_close(&m_sqlCon);//关闭Mysql连接
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void BrowserByUserDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	int iPosition = m_userlist.GetSelectionMark();
	CString pStritem = m_userlist.GetItemText(iPosition, 0);
	//AfxMessageBox(pStritem);
	Operate op;
	CString str;
	op.ConnectMySQL();

	str = "select * from signoridata where enno = "+ pStritem;
	if (mysql_real_query(&m_sqlCon, str, (unsigned long)strlen(str)))// 查询数据库中的""表  
	{
		return ;
	}
	st_mysql_res *  res = mysql_store_result(&m_sqlCon);//得到存储结果集 

	if (NULL == res)//如果为空则返回
	{
		return ;
	}

	UpdateData(TRUE);//加上
	MYSQL_ROW row;
	int iIndex = 0;
	m_detaillist.DeleteAllItems();
	while (row = mysql_fetch_row(res)) //行数据集为row
	{
		m_detaillist.InsertItem(iIndex, NULL);
		int rols;
		CString colname;
		for (rols = 0; rols < 6; rols++)
		{
			CString myreaddata(row[rols]);//读row rols列
			if (rols == 0)
			{
				m_detaillist.SetItemText(iIndex, 0, myreaddata);
			}
			if (rols == 1)
			{
				m_detaillist.SetItemText(iIndex, 3, myreaddata);
			}
			if (rols == 4)
			{
				m_detaillist.SetItemText(iIndex, 1, myreaddata);
			}
			if (rols == 5)
			{
				m_detaillist.SetItemText(iIndex, 2, myreaddata);
			}
		}
		iIndex++;
	}
	UpdateData(false);//加上
	mysql_close(&m_sqlCon);//关闭Mysql连接
	
	//CDialogEx::OnOK();
}
