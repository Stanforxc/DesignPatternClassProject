// MainUIDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "MainUIDlg.h"
#include"EXPLORER.h"
#include "FootMarkdlg.h"
#include "TLSearchDlg.h"
#include"LOSearchDlg.h"
#include"INSERTDlg.h"
#include"DELETEDlg.h"
#include"REPLACE.h"
#include"NewFootMarkDlg.h"
#include"TimeTest.h"
#include"Login.h"
#include<fstream>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMainUIDlg 对话框




CMainUIDlg::CMainUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainUIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMainUIDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_SearchByTitle, &CMainUIDlg::OnBnClickedButtonSearchbytitle)
	ON_BN_CLICKED(IDC_BUTTON_explore, &CMainUIDlg::OnBnClickedButtonexplore)
	ON_BN_CLICKED(IDC_BUTTON_Track, &CMainUIDlg::OnBnClickedButtonTrack)
	ON_BN_CLICKED(IDC_BUTTON_SearchByLoc, &CMainUIDlg::OnBnClickedButtonSearchbyloc)
	ON_BN_CLICKED(IDC_BUTTON_Insert, &CMainUIDlg::OnBnClickedButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_Remove, &CMainUIDlg::OnBnClickedButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON_Replace, &CMainUIDlg::OnBnClickedButtonReplace)
	ON_BN_CLICKED(IDC_BUTTON_Testing, &CMainUIDlg::OnBnClickedButtonTesting)
	ON_BN_CLICKED(IDC_BUTTON1, &CMainUIDlg::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON2, &CMainUIDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMainUIDlg 消息处理程序

BOOL CMainUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CLogin a;
	a.DoModal();
	basepath = ".\\picLibrary\\";
    if(picLibrary.initialization()==success){	   
		for (int i = 0; i < picLibrary.size(); i++)
		{
			PictureRecord file;
			picLibrary.retrieve(i, file);
			CString filename = basepath;
			filename += file.the_key().c_str();
			CFileFind filefind;
			if (!filefind.FindFile(filename))
			{
				picLibrary.remove(file);
			}
		}
		
	MessageBox(TEXT("OK,Now photo List is initialized."));
	}else{
	    MessageBox(TEXT("Error in Photo List initializing."));
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CMainUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMainUIDlg::OnPaint()
{
	CPaintDC dc(this);

	//显示背景图开始
	CRect rect;
	GetClientRect(&rect);
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP5);

	BITMAP bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap* pbmpPri = dcMem.SelectObject(&bmpBackground);
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
	//----显示背景图结束

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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMainUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMainUIDlg::OnBnClickedButtonSearchbytitle()
{
	// TODO: Add your control notification handler code here
	CTLSearchDlg tlSearchDlg(NULL, &picLibrary);
	tlSearchDlg.DoModal();
}

void CMainUIDlg::OnBnClickedButtonexplore()
{
	// TODO: 
	CEXPLORER a(NULL, &picLibrary);
	a.DoModal();
}

void CMainUIDlg::OnBnClickedButtonTrack()
{
	// TODO:
	CNewFootMarkDlg footMarkdlg(NULL,&picLibrary);
	footMarkdlg.DoModal();

}



void CMainUIDlg::OnBnClickedButtonSearchbyloc()
{
	// TODO:  在此添加控件通知处理程序代码
	CLOSearchDlg loSearchDlg(NULL, &picLibrary);
	loSearchDlg.DoModal();
}


void CMainUIDlg::OnBnClickedButtonInsert()
{
	// TODO:  在此添加控件通知处理程序代码
	CINSERTDlg insDlg(NULL, &picLibrary);
	insDlg.DoModal();
}


void CMainUIDlg::OnBnClickedButtonRemove()
{
	// TODO:  在此添加控件通知处理程序代码
	CDELETEDlg delDlg(NULL, &picLibrary);
	delDlg.DoModal();
}


void CMainUIDlg::OnBnClickedButtonReplace()
{
	// TODO:  在此添加控件通知处理程序代码
	CREPLACE repDlg(NULL, &picLibrary);
	repDlg.DoModal();
}


void CMainUIDlg::OnBnClickedButtonTesting()
{
	// TODO:  在此添加控件通知处理程序代码
	CTimeTest a;
	a.DoModal();
}


void CMainUIDlg::OnBnClickedButton1()
{
	CFootMarkdlg a(NULL, &picLibrary);
	a.DoModal();
}


HBRUSH CMainUIDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);   //设置背景透明   
		return   HBRUSH(GetStockObject(HOLLOW_BRUSH));
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CMainUIDlg::OnBnClickedButton2()
{
	ofstream myFile("MyInfo.csv");
	// TODO:  在此添加控件通知处理程序代码
	int i;
	for (i = 0; i < picLibrary.size(); i++)
	{
		PictureRecord a;
		picLibrary.retrieve(i, a);
		myFile << a;
	}
	CString tmp;
	char num[10];
	tmp = _itoa(i, num, 10);
	tmp = "成功保存了全部";
	tmp += CString(num);
	tmp += CString("项");
	MessageBox(tmp);
}


BOOL CMainUIDlg::PreTranslateMessage(MSG* pMsg)
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
	return CDialog::PreTranslateMessage(pMsg);
}
