// DELETEDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "DELETEDlg.h"
#include "afxdialogex.h"
#include<atlimage.h>

// CDELETEDlg �Ի���

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


// CDELETEDlg ��Ϣ�������


void CDELETEDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
void CDELETEDlg::drawPicture(CStatic *m_Pic/*�ؼ�����*/)
{
	CRect rectPic;
	(*m_Pic).GetClientRect(&rectPic);     //m_pictureΪPicture Control�ؼ���������ÿؼ����������
	CDC* pDC = m_Pic->GetWindowDC();    //�����ʾ�ؼ���DC
	CImage *pImage = new CImage();//װ��ͼ�����
	CString filename = basePath + m_title;
	if (pImage->Load(filename) != E_FAIL){//�Ӵ���װ��ͼƬ,����ҳ�����õ���ͼƬ�±�
		int width = rectPic.Width();//��ʾ����Ŀ�͸�
		int height = rectPic.Height();

		int picW = pImage->GetWidth();//ͼƬ�Ŀ�͸�
		int picH = pImage->GetHeight();
		//�������ű�
		double r1 = double(picW) / double(width);
		double r2 = double(picH) / double(height);
		//rΪ�������ű���
		double r = (r1 >= r2 ? r1 : r2);

		//��ֹ���ź�ʧ��
		SetStretchBltMode(pDC->m_hDC, HALFTONE);
		SetBrushOrgEx(pDC->m_hDC, 0, 0, NULL);
		pImage->StretchBlt(pDC->m_hDC, 0, 0, int(picW / r), int(picH / r));
		//��ʾͼƬ
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
	// TODO:  �ڴ˴������Ϣ����������
	//��ʾ����ͼ��ʼ
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
	//----��ʾ����ͼ����

	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}


HBRUSH CDELETEDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


BOOL CDELETEDlg::PreTranslateMessage(MSG* pMsg)
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
