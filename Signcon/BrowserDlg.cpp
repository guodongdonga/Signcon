// BrowserDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Signcon.h"
#include "BrowserDlg.h"
#include "afxdialogex.h"
#include "Operate.h"
#include "mysql.h"
// BrowserDlg 对话框
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


// BrowserDlg 消息处理程序


BOOL BrowserDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_listbrowser.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);      // 整行选择、网格线  
	m_listbrowser.InsertColumn(0, _T("流水号"), LVCFMT_LEFT, 50);
	m_listbrowser.InsertColumn(1, _T("机器号"), LVCFMT_LEFT, 50);        // 插入第2列的列名  
	m_listbrowser.InsertColumn(2, _T("EnNo"), LVCFMT_LEFT, 100);        // 插入第3列的列名  
	m_listbrowser.InsertColumn(3, _T("姓名"), LVCFMT_LEFT, 80);        // 插入第4列的列名  
	m_listbrowser.InsertColumn(4, _T("签到时间"), LVCFMT_LEFT, 150);        // 插入第5列的列名  

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void BrowserDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString pstrSerchdate;
	m_browserdate.GetWindowTextA(pstrSerchdate);
	//ori数据库中查询对应日期的所有数据
	Operate op;
	CString pStrsql;
	op.ConnectMySQL();

	pStrsql = "select * FROM signoridata where Date = \"" + pstrSerchdate + "\"";
	if (mysql_real_query(&m_sqlCon, pStrsql, (unsigned long)strlen(pStrsql)))// 查询数据库中的""表  
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
	m_listbrowser.DeleteAllItems();
	while (row = mysql_fetch_row(res)) //行数据集为row
	{
		m_listbrowser.InsertItem(iIndex, NULL);
		int irols;
		CString colname;
		for (irols = 0; irols < 6; irols++)
		{
			CString pStrmyreaddata(row[irols]);//读row irols列
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
	UpdateData(false);//加上
}