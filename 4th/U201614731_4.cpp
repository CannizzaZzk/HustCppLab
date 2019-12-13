#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <iostream> 


class STACK{
    int  *const  elems;	//�����ڴ����ڴ��ջ��Ԫ��
    const  int   max;	//ջ�ܴ�ŵ����Ԫ�ظ���
    int   pos;			//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
public:
STACK(int m);		//��ʼ��ջ�����m��Ԫ��
STACK(const STACK&s); 			//��ջs������ʼ��ջ
virtual int  size ( ) const;			//����ջ�����Ԫ�ظ���max
virtual operator int ( ) const;			//����ջ��ʵ��Ԫ�ظ���pos
virtual int operator[ ] (int x) const;	//ȡ�±�x����ջԪ��
virtual STACK& operator<<(int e); 	//��e��ջ,������ջ
virtual STACK& operator>>(int &e);	//��ջ��e,������ջ
virtual STACK& operator=(const STACK&s); //��s��ջ,�����ر���ֵ��ջ
virtual void print( ) const;			//��ӡջ
virtual ~STACK( );					//����ջ
};

//�̳е�STACK��������У��¶����s2���ڳ����У�����֮��Ľ�����s1��Ԫ����s2ת�ƣ�
//��Ҫͨ��s1Ԫ�����γ�ջ������ջs2������� 
class QUEUE : public STACK{
    STACK  s2;
public:
QUEUE(int m); //ÿ��ջ���m��Ԫ�أ�Ҫ��ʵ�ֵĶ����������2m��Ԫ��
QUEUE(const QUEUE&s); 			//�ö���s������ʼ������
virtual operator int ( ) const;			//���ض��е�ʵ��Ԫ�ظ���
virtual int full ( ) const;		       //���ض����Ƿ�������������1�����򷵻�0
virtual int operator[ ](int x)const;   //ȡ�±�Ϊx��Ԫ�أ���1��Ԫ���±�Ϊ0
virtual QUEUE& operator<<(int e);  //��e�����,�����ض���
virtual QUEUE& operator>>(int &e);	//�����е�e,�����ض���
virtual QUEUE& operator=(const QUEUE&s); //��s������,�����ر���ֵ�Ķ���
virtual void print( ) const;			//��ӡ����
virtual ~QUEUE( );					//���ٶ���
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

STACK::operator int ( ) const{			//����ջ��ʵ��Ԫ�ظ���pos
	return pos;
}

int STACK::operator[](int x) const{
	return elems[x];
}

STACK& STACK::operator<<(int e){//��e��ջ,������ջ
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
//���ض�����Ԫ�ظ��� 
QUEUE::operator int ( ) const{

	return STACK::operator int()+int(s2); 
} 

//�ж϶����Ƿ����������򷵻�1�����򷵻�0
//�оݣ����ջ��������� 
int QUEUE::full ( ) const{
	if(STACK::operator int()==STACK::size() )
		return 1;
	
	return 0;
}	

//ȡ�������±�Ϊx��Ԫ��
int QUEUE::operator[ ](int x)const{
	int num_2 = int(s2);//s2�ж����±�Ϊ0~num_2-1 
	
	if(num_2>x)//����Ԫ����s2��
		return s2[num_2-x-1];
	//�������˼�ΪԪ�ش�����s1��
	 
	return STACK::operator[](x-num_2);
}

//��e����в����ض���  
QUEUE& QUEUE::operator<<(int e){
	int temp;

	if (STACK::operator int() == 0) {	// s1Ϊ��
		if (int(s2) < s2.size()) {		// s2δ��
		
			while (int(s2) > 0) {
				s2 >> temp;
				STACK::operator<<(temp);
			}
			// Ԫ��e��ջs1
			STACK::operator<<(e);
			// s1ת��s2
			while ( STACK::operator int() > 0) {
				STACK::operator >> (temp);
				s2 << temp;
			}
		}
		else 	// s2������e��s1��
			STACK::operator<<(e);
	}
	else		// s1��Ϊ�գ�eֱ����s1��
		STACK::operator<<(e);
	return *this;
	
}


QUEUE& QUEUE::operator>>(int &e)//�����е�e,�����ض���
{
	s2 >> e;
	int temp;
	if ((int)s2 == 0) {
		// s1ת��s2
		while (STACK::operator int() > 0) {
			STACK::operator >> (temp);
			s2 << temp;
		}
	}
	return *this;	
}

//Ĭ��������������ͬ 
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
	//����������
	if(argc==1)
	{
		int M,F;
		int targ_m,targ_f,dnc_m,dnc_f;
		printf("��������ʿ��������");
		scanf("%d",&M); 
		printf("������Ůʿ��������");
		scanf("%d",&F); 
		printf("������Ŀ����ʿλ�ã�");
		scanf("%d",&targ_m); 
		printf("������Ŀ��Ůʿλ�ã�");
		scanf("%d",&targ_f); 
		
		QUEUE M_q(M);
		QUEUE F_q(F);
		int que;
		
		if(M==F&&targ_m!=targ_f)
			printf("���˲��Ṳ�衣");
		else if(targ_m>M||targ_f>F)
			printf("������Ч��"); 
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
			
			printf("��%d֧�������˹���",que);
		} 
		getchar();
	}
	
	//-----------------------------------------------------
	int m,e,x;
	int cmd,count;
	
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
		
			if(choice[1] == 'I')//��ջ������ָ��Ϊ-I�������������������ջ 
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
					//����ջ���Ƿ��пռ䣬�еĻ��ͽ�����ջ��������������ѭ������ 
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
			else if(choice[1] == 'O')//��ջ������ָ��Ϊ-O���������������Ϊ���ջ��Ԫ���� 
			{
				fprintf(fp,"%c  ",'O');
				strcpy(choice,argv[cmd++]);
				count = atoi(choice);
				//����ջ��Ԫ�������Ƿ��㹻
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
				//����±�x���ڵ�ǰԪ����Ŀ������
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

