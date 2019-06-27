/*
八数码问题:
编号为1~8的8个正方形滑块被摆成3行3列（有一个格子空留），如图所示。每次可以把与空格相邻的滑块（有公共边才算相邻）移到空格中，而它原来的位置就称为了
新的空格。给定初始局面和目标局面（用0表示空格格），你的任务是计算出最少的移动步数。如果无法达到目标局面，则输-1.

2	6	4     8	 1	5
1	3	7	  7	 3	6
	5	8     4     2
思路：
1 用广度优先搜索，难道得用9个位置剪枝才能达到限定条件?,初始状态和结束状态难道都是一群，而不是能用一个结构体表示，用二维数组表示。
2 八数码问题时图上的最短路径问题，每个状态就是9个各自中的滑块编号（从上到下，从左到右把他们放到一个包含9个元素的数组中）
*/

/*
关键:
typedef int State[9];
State s[100];
int memcmp(void* buf1,void* buf2,size_t count);//比较buf1与buf2的前count个字符,0表示相等
void* memcpy(void* to,const void* from,size_t count);//从to中拷贝前count个字符到to中
//typedef int State[9];//
//State s[100];
//s的素具类型是长度为100的数组，数组元素s[i]的数据类型是State是长度为10的数组，等同于定义了一个二维数组s[100]=iArr[100][9],数组元素师int
//int iarr[100][10]，arr的数据类型是长度为100的数组，数组元素师arr[i],arr[i]的数据类型是长度为10的数组，数组元素师int
*/

