#pragma once
#include"PictureInfoList.h"
#include "ATLComTime.h"

// CINSERTDlg �Ի���

class CINSERTDlg : public CDialog
{
	DECLARE_DYNAMIC(CINSERTDlg)

public:
	CINSERTDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CINSERTDlg(CWnd* pParent,PictureInfoList *ptr);
	virtual ~CINSERTDlg();

// �Ի�������
	enum { IDD = IDD_INSERTDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
