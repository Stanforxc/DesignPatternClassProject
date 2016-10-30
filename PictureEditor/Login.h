#pragma once


// CLogin 对话框

class CLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CLogin)

public:
	CLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLogin();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_password;
	afx_msg void OnBnClickedButton1();
private:
	CString password;
public:
	virtual BOOL OnInitDialog();
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
