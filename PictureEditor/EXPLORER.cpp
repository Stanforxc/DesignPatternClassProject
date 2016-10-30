// EXPLORER.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "EXPLORER.h"
#include "afxdialogex.h"
#include<atlimage.h>
#include"PicShow.h"
// CEXPLORER 对话框

IMPLEMENT_DYNAMIC(CEXPLORER, CDialog)

CEXPLORER::CEXPLORER(CWnd* pParent /*=NULL*/)
	: CDialog(CEXPLORER::IDD, pParent)
{

}
CEXPLORER::CEXPLORER(CWnd* pParent /*=NULL*/,PictureInfoList *ptr)
	: CDialog(CEXPLORER::IDD, pParent)
{
	picListPtr = ptr;
}

CEXPLORER::~CEXPLORER()
{
}

void CEXPLORER::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Pic1, m_Pic1);
	DDX_Control(pDX, IDC_Pic2, m_Pic2);
	DDX_Control(pDX, IDC_Pic3, m_Pic3);
	DDX_Control(pDX, IDC_Pic4, m_Pic4);
}


BEGIN_MESSAGE_MAP(CEXPLORER, CDialog)
	ON_STN_CLICKED(IDC_Pic1, &CEXPLORER::OnStnClickedPic1)
	ON_BN_CLICKED(IDC_BUTTON1, &CEXPLORER::OnBnClickedButton1)
	ON_STN_CLICKED(IDC_Pic2, &CEXPLORER::OnStnClickedPic2)
	ON_STN_CLICKED(IDC_Pic3, &CEXPLORER::OnStnClickedPic3)
	ON_STN_CLICKED(IDC_Pic4, &CEXPLORER::OnStnClickedPic4)
	ON_BN_CLICKED(IDC_BUTTON2, &CEXPLORER::OnBnClickedButton2)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CEXPLORER 消息处理程序


void CEXPLORER::OnStnClickedPic1()
{
	// TODO:  在此添加控件通知处理程序代码
	int pos = currentPage*numInPages + 0;
	CString filepath = filenames[pos];
	CPicShow a(NULL, filepath, picListPtr);
	a.DoModal();
}


void CEXPLORER::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	if (currentPage > 0){
		currentPage--;
		if (m_Pic1.IsWindowVisible() == false)
			m_Pic1.ShowWindow(SW_SHOW);
		if (m_Pic2.IsWindowVisible() == false)
			m_Pic2.ShowWindow(SW_SHOW);
		if (m_Pic3.IsWindowVisible() == false)
			m_Pic3.ShowWindow(SW_SHOW);
		if (m_Pic4.IsWindowVisible() == false)
			m_Pic4.ShowWindow(SW_SHOW);


		CRect rect;

		GetDlgItem(IDC_Pic1)->GetWindowRect(&rect);
		ScreenToClient(rect);
		InvalidateRect(&rect);

		GetDlgItem(IDC_Pic2)->GetWindowRect(&rect);
		ScreenToClient(rect);
		InvalidateRect(&rect);

		GetDlgItem(IDC_Pic3)->GetWindowRect(&rect);
		ScreenToClient(rect);
		InvalidateRect(&rect);

		GetDlgItem(IDC_Pic4)->GetWindowRect(&rect);
		ScreenToClient(rect);
		InvalidateRect(&rect);
		//InvalidateRect(CRect(109,14,165,75), true);//强制刷新
	}
	else
		MessageBox(_T("已经是第一张了！"));
}


void CEXPLORER::OnStnClickedPic2()
{
	// TODO:  在此添加控件通知处理程序代码
	int pos = currentPage*numInPages + 1;
	CString filepath = filenames[pos];
	CPicShow a(NULL, filepath, picListPtr);
	a.DoModal();
}


void CEXPLORER::OnStnClickedPic3()
{
	// TODO:  在此添加控件通知处理程序代码
	int pos = currentPage*numInPages + 2;
	CString filepath = filenames[pos];
	CPicShow a(NULL, filepath, picListPtr);
	a.DoModal();
}


void CEXPLORER::OnStnClickedPic4()
{
	// TODO:  在此添加控件通知处理程序代码
	int pos = currentPage*numInPages + 3;
	CString filepath = filenames[pos];
	CPicShow a(NULL, filepath, picListPtr);
	a.DoModal();
}


void CEXPLORER::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	if (currentPage < count / numInPages && (currentPage + 1)*numInPages<count) {
		currentPage++;

		CRect rect;

		GetDlgItem(IDC_Pic1)->GetWindowRect(&rect);
		ScreenToClient(rect);
		InvalidateRect(&rect);

		GetDlgItem(IDC_Pic2)->GetWindowRect(&rect);
		ScreenToClient(rect);
		InvalidateRect(&rect);

		GetDlgItem(IDC_Pic3)->GetWindowRect(&rect);
		ScreenToClient(rect);
		InvalidateRect(&rect);

		GetDlgItem(IDC_Pic4)->GetWindowRect(&rect);
		ScreenToClient(rect);
		InvalidateRect(&rect);

		//InvalidateRect(CRect(109,14,165,75), true);//强制刷新
	}
	else
		MessageBox(_T("已经是最后第一张了！"));
}


BOOL CEXPLORER::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	basePath = ".\\picLibrary\\";
	currentPage = 0;
	numInPages = 4;
	count = picListPtr->size();

	//初始时从List中获取所有的文件名
	for (int i = 0; i<count; i++){
		PictureRecord picRec;
		picListPtr->retrieve(i, picRec);
		filenames[i] = picRec.the_key().c_str();
		//filenames[i] = basePath + filenames[i];

	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CEXPLORER::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	CDialog::OnPaint();


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

	drawPicture(&m_Pic1, 0);
	drawPicture(&m_Pic2, 1);
	drawPicture(&m_Pic3, 2);
	drawPicture(&m_Pic4, 3);
	// 不为绘图消息调用 CDialog::OnPaint()
}
void CEXPLORER::drawPicture(CStatic* m_Pic/*控件名称*/, int no/*控件编号0-n-1*/){

	CRect rectPic;
	(*m_Pic).GetClientRect(&rectPic);     //m_Picture为Picture Control控件变量，获得控件的区域对象
	CDC* pDC = m_Pic->GetWindowDC();    //获得显示控件的DC

	CImage *pImage = new CImage();//装载图像的类

	int pos = currentPage*numInPages + no;
	CString filepath = basePath + filenames[pos];
	if (pos< count){ //还有图片可以显示
		if (pImage->Load(filepath) != E_FAIL){//从磁盘装载图片,根据页面计算得到的图片下标
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
			string b = (CStringA)filenames[pos];
			picListPtr->searchByKey(b, a);
			picListPtr->remove(a);
		}
	}
	else{
		m_Pic->ShowWindow(SW_HIDE);
	}
}

HBRUSH CEXPLORER::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


BOOL CEXPLORER::PreTranslateMessage(MSG* pMsg)
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
