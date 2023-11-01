#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//二叉树的存储结构

//顺序存储：按满二叉树的结点层次编号，依次存放二叉树中的数据元素
//          如果是一般二叉树，则给结点不存在的编号下存放0，表示不存在此结点
#define MAXSIZE 100    //规定二叉树的最大结点数
//type SqBitree[MAXSIZE];   创建一个二叉树数组即可，数据按结点编号存储
//缺点：
//1、如果二叉树空结点太多，顺序存储会造成空间浪费，例如k层的二叉树只有k个结点，即每一层就一个结点，但还要创建2^k-1个空间，当k较大时，会浪费很多的内存空间
//2、其次如果要进行增加或者减少，操作太麻烦

//顺序存储适合存满二叉树或者完全二叉树

//链式存储：
//由二叉树的定义可知，二叉树的结点由一个数据元素和分别指向其左右子树的两个分支构成
// 所以定义二叉树的链式存储结构时，链表中的一个结点至少包含三个域：数据域，左指针域，右指针域（二叉链表）
//  有时为了便于找到结点的双亲，还可在结点结构中增加一个指向其双亲结点的指针域（三叉链表）
typedef struct Binode
{  //定义二叉链表
	char data;   //设这里的数据元素为char型
	struct Binode* lchild, *rchild;  //左右孩子指针
}Binode,*Bitree;
//  有n个结点就有n+1个空指针域
//typedef struct Binode
//{  //定义三叉链表
//	int data;   //设这里的数据元素为int型
//	struct Binode* lchild, * rchild,*parent;  //左右孩子指针和指向双亲的指针
//}Binode, * Bitree;


//遍历二叉树
// 二叉树有三个结构：根（D），左子树（L），右子树（R）
//  遍历时有六种顺序: DLR,LDR,LRD,DRL,RDL,RLD
//如果规定遍历从左到右，则遍历二叉树有三种情况：DLR、LDR、LRD
//DLR：先（根）序遍历   LDR：中（根）序遍历   LRD：后（根）序遍历   
//这里的先中后情况指的是：先访问根、中间访问根、后访问根

//先序遍历二叉树（递归算法）
void visit(Bitree T)
{
	printf("%c", T->data);
}
void PreOrderTraverse(Bitree T)    //先序遍历，T为根结点
{
	if (!T)   //如果T为空结点，则退出
		return; 
	else
	{
		visit(T); //这里做结点T的访问，具体访问内容可以自己封装visit函数决定，例如打印结点的数据域的数据
		PreOrderTraverse(T->lchild);  //用递归先访问左子树
		PreOrderTraverse(T->rchild);  //再访问右子树
	}
}

//中序遍历（递归算法）
void InOrderTraverse(Bitree T)
{
	if (!T)
		return;
	else
	{
		InOrderTraverse(T->lchild);    //先访问左子树
		visit(T);                   //再访问根节点
		InOrderTraverse(T->rchild);  //最后再访问右子树
	}
}

//后序遍历（递归算法）
void PostOrderTraverse(Bitree T)
{
	if (!T)
		return;
	else
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);     //先访问左子树，再访问右子树，最后访问根节点
		visit(T);
	}
}

//如果去掉visit访问结点语句，则三种遍历算法是一样的。或者说三种算法的访问路径相同，只是访问结点的时机不同。
// 在这条访问路径下，都三次经过了同一个结点，如果第一次经过就访问结点，则是先序访问；如果是第二次经过才访问，就是中序；第三次则是后序
//三种算法每个结点都只访问了一次，所以时间复杂度为O(n)
//如果经过了结点而不访问，则系统要用栈来存储该结点，最坏的情况下就是经过的每一个结点都先不访问，所以栈占用的最大辅助空间为n，空间复杂度为O(n)