/*
关键:
1 typedef int State[9];//s的素具类型是长度为100的数组，数组元素s[i]的数据类型是State是长度为10的数组，等同于定义了一个二维数组s[100]=iArr[100][9],数组元素师int
                     //int iarr[100][10]，arr的数据类型是长度为100的数组，数组元素师arr[i],arr[i]的数据类型是长度为10的数组，数组元素师int
State st[MAXSIZE];//状态数一定要多定义，否则一不小心就超了
2 int iVis[362880],fact[9];//9!=362880，8!=40320,9*8!=9!共有这么多排序，然后我们寻找，我们初始化fact，这是用作编码与解码，确保一一映射
3 bool isInsert(int n)//去重，采用编码与解码机制，确保一个9维状态只能映射到一个数字，并且映射的数字最大值不能超过9!
4 if(st[n][j] < st[n][i])//统计每个排列中，后面小于前面排列的数字个数
5 init();//这里进行判重，对于树不需要判断重复。但是对于图需要判断
6 		if(memcmp(stEnd,state,sizeof(state)) == 0)//判断是否找到的工作要放在开头
		{
			return iFront;
		}
		模拟队列的方法：设置一个数组，front起初比rear小1，然后先给定初始值，弹出front,生成的新状态加在末尾
7 break;//凡是寻找类的问题，一旦找到，必须用break跳出
8 			if(iNewX >= 0 && iNewX < 3 && iNewY >= 0 && iNewY < 3)//剪枝
			{
				State& newState = st[iRear];//这里应该从队尾提前将原来老的状态拷贝给新的状态，再将新状态中需要修改0元素的地方进行修改,需要用引用，为修改做准备
				memcpy(&newState,state,sizeof(state));
				newState[iNewZ] = state[iZ];//新矩阵0元素的位置上放0元素
				newState[iZ] = state[iNewZ];//新矩阵原来放0元素的位置上现在放上新生成的0元素的坐标,这里必须用原来被交换元素的值替换
				iDist[iRear] = iDist[iFront] + 1;//更新移动的步数
			}
9 	memset(iVis,0,sizeof(iVis));//初始化访问内存块,就是这句话没加导致错误的，凡是做宽度优先搜索，必定要先初始化访问数组
10 			if(isInsert(iRear))//修改队尾指针
			{
				iRear++;
			}
		}
		iFront++;//不管是否成功，修改队头
11 int iRes = bfs();//返回的是front的值，但不是移动次数，移动次数得用dist来计算，因为这里是宽度优先搜索，如果用front的值，那么中间尝试的节点也算了
12 int memcmp(void* buf1,void* buf2,size_t count);//比较buf1与buf2的前count个字符,0表示相等
void* memcpy(void* to,const void* from,size_t count);//从to中拷贝前count个字符到to中
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <iostream>
#define MAXSIZE 1000000

using namespace std;

typedef int State[9];//s的数据类型是长度为100的数组，数组元素s[i]的数据类型是State是长度为10的数组，等同于定义了一个二维数组s[100]=iArr[100][9],数组元素师int
                     //int iarr[100][10]，arr的数据类型是长度为100的数组，数组元素师arr[i],arr[i]的数据类型是长度为10的数组，数组元素师int
State st[MAXSIZE];//状态数一定要多定义，否则一不小心就超了
State stEnd;
int iDist[MAXSIZE];

int go[][2] =
{
	{-1,0},
	{1,0},
	{0,-1},
	{0,1}
};



int iVis[362880],fact[9];//9!=362880，8!=40320,9*8!=9!共有这么多排序，然后我们寻找，我们初始化fact
void init()
{
	fact[0] = 1;
	for(int i = 1 ; i < 9; i++)
	{
		fact[i] = fact[i-1]*i;
	}
}


//bool isInsert(State state)
bool isInsert(int n)//去重，采用编码与解码机制，确保一个9维状态只能映射到一个数字，并且映射的数字最大值不能超过9!
{
	int iCode = 0;//编码值
	for(int i = 0 ; i < 9 ; i++)
	{
		int iCnt = 0;
		for(int j = i+1; j < 9;j++)
		{
			if(st[n][j] < st[n][i])//统计每个排列中，后面小于前面排列的数字个数
			{
				iCnt++;
			}
		}
		iCode += fact[8-i]*iCnt;
	}
	if(iVis[iCode])//如果已经访问过
	{
		return false;
	}
	else
	{
		iVis[iCode] = 1;
		return true;//同时完成赋值和返回值操作
	}
}

int bfs()
{
	int iRear = 2,iFront = 1;
	init();//这里进行判重，对于树不需要判断重复。但是对于图需要判断
	while(iFront < iRear)
	{
		State& state = st[iFront];
		if(memcmp(stEnd,state,sizeof(state)) == 0)//判断是否找到的工作要放在开头
		{
			return iFront;
		}

		int iZ,iX,iY;
		for(int i = 0 ; i < 9; i++)//确定0所在的位置
		{
			if(!state[i])
			{
				iZ = i;
				iX = iZ / 3;
				iY = iZ % 3;
				break;//凡是寻找类的问题，一旦找到，必须用break跳出
			}
		}
		//生成下一步位置
		int iNewZ,iNewX,iNewY;
		for(int i = 0; i < 4; i++)
		{
			iNewX = go[i][0] + iX;
			iNewY = go[i][1] + iY;
			iNewZ = iNewX*3 + iNewY;//确定0的新位置
			if(iNewX >= 0 && iNewX < 3 && iNewY >= 0 && iNewY < 3)//剪枝
			{
				State& newState = st[iRear];//这里应该从队尾提前将原来老的状态拷贝给新的状态，再将新状态中需要修改0元素的地方进行修改,需要用引用，为修改做准备
				memcpy(&newState,&state,sizeof(state));
				newState[iNewZ] = state[iZ];//新矩阵0元素的位置上放0元素
				newState[iZ] = state[iNewZ];//新矩阵原来放0元素的位置上现在放上新生成的0元素的坐标,这里必须用原来被交换元素的值替换
				iDist[iRear] = iDist[iFront] + 1;//更新移动的步数
			}
			if(isInsert(iRear))//修改队尾指针
			{
				iRear++;
			}
		}
		iFront++;//不管是否成功，修改队头
	}
	return -1;
}

void process()
{
    cout<<"输入初始队列："<<endl;
	//初始化队头和队尾元素
	for(int i = 0 ; i < 9;i++)
	{
		cin>>st[1][i];
	}
	cout<<"输入目标队列："<<endl;
	for(int j = 0 ; j < 9; j++)
	{
		cin>>stEnd[j];
	}
	cout<<endl;
	iDist[1] = 0;//设置第一步移动的距离为0
	memset(iVis,0,sizeof(iVis));//初始化访问内存块,就是这句话没加导致错误的
}

int main(int argc,char* argv[])
{
	process();
	int iRes = bfs();//返回的是front的值，但不是移动次数，移动次数得用dist来计算，因为这里是宽度优先搜索，如果用front的值，那么中间尝试的节点也算了
	if(iRes > 0)
	{
	    cout<<"移动次数为：";
		cout<<iDist[iRes]<<endl;
	}
	else
	{
		cout<<"error!"<<endl;
	}
	system("pause");
	return 0;
}


