// changeable_lane.cpp: implementation of the changeable_lane class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "changeable_lane.h"
//defined by liyan
class CTestCAApp;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


changeable_lane::changeable_lane(int laneid) : lane(laneid){
	
}

changeable_lane::~changeable_lane()
{
	
}

void changeable_lane::set_change_velocity(int index,lane* p_lane_other)
{	
	const int MAX_V = ((CTestCAApp*)AfxGetApp())->GetMAX_V();
	assert( ! p_lane_other->cells[ index ]->get_a_car() );
	int v_self = this->cells[ index ]->get_v();
	int gap_other_front = p_lane_other->getgap( index );
	if(gap_other_front <= v_self){
		this->cells[ index ]->set_v( gap_other_front );
	}
	else{
		//���ٳ���
		v_self++;
		this->cells[ index ]->set_v( (v_self < MAX_V ? v_self : MAX_V) );
	}

}


int changeable_lane::GetLaneChangeSignal(const int cell_index, int& v_changed )
{
	assert(cell_index >= 0);
	
	const int MAX_V = ((CTestCAApp*)AfxGetApp())->GetMAX_V();
	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
    changeable_lane* p_lane_other = Get_Other_Lane();

	//��һ�׶Σ�����������
	//�����һ�������г������̷���
	if( p_lane_other->cells[cell_index]->get_a_car() )
		return 0;
    //9.21�޸ģ�ǰ��������뿼�ǻ��복����ǰ����������
    //int gap_other_front = p_lane_other->getgap(cell_index);


    //Ϊ�˱�֤��������ͬһ����������һ������ǰ����������ײ��
    //���Ӵ˲���
    vector<changeable_cell*> tempv;
	GetCells(cell_index, 1, tempv);
   

    int gap_other_front = p_lane_other->getgap(cell_index);
    if( gap_other_front == 0 )
        return 0;

	//�Ȳ�����û���Լ������������������
    for(int ifindv = 0; ifindv < MAX_V; ifindv++){
        if( tempv[ifindv]->ipretag >= 0 ){
			//�����ǰ�ڻ��복������ȷ��������������ǰ����ײ
            gap_other_front = ifindv;
            break;
        }
        gap_other_front = MAX_V;
    }
	//�Ƚ�ǰ�ڻ��복������ͬǰ������
	//������ߴ���ǰ�ߣ���Ӧ�Ժ���Ϊ׼
	if( p_lane_other->getgap(cell_index) < gap_other_front )
		gap_other_front = p_lane_other->getgap(cell_index);
    if( gap_other_front == 0 )
        return 0;
	
	//��ñ�����ǰ������
	int gap_self_front = this->getgap(cell_index);   
	assert(gap_self_front >= 0);
	
    //���gap_self_front<gap_other_front,ֱ���Ƴ�
	if( gap_other_front <= gap_self_front)
		return 0;
	//��һ��������ȱ�����ǰ���ո�࣬���һ������
    else{/*( gap_other_front > gap_self_front )*/
		//����gap_other_back��v_other_back
		int gap_other_back, v_other_back;

        //��ȡ�Լ��ĳ���
        int v_self = this->cells[cell_index]->get_v();
		assert(v_self >= 0);
        //���׼�����������Ͷ���û���֮����ٶ�������Χ
        if( v_self >= gap_other_front ){
            if(this->is_accelerate()){
                v_self = gap_other_front;
            }
            else{
                //���gap_other_front = 1,��ôv_self = 0,��ôҲ�Ǻ����
                //���gap_other_front = 0,��ô�������ܳ������д˴������,
                //��Ϊǰ����ж�gap_other_front > gap_self_front�����ٳ���
                v_self = gap_other_front - 1;
            }
        }
        else{
            //vs_self<gap_other_front
            if(is_accelerate()){
                v_self += 1;
            }
            else{
                //v_self = v_self;
            }
        }//�����ٶȽ���
        //���v_self == 0�����ٶ��ж�Ϊ�㣬��Ӧ�ò�����������0
        if(v_self == 0)
            return 0;
#ifdef _DEBUG
		//����ȡ�õ�gap_other_front
		this->cells[cell_index]->iothergap = gap_other_front;
#endif

        //���޶����ٶȸ���v_changed
        assert( v_self >=0 && v_self <=MAX_V );
        v_changed = v_self;
		//�ڶ��׶�:����������
        //��Ȼ�ٶ�������Ҫ�󣬵��ǻ�Ҫ���󳵵��ٶȺͼ���Ƿ�����Ҫ�� 

        //��ʼ�Һ�
		//����Ҫ�ҵ��ٽ��������ĵ�һ����

		//Ѱ����һ����index����Ŀ���index�ĵ�һ����
		assert( !p_lane_other->cells[cell_index]->get_a_car());
		if(cell_index < MAX_V){
			vector<const changeable_cell*> tempvec;
			tempvec.reserve(MAX_V);

			for(int i = dist - 1 - (MAX_V - 1 - cell_index); i < dist; i++){
				tempvec.push_back(p_lane_other->cells[i]);
			}
			for(int j = 0; j < cell_index; j++){
				tempvec.push_back(p_lane_other->cells[j]);
			}
			bool back_car = false;
			int t = MAX_V - 1;
			while(!back_car && t >= 0){
				back_car = tempvec[t]->get_a_car();
				if(back_car){
					v_other_back = tempvec[t]->get_v();
                    //�޸Ĳ����߼��Ļ���������9.21
                    //gap_other_back = MAX_V - t ;
                    //assert(gap_other_back > 0 && gap_other_back <= MAX_V);
					gap_other_back = MAX_V - t -1;
                    assert(gap_other_back >= 0 && gap_other_back <= MAX_V);
					break;
				}
				t--;
			}
            if(!back_car)
                return p_taget_lane->getlaneid();	
            
		}
		else{
			int index = cell_index;
	    	int k = 0;
			bool back_car = false;
			while(!back_car && k < MAX_V){
				index--;
				back_car = p_lane_other->cells[index]->get_a_car();
				if(back_car){
					v_other_back = p_lane_other->cells[index]->get_v();
                    //�޸Ĳ����߼��Ļ�����ģ��9.21
					//gap_other_back = cell_index - index;
                    gap_other_back = cell_index - index - 1;
                     //�޸Ĳ����߼��Ļ�����ģ�͵��ж�����9.21
                    //assert(gap_other_back > 0 && gap_other_back <= MAX_V);
                    assert(gap_other_back >= 0 && gap_other_back <= MAX_V);
					break;
				}
				k++;
			}
            if(!back_car)
                return p_taget_lane->getlaneid();	
		}
		assert(v_other_back >= 0);
        //�󳵲�����ȡ����

        //��ʼ�ж�
		int laneid = p_taget_lane->getlaneid();	
        int returnvar;
        //��Ϊ����������޸�ģ��
        //gap_other_back�ķ�ΧΪ0-4�������5��ֱ���ж����㻻������
        if( gap_other_back >= v_other_back ){
            returnvar = laneid;
        }
        else{
            returnvar = 0;
        }
        return returnvar;
		////	��Ϊĳ������ģ��,�����Ϲ��飬�����ڲ����߼��İ�ȫ����	
		//if( gap_other_back + v_self > v_other_back + 1 )
		//	returnvar = laneid;
		//else
		//	returnvar = 0;
		//return returnvar;
		//��Ϊ��׼STCAģ��
	//	return (gap_other_back+1) >= v_other_back ? laneid : 0; 
	}

}




