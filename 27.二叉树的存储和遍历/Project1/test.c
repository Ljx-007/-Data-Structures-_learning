#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//�������Ĵ洢�ṹ

//˳��洢�������������Ľ���α�ţ����δ�Ŷ������е�����Ԫ��
//          �����һ��������������㲻���ڵı���´��0����ʾ�����ڴ˽��
#define MAXSIZE 100    //�涨���������������
//type SqBitree[MAXSIZE];   ����һ�����������鼴�ɣ����ݰ�����Ŵ洢
//ȱ�㣺
//1������������ս��̫�࣬˳��洢����ɿռ��˷ѣ�����k��Ķ�����ֻ��k����㣬��ÿһ���һ����㣬����Ҫ����2^k-1���ռ䣬��k�ϴ�ʱ�����˷Ѻܶ���ڴ�ռ�
//2��������Ҫ�������ӻ��߼��٣�����̫�鷳

//˳��洢�ʺϴ���������������ȫ������

//��ʽ�洢��
//�ɶ������Ķ����֪���������Ľ����һ������Ԫ�غͷֱ�ָ��������������������֧����
// ���Զ������������ʽ�洢�ṹʱ�������е�һ��������ٰ�����������������ָ������ָ���򣨶�������
//  ��ʱΪ�˱����ҵ�����˫�ף������ڽ��ṹ������һ��ָ����˫�׽���ָ������������
typedef struct Binode
{  //�����������
	char data;   //�����������Ԫ��Ϊchar��
	struct Binode* lchild, *rchild;  //���Һ���ָ��
}Binode,*Bitree;
//  ��n��������n+1����ָ����
//typedef struct Binode
//{  //������������
//	int data;   //�����������Ԫ��Ϊint��
//	struct Binode* lchild, * rchild,*parent;  //���Һ���ָ���ָ��˫�׵�ָ��
//}Binode, * Bitree;


//����������
// �������������ṹ������D������������L������������R��
//  ����ʱ������˳��: DLR,LDR,LRD,DRL,RDL,RLD
//����涨���������ң�����������������������DLR��LDR��LRD
//DLR���ȣ����������   LDR���У����������   LRD���󣨸��������   
//��������к����ָ���ǣ��ȷ��ʸ����м���ʸ�������ʸ�

//����������������ݹ��㷨��
void visit(Bitree T)
{
	printf("%c", T->data);
}
void PreOrderTraverse(Bitree T)    //���������TΪ�����
{
	if (!T)   //���TΪ�ս�㣬���˳�
		return; 
	else
	{
		visit(T); //���������T�ķ��ʣ�����������ݿ����Լ���װvisit���������������ӡ���������������
		PreOrderTraverse(T->lchild);  //�õݹ��ȷ���������
		PreOrderTraverse(T->rchild);  //�ٷ���������
	}
}

//����������ݹ��㷨��
void InOrderTraverse(Bitree T)
{
	if (!T)
		return;
	else
	{
		InOrderTraverse(T->lchild);    //�ȷ���������
		visit(T);                   //�ٷ��ʸ��ڵ�
		InOrderTraverse(T->rchild);  //����ٷ���������
	}
}

//����������ݹ��㷨��
void PostOrderTraverse(Bitree T)
{
	if (!T)
		return;
	else
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);     //�ȷ������������ٷ����������������ʸ��ڵ�
		visit(T);
	}
}

//���ȥ��visit���ʽ����䣬�����ֱ����㷨��һ���ġ�����˵�����㷨�ķ���·����ͬ��ֻ�Ƿ��ʽ���ʱ����ͬ��
// ����������·���£������ξ�����ͬһ����㣬�����һ�ξ����ͷ��ʽ�㣬����������ʣ�����ǵڶ��ξ����ŷ��ʣ��������򣻵��������Ǻ���
//�����㷨ÿ����㶼ֻ������һ�Σ�����ʱ�临�Ӷ�ΪO(n)
//��������˽��������ʣ���ϵͳҪ��ջ���洢�ý�㣬�������¾��Ǿ�����ÿһ����㶼�Ȳ����ʣ�����ջռ�õ�������ռ�Ϊn���ռ临�Ӷ�ΪO(n)

//��������ķǵݹ��㷨
//��֮ǰ��ѧϰ�п�֪���ݹ��㷨ת��Ϊ�ǵݹ��㷨����Ҫ�����Լ�����һ��ջ������ϵͳ��ջ
typedef struct StackNode
{                           //��ջ����Ҫͷ���
	Binode* T;
	struct StackNode* next;
}StackNode,*StackLink;
StackNode* InitStack()
{
	StackLink S = (StackLink)malloc(sizeof(StackNode));
	S= NULL;   //����ջ��ָ�룬������ջʱ��ջΪ�գ�����SΪ��ָ��
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
//��������ǵݹ��㷨
void PreOrderT(Bitree T)
{
	StackLink S = InitStack();
	Binode* p = T;    //����ָ�����p������������T
	while (p || !StackEmpty(S))    //������û�н��ɱ�������ֹͣѭ��
	{
		if (p)     //p�ǿ�ʱ
		{
			Binode* q = p;  //����һ��ָ��ָ������
			printf("%c ", q->data);   //��������ȷ��ʸ����
			Push(&S, q);           //�ٰ����������ջ�����ű���������
			           //��������ջ��Ŀ�������������Ϊ�գ��������»ص������������������
			p = p->lchild;
		}
		else  //���pΪ��
		{
			p = Pop(&S);   //����p��˫�ף�����p������
			p = p->rchild;   //��ʱp��Ϊ���Լ���˫�ף�Ȼ���ٷ���������
		}
	}
}
//��������ǵݹ��㷨
void InOrderT(Bitree T)
{
	StackLink S = InitStack();
	Binode* p = T;  //����һ��ָ�����p������������
	while (p || !StackEmpty(S))   //ֻ��pΪ��ֵ��ջΪ�ղŻ��˳�ѭ������������û�н���ˣ�pΪ�գ���ȫ�������ˣ�ȫ����ջ����ѭ���ͽ�����
	{
		if (p)   //���p�ǿս�㣬��ջ������������
		{
			Push(&S, p);
			p = p->lchild;
		}
		else  //���pΪ�ս�㣬��ջ�����ʸ��ڵ㣬�ٷ���������
		{
			Bitree q = Pop(&S);
			printf("%c ", q->data);
			p = q->rchild;
		}
	}
}

//��������ǵݹ��㷨
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

//�������Ĳ�α����������ս��ı��˳��һ��һ���ı��������ϵ��£������ұ���
//Ҫʵ�ֲ�α�����Ҫ��������ʵ��
//���ȰѸ��ڵ���ӣ��������ڵ��Ƿ������Һ��ӣ�����У����ڵ���Ӻ����Һ������
//���Һ�����Ӻ��ٿ������Ƿ������Һ��ӣ�����У����ӳ��Ӻ��������Һ�����ӣ��Һ���ͬ��
//�Դ�������ɶ������Ĳ�α���
typedef struct
{                 //����һ��˳�����
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
		printf("����\n");
		return;
	}
	S->data[S->rear] = *p;
	S->rear = (S->rear + 1) % MAXSIZE;
}
Binode* OutQueue(SqQueue* S)
{
	if (S->front == S->rear)
	{
		printf("�ӿ�\n");
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
//�������Ĳ�α���
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