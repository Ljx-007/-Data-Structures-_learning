#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//2.括号匹配的检验
typedef struct StackNode
{
	char c;
	struct StackNode* next;
}StackNode,*StackLink;
StackNode* InitStack()
{
	StackLink S = (StackNode*)malloc(sizeof(StackNode));
	S = NULL;
	return S;
}
//判断栈是否为空
int IsEmpty(StackLink* S)
{
	if (*S == NULL)
		return 1;
	else
		return 0;
}
//获取栈顶元素 
char GetTop(StackLink* S)
{
	if (*S)  //如果栈顶不为空，则返回栈顶元素
	{
		return (*S)->c;
	}
	else
	{
		printf("栈为空\n");
		return '-1';
	}
}
//入栈
void Push(StackLink* S, char c)
{
	StackNode* p = (StackNode*)malloc(sizeof(StackNode));
	if (!p)
	{
		printf("malloc error");
		return;
	}
	p->c = c;
	p->next = *S;
	*S = p;
}
//出栈
char Pop(StackLink* S)
{
	if (*S)
	{
		char c = (*S)->c;
		(*S) = (*S)->next;
		return c;
	}
	else
	{
		printf("栈为空");
		return '-1';
	}
}
void check(StackLink* S)
{
	char str[1024];
	printf("输入括号检验是否匹配：\n");
	scanf("%s", str);
	char* ptr = str;
	//创建一个flag变量，来判断是否匹配成功,1代表匹配成功，0代表匹配失败
	int flag = 1;
	char ch;
	//进入循环有两个条件，一个条件是字符串没到末尾，一个条件是flag=1，即前面的括号都匹配成功了
	while ((ch=*ptr++) != '\0' && flag)   //一个一个读取括号，一直读到末尾，退出循环
	{
		switch (ch)
		{
		case '(':
		case '[':   //读到'(','[','{'都直接入栈
		case '{':
			Push(S, ch);
			break;
		case ')':
			if (!IsEmpty(S) && GetTop(S) == '(')   //如果栈不为空，且栈顶元素为(，则出栈
				Pop(S);
			else
				flag = 0;  //如果栈为空或者栈顶元素不为(，则匹配失败
			break;
		case ']':
			if (!IsEmpty(S) && GetTop(S) == '[')      //与 ( 同理
				Pop(S);
			else 
				flag = 0;
			break;
		case '}':
			if (!IsEmpty(S) && GetTop(S) == '{')   //与 ( 同理
				Pop(S);
			else
				flag = 0;
			break;
		default:
			break;
		}
	}
	if (flag == 1)
		printf("匹配成功!\n");
	else
		printf("匹配失败!\n");
}
int main()
{
 	StackLink S = InitStack();
	check(&S);
	return 0;
}