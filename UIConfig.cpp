// UIConfig.cpp: implementation of the CUIConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "testca.h"
#include "UIConfig.h"
#include "TestCADoc.h"
#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUIConfig::CUIConfig() 
{
	const int d = ((CTestCAApp*)AfxGetApp())->GetDist();
	ar_cars1 = new int[d];
	ar_cars2 = new int[d];
	for(int it = 0; it < d; it++){
		ar_cars1[it] = 0;
		ar_cars2[it] = 0;
	}
	ptcells1 = new POINT[d];
	ptcells2 = new POINT[d];
	ptHeavyCar.reserve(5);
	iDetector.reserve(10);
}

CUIConfig::~CUIConfig()
{
	if(ar_cars1 != NULL){
		delete[] ar_cars1;
		ar_cars1 = NULL;
	}
	if(ar_cars2 != NULL){
		delete[] ar_cars2;
		ar_cars2 = NULL;
	}
	if(ptcells1 != NULL){
		delete[] ptcells1;
		ptcells1 = NULL;
	}
	if(ptcells2 != NULL){
		delete[] ptcells2;
		ptcells2 = NULL;
	}
}

BOOL CUIConfig::DrawCell(CDC* pDC,UINT laneid, int t)
{
	if(!InitLaneInterface())
		return FALSE;
	CTestCADoc* pdoc = (CTestCADoc*)( ((CMainFrame*)AfxGetMainWnd())->GetActiveDocument() );
	
	//确定是哪条车道
	CTypedPtrArray<CObArray, Saved_Lane*>* savedlanes;
	COLORREF carcolor;
	COLORREF othercarcolor;
	POINT* ptArray;

	if( laneid == 1 ){
		savedlanes = &(pdoc->m_saved_lanes1);
		carcolor = RGB(255,255,0);
		othercarcolor = RGB(0,0,255);
		//确定点坐标
		ptArray = ptcells1;

	}
	else if( laneid == 2 ){
		savedlanes = &(pdoc->m_saved_lanes2);		
		carcolor = RGB(0,0,255);
		othercarcolor = RGB(255,255,0);
		//确定点坐标
		ptArray = ptcells2;
	}
	else{
		return FALSE;
	}
	//画元胞
	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
	UINT icarlength = lanes[0].Width() / dist;
	Saved_Cell* pcell;
	for(int d = 0; d < dist; d++){		
		POINT lefttop;
		POINT rightbottom;
		lefttop.x = ptArray[d].x + 1;
		lefttop.y = ptArray[d].y;
		rightbottom.x = ptArray[d].x + icarlength - 1;
		rightbottom.y = ptArray[d].y + lanes[laneid-1].Height();
		CRect carrect(lefttop,rightbottom);

		pcell = (*savedlanes)[t]->m_cells[d];
		if(pcell->get_a_car()){
			pDC->FillSolidRect(&carrect,carcolor);	
			if(atoi(&pcell->carname[0]) != laneid)
				pDC->FillSolidRect(&carrect,othercarcolor);	
			if(pcell->get_carkind() == 0)
				pDC->FillSolidRect(&carrect,RGB(255,0,0));
		}
		else{
			pDC->FillSolidRect(&carrect,RGB(192,192,192));				
		}
	}	
	return TRUE;	
}

BOOL CUIConfig::DrawLane(CDC* pDC,UINT laneid)
{
	if(!InitLaneInterface())
		return FALSE;
	//画路面
	CRect* pRect = &lanes[laneid-1];
	pDC->FillSolidRect(pRect,RGB(192,192,192));
	//画元胞的方框
	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
	POINT* ptArray;
	if( laneid == 1 ){
		ptArray = ptcells1;
	}
	else if(laneid == 2){
		ptArray = ptcells2;
	}
	else 
		return FALSE;

	CPen pen(PS_SOLID,0,RGB(0,255,128));
	CPen* poldpen = pDC->SelectObject(&pen);

	for(int j = 0; j < dist; j++){
		pDC->MoveTo(ptArray[j]);
		pDC->LineTo(ptArray[j].x,ptArray[j].y + lanes[laneid-1].Height());
	}


	pDC->SelectObject(poldpen);
	pen.DeleteObject();
	return TRUE;
}

