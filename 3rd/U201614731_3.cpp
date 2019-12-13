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

int main(int argc,char* argv[])
{
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
	STACK p(m);
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

