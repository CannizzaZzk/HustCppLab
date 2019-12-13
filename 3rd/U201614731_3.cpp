#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <iostream> 

class STACK{
    int  *const  elems;	//申请内存用于存放栈的元素
    const  int   max;	//栈能存放的最大元素个数
    int   pos;			//栈实际已有元素个数，栈空时pos=0;
public:
STACK(int m);		//初始化栈：最多m个元素
STACK(const STACK&s); 			//用栈s拷贝初始化栈
virtual int  size ( ) const;			//返回栈的最大元素个数max
virtual operator int ( ) const;			//返回栈的实际元素个数pos
virtual int operator[ ] (int x) const;	//取下标x处的栈元素
virtual STACK& operator<<(int e); 	//将e入栈,并返回栈
virtual STACK& operator>>(int &e);	//出栈到e,并返回栈
virtual STACK& operator=(const STACK&s); //赋s给栈,并返回被赋值的栈
virtual void print( ) const;			//打印栈
virtual ~STACK( );					//销毁栈
};
FILE* fp;

STACK::STACK(int m) : elems(new int[m]),max(m){
	pos = 0;
}

STACK::STACK(const STACK&s) : elems(new int[s.max]),max(s.max){
	for(int i = 0;i<s.pos;i++)
		elems[i] = s.elems[i];
	
	pos = s.pos;
}

int STACK::size() const{
	return max;
}

STACK::operator int ( ) const{			//返回栈的实际元素个数pos
	return pos;
}

int STACK::operator[](int x) const{
	return elems[x];
}

STACK& STACK::operator<<(int e){//将e入栈,并返回栈
	elems[pos] = e;
	pos+=1;
	
	return *this;
}

STACK& STACK::operator>>(int &e){
	e = elems[pos-1];
	pos-=1;
	
	return *this;
}
	
STACK& STACK::operator=(const STACK&s){	
	for(int i=0;i<s.pos;i++)
		elems[i] = s.elems[i];
	
	pos = s.pos;
	
	return *this; 
}

void STACK::print( ) const{
	for(int i=0;i<pos;i++)
		fprintf(fp,"%d  ",elems[i]);
	
	return ;
}

STACK::~STACK( ){
	delete elems;
}

int main(int argc,char* argv[])
{
	int m,e,x;
	int cmd,count;
	
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
	
	cmd+=1;
	strcpy(choice,argv[cmd++]);
	m = atoi(choice);
	STACK p(m);
	fprintf(fp,"%c  %d  ",'S',m);
		
	
	while(cmd <= argc-1)
	{
		strcpy(choice,argv[cmd++]);
		if(choice[0] == '-')
		{
		
			if(choice[1] == 'I')//入栈操作，指令为-I，其后跟随的数字依次入栈 
			{
				fprintf(fp,"%c  ",'I');
				while(1)
				{
					if(cmd == argc)
					{
						p.print();
						break;	
					}
						
					strcpy(choice,argv[cmd++]);
					if(choice[0] == '-')
					{
						p.print();
						cmd-=1;
						break;
					}
					
 					e = atoi(choice);
					//检验栈中是否有空间，有的话就进行入栈操作，否则跳出循环报错 
					if(int(p) == p.size())
					{
						fprintf(fp,"%c  ",'E');
						cmd = argc;
						break ;
					}
					else 
						p<<e;		
				}
			}
			else if(choice[1] == 'O')//出栈操作，指令为-O，其后跟随的数字数为需出栈的元素数 
			{
				fprintf(fp,"%c  ",'O');
				strcpy(choice,argv[cmd++]);
				count = atoi(choice);
				//检验栈中元素数量是否足够
				if(int(p) < count)
				{
					fprintf(fp,"%c  ",'E');
					cmd = argc;
					break ;
				} 
				else 
				{
					for(int i = 0;i<count;i++)
						p>>e;
				}
				p.print();
			}
			else if(choice[1] == 'C')
			{
				fprintf(fp,"%c  ",'C');
				STACK new_stack(p);
				new_stack.print();
			}
			else if(choice[1] == 'A')
			{
				fprintf(fp,"%c  ",'A');
				strcpy(choice,argv[cmd++]);
				m = atoi(choice);
				STACK new_stack(m);
				
				new_stack = p;
				new_stack.print();
			}
			else if(choice[1] == 'N')
			{
				fprintf(fp,"%c  ",'N');
				count = int(p);
				fprintf(fp,"%d  ",count);
			}
			else if(choice[1] == 'G')
			{
				fprintf(fp,"%c  ",'G');
				strcpy(choice,argv[cmd++]);
				x = atoi(choice);
				//如果下标x大于当前元素数目，报错
				if(x>=int(p))
				{
					fprintf(fp,"%c  ",'E');
					cmd = argc;
					break;
				} 
				
				fprintf(fp,"%d  ",p[x]);
			}
		}
	}
	
	
	
	
//	printf("%d \n",argc);
//	printf("%s",file_name);

	return 0; 
}

