#ifndef __BUTTON__
#define __BUTTON__

#include<cmath>
#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<windows.h>
#include<algorithm>
using namespace std;

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)

struct Button{//按钮类型
    int x,y,color;//按钮位置和颜色
    const char *name;//名字
    int len;//名字的长度
};

void GetPos(POINT &pt){//获得鼠标相对于屏幕的位置
//POINT是自带类型
    HWND hwnd=GetForegroundWindow();
    GetCursorPos(&pt);
    ScreenToClient(hwnd,&pt);
    pt.y=pt.y/16,pt.x=pt.x/16;//除以16，想不明白自己把它去掉试试
}

void color(int a){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);}
//修改颜色
//想知道每个颜色的代码就for循环1到256看看
//暂时没用
void gto(int x,int y)//将打字的光标移到x行y列
{
    COORD pos;pos.X=y*2;pos.Y=x;
    //必须反过来
    //y*2是因为汉字是2个字符
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

Button NewButton(int x,int y,int color,const char *name){
    Button t;
    t.x=x,t.y=y,t.name=name;
    t.color=color;
    t.len=strlen(name);
    return t;//新建按钮，返回它
}

bool Preserve(Button A){
    //维护一个按钮
    //如果要使这个起作用必须在循环中不断执行它
    //详见后面的示例
    gto(A.x,A.y),color(0x70),printf("%s",A.name);
    POINT pt;
    GetPos(pt);
    if(pt.y==A.x&&(pt.x>=A.y&&pt.x<=A.y+A.len/2)){
        color(0x70),gto(A.x,A.y),printf("%s",A.name);
        if(KEY_DOWN(MOUSE_MOVED)){
			color(0xf0);
			return 1;//检测到点击按钮
    	}
	}
    color(0xf0); 
    return 0;//没有检测到
}

#endif
