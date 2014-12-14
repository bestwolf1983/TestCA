// DialogRun.cpp : implementation file
//

#include "stdafx.h"
#include "testca.h"
#include "DialogRun.h"
#include "TestCAView.h"
#include "simworld.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogRun dialog


CDialogRun::CDialogRun(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogRun::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogRun)
	m_iradio = -1;
	m_urate = 0;
	m_timeset = 0;
	m_vset = 0;
	m_rec = 0;
	m_kset = 0;
	m_vset2 = 0;
	//}}AFX_DATA_INIT
}


void CDialogRun::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogRun)
	DDX_Radio(pDX, IDC_RADIO1, m_iradio);
	DDX_Text(pDX, IDC_EDIT1, m_urate);
	DDV_MinMaxUInt(pDX, m_urate, 10, 2000);
	DDX_Text(pDX, IDC_EDITTIME, m_timeset);
	DDV_MinMaxInt(pDX, m_timeset, 0, 31000);
	DDX_Text(pDX, IDC_EDITMAXV, m_vset);
	DDV_MinMaxInt(pDX, m_vset, 1, 5);
	DDX_Text(pDX, IDC_EDITREC, m_rec);
	DDV_MinMaxInt(pDX, m_rec, 0, 1000);
	DDX_Text(pDX, IDC_EDITKSET, m_kset);
	DDV_MinMaxInt(pDX, m_kset, 0, 1000);
	DDX_Text(pDX, IDC_EDITMAXV2, m_vset2);
	DDV_MinMaxInt(pDX, m_vset2, 1, 5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogRun, CDialog)
	//{{AFX_MSG_MAP(CDialogRun)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogRun message handlers

void CDialogRun::OnOK() 
{
	UpdateData();

	if(m_iradio == 1 ){/*输出时空斑图和动画过程*/

		if(m_urate == 0){
			MessageBox("错误的运行间隔值","输入错误",MB_OK|MB_ICONERROR);
			return;
		}
	}
	else if(m_iradio != 0){
		MessageBox("请选择两种运行方式中的一种！！");
		return;
	}
	CDialog::OnOK();
}



void CDialogRun::OnRadio2() 
{
	((CEdit*)GetDlgItem(IDC_EDIT1))->EnableWindow(TRUE);

}

void CDialogRun::OnRadio1() 
{
	((CEdit*)GetDlgItem(IDC_EDIT1))->EnableWindow(FALSE);
	
}


