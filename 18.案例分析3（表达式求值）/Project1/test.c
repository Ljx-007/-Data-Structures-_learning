#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//�κ�һ�����ʽ�����ɲ�������operand�����������operator���ͽ��޷���delimiter����ɵ�
//�����������ǳ�����Ҳ�����Ǳ�˵��Ϊ���������ı�ʶ��
//�������Ϊ�������������ϵ��������߼������3��
//�������޷����������źͱ��ʽ�������ȡ�
//��������ۼ��������ʽ��ֵ���⣬ֻ��+��-��*��/�����������

//��������Ҫ����������������
//��1���ȳ˳�����Ӽ�
//��2������������
//��3���������ڣ���������

//���������������򣬿����ƶ�������ż�����ȹ�ϵ������ο��飩 

//����10λ���ڵ����֣����Ҳֻ����ʮλ���ڵ����֣�
//�����Ҫ�����λ������ôҪ��OPNDջ��Ϊint�͵ģ����������ַ�ƴ�����ֺ����ջ��
//�ַ�ƴ�����ֵķ�����
//����Ҫ��ȡ���ַ�Ϊ'"123"���ȶ����ַ�'1'��ת��Ϊ����1= '1'-'0'
//�ٶ����ַ�'2',ƴ�ճ�����ʮ����12=10*1+'2'-'0'
//�ٶ����ַ�'3',ƴ�ճ�����123=12*10+'3'-'0'
//�Դ����ƾͿ��Խ��ַ���ת��Ϊ��������
//�����С���Ļ������Ȱ�������������ȡ��С���󰴹�ģ�ٳ���10��n�η�����
//�磺123.45���Ȱ���12345����Ȼ���ٳ���10^2

#define OPTRMAX 7  //�����������������
char optr[OPTRMAX] = { '+','-','*','/','(',')','#' };   //����һ����������飬�������������
char priority[OPTRMAX][OPTRMAX] = {
	{'>','>','<','<','<','>','>'},
	{'>','>','<','<','<','>','>'},
	{'>','>','>','>','<','>','>'},     //���ȼ���bug��Ҫ��
	{'>','>','>','>','<','>','>'},
	{'<','<','<','<','<','=',0},
	{'>','>','>','>',0,'>','>'} ,//������������ȼ���
	{'<','<','<','<','<',0,'='}
};
//������ջ
typedef struct StackNode
{
	char c;
	struct StackNode* next;
}StackNode,*StackLink;
//��ʼ����ջ
void InitStack(StackLink* S)
{
	*S = (StackNode*)malloc(sizeof(StackNode));
	*S = NULL;
}
//��ջ
void Push(StackLink* S, char ch)
{
	StackNode* p = (StackNode*)malloc(sizeof(StackNode));
	p->c = ch;
	p->next = *S;
	*S = p;
}
//��ջ
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
		printf("ջΪ��\n");
		return -1;
	}
}
//�ж�ch�Ƿ�Ϊ�����
int IsOPTR(char ch)
{
	for (int i = 0;i < OPTRMAX; i++)
	{
		if (ch == optr[i])  //��optr�����Ϊȫ�ֱ�������������ʵ��IsOPTR�����в���Ҫ����optr�����ж�ch�Ƿ�Ϊ������Ĺ���
			return i;
	}
	return -1;
}
//��ȡջ��Ԫ��
char GetTop(StackLink* S)
{
	if (*S != NULL)
		return (*S)->c;
}

//�ж������ջ��ջ��Ԫ��������������ȼ�
char Precede(char ch1, char ch2)
{
	int x = IsOPTR(ch1);  //xΪch1��optr�����е��±�
	int y = IsOPTR(ch2);  //yΪch2��optr�����е��±�
	return priority[x][y];  //�����ȼ������ҵ�ch1��ch2�����ȼ�����
}

//�������ַ����ֽ�������
char Operate(char a, char ope, char b)
{
	//���ַ�����ת��Ϊ����
	//Ҳ����ʹ��atoi������int atoi(const char* str) ������Ҫת��Ϊ�������ַ���������һ������ֵ
	//���û��ִ����Ч��ת��������0
	//�������atoi������һ�㣬��Ϊ��a��bΪ��λ���ַ�����ʱ��'0'�ķ�����Ч��
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
	_itoa(answer,str,10);  //itoa��atoi�����෴��itoa�ǽ�����ת��Ϊ�ַ����֣�char* itoa(int n,char* str,int radix)
	                            //nΪҪת�����ַ���������str��ת����ָ���ַ�����ָ�룬radix��Ҫת���Ľ�����
	return str[0];  //itoa���ص�ָ��ָ���ַ����飬�������Ľ������λ������˷�����Ч
}
char Evaluate(char str[])
{
	StackLink OPTR;  //����һ����ջ��������
	StackLink OPND;  //����һ����ջ��Ų�������������
	InitStack(&OPTR);
	InitStack(&OPND);
	Push(&OPTR, '#');   //�Ȱѿ�ʼ���ʽ��#���������ջ����Ȼ����Ƚ����ȼ�ʱû�еñȽ�
	                    //������ʽ��#��ͷ����#��β
	char ch,ope;  
	while ((ch = *str++) != '\0')
	{
		if (IsOPTR(ch) == -1)   //�ж�ch�Ƿ�Ϊ�������������ǣ��ʹ��OPNDջ��
			Push(&OPND, ch);
		else
		{   //���������������������OPTRջ��ջ��Ԫ�رȽ����ȼ�
			switch (Precede(GetTop(&OPTR),ch))  //Precede���ж������ջ��ջ��Ԫ���������֮�����ȼ���ϵ�ĺ���������ֵΪ'>'��'<'��'='
			{
			case '>':   // ��������ջ��ջ��Ԫ�����ȼ����������ch
				ope=Pop(&OPTR);//�򵯳�ջ���������
				char b = Pop(&OPND);  //�ȵ�������Ϊ���ʽ���������
				char a = Pop(&OPND);  //�󵯳�����Ϊ���ʽ��ǰ������
				char c = Operate(a,ope,b);
				Push(&OPND, c);
				break;
			case '<':   //����������ջ��Ԫ�����ȼ�С��ch
				Push(&OPTR, ch);   //��ch��ջ
				break;
			case '=':   //������ȼ���ȣ�����֮ǰ��������ȼ����֪��ջ��Ԫ�غ�ch�������ţ���ջ��Ԫ���� '(' , ch�� ')'
				//��˵�������ڵ���ʽ���������ˣ�û��������ˣ�������ֻ������
				Pop(&OPTR); //����ջ��Ԫ��'('������������һ��ch��������һ������
				break;
			default:
				break;
			}
		}
		
	}
	return GetTop(&OPND);  //����ȡ������ջջ��λ�õ�Ԫ�ؾ�������������
}
int main()
{
	char str[1024];
	char c;
	printf("������ʽ��10���ڣ���");
	scanf("%s", str);
	c=Evaluate(str);
	printf("%c", c);
	return 0;
}
