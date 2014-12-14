// simworld.cpp: implementation of the simworld class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "simworld.h"
#include "MainFrm.h"
#include "TestCAView.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



simworld::~simworld()
{

	while(!lanes.empty()){
		lane* p_lane = lanes.back();
		delete p_lane;
		lanes.pop_back();
	}
}

simworld::simworld(int nLanes){
	pUI = &(((CTestCAView*)(((CMainFrame*)(AfxGetApp()->GetMainWnd()))->GetActiveView()))->UI);	

	//初始化包含的车道
	for(int i = 1; i < nLanes+1; i++){
		lanes.push_back( new changeable_lane(i) );
	}

	/*！----------------------------------------------------------
	此处，在多条车道领域可改为自动识别，由于目前只有两条车道，所以手动设定
	----------------------------------------------------------！*/

	lanes[0]->Set_Other_Lane( lanes[1] );
	lanes[1]->Set_Other_Lane( lanes[0] );

	
}


void simworld::RefreshV(int t)
{
	lanes[0]->RefreshV(t);
	lanes[1]->RefreshV(t);
}

void simworld::RefreshX(int t)
{
	lanes[0]->RefreshX(t);
	lanes[1]->RefreshX(t);
}

void simworld::InitLanes(int dist)
{
	BOOL IsMB = ((CTestCAView*)(((CMainFrame*)(AfxGetApp()->GetMainWnd()))->GetActiveView()))->IsMB;

	// 初始化仿真元胞
	//如果模拟移动瓶颈则需读取设定的卡车、普通车位置
	if(IsMB){
		SetInitCar(pUI->ar_cars1,pUI->ar_cars2,pUI->ptHeavyCar);
	}
	//如果是普通模拟则设定密度
	else{
		lanes[0]->initlane(dist);
		lanes[1]->initlane(dist);	
	}

	//设置检测器
	int DID = 0;
	for( vector<int>::iterator it = pUI->iDetector.begin(); it != pUI->iDetector.end(); it++ ){
		for(vector<changeable_lane*>::iterator it_lane = lanes.begin(); it_lane != lanes.end(); it_lane++ ){
			(*it_lane)->cells[*it]->SetD(true);
			(*it_lane)->cells[*it]->SetDID(DID);
		}
		DID++;
	}
	//读取仿真数据结束，清除仿真界面数据
	pUI->ClearAll();
}

void simworld::SetInitCar(int *lane1, int *lane2, vector<POINT>& ptHeavyCar)
{
	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
	const int MAX_V = ((CTestCAApp*)AfxGetApp())->GetMAX_V();

	//一些初始化的工作
	for(vector<changeable_lane*>::iterator it = lanes.begin();it != lanes.end(); it++){
		for(int count = 0; count < dist; count++){
			(*it)->cells.push_back(new changeable_cell(false));
			//设置元胞的cellid，用以计算gap[count]
			(*it)->cells.back()->set_cellid(count);
		//		cells.back()->set_carname(0,getlaneid());
		}

		//开始仿真，车辆数从0开始计数 
		(*it)->car_count = 0;
		(*it)->isave = 0;
	}

	//从CUIConfig中读取设置的数据
	int j = 0;
	for(int d = 0; d < dist; d++){
		if( lane1[d] ){
			lanes[0]->cells[d]->set_a_car(true);
			lanes[0]->cells[d]->set_carid(j);
			lanes[0]->cells[d]->set_carname(0,lanes[0]->getlaneid());
			lanes[0]->cells[d]->set_carkind(1);
			lanes[0]->car_count++;
			j++;	
		}
		if( lane2[d] ){
			lanes[1]->cells[d]->set_a_car(true);
			lanes[1]->cells[d]->set_carid(j);
			lanes[1]->cells[d]->set_carname(0,lanes[1]->getlaneid());
			lanes[1]->cells[d]->set_carkind(1);
			lanes[1]->car_count++;
			j++;	
		}	
	}
	for(vector<POINT>::iterator it1 = ptHeavyCar.begin();it1 != ptHeavyCar.end();it1++){
		//y的值为1或2，对应于lanes[0]和lanes[1]
		lanes[(*it1).y-1]->cells[(*it1).x]->set_a_car(true);
		lanes[(*it1).y-1]->cells[(*it1).x]->set_carid(j);
		//设置重型车的laneid为3，代表重型车
		lanes[(*it1).y-1]->cells[(*it1).x]->set_carname(0,3);	
		lanes[(*it1).y-1]->cells[(*it1).x]->set_carkind(0);	
	}


	for(int x = 0; x < dist; x++){
		//设置lane1速度
		if(lanes[0]->cells[x]->get_a_car()){
			int gap0 = lanes[0]->getgap(x);
			gap0 = gap0 > MAX_V ? MAX_V : gap0;
			lanes[0]->cells[x]->set_v(gap0);
			lanes[0]->cells[x]->set_change(0);	
		}
		//设置lane2速度
		if(lanes[1]->cells[x]->get_a_car()){
			int gap1 = lanes[0]->getgap(x);
			gap1 = gap1 > MAX_V ? MAX_V : gap1;
			lanes[1]->cells[x]->set_v(gap1);
			lanes[1]->cells[x]->set_change(0);	
		}
	}

	//设置慢车速度
	int HV = ((CTestCAApp*)AfxGetApp())->GetMax_HV();
	for(vector<POINT>::iterator itv = ptHeavyCar.begin();itv != ptHeavyCar.end();itv++){
		//y的值为1或2，对应于lanes[0]和lanes[1]
		int gap = lanes[(*itv).y-1]->getgap((*itv).x);
		gap = gap < HV ? gap : HV;
		lanes[(*itv).y-1]->cells[(*itv).x]->set_v(gap);
		lanes[(*itv).y-1]->cells[(*itv).x]->set_change(0);

	}
}

// 记录仿真最后阶段的速度信息
bool simworld::WriteRec(void)
{
	ofstream of("result.txt",ios::app);
	if(!of)
		return false;

	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
	const int time = ((CTestCAApp*)AfxGetApp())->GetTime();
	double sum = 0;
	int count = 0;
	for(vector<changeable_lane*>::iterator it = lanes.begin(); it != lanes.end(); it++){
		for(int d = 0; d < dist; d++){
			if((*it)->cells[d]->get_a_car()){
				double mile = (double)(*it)->cells[d]->GetPos() * 7.5 *3.6;
				if((*it)->cells[d]->get_carkind()!=0){
					sum += (mile/time);
					count += 1;
				}
			}
		}
	}	
	of<<"k="<<((CTestCAApp*)AfxGetApp())->GetK()<<endl;
	of<<"average speed:"<<sum/count<<endl;
	of.close();

	lanes[0]->saverecord();
	lanes[1]->saverecord();
	return false;
}
