//�����루�Ź��񣩡�ƴͼ��Ϸ������
/*==============================================================================
	�����������δ�ҵ�·��ʱ��������ʲô��

	�Ƿ�Ϊ OPEN ��Ϊ��ʱ��δ�ҵ�·����Ϊ�޽�����

	��˵Ļ���������̫�󣨴������Ϊ9���������������ø����޷����е����-_-�������Բ�֪���Ƿ���ȷ��

==============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_NODESIZE 362880	//9�Ľ׳�9!=362880

typedef struct node{		//������ṹ��

	int a[3][3];//�ڵ�״̬

	//�ո��±�
	int i_0;
	int j_0;

	//������Ϣ
	int d;		//�������
	int w;		//�����Ӳ�����ȷλ�õ���Ŀ
	int f;		//�ܴ���

	struct node *father;	//ָ�򸸽ڵ�ָ��

}node,*p_node;


typedef struct list	//˳���ṹ��
{
	p_node a[MAX_NODESIZE];
	long length;

}list,*p_list;

//static int s0[3][3]={8,2,3,1,0,4,7,6,5};	//��ʼ���

static int s0[3][3]={2,8,3,1,0,4,7,6,5};	//��ʼ���
/*
2	8	3
1	0	4
7	6	5
*/

static int sg[3][3]={1,2,3,8,0,4,7,6,5};	//Ŀ����
/*
1	2	3
8	0	4
7	6	5
*/

p_node s_0=(p_node) malloc(sizeof(node));	//��ʼ�ڵ�
p_node s_g=(p_node) malloc(sizeof(node));	//Ŀ��ڵ�

p_list OPEN  =(p_list) malloc (sizeof(list));	//OPEN��
p_list CLOSED=(p_list) malloc (sizeof(list));	//CLOSE��


int w(p_node s);						//��������Ӳ�����ȷλ�õ���Ŀ
int f(p_node s);						//���ۺ���
void init_node();						//��ʼ��
void out_node(p_node s);				//���������
void list_reverse(p_node &p);			//����������
void out_list(p_list &l);				//���OPEN��
bool search_list(p_list &l,p_node s);	//�Ա���в��ң��ɹ�����true
void sort_list(p_list &l);				//��OPEN��������򣨰�f��С����
void add_list(p_list &l,p_node s);		//�����㵽OPEN���л�CLOSE����
void copy_node(p_node s1,p_node &s2);	//�����µĽ�㣨��s2��ֵ��s1��
void delete_list(p_list &l);			//��OPEN���CLOSE��ɾ�����
bool is_equal(p_node s1,p_node s2);		//�ж����ڵ��Ƿ����
bool up_mov(p_node &s);					//�ո�����
bool down_mov(p_node &s);				//�ո�����
bool left_mov(p_node &s);				//�ո�����
bool right_mov(p_node &s);				//�ո�����
void move(p_node s);					//�ƶ����ڵ㲢����δ̽�����У���չ��㣩


int main()
{
	init_node();

	printf("\n�������������£�\n");
	printf("=========================================================\n\n");

	while(OPEN->length!=0 && CLOSED->length<=1000)	//���ѭ������1000
	{

		p_node n=OPEN->a[0];		//---------------��Open��ĵ�һ���ڵ�ȡ������Closed�����Ǹýڵ�Ϊn
		delete_list(OPEN);

		if(is_equal(n,s_g))	//����ڵ�n�Ƿ�ΪĿ��ڵ㡣���ǣ����ҵ�������Ľ⣬�ɹ��˳�����ɻ��� if(w(n)==0){...}
		{
			list_reverse(n);
			list_reverse(n);
			list_reverse(n);

			while(n)
			{
				printf("�� %d ����\n",n->d+1);
				out_node(n);
				n=n->father;
			}

			break;
		}

		add_list(CLOSED,n);

		move(n);//��չ���n

		sort_list(OPEN);
	//	out_list(OPEN);
	}

	if(OPEN->length==0 || CLOSED->length>1000)
	{
		printf("\n�ӳ�ʼ����޷�����Ŀ���㣡\n\n");
	}

	return 0;
}

int f(p_node s)	//���ۺ���
{
	return (s->d+s->w);
}


void out_node(p_node s)	//���������
{

	printf("-------------------");
	printf(" x=%d,y=%d\n",s->i_0,s->j_0);
	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			printf("%5d",s->a[i][j]);
		}

		printf("\n");
	}
	printf("-------------------");
	printf(" d=%d,w=%d;  f=%d\n\n\n",s->d,s->w,s->f);

}


void out_list(p_list &l)		//���OPEN��
{

	printf("****************************************************************\n");
	for(int i=0;i<l->length;i++)
	{
		out_node(l->a[i]);
	}
	printf("****************************************************************\n");
}


int w(p_node s)		//��������Ӳ�����ȷλ�õ���Ŀ
{
	int w=0;

	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			if (s->a[i][j]!=sg[i][j])
			{
				w++;
			}
		}
	}

	if (s->a[1][1]==sg[1][1])
	{
		w+=1;
	}

	return w-1;
}

bool left_mov(p_node &s)		//�ո�����
{
	int x=s->i_0,y=s->j_0;

	if (y==0)
	{
		return false;
	}

	int t;
	t=s->a[x][y];
	s->a[x][y]=s->a[x][y-1];
	s->a[x][y-1]=t;

	--s->j_0;

	return true;
}

bool right_mov(p_node &s)	//�ո�����
{
	int x=s->i_0,y=s->j_0;

	if (y==2)
	{
		return false;
	}

	int t;
	t=s->a[x][y];
	s->a[x][y]=s->a[x][y+1];
	s->a[x][y+1]=t;

	++s->j_0;

	return true;
}

