#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>
#include<ctime> 
#include"button.h"

//function defined
inline void village();
inline void fireroom();
inline void mmct();
inline void pth(short,short,int,char[]); 
//end


using namespace std;


char a[20][20],b[20][20];
char x;

clock_t start,sum;

Button FR,WR,MF;
Button TREE,NEST;
Button trip;

Button save=NewButton(31,1,0xf0,"保存");
Button github=NewButton(31,4,0xf,"Github");

Button trap;
Button car;
Button house; 
Button hotel;
Button VL;

//arms 
struct menu{
	int num;
	int hurt;
	int tempo;
	float miss; 
};
menu bonegun={0,3,2};//骨枪 
menu irronsword={0,6,4};//铁剑
menu steelsword={0,9,6};//钢剑
menu bayonet={0,5,8};//刺刀
menu gun={0,5,5};//枪 
menu lasergun={0,20,24};//激光步枪 
int lasso;//套索
int ball;//子弹
int energypack;//能量元件
//end

struct smell{
    short x;
    short y;
}f;
struct flag{
	int fireroom;
	int village;
	int compass;
}fl;
struct data{
	int house;
	int farmer;
	int hunter;
	int toller;
	int cooker;
	int irronrobot;
	int irronplus;
	int Srobot;
	int Mrobot;
	int Gunworker;
	int leatherwalker;
}dt;

struct resource{
	
