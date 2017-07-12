
// DlgProxy.cpp : 实现文件
//

#include "stdafx.h"
#include "Signcon.h"
#include "DlgProxy.h"
#include "SignconDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSignconDlgAutoProxy

IMPLEMENT_DYNCREATE(CSignconDlgAutoProxy, CCmdTarget)

CSignconDlgAutoProxy::CSignconDlgAutoProxy()
{
	EnableAutomation();
	
	// 为使应用程序在自动化对象处于活动状态时一直保持 
	//	运行，构造函数调用 AfxOleLockApp。
	AfxOleLockApp();

	// 通过应用程序的主窗口指针
	//  来访问对话框。  设置代理的内部指针
	//  指向对话框，并设置对话框的后向指针指向
	//  该代理。
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CSignconDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CSignconDlg)))
		{
			m_pDialog = reinterpret_cast<CSignconDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CSignconDlgAutoProxy::~CSignconDlgAutoProxy()
{
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	//	析构函数调用 AfxOleUnlockApp。
	//  除了做其他事情外，这还将销毁主对话框
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CSignconDlgAutoProxy::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CSignconDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CSignconDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 注意: 我们添加了对 IID_ISigncon 的支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {F0E1103C-2440-4CB2-92B6-21473992F8FF}
static const IID IID_ISigncon =
{ 0xF0E1103C, 0x2440, 0x4CB2, { 0x92, 0xB6, 0x21, 0x47, 0x39, 0x92, 0xF8, 0xFF } };

BEGIN_INTERFACE_MAP(CSignconDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CSignconDlgAutoProxy, IID_ISigncon, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 宏在此项目的 StdAfx.h 中定义
// {66649C91-23BC-4858-9F53-13527F73FB22}
IMPLEMENT_OLECREATE2(CSignconDlgAutoProxy, "Signcon.Application", 0x66649c91, 0x23bc, 0x4858, 0x9f, 0x53, 0x13, 0x52, 0x7f, 0x73, 0xfb, 0x22)


// CSignconDlgAutoProxy 消息处理程序
