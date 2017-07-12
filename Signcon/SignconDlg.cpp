
// SignconDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CSignconDlg 对话框


IMPLEMENT_DYNAMIC(CSignconDlg, CDialogEx);

CSignconDlg::CSignconDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SIGNCON_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CSignconDlg::~CSignconDlg()
{
	// 如果该对话框有自动化代理，则
	//  将此代理指向该对话框的后向指针设置为 NULL，以便
	//  此代理知道该对话框已被删除。
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


// CSignconDlg 消息处理程序

BOOL CSignconDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_RESTORE);

	// TODO: 在此添加额外的初始化代码
	CFileFind finder;   //查找是否存在ini文件，若不存在，则生成一个新的默认设置的ini文件，这样就保证了我们更改后的设置每次都可用  
	BOOL ifFind = finder.FindFile(_T("C:\\Program Files\\DBSetting.ini")); //查找ini
	if (!ifFind)
	{
		AfxMessageBox("配置文件不存在，请在管理员页面设置数据库地址。");
		::WritePrivateProfileString(_T("Database connection Info"), _T("IP"), _T("127.0.0.1"), _T("C:\\Program Files\\DBSetting.ini"));
		::WritePrivateProfileString(_T("Database connection Info"), _T("user"), _T("root"), _T("C:\\Program Files\\DBSetting.ini"));
		::WritePrivateProfileString(_T("Database connection Info"), _T("password"), _T("winmysql"), _T("C:\\Program Files\\DBSetting.ini"));
		::WritePrivateProfileString(_T("Database connection Info"), _T("port"), _T("3306"), _T("C:\\Program Files\\DBSetting.ini"));
		::WritePrivateProfileString(_T("Database connection Info"), _T("database"), _T("signconv"), _T("C:\\Program Files\\DBSetting.ini"));
		::WritePrivateProfileString(_T("Setting"), _T("tolerate"), _T("10"), _T("C:\\Program Files\\DBSetting.ini"));

	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSignconDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSignconDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 当用户关闭 UI 时，如果控制器仍保持着它的某个
//  对象，则自动化服务器不应退出。  这些
//  消息处理程序确保如下情形: 如果代理仍在使用，
//  则将隐藏 UI；但是在关闭对话框时，
//  对话框仍然会保留在那里。

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
	// 如果代理对象仍保留在那里，则自动化
	//  控制器仍会保持此应用程序。
	//  使对话框保留在那里，但将其 UI 隐藏起来。
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}





void CSignconDlg::OnExportToExcel()
{
	// TODO: 在此添加命令处理程序代码
	ExportDlg ex;
	ex.DoModal();
}


void CSignconDlg::OnImportData()
{
	// TODO: 在此添加命令处理程序代码
	Operate op;
	op.Readfile();
}


void CSignconDlg::OnViewOri()
{
	// TODO: 在此添加命令处理程序代码
	BrowserDlg bd;
	bd.DoModal();
}


void CSignconDlg::OnAdmin()
{
	// TODO: 在此添加命令处理程序代码
	Login login;
	login.DoModal();
}


void CSignconDlg::OnBrowserByUser()
{
	// TODO: 在此添加命令处理程序代码
	BrowserByUserDlg dlg;
	dlg.DoModal();
}


void CSignconDlg::OnHelp()
{
	// TODO: 在此添加命令处理程序代码
	HelpDlg helpdlg;
	helpdlg.DoModal();
}