void changeable_lane::Set_Other_Lane(changeable_lane* p_other_lane){
	p_taget_lane = p_other_lane;
}
changeable_lane* changeable_lane::Get_Other_Lane() const{
	return p_taget_lane;
}


void changeable_lane::RefreshV(int t)
{
	const int MAX_V = ((CTestCAApp*)AfxGetApp())->GetMAX_V();
	const int MAX_HV = ((CTestCAApp*)AfxGetApp())->GetMax_HV();
	const int mtime = ((CTestCAApp*)AfxGetApp())->GetTime();
	//��ȡָ��Ŀ�공����ָ�룬������ָ�����p_other_lane����
	changeable_lane *p_other_lane = this->Get_Other_Lane();
	//����ʱ���ۼ�����icount,�Ի��ּ�¼����
	icount = t;

	//��ʼ����
	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
	for( int d = dist - 1; d >= 0 ; d-- ){
	    //��������,�������������²�����
		//�����ٶ�,�������ж��Ƿ񻻳���
		if( cells[d]->get_a_car() ){
			//��ȡ��϶
 			int gap = getgap( d );
#if defined _DEBUG
            cells[d]->itestgap = gap;
#endif 
            cells[d]->set_timetag(t);
			//��ȡ�ٶ���Ϣ
			int v = cells[d]->get_v();
			//��ȡ������Ϣ 
			int kind = cells[d]->get_carkind();
			//��������ͳ�
			if(kind == 0){
				if( v > gap ){
					//���ͳ�������
					cells[d]->set_v(gap);
				}
				else if( v < gap && v < MAX_HV ){
					cells[d]->set_v(v+1);
				}
				else{
				//v=gap����v=MAX_HV��������ԭ���ٶȲ���
				}
				cells[d]->set_change(0);
			}
			//С�ͳ��ٶ��ж���ʼ
			else if(kind == 1){
				assert(v <= MAX_V && v >= 0);
				//�ж��ٶ�״̬������ٶ�С��gap��Ӧת�뻻����״̬
				if( v > gap ){
					int v_changed = 0;
					int signal = GetLaneChangeSignal( d, v_changed );
					if( signal ){
						assert( v_changed > 0 );
						cells[d]->set_change( signal );
						//9.20�޸�
						cells[d]->set_v(v_changed);

						vector<changeable_cell*> tempcells;

						GetCells( d, signal, tempcells);
						//����ʱ������һ������ı�ǣ���ֹ���滻�������뱾����������ײ
						tempcells[v_changed-1]->ipretag = v_changed;
			
					}
					//�����ĳ��������㻻�������������Ͳ�����������ԭ��������
					else{
						if(this->is_accelerate() || gap==0){
							cells[d]->set_v(gap);
						}
						else {/*������*/
							cells[d]->set_v(gap-1);
						}
						cells[d]->set_change( 0 );
					}							
				}
		
				else if( v < MAX_V ){
					//v < Max_v && v<=gap
					if( this->is_accelerate() ){
						if( v < gap)
							cells[d]->set_v(v+1);					
					}
						
					else{
						cells[d]->set_v(v);

					}
					cells[d]->set_change( 0 );
				}
					// v=MAX_V
				else{
					if(this->is_accelerate()){
						cells[d]->set_v(v);		
					}
					else{
						//����
						cells[d]->set_v(v-1);		
					}
					cells[d]->set_change( 0 );
				}
				//��ʱ�հ�ͼ
				int hlimit = mtime > dist ? mtime - dist : 0; 
				if( d + v < dist && t >= hlimit ){
					POINT pt1,pt2;
					pt1.x = d;
					pt1.y = t - hlimit;
					pt2.x = d + v;
					pt2.y = t - hlimit + 1;
					pbmp->DrawBmpLine(pt1,pt2,v);
				}
	    		assert(cells[d]->get_v() <= 5 && cells[d]->get_v() >= 0);

			}//С�ͳ��ٶ��ж�����		
		}//d һ��Ԫ�����ٶȱ�ȷ��


		//�������й켣������
		saveBuf( d );
	}//�ٶȵ���ѭ������	
    	//�����㻺��������������£�����켣
	if( (t+1) % 5 == 0 ){
		char pname[50];
		int i = this->getlaneid();
		sprintf(pname,"result%d.txt",i);		
		savetrace( buf, pname );
	}	
    //������
    for(int te = 0; te < dist; te++){
        if(cells[te]->get_a_car() && cells[te]->get_timetag() != t)
            assert(false);
    }
	
}

