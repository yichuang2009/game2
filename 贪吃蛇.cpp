#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

typedef struct snake
{
	int a;
	int b;
	struct snake *u;
	struct snake *n;
}snake,*snake1;
typedef struct food
{
	int a;
	int b;
}food;
int main()
{   
	char c,c0 = 'd';
	int i,j,k,n=1,t,at;
	snake p,q;
	snake *dd,*dd0,*dd1,*dd2;
	food f;
	srand((unsigned)time(NULL));
	p.u = NULL;
	p.n = &q;
	p.a = 5;p.b = 6;q.a = 5;q.b = 5;
	q.u = &p;q.n = NULL;
	dd=dd2= &q;
	f.a=(rand()%15+1);
	f.b=(rand()%15+1);
	while(1)
	{
		srand((unsigned)time(NULL));
		system("cls");
		for(i = 0;i < 17;i ++)
		{
			for(j = 0; j < 17;j++)
			{

				if(i == 0 )
					printf("¨x");
				else if(i == 16)
					printf("¨‰");
				else if(j == 0)
					printf("¨Š");
				else if(j == 16)
					printf("¨‡");
				else if(i == p.a && j == p.b)
					printf("¡ö");
				else if(i == f.a && j == f.b)
					printf("¡ï");
				else 
				{
					t = 0;
					dd = dd2;
					for(k = 0; k < n ;k++)
					{ 
						if(i == dd->a && j == dd->b)
						{
							printf("¡õ");
							t = 1;
							break;
						}
			
						dd = dd->u;	
					}
					if(t == 0)
						printf("  ");
				}
				
			}printf("\n");
		}
		at = 0;
		dd =dd2;
		for(i=0;i<n;i++)
		{
			if(p.a == dd->a  && p.b == dd->b)
			{
				printf("game over!!\n");
				exit(0);
			}
			dd = dd->u;
		}
		if(p.a == f.a && p.b == f.b)
		{
			dd = dd2;
			at =1;
			f.a = (rand()%15+1);
			f.b = (rand()%15+1);
			for(i=0;i<n;i++)
			{
				if(f.a == dd->a && f.b == dd->b)
				{
					f.a = dd2->a;
					f.b = dd2->b;
					break;
				}
			}
			n++;
		}
		if(kbhit())
		{
			c = getch();
			dd = dd2;
			if(c == 'w' && c0 != 's')
			{
				if(at == 1)
				{
					dd0 =(snake1)malloc(sizeof(snake));
					dd0->a = dd2->a;dd0->b = dd2->b;
					dd0->n = NULL;dd0->u = dd2;
					dd2=dd0;
				}
				dd = dd2;
				for(i = 0; i<n ; i++)
				{
					dd1 = dd->u;
					dd->b = dd1->b;
					dd->a = dd1->a;
					dd = dd->u;
				}
				if(p.a == 1)
					p.a = 15;
				else
					p.a = (p.a-1)%15;
			}
			else if(c == 's' && c0 != 'w')
			{	
				if(at == 1)
				{
					dd0 =(snake1)malloc(sizeof(snake));
					dd0->a = dd2->a;dd0->b = dd2->b;
					dd0->n = NULL;dd0->u = dd2;
					dd2=dd0;
				}
				dd = dd2;
				for(i = 0; i<n ; i++)
				{
					dd1 = dd->u;
					dd->b = dd1->b;
					dd->a = dd1->a;
					dd = dd->u;
				}
				p.a = (p.a%15)+1;
			}
			else if(c == 'a' && c0 != 'd')
			{	
				if(at == 1)
				{
					dd0 =(snake1)malloc(sizeof(snake));
					dd0->a = dd2->a;dd0->b = dd2->b;
					dd0->n = NULL;dd0->u = dd2;
					dd2=dd0;
				}
				dd = dd2;
				for(i = 0; i<n ; i++)
				{
					dd1 = dd->u;
					dd->b = dd1->b;
					dd->a = dd1->a;
					dd = dd->u;
				}
				if(p.b == 1)
					p.b = 15;
				else
					p.b = (p.b-1)%15;
			}
			else if(c == 'd' && c0 != 'a')
			{	
				if(at == 1)
				{
					dd0 =(snake1)malloc(sizeof(snake));
					dd0->a = dd2->a;dd0->b = dd2->b;
					dd0->n = NULL;dd0->u = dd2;
					dd2=dd0;
				}
				dd = dd2;
				for(i = 0; i<n ; i++)
				{
					dd1 = dd->u;
					dd->b = dd1->b;
					dd->a = dd1->a;
					dd = dd->u;
				}
				p.b = (p.b%15)+1;
			}			
			else
			{
				goto qq;
			}
			c0 = c;
		}
		else
		{
qq:			if(c0 == 'w')
			{
				if(at == 1)
				{
					dd0 =(snake1)malloc(sizeof(snake));
					dd0->a = dd2->a;dd0->b = dd2->b;
					dd0->n = NULL;dd0->u = dd2;
					dd2=dd0;
				}
				dd = dd2;
				for(i = 0; i<n ; i++)
				{
					dd1 = dd->u;
					dd->b = dd1->b;
					dd->a = dd1->a;
					dd = dd->u;
				}
				if(p.a == 1)
					p.a = 15;
				else
					p.a=(p.a-1)%15;
			}
			else if(c0 == 's')
			{
				if(at == 1)
				{
					dd0 =(snake1)malloc(sizeof(snake));
					dd0->a = dd2->a;dd0->b = dd2->b;
					dd0->n = NULL;dd0->u = dd2;
					dd2=dd0;
				}
				dd = dd2;
				for(i = 0; i<n ; i++)
				{
					dd1 = dd->u;
					dd->b = dd1->b;
					dd->a = dd1->a;
					dd = dd->u;
				}
				p.a=(p.a%15)+1;
			}
			else if(c0 == 'a')
			{
				
				if(at == 1)
				{
					dd0 =(snake1)malloc(sizeof(snake));
					dd0->a = dd2->a;dd0->b = dd2->b;
					dd0->n = NULL;dd0->u = dd2;
					dd2=dd0;
				}
				dd = dd2;
				for(i = 0; i<n ; i++)
				{
					dd1 = dd->u;
					dd->b = dd1->b;
					dd->a = dd1->a;
					dd = dd->u;
				}
				if(p.b == 1)
					p.b = 15;
				else
					p.b=(p.b-1)%15;
			}
			else if(c0 == 'd')
			{
				if(at == 1)
				{
					dd0 =(snake1)malloc(sizeof(snake));
					dd0->a = dd2->a;dd0->b = dd2->b;
					dd0->n = NULL;dd0->u = dd2;
					dd2=dd0;
				}
				dd = dd2;
				for(i = 0; i<n ; i++)
				{
					dd1 = dd->u;
					dd->b = dd1->b;
					dd->a = dd1->a;
					dd = dd->u;
				}
				p.b=(p.b%15)+1;
				
			}
		}
		fflush(stdin);
		dd = &q;
		_sleep(50);
	}
}

