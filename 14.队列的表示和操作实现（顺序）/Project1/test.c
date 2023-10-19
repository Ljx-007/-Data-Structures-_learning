#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//队列：只能在表的一端进行插入运算，在表的另一端删除运算的线性表（头删尾插）
//队列的存储方式也有顺序存储和链式存储

//定义一个队列：顺序存储
#define MAXSIZE 5   //定义队列最大长度
typedef struct Que_Sq
{
	int* base;   //base为队列的指针，指向这个队列  ，这里元素类型为int
	int front;  //front和rear为头指针和尾指针，这里代表的是下标，不是真正的指针
	int rear;  //rear指针永远指向队尾元素的下一个位置
}SqQue;

//队列要求在队头删除元素，队尾添加元素，我们使用数组下标front和rear来指向队头和队尾
//当front=rear时，说明队列为空
//如果队列不为空，队尾增加一个元素，则rear++，队头删除一个元素，front++（头指针指向下一个元素，下一个元素为队头）
//在这样不断头删尾增的情况下，front指针越来越后，rear指针超过数组的尾部造成越界访问。
//出现队列中有空位置（front前），但无法再存放元素的情况，且rear指针越界访问，这种溢出访问称为“假溢出”。

//为解决“假溢出”的问题，我们把队列首尾相连，形成一个循环链表，指针到了数组尾部会重新回到数组头部（注意：数组头部不是队列头部）
//假设队列有5个位置，最开始指针rear等于0，随着元素的增加rear等于4，此时rear已经指向数组尾部，如何让rear回到数组头部呢？（让rear重新等于0）
//我们采用取模（取余数）的方式，rear=（rear+1）% MAXSIZE , MAXSIZE为队列最大长度，这里设为5
//当rear=4，即数组尾部时，rear=（rear+1）% 5 =0 ，此时rear重新等于0，达到我们想要的效果

//循环队列实现后，又会出现新的问题，即当front=rear时，队列有可能时满的也有可能是空的
//如何判断队列满了或者空了呢？我们有以下三种方法：
//1.设立一个标志位以区别队列是空还是满
//2.设立计数器，来判断队列是空还是满
//3.少用一个元素空间，少用一个元素空间后，原本能存放5个元素的队列现在只能放4个，则尾指针rear指向的队列末尾不能存放元素
//  那么少用一个元素后，判断队列满的条件即为（rear+1）% MAXSIZE==front ，即rear指向末尾后再+1取模回到队列头部与front相等，则队列满

//队列的初始化
void InitQueue(SqQue* Q)
{
	Q->base = (int*)malloc(sizeof(int) * MAXSIZE);
	if (!(Q->base))
	{
		perror("malloc error");
		return;
	}
	Q->front = Q->rear = 0;
}

//求队列长度
int LenQueue(SqQue* Q)
{
	//在顺序存储结构中，尾指针-头指针就是中间的元素个数
	//但在循环结构中，尾指针可能在头指针前面，所以不能用尾指针 - 头指针来表示元素个数
	//这里方法为 （尾指针-头指针+队列最大长度）% 队列最大长度
	//这样就可以算出来循环结构中队列的长度了
	return (Q->rear - Q->front + MAXSIZE) % MAXSIZE;
}

//队列入队
void EnQueue(SqQue* Q)
{
	//先判断队列是否满了
	if ((Q->rear + 1) % MAXSIZE == Q->front)    //前面讲过采用少用一个元素空间的方法判断队满，则rear后移一位后等于front
	{
		printf("队列满了\n");
		return;
	}
	printf("输入要入队的元素(int)：");
	scanf("%d", &(Q->base[Q->rear]));
	Q->rear = (Q->rear + 1) % MAXSIZE;  //rear尾指针下标采用取模的方式后移一位
}

//队列出队
int DelQue(SqQue* Q)   //返回出队的元素
{
	//先判断队列是否为空
	if (Q->rear == Q->front)
	{
		printf("队列为空\n");
		return -1;
	}
	int e = Q->base[Q->front];
	Q->front = (Q->front + 1) % MAXSIZE;   //头指针后移一位
	return e;
}

//取队头元素
int GetTop(SqQue Q)
{
	if (Q.front != Q.rear) //如果队列不为空
		return Q.base[Q.front];
}

int main()
{
	return 0;
}