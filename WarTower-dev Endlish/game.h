#ifndef _GAME_H_
#define _GAME_H_
#include<cstring>
class Game{
	public:
		Game():x(0),y(0),m_red_money(0),m_blue_money(0),m_red_home(10),m_blue_home(10){
			memset(tower_map,0,sizeof(tower_map));
			memset(shot_map,0,sizeof(shot_map));
		}
		void play();
	private:
		struct Tower{
			enum type{
				shooter,tank,maze,home
			};
			enum side{
				red,blue
			};
			type m_type;
			side m_side;
			int m_health;
			int m_attack;
			int m_grade;
			Tower(type t,side s):m_type(t),m_side(s),m_grade(1){
				switch(t){
					case shooter:
						m_health=10;
						m_attack=1;
						break;
					case tank:
						m_health=20;
						m_attack=0;
						break;
					case maze:
						m_health=5;
						m_attack=2;
						break;
					case home:
						m_health=100;
						m_attack=0;
						m_grade=5;
				}
			}
			void upgrade(){
				m_grade++;
				switch(m_type){
					case shooter:
						m_health+=10;
						m_attack+=1;
						break;
					case tank:
						m_health+=20;
						m_attack+=0;
						break;
					case maze:
						m_health+=5;
						m_attack+=2;
						break;
					default:
						m_grade--;
				}
			}
			int price()const{
				return m_grade*(m_grade+1)*5;
			}
		};
		Tower *tower_map[10][10];
		int shot_map[10][10];
		int m_red_money,m_blue_money;
		int m_red_home,m_blue_home;
		int x,y;
};
#endif