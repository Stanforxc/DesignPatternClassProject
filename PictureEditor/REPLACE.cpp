// REPLACE.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "REPLACE.h"
#include "afxdialogex.h"
#include<atlimage.h>

// CREPLACE 对话框

IMPLEMENT_DYNAMIC(CREPLACE, CDialog)

CREPLACE::CREPLACE(CWnd* pParent /*=NULL*/)
	: CDialog(CREPLACE::IDD, pParent)
	, m_detail(_T(""))
	, m_filename(_T(""))
	, m_titleEn(_T(""))
	, m_map(_T(""))
	, m_location(_T(""))
	, m_hmap(_T(""))
	, m_hlocation(_T(""))
	, m_owner(_T(""))
{

}
CREPLACE::CREPLACE(CWnd* pParent /*=NULL*/,PictureInfoList *ptr)
	: CDialog(CREPLACE::IDD, pParent)
{
	picListptr = ptr;
}
CREPLACE::CREPLACE(CWnd* pParent /*=NULL*/, PictureInfoList *ptr,CString filename )
	: CDialog(CREPLACE::IDD, pParent)
{
	picListptr = ptr;
	m_filename = filename;

}
CREPLACE::~CREPLACE()
{
}

void CREPLACE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_detail);
	DDX_Text(pDX, IDC_EDIT1, m_filename);
	DDX_Text(pDX, IDC_EDIT3, m_titleEn);
	DDX_Text(pDX, IDC_EDIT4, m_map);
	DDX_Text(pDX, IDC_EDIT5, m_location);
	//  DDX_Control(pDX, IDC_EDIT6, m_hmap);
	DDX_Text(pDX, IDC_EDIT6, m_hmap);
	DDX_Text(pDX, IDC_EDIT7, m_hlocation);
	DDX_Text(pDX, IDC_EDIT8, m_owner);
	DDX_Control(pDX, IDC_Pic1, m_pic1);
}


BEGIN_MESSAGE_MAP(CREPLACE, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CREPLACE::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CREPLACE::OnBnClickedButton2)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CREPLACE 消息处理程序


void CREPLACE::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	string filename = (CStringA)m_filename;
	if (picListptr->searchByKey(filename, a) == notPresent)
	{
		MessageBox(_T("filename error"));
	}
	else
	{
		m_filename = a.the_key().c_str();
		m_detail = a.the_detail().c_str();
		m_titleEn = a.the_titleEn().c_str();
		m_map = a.the_map().c_str();
		m_location = a.the_location().c_str();
		m_hmap = a.the_hmap().c_str();
		m_hlocation = a.the_hlocation().c_str();
		m_owner = a.the_owner().c_str();
		UpdateData(FALSE);
		drawPicture(&m_pic1);
	}
}


void CREPLACE::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	MessageBox(_T("是否确认修改"), 0, MB_OKCANCEL);
	UpdateData(TRUE);
	OthersType the_new_others = a.the_others();
	the_new_others.detail =(CStringA)m_detail;
	the_new_others.titleEn = (CStringA)m_titleEn;
	the_new_others.map = (CStringA)m_map;
	the_new_others.location = (CStringA)m_location;
	the_new_others.hmap = (CStringA)m_hmap;
	the_new_others.hlocation = (CStringA)m_hlocation;
	the_new_others.owner = (CStringA)m_owner;
	string filename = (CStringA)m_filename;
	PictureRecord new_item(filename, the_new_others);
	if (picListptr->replace(new_item)==success)
	{
		MessageBox(_T("修改成功"));
	}
	
}
void CREPLACE::drawPicture(CStatic *m_Pic/*控件名称*/)
{
	CRect rectPic;
	(*m_Pic).GetClientRect(&rectPic);     //m_picture为Picture Control控件变量，获得控件的区域对象
	CDC* pDC = m_Pic->GetWindowDC();    //获得显示控件的DC
	CImage *pImage = new CImage();//装载图像的类
	
	CString file = basepath + m_filename;
	if (pImage->Load((file)) != E_FAIL){//从磁盘装载图片,根据页面计算得到的图片下标
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
		string b = (CStringA)m_filename;
		picListptr->searchByKey(b, a);
		picListptr->remove(a);
	}
}

BOOL CREPLACE::OnInitDialog()
{
	CDialog::OnInitDialog();
	UpdateData(FALSE);
	// TODO:  在此添加额外的初始化
	basepath = ".\\picLibrary\\";
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


HBRUSH CREPLACE::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CREPLACE::OnPaint()
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


BOOL CREPLACE::PreTranslateMessage(MSG* pMsg)
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
