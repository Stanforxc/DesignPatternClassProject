// INSERTDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "INSERTDlg.h"
#include "afxdialogex.h"
#include"PdfJpeg.h"

// CINSERTDlg 对话框

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


// CINSERTDlg 消息处理程序


BOOL CINSERTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CINSERTDlg::OnPaint()
{
	// device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	CPaintDC dc(this);

	//显示背景图开始
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
	//----显示背景图结束

}


void CINSERTDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	TCHAR szFilter[] = _T("JPEG文件(*.jpg)|*.jpg|所有文件(*.*)|*.*||");
	CFileDialog fileDlg(true, _T("*.jpg"), NULL, 0, szFilter, this);

	CString strFilePath;

	if (IDOK == fileDlg.DoModal()){
		strFilePath = fileDlg.GetPathName();//获取选择的文件路径
		SetDlgItemText(IDC_EDIT5, strFilePath);  //将其显示在文本框

		SetDlgItemText(IDC_EDIT6, fileDlg.GetFileName()); //将文件名显示在文本框

		string fileName = (CStringA)strFilePath;
		filename = fileName;
		char tmpname[100];
		strcpy(tmpname, fileName.c_str());

		PdfJpeg jepg(tmpname); //加入的PdfJpeg类

		int readResult = jepg.ReadImage();

		if (readResult == -1){
			MessageBox(_T("Error in read file: "));		   return;
		}

		int width = jepg.GetWidth();
		int height = jepg.GetHeight();
		int size = int((jepg.GetDataLength()) / 1024.0 + 1); //上取整数
		SetDlgItemInt(IDC_EDIT1, width);
		SetDlgItemInt(IDC_EDIT2, height);
		SetDlgItemInt(IDC_EDIT3, size);


		//获取最后的修改时间time
		CFileStatus  status;//获取文件相关时间
		if (CFile::GetStatus(strFilePath, status)){
			//m_creatTime = status.m_ctime;//得到创建时间
			/*CTime m_ctime	文件创建的时间。   CTime m_mtime	文件最后一次修改的时间  	CTime m_atime	最后一次访问文件并读取的时间。*/
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
	// TODO:  在此添加控件通知处理程序代码
	CString mapName = _T("NULL");
	if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck())
		mapName = _T("华师大");
	else if (((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck())
		mapName = _T("中国");
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

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);   //设置背景透明   
		return   HBRUSH(GetStockObject(HOLLOW_BRUSH));
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


BOOL CINSERTDlg::PreTranslateMessage(MSG* pMsg)
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
