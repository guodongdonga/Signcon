#pragma once
#include "afxwin.h"


// UserList �Ի���

class UserList : public CDialogEx
{
	DECLARE_DYNAMIC(UserList)

public:
	UserList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~UserList();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USERLIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// �û��б�
	CListBox m_list;
	virtual BOOL OnInitDialog();
};
