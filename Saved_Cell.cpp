// Saved_Cell.cpp: implementation of the Saved_Cell class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Saved_Cell.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(Saved_Cell, CObject, 1)

Saved_Cell::Saved_Cell()
{
	carname[0] = '\0';
}

Saved_Cell::~Saved_Cell()
{

}

Saved_Cell::Saved_Cell(bool bhas_car, int isignal, int icar_id,int icar_kind)
{
	thecar->valuable    = bhas_car;
	lanechangesignal    = isignal;
	thecar->car_id      = icar_id;
	thecar->icarkind = icar_kind;

}

void Saved_Cell::Serialize(CArchive &ar){

}


void Saved_Cell::GenerateCarname(char* name)
{	
	assert( strlen(name) <= 10 );
	strcpy(carname,name);
}
