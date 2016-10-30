// REPLACE.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "REPLACE.h"
#include "afxdialogex.h"
#include<atlimage.h>

// CREPLACE �Ի���

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


// CREPLACE ��Ϣ�������


void CREPLACE::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	MessageBox(_T("�Ƿ�ȷ���޸�"), 0, MB_OKCANCEL);
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
		MessageBox(_T("�޸ĳɹ�"));
	}
	
}
void CREPLACE::drawPicture(CStatic *m_Pic/*�ؼ�����*/)
{
	CRect rectPic;
	(*m_Pic).GetClientRect(&rectPic);     //m_pictureΪPicture Control�ؼ���������ÿؼ����������
	CDC* pDC = m_Pic->GetWindowDC();    //�����ʾ�ؼ���DC
	CImage *pImage = new CImage();//װ��ͼ�����
	
	CString file = basepath + m_filename;
	if (pImage->Load((file)) != E_FAIL){//�Ӵ���װ��ͼƬ,����ҳ�����õ���ͼƬ�±�
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
		string b = (CStringA)m_filename;
		picListptr->searchByKey(b, a);
		picListptr->remove(a);
	}
}

BOOL CREPLACE::OnInitDialog()
{
	CDialog::OnInitDialog();
	UpdateData(FALSE);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	basepath = ".\\picLibrary\\";
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


HBRUSH CREPLACE::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CREPLACE::OnPaint()
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


BOOL CREPLACE::PreTranslateMessage(MSG* pMsg)
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
