#include<cstdio>
#include<cstring>
#include<algorithm>
#include<conio.h>
#include<windows.h>
#include<cstdlib>
#include<ctime>
using namespace std;
#define MAXN 35
#define MIDX 10
#define MIDY 40
#define CG 25
#define CK 80
int G,K,Lnum,Wnum;//G为地图高，K为地图，Lnum为地图中的雷数，Wnum为剩余的小旗数
int nx,ny;//现在光标所在的位置
bool QR=0,Lose=0,is_flag_true[MAXN][MAXN];//QR为确认模式是否打开，Lose为是否输，第三个是这个位置上的旗是否放对
char map[MAXN][MAXN],tmap[MAXN][MAXN];//第一个是只有雷和空地的地图，第二个是玩家能看到的地图
int map1[MAXN][MAXN],mapc[MAXN][MAXN];//map1为数字的地图，其中0代表空地，-1为雷，1-8为周围雷的个数
//mapc为当前格子的颜色
int col[10]={240,249,242,252,241,244,243,240,248};//col[i]表示windows扫雷中i的颜色,col[0]为空格的颜色
int d[10][4]={{0},{0,1},{1,0},{0,-1},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};//8个方向
bool ZB;//作弊是否打开

/*各种函数*/

void color(int);//颜色
void gto(int,int);//光标位置
void make();//制作随机地图
void print();//打印地图等
bool check(int,int);//判断坐标是否合法
bool is_win();//判断是否赢
bool is_lose();//是否输
void dfs(int,int);//用深搜来打开方块
void st(int,int);//试探，即windows扫雷中的左右键同时按
void flag(int,int);//小旗
void bj(int,int);//标记
void swt();//确认模式
void again();//重新开始
void zb();//作弊模式
void mainmain();//主函数
void print_real_map();//打印最终的地图
void begin();//各种操作
int main()
{
mainmain();
}
void color(int a){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);}
void gto(int x,int y)
{
COORD pos;pos.X=y;pos.Y=x;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
void make()
{
for(int i=1;i<=G;i++)
for(int j=1;j<=K;j++)
map[i][j]='#';//初始化
for(int i=1;i<=Lnum;i++)
{
int x=rand()%G+1,y=rand()%K+1;
while(map[x][y]=='O')
x=rand()%G+1,y=rand()%K+1;
map[x][y]='O';

}//随机放雷

for(int i=1;i<=G;i++)
for(int j=1;j<=K;j++)
{
if(map[i][j]=='O')map1[i][j]=-1,mapc[i][j]=240;//如果是雷
else
{
for(int k=1;k<=8;k++)
if(map[i+d[k][0]][j+d[k][1]]=='O')
map1[i][j]++;//计算周围雷的个数
mapc[i][j]=col[map1[i][j]];//根据格子上的数设置颜色
}
}
for(int i=1;i<=G;i++)
for(int j=1;j<=K;j++)
if(mapc[i][j]==0)//空地
mapc[i][j]=240;
}
void print()
{
system("cls");
gto(0,MIDY-4); color(233); printf("扫雷");
color(240);
gto(1,MIDY);
for(int i=2;i<=G+1;i++)
{
gto(i,0);
for(int j=1;j<=K;j++)
printf("#"),tmap[i-1][j]='#';//初始化玩家所看到的地图
}
gto(2,0);
nx=2,ny=0;
color(15);
printf("@");
color(15);
gto(2,2*K+5);printf("-----规则-----");
gto(3,2*K+5);printf("wasd：选择位置");
gto(4,2*K+5);printf("空格：打开");
gto(5,2*K+5);printf("1键：试探周围8个方块，如果其中有雷则不会打开，无");
gto(6,2*K+5);printf(" 雷或旗帜标对了则会将周围无雷的位置打开，");
gto(7,2*K+5);printf(" 如果试探时周围有标错的旗帜，则会游戏失败");
gto(8,2*K+5);printf(" 必须额外确认一次，以便查看周围被试探的区域");
gto(9,2*K+5);printf("2键：放置/取消小旗（F）");
gto(10,2*K+5);printf("3键：放置/取消标记（？）");
gto(11,2*K+5);printf("4键：打开/关闭确认模式，即每次操作需再按一次确认");
gto(12,2*K+5);printf("5键：打开/关闭作弊模式，即显示原本地图");
gto(13,2*K+5);printf("0键：重新开始");//打印规则
gto(G+4,0);printf("-----操作提示-----\n");
printf("请选择方块进行操作");
gto(1,2*K+10);color(12);printf("剩余小旗数：%d",Wnum=Lnum);
}
bool check(int x,int y){return y>=0&&y<K&&x>=2&&x<G+2;}
//因为地图是从2行0列开始打的，而地图是从1行1列开始存的，所以gto(x,y)走到的是map[x-1][y+1]
bool is_win()
{
int cnt=0;
for(int i=1;i<=G;i++)
for(int j=1;j<=K;j++)
if(map[i][j]=='#'&&map1[i][j]==-1)
cnt++;
if(cnt==Lnum) return 1;
//所有没被打开的方块都是雷=>胜利
for(int i=1;i<=G;i++)
for(int j=1;j<=K;j++)
if((tmap[i][j]!='F'&&map1[i][j]==-1)||(tmap[i][j]=='F'&&map1[i][j]!=-1))
return 0;
return 1;
//所有雷都标有旗
}
bool is_lose(){return Lose;}
void dfs(int x,int y)
{
if(map1[x-1][y+1]>0)//只要边界全部是数字就return
{
gto(x,y),color(mapc[x-1][y+1]),printf("%d",map1[x-1][y+1]);
tmap[x-1][y+1]=map1[x-1][y+1]+'0';
return;
}
gto(x,y);color(255);
tmap[x-1][y+1]=' ';
printf(" ");//因为下面判断了雷，上面判断了数字，这里就一定是空地
for(int i=1;i<=8;i++)
{
int xx=x+d[i][0]-1,yy=y+d[i][1]+1;//这里的xx和yy是在map中的，而不是gto中的
if(check(xx+1,yy-1)&&tmap[xx][yy]=='#'&&map1[xx][yy]!=-1)//所以check和dfs的参数要变化
dfs(xx+1,yy-1);
}
}
void st(int x,int y)
{
for(int i=1;i<=8;i++)
{
int xx=x+d[i][0],yy=y+d[i][1];
if(check(xx,yy))
{
gto(xx,yy);
if(tmap[xx-1][yy+1]!='#')
color(mapc[xx-1][yy+1]-128);//减去128使周围的8个格子的背景颜色变为灰色
else
color(112);//这里特判一下'#'，应该可以不用
printf("%c",tmap[xx-1][yy+1]);
}
}
gto(G+5,0),color(15),printf("请确认 ");
//试探必须额外确认一次，规则上有说
char c=getch();
if(c=='1')
{
for(int i=1;i<=8;i++)
{
int xx=x+d[i][0],yy=y+d[i][1];
if(check(xx,yy))
if(tmap[xx-1][yy+1]=='F'&&map1[xx-1][yy+1]!=-1)//试探时有格子的小旗标错了=>失败
{
Lose=1;
return;
}
}
for(int i=1;i<=8;i++)
{
int xx=x+d[i][0],yy=y+d[i][1];
if(check(xx,yy))
if(map1[xx-1][yy+1]==-1&&tmap[xx-1][yy+1]!='F')//试探是有格子为雷=>取消打开
return;
}
for(int i=1;i<=8;i++)
{
int xx=x+d[i][0],yy=y+d[i][1];
if(check(xx,yy)&&tmap[xx-1][yy+1]=='#')//打开周围8个格子
dfs(xx,yy);
}
}
}
void flag(int x,int y)
{
x-=1,y+=1;
if(tmap[x][y]=='F')//原本为小旗=>取消小旗
{
tmap[x][y]='#';mapc[x][y]=240;
gto(x+1,y-1),color(240),printf("#");
Wnum++;//更新小旗数
}
else//否则就放置小旗
{
is_flag_true[x][y]=map1[x][y]==-1;//判断小旗是否放对
tmap[x][y]='F';mapc[x][y]=253;
gto(x+1,y-1),color(253),printf("F");
Wnum--;//更新小旗数
}
gto(1,2*K+10);color(12);printf("剩余小旗数： ");
gto(1,2*K+22);printf("%d",Wnum);//更新小旗数
}
void bj(int x,int y)//和放小旗差不多，只是不用更新is_flag_true
{
x-=1,y+=1;
if(tmap[x][y]=='?')
{
gto(x+1,y-1),color(240),printf("#");
tmap[x][y]='#';mapc[x][y]=240;
}
else
{
if(tmap[x][y]=='F')//如果原本这个位置上是小旗，而你把它变为了标记，就要更新小旗数
{
Wnum++;
gto(1,2*K+10);color(12);printf("剩余小旗数： ");
gto(1,2*K+22);printf("%d",Wnum);
}
gto(x+1,y-1),color(240),printf("?");
tmap[x][y]='?';mapc[x][y]=240;
}
}
void swt(){QR=!QR;}
void zb()
{
if(ZB)//如果本来作弊打开了就把作弊地图清除
{
for(int i=1;i<=G;i++)
{
gto(i+1,K+2);
for(int j=1;j<=K;j++)
color(15),printf(" ");
}
ZB=0;
}
else//否则打印作弊地图
{
for(int i=1;i<=G;i++)
{
gto(i+1,K+2);
for(int j=1;j<=K;j++)
{
color(mapc[i][j]);
if(map1[i][j]==-1) printf("O");
else if(map1[i][j]>0) printf("%d",map1[i][j]);
else printf(" ");
}
}
ZB=1;
}
}
void again()
{
G=K=Lnum=nx=ny=Lose=ZB=0;
QR=0;
memset(is_flag_true,0,sizeof(is_flag_true));
memset(map,0,sizeof(map));
memset(tmap,0,sizeof(tmap));
memset(map1,0,sizeof(map1));
memset(mapc,0,sizeof(mapc));
color(15);
system("cls");//初始化
mainmain();
}
void begin()//各种操作
{
char c=getch(); 
gto(G+5,0),color(15),printf("请选择方块进行操作");
color(240);
if(c=='w'&&check(nx-1,ny))
{
gto(nx,ny);
if(tmap[nx-1][ny+1]!='#'||tmap[nx-1][ny+1]==' ')
color(mapc[nx-1][ny+1]);
printf("%c",tmap[nx-1][ny+1]);
gto(nx-=1,ny);color(15);printf("@");
}
else if(c=='s'&&check(nx+1,ny))
{
gto(nx,ny);if(tmap[nx-1][ny+1]!='#'||tmap[nx-1][ny+1]==' ')color(mapc[nx-1][ny+1]);printf("%c",tmap[nx-1][ny+1]);
gto(nx+=1,ny);color(15);printf("@");
}
else if(c=='a'&&check(nx,ny-1))
{
gto(nx,ny);if(tmap[nx-1][ny+1]!='#'||tmap[nx-1][ny+1]==' ')color(mapc[nx-1][ny+1]);printf("%c",tmap[nx-1][ny+1]);
gto(nx,ny-=1);color(15);printf("@");
}
else if(c=='d'&&check(nx,ny+1))
{
gto(nx,ny);if(tmap[nx-1][ny+1]!='#'||tmap[nx-1][ny+1]==' ')color(mapc[nx-1][ny+1]);printf("%c",tmap[nx-1][ny+1]);
gto(nx,ny+=1);color(15);printf("@");
}
//上下左右移动
else
{
if(c==' '&&(!(tmap[nx-1][ny+1]<='9'&&tmap[nx-1][ny+1]>='0'))&&tmap[nx-1][ny+1]!='F')
{
mapc[nx-1][ny+1]=col[map1[nx-1][ny+1]];//如果本来放了标记，mapc[nx-1][ny+1]的颜色为黑色,在打开时里面的颜色却不一定是黑色
if(QR)
{
gto(G+5,0),color(15),printf("请确认 ");
if(getch()==' ')
{
if(map1[nx-1][ny+1]==-1) {Lose=1;return;}
dfs(nx,ny);
}
}
else
{
if(map1[nx-1][ny+1]==-1) {Lose=1;return;}
dfs(nx,ny);
}
}
else if(c=='1')
{
if(QR)
{
gto(G+5,0),color(15),printf("请确认 ");
if(getch()=='1') st(nx,ny);
}
else st(nx,ny);
for(int i=1;i<=8;i++)
{
int xx=nx+d[i][0],yy=ny+d[i][1];
if(check(xx,yy))
{
gto(xx,yy);
if(tmap[xx-1][yy+1]!='#') color(mapc[xx-1][yy+1]);
else color(240);
printf("%c",tmap[xx-1][yy+1]);
}
}
}
else if(c=='2'&&(tmap[nx-1][ny+1]>'9'||tmap[nx-1][ny+1]<'1'))
{
if(QR)
{
gto(G+5,0),color(15),printf("请确认 ");
if(getch()=='2') flag(nx,ny);
}
else flag(nx,ny);
}
else if(c=='3'&&(tmap[nx-1][ny+1]>'9'||tmap[nx-1][ny+1]<'1'))
{
if(QR)
{
gto(G+5,0),color(15),printf("请确认 ");
if(getch()=='3') bj(nx,ny);
}
else bj(nx,ny);
}
else if(c=='4')
{
if(QR)
{
gto(G+5,0),color(15),printf("请确认 ");
if(getch()=='4') swt();
}
else swt();
}
else if(c=='5')
{
if(QR)
{
gto(G+5,0),color(15),printf("请确认 ");
if(getch()=='5') zb();
}
else zb();
}
else if(c=='0')
{
if(QR)
{
gto(G+5,0),color(15),printf("请确认 ");
if(getch()=='0') again();
}
else again();
}
}
}
void mainmain()
{
system("mode con cols=120 lines=35");//设置窗口大小
srand((unsigned)time(NULL));
int mode;
printf("1.初级\n2.中级\n3.高级\n4.自定义\n");
scanf("%d",&mode);if(mode>4) mode=4;
if(mode==1) G=9,K=9,Lnum=10;
else if(mode==2) G=16,K=16,Lnum=40;
else if(mode==3) G=16,K=30,Lnum=99;//三种等级的参数
else
{
printf("请输入雷区高度：");scanf("%d",&G);
printf("请输入雷区宽度：");scanf("%d",&K);
printf("请输入雷个数（建议不超过总大小的三分之一）：");scanf("%d",&Lnum);
if(G>24) G=24;if(K>30) K=30;
if(G<9) G=9;if(K<9) K=9;
if(Lnum<10) Lnum=10;if(Lnum>G*K*9/10) Lnum=G*K*9/10;
//控制参数的范围,最后一个if是雷的数量不超过地图大小的9/10
}
make();
print();
while(1)
{
begin();
bool f1=is_win(),f2=is_lose();
if(f1||f2)
{
gto(0,0);
if(f1)
color(202),gto(0,0),printf("你 赢 了！！是否重来？(y/n)");
if(f2)
color(137),gto(0,0),printf("你 输 了！！是否重来？(y/n)");//输赢
print_real_map();
char c=getch();
if(c=='y'||c=='Y') again();
else
{
color(15);
system("cls");
gto(MIDX,MIDY-5);
printf("欢迎下次再来");
return;
}
}
}
}
void print_real_map()
{
color(240);
for(int i=1;i<=G;i++)
{
gto(i+1,0);
for(int j=1;j<=K;j++)
{
if(tmap[i][j]=='F'&&is_flag_true[i][j]==0)//如果旗标错了显示红色的X
color(252),printf("X");
else if(map1[i][j]==-1)//雷为黑色O
color(240),printf("O");
else if(map1[i][j]==0)//空
color(240),printf(" ");
else//数字
color(mapc[i][j]),printf("%d",map1[i][j]);
}
}
}
