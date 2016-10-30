// Login.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "Login.h"
#include "afxdialogex.h"


// CLogin 对话框

IMPLEMENT_DYNAMIC(CLogin, CDialogEx)

CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogin::IDD, pParent)
	, m_password(_T(""))
{

}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_password);
}


BEGIN_MESSAGE_MAP(CLogin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CLogin::OnBnClickedButton1)
//	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CLogin 消息处理程序


void CLogin::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_password == password)
	{
		CDialog::OnOK();
	}
	else
	{
		MessageBox(_T("密码错误"));
	}

}


BOOL CLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	password = "1234";
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


//void CLogin::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO:  在此添加消息处理程序代码和/或调用默认值
//
//	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
//}


BOOL CLogin::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN) {

		switch (pMsg->wParam) {

		case VK_RETURN: //回车  

			return TRUE;

		case VK_ESCAPE: //ESC  

			return TRUE;

		}

	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
