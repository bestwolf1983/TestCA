// Vehicle.h: interface for the CVehicle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VEHICLE_H__ACF35441_49A9_4275_8B87_0DE90A50B2FB__INCLUDED_)
#define AFX_VEHICLE_H__ACF35441_49A9_4275_8B87_0DE90A50B2FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class cell;
class Saved_Cell;
class CVehicle  
{
friend class cell;
friend class Saved_Cell;
public:
	CVehicle(bool bvaluable,int car_id,int iv,int kind);
	virtual ~CVehicle();
private:
	bool valuable;
	int car_id;
	char car_name[15];
	int icarkind;
	int v;
	int pos;
};

#endif // !defined(AFX_VEHICLE_H__ACF35441_49A9_4275_8B87_0DE90A50B2FB__INCLUDED_)
