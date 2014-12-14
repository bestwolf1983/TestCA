// changeable_cell.h: interface for the changeable_cell class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHANGEABLE_CELL_H__5019509C_BE40_488E_BC4C_58DA9BE2E5A8__INCLUDED_)
#define AFX_CHANGEABLE_CELL_H__5019509C_BE40_488E_BC4C_58DA9BE2E5A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cell.h"

class changeable_cell : public cell  
{
public:
	changeable_cell();
	changeable_cell(bool has_car);
	virtual ~changeable_cell();
	//∏Ωº” Ù–‘
protected:
	int lanechangesignal;

public:

	void set_change(int nlaneid);
	int get_change();
public:
    int ipretag;
#ifdef _DEBUG
    int iothergap;
#endif 
};

#endif // !defined(AFX_CHANGEABLE_CELL_H__5019509C_BE40_488E_BC4C_58DA9BE2E5A8__INCLUDED_)
