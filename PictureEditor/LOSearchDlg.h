#pragma once
#include "afxwin.h"
#include"PictureInfoList.h"

// CLOSearchDlg �Ի���

class CLOSearchDlg : public CDialog
{
	DECLARE_DYNAMIC(CLOSearchDlg)

public:
	CLOSearchDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CLOSearchDlg(CWnd* pParent ,PictureInfoList*picListPtr);
	virtual ~CLOSearchDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_LOSearch };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	void drawPicture(CStatic *m_Pic/*�ؼ�����*/, int no/*�ؼ����0-count-1*/);
	DECLARE_MESSAGE_MAP()
public:
	CString m_location;
	CStatic m_pic1;
	CStatic m_pic2;
	CStatic m_pic3;
	CStatic m_pic4;
private:
	PictureInfoList *picListPtr;

	const Node<PictureRecord >*   items[1000];//��Ų�ѯ���
	CString filenames[4000];//��Ҫ��ʾ�������ļ�����
	CString basePath;//picLibrary��·��
	int currentPage;//��ǰҳ��
	int numInPages;//ÿҳ��ͼƬ��Ŀ
	int count;//�ܵ�ͼƬ��Ŀ

public:
	virtual BOOL OnInitDialog();
	
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonpre();
	afx_msg void OnBnClickedButtonnext();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedButtonsearch();
	afx_msg void OnStnClickedPic1();
	afx_msg void OnStnClickedPic2();
	afx_msg void OnStnClickedPic3();
	afx_msg void OnStnClickedPic4();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
