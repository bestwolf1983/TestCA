// changeable_lane.h: interface for the changeable_lane class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHANGEABLE_LANE_H__7523C5CF_32F0_49BF_9EC7_B1440C616701__INCLUDED_)
#define AFX_CHANGEABLE_LANE_H__7523C5CF_32F0_49BF_9EC7_B1440C616701__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "lane.h"
#include "changeable_cell.h"

class changeable_lane : public lane  
{
public:
	changeable_lane(int);
	virtual ~changeable_lane();

	virtual int GetLaneChangeSignal(const int cell_index,int& v_changed) ;
	void set_change_velocity(int index,lane* p_lane_other);
protected:
	changeable_lane* p_taget_lane;

public:
	void RefreshX(int t);
	void RefreshV(int t);
	void Set_Other_Lane(changeable_lane* p_other_lane);
	changeable_lane* Get_Other_Lane() const;
    vector<changeable_cell*>& GetCells(const int index,const int change_signal,vector<changeable_cell*>& tempvec);
	void RefreshX_STCA(int t);
	void RefreshV_STCA(int);
};

#endif // !defined(AFX_CHANGEABLE_LANE_H__7523C5CF_32F0_49BF_9EC7_B1440C616701__INCLUDED_)