//中序遍历的非递归算法
//由之前的学习中可知，递归算法转化为非递归算法，需要我们自己创建一个栈来代替系统的栈
typedef struct StackNode
{                           //链栈不需要头结点
	Binode* T;
	struct StackNode* next;
}StackNode,*StackLink;
StackNode* InitStack()
{
	StackLink S = (StackLink)malloc(sizeof(StackNode));
	S= NULL;   //创建栈顶指针，创建链栈时链栈为空，所以S为空指针
	return S;
}
void Push(StackLink* S,Bitree T)
{
	StackNode* p = (StackNode*)malloc(sizeof(StackNode));
	if (p)
	{
		p->T = T;
		p->next = *S;
		*S = p;
	}
}
Bitree Pop(StackLink* S)
{
	Bitree e = (*S)->T;
	*S = (*S)->next;
	return e;
}
int StackEmpty(StackLink S)
{
	if (!S)
		return;
	else
		return 0;
}
Bitree GetTop(StackLink S)
{
	if (S)
	{
		Bitree e = S->T;
		return e;
	}
}
//先序遍历非递归算法
void PreOrderT(Bitree T)
{
	StackLink S = InitStack();
	Binode* p = T;    //创建指针变量p来遍历二叉树T
	while (p || !StackEmpty(S))    //二叉树没有结点可遍历了则停止循环
	{
		if (p)     //p非空时
		{
			Binode* q = p;  //创建一个指针指向根结点
			printf("%c ", q->data);   //先序遍历先访问根结点
			Push(&S, q);           //再把这个根结点进栈，接着遍历左子树
			           //将根结点进栈的目的是如果左子树为空，可以重新回到这个根结点访问右子树
			p = p->lchild;
		}
		else  //如果p为空
		{
			p = Pop(&S);   //弹出p的双亲，并用p来接收
			p = p->rchild;   //此时p成为了自己的双亲，然后再访问右子树
		}
	}
}
//中序遍历非递归算法
void InOrderT(Bitree T)
{
	StackLink S = InitStack();
	Binode* p = T;  //创建一个指针变量p来遍历二叉树
	while (p || !StackEmpty(S))   //只有p为空值且栈为空才会退出循环，即二叉树没有结点了（p为空），全部访问了（全部出栈），循环就结束了
	{
		if (p)   //如果p非空结点，进栈，访问左子树
		{
			Push(&S, p);
			p = p->lchild;
		}
		else  //如果p为空结点，出栈并访问根节点，再访问右子树
		{
			Bitree q = Pop(&S);
			printf("%c ", q->data);
			p = q->rchild;
		}
	}
}

//后序遍历非递归算法
void PostOrderT(Bitree T)
{
	Binode* p = T;
	Binode* r = NULL;
	StackLink S = InitStack();
	while (p || !StackEmpty(S))
	{
		if (p)
		{
			Push(&S, p);
			p = p->lchild;
		}
		else
		{
			p = GetTop(S);
			if (p->rchild!=NULL&&p->rchild!=r)
			{
				p = p->rchild;
				Push(&S,p);
				p = p->lchild;
			}
			else
			{
				p = Pop(&S);
				printf("%c ", p->data);
				r == p;
				p = NULL;
			}	
		}
	}
}

//二叉树的层次遍历，即按照结点的编号顺序一个一个的遍历，从上到下，从左到右遍历
//要实现层次遍历，要借助队列实现
//首先把根节点入队，看看根节点是否有左右孩子，如果有，根节点出队后将左右孩子入队
//左右孩子入队后再看左孩子是否有左右孩子，如果有，左孩子出队后将它的左右孩子入队，右孩子同理。
//以此类推完成二叉树的层次遍历
typedef struct
{                 //定义一个顺序队列
	Binode data[MAXSIZE];
	int front, rear;
}SqQueue;
SqQueue* InitQueue()
{
	SqQueue* S = (SqQueue*)malloc(sizeof(SqQueue));
	S->front = S->rear = 0;
	return S;
}
void EnQueue(SqQueue* S,Binode* p)
{
	if ((S->rear + 1) % MAXSIZE == S->front)
	{
		printf("队满\n");
		return;
	}
	S->data[S->rear] = *p;
	S->rear = (S->rear + 1) % MAXSIZE;
}
Binode* OutQueue(SqQueue* S)
{
	if (S->front == S->rear)
	{
		printf("队空\n");
		return;
	}
	Binode* e = &S->data[S->front];
	S->front = (S->front + 1) % MAXSIZE;
	return e;
}
int QueueEmpty(SqQueue* S)
{
	if (S->front == S->rear)
		return 1;
	else
		return 0;
}
//二叉树的层次遍历
void LevelOrder(Bitree T)
{
	SqQueue* S = InitQueue();
	Binode* p = T;
	EnQueue(S, p);
	while (!QueueEmpty(S))
	{
		Binode* p = OutQueue(S);
		printf("%c ", p->data);
		if (p->lchild != NULL)
			EnQueue(S, p->lchild);
		if (p->rchild != NULL)
			EnQueue(S, p->rchild);
	}
}