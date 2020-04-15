#include<ctime>
#include"console.h"
#include"launcher.h"
#include"my_rand.h"
int main(){
	MyRand::srand(time(nullptr));
	Console con;
	Console::cursor_set(false);
	Launcher::main_menu();
	Console::cursor_set(true);
	return 0;
}
//#error This file requires compiler and library support for the \
