#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <iostream> 
struct STACK{
    int  *elems;	//�����ڴ����ڴ��ջ��Ԫ��
    int   max;	//ջ�ܴ�ŵ����Ԫ�ظ���
    int   pos;	//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
};
FILE *fp;
typedef STACK STACK;
void initSTACK(STACK *const p, int m);	//��ʼ��pָ���ջ�����m��Ԫ��
void initSTACK_1(STACK *const p, const STACK&s); //��ջs��ʼ��pָ���ջ
int  size (const STACK *const p);		//����pָ���ջ�����Ԫ�ظ���max
int  howMany (const STACK *const p);	//����pָ���ջ��ʵ��Ԫ�ظ���pos
int  getelem (const STACK *const p, int x);	//ȡ�±�x����ջԪ��
STACK *const push(STACK *const p, int e); 	//��e��ջ��������p
STACK *const pop(STACK *const p, int &e); 	//��ջ��e��������p
STACK *const assign(STACK*const p, const STACK&s); //��s��pָ��ջ,������p
void print(const STACK*const p);			//��ӡpָ���ջ
void destroySTACK(STACK*const p);		//����pָ���ջ

int main(int argc,char* argv[])
{
	int m,e,x;
	int cmd,count;
	STACK * p;
	p = (STACK*)malloc(sizeof(STACK));
	
	cmd = 0;//˳���ȡ�����в��� 

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
			if(choice[1] == 'S')//��ʼ��ջ��ָ��Ϊ-S��������ջ�ĳ��� 
			{
				strcpy(choice,argv[cmd++]);
				m = atoi(choice);
				initSTACK(p,m);
				fprintf(fp,"%c  %d  ",'S',m);
			}
			else if(choice[1] == 'I')//��ջ������ָ��Ϊ-I�������������������ջ 
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
					//����ջ���Ƿ��пռ䣬�еĻ��ͽ�����ջ��������������ѭ������ 
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
			else if(choice[1] == 'O')//��ջ������ָ��Ϊ-O���������������Ϊ���ջ��Ԫ���� 
			{
				fprintf(fp,"%c  ",'O');
				strcpy(choice,argv[cmd++]);
				count = atoi(choice);
				//����ջ��Ԫ�������Ƿ��㹻
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
				//����±�x���ڵ�ǰԪ����Ŀ������
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

int  size (const STACK *const p)	//����pָ���ջ�����Ԫ�ظ���max
{
	return p->max;
}

int  howMany (const STACK *const p)	//����pָ���ջ��ʵ��Ԫ�ظ���pos
{
	return p->pos;	
}

int  getelem (const STACK *const p, int x)	//ȡ�±�x����ջԪ��
{
	return p->elems[x];
}

STACK *const push(STACK *const p, int e) 	//��e��ջ��������p
{
	int position = p->pos;
	p->elems[position] = e;
	p->pos += 1;
	
	return p;
}

STACK *const pop(STACK *const p, int &e) 	//��ջ��e��������p
{
	int position = p->pos - 1;
	e = p->elems[position];
	p->pos -= 1;
	
	return p;
}

STACK *const assign(STACK*const p, const STACK&s) //��s��pָ��ջ,������p
{
	p->max = s.max;
	p->elems = (int*)malloc(sizeof(int)*s.max);
	int i;
	for(i=0;i<s.pos;i++)
		p->elems[i] = s.elems[i];
	
	p->pos = s.pos;
	
	return p;
}

void print(const STACK*const p)			//��ӡpָ���ջ
{
	int i;
	for(i=0;i<p->pos;i++)
		fprintf(fp,"%d  ",p->elems[i]);

	 
	return ;
}


void destroySTACK(STACK*const p)		//����pָ���ջ
{
	free(p->elems);
		
	return ;		
}
