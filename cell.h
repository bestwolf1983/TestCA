// cell.h: interface for the cell class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CELL_H__5BF1D396_29F7_48CC_9EF7_5AC977471362__INCLUDED_)
#define AFX_CELL_H__5BF1D396_29F7_48CC_9EF7_5AC977471362__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Vehicle.h"
#include "Detector.h"

class cell  
{
public:
#if defined _DEBUG
	int itest;
    int itestgap;

#endif 
	cell();
	cell(bool);
	virtual ~cell();

protected:
//	char car_name[10];
//	int v;
//	bool has_car;
//	int car_id;
	int cell_id;
    int itime;
//	int icarkind;

public:
	void set_carname(char* name,int lane_id = 0);
	void set_v(int iv);
	void set_a_car(bool t);
	void set_carid(int id);
	void set_cellid(int id);
    void set_timetag(int itime);
	void set_carkind(int carkind);

	char* get_carname() ;
	int get_v() const;
	bool get_a_car() const;
	int get_carid() const;
	int get_cellid() const;
    int get_timetag() const;
	int get_carkind() const;
public:
	//记录车辆运行过的格子总数
	int GetPos() const;
	void SetPos(int d);
	int GetDInfo() const;
	void SetDInfo();
	int GetDID() const;
	void SetDID(int id);
	void SetD(bool d);
	bool GetD()const;

protected:
	//10.25新增代码，分离元胞与小汽车
	CVehicle* thecar;
	CDetector* thedetector;

};

#endif // !defined(AFX_CELL_H__5BF1D396_29F7_48CC_9EF7_5AC977471362__INCLUDED_)
