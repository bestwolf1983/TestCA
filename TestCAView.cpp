// TestCAView.cpp : implementation of the CTestCAView class
//

#include "stdafx.h"
#include "TestCA.h"

//#include "TestCADoc.h"
#include "TestCAView.h"
#include "MainFrm.h"

//liyan define
#include "DialogRun.h"
#include "DlgCar.h"
#include "DigSet.h"
#include "DlgD.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestCAView

IMPLEMENT_DYNCREATE(CTestCAView, CView)

BEGIN_MESSAGE_MAP(CTestCAView, CView)
	//{{AFX_MSG_MAP(CTestCAView)
	ON_COMMAND(IDM_RUN, OnRun1)
	ON_WM_TIMER()
	ON_COMMAND(IDM_SETCAR, OnSetcar)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(IDM_SET, &CTestCAView::OnSet)
	ON_COMMAND(IDM_SETD, &CTestCAView::OnSetd)
	ON_UPDATE_COMMAND_UI(IDM_STCA, &CTestCAView::OnUpdateStca)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestCAView construction/destruction

CTestCAView::CTestCAView()
: IsD(FALSE)
{
	// TODO: add construction code here
	m_utimepassed = 0;
	m_utimerate   = 0;
	IsSetting = FALSE;
	pcar_setting = NULL;
	IsMB = FALSE;
}

CTestCAView::~CTestCAView()
{
}

BOOL CTestCAView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestCAView drawing

void CTestCAView::OnDraw(CDC* pDC)
{
	CTestCADoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	UI.DrawLane(pDC,1);
	UI.DrawLane(pDC,2);
	
}

/////////////////////////////////////////////////////////////////////////////
// CTestCAView printing

BOOL CTestCAView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestCAView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestCAView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTestCAView diagnostics

#ifdef _DEBUG
void CTestCAView::AssertValid() const
{
	CView::AssertValid();
}

