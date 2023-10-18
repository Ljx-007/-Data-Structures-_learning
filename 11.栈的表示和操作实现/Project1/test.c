#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//栈的定义：
//栈（stack）是限定仅在表尾进行插入或删除操作的线性表。具有后进先出的特点
//应用场景：
//数制的转换，括号的匹配检验，表达式求值等问题
//存储结构：
// 顺序栈和链栈


//顺序栈的表示
//顺序栈的存储方式与顺序表相同，利用一组连续的存储单元结构依次存放从栈底到栈顶的数据元素，栈底一般在低地址端。
//同时栈还要设立top指针，指向栈顶位置，再设立base指针，指向栈底位置
//为了操作方便，通常top的指向为栈顶元素之上的下标位置
//另外，用stacksize表示顺序栈可使用的最大容量

//定义一个栈
#define MAXSIZE 20   //定义顺序栈的最大容量
typedef struct Sqstack
{
	int* top;    //这里暂设栈元素类型为int，设立top指针指向栈顶，base指向栈底
	int* base;
	int stacksize;
}Sqstack;

//栈的初始化
void InitStack(Sqstack* S)
{
	S->base = (int*)malloc(sizeof(int) * MAXSIZE);  //创建一块地址连续的空间
	if (!S->base)
	{
		perror("creat stack error");
		return;
	}
	S->top = S->base;   //top=base，代表初始化的栈为空栈
	S->stacksize = MAXSIZE;
}

//判断栈是否为空
int StackEmpty(Sqstack S)
{
	if (S.base == S.top)
		return 1;
	else
		return 0;
}

//求顺序栈长度
int LenStack(Sqstack S)
{
	return S.top - S.base;
}
//清空顺序栈
void Clear(Sqstack* S)
{
	if (S->base)
		S->top = S->base;  //让top指针指向栈底，不用管栈之前存了什么，新存储的数字会覆盖掉之前的数据，所以可以直接当成空栈
	else
		printf("栈不存在\n");
}

//销毁顺序栈
void Destroy(Sqstack* S)
{
	free(S->base), S->base = NULL;
	S->top = NULL;  //把top和base都置空
	S->stacksize = 0;  //栈容量改为0
}

//顺序栈的入栈
void Push(Sqstack* S)
{
	int ret, n;
	char str[1001];
	printf("请输入进栈的元素个数：");
again:
	ret = scanf("%d", &n);
	if (!ret)
	{
		while (gets_s(str, 1000))
		{
			printf("请输入正确的数字：");
			goto again;
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (S->top - S->base == S->stacksize)   //判断栈是否满了
		{
			printf("栈满了\n");
			break;
		}
		printf("请输入进栈的数据(int型)：");
	again2:
		ret = scanf("%d", S->top++);   //这里可以把给S->top指向的空间赋值和top指针自增合并在一起写，没有问题
		if (!ret)
		{
			while (gets_s(str, 1000))
			{
				printf("请输入正确的数字：");
				goto again2;
			}
		}
		//S->top++;
	}
}

//顺序栈的出栈--将栈顶元素删除
int Pop(Sqstack* S)   //返回出栈删除的那个元素
{
	if (S->top == S->base)
	{
		printf("栈是空的\n");
		return -1;
	}
	S->top--;
	int e = *(S->top);
	//上述两行代码可改为
	//int e=*--S->top; 
	return e;
}

//顺序栈取栈顶元素
int GetTop(Sqstack S)
{
	if (S.top != S.base)   //如果栈不是空的
		return *(S.top - 1);  //top指针不减
	else
	{
		printf("栈是空的\n");
		return -1;
	}
}
int main()
{
	Sqstack S;
	InitStack(&S);
	Push(&S);
	Pop(&S);
	printf("%d ", GetTop(S));
	return 0;
}