void changeable_lane::RefreshV_STCA(int t)
{
	const int MAX_V = ((CTestCAApp*)AfxGetApp())->GetMAX_V();
	const int MAX_HV = ((CTestCAApp*)AfxGetApp())->GetMax_HV();
	const int mtime = ((CTestCAApp*)AfxGetApp())->GetTime();
	//��ȡָ��Ŀ�공����ָ�룬������ָ�����p_other_lane����
	changeable_lane *p_other_lane = this->Get_Other_Lane();
	//����ʱ���ۼ�����icount,�Ի��ּ�¼����
	icount = t;	

	//��ʼ����
	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
	for( int d = dist - 1; d >= 0 ; d-- ){

		//�����ٶ�,�������ж��Ƿ񻻳���
		if( cells[d]->get_a_car() ){
		//��ȡ��϶
 		int gap = getgap( d );
		//��ȡ�ٶ���Ϣ
		int v = cells[d]->get_v();
		//��ȡ������Ϣ 
		int kind = cells[d]->get_carkind();

		//��������ͳ�
		if(kind == 0){
			if( v > gap ){
				//���ͳ�������
				cells[d]->set_v(gap);
			}
			else if( v < gap && v < MAX_HV ){
				cells[d]->set_v(v+1);
			}
			else{
			//v=gap����v=MAX_HV��������ԭ���ٶȲ���
			}
			cells[d]->set_change(0);
		}
		//С�ͳ��ٶ��ж���ʼ
		else if(kind == 1){
			assert(v <= MAX_V && v >= 0);
			//�ж��ٶ�״̬������ٶ�С��gap��Ӧת�뻻����״̬
			if( v > gap ){
				int v_changed = 0;
				int signal = GetLaneChangeSignal( d, v_changed );
				if( signal ){
					assert( v_changed > 0 );
					cells[d]->set_change( signal );
					//9.20�޸�
					cells[d]->set_v(v_changed);

					//vector<changeable_cell*> tempcells;
					//GetCells( d, signal, tempcells);
					//����ʱ������һ������ı�ǣ���ֹ���滻�������뱾����������ײ
					//tempcells[v_changed-1]->ipretag = v_changed;
		
				}
				//�����ĳ��������㻻�������������Ͳ�����������ԭ��������
				else{
					if(this->is_accelerate() || gap==0){
						cells[d]->set_v(gap);
					}
					else {/*������*/
						cells[d]->set_v(gap-1);
					}
					cells[d]->set_change( 0 );
				}							
			}
	
			else if( v < MAX_V ){
				//v < Max_v && v<=gap
				if( this->is_accelerate() ){
					if( v < gap)
						cells[d]->set_v(v+1);					
				}
					
				else{
					cells[d]->set_v(v);

				}
				cells[d]->set_change( 0 );
			}
				// v=MAX_V
			else{
				if(this->is_accelerate()){
					cells[d]->set_v(v);		
				}
				else{
					//����
					cells[d]->set_v(v-1);		
				}
				cells[d]->set_change( 0 );
			}
			//��ʱ�հ�ͼ
			int hlimit = mtime > dist ? mtime - dist : 0; 
			if( d + v < dist && t >= hlimit ){
				POINT pt1,pt2;
				pt1.x = d;
				pt1.y = t - hlimit;
				pt2.x = d + v;
				pt2.y = t - hlimit + 1;
				pbmp->DrawBmpLine(pt1,pt2,v);
			}
    		assert(cells[d]->get_v() <= 5 && cells[d]->get_v() >= 0);

		}//С�ͳ��ٶ��ж�����		
	}//d һ��Ԫ�����ٶȱ�ȷ��


	//�������й켣������
	saveBuf( d );
}//�ٶȵ���ѭ������	
	//�����㻺��������������£�����켣
if( (t+1) % 5 == 0 ){
	char pname[50];
	int i = this->getlaneid();
	sprintf(pname,"result%d.txt",i);		
	savetrace( buf, pname );
}	
//������
for(int te = 0; te < dist; te++){
    if(cells[te]->get_a_car() && cells[te]->get_timetag() != t)
        assert(false);
}


}

