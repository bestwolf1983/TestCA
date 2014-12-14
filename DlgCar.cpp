// DlgCar.cpp : implementation file
//

#include "stdafx.h"
#include "testca.h"
#include "DlgCar.h"
#include "TestCAView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "MainFrm.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgCar dialog


CDlgCar::CDlgCar(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCar::IDD, pParent),m_carkind(0)
{
	//{{AFX_DATA_INIT(CDlgCar)
	m_carkind = -1;
	//}}AFX_DATA_INIT
}


void CDlgCar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCar)
	DDX_Radio(pDX, IDC_Heavy, m_carkind);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCar, CDialog)
	//{{AFX_MSG_MAP(CDlgCar)
	ON_BN_CLICKED(ID_DONE, OnDone)
	ON_BN_CLICKED(IDC_Heavy, OnHeavy)
	ON_BN_CLICKED(IDC_NORMAL, OnNormal)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCar message handlers

void CDlgCar::PostNcDestroy() 
{
	delete this;
	((CTestCAView*)(((CMainFrame*)AfxGetMainWnd())->GetActiveView()))->pcar_setting = NULL;	
	((CTestCAView*)(((CMainFrame*)AfxGetMainWnd())->GetActiveView()))->IsSetting = FALSE;	
	CDialog::PostNcDestroy();
}

void CDlgCar::OnDone() 
{
	((CTestCAView*)(::AfxGetMainWnd()->GetActiveWindow()))->IsSetting = FALSE;
	DestroyWindow();	
}

BOOL CDlgCar::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.cx = 120;
	cs.cy = 50;
	return CDialog::PreCreateWindow(cs);
}

void CDlgCar::OnHeavy() 
{
	// TODO: Add your control notification handler code here

	m_carkind = 0;
}

void CDlgCar::OnNormal() 
{
	// TODO: Add your control notification handler code here
	m_carkind = 1;
	
}

void CDlgCar::OnOK()
{
	DestroyWindow();
}

void CDlgCar::OnCancel()
{
	DestroyWindow();
}
