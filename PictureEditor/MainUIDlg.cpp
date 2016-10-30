// MainUIDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMainUIDlg �Ի���




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


// CMainUIDlg ��Ϣ�������

BOOL CMainUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�

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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMainUIDlg::OnPaint()
{
	CPaintDC dc(this);

	//��ʾ����ͼ��ʼ
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
	//----��ʾ����ͼ����

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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CLOSearchDlg loSearchDlg(NULL, &picLibrary);
	loSearchDlg.DoModal();
}


void CMainUIDlg::OnBnClickedButtonInsert()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CINSERTDlg insDlg(NULL, &picLibrary);
	insDlg.DoModal();
}


void CMainUIDlg::OnBnClickedButtonRemove()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDELETEDlg delDlg(NULL, &picLibrary);
	delDlg.DoModal();
}


void CMainUIDlg::OnBnClickedButtonReplace()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CREPLACE repDlg(NULL, &picLibrary);
	repDlg.DoModal();
}


void CMainUIDlg::OnBnClickedButtonTesting()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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

	// TODO:  �ڴ˸��� DC ���κ�����
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);   //���ñ���͸��   
		return   HBRUSH(GetStockObject(HOLLOW_BRUSH));
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CMainUIDlg::OnBnClickedButton2()
{
	ofstream myFile("MyInfo.csv");
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	tmp = "�ɹ�������ȫ��";
	tmp += CString(num);
	tmp += CString("��");
	MessageBox(tmp);
}


BOOL CMainUIDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN) {

		switch (pMsg->wParam) {

		case VK_RETURN: //�س�  

			return TRUE;

		case VK_ESCAPE: //ESC  

			return TRUE;

		}

	}
	return CDialog::PreTranslateMessage(pMsg);
}
