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
		//加速超车
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

	//第一阶段，动机性条件
	//如果另一车道上有车，立刻返回
	if( p_lane_other->cells[cell_index]->get_a_car() )
		return 0;
    //9.21修改，前车距离必须考虑换入车道的前方其他车辆
    //int gap_other_front = p_lane_other->getgap(cell_index);


    //为了保证换车道后同一车道换至另一车道的前车不发生冲撞，
    //增加此部分
    vector<changeable_cell*> tempv;
	GetCells(cell_index, 1, tempv);
   

    int gap_other_front = p_lane_other->getgap(cell_index);
    if( gap_other_front == 0 )
        return 0;

	//先测试有没有自己车道换入的其他车辆
    for(int ifindv = 0; ifindv < MAX_V; ifindv++){
        if( tempv[ifindv]->ipretag >= 0 ){
			//如果有前期换入车辆，则确保本车辆不会与前车相撞
            gap_other_front = ifindv;
            break;
        }
        gap_other_front = MAX_V;
    }
	//比较前期换入车辆距离同前车距离
	//如果后者大于前者，则应以后者为准
	if( p_lane_other->getgap(cell_index) < gap_other_front )
		gap_other_front = p_lane_other->getgap(cell_index);
    if( gap_other_front == 0 )
        return 0;
	
	//获得本车道前车距离
	int gap_self_front = this->getgap(cell_index);   
	assert(gap_self_front >= 0);
	
    //如果gap_self_front<gap_other_front,直接推出
	if( gap_other_front <= gap_self_front)
		return 0;
	//另一车道满足比本车道前方空格多，则进一步计算
    else{/*( gap_other_front > gap_self_front )*/
		//定义gap_other_back和v_other_back
		int gap_other_back, v_other_back;

        //获取自己的车速
        int v_self = this->cells[cell_index]->get_v();
		assert(v_self >= 0);
        //如果准备换车道，就定义好换了之后的速度至合理范围
        if( v_self >= gap_other_front ){
            if(this->is_accelerate()){
                v_self = gap_other_front;
            }
            else{
                //如果gap_other_front = 1,那么v_self = 0,那么也是合理的
                //如果gap_other_front = 0,那么将不可能出现运行此处的情况,
                //因为前面的判断gap_other_front > gap_self_front将不再成立
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
        }//定义速度结束
        //如果v_self == 0，即速度判断为零，则应该不换车道返回0
        if(v_self == 0)
            return 0;
#ifdef _DEBUG
		//定义取得的gap_other_front
		this->cells[cell_index]->iothergap = gap_other_front;
#endif

        //将修订后速度赋给v_changed
        assert( v_self >=0 && v_self <=MAX_V );
        v_changed = v_self;
		//第二阶段:可能性条件
        //虽然速度满足了要求，但是还要看后车的速度和间距是否满足要求 

        //开始找后车
		//首先要找到临近车道向后的第一辆车

		//寻找另一车道index后面的靠近index的第一辆车
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
                    //修改不合逻辑的换车道条件9.21
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
                    //修改不合逻辑的换车道模型9.21
					//gap_other_back = cell_index - index;
                    gap_other_back = cell_index - index - 1;
                     //修改不合逻辑的换车道模型的判断条件9.21
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
        //后车参数获取结束

        //开始判断
		int laneid = p_taget_lane->getlaneid();	
        int returnvar;
        //此为本人提出的修改模型
        //gap_other_back的范围为0-4，如果是5则直接判定满足换道条件
        if( gap_other_back >= v_other_back ){
            returnvar = laneid;
        }
        else{
            returnvar = 0;
        }
        return returnvar;
		////	此为某论文里模型,更符合国情，但存在不合逻辑的安全隐患	
		//if( gap_other_back + v_self > v_other_back + 1 )
		//	returnvar = laneid;
		//else
		//	returnvar = 0;
		//return returnvar;
		//此为标准STCA模型
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
	//获取指向目标车道的指针，保留在指针变量p_other_lane里面
	changeable_lane *p_other_lane = this->Get_Other_Lane();
	//保存时间累计数到icount,以划分记录界限
	icount = t;

	//开始仿真
	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
	for( int d = dist - 1; d >= 0 ; d-- ){
	    //车辆发生,在周期性条件下不发生
		//迭代速度,在这里判断是否换车道
		if( cells[d]->get_a_car() ){
			//获取间隙
 			int gap = getgap( d );
#if defined _DEBUG
            cells[d]->itestgap = gap;
#endif 
            cells[d]->set_timetag(t);
			//获取速度信息
			int v = cells[d]->get_v();
			//获取车型信息 
			int kind = cells[d]->get_carkind();
			//如果是重型车
			if(kind == 0){
				if( v > gap ){
					//重型车不换道
					cells[d]->set_v(gap);
				}
				else if( v < gap && v < MAX_HV ){
					cells[d]->set_v(v+1);
				}
				else{
				//v=gap或者v=MAX_HV，即保持原来速度不变
				}
				cells[d]->set_change(0);
			}
			//小型车速度判定开始
			else if(kind == 1){
				assert(v <= MAX_V && v >= 0);
				//判断速度状态，如果速度小于gap则应转入换车道状态
				if( v > gap ){
					int v_changed = 0;
					int signal = GetLaneChangeSignal( d, v_changed );
					if( signal ){
						assert( v_changed > 0 );
						cells[d]->set_change( signal );
						//9.20修改
						cells[d]->set_v(v_changed);

						vector<changeable_cell*> tempcells;

						GetCells( d, signal, tempcells);
						//换道时需设置一个额外的标记，防止后面换道车辆与本车辆发生碰撞
						tempcells[v_changed-1]->ipretag = v_changed;
			
					}
					//如果别的车道不满足换车道的条件，就不换车道并在原车道减速
					else{
						if(this->is_accelerate() || gap==0){
							cells[d]->set_v(gap);
						}
						else {/*减速了*/
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
						//减速
						cells[d]->set_v(v-1);		
					}
					cells[d]->set_change( 0 );
				}
				//画时空斑图
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

			}//小型车速度判定结束		
		}//d 一个元胞的速度被确定


		//保存运行轨迹到数组
		saveBuf( d );
	}//速度叠代循环结束	
    	//在满足缓冲区条件的情况下，保存轨迹
	if( (t+1) % 5 == 0 ){
		char pname[50];
		int i = this->getlaneid();
		sprintf(pname,"result%d.txt",i);		
		savetrace( buf, pname );
	}	
    //检查测试
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
	//获取指向目标车道的指针，保留在指针变量p_other_lane里面
	changeable_lane *p_other_lane = this->Get_Other_Lane();
	//保存时间累计数到icount,以划分记录界限
	icount = t;	

	//开始仿真
	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
	for( int d = dist - 1; d >= 0 ; d-- ){

		//迭代速度,在这里判断是否换车道
		if( cells[d]->get_a_car() ){
		//获取间隙
 		int gap = getgap( d );
		//获取速度信息
		int v = cells[d]->get_v();
		//获取车型信息 
		int kind = cells[d]->get_carkind();

		//如果是重型车
		if(kind == 0){
			if( v > gap ){
				//重型车不换道
				cells[d]->set_v(gap);
			}
			else if( v < gap && v < MAX_HV ){
				cells[d]->set_v(v+1);
			}
			else{
			//v=gap或者v=MAX_HV，即保持原来速度不变
			}
			cells[d]->set_change(0);
		}
		//小型车速度判定开始
		else if(kind == 1){
			assert(v <= MAX_V && v >= 0);
			//判断速度状态，如果速度小于gap则应转入换车道状态
			if( v > gap ){
				int v_changed = 0;
				int signal = GetLaneChangeSignal( d, v_changed );
				if( signal ){
					assert( v_changed > 0 );
					cells[d]->set_change( signal );
					//9.20修改
					cells[d]->set_v(v_changed);

					//vector<changeable_cell*> tempcells;
					//GetCells( d, signal, tempcells);
					//换道时需设置一个额外的标记，防止后面换道车辆与本车辆发生碰撞
					//tempcells[v_changed-1]->ipretag = v_changed;
		
				}
				//如果别的车道不满足换车道的条件，就不换车道并在原车道减速
				else{
					if(this->is_accelerate() || gap==0){
						cells[d]->set_v(gap);
					}
					else {/*减速了*/
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
					//减速
					cells[d]->set_v(v-1);		
				}
				cells[d]->set_change( 0 );
			}
			//画时空斑图
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

		}//小型车速度判定结束		
	}//d 一个元胞的速度被确定


	//保存运行轨迹到数组
	saveBuf( d );
}//速度叠代循环结束	
	//在满足缓冲区条件的情况下，保存轨迹
if( (t+1) % 5 == 0 ){
	char pname[50];
	int i = this->getlaneid();
	sprintf(pname,"result%d.txt",i);		
	savetrace( buf, pname );
}	
//检查测试
for(int te = 0; te < dist; te++){
    if(cells[te]->get_a_car() && cells[te]->get_timetag() != t)
        assert(false);
}


}

void changeable_lane::RefreshX(int t)
{
	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
	const int MAX_V = ((CTestCAApp*)AfxGetApp())->GetMAX_V();


	//车辆运行循环迭代开始
	for(int x = dist - 1; x >= 0; x--){
        //如果时间标签是下一次的时间，则该车辆本次迭代已经完成，
        //不再参与位移迭代
        if( cells[x]->get_timetag() == t + 1 ){
			continue;
		}
		if( x < dist && cells[x]->get_a_car() ){
	
			int v = cells[x]->get_v();
			assert(v >=0 && v <= MAX_V);
				
			//原来位置上的元胞没有了 
			cells[x]->set_a_car(false);


			//车辆跑到了前方的位置上
				
			int signal = cells[x]->get_change();
			//根据signal,判断在哪个车道上更新元胞
			changeable_lane* p_other_lane  = Get_Other_Lane();
			vector<changeable_cell*>& _cells = signal ? p_other_lane->cells : cells;


			//车辆更新位置，如果要换车道则更新临近车道的位置


			//判断更新车辆是否与前面的车辆有冲突
#ifdef _DEBUG
            vector<changeable_cell*> tempvec;
            GetCells(x, signal, tempvec);
            for(int i = 0; i < v; i++){
                assert(!tempvec[i]->get_a_car());   
            }
#endif
			
			//如果超过一个周期范围，则进入下一周期
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
				//新增保存位移的代码
				_cells[x+v]->SetPos(cells[x]->GetPos() + v_formal);
			}
			else{
				_cells[x+v]->set_v(v);
				//新增保存位移的代码
				_cells[x+v]->SetPos(cells[x]->GetPos() + v);
			}

			_cells[x+v]->set_carid(cells[x]->get_carid());	
			_cells[x+v]->set_carname(cells[x]->get_carname());
			//新增加的车型代码
			_cells[x+v]->set_carkind(cells[x]->get_carkind());

			//新增结束
			
            //一个车辆完成位置迭代后，即记录迭代后的时间标签
            _cells[x+v]->set_timetag(t + 1);           		
        }//一辆车判断结束			
	}
    //车辆运行循环结束 
	
	//检测器计数单元开始
	for(int y = 0; y < dist; y++){
		if( cells[y]->GetD() && cells[y]->get_a_car() ){
			cells[y]->SetDInfo();
		}
	}
}
void changeable_lane::RefreshX_STCA(int t){

	const int dist = ((CTestCAApp*)AfxGetApp())->GetDist();
	const int MAX_V = ((CTestCAApp*)AfxGetApp())->GetMAX_V();


	//车辆运行循环迭代开始
	for(int x = dist - 1; x >= 0; x--){
        //如果时间标签是下一次的时间，则该车辆本次迭代已经完成，
        //不再参与位移迭代
  //      if( cells[x]->get_timetag() == t + 1 ){
		//	continue;
		//}
		if( x < dist && cells[x]->get_a_car() ){
	
			int v = cells[x]->get_v();
			assert(v >=0 && v <= MAX_V);
				
			//原来位置上的元胞没有了 
			cells[x]->set_a_car(false);


			//车辆跑到了前方的位置上
				
			int signal = cells[x]->get_change();
			//根据signal,判断在哪个车道上更新元胞
			changeable_lane* p_other_lane  = Get_Other_Lane();
			vector<changeable_cell*>& _cells = signal ? p_other_lane->cells : cells;


			//车辆更新位置，如果要换车道则更新临近车道的位置


			//判断更新车辆是否与前面的车辆有冲突,有则记录为错误数

            vector<changeable_cell*> tempvec;
            GetCells(x, signal, tempvec);
            for(int i = 0; i < v; i++){
                if(tempvec[i]->get_a_car())
					((CTestCAApp*)AfxGetApp())->errorrec0++;
            }

			
			//如果超过一个周期范围，则进入下一周期
			bool is_next = false;
			int v_formal = -1; 
			if( x + v > dist - 1 ){
				v_formal = v;
				v -= dist;
				is_next = true;
			}
			assert( x + v < dist && x + v >= 0 ); 
            

			bool testcar =   _cells[x+v]->get_a_car();
			//记录STCA模型的错误
			if(testcar)
				((CTestCAApp*)AfxGetApp())->errorrec1++;

			//assert(!testcar);

			_cells[x+v]->set_a_car(true);
			if(is_next){
				_cells[x+v]->set_v(v_formal);
				//新增保存位移的代码
				_cells[x+v]->SetPos(cells[x]->GetPos() + v_formal);
			}
			else{
				_cells[x+v]->set_v(v);
				//新增保存位移的代码
				_cells[x+v]->SetPos(cells[x]->GetPos() + v);
			}

			_cells[x+v]->set_carid(cells[x]->get_carid());	
			_cells[x+v]->set_carname(cells[x]->get_carname());
			//新增加的车型代码
			_cells[x+v]->set_carkind(cells[x]->get_carkind());

			//新增结束
			
            //一个车辆完成位置迭代后，即记录迭代后的时间标签
            //_cells[x+v]->set_timetag(t + 1);           		
        }//一辆车判断结束			
	}
    //车辆运行循环结束 
	
	//检测器计数单元开始
	for(int y = 0; y < dist; y++){
		if( cells[y]->GetD() && cells[y]->get_a_car() ){
			cells[y]->SetDInfo();
		}
	}

}
//在循环迭代中获取准确的元胞位置
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
	//储存tempvec;
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