void CTestCAView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestCADoc* CTestCAView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestCADoc)));
	return (CTestCADoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestCAView message handlers

void CTestCAView::OnRun1() 
{

	CDialogRun dlg;
	dlg.m_urate = 500;
//	dlg.m_distset = ((CTestCAApp*)AfxGetApp())->GetDist();
	dlg.m_timeset = ((CTestCAApp*)AfxGetApp())->GetTime();
	dlg.m_vset = ((CTestCAApp*)AfxGetApp())->GetMAX_V();
	dlg.m_rec = ((CTestCAApp*)AfxGetApp())->GetTime();
	//����ʼ�ܶ�����Ϊ������ʽ
	dlg.m_kset = ((CTestCAApp*)AfxGetApp())->GetDist() / 3;
	//���ô󳵵�����ٶ�
	dlg.m_vset2 = ((CTestCAApp*)AfxGetApp())->GetMax_HV();
	

	if(dlg.DoModal() == IDOK){
		m_utimerate = dlg.m_urate;
//		((CTestCAApp*)AfxGetApp())->SetDist(dlg.m_distset);
		((CTestCAApp*)AfxGetApp())->SetTime(dlg.m_timeset);
		((CTestCAApp*)AfxGetApp())->SetMAX_V(dlg.m_vset);
		((CTestCAApp*)AfxGetApp())->SetRec(dlg.m_rec);
		((CTestCAApp*)AfxGetApp())->SetK(dlg.m_kset);
		((CTestCAApp*)AfxGetApp())->SetMax_HV(dlg.m_vset2);


		int m_ichoice = dlg.m_iradio;
		if(m_ichoice == 0){
			//��ʼ������
			simworld* p_theworld = new simworld(2);
			//��ʼ��Ԫ������
			const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
			ASSERT(p_theworld);
			p_theworld->InitLanes(dist);
			const int _time = ((CTestCAApp*)AfxGetApp())->GetTime();
			for(int t = 0; t < _time; t++){	
				p_theworld->RefreshV(t);
				p_theworld->RefreshX(t);
			}
			p_theworld->WriteRec();
			delete p_theworld;
		}
		else if(m_ichoice == 1){	
			simworld* p_theworld = new simworld(2);
			BeginSim(p_theworld);
			//������ɣ���¼�ٶ���Ϣ
			p_theworld->WriteRec();
			
			//������ɣ��ͷ��ڴ�
			delete p_theworld;
			
			//��ʼչ��
			SetTimer(1, m_utimerate,NULL);
		}
	}
}



void CTestCAView::BeginSim(simworld* p_simworld)
{
	//��ʼ��Ԫ������
	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
	ASSERT(p_simworld);
	p_simworld->InitLanes(dist);

	//������ӻ������ʼ��doc�ĵ�������lane�����cell����,Ϊ������ڴ�ռ�
	(GetDocument())->InitDocument();
	//��ʼ��¼ÿһ�ε�������
	const int _time = ((CTestCAApp*)AfxGetApp())->GetTime();
	for(int t = 0; t < _time; t++){	
		//simworldִ��һ������
		p_simworld->RefreshV(t);

		//TestCADoc�ͼ�¼һ��
		//�趨���Ƽ�¼������ʱ��1		
		Saved_Lane* p_lane1 = GetDocument()->m_saved_lanes1[t];
		p_lane1->m_itime = t;
		//�趨������Ӧ��id
		p_lane1->m_ilaneid = 1;

		//�趨���Ƽ�¼��Ԫ��1
		for(int d = 0; d < dist; d++){
			changeable_cell* p_cell = p_simworld->lanes[0]->cells[d]; 
			p_lane1->m_cells[d] = new Saved_Cell
				( p_cell->get_a_car(), p_cell->get_change(), p_cell->get_carid(),p_cell->get_carkind() );		
			if(p_cell->get_a_car()){
				p_lane1->m_cells[d]->GenerateCarname(p_cell->get_carname());
			}
		}

		//�趨���Ƽ�¼������ʱ��2
		Saved_Lane* p_lane2 = GetDocument()->m_saved_lanes2[t];
		p_lane2->m_itime = t;
		//�趨������Ӧ��id
		p_lane2->m_ilaneid = 2;


		//�趨���Ƽ�¼��Ԫ��2
		for(int _d = 0; _d < dist; _d++){
			changeable_cell* p_cell = p_simworld->lanes[1]->cells[_d]; 
			p_lane2->m_cells[_d] = new Saved_Cell
				( p_cell->get_a_car(), p_cell->get_change(), p_cell->get_carid(),p_cell->get_carkind() );
			if(p_cell->get_a_car()){
				p_lane2->m_cells[_d]->GenerateCarname(p_cell->get_carname());
			}
		}
		//���ƽ���,����λ��
		p_simworld->RefreshX(t);
	}

	//���ý�����
//	CRect rect;
//	CMainFrame* p_main = (CMainFrame*)GetParent();
//	p_main->m_wndStatusBar.GetItemRect(p_main->m_wndStatusBar.CommandToIndex(IDS_PROGRESS),&rect);
//a	p_main->m_progress.Create(WS_CHILD|WS_VISIBLE|PBS_SMOOTH,rect,&( p_main->m_wndStatusBar),123);

//	p_main->m_progress.SetRange(0, _time);
//	p_main->m_progress.SetStep(1);
}

void CTestCAView::EndSim()
{
	GetDocument()->DelDocument();

}

void CTestCAView::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent != 1)
		return;
	const int _time = ((CTestCAApp*)AfxGetApp())->GetTime();
	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
	if(m_utimepassed >= _time){
		KillTimer(1);
		EndSim();
		m_utimepassed = 0;
		MessageBox("Simulate End!");
		Invalidate();
		return;
	}

	//��ʼ��ʾ����
//	Invalidate();
	CClientDC dc(this);
	CDC* pDC = &dc;



	CString str;
	str.Format("step: %d",m_utimepassed);

	pDC->SetBkColor( RGB(255,255,255) );
	pDC->TextOut(50,50,str);

//	p_doc->m_saved_lanes1[m_utimepassed]->DrawLane(pDC ,rect);
//	p_doc->m_saved_lanes2[m_utimepassed]->DrawLane(pDC ,rect);
	UI.DrawCell(pDC,1,m_utimepassed);
	UI.DrawCell(pDC,2,m_utimepassed);

	m_utimepassed++;
	
//	((CMainFrame*)GetParent())->m_progress.StepIt();
	CView::OnTimer(nIDEvent);
}


void CTestCAView::OnSetcar() 
{
	// TODO: Add your command handler code here
	pcar_setting = new CDlgCar;
	//�˴�Ӧ����
	IsMB = TRUE;
	IsSetting = TRUE;
	pcar_setting->Create(IDD_DIAL_CAR,this);
	pcar_setting->ShowWindow(SW_SHOW);

	
}

void CTestCAView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);
	CDC* pDC = &dc;
	if(IsSetting){
		if(!pcar_setting)
			MessageBox("error!");
		UI.SetCar(point, pcar_setting->m_carkind,pDC);
	}
	if(IsD){
		UI.SetDetector(point,pDC);
	}
	CView::OnLButtonDown(nFlags, point);
}

void CTestCAView::OnSet()
{

	
}

void CTestCAView::OnSetd()
{
	IsD = TRUE;
	CDlgD* pdlg = new CDlgD;
	pdlg->Create(IDD_DLG_D,this);
	pdlg->ShowWindow(SW_SHOW);
}

void CTestCAView::OnUpdateStca(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck();
	
	// TODO: �ڴ������������û����洦��������
}
