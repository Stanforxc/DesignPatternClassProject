// TLSearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MainUI.h"
#include "TLSearchDlg.h"
#include <atlimage.h>
#include"PicShow.h"


// CTLSearchDlg dialog

IMPLEMENT_DYNAMIC(CTLSearchDlg, CDialog)

CTLSearchDlg::CTLSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTLSearchDlg::IDD, pParent)
	, m_title(_T(""))
{

}

CTLSearchDlg::CTLSearchDlg(CWnd* pParent,PictureInfoList *picListPtr_)
	: CDialog(CTLSearchDlg::IDD, pParent)
{
    picListPtr=picListPtr_;
}

CTLSearchDlg::~CTLSearchDlg()
{
}

void CTLSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Pic1, m_Pic1);
	DDX_Control(pDX, IDC_Pic2, m_Pic2);
	DDX_Control(pDX, IDC_Pic3, m_Pic3);
	DDX_Control(pDX, IDC_Pic4, m_Pic4);
	DDX_Text(pDX, IDC_EDIT2, m_title);
}


BEGIN_MESSAGE_MAP(CTLSearchDlg, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTONPre, &CTLSearchDlg::OnBnClickedButtonpre)
	ON_BN_CLICKED(IDC_BUTTONNext, &CTLSearchDlg::OnBnClickedButtonnext)
	ON_EN_CHANGE(IDC_EDIT2, &CTLSearchDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTONSearch, &CTLSearchDlg::OnBnClickedButtonsearch)
	ON_STN_CLICKED(IDC_Pic1, &CTLSearchDlg::OnStnClickedPic1)
	ON_STN_CLICKED(IDC_Pic2, &CTLSearchDlg::OnStnClickedPic2)
	ON_STN_CLICKED(IDC_Pic3, &CTLSearchDlg::OnStnClickedPic3)
	ON_STN_CLICKED(IDC_Pic4, &CTLSearchDlg::OnStnClickedPic4)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CTLSearchDlg message handlers


void CTLSearchDlg::drawPicture(CStatic* m_Pic/*�ؼ�����*/, int no/*�ؼ����0-n-1*/){

    	CRect rectPic;
        (*m_Pic).GetClientRect(&rectPic);     //m_pictureΪPicture Control�ؼ���������ÿؼ����������
        CDC* pDC = m_Pic->GetWindowDC();    //�����ʾ�ؼ���DC

		CImage *pImage = new CImage();//װ��ͼ�����
		
		int pos = currentPage*numInPages+no;
		CString filename = basePath + filenames[pos];
		if (pos< count){ //����ͼƬ������ʾ
			if (pImage->Load(filename) != E_FAIL)//�Ӵ���װ��ͼƬ,����ҳ�����õ���ͼƬ�±�
			{
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
}else{
      m_Pic->ShowWindow(SW_HIDE);          
}
}		



BOOL CTLSearchDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  Add extra initialization here
	basePath = ".\\picLibrary\\";
	currentPage=0;
	numInPages = 4;
	count = picListPtr->size();

	//��ʼʱ��List�л�ȡ���е��ļ���
	for(int i=0; i<count; i++){
		 PictureRecord picRec;
         picListPtr->retrieve(i,picRec);
		 filenames[i] =picRec.the_key().c_str();
       //  filenames[i] = basePath+filenames[i];
	
	}
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CTLSearchDlg::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages

	CDialog::OnPaint();
	CPaintDC dc(this);
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
}

void CTLSearchDlg::OnBnClickedButtonpre()
{
	// TODO: Add your control notification handler code here
	if (currentPage > 0){
	  currentPage--;   
      if(m_Pic1.IsWindowVisible()== false)
         m_Pic1.ShowWindow(SW_SHOW);  
	  if(m_Pic2.IsWindowVisible() == false)
         m_Pic2.ShowWindow(SW_SHOW); 
	  if(m_Pic3.IsWindowVisible() == false)
         m_Pic3.ShowWindow(SW_SHOW); 
	   if(m_Pic4.IsWindowVisible() == false)
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

void CTLSearchDlg::OnBnClickedButtonnext()
{
	// TODO: Add your control notification handler code here
	
	if (currentPage < count/numInPages && (currentPage+1)*numInPages<count) {
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

void CTLSearchDlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);//��������ֵ�ĸ��±����ڱ�����
}

void CTLSearchDlg::OnBnClickedButtonsearch()
{
	// TODO: Add your control notification handler code here
    string titleEn = (CStringA)m_title; //CString -> String
	int n;
     //searchByTitle(string title, int& n , Node<PictureRecord >*   items[]);
	if( picListPtr->searchByTitle(titleEn,n, items)==success ){
		  //�õ����е��ļ���
		  for (int k=0; k<n; k++){
			PictureRecord pr = items[k]->entry;
			filenames[k] = pr.the_key().c_str(); //string -��String
        //    filenames[k] = basePath+filenames[k];
		   }
	  
	  currentPage=0;
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
	      MessageBox(_T("The Word is not exist!"));



}

void CTLSearchDlg::OnStnClickedPic1()
{
	// TODO: Add your control notification handler code here
	int pos = currentPage*numInPages;
	CString filepath = filenames[pos];
	CPicShow a(NULL, filepath,picListPtr);
	a.DoModal();
}

void CTLSearchDlg::OnStnClickedPic2()
{
		// TODO: Add your control notification handler code here
	int pos =currentPage*numInPages+1;
	CString filepath = filenames[pos];
	CPicShow a(NULL, filepath,picListPtr);
	a.DoModal();
}

void CTLSearchDlg::OnStnClickedPic3()
{
		// TODO: Add your control notification handler code here
	int pos =currentPage*numInPages+2;
	CString filepath = filenames[pos];
	CPicShow a(NULL, filepath,picListPtr);
	a.DoModal();
}

void CTLSearchDlg::OnStnClickedPic4()
{
		// TODO: Add your control notification handler code here
	int pos =currentPage*numInPages+3;
	CString filepath = filenames[pos];
	CPicShow a(NULL, filepath,picListPtr);
	a.DoModal();
}


HBRUSH CTLSearchDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


BOOL CTLSearchDlg::PreTranslateMessage(MSG* pMsg)
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
