// Saved_Lane.h: interface for the Saved_Lane class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAVED_LANE_H__A4457167_E22E_4840_8D95_59DB89C8E0EF__INCLUDED_)
#define AFX_SAVED_LANE_H__A4457167_E22E_4840_8D95_59DB89C8E0EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Saved_Cell.h"

class Saved_Lane  : public CObject
{
public:
	Saved_Lane();
	virtual ~Saved_Lane();
	DECLARE_SERIAL(Saved_Lane)
public:
	virtual void Serialize(CArchive& ar);
public:

	int m_itime;
	int m_ilaneid;
	CTypedPtrArray<CObArray, Saved_Cell*> m_cells;


};

#endif // !defined(AFX_SAVED_LANE_H__A4457167_E22E_4840_8D95_59DB89C8E0EF__INCLUDED_)
