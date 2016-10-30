#pragma once
#include"PictureInfoList.h"
#include "afxwin.h"

// CDELETEDlg �Ի���

class CDELETEDlg : public CDialog
{
	DECLARE_DYNAMIC(CDELETEDlg)

public:
	CDELETEDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CDELETEDlg(CWnd* pParent,PictureInfoList *ptr);
	virtual ~CDELETEDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_Delete };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	void drawPicture(CStatic *m_Pic/*�ؼ�����*/);

	DECLARE_MESSAGE_MAP()
private:
	PictureInfoList *picListptr;
	CString basePath;
public:
	CString m_title;
	afx_msg void OnBnClickedButton3();

	CStatic m_Pic1;
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
