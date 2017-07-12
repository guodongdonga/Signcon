// UserManage.cpp : 实现文件
//

#include "stdafx.h"
#include "Signcon.h"
#include "UserManage.h"
#include "afxdialogex.h"
#include "Operate.h"
#include "mysql.h"
#include "AddUserDlg.h"
extern MYSQL m_sqlCon;
// UserManage 对话框

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


// UserManage 消息处理程序


BOOL UserManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_userlist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);      // 整行选择、网格线  
	m_userlist.InsertColumn(0, _T("EnNo"), LVCFMT_LEFT, 70);
	m_userlist.InsertColumn(1, _T("姓名"), LVCFMT_LEFT, 100);        // 插入第2列的列名  

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




	// TODO:  在此添加额外的初始化
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void UserManage::OnBnClickedDel()
{
	// TODO: 在此添加控件通知处理程序代码
	int iPosition = m_userlist.GetSelectionMark();
	CString pStritem = m_userlist.GetItemText(iPosition,0);
	//AfxMessageBox(pStritem);
	m_userlist.DeleteItem(iPosition);
	Operate op;
	CString str;
	op.ConnectMySQL();

	str = "DELETE FROM USER where EnNo =\""+pStritem+"\"";
	mysql_query(&m_sqlCon, str);
	mysql_close(&m_sqlCon);//关闭Mysql连接
}


void UserManage::OnBnClickedDelanddeldata()
{
	// TODO: 在此添加控件通知处理程序代码
	int iPosition = m_userlist.GetSelectionMark();
	CString pStritem = m_userlist.GetItemText(iPosition, 0);
	//AfxMessageBox(pStritem);
	m_userlist.DeleteItem(iPosition);
	Operate op;
	CString str;
	op.ConnectMySQL();
	str = "DELETE FROM USER where EnNo =\"" + pStritem + "\"";
	mysql_query(&m_sqlCon, str);
	str = "DELETE FROM signoridata where EnNo =\"" + pStritem + "\"";
	mysql_query(&m_sqlCon, str);
	str = "DELETE FROM preprocess where EnNo =\"" + pStritem + "\"";
	mysql_query(&m_sqlCon, str);
}


void UserManage::OnBnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	AddUserDlg adduserdlg;
	adduserdlg.DoModal();
}
