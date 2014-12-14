// simworld.h: interface for the simworld class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMWORLD_H__CB3D0FE1_A54F_4E01_B3E8_28855CD091E2__INCLUDED_)
#define AFX_SIMWORLD_H__CB3D0FE1_A54F_4E01_B3E8_28855CD091E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "changeable_lane.h"
#include "TestCAView.h"
class CUIConfig;


class simworld  
{
public:
	void SetInitCar(int* lane1,int* lane2, vector<POINT>& ptHeavyCar);
	void InitLanes(int dist);

	void RefreshV(int t);
	void RefreshX(int t);
	virtual ~simworld();

	simworld(int nLanes);
	vector<changeable_lane*> lanes;

private:
	CUIConfig* pUI;
public:
	// 记录仿真最后阶段的速度信息
	bool WriteRec(void);

};

#endif // !defined(AFX_SIMWORLD_H__CB3D0FE1_A54F_4E01_B3E8_28855CD091E2__INCLUDED_)
