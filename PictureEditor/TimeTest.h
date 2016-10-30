#pragma once
#include "Graph.h"
#include "GraphSeries.h"


// CTimeTest 对话框

class CTimeTest : public CDialog
{
	DECLARE_DYNAMIC(CTimeTest)

public:
	CTimeTest(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTimeTest();

// 对话框数据
	enum { IDD = IDD_DIALOG_TimeTest };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
