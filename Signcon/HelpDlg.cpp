// HelpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Signcon.h"
#include "HelpDlg.h"
#include "afxdialogex.h"


// HelpDlg �Ի���

IMPLEMENT_DYNAMIC(HelpDlg, CDialogEx)

HelpDlg::HelpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HELP, pParent)
{

}

HelpDlg::~HelpDlg()
{
}

void HelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(HelpDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &HelpDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// HelpDlg ��Ϣ�������


void HelpDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
	if (DeleteFile("C:\\Program Files\\DBSetting.ini"))
	{
		AfxMessageBox("������ɣ������󼴿���������");
		PostMessage(WM_QUIT, 0, 0);
	}
}
