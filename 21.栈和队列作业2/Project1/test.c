#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//6.假设以带头结点的循环链表表示队列，并且只设一个指针指向队尾元素结点（注意：不设头指针），试编写相应的置空队列、判断队列是否为空，入队和出队等算法
typedef struct QueueNode
{
	int a;                  //定义结点类型
	struct QueueNode* next;
}QueueNode,*QueuePtr;
typedef struct QueueLink
{
	QueuePtr rear;   //只设置一个尾指针,则rear->next就是头结点
}QueueLink;
//初始化
void InitQueue(QueueLink* Q)
{
	(*Q).rear = (QueueNode*)malloc(sizeof(QueueNode));
	(*Q).rear->next = (*Q).rear;
}
//入队
void EnQueue(QueueLink* Q,int a)
{
	QueueNode* p = (QueueNode*)malloc(sizeof(QueueNode));
	p->a = a;
	p->next = (*Q).rear->next;
	(*Q).rear->next = p;
	(*Q).rear = p;
}
//出队
int OutQueue(QueueLink* Q)
{
	if (Q->rear->next == Q->rear)
	{
		printf("队列为空 ");
		return -1;
	}
	QueueNode* p = Q ->rear->next->next;
	int e = p->a;
	Q->rear->next->next = p->next;
	if (p == (*Q).rear)
		(*Q).rear = Q->rear->next;
	free(p), p = NULL;
	return e;
}
//判断队列是否为空
int IsEmpty(QueueLink* Q)
{
	if (Q->rear->next == Q->rear)
		return 1;
	else
		return 0;
}
//置空队列
void ClearQueue(QueueLink* Q)
{
	if(Q->rear->next==Q->rear)
	{
		printf("队列已经为空\n");
		return;
	}
	while (Q->rear->next != Q->rear)
	{
		QueueNode* p = Q->rear->next->next;
		Q->rear->next->next = p->next;
		if (p == (*Q).rear)
			(*Q).rear = Q->rear->next;
		free(p), p = NULL;
	}
}
//测试代码
//int main()
//{
//	QueueLink Q;
//	InitQueue(&Q);
//	EnQueue(&Q, 1);
//	EnQueue(&Q, 2);
//	EnQueue(&Q, 3);
//	EnQueue(&Q, 4);
//	EnQueue(&Q, 5);
//	OutQueue(&Q);
//	OutQueue(&Q);
//	ClearQueue(&Q);
//	return 0;
//}


//7.假设以数组Q[m]存放循环队列中的元素，同时设置一个标志tag，以tag==0和tag==1来区别在队头指针（front）和队尾指针（rear）相等时。
//  队列状态为“空”还是“满”。试编写与此结构相应的插入(enqueue)和删除(dequeue)算法
#define M 5
typedef struct SqQueue
{
	int* base;
	int front;           //定义一个顺序队列
	int rear;
	int tag;    //这里不用少用一个空间来区别循环队列满没满了，这里使用标志tag来区分循环队列空还是满
}SqQueue;
void InitSqQueue(SqQueue* Q)
{
	Q->base = (int*)malloc(sizeof(int) * M);   //这里设数组Q[m]的大小为10
	Q->front = Q->rear = 0;
	Q->tag = 0;
}
//插入
void enqueue(SqQueue* Q,int a)
{
	if (Q->tag==1)
	{
		printf("队列满了\n");
		return;
	}
	Q->base[Q->rear] = a;
	Q->rear = (Q->rear + 1) % M;
	if (Q->front == Q->rear)
		Q->tag = 1;
}
//删除
int dequeue(SqQueue* Q)
{
	if (Q->tag==0)
	{
		printf("队列已空\n");
		return;
	}
	int e = Q->base[Q->front];
	Q->front = (Q->front + 1) % M;
	if (Q->front == Q->rear)
		Q->tag = 0;
	return e;
}
//int main()
//{
//	SqQueue Q;
//	InitSqQueue(&Q);
//	enqueue(&Q, 1);
//	enqueue(&Q, 2);
//	enqueue(&Q, 3);
//	enqueue(&Q, 4);
//	enqueue(&Q, 5);
//	dequeue(&Q);
//	dequeue(&Q);
//	dequeue(&Q);
//	dequeue(&Q);
//	dequeue(&Q);
//	return 0;
//}


