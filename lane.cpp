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
���ܣ�����ָ������ǰ��������Զ����Ŀո���
���룺ָ������
������ո���
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
���ܣ�������һ�������£��������е����ݼ�¼��ָ���ļ���
���룺Ҫ��¼�Ļ���ͷָ�룬�Լ�Ҫ��¼���ļ���
�������¼�ɹ����
--------------------------------------------------------*/
bool lane::savetrace(char *p , const char *name){
	//icount �������Ǽ�ʱ
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
	//��¼�������� 
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
���ܣ�����lane�����Ԫ��
���룺Ԫ�����ܸ������������һ��Ϊ��ʧ��
�����������cell��vectorѹ��cell���󣬲��Զ�����г�ʼ����
--------------------------------------------------------*/
void lane::initlane(const int d)
{
	//һЩ��ʼ���Ĺ���
	for(int count = 0; count < d; count++){
		cells.push_back(new changeable_cell(false));
		//����Ԫ����cellid�����Լ���gap[count]
		cells.back()->set_cellid(count);
//		cells.back()->set_carname(0,getlaneid());
	}
	//��ʼ���棬��������0��ʼ���� 
	car_count = 0;
	isave = 0;

	//Ϊ��ʼ���������ܶ�
	int k = ((CTestCAApp*)AfxGetApp())->GetK();	
	SetLaneK(k);
}
/*-------------------------------------------------------
���ܣ�������ļ�¼ͨ���任¼�뻺��
���룺Ҫ��¼�ĵ�Ԫ�������
����������ж�Ӧ��Ϣ���뵽����
--------------------------------------------------------*/
void lane::saveBuf(int d)
{
	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
	//ֱ����ʾ�ٶȷ���
	int mapping[6] = {0,1,2,3,4,5};
	//ת��Ϊ�Ҷ�ͼ������
//	int mapping[6] = {1,2,3,4,5,6};

	if( d <= dist-1 ){
		if(cells[d]->get_a_car() && !( cells[d]->get_change() ) ){
			//ֱ�ӽ��ٶ�ת��Ϊ�ַ�
			//buf[isave] = cells[d]->get_v() + 48;

			//�жϲ���
			assert(cells[d]->get_v() <= 5 && cells[d]->get_v() >= 0);

			//���Խ���
			buf[isave] = mapping[cells[d]->get_v()] + 48 ;	
		}
		else if( cells[d]->get_a_car() && ( cells[d]) ->get_change() ){
			//����������ʾΪA��B�� 
			//	buf[isave] = cells[d]->get_v() + 65;
			//�жϲ���
			assert(cells[d]->get_v() <= 5 && cells[d]->get_v() >= 0);
			//���Խ���

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

	//����ո�matlab��ȡ��
	//	buf[++isave] = ' ';
	isave++;
}



/*-------------------------------------------------------
���ܣ�����������������Ϊ���׳�����Ӧ�г����İٷ���
���룺����
����������İٷ���
--------------------------------------------------------*/
int lane::SetLaneQ(const int q)
{
		const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
	int inum = rand() % dist;
	
	//����ɲ��������İٷ���
	drate = ((double)q / (double)3600) * 100;
	return drate;
}

int compare(const void* a, const void* b){
	return (*(int*)a - *(int*)b);	
}
/*-------------------------------------------------------
���ܣ��ó�ʼ�ܶȳ�ʼ�������ϵĳ���,��initlane��Ӧ�ô˺���
���룺ָ���ܶ�
��������óɹ����1
--------------------------------------------------------*/
int lane::SetLaneK(const int k)
{
	//���ģʽ
	const int MAX_V = ((CTestCAApp*)AfxGetApp())->GetMAX_V();
	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
	//133 = 1000/7.5,�ǻ����ÿ������Ӧ�е�ƽ��������
	int ktransform = k * (dist - MAX_V) / 133;

	//dist-MAX_V  ��λ�ö��ǿ��Էų�ʼ������

	int* itemparray = new int[dist-1];
	int icount = 0;
	itemparray[0] = rand() % dist;

	
	int itemppos = 0;

	//��֤��������ĳ���λ�õ�Ψһ��
	bool is_explicity = true;
	//ȷ���ܶȲ����������������Ԫ������
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
	//��֤����
	int iact_cell = 0;
	qsort( itemparray, icount ,sizeof(int) , compare); 
	for(int j = 0; j <= icount; j++){
		iact_cell = itemparray[ j ];
		//���ó�
		cells[iact_cell]->set_a_car(true); 
		cells[iact_cell]->set_carid(j);
		cells[iact_cell]->set_carname(0,this->getlaneid());
		//���ó�������ͳһΪ��ͨ�� 
		cells[iact_cell]->set_carkind(1);

	}
	
	for(int q = 0; q <= icount; q++){
		iact_cell = itemparray[ q ];
		//�����ٶ�
		int gap = getgap(iact_cell) > MAX_V ? MAX_V : getgap(iact_cell);
		gap = rand() % (gap + 1);
		cells[iact_cell]->set_v(gap);
		cells[iact_cell]->set_change(0);
	}
	delete[] itemparray;
	return 1;
	
}


// �������ʱ��¼�ٶ���Ϣ
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