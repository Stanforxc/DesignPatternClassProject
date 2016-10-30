// FootMarkShow.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "FootMarkShow.h"
#include "afxdialogex.h"
#include"PicShow.h"

// CFootMarkShow �Ի���

IMPLEMENT_DYNAMIC(CFootMarkShow, CDialogEx)

CFootMarkShow::CFootMarkShow(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFootMarkShow::IDD, pParent)
{

}

CFootMarkShow::CFootMarkShow(CWnd* pParent, const List <const Node<PictureRecord >  *>*ptr,PictureInfoList*picListptr)
	: CDialogEx(CFootMarkShow::IDD, pParent)
{
	trackListPtr = ptr;
	this->picListptr = picListptr;
}
CFootMarkShow::~CFootMarkShow()
{
}

void CFootMarkShow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Pic1, m_pic1);
	DDX_Control(pDX, IDC_Pic2, m_pic2);
	DDX_Control(pDX, IDC_Pic3, m_pic3);
	DDX_Control(pDX, IDC_Pic4, m_pic4);
}


BEGIN_MESSAGE_MAP(CFootMarkShow, CDialogEx)
	ON_STN_CLICKED(IDC_Pic1, &CFootMarkShow::OnStnClickedPic1)
	ON_BN_CLICKED(IDC_BUTTON2, &CFootMarkShow::OnBnClickedButton2)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &CFootMarkShow::OnBnClickedButton1)
	ON_STN_CLICKED(IDC_Pic2, &CFootMarkShow::OnStnClickedPic2)
	ON_STN_CLICKED(IDC_Pic3, &CFootMarkShow::OnStnClickedPic3)
	ON_STN_CLICKED(IDC_Pic4, &CFootMarkShow::OnStnClickedPic4)
END_MESSAGE_MAP()


// CFootMarkShow ��Ϣ�������


void CFootMarkShow::OnStnClickedPic1()
{
	int pos = currentPage*numInPages + 0;
	CPicShow a(NULL, filenames[pos],picListptr);
	a.DoModal();
}


void CFootMarkShow::OnBnClickedButton2()
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


BOOL CFootMarkShow::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	basePath = ".\\picLibrary\\";
	currentPage = 0;
	numInPages = 4;
	count = trackListPtr->size();

	//��ʼʱ��List�л�ȡ���е��ļ���
	for (int i = 0; i<count; i++){
		const Node<PictureRecord >  * picRec;
		trackListPtr->retrieve(i, picRec);
		filenames[i] = picRec->entry.the_key().c_str();
		//filenames[i] = basePath + filenames[i];

	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
void CFootMarkShow::drawPicture(CStatic* m_Pic/*�ؼ�����*/, int no/*�ؼ����0-n-1*/){

	CRect rectPic;
	(*m_Pic).GetClientRect(&rectPic);     //m_pictureΪPicture Control�ؼ���������ÿؼ����������
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
			//������
		}
	}
	else{
		m_Pic->ShowWindow(SW_HIDE);
	}
}

void CFootMarkShow::OnPaint()
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

	drawPicture(&m_pic1, 0);
	drawPicture(&m_pic2, 1);
	drawPicture(&m_pic3, 2);
	drawPicture(&m_pic4, 3);
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


HBRUSH CFootMarkShow::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);   //���ñ���͸��   
		return   HBRUSH(GetStockObject(HOLLOW_BRUSH));
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CFootMarkShow::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (currentPage > 0){
		currentPage--;
		if (m_pic1.IsWindowVisible() == false)
			m_pic1.ShowWindow(SW_SHOW);
		if (m_pic2.IsWindowVisible() == false)
			m_pic2.ShowWindow(SW_SHOW);
		if (m_pic3.IsWindowVisible() == false)
			m_pic3.ShowWindow(SW_SHOW);
		if (m_pic4.IsWindowVisible() == false)
			m_pic4.ShowWindow(SW_SHOW);


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


BOOL CFootMarkShow::PreTranslateMessage(MSG* pMsg)
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
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CFootMarkShow::OnStnClickedPic2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int pos = currentPage*numInPages + 1;
	CPicShow a(NULL, filenames[pos], picListptr);
	a.DoModal();
}


void CFootMarkShow::OnStnClickedPic3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int pos = currentPage*numInPages + 2;
	CPicShow a(NULL, filenames[pos], picListptr);
	a.DoModal();
}


void CFootMarkShow::OnStnClickedPic4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int pos = currentPage*numInPages + 3;
	CPicShow a(NULL, filenames[pos], picListptr);
	a.DoModal();
}
