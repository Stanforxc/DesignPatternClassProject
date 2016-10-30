// FootMarkdlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "FootMarkdlg.h"
#include"FootMarkShow.h"

// CFootMarkdlg 对话框

IMPLEMENT_DYNAMIC(CFootMarkdlg, CDialog)

CFootMarkdlg::CFootMarkdlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFootMarkdlg::IDD, pParent)
{

}
CFootMarkdlg::CFootMarkdlg(CWnd* pParent /*=NULL*/,PictureInfoList *ptr)
	: CDialog(CFootMarkdlg::IDD, pParent)
{
	picLibraryPtr = ptr;
}
CFootMarkdlg::~CFootMarkdlg()
{
}

void CFootMarkdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFootMarkdlg, CDialog)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CFootMarkdlg 消息处理程序

void CFootMarkdlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CDialog::OnPaint();
	//显示背景图开始
	CRect rect;
	GetClientRect(&rect);
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP1);

	BITMAP bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap* pbmpPri = dcMem.SelectObject(&bmpBackground);
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);


	//绘制足迹信息    
	int count = ecnuMap.get_verterxCount();
	VertexRecord vr; //图中节点记录
	const List <const Node<PictureRecord >  *>* trackListPtr = NULL;//图中点对应的照片集合
	//依次绘制地图上每个节点的照片数量 
	for (int i = 0; i<count; i++){
		ecnuMap.get_trackByIndex(i, vr, trackListPtr);
		if (trackListPtr != NULL&&trackListPtr->size()>0){
			dc.Ellipse(vr.the_x() - 10, vr.the_y() - 10, vr.the_x() + 10, vr.the_y() + 10);//围绕中心点画个圆形；
			dc.SetTextColor(RGB(255, 0, 0));

			CString tmp;
			tmp.Format(_T("%d"), trackListPtr->size());//绘制数量
			dc.TextOut(vr.the_x() - 8, vr.the_y(), tmp);


		}
	}
	

}

BOOL CFootMarkdlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//按照图像比例显示图形。877×740
	CRect   temprect(0, 0, 877, 740);
	CWnd::SetWindowPos(NULL, 0, 0, temprect.Width(), temprect.Height(), SWP_NOZORDER | SWP_NOMOVE);

	if (ecnuMap.Initialize("华师大", "ecnu") == success){
		MessageBox(_T("OK,Now map is initialized."));

	}
	else{

		MessageBox(_T("error,map load failed."));

	}
	//查找得到足迹
	picLibraryPtr->searchByFootmark(ecnuMap);
	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}


void CFootMarkdlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	int no, index;
	//找到用户点击位置对应的地图中的节点编号no和存储下标index
	ecnuMap.positionToNum(point.x, point.y, index, no);

	VertexRecord vr; //图中节点记录
	const List <const Node<PictureRecord >  *>*     trackListPtr = NULL;//图中点对应的照片集合
	//获得该节点对应的照片信息
	ecnuMap.get_trackByIndex(index, vr, trackListPtr);
	
	CFootMarkShow a(NULL,trackListPtr,picLibraryPtr);
	a.DoModal();
	CDialog::OnLButtonDown(nFlags, point);
}


BOOL CFootMarkdlg::PreTranslateMessage(MSG* pMsg)
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
