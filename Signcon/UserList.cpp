// UserList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Signcon.h"
#include "UserList.h"
#include "afxdialogex.h"


// UserList �Ի���

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


// UserList ��Ϣ�������


BOOL UserList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_list.AddString(_T("123"));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
