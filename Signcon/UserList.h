#pragma once
#include "afxwin.h"


// UserList 对话框

class UserList : public CDialogEx
{
	DECLARE_DYNAMIC(UserList)

public:
	UserList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~UserList();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USERLIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 用户列表
	CListBox m_list;
	virtual BOOL OnInitDialog();
};
