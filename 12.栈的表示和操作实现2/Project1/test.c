#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//链栈：指使用链式存储结构实现的栈，只能在链表头部操作
//栈顶为头指针,链栈不需要头结点，且不会出现满栈的情况，空栈相当于头指针指向空
//插入和删除仅在栈顶处执行

//定义一个链栈
typedef struct  StackNode
{
	int data;
	struct StackNode* next;
}StackNode,*LinkStack;

//初始化链栈
void InitStack(LinkStack S)
{
	S = NULL;
}
//判断栈是否为空
int is_empty(LinkStack S)
{
	if (!S)    //S为空返回0
		return 0;
	else    //不为空返回1
		return 1;
}

//链栈的入栈
void Push(LinkStack S)
{
	int n;
	printf("请输入入栈的元素个数：");
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		StackNode* p = (StackNode*)malloc(sizeof(StackNode));
		if (!p)
		{
			perror("malloc error");
			return;
		}
		printf("请输入该栈的数据(int型):");
		scanf("%d", &p->data);
		p->next = S;   //将新的元素放在栈顶
		S = p;   //S为头指针，始终指向栈顶
	}
}

//链栈的出栈
int Pop(LinkStack S)
{
	if (!S)
	{
		printf("栈为空\n");
		return;
	}
	StackNode* f = S;
	S = S->next;
	int e = f->data;
	free(f), f = NULL; //释放出栈结点的空间
	return e;   //把出栈元素的数据返回出来
}

//取栈顶元素
int GetTop(LinkStack S)
{
	if (!S)
	{
		printf("栈为空\n");
		return;
	}
	return S->data;
}