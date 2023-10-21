#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//任何一个表达式都是由操作数（operand）、运算符（operator）和界限符（delimiter）组成的
//操作数可以是常数，也可以是被说明为变量或常数的标识符
//运算符分为算术运算符，关系运算符和逻辑运算符3类
//基本界限符由左右括号和表达式结束符等。
//这里仅讨论简单算术表达式求值问题，只含+，-，*，/，四种运算符

//算术运算要遵守以下三条规则：
//（1）先乘除，后加减
//（2）从左到右运算
//（3）先括号内，后括号外

//根据以上三条规则，可以制定运算符号间的优先关系（具体参考书） 

//计算10位以内的数字（结果也只能是十位以内的数字）
//如果想要计算多位数，那么要将OPND栈改为int型的，读入数字字符拼成数字后放入栈内
//字符拼成数字的方法：
//假设要读取的字符为'"123"，先读入字符'1'，转换为数字1= '1'-'0'
//再读入字符'2',拼凑成数字十二：12=10*1+'2'-'0'
//再读入字符'3',拼凑成数字123=12*10+'3'-'0'
//以此类推就可以将字符数转化为整型数了
//如果是小数的话，则先按照整数处理，读取到小数后按规模再除以10的n次方即可
//如：123.45，先按照12345处理，然后再除以10^2

#define OPTRMAX 7  //定义运算符的最大个数
char optr[OPTRMAX] = { '+','-','*','/','(',')','#' };   //创建一个运算符数组，用来查找运算符
char priority[OPTRMAX][OPTRMAX] = {
	{'>','>','<','<','<','>','>'},
	{'>','>','<','<','<','>','>'},
	{'>','>','>','>','<','>','>'},     //优先级有bug，要改
	{'>','>','>','>','<','>','>'},
	{'<','<','<','<','<','=',0},
	{'>','>','>','>',0,'>','>'} ,//创建运算符优先级表
	{'<','<','<','<','<',0,'='}
};
//创建链栈
typedef struct StackNode
{
	char c;
	struct StackNode* next;
}StackNode,*StackLink;
//初始化链栈
void InitStack(StackLink* S)
{
	*S = (StackNode*)malloc(sizeof(StackNode));
	*S = NULL;
}
//入栈
void Push(StackLink* S, char ch)
{
	StackNode* p = (StackNode*)malloc(sizeof(StackNode));
	p->c = ch;
	p->next = *S;
	*S = p;
}
//出栈
char Pop(StackLink* S)
{
	if (*S)
	{
		StackNode* p = *S;
		*S = (*S)->next;
		char c = p->c;
		free(p), p = NULL;
		return c;
	}
	else
	{
		printf("栈为空\n");
		return -1;
	}
}
//判断ch是否为运算符
int IsOPTR(char ch)
{
	for (int i = 0;i < OPTRMAX; i++)
	{
		if (ch == optr[i])  //让optr数组成为全局变量，可以完美实现IsOPTR函数中不需要传参optr就能判断ch是否为运算符的功能
			return i;
	}
	return -1;
}
//获取栈顶元素
char GetTop(StackLink* S)
{
	if (*S != NULL)
		return (*S)->c;
}

//判断运算符栈的栈顶元素与运算符的优先级
char Precede(char ch1, char ch2)
{
	int x = IsOPTR(ch1);  //x为ch1在optr数组中的下标
	int y = IsOPTR(ch2);  //y为ch2在optr数组中的下表
	return priority[x][y];  //从优先级表中找到ch1，ch2的优先级符号
}

//将两个字符数字进行运算
char Operate(char a, char ope, char b)
{
	//将字符数字转化为数字
	//也可以使用atoi函数，int atoi(const char* str) ，传入要转换为整数的字符串，返回一个整型值
	//如果没有执行有效的转换，返回0
	//这里采用atoi函数好一点，因为当a，b为两位数字符数字时减'0'的方法无效了
	int a1 = atoi(&a);  //int a1 = a - '0';   
	int b1 = atoi(&b);  //int b1 = b - '0';  
	int answer;
	char str[10];
	switch (ope)
	{
	case '+':
		answer = a1 + b1;
		break;
	case '-':
		answer = a1 - b1;
		break;
	case '*':
		answer = a1 * b1;
		break;
	case '/':
		answer = a1 / b1;
		break;
	default:
		break;
	}
	_itoa(answer,str,10);  //itoa与atoi函数相反，itoa是将数字转化为字符数字，char* itoa(int n,char* str,int radix)
	                            //n为要转换成字符的整数，str是转换后指向字符串的指针，radix即要转换的进制数
	return str[0];  //itoa返回的指针指向字符数组，如果计算的结果是两位数，则此方法无效
}
char Evaluate(char str[])
{
	StackLink OPTR;  //创建一个链栈存放运算符
	StackLink OPND;  //创建一个链栈存放操作数和运算结果
	InitStack(&OPTR);
	InitStack(&OPND);
	Push(&OPTR, '#');   //先把开始表达式的#放入运算符栈，不然后面比较优先级时没有得比较
	                    //计算表达式以#开头，以#结尾
	char ch,ope;  
	while ((ch = *str++) != '\0')
	{
		if (IsOPTR(ch) == -1)   //判断ch是否为运算符，如果不是，就存进OPND栈中
			Push(&OPND, ch);
		else
		{   //如果是运算符，则与运算符OPTR栈的栈顶元素比较优先级
			switch (Precede(GetTop(&OPTR),ch))  //Precede是判定运算符栈的栈顶元素与运算符之间优先级关系的函数，返回值为'>'或'<'或'='
			{
			case '>':   // 如果运算符栈的栈顶元素优先级大于运算符ch
				ope=Pop(&OPTR);//则弹出栈顶的运算符
				char b = Pop(&OPND);  //先弹出的数为表达式靠后的数字
				char a = Pop(&OPND);  //后弹出的数为表达式靠前的数字
				char c = Operate(a,ope,b);
				Push(&OPND, c);
				break;
			case '<':   //如果运算符的栈顶元素优先级小于ch
				Push(&OPTR, ch);   //则ch入栈
				break;
			case '=':   //如果优先级相等，根据之前定义的优先级表可知，栈顶元素和ch都是括号，且栈顶元素是 '(' , ch是 ')'
				//且说明括号内的算式都运算完了，没有运算符了，括号内只有数字
				Pop(&OPTR); //弹出栈顶元素'('，继续读入下一个ch，进行下一步运算
				break;
			default:
				break;
			}
		}
		
	}
	return GetTop(&OPND);  //最后获取操作数栈栈顶位置的元素就是最终运算结果
}
int main()
{
	char str[1024];
	char c;
	printf("输入表达式（10以内）：");
	scanf("%s", str);
	c=Evaluate(str);
	printf("%c", c);
	return 0;
}
