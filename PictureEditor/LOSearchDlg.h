#pragma once
#include "afxwin.h"
#include"PictureInfoList.h"

// CLOSearchDlg 对话框

class CLOSearchDlg : public CDialog
{
	DECLARE_DYNAMIC(CLOSearchDlg)

public:
	CLOSearchDlg(CWnd* pParent = NULL);   // 标准构造函数
	CLOSearchDlg(CWnd* pParent ,PictureInfoList*picListPtr);
	virtual ~CLOSearchDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_LOSearch };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void drawPicture(CStatic *m_Pic/*控件名称*/, int no/*控件编号0-count-1*/);
	DECLARE_MESSAGE_MAP()
public:
	CString m_location;
	CStatic m_pic1;
	CStatic m_pic2;
	CStatic m_pic3;
	CStatic m_pic4;
private:
	PictureInfoList *picListPtr;

	const Node<PictureRecord >*   items[1000];//存放查询结果
	CString filenames[4000];//需要显示的所有文件名称
	CString basePath;//picLibrary的路径
	int currentPage;//当前页面
	int numInPages;//每页的图片数目
	int count;//总的图片数目

public:
	virtual BOOL OnInitDialog();
	
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonpre();
	afx_msg void OnBnClickedButtonnext();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedButtonsearch();
	afx_msg void OnStnClickedPic1();
	afx_msg void OnStnClickedPic2();
	afx_msg void OnStnClickedPic3();
	afx_msg void OnStnClickedPic4();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
