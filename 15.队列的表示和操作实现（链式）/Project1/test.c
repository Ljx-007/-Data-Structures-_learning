#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//����޷�Ԥ�����еĳ��ȣ��������ʽ����
//Ϊ�������㣬����������һ��ͷ��㣬����ͷָ��ʼ��ָ��ͷ���
typedef struct Qnode
{
	int data;
	struct Qnode* next;
}Qnode,*Qptr;   //Qptr Ϊ���ָ�� ptr����pointer����˼��pointer��˼��ָ��

//�������У�һ��ʹ��һ��ͷָ�뼴�ɷ�������
//������ʽ���У�Ҫ����ͷɾβ���ԭ����Ҫ��ͷָ���βָ����������ɾ����
//���԰�ͷָ���βָ�����һ���ṹ���У��������
typedef struct
{
	Qptr front;  //��ͷָ��
	Qptr rear;   //��βָ��
}LinkQueue;

//���ӳ�ʼ��
void InitQue(LinkQueue* Q)
{
	Q->front = Q->rear = (Qnode*)malloc(sizeof(Qnode));
	Q->front->next = NULL; 
}

//��������
void DestroyQueue(LinkQueue* Q)
{
	while (Q->front)
	{
		Qnode* p = Q->front;        //������Բ��ô�������p������ֱ��ʹ���ֳɵ�rearָ��
		Q->front = Q->front->next;   
		free(p), p = NULL;
	}
}

//���ӵ����
void EnQueue(LinkQueue* Q)
{
	int n;
	printf("������Ҫ��ӵ�Ԫ�ظ�����");
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		Qnode* p = (Qnode*)malloc(sizeof(Qnode));
		if (!p)
		{
			perror("malloc error");
			return;
		}
		printf("������Ҫ��ӵ�Ԫ��(int):");
		scanf("%d", &(p->data));
		p->next = Q->rear->next;
		Q->rear->next = p;   //β�巨��Ԫ�ز����β
		Q->rear = p;
	}
}

//���ӵ�ɾ��
int DelQueue(LinkQueue* Q)  //����ɾ����Ԫ��
{
	if (Q->front == Q->rear)
	{
		printf("����Ϊ��\n");
		return -1;
	}
	else
	{
		Qnode* p = Q->front->next;
		Q->front->next = p->next;
		//���ɾ���������һ�����Ļ���β���ָ��Ҫ�ı䣬��ͷָ����ͬ
		if (p == Q->rear)
			Q->rear = Q->front;
		int e = p->data;
		free(p), p = NULL;
		return e;
	}
}

//ȡ���Ӷ�ͷԪ��
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