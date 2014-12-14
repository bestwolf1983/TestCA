// Vehicle.cpp: implementation of the CVehicle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "testca.h"
#include "Vehicle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVehicle::CVehicle(bool bvaluable,int id,int iv,int kind) : valuable(bvaluable),car_id(id),v(iv),icarkind(kind),pos(0)
{

}

CVehicle::~CVehicle()
{

}
