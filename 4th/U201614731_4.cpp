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

//继承的STACK用于入队列，新定义的s2用于出队列，两者之间的交互（s1中元素向s2转移）
//主要通过s1元素依次出栈，再入栈s2，来完成 
class QUEUE : public STACK{
    STACK  s2;
public:
QUEUE(int m); //每个栈最多m个元素，要求实现的队列最多能入2m个元素
QUEUE(const QUEUE&s); 			//用队列s拷贝初始化队列
virtual operator int ( ) const;			//返回队列的实际元素个数
virtual int full ( ) const;		       //返回队列是否已满，满返回1，否则返回0
virtual int operator[ ](int x)const;   //取下标为x的元素，第1个元素下标为0
virtual QUEUE& operator<<(int e);  //将e入队列,并返回队列
virtual QUEUE& operator>>(int &e);	//出队列到e,并返回队列
virtual QUEUE& operator=(const QUEUE&s); //赋s给队列,并返回被赋值的队列
virtual void print( ) const;			//打印队列
virtual ~QUEUE( );					//销毁队列
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

QUEUE::QUEUE(int m) : STACK(m),s2(m){

};

QUEUE::QUEUE(const QUEUE &s) : STACK(s.s2.size()),s2(s.s2.size()){
	*this = s;
} 
//返回队列中元素个数 
QUEUE::operator int ( ) const{

	return STACK::operator int()+int(s2); 
} 

//判断队列是否已满，满则返回1，否则返回0
//判据：入队栈满则队列满 
int QUEUE::full ( ) const{
	if(STACK::operator int()==STACK::size() )
		return 1;
	
	return 0;
}	

//取队列中下标为x的元素
int QUEUE::operator[ ](int x)const{
	int num_2 = int(s2);//s2中队列下标为0~num_2-1 
	
	if(num_2>x)//即该元素在s2中
		return s2[num_2-x-1];
	//运行至此即为元素存在于s1中
	 
	return STACK::operator[](x-num_2);
}

//将e入队列并返回队列  
QUEUE& QUEUE::operator<<(int e){
	int temp;

	if (STACK::operator int() == 0) {	// s1为空
		if (int(s2) < s2.size()) {		// s2未满
		
			while (int(s2) > 0) {
				s2 >> temp;
				STACK::operator<<(temp);
			}
			// 元素e入栈s1
			STACK::operator<<(e);
			// s1转入s2
			while ( STACK::operator int() > 0) {
				STACK::operator >> (temp);
				s2 << temp;
			}
		}
		else 	// s2已满，e入s1中
			STACK::operator<<(e);
	}
	else		// s1不为空，e直接入s1中
		STACK::operator<<(e);
	return *this;
	
}


QUEUE& QUEUE::operator>>(int &e)//出队列到e,并返回队列
{
	s2 >> e;
	int temp;
	if ((int)s2 == 0) {
		// s1转入s2
		while (STACK::operator int() > 0) {
			STACK::operator >> (temp);
			s2 << temp;
		}
	}
	return *this;	
}

//默认两队列类型相同 
QUEUE& QUEUE::operator=(const QUEUE&s)
{
	this->STACK::operator=(s);
	
	int i;
//	this->STACK = s.STACK;
//	int count = this->STACK::operator int();
//	int temp;
//	for ( i = 0; i < count; i++)
//		this->STACK::operator>>(temp);
//	count = s.STACK::operator int();
//	for (i = 0; i < count && i < this->STACK::size(); i++)
//		this->STACK::operator<<(s.STACK::operator[](i));
	this->s2=s.s2;
	
	return *this; 
	
} 

void QUEUE::print( ) const
{
	int i,count;
	count = this->operator int();
	
	for (i = 0; i < count; i++) {
		fprintf(fp, "%d  ", this->operator[](i));
	}
	
	return ;
}

QUEUE::~QUEUE( )
{
	
}

int main(int argc,char* argv[])
{
	//-----------------------------------------------------
	//舞伴问题求解
	if(argc==1)
	{
		int M,F;
		int targ_m,targ_f,dnc_m,dnc_f;
		printf("请输入男士队人数：");
		scanf("%d",&M); 
		printf("请输入女士队人数：");
		scanf("%d",&F); 
		printf("请输入目标男士位置：");
		scanf("%d",&targ_m); 
		printf("请输入目标女士位置：");
		scanf("%d",&targ_f); 
		
		QUEUE M_q(M);
		QUEUE F_q(F);
		int que;
		
		if(M==F&&targ_m!=targ_f)
			printf("二人不会共舞。");
		else if(targ_m>M||targ_f>F)
			printf("输入无效。"); 
		else{
			for(que = 0;que<M;que++)
			{
				if(que==targ_m-1)
					M_q<<1;
				else
					M_q<<0;
			}
			
			for(que = 0;que<F;que++)
			{
				if(que==targ_f-1)
					F_q<<1;
				else
					F_q<<0;
			}
			
			for(que=1; ;que++)
			{
				M_q>>dnc_m;
				F_q>>dnc_f;
				
				if(dnc_m&&dnc_f)
					break;
				
				M_q<<dnc_m;
				F_q<<dnc_f;
			}
			
			printf("第%d支舞曲二人共舞",que);
		} 
		getchar();
	}
	
	//-----------------------------------------------------
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
	QUEUE p(m);
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
					if(p.full()==1)
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
				QUEUE new_stack(p);
				new_stack.print();
			}
			else if(choice[1] == 'A')
			{
				fprintf(fp,"%c  ",'A');
				strcpy(choice,argv[cmd++]);
				m = atoi(choice);
				QUEUE new_stack(m);
				
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

