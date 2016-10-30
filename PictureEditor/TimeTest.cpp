// TimeTest.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "TimeTest.h"
#include "afxdialogex.h"


// CTimeTest �Ի���

IMPLEMENT_DYNAMIC(CTimeTest, CDialog)

CTimeTest::CTimeTest(CWnd* pParent /*=NULL*/)
	: CDialog(CTimeTest::IDD, pParent)
{

}

CTimeTest::~CTimeTest()
{
	if (testGraph != NULL)
		delete testGraph;

}

void CTimeTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTimeTest, CDialog)
	ON_BN_CLICKED(IDC_BUTTON3, &CTimeTest::OnBnClickedButton3)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &CTimeTest::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTimeTest::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CTimeTest::OnBnClickedButton4)
END_MESSAGE_MAP()


// CTimeTest ��Ϣ�������


void CTimeTest::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	testGraph->SetGraphType(2);
	Invalidate(TRUE);

}


void CTimeTest::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	CWnd* graphFrame = (CWnd*)GetDlgItem(IDC_Pic);
	CDC* pDC = graphFrame->GetDC();
	testGraph->DrawGraph(pDC);
	ReleaseDC(pDC);

	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}


BOOL CTimeTest::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	testGraph = new CGraph();

	testGraph->SetGraphTitle(_T("Test Results"));
	testGraph->SetTickRange(150);
	testGraph->SetTickSpace(20);
	testGraph->SetXAxisAlignment(0);

	testGraph->SetXAxisLabel(_T("Students"));
	testGraph->SetYAxisLabel(_T("Test Scores"));

	CGraphSeries* series1 = new CGraphSeries();
	CGraphSeries* series2 = new CGraphSeries();
	CGraphSeries* series3 = new CGraphSeries();
	series1->SetLabel(_T("Student 1"));
	series2->SetLabel(_T("Student 2"));
	series3->SetLabel(_T("Student 3"));

	series1->SetData(0, 87);
	series1->SetData(1, 92);
	series1->SetData(2, 73);
	series2->SetData(0, 64);
	series2->SetData(1, 58);
	series2->SetData(2, 86);

	series3->SetData(0, 94);
	series3->SetData(1, 100);
	series3->SetData(2, 91);
	testGraph->AddSeries(series1);
	testGraph->AddSeries(series2);
	testGraph->AddSeries(series3);

	testGraph->SetLegend(0, _T("English "));
	testGraph->SetLegend(1, _T("Math    "));
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CTimeTest::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	testGraph->SetGraphType(1);
	Invalidate(TRUE);

}


void CTimeTest::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	testGraph->SetGraphType(0);
	Invalidate(TRUE);

}


void CTimeTest::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	delete testGraph;
	testGraph = NULL;
	CDialog::OnOK();


}
