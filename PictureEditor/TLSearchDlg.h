#pragma once
#include "PictureInfoList.h"
#include "afxwin.h"

// CTLSearchDlg dialog

class CTLSearchDlg : public CDialog
{
	DECLARE_DYNAMIC(CTLSearchDlg)

public:
	CTLSearchDlg(CWnd* pParent = NULL);   // standard constructor
	CTLSearchDlg(CWnd* pParent,PictureInfoList *picListPtr_);  
	
	virtual ~CTLSearchDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_TlSearch };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void drawPicture(CStatic *m_Pic/*�ؼ�����*/, int no/*�ؼ����0-count-1*/);

	DECLARE_MESSAGE_MAP()
private:
	PictureInfoList *picListPtr;
    
	const Node<PictureRecord >*   items[2000];//��Ų�ѯ���
	CString filenames[4000];//��Ҫ��ʾ�������ļ�����
	CString basePath;//picLibrary��·��
	int currentPage;//��ǰҳ��
	int numInPages;//ÿҳ��ͼƬ��Ŀ
	int count;//�ܵ�ͼƬ��Ŀ

public:
	CStatic m_Pic1;
	CStatic m_Pic2;
	CStatic m_Pic3;
	CStatic m_Pic4;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonpre();
	afx_msg void OnBnClickedButtonnext();
private:
	CString m_title;
public:
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedButtonsearch();
	afx_msg void OnStnClickedPic1();
	afx_msg void OnStnClickedPic2();
	afx_msg void OnStnClickedPic3();
	afx_msg void OnStnClickedPic4();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
