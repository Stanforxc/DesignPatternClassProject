#pragma once

#include"PictureInfoList.h"
// CNewFootMarkDlg 对话框

class CNewFootMarkDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewFootMarkDlg)

public:
	CNewFootMarkDlg(CWnd* pParent = NULL);   // 标准构造函数
	CNewFootMarkDlg(CWnd* pParent,PictureInfoList *ptr);
	virtual ~CNewFootMarkDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_newFootmark };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
private:
	LocationGraph<200> ecnuMap;
	PictureInfoList * picLibraryPtr;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
