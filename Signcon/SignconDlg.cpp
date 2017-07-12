
// SignconDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Signcon.h"
#include "SignconDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"
#include "Operate.h"
#include "ExportDlg.h"
#include "AdminDlg.h"
#include "BrowserDlg.h"
#include "Login.h"
#include "LoginDlg.h"
#include "BrowserByUserDlg.h"
#include "HelpDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSignconDlg �Ի���


IMPLEMENT_DYNAMIC(CSignconDlg, CDialogEx);

CSignconDlg::CSignconDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SIGNCON_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CSignconDlg::~CSignconDlg()
{
	// ����öԻ������Զ���������
	//  ���˴���ָ��öԻ���ĺ���ָ������Ϊ NULL���Ա�
	//  �˴���֪���öԻ����ѱ�ɾ����
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CSignconDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSignconDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_APP_ABOUT, &CSignconDlg::OnExportToExcel)
	ON_COMMAND(ID_32772, &CSignconDlg::OnImportData)
	ON_COMMAND(ID_32775, &CSignconDlg::OnViewOri)
	ON_COMMAND(ID_32776, &CSignconDlg::OnAdmin)
	ON_COMMAND(ID_32778, &CSignconDlg::OnBrowserByUser)
	ON_COMMAND(ID_32777, &CSignconDlg::OnHelp)
END_MESSAGE_MAP()


// CSignconDlg ��Ϣ�������

BOOL CSignconDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_RESTORE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CFileFind finder;   //�����Ƿ����ini�ļ����������ڣ�������һ���µ�Ĭ�����õ�ini�ļ��������ͱ�֤�����Ǹ��ĺ������ÿ�ζ�����  
	BOOL ifFind = finder.FindFile(_T("C:\\Program Files\\DBSetting.ini")); //����ini
	if (!ifFind)
	{
		AfxMessageBox("�����ļ������ڣ����ڹ���Աҳ���������ݿ��ַ��");
		::WritePrivateProfileString(_T("Database connection Info"), _T("IP"), _T("127.0.0.1"), _T("C:\\Program Files\\DBSetting.ini"));
		::WritePrivateProfileString(_T("Database connection Info"), _T("user"), _T("root"), _T("C:\\Program Files\\DBSetting.ini"));
		::WritePrivateProfileString(_T("Database connection Info"), _T("password"), _T("winmysql"), _T("C:\\Program Files\\DBSetting.ini"));
		::WritePrivateProfileString(_T("Database connection Info"), _T("port"), _T("3306"), _T("C:\\Program Files\\DBSetting.ini"));
		::WritePrivateProfileString(_T("Database connection Info"), _T("database"), _T("signconv"), _T("C:\\Program Files\\DBSetting.ini"));
		::WritePrivateProfileString(_T("Setting"), _T("tolerate"), _T("10"), _T("C:\\Program Files\\DBSetting.ini"));

	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSignconDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSignconDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSignconDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ���û��ر� UI ʱ������������Ա���������ĳ��
//  �������Զ�����������Ӧ�˳���  ��Щ
//  ��Ϣ�������ȷ����������: �����������ʹ�ã�
//  ������ UI�������ڹرնԻ���ʱ��
//  �Ի�����Ȼ�ᱣ�������

void CSignconDlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CSignconDlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void CSignconDlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CSignconDlg::CanExit()
{
	// �����������Ա�����������Զ���
	//  �������Իᱣ�ִ�Ӧ�ó���
	//  ʹ�Ի���������������� UI ����������
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}





void CSignconDlg::OnExportToExcel()
{
	// TODO: �ڴ���������������
	ExportDlg ex;
	ex.DoModal();
}


void CSignconDlg::OnImportData()
{
	// TODO: �ڴ���������������
	Operate op;
	op.Readfile();
}


void CSignconDlg::OnViewOri()
{
	// TODO: �ڴ���������������
	BrowserDlg bd;
	bd.DoModal();
}


void CSignconDlg::OnAdmin()
{
	// TODO: �ڴ���������������
	Login login;
	login.DoModal();
}


void CSignconDlg::OnBrowserByUser()
{
	// TODO: �ڴ���������������
	BrowserByUserDlg dlg;
	dlg.DoModal();
}


void CSignconDlg::OnHelp()
{
	// TODO: �ڴ���������������
	HelpDlg helpdlg;
	helpdlg.DoModal();
}
