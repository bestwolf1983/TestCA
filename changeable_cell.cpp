// changeable_cell.cpp: implementation of the changeable_cell class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "changeable_cell.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

changeable_cell::changeable_cell(): lanechangesignal(0)
{

}

changeable_cell::changeable_cell(bool has_car) : cell(has_car),lanechangesignal(0),ipretag(-1){
#ifdef _DEBUG
    iothergap = -1;
#endif
}

changeable_cell::~changeable_cell()
{

}

void changeable_cell::set_change(int nlaneid){
	//lanechangesignal是对应所换车道的laneid，0代表不换车道
	lanechangesignal = nlaneid;
}

int changeable_cell::get_change(){

	return lanechangesignal;
}