void changeable_lane::RefreshX(int t)
{
	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
	const int MAX_V = ((CTestCAApp*)AfxGetApp())->GetMAX_V();


	//��������ѭ��������ʼ
	for(int x = dist - 1; x >= 0; x--){
        //���ʱ���ǩ����һ�ε�ʱ�䣬��ó������ε����Ѿ���ɣ�
        //���ٲ���λ�Ƶ���
        if( cells[x]->get_timetag() == t + 1 ){
			continue;
		}
		if( x < dist && cells[x]->get_a_car() ){
	
			int v = cells[x]->get_v();
			assert(v >=0 && v <= MAX_V);
				
			//ԭ��λ���ϵ�Ԫ��û���� 
			cells[x]->set_a_car(false);


			//�����ܵ���ǰ����λ����
				
			int signal = cells[x]->get_change();
			//����signal,�ж����ĸ������ϸ���Ԫ��
			changeable_lane* p_other_lane  = Get_Other_Lane();
			vector<changeable_cell*>& _cells = signal ? p_other_lane->cells : cells;


			//��������λ�ã����Ҫ������������ٽ�������λ��


			//�жϸ��³����Ƿ���ǰ��ĳ����г�ͻ
#ifdef _DEBUG
            vector<changeable_cell*> tempvec;
            GetCells(x, signal, tempvec);
            for(int i = 0; i < v; i++){
                assert(!tempvec[i]->get_a_car());   
            }
#endif
			
			//�������һ�����ڷ�Χ���������һ����
			bool is_next = false;
			int v_formal = -1; 
			if( x + v > dist - 1 ){
				v_formal = v;
				v -= dist;
				is_next = true;
			}
			assert( x + v < dist && x + v >= 0 ); 
            

			bool testcar =   _cells[x+v]->get_a_car();
			assert(!testcar);

			_cells[x+v]->set_a_car(true);
			if(is_next){
				_cells[x+v]->set_v(v_formal);
				//��������λ�ƵĴ���
				_cells[x+v]->SetPos(cells[x]->GetPos() + v_formal);
			}
			else{
				_cells[x+v]->set_v(v);
				//��������λ�ƵĴ���
				_cells[x+v]->SetPos(cells[x]->GetPos() + v);
			}

			_cells[x+v]->set_carid(cells[x]->get_carid());	
			_cells[x+v]->set_carname(cells[x]->get_carname());
			//�����ӵĳ��ʹ���
			_cells[x+v]->set_carkind(cells[x]->get_carkind());

			//��������
			
            //һ���������λ�õ����󣬼���¼�������ʱ���ǩ
            _cells[x+v]->set_timetag(t + 1);           		
        }//һ�����жϽ���			
	}
    //��������ѭ������ 
	
	//�����������Ԫ��ʼ
	for(int y = 0; y < dist; y++){
		if( cells[y]->GetD() && cells[y]->get_a_car() ){
			cells[y]->SetDInfo();
		}
	}
}
void changeable_lane::RefreshX_STCA(int t){

	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
	const int MAX_V = ((CTestCAApp*)AfxGetApp())->GetMAX_V();


	//��������ѭ��������ʼ
	for(int x = dist - 1; x >= 0; x--){
        //���ʱ���ǩ����һ�ε�ʱ�䣬��ó������ε����Ѿ���ɣ�
        //���ٲ���λ�Ƶ���
  //      if( cells[x]->get_timetag() == t + 1 ){
		//	continue;
		//}
		if( x < dist && cells[x]->get_a_car() ){
	
			int v = cells[x]->get_v();
			assert(v >=0 && v <= MAX_V);
				
			//ԭ��λ���ϵ�Ԫ��û���� 
			cells[x]->set_a_car(false);


			//�����ܵ���ǰ����λ����
				
			int signal = cells[x]->get_change();
			//����signal,�ж����ĸ������ϸ���Ԫ��
			changeable_lane* p_other_lane  = Get_Other_Lane();
			vector<changeable_cell*>& _cells = signal ? p_other_lane->cells : cells;


			//��������λ�ã����Ҫ������������ٽ�������λ��


			//�жϸ��³����Ƿ���ǰ��ĳ����г�ͻ,�����¼Ϊ������

            vector<changeable_cell*> tempvec;
            GetCells(x, signal, tempvec);
            for(int i = 0; i < v; i++){
                if(tempvec[i]->get_a_car())
					((CTestCAApp*)AfxGetApp())->errorrec0++;
            }

			
			//�������һ�����ڷ�Χ���������һ����
			bool is_next = false;
			int v_formal = -1; 
			if( x + v > dist - 1 ){
				v_formal = v;
				v -= dist;
				is_next = true;
			}
			assert( x + v < dist && x + v >= 0 ); 
            

			bool testcar =   _cells[x+v]->get_a_car();
			//��¼STCAģ�͵Ĵ���
			if(testcar)
				((CTestCAApp*)AfxGetApp())->errorrec1++;

			//assert(!testcar);

			_cells[x+v]->set_a_car(true);
			if(is_next){
				_cells[x+v]->set_v(v_formal);
				//��������λ�ƵĴ���
				_cells[x+v]->SetPos(cells[x]->GetPos() + v_formal);
			}
			else{
				_cells[x+v]->set_v(v);
				//��������λ�ƵĴ���
				_cells[x+v]->SetPos(cells[x]->GetPos() + v);
			}

			_cells[x+v]->set_carid(cells[x]->get_carid());	
			_cells[x+v]->set_carname(cells[x]->get_carname());
			//�����ӵĳ��ʹ���
			_cells[x+v]->set_carkind(cells[x]->get_carkind());

			//��������
			
            //һ���������λ�õ����󣬼���¼�������ʱ���ǩ
            //_cells[x+v]->set_timetag(t + 1);           		
        }//һ�����жϽ���			
	}
    //��������ѭ������ 
	
	//�����������Ԫ��ʼ
	for(int y = 0; y < dist; y++){
		if( cells[y]->GetD() && cells[y]->get_a_car() ){
			cells[y]->SetDInfo();
		}
	}

}
//��ѭ�������л�ȡ׼ȷ��Ԫ��λ��
vector<changeable_cell*>& changeable_lane::GetCells(const int index,const int change_signal, vector<changeable_cell*>& tempvec) {
	const int MAX_V = ((CTestCAApp*)AfxGetApp())->GetMAX_V();
	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();

	tempvec.reserve(MAX_V);
	changeable_lane*  p_lane = 0;
	if(change_signal){	
		p_lane = Get_Other_Lane();	
	}
	else{
		p_lane = const_cast<changeable_lane*>(this);;
	}
	//����tempvec;
    if( index >= dist - MAX_V ){
        for( int tempi = index + 1; tempi < dist; tempi++ ){
            tempvec.push_back( p_lane->cells[tempi] );
        }
        for( int tempj = 0; tempj < MAX_V - ( dist - 1 - index ); tempj++ ){ 
            tempvec.push_back( p_lane->cells[tempj] );
        }
    }
    else{
        for( int tempk = index + 1; tempk <= index + MAX_V; tempk++ ){
            tempvec.push_back( p_lane->cells[tempk] );
        }
    }
	return tempvec;
}
