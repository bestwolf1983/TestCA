// DlgD.cpp : 实现文件
//

#include "stdafx.h"
#include "TestCA.h"
#include "DlgD.h"

#include "MainFrm.h"
#include "TestCAView.h"

// CDlgD 对话框

IMPLEMENT_DYNAMIC(CDlgD, CDialog)

CDlgD::CDlgD(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgD::IDD, pParent)
{

}

CDlgD::~CDlgD()
{
}

void CDlgD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgD, CDialog)
END_MESSAGE_MAP()


// CDlgD 消息处理程序

void CDlgD::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类
	delete this;
	((CTestCAView*)(((CMainFrame*)AfxGetMainWnd())->GetActiveView()))->IsD = FALSE;		
	CDialog::PostNcDestroy();
}

void CDlgD::OnOK()
{
	DestroyWindow();
}

void CDlgD::OnCancel()
{
	DestroyWindow();
}
