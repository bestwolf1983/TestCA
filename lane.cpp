// lane.cpp: implementation of the lane class.
//
//////////////////////////////////////////////////////////////////////
#include <memory.h>
#include "stdafx.h"
#include "lane.h"

class CTestCAView;

class CUIConfig;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////





lane::~lane()
{
	delete [] buf;
	char filename[20];
	sprintf(filename,"lane%d.bmp",getlaneid());
	pbmp->SaveImg(filename);
	delete pbmp;
	while(!cells.empty()){
		changeable_cell* p_cell = cells.back();
		delete p_cell;
		cells.pop_back();
	}	
}

lane::lane(int nLaneid) {
	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();

	laneid = nLaneid;
	srand((unsigned)time(NULL));
	buf = new char[10*(dist+1)+10];

	car_count = 0;
    isave = 0;	
	
	int w = (4 - dist % 4) % 4 + dist;
	int time = ((CTestCAApp*)AfxGetApp())->GetTime();
	int h = time > dist ? dist : time; 
	pbmp = new CBmp(w,h);


}



bool lane::is_generate_car(){

	int irandseed = rand() % 10;
	if(irandseed < 5)
		return true;
	else 
		return false;
}

bool lane::is_accelerate(){

	int irandseed = rand() % 10;
	if(irandseed < 5)
		return true;
	else 
		return false;
}

/*-------------------------------------------------------
功能：计算指定序列前方可以最远到达的空格数
输入：指定序列
输出：空格数
--------------------------------------------------------*/

int lane::getgap( int index){
	int MAX_V = ((CTestCAApp*)AfxGetApp())->GetMAX_V();
	int DIST  = ((CTestCAApp*)AfxGetApp())->GetDist();

	if( index > DIST - MAX_V -1 ){
		vector<const changeable_cell* > tempv;
		tempv.reserve(MAX_V);
		int tempi = 0;
		for(int i = index + 1 ; i < DIST; i++){
			tempv.push_back( cells[i] );
		}
		for(int j = 0; j < index + MAX_V - (DIST-1) ; j++){
			tempv.push_back( cells[j] );
		}
		vector<const changeable_cell*>::iterator it = tempv.begin();

		int gap = 0;
		while(it != tempv.end() ){

			if( (*it)->get_a_car() ){
				assert( gap <= MAX_V); 
				return gap;
			}
			gap++;
      		it++;
		}
		return MAX_V;
	}
	else{
		vector<changeable_cell*>::iterator it = cells.begin() + index;
        assert( index + MAX_V  <= DIST - 1 );
		int gap;
        int ii = 0;
		while( ii < MAX_V ){
			it++;
			if( (*it)->get_a_car() ){
				gap = (*it)->get_cellid() - cells[index]->get_cellid() - 1;
				return gap;
			}
            ii++;
		}
		gap = MAX_V;
		return gap;
	}
}


/*-------------------------------------------------------
功能：在满足一定条件下，将缓存中的内容记录到指定文件中
输入：要记录的缓存头指针，以及要记录的文件名
输出：记录成功与否
--------------------------------------------------------*/
bool lane::savetrace(char *p , const char *name){
	//icount 的作用是计时
	int rec = ((CTestCAApp*)AfxGetApp())->GetRec();
	int _time =  ((CTestCAApp*)AfxGetApp())->GetTime();
	
	assert(rec <= _time);
	if( icount < _time - rec){
		isave = 0;
		return false;
	}
	this->buf[isave] = '\0';
	
	ofstream os(name,ios::app); 
	os<<p;
	os.close();
	//记录索引清零 
	isave = 0;		
	return true;
}




int lane::getlaneid(){
	return laneid;
}

void lane::setlaneid(int id){
	
	laneid = id;
}

/*-------------------------------------------------------
功能：设置lane对象的元胞
输入：元胞的总个数，其中最后一个为消失格
输出：将管理cell的vector压入cell对象，并对对象进行初始设置
--------------------------------------------------------*/
void lane::initlane(const int d)
{
	//一些初始化的工作
	for(int count = 0; count < d; count++){
		cells.push_back(new changeable_cell(false));
		//设置元胞的cellid，用以计算gap[count]
		cells.back()->set_cellid(count);
//		cells.back()->set_carname(0,getlaneid());
	}
	//开始仿真，车辆数从0开始计数 
	car_count = 0;
	isave = 0;

	//为初始车道设置密度
	int k = ((CTestCAApp*)AfxGetApp())->GetK();	
	SetLaneK(k);
}
/*-------------------------------------------------------
功能：将仿真的记录通过变换录入缓存
输入：要记录的单元格的序列
输出：将序列对应信息输入到缓存
--------------------------------------------------------*/
void lane::saveBuf(int d)
{
	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
	//直接显示速度符号
	int mapping[6] = {0,1,2,3,4,5};
	//转化为灰度图像后符号
//	int mapping[6] = {1,2,3,4,5,6};

	if( d <= dist-1 ){
		if(cells[d]->get_a_car() && !( cells[d]->get_change() ) ){
			//直接将速度转化为字符
			//buf[isave] = cells[d]->get_v() + 48;

			//判断测试
			assert(cells[d]->get_v() <= 5 && cells[d]->get_v() >= 0);

			//测试结束
			buf[isave] = mapping[cells[d]->get_v()] + 48 ;	
		}
		else if( cells[d]->get_a_car() && ( cells[d]) ->get_change() ){
			//换车道则显示为A、B等 
			//	buf[isave] = cells[d]->get_v() + 65;
			//判断测试
			assert(cells[d]->get_v() <= 5 && cells[d]->get_v() >= 0);
			//测试结束

			buf[isave] = mapping[cells[d]->get_v()] + 48 ;
		}
		else{
			buf[isave] = ' ';
		//	buf[isave] = 0 + 48;
		}
	    if(d == 0){
		    //buf[isave] = '\n';
		    buf[++isave] = '\n';
	    }
	}

	//输出空格供matlab读取用
	//	buf[++isave] = ' ';
	isave++;
}



