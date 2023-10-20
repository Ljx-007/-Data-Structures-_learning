#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//1.数制的转换--链栈实现
typedef struct StackNode
{
	int data;
	struct StackNode* next;
}StackNode,*StackLink;
//初始化链栈
StackLink InitStack()
{
	StackLink S = (StackNode*)malloc(sizeof(StackNode));
	S= NULL;
	return S;   //创建一个头指针
}
//入栈
void Push(StackLink* S,int n)
{
	StackNode* p = (StackNode*)malloc(sizeof(StackNode));
	p->data = n;
	p->next = *S;
	*S = p;
}
//出栈
int Pop(StackLink* S)
{
	int e = (*S)->data;
	StackNode* p = *S;
	(*S) = (*S)->next;
	free(p), p = NULL;
	return e;
}
//判断栈是否为空
int IsEmpty(StackLink* S)
{
	if (*S == NULL)
		return 0;
	else
		return 1;
}

//把十进制数转换为8进制
//方法：N除以d取倒余  N：十进制数  d：d进制权重
//N除以d，取余数后，商再除以d，再取余数，直到商为0，把得到的所有余数倒着排列，则是十进制数N在d进制中的表示
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
//转换2进制
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
//转换成16进制
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

