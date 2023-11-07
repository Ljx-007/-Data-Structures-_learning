#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//以二叉链表作为二叉树的存储结构，编写以下算法
//（1）统计二叉树的叶结点个数
typedef struct BiNode
{
	int data;
	struct BiNode* lchild, * rchild;
}BiNode,*BiTree;
int CountLeaf(BiTree BT)
{
	if (!BT)
		return 0;
	if (BT->lchild == NULL && BT->rchild == NULL)
		return 1;
	return CountLeaf(BT->rchild)+CountLeaf(BT->lchild);
}
//(2)判别两棵树是否相等
int CompareTree(BiTree BT1, BiTree BT2)
{   //相等返回1，不相等返回0
	if (BT1 == NULL && BT2 == NULL)
		return 1;
	else if (BT1 == NULL || BT2 == NULL)
		return 0;
	else 
	{
		if (BT1->data == BT2->data)
		{
			int m=CompareTree(BT1->lchild, BT2->lchild);   //判断孩子是否相等
			int n=CompareTree(BT1->rchild, BT2->rchild);
			int p=CompareTree(BT1->rchild, BT2->lchild);  //两棵树有可能是镜像的，所以树1的左右孩子要和树2的右左孩子比较
			int q=CompareTree(BT1->lchild, BT2->rchild);
			return (m && q) || (p && q);  //左左，右右相等或者左右，右左相等，有一个满足条件就返回1，都不满足就返回0
		}
		else
			return 0;
	}
}
//（3）交换二叉树的每个结点的左孩子和右孩子
void Change(BiTree *BT)
{
	if (!*BT)
		return;
	BiNode* tmp = (*BT)->lchild;
	(*BT)->lchild = (*BT)->rchild;
	(*BT)->rchild = tmp;
	Change(&(*BT)->lchild);
	Change(&(*BT)->rchild);
}
//(4)设计二叉树的双序遍历算法
//（双序遍历是指对于二叉树的每一个结点来说，先访问这个结点，再按双序遍历他的左子树，然后再一次访问这个结点，接下来双序遍历它的右子树）
void DoubleTraverse(BiTree BT)
{
	if (!BT)
		return;
	else if (BT->lchild == NULL && BT->rchild == NULL)
		printf("%d ", BT->data);   //输出叶子结点，如果不添加这条语句，则叶子结点会被输出两次
	else 
	{
		printf("%d ", BT->data);
		DoubleTraverse(BT->lchild);
		printf("%d ", BT->data);
		DoubleTraverse(BT->rchild);
	}
}
//(5)计算二叉树的最大宽度（二叉树的最大宽度是指二叉树所有层中结点个数的最大值)
int TreeWidth(BiTree BT)
{
	if (!BT)
		return 0;
	BiTree Q[1024];  //创建队列
	int front, rear, last;   //front是队头指针，rear是队尾指针，last是同层最右边的结点在队列中的位置
	front = rear = last=0;   
	int tmpw, maxw;   //tmpw是某层的宽度，maxw是最大宽度
	tmpw = maxw = 0;
	Q[rear] = BT;   //根结点入队
	while (front <= last)       //如果last没有大于等于front，说明没有下一层了，则循环结束
	{
		BiTree p = Q[front++];   //给p赋值某个某一层的结点，并用其让该结点的左右孩子入队
		tmpw++;                  //每读取一个结点，二叉树某层的宽度就加1
		if (p->lchild != NULL)       //如果p的左右孩子不为空，就入队
			Q[++rear] = p->lchild;
		if (p->rchild != NULL)
			Q[++rear] = p->rchild;
		if (front > last)    //front才会跑到last前面时，代表front已经指向下一层了
		{
			last = rear;     //让last指向下一层的最右边的结点
			if (tmpw > maxw)   //每一层的宽度与最大宽度作比较
			{
				maxw = tmpw;   //如果某层宽度大于最大宽度，那么最大宽度更新为该层宽度
				tmpw = 0;     //将tmpw置零，开始下一次计算宽度
			}
		}
	}
	return maxw;
}
//(6)用按层次顺序遍历二叉树的方法，统计树中度为1的点
#define SIZE 100
typedef struct SqQueue
{
	BiNode TreeQ[SIZE];
	int front, rear;
}SqQueue;
void InitQueue(SqQueue* S)
{
	S = (SqQueue*)malloc(sizeof(SqQueue));
	S->front = S->rear=0;
}
void EnQueue(SqQueue* S,BiNode* p)
{
	if ((S->rear + 1) % SIZE == S->front)
	{
		printf("队满\n");
		return;
	}
	S->TreeQ[S->rear] = *p;
	S->rear = (S->rear + 1) % SIZE;
}
BiNode OutQueue(SqQueue* S)
{
	if (S->rear == S->front)
	{
		printf("队空\n");
		return;
	}
	BiNode e = S->TreeQ[S->front];
	S->front = (S->front + 1) % SIZE;
	return e;
}
int QueueEmpty(SqQueue* S)
{
	if (S->rear == S->front)
		return 1;
	else
		return 0;
}
int Level(BiTree BT)
{
	if (!BT)
		return 0;
	SqQueue S;
	int count=0;   //用count来记录度为1的结点个数
	InitQueue(&S);
	BiTree p = BT;
	EnQueue(&S, p);
	while (!QueueEmpty(&S))
	{
		BiNode q = OutQueue(&S);
		if ((q.lchild != NULL && q.rchild == NULL) || (q.rchild != NULL && q.lchild == NULL))   //如果左右孩子其中有一个为空，说明该结点度为1
			count++;
		if (q.lchild)   //左孩子或右孩子如果不为空，就入队
			EnQueue(&S, q.lchild);
		if (q.rchild)
			EnQueue(&S, q.rchild);
	}
	return count;
}
//（7）求任意二叉树中第一条最长的路径长度，并输出此路径上各结点的值
int path(BiTree BT)    //计算路径长度
{
	if (!BT)
		return 0;
	int m = path(BT->lchild);
	int n = path(BT->rchild);
	return m > n ? m : n;      //不+1是因为路径长度为 树的深度-1
}
void Longestpath(BiTree BT)
{
	if (!BT)
		return;
	printf("%d ", BT->data);  //先输出结点信息
	int r = path(BT->rchild);  //计算右子树的路径长度
	int l = path(BT->lchild);  //计算左子树的路径长度
	if (l >= r)   //如果左子树路径长度比右子树深
		Longestpath(BT->lchild);  //则走左子树，输出左孩子结点信息
	else  //反之走右子树
		Longestpath(BT->rchild);
}
//（8）输出二叉树中从每个叶子结点到根结点的路径
typedef struct SqStack
{
	BiNode TreeS[100];
	int top;
	int base;
	int stacksize;
}SqStack;
void InitStack(SqStack* S)
{
	S->top = 0, S->stacksize = 100;
	S->base = 0;
}
void Push(SqStack* S,BiTree T)
{
	if (S->top - S->base == 100)
	{
		printf("栈满\n");
		return;
	}
	S->TreeS[S->top++] = *T;
}
BiNode Pop(SqStack* S)
{
	if (S->base == S->top)
	{
		printf("栈空\n");
		return;
	}
	BiNode e = S->TreeS[S->top--];
	return e;
}
void Allpath(BiTree BT,SqStack* S)  
{ //输出所有叶子结点到根结点的路径，要知道一个结点是否为叶结点，必须得遍历到这个结点才可以
	//而输出路径结点又是从上往下的，所以我们要逆序输出，要用到栈
	if (!BT)
		return;
	Push(S, BT);  //先将该结点入栈
	if(!BT->lchild&&!BT->rchild)    //如果是该叶结点，那么就把栈中的结点全部输出
	{
		for (int i = 0; i < S->top; i++)
		{
			int data = S->TreeS[i].data;
			printf("%d ", data);
		}
	}
	else
	{ //如果该结点不是叶结点，那么就继续寻找其左孩子和右孩子是否为叶结点
		Allpath(BT->lchild, S);
		Allpath(BT->rchild, S);
	}
	Pop(S);  //当走到这一步时，说明已找到一个叶结点并已输出其路径，那么就要寻找其他的叶结点，于是将该叶结点出栈
	  //出栈后函数结束，如果进入了递归，则回退到上一层函数中，回退后的函数处理的结点就是出栈的叶结点的双亲，再让上一层的函数去处理另外的子树
}