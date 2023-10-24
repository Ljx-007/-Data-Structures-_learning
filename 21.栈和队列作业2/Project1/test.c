#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//6.�����Դ�ͷ����ѭ�������ʾ���У�����ֻ��һ��ָ��ָ���βԪ�ؽ�㣨ע�⣺����ͷָ�룩���Ա�д��Ӧ���ÿն��С��ж϶����Ƿ�Ϊ�գ���Ӻͳ��ӵ��㷨
typedef struct QueueNode
{
	int a;                  //����������
	struct QueueNode* next;
}QueueNode,*QueuePtr;
typedef struct QueueLink
{
	QueuePtr rear;   //ֻ����һ��βָ��,��rear->next����ͷ���
}QueueLink;
//��ʼ��
void InitQueue(QueueLink* Q)
{
	(*Q).rear = (QueueNode*)malloc(sizeof(QueueNode));
	(*Q).rear->next = (*Q).rear;
}
//���
void EnQueue(QueueLink* Q,int a)
{
	QueueNode* p = (QueueNode*)malloc(sizeof(QueueNode));
	p->a = a;
	p->next = (*Q).rear->next;
	(*Q).rear->next = p;
	(*Q).rear = p;
}
//����
int OutQueue(QueueLink* Q)
{
	if (Q->rear->next == Q->rear)
	{
		printf("����Ϊ�� ");
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
//�ж϶����Ƿ�Ϊ��
int IsEmpty(QueueLink* Q)
{
	if (Q->rear->next == Q->rear)
		return 1;
	else
		return 0;
}
//�ÿն���
void ClearQueue(QueueLink* Q)
{
	if(Q->rear->next==Q->rear)
	{
		printf("�����Ѿ�Ϊ��\n");
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
//���Դ���
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


//7.����������Q[m]���ѭ�������е�Ԫ�أ�ͬʱ����һ����־tag����tag==0��tag==1�������ڶ�ͷָ�루front���Ͷ�βָ�루rear�����ʱ��
//  ����״̬Ϊ���ա����ǡ��������Ա�д��˽ṹ��Ӧ�Ĳ���(enqueue)��ɾ��(dequeue)�㷨
#define M 5
typedef struct SqQueue
{
	int* base;
	int front;           //����һ��˳�����
	int rear;
	int tag;    //���ﲻ������һ���ռ�������ѭ��������û���ˣ�����ʹ�ñ�־tag������ѭ�����пջ�����
}SqQueue;
void InitSqQueue(SqQueue* Q)
{
	Q->base = (int*)malloc(sizeof(int) * M);   //����������Q[m]�Ĵ�СΪ10
	Q->front = Q->rear = 0;
	Q->tag = 0;
}
//����
void enqueue(SqQueue* Q,int a)
{
	if (Q->tag==1)
	{
		printf("��������\n");
		return;
	}
	Q->base[Q->rear] = a;
	Q->rear = (Q->rear + 1) % M;
	if (Q->front == Q->rear)
		Q->tag = 1;
}
//ɾ��
int dequeue(SqQueue* Q)
{
	if (Q->tag==0)
	{
		printf("�����ѿ�\n");
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


//8.���������ѭ�����е����˶����Խ��в����ɾ��������Ҫ��
//��1��д��ѭ�����е����Ͷ��壻
//��2��д�����Ӷ�βɾ�����͡��Ӷ�ͷ���롱���㷨
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
//��ͷ����
void En_front(CirQueue* C, int a)
{
	if ((C->front - 1 + M) % M == C->rear)
	{
		printf("��������\n");
		return;
	}
	C->front = (C->front - 1 + M) % M;    //��ͷ���ӵ�����ͷ����ѭ��������β����������
	C->base[C->front] = a;
}
//��βɾ��
int Del_rear(CirQueue* C)
{
	if (C->rear == C->front)
	{
		printf("�����ѿ�\n");
		return;
	}
	C->rear = (C->rear - 1 + M) % M;   //��βɾ��������ͷ����ѭ��������β������ɾ��
	int e = C->base[C->rear];
	return e;
}

//9.��֪Ackermann�����������£�
//            n+1                    ��m=0ʱ
//Ack(m,n)=   Ack(m-1,1)             ��m!=0,n=0ʱ
//            Ack(m-1,Ack(m,n-1))    ��m!=0,n!=0ʱ
//��1��д������Ack(m,n)�ĵݹ��㷨�������ݴ��㷨����Ack(2,1)�ļ�����̡�
//��2��д������Ack(m,n)�ķǵݹ��㷨
int Ack(int m, int n)
{  //�ݹ��㷨
	if (m == 0)
		return n + 1;
	else if (n == 0 && m != 0)
		return Ack(m - 1, 1);
	else
		return Ack(m - 1, Ack(m, n - 1));
}
//�ǵݹ��㷨
//�ǵݹ��㷨�е㸴�ӣ�Ҫ�Լ�����ջ���ݹ�ת��Ϊ�ǵݹ�
//����ջת���ݹ鲽�����£�
//1.����һ������ջ��ŵݹ鹤����¼��ʵ�Σ����ص�ַ���ֲ������ȣ������б���Ϊm,n��Ack�����ķ���ֵ���Ƿ�����Ack������ֵ�ȣ�
//2.����ǵݹ������ڣ��������ó���ʼ�����˴�����Ϊm=0ʱ��Ack(m,n)=n+1��
//3.����ݹ������ڣ�����ִ��ʱÿһ�εݹ鶼����Ack��������Ϣ��ʵ�Σ�����ֵ�����ص�ַ���ֲ�����������������ջ
//4.�ݹ�����������㣬������ݹ���ڵĸ���������Ϊ��ǰ�ĺ���ֵ
//5.���ش���ջ���յ�����£������˳�ջ����¼�����ݼ�¼�е���Ϣ���м��㺯��ֵ������ֱ��ջ��Ϊֹ
//����ɲο�https://blog.csdn.net/sanqima/article/details/48831679

//int main()
//{
//	printf("%d",Ack(2, 1));
//	return 0;
//}


//10.��֪fΪ�������ͷָ�룬�����д洢�Ķ����������ݣ���д��ʵ����������ĵݹ��㷨��
//��1���������е��������
//��2���������еĽ�����
//��3��������������ƽ��ֵ
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
//�������е��������
int Findmax(StackLink S)
{
	StackNode* f = S->next;
	if (!f)
	{
		printf("����Ϊ��\n");
		return;
	}
	else if (!f->next)    //�������ֻ��һ��Ԫ�أ��򷵻���һ��Ԫ��
		return f->a;
	else
	{
		int max = Findmax(f);   //��ȡ��������е����ֵ
		return f->a>max ? f->a : max;    //���˽���ֵ�ͺ����������ֵ�Ƚϣ����ش���Ǹ�
	}
}
//������Ľ�����
int Findnode(StackLink S)
{
	StackNode* f = S;
	if (!f->next)
		return 1;
	else
		return 1+Findnode(f->next);
}
//������������ƽ��ֵ
float average(StackLink S,int n)   //����ͷ�����n������ƽ��ֵ
{
	StackNode* f = S->next;   //����ͷ���ָ����Ԫ���
	if (!f)
	{
		printf("����Ϊ��");
		return -1;
	}
	else if (!f->next)    //���ֻ��һ����㣬���ظý���ֵ
		return f->a;
	else
	{
		//Ҫ����ͷ����n������ƽ��ֵ����Ҫ������Ԫ����n-1������ƽ��ֵ
		float ave = average(f, n - 1);    //����f����n-1������ƽ��ֵ
		return (ave * (n - 1) + f->a) / n;   //n-1������ƽ��ֵ������Ԫ����ֵ����n�õ�ƽ��ֵ
	}
}
//��������
void Add(StackLink* S)
{
	StackNode* r = *S;
	for (int i = 0; i < 5; i++)
	{
		StackNode* p = (StackNode*)malloc(sizeof(StackNode));
		printf("�������ݣ�");
		scanf("%d", &p->a);
		p->next = r->next;
		r->next = p;
		r = p;
	}
}
//���Դ���
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