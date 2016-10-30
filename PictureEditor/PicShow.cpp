// PicShow.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "PicShow.h"
#include "afxdialogex.h"
#include<atlimage.h>
#include"REPLACE.h"
// CPicShow 对话框

IMPLEMENT_DYNAMIC(CPicShow, CDialog)

CPicShow::CPicShow(CWnd* pParent /*=NULL*/)
	: CDialog(CPicShow::IDD, pParent)
{

}

CPicShow::CPicShow(CWnd* pParent, CString filename, PictureInfoList*ptr)
	: CDialog(CPicShow::IDD, pParent)
{
	this->filename = filename;
	this->picListptr = ptr;
}
CPicShow::~CPicShow()
{
}

void CPicShow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Pic1, m_Pic1);
}


BEGIN_MESSAGE_MAP(CPicShow, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &CPicShow::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPicShow::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CPicShow::OnBnClickedButton3)
END_MESSAGE_MAP()


// CPicShow 消息处理程序
void CPicShow::drawPicture(CStatic *m_Pic/*控件名称*/)
{

	CRect rectPic;
	(*m_Pic).GetClientRect(&rectPic);     //m_picture为Picture Control控件变量，获得控件的区域对象
	CDC* pDC = m_Pic->GetWindowDC();    //获得显示控件的DC
	CImage *pImage = new CImage();//装载图像的类
	CString filenames = basePath+filename;
	if (pImage->Load(filenames) != E_FAIL){//从磁盘装载图片,根据页面计算得到的图片下标
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
		string b = (CStringA)filename;
		picListptr->searchByKey(b, a);
		picListptr->remove(a);
	}
}


BOOL CPicShow::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	basePath = ".\\picLibrary\\";
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CPicShow::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	drawPicture(&m_Pic1);
	// 不为绘图消息调用 CDialog::OnPaint()

}


void CPicShow::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	CREPLACE a(NULL,picListptr,filename);
	a.DoModal();
}


void CPicShow::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	PictureRecord a;
	string key = (CStringA)filename;
	picListptr->searchByKey(key, a);
	picListptr->remove(a);
	MessageBox(_T("删除成功"));
}


void CPicShow::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialog::OnOK();
}
