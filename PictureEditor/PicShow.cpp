// PicShow.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "PicShow.h"
#include "afxdialogex.h"
#include<atlimage.h>
#include"REPLACE.h"
// CPicShow �Ի���

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


// CPicShow ��Ϣ�������
void CPicShow::drawPicture(CStatic *m_Pic/*�ؼ�����*/)
{

	CRect rectPic;
	(*m_Pic).GetClientRect(&rectPic);     //m_pictureΪPicture Control�ؼ���������ÿؼ����������
	CDC* pDC = m_Pic->GetWindowDC();    //�����ʾ�ؼ���DC
	CImage *pImage = new CImage();//װ��ͼ�����
	CString filenames = basePath+filename;
	if (pImage->Load(filenames) != E_FAIL){//�Ӵ���װ��ͼƬ,����ҳ�����õ���ͼƬ�±�
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
		string b = (CStringA)filename;
		picListptr->searchByKey(b, a);
		picListptr->remove(a);
	}
}


BOOL CPicShow::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	basePath = ".\\picLibrary\\";
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CPicShow::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	drawPicture(&m_Pic1);
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()

}


void CPicShow::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CREPLACE a(NULL,picListptr,filename);
	a.DoModal();
}


void CPicShow::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	PictureRecord a;
	string key = (CStringA)filename;
	picListptr->searchByKey(key, a);
	picListptr->remove(a);
	MessageBox(_T("ɾ���ɹ�"));
}


void CPicShow::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}
