// DlgD.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestCA.h"
#include "DlgD.h"

#include "MainFrm.h"
#include "TestCAView.h"

// CDlgD �Ի���

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


// CDlgD ��Ϣ�������

void CDlgD::PostNcDestroy()
{
	// TODO: �ڴ����ר�ô����/����û���
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
