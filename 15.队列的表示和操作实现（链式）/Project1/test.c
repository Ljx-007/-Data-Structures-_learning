#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//如果无法预估队列的长度，则采用链式队列
//为操作方便，给链队增加一个头结点，并令头指针始终指向头结点
typedef struct Qnode
{
	int data;
	struct Qnode* next;
}Qnode,*Qptr;   //Qptr 为结点指针 ptr就是pointer的意思，pointer意思是指针

//在链表中，一般使用一个头指针即可访问链表
//但在链式队列，要遵守头删尾插的原则，需要有头指针和尾指针来进行增删操作
//所以把头指针和尾指针放在一个结构体中，方便操作
typedef struct
{
	Qptr front;  //队头指针
	Qptr rear;   //队尾指针
}LinkQueue;

//链队初始化
void InitQue(LinkQueue* Q)
{
	Q->front = Q->rear = (Qnode*)malloc(sizeof(Qnode));
	Q->front->next = NULL; 
}

//链队销毁
void DestroyQueue(LinkQueue* Q)
{
	while (Q->front)
	{
		Qnode* p = Q->front;        //这里可以不用创建变量p，可以直接使用现成的rear指针
		Q->front = Q->front->next;   
		free(p), p = NULL;
	}
}

//链队的入队
void EnQueue(LinkQueue* Q)
{
	int n;
	printf("请输入要入队的元素个数：");
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		Qnode* p = (Qnode*)malloc(sizeof(Qnode));
		if (!p)
		{
			perror("malloc error");
			return;
		}
		printf("请输入要入队的元素(int):");
		scanf("%d", &(p->data));
		p->next = Q->rear->next;
		Q->rear->next = p;   //尾插法将元素插入队尾
		Q->rear = p;
	}
}

//链队的删除
int DelQueue(LinkQueue* Q)  //返回删除的元素
{
	if (Q->front == Q->rear)
	{
		printf("链队为空\n");
		return -1;
	}
	else
	{
		Qnode* p = Q->front->next;
		Q->front->next = p->next;
		//如果删除的是最后一个结点的话，尾结点指针要改变，与头指针相同
		if (p == Q->rear)
			Q->rear = Q->front;
		int e = p->data;
		free(p), p = NULL;
		return e;
	}
}

//取链队队头元素
int GetTop(LinkQueue* Q)
{
	if (Q->front != Q->rear)
		return Q->front->next->data;
	else
		return -1;
}
int main()
{
	LinkQueue Q;
	InitQue(&Q);
	EnQueue(&Q);
	return 0;
}