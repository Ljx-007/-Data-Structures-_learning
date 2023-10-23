#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//1.将编号为0和1的两个栈存放于一个数组空间V[m]中，栈底分别处于数组的两端。当第0号栈的栈顶指针top[0]等于-1时该栈为空；当第1号栈的栈顶指针top[1]等于m时
//该栈为空。两个栈均从两端向中间增长。试编写双栈初始化，判断栈空、栈满、进栈和出栈等算法的函数。
//双栈数据结构的定义如下：
typedef struct
{
	int top[2], bot[2];   //栈顶和栈底指针
	int* V;               //栈数组
	int m;                //栈最大可容纳元素个数
}DblStack;
//双栈初始化
void InitDblStack(DblStack* D)
{
	D->V = (int*)malloc(sizeof(int) * (D->m));
	D->top[0] =-1;
	D->top[1] =D->m;
	D->bot[0] = 0;
	D->bot[1] = D->m - 1;
}
//判断栈空
int IsEmpty(DblStack* D)
{
	if (D->top[0] == -1 && D->top[1] == D->m)
		return 1;
	else
		return 0;
}
//判断栈满
int IsFull(DblStack* D)
{
	if (D->top[0]+1 == D->top[1])
		return 1;
	else
		return 0;
}
//进栈
void EnDblStack(DblStack* D)
{
	int answer;
	if (IsFull(D))
	{
		printf("栈满了");
		return;
	}
	printf("进0号还是1号栈:");
	scanf("%d", &answer);
	switch (answer)
	{
	case 0:
		printf("输入进栈的元素：");
		scanf("%d", &(D->V[++D->top[0]]));
		break;
	case 1:
		printf("输入进栈的元素：");
		scanf("%d", &(D->V[--D->top[1]]));
		break;
	default:
		printf("输入错误\n");
		break;
	}
}
//出栈
void DelDblStack(DblStack* D)
{
	int ret;
	if (IsEmpty(D))
	{
		printf("栈为空\n");
		return;
	}
	printf("出0号还是1号栈：");
	scanf("%d", &ret);
	switch (ret)
	{
	case 0:
		if (D->top[0] == -1)
			printf("0号栈为空");
		else
			D->top[0]--;
		break;
	case 1:
		if (D->top[1] == D->m)
			printf("1号栈为空");
		else
			D->top[1]++;
		break;
	default:
		break;
	}
}

//2.回文是指正读反读均相同的字符序列，如“abba”和“abdba”均是回文，但“good”不是回文。
//  试写一个算法判定给定的字符序列是否为回文（提示：将一半字符入栈）
#define MAXSIZE 100
//定义一个顺序栈指针
typedef struct HuiStack
{
	char* base;
	char* top;
	int stacksize;  //定义栈可用的最大容量
}HuiStack;
void InitHui(HuiStack* H)
{
	H->base = (char*)malloc(sizeof(char) * MAXSIZE);
	H->top = H->base;
	H->stacksize = MAXSIZE;
}
int IsHui(char* str)
{
	HuiStack H;
	InitHui(&H);
	int len = strlen(str);
	for (int i = 0; i < len / 2; i++)
	{
		H.base[i] = *str++;
		H.top++;
	}
	if (len % 2 == 0)  //len为偶数，不需要跳过中间元素比较
	{
		while (*str && *--(H.top) == *str++) { ; }
		//跳出循环有两种可能：
		//1.str到头了  2.字符串两边元素不对称
		if (!(*str))  //如果str到头了,说明是回文
			return 1;
		else         //如果不是则不是回文
			return 0;
	}
	else   //len为奇数，要跳过中间元素再比较
	{
		str++;  //跳过中间元素
		while (*str && *--(H.top) == *str++) { ; }
		//跳出循环有两种可能：
		//1.str到头了  2.字符串两边元素不对称
		if (!(*str))  //如果str到头了,说明是回文
			return 1;
		else         //如果不是则不是回文
			return 0;
	}
}
//测试代码
//int main()
//{
//	char str[100];
//	gets_s(str, 100);
//	if (IsHui(str))
//		printf("是回文\n");
//	else
//		printf("不是回文\n");
//	return 0;
//}


//3.从键盘输入一个整数的序列：a1,a2,a3,....,an,试编写算法实现：用栈结构存储输入的整数，当ai!=-1时，将ai进栈；当ai=-1时，输出栈顶整数并出栈。
//  算法应对异常情况（入栈满等）给出相应的信息。
//定义一个链栈
typedef struct StackNode
{
	int a;
	struct StackNode* next;
}StackNode,*StackLink;
//初始化链栈
void InitStack(StackLink* S)
{
	*S = NULL;
}
//进栈
void PushStack(StackLink* S,int a)
{
	StackNode* p = (StackNode*)malloc(sizeof(StackNode));
	p->a = a;
	p->next = *S;
	*S = p;
}
//出栈
int PopStack(StackLink* S)
{
	if (*S== NULL)
	{
		printf("栈已空\n");
		return -1;
	}
	StackNode* f = *S;
	int e = (*S)->a;
	*S = (*S)->next;
	free(f), f = NULL;
	return e;
}
void InOutStack()
{
	StackLink S;
	InitStack(&S);
	int ret;
	for(int i=1;i<=5;i++)
	{
		printf("输入数字：");
		scanf("%d", &ret);
		if(ret!=-1)
			PushStack(&S, ret);
		else
		{
			if (PopStack(&S) == -1)
				break;
			else
				printf("栈顶数字为：%d\n", PopStack(&S));
		}
	}
}


