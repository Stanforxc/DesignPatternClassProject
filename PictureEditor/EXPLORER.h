#pragma once

#include"PictureInfoList.h"
#include "afxwin.h"
// CEXPLORER 对话框

class CEXPLORER : public CDialog
{
	DECLARE_DYNAMIC(CEXPLORER)

public:
	CEXPLORER(CWnd* pParent = NULL);   // 标准构造函数
	CEXPLORER(CWnd* pParent,PictureInfoList *ptr);
	virtual ~CEXPLORER();

// 对话框数据
	enum { IDD = IDD_EXPLORER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	PictureInfoList *picListPtr;
	void drawPicture(CStatic *m_Pic/*控件名称*/, int no/*控件编号0-count-1*/);
	CString filenames[4000];//需要显示的所有文件名称
	CString basePath;//picLibrary的路径
	int currentPage;//当前页面
	int numInPages;//每页的图片数目
	int count;//总的图片数目
public:
	afx_msg void OnStnClickedPic1();
	CStatic m_Pic1;
	CStatic m_Pic2;
	CStatic m_Pic3;
	CStatic m_Pic4;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnStnClickedPic2();
	afx_msg void OnStnClickedPic3();
	afx_msg void OnStnClickedPic4();
	afx_msg void OnBnClickedButton2();

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
