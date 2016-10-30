// LOSearchDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "LOSearchDlg.h"
#include "afxdialogex.h"
#include <atlimage.h>
#include "PicShow.h"
// CLOSearchDlg �Ի���

IMPLEMENT_DYNAMIC(CLOSearchDlg, CDialog)

CLOSearchDlg::CLOSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLOSearchDlg::IDD, pParent)
	, m_location(_T(""))
{

}
CLOSearchDlg::CLOSearchDlg(CWnd* pParent /*=NULL*/,PictureInfoList *picListPtr)
	: CDialog(CLOSearchDlg::IDD, pParent)
	, m_location(_T(""))
{
	this->picListPtr = picListPtr;
}
CLOSearchDlg::~CLOSearchDlg()
{
}

void CLOSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_location);
	DDX_Control(pDX, IDC_Pic1, m_pic1);
	DDX_Control(pDX, IDC_Pic2, m_pic2);
	DDX_Control(pDX, IDC_Pic3, m_pic3);
	DDX_Control(pDX, IDC_Pic4, m_pic4);
}


BEGIN_MESSAGE_MAP(CLOSearchDlg, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTONPre, &CLOSearchDlg::OnBnClickedButtonpre)
	ON_BN_CLICKED(IDC_BUTTONNext, &CLOSearchDlg::OnBnClickedButtonnext)
	ON_EN_CHANGE(IDC_EDIT2, &CLOSearchDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTONSearch, &CLOSearchDlg::OnBnClickedButtonsearch)
	ON_STN_CLICKED(IDC_Pic1, &CLOSearchDlg::OnStnClickedPic1)
	ON_STN_CLICKED(IDC_Pic2, &CLOSearchDlg::OnStnClickedPic2)
	ON_STN_CLICKED(IDC_Pic3, &CLOSearchDlg::OnStnClickedPic3)
	ON_STN_CLICKED(IDC_Pic4, &CLOSearchDlg::OnStnClickedPic4)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CLOSearchDlg ��Ϣ�������
void CLOSearchDlg::drawPicture(CStatic* m_Pic/*�ؼ�����*/, int no/*�ؼ����0-n-1*/){

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

BOOL CLOSearchDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CDialog::OnInitDialog();
	// TODO:  Add extra initialization here
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
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CLOSearchDlg::OnPaint()
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

	drawPicture(&m_pic1, 0);
	drawPicture(&m_pic2, 1);
	drawPicture(&m_pic3, 2);
	drawPicture(&m_pic4, 3);
}


void CLOSearchDlg::OnBnClickedButtonpre()
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


void CLOSearchDlg::OnBnClickedButtonnext()
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
		MessageBox(_T("�Ѿ������һ���ˣ�"));
}


void CLOSearchDlg::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}


void CLOSearchDlg::OnBnClickedButtonsearch()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	string titleEn = (CStringA)m_location; //CString -> String
	int n;
	//searchByTitle(string title, int& n , Node<PictureRecord >*   items[]);
	if (picListPtr->searchByLocation(titleEn, n, items) == success){
		//�õ����е��ļ���
		for (int k = 0; k<n; k++){
			PictureRecord pr = items[k]->entry;
			filenames[k] = pr.the_key().c_str(); //string -��String
			//filenames[k] = basePath + filenames[k];
		}

		currentPage = 0;
		count = n;

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
	}
	else
		MessageBox(_T("The Place is not exist!"));
}


void CLOSearchDlg::OnStnClickedPic1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int pos = currentPage*numInPages + 0;
	CString filepath = filenames[pos];
	CPicShow a(NULL, filepath,picListPtr);
	a.DoModal();
}


void CLOSearchDlg::OnStnClickedPic2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int pos = currentPage*numInPages + 1;
	CString filepath = filenames[pos];
	CPicShow a(NULL, filepath,picListPtr);
	a.DoModal();
}


void CLOSearchDlg::OnStnClickedPic3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int pos = currentPage*numInPages + 2;
	CString filepath = filenames[pos];
	CPicShow a(NULL, filepath,picListPtr);
	a.DoModal();
}


void CLOSearchDlg::OnStnClickedPic4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	int pos = currentPage*numInPages + 3;
	CString filepath = filenames[pos];
	CPicShow a(NULL, filepath,picListPtr);
	a.DoModal();
}


HBRUSH CLOSearchDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


BOOL CLOSearchDlg::PreTranslateMessage(MSG* pMsg)
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
