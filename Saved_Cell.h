// Saved_Cell.h: interface for the Saved_Cell class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAVED_CELL_H__2F429653_5DEB_4FF9_A1DC_85D962BEE663__INCLUDED_)
#define AFX_SAVED_CELL_H__2F429653_5DEB_4FF9_A1DC_85D962BEE663__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "changeable_cell.h"

class Saved_Cell  : public CObject, public changeable_cell
{
public:
	Saved_Cell();
	Saved_Cell(bool bhas_car, int isignal, int icar_id, int icar_kind); 
	virtual ~Saved_Cell();
	DECLARE_SERIAL(Saved_Cell)
public:
	virtual void Serialize(CArchive& ar);
public:
	char carname[10];
	void GenerateCarname(char* name);

};

#endif // !defined(AFX_SAVED_CELL_H__2F429653_5DEB_4FF9_A1DC_85D962BEE663__INCLUDED_)
