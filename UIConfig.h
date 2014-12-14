// UIConfig.h: interface for the CUIConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UICONFIG_H__5D3D30EF_35BF_41D0_8AAD_9278BA1E14D2__INCLUDED_)
#define AFX_UICONFIG_H__5D3D30EF_35BF_41D0_8AAD_9278BA1E14D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUIConfig  
{
public:
	CUIConfig();
	virtual ~CUIConfig();
public:
	void SetCar(CPoint point, int carkind,CDC* pDC);
	BOOL DrawLane(CDC* pDC,UINT laneid);
	BOOL DrawCell(CDC* pDC,UINT laneid, int t);
	//小型车族
	int* ar_cars1;
	int* ar_cars2;
	//重车族
	vector<POINT> ptHeavyCar;
	//检测器族
	vector<int> iDetector;
private:
	BOOL InitLaneInterface();
	//lanes[2]代表两条车道的界面属性
	CRect lanes[2];
	//记录每个元胞格的位置的点位族，代表每个元胞的左上角坐标
	POINT* ptcells1;
	POINT* ptcells2;

public:
	void SetDetector(CPoint point, CDC* pDC);
public:
	// 清除仿真界面所有单元
	void ClearAll(void);
};

#endif // !defined(AFX_UICONFIG_H__5D3D30EF_35BF_41D0_8AAD_9278BA1E14D2__INCLUDED_)
