#pragma once
#include"PictureInfoList.h"
#include "afxwin.h"

// CPicShow �Ի���

class CPicShow : public CDialog
{
	DECLARE_DYNAMIC(CPicShow)

public:
	CPicShow(CWnd* pParent = NULL);   // ��׼���캯��
	CPicShow(CWnd* pParent,CString filename,PictureInfoList*ptr);
	virtual ~CPicShow();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	void drawPicture(CStatic *m_Pic/*�ؼ�����*/);
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
