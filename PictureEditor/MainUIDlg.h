// MainUIDlg.h : 头文件
//

#pragma once
#include "PictureInfoList.h"//增加头文件



// CMainUIDlg 对话框
class CMainUIDlg : public CDialog
{
// 构造
public:
	CMainUIDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MAINUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSearchbytitle();
	afx_msg void OnBnClickedButtonexplore();
	afx_msg void OnBnClickedButtonTrack();
private:
	PictureInfoList picLibrary; //增加新的对象
	CString basepath;
public:
	afx_msg void OnBnClickedButtonSearchbyloc();
	afx_msg void OnBnClickedButtonInsert();
	afx_msg void OnBnClickedButtonRemove();
	afx_msg void OnBnClickedButtonReplace();
	afx_msg void OnBnClickedButtonTesting();
	afx_msg void OnBnClickedButton1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton2();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
