// DigSet.cpp : 实现文件
//

#include "stdafx.h"
#include "TestCA.h"
#include "DigSet.h"


// CDigSet 对话框

IMPLEMENT_DYNAMIC(CDigSet, CDialog)

CDigSet::CDigSet(CWnd* pParent /*=NULL*/)
	: CDialog(CDigSet::IDD, pParent)
	, m_dist(0)
{

}

CDigSet::~CDigSet()
{
}

void CDigSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_dist);
	DDV_MinMaxInt(pDX, m_dist, 30, 5000);
}


BEGIN_MESSAGE_MAP(CDigSet, CDialog)

END_MESSAGE_MAP()




