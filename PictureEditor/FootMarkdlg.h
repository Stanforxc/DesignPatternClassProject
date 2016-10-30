#pragma once

#include"PictureInfoList.h"
// CFootMarkdlg �Ի���

class CFootMarkdlg : public CDialog
{
	DECLARE_DYNAMIC(CFootMarkdlg)

public:
	CFootMarkdlg(CWnd* pParent = NULL);   // ��׼���캯��
	CFootMarkdlg(CWnd* pParent,PictureInfoList *ptr);
	virtual ~CFootMarkdlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_FootMarkDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
