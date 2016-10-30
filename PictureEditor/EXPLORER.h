#pragma once

#include"PictureInfoList.h"
#include "afxwin.h"
// CEXPLORER �Ի���

class CEXPLORER : public CDialog
{
	DECLARE_DYNAMIC(CEXPLORER)

public:
	CEXPLORER(CWnd* pParent = NULL);   // ��׼���캯��
	CEXPLORER(CWnd* pParent,PictureInfoList *ptr);
	virtual ~CEXPLORER();

// �Ի�������
	enum { IDD = IDD_EXPLORER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	PictureInfoList *picListPtr;
	void drawPicture(CStatic *m_Pic/*�ؼ�����*/, int no/*�ؼ����0-count-1*/);
	CString filenames[4000];//��Ҫ��ʾ�������ļ�����
	CString basePath;//picLibrary��·��
	int currentPage;//��ǰҳ��
	int numInPages;//ÿҳ��ͼƬ��Ŀ
	int count;//�ܵ�ͼƬ��Ŀ
public:
	afx_msg void OnStnClickedPic1();
	CStatic m_Pic1;
	CStatic m_Pic2;
	CStatic m_Pic3;
	CStatic m_Pic4;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnStnClickedPic2();
	afx_msg void OnStnClickedPic3();
	afx_msg void OnStnClickedPic4();
	afx_msg void OnBnClickedButton2();

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
