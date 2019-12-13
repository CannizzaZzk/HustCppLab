#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <iostream> 
struct STACK{
    int  *elems;	//申请内存用于存放栈的元素
    int   max;	//栈能存放的最大元素个数
    int   pos;	//栈实际已有元素个数，栈空时pos=0;
};
FILE *fp;
typedef STACK STACK;
void initSTACK(STACK *const p, int m);	//初始化p指向的栈：最多m个元素
void initSTACK_1(STACK *const p, const STACK&s); //用栈s初始化p指向的栈
int  size (const STACK *const p);		//返回p指向的栈的最大元素个数max
int  howMany (const STACK *const p);	//返回p指向的栈的实际元素个数pos
int  getelem (const STACK *const p, int x);	//取下标x处的栈元素
STACK *const push(STACK *const p, int e); 	//将e入栈，并返回p
STACK *const pop(STACK *const p, int &e); 	//出栈到e，并返回p
STACK *const assign(STACK*const p, const STACK&s); //赋s给p指的栈,并返回p
void print(const STACK*const p);			//打印p指向的栈
void destroySTACK(STACK*const p);		//销毁p指向的栈

int main(int argc,char* argv[])
{
	int m,e,x;
	int cmd,count;
	STACK * p;
	p = (STACK*)malloc(sizeof(STACK));
	
	cmd = 0;//顺序读取命令行参数 

//	printf("%d \n",argc);
	char file_name[100];
	
//	for(int i=0;i<argc;i++)
//		printf("%s\n",argv[i]);
	
	strcpy(file_name,argv[cmd++]);
	int del;
	del = strlen(file_name);
	for(int j=0;j<4;j++)
	{
		file_name[del-1] = file_name[del];
		del-=1;
	}
	strcat(file_name,".txt");

	fp = fopen(file_name,"w+");
	
	char choice[5];
	
	while(cmd <= argc-1)
	{
		strcpy(choice,argv[cmd++]);
		if(choice[0] == '-')
		{
			if(choice[1] == 'S')//初始化栈，指令为-S，其后跟随栈的长度 
			{
				strcpy(choice,argv[cmd++]);
				m = atoi(choice);
				initSTACK(p,m);
				fprintf(fp,"%c  %d  ",'S',m);
			}
			else if(choice[1] == 'I')//入栈操作，指令为-I，其后跟随的数字依次入栈 
			{
				fprintf(fp,"%c  ",'I');
				while(1)
				{
					if(cmd == argc)
					{
						print(p);
						break;	
					}
						
					strcpy(choice,argv[cmd++]);
					if(choice[0] == '-')
					{
						print(p);
						cmd-=1;
						break;
					}
					
 					e = atoi(choice);
					//检验栈中是否有空间，有的话就进行入栈操作，否则跳出循环报错 
					if(p->pos == p->max)
					{
						fprintf(fp,"%c  ",'E');
						cmd = argc;
						break ;
					}
					else 
						push(p,e);		
				}
			}
			else if(choice[1] == 'O')//出栈操作，指令为-O，其后跟随的数字数为需出栈的元素数 
			{
				fprintf(fp,"%c  ",'O');
				strcpy(choice,argv[cmd++]);
				count = atoi(choice);
				//检验栈中元素数量是否足够
				if(p->pos < count)
				{
					fprintf(fp,"%c  ",'E');
					cmd = argc;
					break ;
				} 
				else 
				{
					for(int i = 0;i<count;i++)
						pop(p,e);
				}
				print(p);
			}
			else if(choice[1] == 'C')
			{
				fprintf(fp,"%c  ",'C');
				STACK * new_stack;
					new_stack = (STACK*)malloc(sizeof(STACK));
				const STACK q = *p;
				initSTACK_1(new_stack,q);
				print(new_stack);
			}
			else if(choice[1] == 'A')
			{
				fprintf(fp,"%c  ",'A');
				strcpy(choice,argv[cmd++]);
				m = atoi(choice);
				STACK *new_stack;
				new_stack = (STACK*)malloc(sizeof(STACK));
				initSTACK(new_stack,m);
				
				assign(new_stack,*p);
				print(new_stack);
			}
			else if(choice[1] == 'N')
			{
				fprintf(fp,"%c  ",'N');
				count = howMany(p);
				fprintf(fp,"%d  ",count);
			}
			else if(choice[1] == 'G')
			{
				fprintf(fp,"%c  ",'G');
				strcpy(choice,argv[cmd++]);
				x = atoi(choice);
				//如果下标x大于当前元素数目，报错
				if(x>=p->pos)
				{
					fprintf(fp,"%c  ",'E');
					cmd = argc;
					break;
				} 
				
				fprintf(fp,"%d  ",getelem(p,x));
			}
		}
	}
	
	
	
	
//	printf("%d \n",argc);
//	printf("%s",file_name);

	return 0; 
}

void initSTACK(STACK *const p, int m)
{
	p->elems = (int*)malloc(sizeof(int) * m);
	p->max = m;
	p->pos = 0;
	
	return ;
}

void initSTACK_1(STACK *const p,const STACK &s)
{

	p->elems = (int*)malloc(sizeof(int) * s.max);
	p->max = s.max;
	p->pos = 0;
	
	int i;
	for(i=0;i<s.pos;i++)
		p->elems[i] = s.elems[i];
	
	
	p->pos = i;
	
	return ;
}

int  size (const STACK *const p)	//返回p指向的栈的最大元素个数max
{
	return p->max;
}

int  howMany (const STACK *const p)	//返回p指向的栈的实际元素个数pos
{
	return p->pos;	
}

int  getelem (const STACK *const p, int x)	//取下标x处的栈元素
{
	return p->elems[x];
}

STACK *const push(STACK *const p, int e) 	//将e入栈，并返回p
{
	int position = p->pos;
	p->elems[position] = e;
	p->pos += 1;
	
	return p;
}

STACK *const pop(STACK *const p, int &e) 	//出栈到e，并返回p
{
	int position = p->pos - 1;
	e = p->elems[position];
	p->pos -= 1;
	
	return p;
}

STACK *const assign(STACK*const p, const STACK&s) //赋s给p指的栈,并返回p
{
	p->max = s.max;
	p->elems = (int*)malloc(sizeof(int)*s.max);
	int i;
	for(i=0;i<s.pos;i++)
		p->elems[i] = s.elems[i];
	
	p->pos = s.pos;
	
	return p;
}

void print(const STACK*const p)			//打印p指向的栈
{
	int i;
	for(i=0;i<p->pos;i++)
		fprintf(fp,"%d  ",p->elems[i]);

	 
	return ;
}


void destroySTACK(STACK*const p)		//销毁p指向的栈
{
	free(p->elems);
		
	return ;		
}
