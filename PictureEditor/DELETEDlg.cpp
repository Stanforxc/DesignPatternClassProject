// DELETEDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DELETEDlg.h"
#include "afxdialogex.h"
#include<atlimage.h>

// CDELETEDlg 对话框

IMPLEMENT_DYNAMIC(CDELETEDlg, CDialog)

CDELETEDlg::CDELETEDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDELETEDlg::IDD, pParent)
	, m_title(_T(""))
{

}
CDELETEDlg::CDELETEDlg(CWnd* pParent /*=NULL*/,PictureInfoList *ptr)
	: CDialog(CDELETEDlg::IDD, pParent)
{
	picListptr = ptr;
}
CDELETEDlg::~CDELETEDlg()
{
}

void CDELETEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_title);
	DDX_Control(pDX, IDC_Pic1, m_Pic1);
	DDX_Control(pDX, IDC_Pic1, m_Pic1);
}


BEGIN_MESSAGE_MAP(CDELETEDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON3, &CDELETEDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CDELETEDlg::OnBnClickedButton1)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDELETEDlg 消息处理程序


void CDELETEDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码

	PictureRecord a;
	string title = (CStringA)m_title;
	if (picListptr->searchByKey(title, a) == notPresent)
	{
		MessageBox(_T("The photo doesn't exist"));
		return;
	}
	else
	{
		MessageBox(_T("Are you sure to delete the Picture? "));
		picListptr->remove(a);
		MessageBox(_T("The photo has been deleted successfully"));
		
	}
}


void CDELETEDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	PictureRecord a;
	string title = (CStringA)m_title;
	if (picListptr->searchByKey(title, a) == notPresent)
	{
		MessageBox(_T("The photo doesn't exist"));
	}
	else
	{
		
		m_title = a.the_key().c_str();
		UpdateData(FALSE);
		drawPicture(&m_Pic1);
	}
}


BOOL CDELETEDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	basePath = ".\\picLibrary\\";

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
void CDELETEDlg::drawPicture(CStatic *m_Pic/*控件名称*/)
{
	CRect rectPic;
	(*m_Pic).GetClientRect(&rectPic);     //m_picture为Picture Control控件变量，获得控件的区域对象
	CDC* pDC = m_Pic->GetWindowDC();    //获得显示控件的DC
	CImage *pImage = new CImage();//装载图像的类
	CString filename = basePath + m_title;
	if (pImage->Load(filename) != E_FAIL){//从磁盘装载图片,根据页面计算得到的图片下标
		int width = rectPic.Width();//显示区域的宽和高
		int height = rectPic.Height();

		int picW = pImage->GetWidth();//图片的宽和高
		int picH = pImage->GetHeight();
		//计算缩放比
		double r1 = double(picW) / double(width);
		double r2 = double(picH) / double(height);
		//r为最优缩放比例
		double r = (r1 >= r2 ? r1 : r2);

		//防止缩放后失真
		SetStretchBltMode(pDC->m_hDC, HALFTONE);
		SetBrushOrgEx(pDC->m_hDC, 0, 0, NULL);
		pImage->StretchBlt(pDC->m_hDC, 0, 0, int(picW / r), int(picH / r));
		//显示图片
		pImage->Draw(pDC->m_hDC, 0, 0, int(picW / r), int(picH / r));


		ReleaseDC(pDC);
		delete pImage;
	}
	else
	{
		MessageBox(_T("Load file fail"));
		PictureRecord a;
		string b = (CStringA)m_title;
		picListptr->searchByKey(b, a);
		picListptr->remove(a);
		m_Pic->ShowWindow(SW_HIDE);
	}
	
}


void CDELETEDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	//显示背景图开始
	CRect rect;
	GetClientRect(&rect);
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP3);

	BITMAP bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap* pbmpPri = dcMem.SelectObject(&bmpBackground);
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
	//----显示背景图结束

	// 不为绘图消息调用 CDialog::OnPaint()
}


HBRUSH CDELETEDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


BOOL CDELETEDlg::PreTranslateMessage(MSG* pMsg)
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
