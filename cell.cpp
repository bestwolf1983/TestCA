// cell.cpp: implementation of the cell class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "cell.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cell::cell() : cell_id(0),itime(-1)
{
#ifdef _DEBUG
	itest = 0;

	itestgap = -1;
#endif  
	thecar = new CVehicle(false,0,0,-1);
	thedetector = new CDetector();
}

cell::~cell()
{
	if(thecar != NULL)
		delete thecar;
	thecar = NULL;
	if(thedetector != NULL)
		delete thedetector;
	thedetector = NULL;
}


cell::cell(bool is_car) : cell_id(0),itime(-1)
{
#ifdef _DEBUG
	itest = 0;

	itestgap = -1;
#endif
	thecar = new CVehicle(is_car,0,0,-1);
	thedetector = new CDetector();
}

void cell::set_v(int iv){
	thecar->v = iv;
}

void cell::set_a_car(bool t) {
	thecar->valuable = t;
}

int cell::get_v() const{
	return thecar->v;
}

bool cell::get_a_car() const{
	return thecar->valuable;
}

void cell::set_carid(int id){
	thecar->car_id = id;
}

int cell::get_carid() const{
	return thecar->car_id;
}

void cell::set_cellid(int id){
	cell_id = id;
}

int cell::get_cellid() const{
	return cell_id;
}


char* cell::get_carname() 
{
	return thecar->car_name;
}

void cell::set_carname(char* name,int lane_id)
{	
	if( lane_id != 0){
		sprintf(thecar->car_name,"%d-%d",lane_id,thecar->car_id);
	}
	else{
		assert(strlen(name)<=10);
		strcpy(thecar->car_name,name);		
	}
}
void cell::set_timetag(int itime){
    this->itime = itime;
}

int cell::get_timetag() const{
    return itime;
}

void cell::set_carkind(int carkind){
	thecar->icarkind = carkind;
}

int cell::get_carkind() const{
	return thecar->icarkind;
}
void cell::SetPos(int d){
	thecar->pos = d;
}
int cell::GetPos() const{
	return thecar->pos;
}
void cell::SetDInfo(){
	thedetector->count+=1;
}
int cell::GetDInfo() const{
	return thedetector->count;
}

void cell::SetDID(int id){
	thedetector->id = id;
}
int cell::GetDID() const{
	return thedetector->id;
}
bool cell::GetD()const{
	return thedetector->hasd;
}
void cell::SetD(bool d){
	thedetector->hasd = d;
}
