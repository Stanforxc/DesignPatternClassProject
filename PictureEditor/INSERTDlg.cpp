// INSERTDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "INSERTDlg.h"
#include "afxdialogex.h"
#include"PdfJpeg.h"

// CINSERTDlg �Ի���

IMPLEMENT_DYNAMIC(CINSERTDlg, CDialog)

CINSERTDlg::CINSERTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CINSERTDlg::IDD, pParent)
	, m_creatTime(COleDateTime::GetCurrentTime())
{

}
CINSERTDlg::CINSERTDlg(CWnd* pParent /*=NULL*/,PictureInfoList *ptr)
	: CDialog(CINSERTDlg::IDD, pParent)
{
	picListptr = ptr;
}
CINSERTDlg::~CINSERTDlg()
{
}

void CINSERTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_creatTime);
}


BEGIN_MESSAGE_MAP(CINSERTDlg, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON2, &CINSERTDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CINSERTDlg::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CINSERTDlg ��Ϣ�������


BOOL CINSERTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CINSERTDlg::OnPaint()
{
	// device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
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

}


void CINSERTDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	TCHAR szFilter[] = _T("JPEG�ļ�(*.jpg)|*.jpg|�����ļ�(*.*)|*.*||");
	CFileDialog fileDlg(true, _T("*.jpg"), NULL, 0, szFilter, this);

	CString strFilePath;

	if (IDOK == fileDlg.DoModal()){
		strFilePath = fileDlg.GetPathName();//��ȡѡ����ļ�·��
		SetDlgItemText(IDC_EDIT5, strFilePath);  //������ʾ���ı���

		SetDlgItemText(IDC_EDIT6, fileDlg.GetFileName()); //���ļ�����ʾ���ı���

		string fileName = (CStringA)strFilePath;
		filename = fileName;
		char tmpname[100];
		strcpy(tmpname, fileName.c_str());

		PdfJpeg jepg(tmpname); //�����PdfJpeg��

		int readResult = jepg.ReadImage();

		if (readResult == -1){
			MessageBox(_T("Error in read file: "));		   return;
		}

		int width = jepg.GetWidth();
		int height = jepg.GetHeight();
		int size = int((jepg.GetDataLength()) / 1024.0 + 1); //��ȡ����
		SetDlgItemInt(IDC_EDIT1, width);
		SetDlgItemInt(IDC_EDIT2, height);
		SetDlgItemInt(IDC_EDIT3, size);


		//��ȡ�����޸�ʱ��time
		CFileStatus  status;//��ȡ�ļ����ʱ��
		if (CFile::GetStatus(strFilePath, status)){
			//m_creatTime = status.m_ctime;//�õ�����ʱ��
			/*CTime m_ctime	�ļ�������ʱ�䡣   CTime m_mtime	�ļ����һ���޸ĵ�ʱ��  	CTime m_atime	���һ�η����ļ�����ȡ��ʱ�䡣*/
			time_t time2 = status.m_mtime.GetTime(); //CTime--->time_t
			COleDateTime time3(time2); //time_t--->COleDateTime
			m_creatTime = time3;
			UpdateData(false);
		}
		new_item.height = height;
		new_item.width = width;
		new_item.size = size;
		
	}
}


void CINSERTDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString mapName = _T("NULL");
	if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck())
		mapName = _T("��ʦ��");
	else if (((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck())
		mapName = _T("�й�");
	//new_item.map = (CStringA)mapName;
	int index = filename.find_last_of('\\');
	filename = filename.substr(index+1, 50);
	PictureRecord new_picRecord(filename, new_item);
	if (picListptr->insert(new_picRecord) == success)
		MessageBox(_T("insert success"));
	else
		MessageBox(_T("The picture is already in the picLibrary"));
}


HBRUSH CINSERTDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


BOOL CINSERTDlg::PreTranslateMessage(MSG* pMsg)
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
