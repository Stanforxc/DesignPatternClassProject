#pragma once
#include "afxwin.h"
#include"PictureInfoList.h"

// CFootMarkShow �Ի���

class CFootMarkShow : public CDialogEx
{
	DECLARE_DYNAMIC(CFootMarkShow)

public:
	CFootMarkShow(CWnd* pParent = NULL);   // ��׼���캯��
	CFootMarkShow(CWnd* pParent, const List <const Node<PictureRecord >  *>*ptr,PictureInfoList *picListptr);
	virtual ~CFootMarkShow();

// �Ի�������
	enum { IDD = IDD_DIALOG_FootMarkshow };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	void drawPicture(CStatic *m_Pic/*�ؼ�����*/, int no/*�ؼ����0-count-1*/);
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_pic1;
	afx_msg void OnStnClickedPic1();
private:
	const List <const Node<PictureRecord >  *>*     trackListPtr;
	PictureInfoList *picListptr;
	CString filenames[2000];//��Ҫ��ʾ�������ļ�����
	CString basePath;//picLibrary��·��
	int currentPage;//��ǰҳ��
	int numInPages;//ÿҳ��ͼƬ��Ŀ
	int count;//�ܵ�ͼƬ��Ŀ
public:
	CStatic m_pic2;
	CStatic m_pic3;
	CStatic m_pic4;
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnStnClickedPic2();
	afx_msg void OnStnClickedPic3();
	afx_msg void OnStnClickedPic4();
};
