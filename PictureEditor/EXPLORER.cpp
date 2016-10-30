// EXPLORER.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "EXPLORER.h"
#include "afxdialogex.h"
#include<atlimage.h>
#include"PicShow.h"
// CEXPLORER �Ի���

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


// CEXPLORER ��Ϣ�������


void CEXPLORER::OnStnClickedPic1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int pos = currentPage*numInPages + 0;
	CString filepath = filenames[pos];
	CPicShow a(NULL, filepath, picListPtr);
	a.DoModal();
}


void CEXPLORER::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
		//InvalidateRect(CRect(109,14,165,75), true);//ǿ��ˢ��
	}
	else
		MessageBox(_T("�Ѿ��ǵ�һ���ˣ�"));
}


void CEXPLORER::OnStnClickedPic2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int pos = currentPage*numInPages + 1;
	CString filepath = filenames[pos];
	CPicShow a(NULL, filepath, picListPtr);
	a.DoModal();
}


void CEXPLORER::OnStnClickedPic3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int pos = currentPage*numInPages + 2;
	CString filepath = filenames[pos];
	CPicShow a(NULL, filepath, picListPtr);
	a.DoModal();
}


void CEXPLORER::OnStnClickedPic4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int pos = currentPage*numInPages + 3;
	CString filepath = filenames[pos];
	CPicShow a(NULL, filepath, picListPtr);
	a.DoModal();
}


void CEXPLORER::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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

		//InvalidateRect(CRect(109,14,165,75), true);//ǿ��ˢ��
	}
	else
		MessageBox(_T("�Ѿ�������һ���ˣ�"));
}


BOOL CEXPLORER::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	basePath = ".\\picLibrary\\";
	currentPage = 0;
	numInPages = 4;
	count = picListPtr->size();

	//��ʼʱ��List�л�ȡ���е��ļ���
	for (int i = 0; i<count; i++){
		PictureRecord picRec;
		picListPtr->retrieve(i, picRec);
		filenames[i] = picRec.the_key().c_str();
		//filenames[i] = basePath + filenames[i];

	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CEXPLORER::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	CDialog::OnPaint();


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

	drawPicture(&m_Pic1, 0);
	drawPicture(&m_Pic2, 1);
	drawPicture(&m_Pic3, 2);
	drawPicture(&m_Pic4, 3);
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}
void CEXPLORER::drawPicture(CStatic* m_Pic/*�ؼ�����*/, int no/*�ؼ����0-n-1*/){

	CRect rectPic;
	(*m_Pic).GetClientRect(&rectPic);     //m_PictureΪPicture Control�ؼ���������ÿؼ����������
	CDC* pDC = m_Pic->GetWindowDC();    //�����ʾ�ؼ���DC

	CImage *pImage = new CImage();//װ��ͼ�����

	int pos = currentPage*numInPages + no;
	CString filepath = basePath + filenames[pos];
	if (pos< count){ //����ͼƬ������ʾ
		if (pImage->Load(filepath) != E_FAIL){//�Ӵ���װ��ͼƬ,����ҳ�����õ���ͼƬ�±�
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

	// TODO:  �ڴ˸��� DC ���κ�����
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);   //���ñ���͸��   
		return   HBRUSH(GetStockObject(HOLLOW_BRUSH));
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


BOOL CEXPLORER::PreTranslateMessage(MSG* pMsg)
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
