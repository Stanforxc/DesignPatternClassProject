// NewFootMarkDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "NewFootMarkDlg.h"
#include "afxdialogex.h"
#include"FootMarkShow.h"

// CNewFootMarkDlg �Ի���

IMPLEMENT_DYNAMIC(CNewFootMarkDlg, CDialog)

CNewFootMarkDlg::CNewFootMarkDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewFootMarkDlg::IDD, pParent)
{

}
CNewFootMarkDlg::CNewFootMarkDlg(CWnd* pParent /*=NULL*/,PictureInfoList*ptr)
	: CDialog(CNewFootMarkDlg::IDD, pParent)
{
	picLibraryPtr = ptr;
}
CNewFootMarkDlg::~CNewFootMarkDlg()
{
}

void CNewFootMarkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNewFootMarkDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CNewFootMarkDlg ��Ϣ�������


void CNewFootMarkDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CDialog::OnPaint();
	//��ʾ����ͼ��ʼ
	CRect rect;
	GetClientRect(&rect);
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP2);

	BITMAP bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap* pbmpPri = dcMem.SelectObject(&bmpBackground);
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);


	//�����㼣��Ϣ    
	int count = ecnuMap.get_verterxCount();
	VertexRecord vr; //ͼ�нڵ��¼
	const List <const Node<PictureRecord >  *>* trackListPtr = NULL;//ͼ�е��Ӧ����Ƭ����
	//���λ��Ƶ�ͼ��ÿ���ڵ����Ƭ���� 
	for (int i = 0; i<count; i++){
		ecnuMap.get_trackByIndex(i, vr, trackListPtr);
		if (trackListPtr != NULL&&trackListPtr->size()>0){
			dc.Ellipse(vr.the_x() - 3, vr.the_y() - 3, vr.the_x() + 3, vr.the_y() + 3);//Χ�����ĵ㻭��Բ�Σ�
			dc.SetTextColor(RGB(255, 0, 0));

			CString tmp;
			tmp.Format(_T("%d"), trackListPtr->size());//��������
			dc.TextOut(vr.the_x() - 2, vr.the_y(), tmp);


		}
	}
}


BOOL CNewFootMarkDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//����ͼ�������ʾͼ�Ρ�877��740
	CRect   temprect(0, 0, 1118, 700);
	CWnd::SetWindowPos(NULL, 0, 0, temprect.Width(), temprect.Height(), SWP_NOZORDER | SWP_NOMOVE);

	if (ecnuMap.Initialize("�й�", "China") == success){
		MessageBox(_T("OK,Now map is initialized."));

	}
	else{

		MessageBox(_T("error,map load failed."));

	}
	//���ҵõ��㼣
	picLibraryPtr->searchByFootmark(ecnuMap);
	return TRUE;
}


void CNewFootMarkDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int no, index;
	//�ҵ��û����λ�ö�Ӧ�ĵ�ͼ�еĽڵ���no�ʹ洢�±�index
	ecnuMap.positionToNum(point.x, point.y, index, no);

	VertexRecord vr; //ͼ�нڵ��¼
	const List <const Node<PictureRecord >  *>*     trackListPtr = NULL;//ͼ�е��Ӧ����Ƭ����
	//��øýڵ��Ӧ����Ƭ��Ϣ
	ecnuMap.get_trackByIndex(index, vr, trackListPtr);
	CFootMarkShow a(NULL, trackListPtr,picLibraryPtr);
	a.DoModal();
	
	CDialog::OnLButtonDown(nFlags, point);
}


BOOL CNewFootMarkDlg::PreTranslateMessage(MSG* pMsg)
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
