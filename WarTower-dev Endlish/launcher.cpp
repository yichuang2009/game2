#include"launcher.h"
#include"console.h"
#include"game.h"
void Launcher::main_menu(){
	bool echo=true;
	while(1){
		if(echo){
			Console::clear();
			Console::move(0,0);
			Console::print("War Tower");
			Console::move(1,9);
			Console::print("By EnderPearl");
			Console::move(2,0);
			Console::print("1.New Game");
			Console::move(3,0);
			Console::print("2.Help");
			Console::move(4,0);
			Console::print("0.Quit");
			echo=false;
		}
		char c=getch();
		switch(c){
			case '1':{
				Game game;
				game.play();
				echo=true;
				break;
			}
			case '2':{
				help();
				echo=true;
				break;
			}
			case '0':
				return;
		}
	}
}
void Launcher::help(){

}