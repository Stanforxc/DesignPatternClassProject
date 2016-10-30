#pragma once
#include "afxwin.h"
#include"PictureInfoList.h"

// CFootMarkShow 对话框

class CFootMarkShow : public CDialogEx
{
	DECLARE_DYNAMIC(CFootMarkShow)

public:
	CFootMarkShow(CWnd* pParent = NULL);   // 标准构造函数
	CFootMarkShow(CWnd* pParent, const List <const Node<PictureRecord >  *>*ptr,PictureInfoList *picListptr);
	virtual ~CFootMarkShow();

// 对话框数据
	enum { IDD = IDD_DIALOG_FootMarkshow };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void drawPicture(CStatic *m_Pic/*控件名称*/, int no/*控件编号0-count-1*/);
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_pic1;
	afx_msg void OnStnClickedPic1();
private:
	const List <const Node<PictureRecord >  *>*     trackListPtr;
	PictureInfoList *picListptr;
	CString filenames[2000];//需要显示的所有文件名称
	CString basePath;//picLibrary的路径
	int currentPage;//当前页面
	int numInPages;//每页的图片数目
	int count;//总的图片数目
public:
	CStatic m_pic2;
	CStatic m_pic3;
	CStatic m_pic4;
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnStnClickedPic2();
	afx_msg void OnStnClickedPic3();
	afx_msg void OnStnClickedPic4();
};
