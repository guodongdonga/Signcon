// UserList.cpp : 实现文件
//

#include "stdafx.h"
#include "Signcon.h"
#include "UserList.h"
#include "afxdialogex.h"


// UserList 对话框

IMPLEMENT_DYNAMIC(UserList, CDialogEx)

UserList::UserList(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

UserList::~UserList()
{
}

void UserList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USERLIST, m_list);
}


BEGIN_MESSAGE_MAP(UserList, CDialogEx)
END_MESSAGE_MAP()


// UserList 消息处理程序


BOOL UserList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_list.AddString(_T("123"));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
