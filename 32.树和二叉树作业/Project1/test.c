#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//�Զ���������Ϊ�������Ĵ洢�ṹ����д�����㷨
//��1��ͳ�ƶ�������Ҷ������
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
//(2)�б��������Ƿ����
int CompareTree(BiTree BT1, BiTree BT2)
{   //��ȷ���1������ȷ���0
	if (BT1 == NULL && BT2 == NULL)
		return 1;
	else if (BT1 == NULL || BT2 == NULL)
		return 0;
	else 
	{
		if (BT1->data == BT2->data)
		{
			int m=CompareTree(BT1->lchild, BT2->lchild);   //�жϺ����Ƿ����
			int n=CompareTree(BT1->rchild, BT2->rchild);
			int p=CompareTree(BT1->rchild, BT2->lchild);  //�������п����Ǿ���ģ�������1�����Һ���Ҫ����2�������ӱȽ�
			int q=CompareTree(BT1->lchild, BT2->rchild);
			return (m && q) || (p && q);  //����������Ȼ������ң�������ȣ���һ�����������ͷ���1����������ͷ���0
		}
		else
			return 0;
	}
}
//��3��������������ÿ���������Ӻ��Һ���
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
//(4)��ƶ�������˫������㷨
//��˫�������ָ���ڶ�������ÿһ�������˵���ȷ��������㣬�ٰ�˫�����������������Ȼ����һ�η��������㣬������˫�����������������
void DoubleTraverse(BiTree BT)
{
	if (!BT)
		return;
	else if (BT->lchild == NULL && BT->rchild == NULL)
		printf("%d ", BT->data);   //���Ҷ�ӽ�㣬��������������䣬��Ҷ�ӽ��ᱻ�������
	else 
	{
		printf("%d ", BT->data);
		DoubleTraverse(BT->lchild);
		printf("%d ", BT->data);
		DoubleTraverse(BT->rchild);
	}
}
//(5)���������������ȣ����������������ָ���������в��н����������ֵ)
int TreeWidth(BiTree BT)
{
	if (!BT)
		return 0;
	BiTree Q[1024];  //��������
	int front, rear, last;   //front�Ƕ�ͷָ�룬rear�Ƕ�βָ�룬last��ͬ�����ұߵĽ���ڶ����е�λ��
	front = rear = last=0;   
	int tmpw, maxw;   //tmpw��ĳ��Ŀ�ȣ�maxw�������
	tmpw = maxw = 0;
	Q[rear] = BT;   //��������
	while (front <= last)       //���lastû�д��ڵ���front��˵��û����һ���ˣ���ѭ������
	{
		BiTree p = Q[front++];   //��p��ֵĳ��ĳһ��Ľ�㣬�������øý������Һ������
		tmpw++;                  //ÿ��ȡһ����㣬������ĳ��Ŀ�Ⱦͼ�1
		if (p->lchild != NULL)       //���p�����Һ��Ӳ�Ϊ�գ������
			Q[++rear] = p->lchild;
		if (p->rchild != NULL)
			Q[++rear] = p->rchild;
		if (front > last)    //front�Ż��ܵ�lastǰ��ʱ������front�Ѿ�ָ����һ����
		{
			last = rear;     //��lastָ����һ������ұߵĽ��
			if (tmpw > maxw)   //ÿһ��Ŀ������������Ƚ�
			{
				maxw = tmpw;   //���ĳ���ȴ�������ȣ���ô����ȸ���Ϊ�ò���
				tmpw = 0;     //��tmpw���㣬��ʼ��һ�μ�����
			}
		}
	}
	return maxw;
}
//(6)�ð����˳������������ķ�����ͳ�����ж�Ϊ1�ĵ�
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
		printf("����\n");
		return;
	}
	S->TreeQ[S->rear] = *p;
	S->rear = (S->rear + 1) % SIZE;
}
BiNode OutQueue(SqQueue* S)
{
	if (S->rear == S->front)
	{
		printf("�ӿ�\n");
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
	int count=0;   //��count����¼��Ϊ1�Ľ�����
	InitQueue(&S);
	BiTree p = BT;
	EnQueue(&S, p);
	while (!QueueEmpty(&S))
	{
		BiNode q = OutQueue(&S);
		if ((q.lchild != NULL && q.rchild == NULL) || (q.rchild != NULL && q.lchild == NULL))   //������Һ���������һ��Ϊ�գ�˵���ý���Ϊ1
			count++;
		if (q.lchild)   //���ӻ��Һ��������Ϊ�գ������
			EnQueue(&S, q.lchild);
		if (q.rchild)
			EnQueue(&S, q.rchild);
	}
	return count;
}
//��7��������������е�һ�����·�����ȣ��������·���ϸ�����ֵ
int path(BiTree BT)    //����·������
{
	if (!BT)
		return 0;
	int m = path(BT->lchild);
	int n = path(BT->rchild);
	return m > n ? m : n;      //��+1����Ϊ·������Ϊ �������-1
}
void Longestpath(BiTree BT)
{
	if (!BT)
		return;
	printf("%d ", BT->data);  //����������Ϣ
	int r = path(BT->rchild);  //������������·������
	int l = path(BT->lchild);  //������������·������
	if (l >= r)   //���������·�����ȱ���������
		Longestpath(BT->lchild);  //������������������ӽ����Ϣ
	else  //��֮��������
		Longestpath(BT->rchild);
}
//��8������������д�ÿ��Ҷ�ӽ�㵽������·��
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
		printf("ջ��\n");
		return;
	}
	S->TreeS[S->top++] = *T;
}
BiNode Pop(SqStack* S)
{
	if (S->base == S->top)
	{
		printf("ջ��\n");
		return;
	}
	BiNode e = S->TreeS[S->top--];
	return e;
}
void Allpath(BiTree BT,SqStack* S)  
{ //�������Ҷ�ӽ�㵽������·����Ҫ֪��һ������Ƿ�ΪҶ��㣬����ñ�����������ſ���
	//�����·��������Ǵ������µģ���������Ҫ���������Ҫ�õ�ջ
	if (!BT)
		return;
	Push(S, BT);  //�Ƚ��ý����ջ
	if(!BT->lchild&&!BT->rchild)    //����Ǹ�Ҷ��㣬��ô�Ͱ�ջ�еĽ��ȫ�����
	{
		for (int i = 0; i < S->top; i++)
		{
			int data = S->TreeS[i].data;
			printf("%d ", data);
		}
	}
	else
	{ //����ý�㲻��Ҷ��㣬��ô�ͼ���Ѱ�������Ӻ��Һ����Ƿ�ΪҶ���
		Allpath(BT->lchild, S);
		Allpath(BT->rchild, S);
	}
	Pop(S);  //���ߵ���һ��ʱ��˵�����ҵ�һ��Ҷ��㲢�������·������ô��ҪѰ��������Ҷ��㣬���ǽ���Ҷ����ջ
	  //��ջ������������������˵ݹ飬����˵���һ�㺯���У����˺�ĺ�������Ľ����ǳ�ջ��Ҷ����˫�ף�������һ��ĺ���ȥ�������������
}