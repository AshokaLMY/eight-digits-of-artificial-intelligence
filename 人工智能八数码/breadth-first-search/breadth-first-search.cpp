/*
����������:
���Ϊ1~8��8�������λ��鱻�ڳ�3��3�У���һ�����ӿ���������ͼ��ʾ��ÿ�ο��԰���ո����ڵĻ��飨�й����߲������ڣ��Ƶ��ո��У�����ԭ����λ�þͳ�Ϊ��
�µĿո񡣸�����ʼ�����Ŀ����棨��0��ʾ�ո�񣩣���������Ǽ�������ٵ��ƶ�����������޷��ﵽĿ����棬����-1.

2	6	4     8	 1	5
1	3	7	  7	 3	6
	5	8     4     2
˼·��
1 �ù�������������ѵ�����9��λ�ü�֦���ܴﵽ�޶�����?,��ʼ״̬�ͽ���״̬�ѵ�����һȺ������������һ���ṹ���ʾ���ö�ά�����ʾ��
2 ����������ʱͼ�ϵ����·�����⣬ÿ��״̬����9�������еĻ����ţ����ϵ��£������Ұ����Ƿŵ�һ������9��Ԫ�ص������У�
*/

/*
�ؼ�:
typedef int State[9];
State s[100];
int memcmp(void* buf1,void* buf2,size_t count);//�Ƚ�buf1��buf2��ǰcount���ַ�,0��ʾ���
void* memcpy(void* to,const void* from,size_t count);//��to�п���ǰcount���ַ���to��
//typedef int State[9];//
//State s[100];
//s���ؾ������ǳ���Ϊ100�����飬����Ԫ��s[i]������������State�ǳ���Ϊ10�����飬��ͬ�ڶ�����һ����ά����s[100]=iArr[100][9],����Ԫ��ʦint
//int iarr[100][10]��arr�����������ǳ���Ϊ100�����飬����Ԫ��ʦarr[i],arr[i]�����������ǳ���Ϊ10�����飬����Ԫ��ʦint
*/