	int steel; //钢 
	int sulfur; //硫磺 
	int coal;//煤 
	int irron;//铁 
	int trap;
	int wood;//木头 
	int meat;//肉 
	int tooth;//牙齿 
	int scale;//鳞片 
	int fur;//毛皮 
	int car;//货车
	int toll;//诱饵
	int rice;//熏肉
	int cloth;//布 
	int leather;//皮革 
}rc;
inline void armsinput(){
	freopen("data.log","r",stdin);
	scanf("%d%d%d%d%d%d%d%d",&bonegun.num,&irronsword.num,&steelsword.num,&gun.num,&lasergun.num,&ball,&energypack,&lasso);
	fclose(stdin);
}
inline void armsoutput(){
	freopen("data.log","w",stdout);
	printf("%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",bonegun.num,irronsword.num,steelsword.num,gun.num,lasergun.num,ball,energypack,lasso);
	fclose(stdout);
}
inline void dataoutput(){
	freopen("data.log","w",stdout);
	printf("%d\n%d\n%d\n%d\n",dt.farmer,dt.house,dt.hunter,dt.toller);
	fclose(stdout);
}
inline void datainput(){
	freopen("data.log","r",stdin);
	scanf("%d%d%d%d",&dt.farmer,&dt.house,&dt.hunter,&dt.toller);
	fclose(stdin);
}
inline void flagoutput(){
	freopen("flag.log","w",stdout);
	printf("%d\n%d\n%d\n",fl.compass,fl.fireroom,fl.village);
	fclose(stdout);
}
inline void flaginput(){
	freopen("flag.log","r",stdin);
	scanf("%d%d%d",&fl.compass,&fl.fireroom,&fl.village);
	fclose(stdin);
}
inline void MSGPrint(const char Message[]){
	gto(22,0);
	printf("                                               ");
	gto(22,0);
	printf("%s",Message);
}
inline void resourceinput(){
	freopen("resource.log","r",stdin);
	scanf("%d%d%d%d%d%d%d%d%d%d",&rc.wood,&rc.meat,&rc.tooth,&rc.scale,&rc.fur,&rc.car,&rc.toll,&rc.rice,&rc.cloth,&rc.trap);
	fclose(stdin);
} 
inline void resourceoutput(){
	freopen("resource.log","w",stdout); 
	printf("%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",rc.wood,rc.meat,rc.tooth,rc.scale,rc.fur,rc.car,rc.toll,rc.rice,rc.cloth,rc.trap);
	fclose(stdout);
}
inline void save_a(){
	MessageBox(0,"已保存","消息",MB_OK);
	flagoutput();
	resourceoutput();
	dataoutput();
	armsoutput();
}
inline void village(){ 
	system("cls");
	system("title 静谧森林");
	FR = NewButton(1,1,0xf,"生火间");
	//trip = NewButton(1,19,0xf,"侦察四周"); 
	Preserve(FR);
	Preserve(trip);
	Preserve(github);
	Preserve(save);
	if(!dt.house){
		system("title 静谧森林");
		gto(22,0);
		printf("                                                   ");
		gto(22,0);
		printf("这是个晴朗的夜晚，风无情地刮着。");
		VL = NewButton(1,10,0xf,"静谧森林");
	}
	if(dt.house==1)
		system("title 孤独小屋"),VL = NewButton(1,10,0xf,"孤独小屋");
	if(dt.house>1)
		system("title 小型村落"),VL = NewButton(1,10,0xf,"小型村落");
	if(dt.house>10)
		system("title 中型村落"),VL = NewButton(1,10,0xf,"中型村落");
	if(dt.house>30)
		system("title 大型村落"),VL = NewButton(1,10,0xf,"大型村落");
	if(dt.house>60)
		system("title 喧嚣小镇"),VL = NewButton(1,10,0xf,"喧嚣小镇");
	
	gto(20,0);
	printf("消息\n----------------------");
	gto(24,0);
	printf("物品\n----------------------");
	gto(29,0);
	printf("选项\n----------------------");
	MF = NewButton(3,1,0xf,"伐木");
//	NEST = NewButton(3,1,0xf,"查看陷阱"); 
	Preserve(VL);
	while(1){
		pth(26,0,rc.wood,"木头");pth(26,10,rc.cloth,"布料");pth(26,20,rc.fur,"毛皮");pth(26,30,rc.tooth,"牙齿");
		sum=clock();
		if((sum-start)%50==0){
			rc.wood+=dt.farmer*2;
			rc.fur+=dt.hunter*5;
			rc.meat+=dt.hunter*5;
			if(rc.meat-dt.toller*10>=0){
				rc.meat-=dt.toller*10;
				rc.toll+=dt.toller;
			}
			if(rc.meat-dt.cooker>=0 && rc.wood-dt.cooker*5>=0){
				rc.meat-=dt.cooker;
				rc.wood-=dt.cooker*10;
				rc.rice+=dt.cooker;
			}
			if(rc.rice-dt.irronrobot*5>=0){
				rc.rice-=dt.irronrobot*5;
				rc.irron+=dt.irronrobot;
			}
			if(rc.fur-dt.leatherwalker*5>=0){
				rc.fur-=dt.leatherwalker*5;
				rc.leather+=dt.leatherwalker;
			}
		} 
		if(rand()%10 == 4 && dt.farmer+dt.hunter+dt.toller<dt.house*4){
			if(dt.house*4-(dt.farmer+dt.hunter+dt.toller)==1) MSGPrint("陌生人在夜里抵达"),dt.farmer++;
			else if(dt.house*4-(dt.farmer+dt.hunter+dt.toller)<5) MSGPrint("一户饱经风霜的人家住进了一间小屋"),dt.farmer+=4;
			else if(dt.house*4-(dt.farmer+dt.hunter+dt.toller)<12) MSGPrint("一群瘦骨嶙峋的人抵达了"),dt.farmer+=10;
			else MSGPrint("车队来了，带着愁苦，同时也带着希望"),dt.farmer+=12;
		}
		if(Preserve(trip)) mmct(),village(); 
		if(Preserve(FR)) fireroom();
		if(Preserve(MF)){
			rc.wood+=(1+rc.car)*5;
			gto(22,0);
			printf("                                                   ");
			gto(22,0);
			printf("林地上散落着枯枝败叶"); 
			Sleep(100);
		}
		if(Preserve(github)) system("start github.html");
		if(Preserve(save)) {
			save_a();
		}
	}
}
inline void yd(){
    x=_getch();
    switch(x)
    {
        case 'w':
            if(f.x>0)
                f.x--;
            break;
        case 'a':
            if(f.y>0)
                f.y--;
            break;
        case 's':
            if(f.x<8)
                f.x++;
            break;
        case 'd':
            if(f.y<8)
                f.y++;
            break;
    }    
}
inline void mmct(){
	MessageBox(0,"这个模式可以让你探寻村庄附近，在此过程中你可以扩大你的已知范围，同时，你不会死亡。\n不过，你也同样不能遭遇任何怪物、进行特定地点的某些事件。\n那么，勇士，出发吧！使用w,a,s,d来控制你的移动。","侦察四周",MB_OK); 
	system("cls");
	system("title 荒芜世界"); 
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD defaul = 0xf6;
	WORD build  = 0xf0;
	WORD build_empty  = 0xf8;
	WORD grass  = 0xfa;
	WORD desert = 0xf6;
	WORD forest = 0xfb;
	WORD walker = 0xf1;
    f.x=4;
    f.y=4;
    bool flag=false;
    while(1)
    {
        b[f.x+1][f.y]=1;
        b[f.x-1][f.y]=1;
        b[f.x][f.y+1]=1;
        b[f.x][f.y-1]=1;
        system("cls");
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                if(i==f.x && j==f.y){
                	SetConsoleTextAttribute(hOut, walker);
                	putchar('@');
				}
                else if(b[i][j]==1){
                	if(a[i][j]!='.' && a[i][j]!=';' && a[i][j]!=',') SetConsoleTextAttribute(hOut, build);
                	else if(a[i][j]==',') SetConsoleTextAttribute(hOut, grass);
                	else if(a[i][j]==';') SetConsoleTextAttribute(hOut, forest);
                	else if(a[i][j]=='.') SetConsoleTextAttribute(hOut, desert);
					else SetConsoleTextAttribute(hOut, defaul);
                	putchar(a[i][j]);
				}
                else putchar(' ');
                putchar(' ');
            }
            putchar('\n');
        }
        yd();
        b[f.x++][f.y]=1;
        b[f.x--][f.y]=1;
        b[f.x][f.y++]=1;
        b[f.x][f.y--]=1;
        flag=true;
        if(a[f.x][f.y]=='A' && flag==true)
        {
            system("cls");
            for(int i=0;i<9;i++)
            {
                for(int j=0;j<9;j++)
                {
                    if(i==f.x && j==f.y) putchar('@');
                    else if(b[i][j]==1) putchar(a[i][j]);
                    else putchar(' ');
                    putchar(' ');
                }
                putchar('\n');
            }
            return;
        }
    }
}
inline void pth(short x,short y,int th,char thname[]){
	gto(x,y);
	color(0x70);
	if(th){
		printf("         ");
		gto(x,y);
		printf("%s%d",thname,th);
	}
	color(0xf0);
}
inline void pthnum(short x,short y,int th,char thname[]){
	gto(x,y);
	color(0xf0);
	if(th){
		printf("  ");
		gto(x,y);
		printf("%s%d",thname,th);
	}
	color(0xf0);
}
inline void fireroom(){
	
	start=clock();
	srand((unsigned)time(0));
	
	color(0xf0); 
	system("cls");
	gto(20,0);
	printf("消息\n----------------------");
	gto(24,0);
	printf("物品\n----------------------");
	gto(29,0);
	printf("选项\n----------------------"); 
	
	pth(26,0,rc.wood,"木头");pth(26,10,rc.cloth,"布料");pth(26,20,rc.fur,"毛皮");pth(26,30,rc.tooth,"牙齿"); 
	MF = NewButton(3,1,0xf,"   生火   ");
	if(!fl.fireroom){
		system("title 小黑屋") ;
		FR = NewButton(1,1,0xf,"小黑屋");
		Preserve(FR);
		rc.wood = 7;
		gto(22,0);
		printf("火堆熄灭了，小黑屋寒冷刺骨\n");
	}
	else{
		system("title 生火间");
		FR = NewButton(1,1,0xf,"生火间");
		MF = NewButton(3,1,0xf," 不可添柴 "); 
		Preserve(VL); 
		Preserve(FR);
		Preserve(trap);
		Preserve(car);
		Preserve(house);
		Preserve(hotel);
		Preserve(trip); 
		if(rc.car) car = NewButton(5,1,0xf,"已拥有货车");  
	}
	while(1){
		sum=clock();
		if((sum-start)%100==0){
			rc.wood+=dt.farmer*2;
			rc.fur+=dt.hunter*5;
			rc.meat+=dt.hunter*5;
			if(rc.meat-dt.toller*10>=0){
				rc.meat-=dt.toller*10;
				rc.toll+=dt.toller;
			}
			if(rc.meat-dt.cooker>=0 && rc.wood-dt.cooker*5>=0){
				rc.meat-=dt.cooker;
				rc.wood-=dt.cooker*10;
				rc.rice+=dt.cooker;
			}
			if(rc.rice-dt.irronrobot*5>=0){
				rc.rice-=dt.irronrobot*5;
				rc.irron+=dt.irronrobot;
			}
			if(rc.fur-dt.leatherwalker*5>=0){
				rc.fur-=dt.leatherwalker*5;
				rc.leather+=dt.leatherwalker;
			}
		}
		if(rand()%10 == 4 && dt.farmer+dt.hunter+dt.toller<dt.house*4){
			if(dt.house*4-(dt.farmer+dt.hunter+dt.toller)==1) MSGPrint("陌生人在夜里抵达"),dt.farmer++;
			else if(dt.house*4-(dt.farmer+dt.hunter+dt.toller)<5) MSGPrint("一户饱经风霜的人家住进了一间小屋"),dt.farmer+=4;
			else if(dt.house*4-(dt.farmer+dt.hunter+dt.toller)<12) MSGPrint("一群瘦骨嶙峋的人抵达了"),dt.farmer+=10;
			else MSGPrint("车队来了，带着愁苦，同时也带着希望"),dt.farmer+=12;
		}
		if(rand()%50 == 4 && rc.wood>=9900){
			MessageBox(0,"一场大火席卷了仓库，剩余的木头寥寥无几","消息",MB_OK);
			MSGPrint("一些木头被烧毁了"); 
			rc.wood-=9000;
		}
		gto(26,0);
		pth(26,0,rc.wood,"木头");pth(26,10,rc.cloth,"布料");pth(26,20,rc.fur,"毛皮");pth(26,30,rc.tooth,"牙齿");
		pthnum(4,6,rc.trap," ");
		pthnum(6,6,dt.house," "); 
        if(Preserve(save)) save_a();
		else if(Preserve(github)) system("start github.html");
		else if(Preserve(trip)) mmct(),fireroom();
		else if(Preserve(MF) && !fl.fireroom){
            gto(22,0);
            printf("                                                   ");
			gto(22,0); 
            printf("屋子很冷,火堆燃烧\n"); 
            MF = NewButton(3,1,0xf,"   添柴   ");//之后再加一个计时器 
            FR = NewButton(1,1,0xf,"生火间");
            Preserve(FR);
            system("title 生火间");
            rc.wood-=1;
            fl.fireroom = 5;
            Sleep(100);
    	}
        else if(Preserve(MF) && fl.fireroom){
        	if(fl.fireroom-1!=0 && rc.wood-1>=0){
        		fl.fireroom -=1;
        		gto(22,0);
        		printf("                                               ");
        		gto(22,0);
        		printf("屋子暖和,火堆燃烧\n");
        		rc.wood -=1;
        		Sleep(100);
			}
			/*
			else if(fl.fireroom-1==1){
        		fl.fireroom -=1;
        		gto(22,0);
        		printf("                                               ");
        		gto(22,0);
        		printf("屋子暖和,火堆燃烧\n");
        		rc.wood -=1;
        		Sleep(100);
        		trap=NewButton(4,1,0xf,"   陷阱   ");
				car=NewButton(5,1,0xf,"   货车   ");
				house=NewButton(6,1,0xf,"   小屋   "); 
				hotel=NewButton(7,1,0xf," 狩猎小屋 ");	
			}
			*/
			else{
				gto(22,0);
				printf("                                               ");
				gto(22,0); 
				printf("火堆已经燃起。木柴不够了。\n");
				fl.fireroom=1;
				fl.village=1;
				MF = NewButton(3,1,8," 不可添柴 ");
				VL = NewButton(1,10,0xf,"静谧森林");
				MessageBox(0,"一个陌生人走进小屋，哆嗦着蜷缩在角落里","消息",MB_OK);
				MessageBox(0,"陌生人的呼吸平静了下来，她说她会制造很多东西","消息",MB_OK); 
				if(!rc.car)car=NewButton(5,1,0xf,"   货车   ");
				house=NewButton(6,1,0xf,"   小屋   "); 		
				hotel=NewButton(7,1,0xf," 狩猎小屋 ");
				trap=NewButton(4,1,0xf,"   陷阱   ");
				trip = NewButton(1,19,0xf,"侦察四周");
				Preserve(trap);
				Preserve(car);
				Preserve(house);
				Preserve(hotel);
			}	 
		}
		else if(Preserve(VL) && fl.fireroom)village();
		else if(Preserve(car) && !rc.car){
			if(rc.wood - 30>=0){
			rc.wood-=30;
			rc.car=1;
			car = NewButton(5,1,0xf,"已拥有货车"); 
			MSGPrint("摇摇晃晃的货车满载着从森林运出的木头"); 
			}
			else MSGPrint("木头不够了");
		}
		else if(Preserve(trap)){
			if(rc.wood-10*(rc.trap+1)>=0 && rc.trap<20){
				rc.wood -= 10*(rc.trap+1);
				rc.trap+=1;
				MSGPrint("陷阱越多，抓获的猎物越多"); 
			}
			else if(rc.trap<20) MSGPrint("木头不够了");
			else MSGPrint("再增加陷阱已经毫无裨益");
		}
		else if(Preserve(house)){
			if(rc.wood-100*(dt.house+1)>=0 && dt.house<80){
				rc.wood -= 100*(dt.house+1);
				dt.house+=1;
				MSGPrint("建造者筑起了一间小屋，她说消息很快会传出去"); 
			}
			else if(dt.house<80) MSGPrint("木头不够了");
			else MSGPrint("再也没有建造小屋的空地了");	
		}
	}
} 
int main(){
	system("mode 80,45"); 
	//system("color 8f"); //如果要换颜色就把这行解除备注，备注下一行 
    system("color f0");
    
	freopen("sperr.txt","r",stdin);
    for(int i=0;i<9;i++){
    	for(int j=0;j<9;j++)
        {
		    a[i][j]=getchar();
        }
        getchar();
	}
    for(int i=0;i<9;i++){
    	for(int j=0;j<9;j++)
        {
            a[i][j]=getchar();
        }
        getchar();
	}
    fclose(stdin);
    resourceinput();
    flaginput();
    datainput();
    armsinput();
    if(fl.fireroom == 1){
		car=NewButton(5,1,0xf,"   货车   ");
		house=NewButton(6,1,0xf,"   小屋   "); 		
		hotel=NewButton(7,1,0xf," 狩猎小屋 ");
		trap=NewButton(4,1,0xf,"   陷阱   ");		    	
		VL = NewButton(1,10,0xf,"静谧森林");
		trip = NewButton(1,19,0xf,"侦察四周");
	} 
	MessageBox(0,"Welcome to a dark room v0.1.1!","Stdin Cache complete!",MB_OK);
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);
    CursorInfo.bVisible = false; 
    SetConsoleCursorInfo(handle, &CursorInfo);
    system("cls"); 
    fireroom();
    system("pause");
    return 0; 
}