BOOL CUIConfig::InitLaneInterface()
{
	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
	CRect rect;
	GetClientRect( ( (CMainFrame*) (AfxGetApp()->GetMainWnd()) )->GetActiveView()->m_hWnd,&rect);

	const UINT lane_length  = (rect.right - rect.left) * 0.95;
	const UINT car_length = lane_length / dist * 0.9;
	const UINT lane_width = car_length * 9 / 16;
	const UINT car_width = lane_width * 0.9;


	lanes[0].left = (rect.Width() - lane_length) / 2;
	lanes[0].right = rect.Width() - (rect.Width() - lane_length) / 2;
	lanes[0].top = rect.Height() / 2 - lane_width / 2 - lane_width;
	lanes[0].bottom = rect.Height() / 2 - lane_width / 2;

	lanes[1].left = (rect.Width() - lane_length) / 2;
	lanes[1].right = rect.Width() - (rect.Width() - lane_length) / 2;
	lanes[1].top = rect.Height() / 2 + lane_width / 2 ;
	lanes[1].bottom = rect.Height() / 2 + lane_width / 2 + lane_width;

	UINT icarlength = lanes[0].Width() / dist;
	ptcells1[0].x = lanes[0].left;
	ptcells1[0].y = lanes[0].top;

	for(int i = 1; i < dist; i++){
		ptcells1[i].x = ptcells1[i-1].x + icarlength;
		ptcells1[i].y = ptcells1[i-1].y;
	}

	ptcells2[0].x = lanes[1].left;
	ptcells2[0].y = lanes[1].top;

	for(int j = 1; j < dist; j++){
		ptcells2[j].x = ptcells2[j-1].x + icarlength;
		ptcells2[j].y = ptcells2[j-1].y;
	}
	return TRUE;
}
/*
carkind为车辆类型，0为重型车，1为一般车
*/
void CUIConfig::SetCar(CPoint point, int carkind,CDC* pDC)
{
	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
	UINT icarlength = lanes[0].Width() / dist;
	UINT icarwidth = lanes[0].Height();
	POINT* ptcells;
	int* ar_cars;

	//sign为检测车辆属于哪个车道的标志
	int sign = 0;
	//先检测属于哪个车道
	if(lanes[0].PtInRect(point)){
		ptcells = ptcells1;
		ar_cars = ar_cars1;
		sign = 1;
	}
	else if((lanes[1].PtInRect(point))){

		ptcells = ptcells2;
		ar_cars = ar_cars2;
		sign = 2;
	}
	else
		return;
	//再检测属于哪个方格
	CRect rect;
	//now表示第几个单元格被选中
	int now = 0;
	for(int d = 0; d < dist; d++){
		rect.top = ptcells[d].y;
		rect.left = ptcells[d].x;
		rect.bottom = rect.top + icarwidth;
		rect.right = rect.left + icarlength;
		if(rect.PtInRect(point)){
			now = d;
			ar_cars[d] = 1;
			break;
		}
	}

	if(carkind == 0){
		POINT pt;
		pt.x = now;
		pt.y= sign;
		ptHeavyCar.push_back(pt);
		pDC->FillSolidRect(&rect,RGB(255,0,0));
	}
	else if(carkind == 1){
		if(sign == 1)
			pDC->FillSolidRect(&rect,RGB(255,255,0));
		else if(sign == 2)
			pDC->FillSolidRect(&rect,RGB(0,0,255));
	}
}



void CUIConfig::SetDetector(CPoint point, CDC* pDC)
{
	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
	CRect rect;
	int icarheight = lanes[0].Height();
	int icarlength = lanes[0].Width()/dist;
	//now表示第几个单元格被选中
	int now = 0;
	for(int d = 0; d < dist; d++){
		rect.top = ptcells1[d].y;
		rect.left = ptcells1[d].x;
		rect.bottom = ptcells2[d].y + icarheight + 1;
		rect.right = rect.left + icarlength;
		if(rect.PtInRect(point)){
			iDetector.push_back(d);
			CRect rect1;
			rect1.bottom = rect.top - 1;
			rect1.top = rect.top - 3;
			rect1.left = rect.left;
			rect1.right = rect.right;

			CRect rect2;
			rect2.top = rect.bottom + 1;
			rect2.bottom = rect.bottom + 3;
			rect2.left = rect.left;
			rect2.right = rect.right;

			pDC->FillSolidRect(&rect1,RGB(0,255,0));
			pDC->FillSolidRect(&rect2,RGB(0,255,0));
		}
	}	
}

// 清除仿真界面所有单元
void CUIConfig::ClearAll(void)
{
	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
	iDetector.clear();
	ptHeavyCar.clear();
	for(int it = 0; it < dist; it++){
		ar_cars1[it] = 0;
		ar_cars2[it] = 0;
	}	
}