/*-------------------------------------------------------
功能：将给定的流量换算为彻底车道上应有车辆的百分率
输入：流量
输出：换算后的百分率
--------------------------------------------------------*/
int lane::SetLaneQ(const int q)
{
		const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
	int inum = rand() % dist;
	
	//换算成产生车辆的百分率
	drate = ((double)q / (double)3600) * 100;
	return drate;
}

int compare(const void* a, const void* b){
	return (*(int*)a - *(int*)b);	
}
/*-------------------------------------------------------
功能：用初始密度初始化车道上的车辆,在initlane中应用此函数
输入：指定密度
输出：设置成功输出1
--------------------------------------------------------*/
int lane::SetLaneK(const int k)
{
	//随机模式
	const int MAX_V = ((CTestCAApp*)AfxGetApp())->GetMAX_V();
	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
	//133 = 1000/7.5,是换算成每个方格应有的平均车辆数
	int ktransform = k * (dist - MAX_V) / 133;

	//dist-MAX_V  的位置都是可以放初始车辆的

	int* itemparray = new int[dist-1];
	int icount = 0;
	itemparray[0] = rand() % dist;

	
	int itemppos = 0;

	//验证随机产生的车辆位置的唯一性
	bool is_explicity = true;
	//确保密度不会大于整个环境的元胞个数
	if( ktransform > dist )
		ktransform = dist;
	while ( icount < ktransform ){
		itemppos = rand() % dist;
		for(int i = 0; i <= icount; i++){
			if( itemparray[i] == itemppos){
				is_explicity = false;
				break;
			}
		}
		if( is_explicity )
			itemparray[++icount] = itemppos;
		is_explicity = true;
	}
	//验证结束
	int iact_cell = 0;
	qsort( itemparray, icount ,sizeof(int) , compare); 
	for(int j = 0; j <= icount; j++){
		iact_cell = itemparray[ j ];
		//设置车
		cells[iact_cell]->set_a_car(true); 
		cells[iact_cell]->set_carid(j);
		cells[iact_cell]->set_carname(0,this->getlaneid());
		//设置车辆类型统一为普通车 
		cells[iact_cell]->set_carkind(1);

	}
	
	for(int q = 0; q <= icount; q++){
		iact_cell = itemparray[ q ];
		//设置速度
		int gap = getgap(iact_cell) > MAX_V ? MAX_V : getgap(iact_cell);
		gap = rand() % (gap + 1);
		cells[iact_cell]->set_v(gap);
		cells[iact_cell]->set_change(0);
	}
	delete[] itemparray;
	return 1;
	
}


// 仿真结束时记录速度信息
bool lane::saverecord()
{
	char name[20];
	sprintf(name,"result%d.txt",getlaneid());		

	ofstream of(name,ios::app);
	if(!of)
		return false;
	of<<endl;
	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
	const int time = ((CTestCAApp*)AfxGetApp())->GetTime();
	double sum = 0;
	int count = 0;
	for(int d = 0; d < dist; d++){
		if(cells[d]->get_a_car()){
			double mile = (double)cells[d]->GetPos() * 7.5 *3.6;
			if(cells[d]->get_carkind()!=0){
				of<<"car "<<cells[d]->get_carname()<<"'s velocity:"<<mile/time<<endl;
				sum += (mile/time);
				count += 1;
			}
			else{
				of<<"heavy car"<<cells[d]->get_carname()<<"'s velocity:"<<mile/time<<endl;
			}
		}
	}
	
	of<<"average speed:"<<sum/count<<endl;
	for(int de = 0; de < dist; de++){
		if(cells[de]->GetD()){
			of<<"detector"<<cells[de]->GetDID()<<"at position"<<de<<" get car count:"<<cells[de]->GetDInfo()<<endl;
		}
	}

	of.close();
	return true;
}
