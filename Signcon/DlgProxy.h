
// DlgProxy.h: ͷ�ļ�
//

#pragma once

class CSignconDlg;


// CSignconDlgAutoProxy ����Ŀ��

class CSignconDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CSignconDlgAutoProxy)

	CSignconDlgAutoProxy();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��

// ����
public:
	CSignconDlg* m_pDialog;

// ����
public:

// ��д
	public:
	virtual void OnFinalRelease();

// ʵ��
protected:
	virtual ~CSignconDlgAutoProxy();

	// ���ɵ���Ϣӳ�亯��

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CSignconDlgAutoProxy)

	// ���ɵ� OLE ����ӳ�亯��

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

