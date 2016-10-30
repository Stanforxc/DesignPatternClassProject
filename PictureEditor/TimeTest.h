#pragma once
#include "Graph.h"
#include "GraphSeries.h"


// CTimeTest �Ի���

class CTimeTest : public CDialog
{
	DECLARE_DYNAMIC(CTimeTest)

public:
	CTimeTest(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTimeTest();

// �Ի�������
	enum { IDD = IDD_DIALOG_TimeTest };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
private:
	CGraph* testGraph;
	BOOL graphComplete;

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
};