bool up_mov(p_node &s)	//�ո�����
{
	int x=s->i_0,y=s->j_0;

	if (x==0)
	{
		return false;
	}

	int t;
	t=s->a[x][y];
	s->a[x][y]=s->a[x-1][y];
	s->a[x-1][y]=t;

	--s->i_0;

	return true;
}

bool down_mov(p_node &s)	//�ո�����
{
	int x=s->i_0,y=s->j_0;

	if (x==2)
	{
		return false;
	}

	int t;
	t=s->a[x][y];
	s->a[x][y]=s->a[x+1][y];
	s->a[x+1][y]=t;

	++s->i_0;

	return true;
}

bool is_equal(p_node s1,p_node s2)	//�ж����ڵ��Ƿ����
{
	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			if (s1->a[i][j]!=s2->a[i][j])
			{
				return false;
			}
		}
	}

	return true;
}

void copy_node(p_node s1,p_node &s2)	//�����µĽ�㣨��s2��ֵ��s1��
{

	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			s1->a[i][j]=s2->a[i][j];
		}
	}

	s1->i_0=s2->i_0;
	s1->j_0=s2->j_0;

	s1->d=s2->d;
	s1->w=s2->w;
	s1->f=s2->f;
	s1->father=s2->father;

}

void add_list(p_list &l,p_node s)	//�����㵽OPEN���л�CLOSE����
{

	l->a[l->length++]=s;

}

void delete_list(p_list &l)		//��OPEN���CLOSE��ɾ�����
{
	for (int i=0;i<l->length;i++)
	{
		l->a[i]=l->a[i+1];

	}
	l->length--;
}

bool search_list(p_list &l,p_node s)//�Ա���в��ң��ɹ�����true
{
	for(int i=0;i<l->length;i++)
	{
		if(is_equal(l->a[i],s))
			return true;
	}

	return false;
}

void move(p_node s)//�ƶ����ڵ㲢����δ̽�����У���չ��㣩
{

	p_node p1=(p_node) malloc(sizeof(node));
	p_node p2=(p_node) malloc(sizeof(node));
	p_node p3=(p_node) malloc(sizeof(node));
	p_node p4=(p_node) malloc(sizeof(node));


	copy_node(p1,s);
	copy_node(p2,s);
	copy_node(p3,s);
	copy_node(p4,s);

	p1->father=s;
	p2->father=s;
	p3->father=s;
	p4->father=s;


	//����ܹ��ƶ�����CLOSED���в����ڣ������OPEN����

	if(left_mov(p1) && !is_equal(p1,p1->father) && !search_list(CLOSED,p1) && !search_list(OPEN,p1))
	{
		add_list(OPEN,p1);

		p1->d+=1;
		p1->w=w(p1);
		p1->f=f(p1);
	}
	else
	{
		free(p1);
	}

	if(right_mov(p2) && !is_equal(p2,p2->father) && !search_list(CLOSED,p2) && !search_list(OPEN,p2))
	{
		add_list(OPEN,p2);

		p2->d+=1;
		p2->w=w(p2);
		p2->f=f(p2);
	}
	else
	{
		free(p2);
	}

	if(up_mov(p3) && !is_equal(p3,p3->father) && !search_list(CLOSED,p3) && !search_list(OPEN,p3))
	{
		add_list(OPEN,p3);

		p3->d+=1;
		p3->w=w(p3);
		p3->f=f(p3);
	}
	else
	{
		free(p3);
	}

	if(down_mov(p4) && !is_equal(p4,p4->father) && !search_list(CLOSED,p4) && !search_list(OPEN,p4))
	{
		add_list(OPEN,p4);

		p4->d+=1;
		p4->w=w(p4);
		p4->f=f(p4);
	}
	else
	{
		free(p4);
	}

}

void sort_list(p_list &l)	//��OPEN��������򣬲��뷨���򣨰�f��С����
{
	p_node t=(p_node) malloc (sizeof(node));
    int j;
	for(int i=1;i<l->length;i++)
	{
		if(l->a[i]->f < l->a[i-1]->f)
		{
			copy_node(t,l->a[i]);

			for(j=i;j>0;j--)
			{
				copy_node(l->a[j],l->a[j-1]);
			}
			copy_node(l->a[j],t);
		}
	}
}

void list_reverse(p_node &p)		//����������
{
	p_node p_pre,p_suc;

	p_pre=NULL;
	p_suc=p->father;

	while(p)
	{
		p->father=p_pre;
		p_pre=p;
		if(p_suc == NULL)
		{
			break;
		}
		p=p_suc;
		p_suc=p_suc->father;
	}
}

void init_node()	//��ʼ��
{
	//---------------------------------------��ʼ����ʼ���

	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			s_0->a[i][j]=s0[i][j];

			if(s_0->a[i][j] == 0)
			{
				s_0->i_0=i;
				s_0->j_0=j;
			}
		}
	}

	s_0->d=0;
	s_0->father=NULL;
	s_0->w=w(s_0);
	s_0->f=f(s_0);

	//---------------------------------------��ʼ��Ŀ����

	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			s_g->a[i][j]=sg[i][j];

			if(s_0->a[i][j] == 0)
			{
				s_g->i_0=i;
				s_g->j_0=j;
			}
		}
	}

	s_g->d=0;
	s_g->w=w(s_g);
	s_g->f=f(s_g);

	OPEN->length=0;
	CLOSED->length=0;

	add_list(OPEN,s_0);	//��ʼ������OPEN����

	printf("��ʼ���Ϊ��\n");
	out_node(s_0);

	printf("Ŀ����Ϊ��\n");
	out_node(s_g);
}
