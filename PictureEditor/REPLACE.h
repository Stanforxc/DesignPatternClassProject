#pragma once
#include"PictureInfoList.h"
#include "afxwin.h"

// CREPLACE 对话框

class CREPLACE : public CDialog
{
	DECLARE_DYNAMIC(CREPLACE)

public:
	CREPLACE(CWnd* pParent = NULL);   // 标准构造函数
	CREPLACE(CWnd* pParent,PictureInfoList *ptr);
	CREPLACE(CWnd* pParent, PictureInfoList *ptr,CString filename);
	virtual ~CREPLACE();

// 对话框数据
	enum { IDD = IDD_DIALOG_Replace };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void drawPicture(CStatic *m_Pic/*控件名称*/);
	DECLARE_MESSAGE_MAP()
private:
	PictureInfoList *picListptr;
	PictureRecord a;
	int pos;
public:
	CString m_detail;
	CString m_filename;
	CString m_titleEn;
	CString m_map;
	CString m_location;
//	CEdit m_hmap;
	CString m_hmap;
	CString m_hlocation;
	CString m_owner;
	CString basepath;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CStatic m_pic1;
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
