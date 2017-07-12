
// DlgProxy.cpp : ʵ���ļ�
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
	
	// ΪʹӦ�ó������Զ��������ڻ״̬ʱһֱ���� 
	//	���У����캯������ AfxOleLockApp��
	AfxOleLockApp();

	// ͨ��Ӧ�ó����������ָ��
	//  �����ʶԻ���  ���ô�����ڲ�ָ��
	//  ָ��Ի��򣬲����öԻ���ĺ���ָ��ָ��
	//  �ô���
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
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	//	������������ AfxOleUnlockApp��
	//  ���������������⣬�⻹���������Ի���
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CSignconDlgAutoProxy::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CSignconDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CSignconDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// ע��: ��������˶� IID_ISigncon ��֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {F0E1103C-2440-4CB2-92B6-21473992F8FF}
static const IID IID_ISigncon =
{ 0xF0E1103C, 0x2440, 0x4CB2, { 0x92, 0xB6, 0x21, 0x47, 0x39, 0x92, 0xF8, 0xFF } };

BEGIN_INTERFACE_MAP(CSignconDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CSignconDlgAutoProxy, IID_ISigncon, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 ���ڴ���Ŀ�� StdAfx.h �ж���
// {66649C91-23BC-4858-9F53-13527F73FB22}
IMPLEMENT_OLECREATE2(CSignconDlgAutoProxy, "Signcon.Application", 0x66649c91, 0x23bc, 0x4858, 0x9f, 0x53, 0x13, 0x52, 0x7f, 0x73, 0xfb, 0x22)


// CSignconDlgAutoProxy ��Ϣ�������
