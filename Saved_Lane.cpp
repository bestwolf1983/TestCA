// Saved_Lane.cpp: implementation of the Saved_Lane class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Saved_Lane.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(Saved_Lane, CObject, 1)

Saved_Lane::Saved_Lane()
{
	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
	try{
	m_cells.SetSize(dist);
	}
	catch(CMemoryException e){

	}
	m_itime = 0;
	m_ilaneid = 0;
}

Saved_Lane::~Saved_Lane()
{
	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
	for(int d = 0; d < dist; d++){
		delete m_cells[d];
	}
	m_cells.RemoveAll();
}

void Saved_Lane::Serialize(CArchive &ar){
	
}

//DEL void Saved_Lane::DrawLane(CDC *pDC, CRect& viewrect)
//DEL {
//DEL 	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
//DEL 	//初始化绘图参数
//DEL 	const UINT lane_length  = (viewrect.right - viewrect.left) * 0.95;
//DEL 	const UINT car_length   = lane_length / dist - 1;
//DEL 	const UINT lane_width   = car_length * 9 / 16;
//DEL 	const UINT car_width    = lane_width * 0.9;
//DEL 	
//DEL 	int cy;
//DEL 	if( m_ilaneid == 1){
//DEL 		cy = (viewrect.bottom - viewrect.top) / 2 - lane_width ;
//DEL 	}
//DEL 	else{
//DEL 		cy = (viewrect.bottom - viewrect.top) / 2 + lane_width ;
//DEL 	}
//DEL 
//DEL 	POINT* ptArray = new POINT[dist];
//DEL 	ptArray[0].x = ( viewrect.right - viewrect.left ) * 0.025;
//DEL 
//DEL 	//初始化绘图设备
//DEL 	CPen pen_car;
//DEL 
//DEL 	//选择设置笔刷
//DEL 	LOGBRUSH logBrushBottom; 
//DEL 	logBrushBottom.lbStyle = BS_SOLID; 
//DEL 	if( m_ilaneid == 1){
//DEL 		logBrushBottom.lbColor = RGB(255,128,0);
//DEL 	}
//DEL 	else{
//DEL 		logBrushBottom.lbColor = RGB(0,255,0);
//DEL 	}
//DEL 	logBrushBottom.lbHatch = 0; 
//DEL 	pen_car.CreatePen( PS_GEOMETRIC|PS_ENDCAP_SQUARE, car_width , &logBrushBottom );
//DEL 	CPen* pOldPen = pDC->SelectObject(&pen_car);
//DEL 
//DEL 	//初始化结束 
//DEL 
//DEL 
//DEL 
//DEL 	int istep =  lane_length / dist;
//DEL 
//DEL 	for(int d0 = 1; d0 < dist; d0++){
//DEL 		ptArray[d0].x = ptArray[d0-1].x + istep;
//DEL 		ptArray[d0].y = cy;	
//DEL 	}
//DEL 	//画小车
//DEL 	for(int d = 1; d < dist-1; d++){
//DEL 		int car_id = m_cells[d]->get_carid();
//DEL 		int change = m_cells[d]->get_change();
//DEL 		bool a_car = m_cells[d]->get_a_car();
//DEL 		if(a_car){
//DEL 			if(change > 0){
//DEL 				CPen pen_changed;
//DEL 
//DEL 				//设置笔刷
//DEL 				LOGBRUSH logBrushChange; 
//DEL 
//DEL 				logBrushChange.lbStyle = BS_SOLID; 
//DEL 				logBrushChange.lbColor = RGB(128,0,0);
//DEL 				logBrushBottom.lbHatch = 0; 
//DEL 				pen_changed.CreatePen( PS_GEOMETRIC|PS_ENDCAP_SQUARE, car_width , &logBrushChange );
//DEL 				CPen* p_oldpen = pDC->SelectObject(&pen_changed);
//DEL 				pDC->MoveTo(ptArray[d]);
//DEL 				pDC->LineTo(ptArray[d+1]);
//DEL 				pDC->SelectObject(&p_oldpen);
//DEL 				pen_changed.DeleteObject();
//DEL 			}
//DEL 			else{
//DEL 				pDC->MoveTo(ptArray[d]);
//DEL 				pDC->LineTo(ptArray[d+1]);
//DEL 			}
//DEL 			//画车的ID
//DEL 			char* carname = m_cells[d]->carname; 
//DEL 		//	CFont font;
//DEL 		//	font.CreatePointFont(50,"Times New Roman",NULL);
//DEL 		//	CFont* poldfont = pDC->SelectObject(&font);
//DEL 
//DEL 		//	pDC->DrawText(carname,-1,&rectid,DT_LEFT);
//DEL 		//	pDC->SelectObject(poldfont);
//DEL 
//DEL 			POINT ptText;
//DEL 			ptText.x = ptArray[d].x;
//DEL 			if( m_ilaneid == 1){
//DEL 				ptText.y = ptArray[d].y - 2 * lane_width; 
//DEL 			}
//DEL 			else{
//DEL 				ptText.y = ptArray[d].y + lane_width; 
//DEL 			}
//DEL 
//DEL 			CString str(carname);
//DEL 
//DEL 		    CFont font;
//DEL 		    font.CreatePointFont(lane_width*10,"Times New Roman",NULL);
//DEL 			pDC->SetBkColor( RGB(255,255,255) );
//DEL 			pDC->SelectObject(&font);
//DEL 			pDC->TextOut(ptText.x, ptText.y, str);
//DEL 			font.DeleteObject();
//DEL 		}	
//DEL 	}
//DEL 	pDC->SelectObject(pOldPen);
//DEL 
//DEL 	//画小车结束,释放资源
//DEL 	delete[] ptArray;
//DEL 	pen_car.DeleteObject();
//DEL 
//DEL }

