#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//��ջ��ָʹ����ʽ�洢�ṹʵ�ֵ�ջ��ֻ��������ͷ������
//ջ��Ϊͷָ��,��ջ����Ҫͷ��㣬�Ҳ��������ջ���������ջ�൱��ͷָ��ָ���
//�����ɾ������ջ����ִ��

//����һ����ջ
typedef struct  StackNode
{
	int data;
	struct StackNode* next;
}StackNode,*LinkStack;

//��ʼ����ջ
void InitStack(LinkStack S)
{
	S = NULL;
}
//�ж�ջ�Ƿ�Ϊ��
int is_empty(LinkStack S)
{
	if (!S)    //SΪ�շ���0
		return 0;
	else    //��Ϊ�շ���1
		return 1;
}

//��ջ����ջ
void Push(LinkStack S)
{
	int n;
	printf("��������ջ��Ԫ�ظ�����");
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		StackNode* p = (StackNode*)malloc(sizeof(StackNode));
		if (!p)
		{
			perror("malloc error");
			return;
		}
		printf("�������ջ������(int��):");
		scanf("%d", &p->data);
		p->next = S;   //���µ�Ԫ�ط���ջ��
		S = p;   //SΪͷָ�룬ʼ��ָ��ջ��
	}
}

//��ջ�ĳ�ջ
int Pop(LinkStack S)
{
	if (!S)
	{
		printf("ջΪ��\n");
		return;
	}
	StackNode* f = S;
	S = S->next;
	int e = f->data;
	free(f), f = NULL; //�ͷų�ջ���Ŀռ�
	return e;   //�ѳ�ջԪ�ص����ݷ��س���
}

//ȡջ��Ԫ��
int GetTop(LinkStack S)
{
	if (!S)
	{
		printf("ջΪ��\n");
		return;
	}
	return S->data;
}