/*
�ؼ�:
1 typedef int State[9];//s���ؾ������ǳ���Ϊ100�����飬����Ԫ��s[i]������������State�ǳ���Ϊ10�����飬��ͬ�ڶ�����һ����ά����s[100]=iArr[100][9],����Ԫ��ʦint
                     //int iarr[100][10]��arr�����������ǳ���Ϊ100�����飬����Ԫ��ʦarr[i],arr[i]�����������ǳ���Ϊ10�����飬����Ԫ��ʦint
State st[MAXSIZE];//״̬��һ��Ҫ�ඨ�壬����һ��С�ľͳ���
2 int iVis[362880],fact[9];//9!=362880��8!=40320,9*8!=9!������ô������Ȼ������Ѱ�ң����ǳ�ʼ��fact������������������룬ȷ��һһӳ��
3 bool isInsert(int n)//ȥ�أ����ñ����������ƣ�ȷ��һ��9ά״ֻ̬��ӳ�䵽һ�����֣�����ӳ����������ֵ���ܳ���9!
4 if(st[n][j] < st[n][i])//ͳ��ÿ�������У�����С��ǰ�����е����ָ���
5 init();//����������أ�����������Ҫ�ж��ظ������Ƕ���ͼ��Ҫ�ж�
6 		if(memcmp(stEnd,state,sizeof(state)) == 0)//�ж��Ƿ��ҵ��Ĺ���Ҫ���ڿ�ͷ
		{
			return iFront;
		}
		ģ����еķ���������һ�����飬front�����rearС1��Ȼ���ȸ�����ʼֵ������front,���ɵ���״̬����ĩβ
7 break;//����Ѱ��������⣬һ���ҵ���������break����
8 			if(iNewX >= 0 && iNewX < 3 && iNewY >= 0 && iNewY < 3)//��֦
			{
				State& newState = st[iRear];//����Ӧ�ôӶ�β��ǰ��ԭ���ϵ�״̬�������µ�״̬���ٽ���״̬����Ҫ�޸�0Ԫ�صĵط������޸�,��Ҫ�����ã�Ϊ�޸���׼��
				memcpy(&newState,state,sizeof(state));
				newState[iNewZ] = state[iZ];//�¾���0Ԫ�ص�λ���Ϸ�0Ԫ��
				newState[iZ] = state[iNewZ];//�¾���ԭ����0Ԫ�ص�λ�������ڷ��������ɵ�0Ԫ�ص�����,���������ԭ��������Ԫ�ص�ֵ�滻
				iDist[iRear] = iDist[iFront] + 1;//�����ƶ��Ĳ���
			}
9 	memset(iVis,0,sizeof(iVis));//��ʼ�������ڴ��,������仰û�ӵ��´���ģ���������������������ض�Ҫ�ȳ�ʼ����������
10 			if(isInsert(iRear))//�޸Ķ�βָ��
			{
				iRear++;
			}
		}
		iFront++;//�����Ƿ�ɹ����޸Ķ�ͷ
11 int iRes = bfs();//���ص���front��ֵ���������ƶ��������ƶ���������dist�����㣬��Ϊ�����ǿ�����������������front��ֵ����ô�м䳢�ԵĽڵ�Ҳ����
12 int memcmp(void* buf1,void* buf2,size_t count);//�Ƚ�buf1��buf2��ǰcount���ַ�,0��ʾ���
void* memcpy(void* to,const void* from,size_t count);//��to�п���ǰcount���ַ���to��
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <iostream>
#define MAXSIZE 1000000

using namespace std;

typedef int State[9];//s�����������ǳ���Ϊ100�����飬����Ԫ��s[i]������������State�ǳ���Ϊ10�����飬��ͬ�ڶ�����һ����ά����s[100]=iArr[100][9],����Ԫ��ʦint
                     //int iarr[100][10]��arr�����������ǳ���Ϊ100�����飬����Ԫ��ʦarr[i],arr[i]�����������ǳ���Ϊ10�����飬����Ԫ��ʦint
State st[MAXSIZE];//״̬��һ��Ҫ�ඨ�壬����һ��С�ľͳ���
State stEnd;
int iDist[MAXSIZE];

int go[][2] =
{
	{-1,0},
	{1,0},
	{0,-1},
	{0,1}
};



int iVis[362880],fact[9];//9!=362880��8!=40320,9*8!=9!������ô������Ȼ������Ѱ�ң����ǳ�ʼ��fact
void init()
{
	fact[0] = 1;
	for(int i = 1 ; i < 9; i++)
	{
		fact[i] = fact[i-1]*i;
	}
}


//bool isInsert(State state)
bool isInsert(int n)//ȥ�أ����ñ����������ƣ�ȷ��һ��9ά״ֻ̬��ӳ�䵽һ�����֣�����ӳ����������ֵ���ܳ���9!
{
	int iCode = 0;//����ֵ
	for(int i = 0 ; i < 9 ; i++)
	{
		int iCnt = 0;
		for(int j = i+1; j < 9;j++)
		{
			if(st[n][j] < st[n][i])//ͳ��ÿ�������У�����С��ǰ�����е����ָ���
			{
				iCnt++;
			}
		}
		iCode += fact[8-i]*iCnt;
	}
	if(iVis[iCode])//����Ѿ����ʹ�
	{
		return false;
	}
	else
	{
		iVis[iCode] = 1;
		return true;//ͬʱ��ɸ�ֵ�ͷ���ֵ����
	}
}

int bfs()
{
	int iRear = 2,iFront = 1;
	init();//����������أ�����������Ҫ�ж��ظ������Ƕ���ͼ��Ҫ�ж�
	while(iFront < iRear)
	{
		State& state = st[iFront];
		if(memcmp(stEnd,state,sizeof(state)) == 0)//�ж��Ƿ��ҵ��Ĺ���Ҫ���ڿ�ͷ
		{
			return iFront;
		}

		int iZ,iX,iY;
		for(int i = 0 ; i < 9; i++)//ȷ��0���ڵ�λ��
		{
			if(!state[i])
			{
				iZ = i;
				iX = iZ / 3;
				iY = iZ % 3;
				break;//����Ѱ��������⣬һ���ҵ���������break����
			}
		}
		//������һ��λ��
		int iNewZ,iNewX,iNewY;
		for(int i = 0; i < 4; i++)
		{
			iNewX = go[i][0] + iX;
			iNewY = go[i][1] + iY;
			iNewZ = iNewX*3 + iNewY;//ȷ��0����λ��
			if(iNewX >= 0 && iNewX < 3 && iNewY >= 0 && iNewY < 3)//��֦
			{
				State& newState = st[iRear];//����Ӧ�ôӶ�β��ǰ��ԭ���ϵ�״̬�������µ�״̬���ٽ���״̬����Ҫ�޸�0Ԫ�صĵط������޸�,��Ҫ�����ã�Ϊ�޸���׼��
				memcpy(&newState,&state,sizeof(state));
				newState[iNewZ] = state[iZ];//�¾���0Ԫ�ص�λ���Ϸ�0Ԫ��
				newState[iZ] = state[iNewZ];//�¾���ԭ����0Ԫ�ص�λ�������ڷ��������ɵ�0Ԫ�ص�����,���������ԭ��������Ԫ�ص�ֵ�滻
				iDist[iRear] = iDist[iFront] + 1;//�����ƶ��Ĳ���
			}
			if(isInsert(iRear))//�޸Ķ�βָ��
			{
				iRear++;
			}
		}
		iFront++;//�����Ƿ�ɹ����޸Ķ�ͷ
	}
	return -1;
}

void process()
{
    cout<<"�����ʼ���У�"<<endl;
	//��ʼ����ͷ�Ͷ�βԪ��
	for(int i = 0 ; i < 9;i++)
	{
		cin>>st[1][i];
	}
	cout<<"����Ŀ����У�"<<endl;
	for(int j = 0 ; j < 9; j++)
	{
		cin>>stEnd[j];
	}
	cout<<endl;
	iDist[1] = 0;//���õ�һ���ƶ��ľ���Ϊ0
	memset(iVis,0,sizeof(iVis));//��ʼ�������ڴ��,������仰û�ӵ��´����
}

int main(int argc,char* argv[])
{
	process();
	int iRes = bfs();//���ص���front��ֵ���������ƶ��������ƶ���������dist�����㣬��Ϊ�����ǿ�����������������front��ֵ����ô�м䳢�ԵĽڵ�Ҳ����
	if(iRes > 0)
	{
	    cout<<"�ƶ�����Ϊ��";
		cout<<iDist[iRes]<<endl;
	}
	else
	{
		cout<<"error!"<<endl;
	}
	system("pause");
	return 0;
}


