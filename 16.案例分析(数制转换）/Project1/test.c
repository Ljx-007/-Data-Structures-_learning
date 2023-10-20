#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//1.���Ƶ�ת��--��ջʵ��
typedef struct StackNode
{
	int data;
	struct StackNode* next;
}StackNode,*StackLink;
//��ʼ����ջ
StackLink InitStack()
{
	StackLink S = (StackNode*)malloc(sizeof(StackNode));
	S= NULL;
	return S;   //����һ��ͷָ��
}
//��ջ
void Push(StackLink* S,int n)
{
	StackNode* p = (StackNode*)malloc(sizeof(StackNode));
	p->data = n;
	p->next = *S;
	*S = p;
}
//��ջ
int Pop(StackLink* S)
{
	int e = (*S)->data;
	StackNode* p = *S;
	(*S) = (*S)->next;
	free(p), p = NULL;
	return e;
}
//�ж�ջ�Ƿ�Ϊ��
int IsEmpty(StackLink* S)
{
	if (*S == NULL)
		return 0;
	else
		return 1;
}

//��ʮ������ת��Ϊ8����
//������N����dȡ����  N��ʮ������  d��d����Ȩ��
//N����d��ȡ���������ٳ���d����ȡ������ֱ����Ϊ0���ѵõ������������������У�����ʮ������N��d�����еı�ʾ
void  convert_8(int n)
{
	StackLink S=InitStack();
	while(n)
	{
		Push(&S, n % 8);
		n = n / 8;
	}
	while (IsEmpty(&S))
	{
		printf("%d", Pop(&S));
	}
	printf("\n");
}
//ת��2����
void convert_2(int n)
{
	StackLink S = InitStack();
	while (n)
	{
		Push(&S, n % 2);
		n = n / 2;
	}
	while (IsEmpty(&S))
	{
		printf("%d", Pop(&S));
	}
	printf("\n");
}
//ת����16����
void convert_16(int n)
{
	StackLink S = InitStack();
	while (n)
	{
		Push(&S, n % 16);
		n = n / 16;
	}
	while (IsEmpty(&S))
	{
		char c;
		int i = Pop(&S);
		if (i > 9)
			c = i + 'A' - 10;
		else
			c = i + '0';
		printf("%c", c);
	}
}
int main()
{
	convert_8(31);
	convert_2(31);
	convert_16(31);
	return 0;
}