//8.如果允许在循环队列的两端都可以进行插入和删除操作。要求；
//（1）写出循环队列的类型定义；
//（2）写出“从队尾删除”和“从队头插入”的算法
typedef struct CirQueue
{
	int base[M];
	int front;
	int rear;
}CirQueue;
void InitCirQueue(CirQueue* C)
{
	C->front = C->rear = 0;
}
//队头插入
void En_front(CirQueue* C, int a)
{
	if ((C->front - 1 + M) % M == C->rear)
	{
		printf("队列满了\n");
		return;
	}
	C->front = (C->front - 1 + M) % M;    //队头增加到数组头部后循环到数组尾部继续增加
	C->base[C->front] = a;
}
//队尾删除
int Del_rear(CirQueue* C)
{
	if (C->rear == C->front)
	{
		printf("队列已空\n");
		return;
	}
	C->rear = (C->rear - 1 + M) % M;   //队尾删除到数组头部后循环到数组尾部继续删除
	int e = C->base[C->rear];
	return e;
}

//9.已知Ackermann函数定义如下：
//            n+1                    当m=0时
//Ack(m,n)=   Ack(m-1,1)             当m!=0,n=0时
//            Ack(m-1,Ack(m,n-1))    当m!=0,n!=0时
//（1）写出计算Ack(m,n)的递归算法，并根据此算法给出Ack(2,1)的计算过程。
//（2）写出计算Ack(m,n)的非递归算法
int Ack(int m, int n)
{  //递归算法
	if (m == 0)
		return n + 1;
	else if (n == 0 && m != 0)
		return Ack(m - 1, 1);
	else
		return Ack(m - 1, Ack(m, n - 1));
}
//非递归算法
//非递归算法有点复杂，要自己建立栈将递归转化为非递归
//利用栈转化递归步骤如下：
//1.设置一个工作栈存放递归工作记录（实参，返回地址及局部变量等，此题中表现为m,n，Ack函数的返回值，是否计算出Ack函数的值等）
//2.进入非递归调用入口，即被调用程序开始处（此处表现为m=0时，Ack(m,n)=n+1）
//3.进入递归调用入口，程序执行时每一次递归都计算Ack函数的信息（实参，返回值，返回地址，局部变量），并将其入栈
//4.递归结束条件满足，将到达递归出口的给定常数作为当前的函数值
//5.返回处理：栈不空的情况下，反复退出栈顶记录，根据记录中的信息进行计算函数值操作，直到栈空为止
//详情可参考https://blog.csdn.net/sanqima/article/details/48831679

//int main()
//{
//	printf("%d",Ack(2, 1));
//	return 0;
//}


//10.已知f为单链表的头指针，链表中存储的都是整型数据，试写出实现下列运算的递归算法：
//（1）求链表中的最大整数
//（2）求链表中的结点个数
//（3）求所有整数的平均值
typedef struct StackNode
{
	int a;
	struct StackNode* next;
}StackNode,*StackLink;
void InitStack(StackLink* S)
{
	*S = (StackNode*)malloc(sizeof(StackNode));
	(*S)->next = NULL;
}
//求链表中的最大整数
int Findmax(StackLink S)
{
	StackNode* f = S->next;
	if (!f)
	{
		printf("链表为空\n");
		return;
	}
	else if (!f->next)    //如果链表只有一个元素，则返回那一个元素
		return f->a;
	else
	{
		int max = Findmax(f);   //获取后续结点中的最大值
		return f->a>max ? f->a : max;    //将此结点的值和后续结点的最大值比较，返回大的那个
	}
}
//求链表的结点个数
int Findnode(StackLink S)
{
	StackNode* f = S;
	if (!f->next)
		return 1;
	else
		return 1+Findnode(f->next);
}
//求所有整数的平均值
float average(StackLink S,int n)   //计算头结点后的n个结点的平均值
{
	StackNode* f = S->next;   //跳过头结点指向首元结点
	if (!f)
	{
		printf("链表为空");
		return -1;
	}
	else if (!f->next)    //如果只有一个结点，返回该结点的值
		return f->a;
	else
	{
		//要计算头结点后n个结点的平均值，就要计算首元结点后n-1个结点的平均值
		float ave = average(f, n - 1);    //计算f结点后n-1个结点的平均值
		return (ave * (n - 1) + f->a) / n;   //n-1个结点的平均值加上首元结点的值除以n得到平均值
	}
}
//插入链表
void Add(StackLink* S)
{
	StackNode* r = *S;
	for (int i = 0; i < 5; i++)
	{
		StackNode* p = (StackNode*)malloc(sizeof(StackNode));
		printf("输入数据：");
		scanf("%d", &p->a);
		p->next = r->next;
		r->next = p;
		r = p;
	}
}
//测试代码
int main()
{
	StackLink S;
	InitStack(&S);
	Add(&S);
	printf("%d\n",Findmax(S));
	printf("%d\n",Findnode(S));
	printf("%f\n", average(S,5));
	return 0;
}