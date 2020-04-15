#include<queue>
#include<set>
#include<thread>
#include<mutex>
#include<cctype>
#include"game.h"
#include"console.h"
#include"my_rand.h"
using namespace std;
void Game::play(){
	static Console::Color black(Console::Color::black,Console::Color::black),red(Console::Color::red,Console::Color::black),blue(Console::Color::blue,Console::Color::black),cyan(Console::Color::cyan,Console::Color::black),yellow(Console::Color::yellow,Console::Color::black),white(Console::Color::white,Console::Color::black);
	static Console::Color back_black(Console::Color::black,Console::Color::white),back_red(Console::Color::red,Console::Color::white),back_blue(Console::Color::blue,Console::Color::white),back_cyan(Console::Color::cyan,Console::Color::white),back_yellow(Console::Color::yellow,Console::Color::white);
	mutex show_lock,xy_lock;
	auto show=[this,&show_lock](int x,int y,bool back){
		if(tower_map[x][y]==nullptr){
			lock_guard<mutex> lock(show_lock);
			if(shot_map[x][y]==0){
				if(back)
					Console::set_color(back_black);
				else
					Console::set_color(black);
				Console::mvprint(x,y*5,"     "); //space*5
			}
			else{
				if(shot_map[x][y]>0){
					if(back)
						Console::set_color(back_yellow);
					else
						Console::set_color(yellow);
				}
				else{
					if(back)
						Console::set_color(back_cyan);
					else
						Console::set_color(cyan);
				}
				Console::move(x,y*5);
				con_print("%4d ",abs(shot_map[x][y]));
			}
		}
		else{
			if(tower_map[x][y]->m_side==Tower::red){
				if(back)
					Console::set_color(back_red);
				else
					Console::set_color(red);
			}
			else{
				if(back)
					Console::set_color(back_blue);
				else
					Console::set_color(blue);
			}
			Console::move(x,y*5);
			con_print("%4d ",tower_map[x][y]->m_health);
		}
	};
	auto show_money=[this,&show_lock](Tower::side s){
		int money;
		lock_guard<mutex> lock(show_lock);
		if(s==Tower::red){
			money=m_red_money;
			Console::set_color(red);
			Console::move(10,6);
			con_print("%4d",money);
		}
		else{
			money=m_blue_money;
			Console::set_color(blue);
			Console::move(10,13);
			con_print("%4d",money);
		}
	};
	auto show_home=[this,&show_lock](Tower::side s){
		int home;
		lock_guard<mutex> lock(show_lock);
		if(s==Tower::red){
			home=m_red_home;
			Console::set_color(red);
			Console::move(11,5);
			con_print("%4d",home);
		}
		else{
			home=m_blue_home;
			Console::set_color(blue);
			Console::move(11,12);
			con_print("%4d",home);
		}
	};
	bool run=true;
	auto proc=[this,&run,&show_lock,&xy_lock,show,show_home,show_money](char msg){
		switch(msg){
			case 'W':{
				lock_guard<mutex> lock(xy_lock);
				if(x>0){
					x--;
					if(y==-1)
						for(int i=0;i<10;i++){
							show(x,i,true);
							show(x+1,i,false);
						}
					else{
						show(x,y,true);
						show(x+1,y,false);
					}
				}
				break;
			}
			case 'A':{
				lock_guard<mutex> lock(xy_lock);
				if(y>0){
					y--;
					if(x==-1)
						for(int i=0;i<10;i++){
							show(i,y,true);
							show(i,y+1,false);
						}
					else{
						show(x,y,true);
						show(x,y+1,false);
					}
				}
				break;
			}
			case 'S':{
				lock_guard<mutex> lock(xy_lock);
				if(x!=-1 && x!=9){
					x++;
					if(y==-1)
						for(int i=0;i<10;i++){
							show(x,i,true);
							show(x-1,i,false);
						}
					else{
						show(x,y,true);
						show(x-1,y,false);
					}
				}
				break;
			}
			case 'D':{
				lock_guard<mutex> lock(xy_lock);
				if(y!=-1 && y!=9){
					y++;
					if(x==-1)
						for(int i=0;i<10;i++){
							show(i,y,true);
							show(i,y-1,false);
						}
					else{
						show(x,y,true);
						show(x,y-1,false);
					}
				}
				break;
			}
			case 'J':{
				lock_guard<mutex> lock(xy_lock);
				if(x==-1){
					if(y<5){
						int sum=0;
						for(int i=0;i<10;i++)
							if(tower_map[i][y]==nullptr)
								sum++;
						if(sum*10<=m_red_money){
							for(int i=0;i<10;i++)
								if(tower_map[i][y]==nullptr){
									tower_map[i][y]=new Tower(Tower::shooter,Tower::red);
									show(i,y,true);
								}
							m_red_money-=sum*10;
							show_money(Tower::red);
						}
					}
				}
				else{
					if(y==-1){
						int sum=0;
						for(int i=0;i<5;i++)
							if(tower_map[x][i]==nullptr)
								sum++;
						if(sum*10<=m_red_money){
							for(int i=0;i<5;i++)
								if(tower_map[x][i]==nullptr){
									tower_map[x][i]=new Tower(Tower::shooter,Tower::red);
									show(x,i,true);
								}
							m_red_money-=sum*10;
							show_money(Tower::red);
						}
					}
					else if(y<5 && m_red_money>=10 && tower_map[x][y]==nullptr){
						tower_map[x][y]=new Tower(Tower::shooter,Tower::red);
						show(x,y,true);
						m_red_money-=10;
						show_money(Tower::red);
					}
				}
				break;
			}
			case 'K':{
				lock_guard<mutex> lock(xy_lock);
				if(x==-1){
					if(y<5){
						int sum=0;
						for(int i=0;i<10;i++)
							if(tower_map[i][y]==nullptr)
								sum++;
						if(sum*10<=m_red_money){
							for(int i=0;i<10;i++)
								if(tower_map[i][y]==nullptr){
									tower_map[i][y]=new Tower(Tower::maze,Tower::red);
									show(i,y,true);
								}
							m_red_money-=sum*10;
							show_money(Tower::red);
						}
					}
				}
				else{
					if(y==-1){
						int sum=0;
						for(int i=0;i<5;i++)
							if(tower_map[x][i]==nullptr)
								sum++;
						if(sum*10<=m_red_money){
							for(int i=0;i<5;i++)
								if(tower_map[x][i]==nullptr){
									tower_map[x][i]=new Tower(Tower::maze,Tower::red);
									show(x,i,true);
								}
							m_red_money-=sum*10;
							show_money(Tower::red);
						}
					}
					else if(y<5 && m_red_money>=10 && tower_map[x][y]==nullptr){
						tower_map[x][y]=new Tower(Tower::maze,Tower::red);
						show(x,y,true);
						m_red_money-=10;
						show_money(Tower::red);
					}
				}
				break;
			}
			case 'L':{
				lock_guard<mutex> lock(xy_lock);
				if(x==-1){
					if(y<5){
						int sum=0;
						for(int i=0;i<10;i++)
							if(tower_map[i][y]==nullptr)
								sum++;
						if(sum*10<=m_red_money){
							for(int i=0;i<10;i++)
								if(tower_map[i][y]==nullptr){
									tower_map[i][y]=new Tower(Tower::tank,Tower::red);
									show(i,y,true);
								}
							m_red_money-=sum*10;
							show_money(Tower::red);
						}
					}
				}
				else{
					if(y==-1){
						int sum=0;
						for(int i=0;i<5;i++)
							if(tower_map[x][i]==nullptr)
								sum++;
						if(sum*10<=m_red_money){
							for(int i=0;i<5;i++)
								if(tower_map[x][i]==nullptr){
									tower_map[x][i]=new Tower(Tower::tank,Tower::red);
									show(x,i,true);
								}
							m_red_money-=sum*10;
							show_money(Tower::red);
						}
					}
					else if(y<5 && m_red_money>=10 && tower_map[x][y]==nullptr){
						tower_map[x][y]=new Tower(Tower::tank,Tower::red);
						show(x,y,true);
						m_red_money-=10;
						show_money(Tower::red);
					}
				}
				break;
			}
			case 'U':{
				lock_guard<mutex> lock(xy_lock);
				if(x==-1){
					if(y<5 && y>0){
						int sum=0;
						for(int i=0;i<10;i++)
							if(tower_map[i][y])
								sum+=(tower_map[i][y]->m_grade+1)*10;
						if(sum<=m_red_money){
							for(int i=0;i<10;i++)
								if(tower_map[i][y]){
									tower_map[i][y]->upgrade();
									show(i,y,true);
								}
							m_red_money-=sum;
							show_money(Tower::red);
						}
					}
				}
				else{
					if(y==-1){
						int sum=0;
						for(int i=0;i<5;i++)
							if(tower_map[x][i])
								sum+=(tower_map[x][i]->m_grade+1)*10;
						if(sum<=m_red_money)
							for(int i=0;i<5;i++)
								if(tower_map[x][i]){
									tower_map[x][i]->upgrade();
									show(x,i,true);
								}
						m_red_money-=sum;
						show_money(Tower::red);
					}
					else if(y<5 && y>0 && tower_map[x][y] && m_red_money>=(tower_map[x][y]->m_grade+1)*10){
						m_red_money-=(tower_map[x][y]->m_grade+1)*10;
						tower_map[x][y]->upgrade();
						show(x,y,true);
						show_money(Tower::red);
					}
				}
				break;
			}
			case 'I':{
				lock_guard<mutex> lock(xy_lock);
				if(x==-1){
					if(y<5 && y>0){
						for(int i=0;i<10;i++)
							if(tower_map[i][y]){
								m_red_money+=tower_map[i][y]->price()/2;
								show_money(Tower::red);
								delete tower_map[i][y];
								tower_map[i][y]=nullptr;
								show(i,y,true);
							}
					}
				}
				else{
					if(y==-1){
						for(int i=0;i<5;i++)
							if(tower_map[x][i]){
								m_red_money+=tower_map[x][i]->price()/2;
								show_money(Tower::red);
								delete tower_map[x][i];
								tower_map[x][i]=nullptr;
								show(x,i,true);
							}
					}
					else if(y<5 && y>0 && tower_map[x][y]){
						m_red_money+=tower_map[x][y]->price()/2;
						show_money(Tower::red);
						delete tower_map[x][y];
						tower_map[x][y]=nullptr;
						show(x,y,true);
					}
				}
				break;
			}
			case '\n':
				m_red_money++;
				m_blue_money+=2;
				show_money(Tower::red);
				show_money(Tower::blue);
				for(int i=0;i<10;i++)
					for(int j=9;j>-1;j--){
						if(shot_map[i][j]>0){
							if(j!=9)
								shot_map[i][j+1]+=shot_map[i][j];
							shot_map[i][j]=0;
							/*show(i,j,x==i && y==j || x==i && y==-1 || x==-1 && y==j);
							show(i,j+1,x==i && y==j+1 || x==i && y==-1 || x==-1 && y==j+1);*/
						}
					}
				for(int i=0;i<10;i++)
					for(int j=0;j<10;j++){
						if(shot_map[i][j]<0){
							if(j!=0)
								shot_map[i][j-1]+=shot_map[i][j];
							shot_map[i][j]=0;
							/*show(i,j,x==i && y==j || x==i && y==-1 || x==-1 && y==j);
							show(i,j-1,x==i && y==j-1 || x==i && y==-1 || x==-1 && y==j-1);*/
						}
					}
				for(int i=0;i<10;i++)
					for(int j=0;j<10;j++)
						if(tower_map[i][j]){
							if(tower_map[i][j]->m_side==Tower::red){
								shot_map[i][j+1]+=tower_map[i][j]->m_attack;
								//show(i,j+1,x==i && y==j+1 || x==i && y==-1 || x==-1 && y==j+1);
							}
							else{
								shot_map[i][j-1]-=tower_map[i][j]->m_attack;
								//show(i,j-1,x==i && y==j-1 || x==i && y==-1 || x==-1 && y==j-1);
							}
						}
				for(int i=0;i<10;i++)
					for(int j=0;j<10;j++){
						if(shot_map[i][j]>0 && tower_map[i][j] && tower_map[i][j]->m_side==Tower::blue){
							if(tower_map[i][j]->m_health>shot_map[i][j]){
								tower_map[i][j]->m_health-=shot_map[i][j];
								shot_map[i][j]=0;
							}
							else{
								shot_map[i][j]-=tower_map[i][j]->m_health;
								m_red_money+=tower_map[i][j]->price()/2;
								show_money(Tower::red);
								delete tower_map[i][j];
								tower_map[i][j]=nullptr;
								if(j==9){
									m_blue_home--;
									show_home(Tower::blue);
								}
							}
						}
						else if(shot_map[i][j]<0 && tower_map[i][j] && tower_map[i][j]->m_side==Tower::red){
							if(tower_map[i][j]->m_health>-shot_map[i][j]){
								tower_map[i][j]->m_health+=shot_map[i][j];
								shot_map[i][j]=0;
							}
							else{
								shot_map[i][j]+=tower_map[i][j]->m_health;
								m_blue_money+=tower_map[i][j]->price()/2;
								show_money(Tower::blue);
								delete tower_map[i][j];
								tower_map[i][j]=nullptr;
								if(j==0){
									m_red_home--;
									show_home(Tower::red);
								}
							}
						}
					}
				{
					lock_guard<mutex> lock(xy_lock);
					for(int i=0;i<10;i++)
						for(int j=0;j<10;j++)
							show(i,j,x==i && y==j || x==i && y==-1 || x==-1 && y==j);
				}
				if(m_red_home==0){
					lock_guard<mutex> lock(show_lock);
					Console::set_color(white);
					Console::move(12,0);
					if(m_blue_home==0)
						Console::print("Draw");
					else
						Console::print("You Lose");
					run=false;
					Console::sleep(2000);
					Console::set_color(Console::Color(Console::Color::white,Console::Color::black));
					Console::mvprint(13,0,"Press any key to continue...");
				}
				else if(m_blue_home==0){
					lock_guard<mutex> lock(show_lock);
					Console::set_color(white);
					Console::mvprint(12,0,"You Win");
					run=false;
					Console::sleep(2000);
					Console::set_color(Console::Color(Console::Color::white,Console::Color::black));
					Console::mvprint(13,0,"Press any key to continue...");
				}
				break;
			case 'G':
				m_red_home=0;
				break;
			case 'j':
				if(m_blue_money>=10){
					int a=MyRand::rand()%10,b=MyRand::rand()%4+5;
					//MessageBoxA(nullptr,("a="+to_string(a)+";b="+to_string(b)).c_str(),"rand",MB_OK);
					if(tower_map[a][b]==nullptr){
						m_blue_money-=10;
						tower_map[a][b]=new Tower(Tower::shooter,Tower::blue);
					}
				}
				break;
			case 'k':
				if(m_blue_money>=10){
					int a=MyRand::rand()%10,b=MyRand::rand()%4+5;
					//MessageBoxA(nullptr,("a="+to_string(a)+";b="+to_string(b)).c_str(),"rand",MB_OK);
					if(tower_map[a][b]==nullptr){
						m_blue_money-=10;
						tower_map[a][b]=new Tower(Tower::maze,Tower::blue);
					}
				}
				break;
			case 'l':
				if(m_blue_money>=10){
					int a=MyRand::rand()%10,b=MyRand::rand()%4+5;
					//MessageBoxA(nullptr,("a="+to_string(a)+";b="+to_string(b)).c_str(),"rand",MB_OK);
					if(tower_map[a][b]==nullptr){
						m_blue_money-=10;
						tower_map[a][b]=new Tower(Tower::tank,Tower::blue);
					}
				}
				break;
			case 'u':{
				int a=MyRand::rand()%10,b=MyRand::rand()%4+5;
				//MessageBoxA(nullptr,("a="+to_string(a)+";b="+to_string(b)).c_str(),"rand",MB_OK);
				if(tower_map[a][b] && m_blue_money>=(tower_map[a][b]->m_grade+1)*10){
					m_blue_money-=(tower_map[a][b]->m_grade+1)*10;
					tower_map[a][b]->upgrade();
				}
				break;
			}
			case 'i':{
				int a=MyRand::rand()%10,b=MyRand::rand()%4+5;
				//MessageBoxA(nullptr,("a="+to_string(a)+";b="+to_string(b)).c_str(),"rand",MB_OK);
				if(tower_map[a][b]){
					m_blue_money+=tower_map[a][b]->price()/2;
					delete tower_map[a][b];
					tower_map[a][b]=nullptr;
				}
				break;
			}
			default:{
				lock_guard<mutex> lock(xy_lock);
				if(x==-1){
					x=msg-'0';
					for(int i=0;i<10;i++)
						if(i!=x)
							show(i,y,false);
				}
				else{
					show(x,y,false);
					x=-1;
					y=msg-'0';
					for(int i=0;i<9;i++)
						show(i,y,true);
				}
			}
		}
	};
	Console::clear();
	for(int i=0;i<10;i++){
		tower_map[i][0]=new Tower(Tower::home,Tower::red);
		show(i,0,i==0);
		tower_map[i][9]=new Tower(Tower::home,Tower::blue);
		show(i,9,false);
	}
	{
		lock_guard<mutex> lock(show_lock);
		Console::set_color(white);
		Console::mvprint(10,0,"money:     vs");
		Console::mvprint(11,0,"home:     vs");
	}
	show_money(Tower::red);
	show_money(Tower::blue);
	show_home(Tower::red);
	show_home(Tower::blue);
	thread timer([&run,proc]{
		while(run){
			thread t(proc,'\n');
			t.detach();
			Console::sleep(400);
		}
	}),
	AI([this,&run,proc]{
		while(run){
			int choice=MyRand::rand()%6;
			//MessageBoxA(nullptr,("choice="+to_string(choice)).c_str(),"rand",MB_OK);
			switch(choice){
				case 0:
				{
					thread t(proc,'j');
					t.detach();
					break;
				}
				case 1:
				{
					thread t(proc,'k');
					t.detach();
					break;
				}
				case 2:
				{
					thread t(proc,'l');
					t.detach();
					break;
				}
				case 3:
				{
					thread t(proc,'u');
					t.detach();
					break;
				}
				/*case 4:{
				thread t(proc,'i');
				t.detach();
				}*/
			}
			Console::sleep(40);
		}
	});
	bool g=false;
	while(run){
		char c=toupper(getch());
		if(c=='G'){
			if(g){
				thread t(proc,'G');
				t.detach();
			}
			else
				g=true;
		}
		else
			g=false;
		if(set<char>({'W','A','S','D','J','K','L','U','I'}).count(c) || c>='0' && c<='9'){
			thread t(proc,c);
			t.detach();
		}
	}
	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++)
			delete tower_map[i][j];
	getch();
	timer.join();
	AI.join();
	Console::set_color(white);
}