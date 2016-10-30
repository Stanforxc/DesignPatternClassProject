#pragma once
#include"PictureInfoList.h"
#include "ATLComTime.h"

// CINSERTDlg 对话框

class CINSERTDlg : public CDialog
{
	DECLARE_DYNAMIC(CINSERTDlg)

public:
	CINSERTDlg(CWnd* pParent = NULL);   // 标准构造函数
	CINSERTDlg(CWnd* pParent,PictureInfoList *ptr);
	virtual ~CINSERTDlg();

// 对话框数据
	enum { IDD = IDD_INSERTDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	PictureInfoList *picListptr;
	OthersType new_item;
	string filename;
public:
	virtual BOOL OnInitDialog();
	COleDateTime m_creatTime;
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
