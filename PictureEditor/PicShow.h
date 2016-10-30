#pragma once
#include"PictureInfoList.h"
#include "afxwin.h"

// CPicShow 对话框

class CPicShow : public CDialog
{
	DECLARE_DYNAMIC(CPicShow)

public:
	CPicShow(CWnd* pParent = NULL);   // 标准构造函数
	CPicShow(CWnd* pParent,CString filename,PictureInfoList*ptr);
	virtual ~CPicShow();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void drawPicture(CStatic *m_Pic/*控件名称*/);
	DECLARE_MESSAGE_MAP()
private:
	CString filename;
	PictureInfoList *picListptr;
	CString basePath;
public:
	CStatic m_Pic1;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