//4.从键盘上输入一个后缀表达式，试编写算法计算表达式的值。规定：逆波兰表达式的长度不超过一行，以“$”作为输入结束，操作数之间用空格分隔
//  操作符只可能有+，-，*，/ 四种运算。例如：234 34+2*$
// 逆波兰表达式的运算符是按计算顺序排序的，所以不需要运算符栈
//此题与之前表达式求值相似，需要创建一个操作数栈
typedef struct OPND  //创建操作数栈
{
	float a;
	struct OPND* next;
}OPND;
void InitOPND(OPND** O)
{
	*O = (OPND*)malloc(sizeof(OPND));
	*O = NULL;
}
//入栈
void Push(OPND** O,float e)
{
	OPND* p = (OPND*)malloc(sizeof(OPND));
	p->a = e;
	p->next = *O;
	*O = p;
}
//出栈
float Pop(OPND** O)
{
	if (!O)
	{
		printf("栈为空\n");
		return -1;
	}
	OPND* f = *O;
	float e = (*O)->a;
	*O = (*O)->next;
	free(f), f = NULL;
	return e;
}
//获取栈顶元素
float GetTop(OPND** O)
{
	if (!*O)
	{
		printf("栈为空");
		return -1;
	}
	float e = (*O)->a;
	return e;
}
void CalPoland(char* str)
{
	OPND* O;
	InitOPND(&O);
	char ch;
	float result=0;
	int scale;  //result用来合并字符数字，scale用来记录小数规模
	float a, b;  //a,b用来计算减法和除法，因为减法和除法要分先后顺序
	while ((ch = *str++) != '\0')
	{
		if((ch >= '0' && ch <= '9')||ch=='.')   //读取到的字符是数字或者小数则进入语句
		{
			while (ch >= '0' && ch <= '9')    //如果是数字字符则计算result
			{
				result = result * 10 + ch - '0';
				ch = *str++;
			}
			if (ch == '.')   //读取出来的字符是小数点，则进入语句，如果没有小数点则直接得到拼接的整数
			{   //处理小数
				scale = 1;
				while ((ch = *str++) != ' ')
				{
					result = result * 10 + ch - '0';    //先把字符全部转化为整数，再除以小数的规模，得到小数
					scale = scale * 10;
				}
				result = result / scale;
			}
			Push(&O, result);    //最后得到的结果存到栈中
			result = 0;
		}
		else   //如果读到的不是数字或者小数点，而是运算符或者空格则进入else
		{
			switch (ch)
			{
			case ' ':
				break;
			case '+':
				Push(&O, Pop(&O) + Pop(&O));
				break;
			case '-':
				a = Pop(&O);
				b = Pop(&O);
				Push(&O, b - a);
				break;
			case '*':
				Push(&O, Pop(&O) * Pop(&O));
				break;
			case '/':
				a = Pop(&O);
				b = Pop(&O);
				Push(&O, b / a);
				break;
			default:
				break;
			}
		}
	}
	printf("%f", GetTop(&O));
}
//测试代码
int main()
{
	char str[1024];
	gets_s(str, 1024);
	CalPoland(str);
	return 0;
}


//5.假设以I和O分别表示入栈和出栈操作。栈的初态和终态均为空，入栈和出栈的操作序列可表示为仅由I和O组成的序列
//  称可以操作的序列为合法序列，否则称为非法序列
//写出一个算法，判定所给的操作序列是否合法。若合法，返回true，否则返回false。（假定被判定的操作序列已存入一维数组中）
int Islegal(char* str)
{
	//入栈和出栈的次数相同，且随着数组的遍历出栈的次数不超过入栈的次数
	int i = 0;
	int j = 0;  //i和j分别记录入栈和出栈的次数
	char ch;
	while ((ch = *str++) != '\0')
	{
		if (ch == 'I')   
			i++;
		if (ch == 'O')
			j++;
		if (j > i)   //出栈的次数不能大于入栈的次数，否则非法
			return 0;
	}
	if (i == j)   //题目规定栈的初态和终态为空，所以入栈和出栈的次数要相等
		return 1;
	else
		return 0;
}
//int main()
//{
//	char str[10] = "IOIIOIOO";
//	int ret=Islegal(str);
//	if (ret)
//		printf("合法序列\n");
//	else
//		printf("非法序列\n");
//	return 0;
//}