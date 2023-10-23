#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//1.�����Ϊ0��1������ջ�����һ������ռ�V[m]�У�ջ�׷ֱ�����������ˡ�����0��ջ��ջ��ָ��top[0]����-1ʱ��ջΪ�գ�����1��ջ��ջ��ָ��top[1]����mʱ
//��ջΪ�ա�����ջ�����������м��������Ա�д˫ջ��ʼ�����ж�ջ�ա�ջ������ջ�ͳ�ջ���㷨�ĺ�����
//˫ջ���ݽṹ�Ķ������£�
typedef struct
{
	int top[2], bot[2];   //ջ����ջ��ָ��
	int* V;               //ջ����
	int m;                //ջ��������Ԫ�ظ���
}DblStack;
//˫ջ��ʼ��
void InitDblStack(DblStack* D)
{
	D->V = (int*)malloc(sizeof(int) * (D->m));
	D->top[0] =-1;
	D->top[1] =D->m;
	D->bot[0] = 0;
	D->bot[1] = D->m - 1;
}
//�ж�ջ��
int IsEmpty(DblStack* D)
{
	if (D->top[0] == -1 && D->top[1] == D->m)
		return 1;
	else
		return 0;
}
//�ж�ջ��
int IsFull(DblStack* D)
{
	if (D->top[0]+1 == D->top[1])
		return 1;
	else
		return 0;
}
//��ջ
void EnDblStack(DblStack* D)
{
	int answer;
	if (IsFull(D))
	{
		printf("ջ����");
		return;
	}
	printf("��0�Ż���1��ջ:");
	scanf("%d", &answer);
	switch (answer)
	{
	case 0:
		printf("�����ջ��Ԫ�أ�");
		scanf("%d", &(D->V[++D->top[0]]));
		break;
	case 1:
		printf("�����ջ��Ԫ�أ�");
		scanf("%d", &(D->V[--D->top[1]]));
		break;
	default:
		printf("�������\n");
		break;
	}
}
//��ջ
void DelDblStack(DblStack* D)
{
	int ret;
	if (IsEmpty(D))
	{
		printf("ջΪ��\n");
		return;
	}
	printf("��0�Ż���1��ջ��");
	scanf("%d", &ret);
	switch (ret)
	{
	case 0:
		if (D->top[0] == -1)
			printf("0��ջΪ��");
		else
			D->top[0]--;
		break;
	case 1:
		if (D->top[1] == D->m)
			printf("1��ջΪ��");
		else
			D->top[1]++;
		break;
	default:
		break;
	}
}

//2.������ָ������������ͬ���ַ����У��硰abba���͡�abdba�����ǻ��ģ�����good�����ǻ��ġ�
//  ��дһ���㷨�ж��������ַ������Ƿ�Ϊ���ģ���ʾ����һ���ַ���ջ��
#define MAXSIZE 100
//����һ��˳��ջָ��
typedef struct HuiStack
{
	char* base;
	char* top;
	int stacksize;  //����ջ���õ��������
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
	if (len % 2 == 0)  //lenΪż��������Ҫ�����м�Ԫ�رȽ�
	{
		while (*str && *--(H.top) == *str++) { ; }
		//����ѭ�������ֿ��ܣ�
		//1.str��ͷ��  2.�ַ�������Ԫ�ز��Գ�
		if (!(*str))  //���str��ͷ��,˵���ǻ���
			return 1;
		else         //����������ǻ���
			return 0;
	}
	else   //lenΪ������Ҫ�����м�Ԫ���ٱȽ�
	{
		str++;  //�����м�Ԫ��
		while (*str && *--(H.top) == *str++) { ; }
		//����ѭ�������ֿ��ܣ�
		//1.str��ͷ��  2.�ַ�������Ԫ�ز��Գ�
		if (!(*str))  //���str��ͷ��,˵���ǻ���
			return 1;
		else         //����������ǻ���
			return 0;
	}
}
//���Դ���
//int main()
//{
//	char str[100];
//	gets_s(str, 100);
//	if (IsHui(str))
//		printf("�ǻ���\n");
//	else
//		printf("���ǻ���\n");
//	return 0;
//}


//3.�Ӽ�������һ�����������У�a1,a2,a3,....,an,�Ա�д�㷨ʵ�֣���ջ�ṹ�洢�������������ai!=-1ʱ����ai��ջ����ai=-1ʱ�����ջ����������ջ��
//  �㷨Ӧ���쳣�������ջ���ȣ�������Ӧ����Ϣ��
//����һ����ջ
typedef struct StackNode
{
	int a;
	struct StackNode* next;
}StackNode,*StackLink;
//��ʼ����ջ
void InitStack(StackLink* S)
{
	*S = NULL;
}
//��ջ
void PushStack(StackLink* S,int a)
{
	StackNode* p = (StackNode*)malloc(sizeof(StackNode));
	p->a = a;
	p->next = *S;
	*S = p;
}
//��ջ
int PopStack(StackLink* S)
{
	if (*S== NULL)
	{
		printf("ջ�ѿ�\n");
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
		printf("�������֣�");
		scanf("%d", &ret);
		if(ret!=-1)
			PushStack(&S, ret);
		else
		{
			if (PopStack(&S) == -1)
				break;
			else
				printf("ջ������Ϊ��%d\n", PopStack(&S));
		}
	}
}


//4.�Ӽ���������һ����׺���ʽ���Ա�д�㷨������ʽ��ֵ���涨���沨�����ʽ�ĳ��Ȳ�����һ�У��ԡ�$����Ϊ���������������֮���ÿո�ָ�
//  ������ֻ������+��-��*��/ �������㡣���磺234 34+2*$
// �沨�����ʽ��������ǰ�����˳������ģ����Բ���Ҫ�����ջ
//������֮ǰ���ʽ��ֵ���ƣ���Ҫ����һ��������ջ
typedef struct OPND  //����������ջ
{
	float a;
	struct OPND* next;
}OPND;
void InitOPND(OPND** O)
{
	*O = (OPND*)malloc(sizeof(OPND));
	*O = NULL;
}
//��ջ
void Push(OPND** O,float e)
{
	OPND* p = (OPND*)malloc(sizeof(OPND));
	p->a = e;
	p->next = *O;
	*O = p;
}
//��ջ
float Pop(OPND** O)
{
	if (!O)
	{
		printf("ջΪ��\n");
		return -1;
	}
	OPND* f = *O;
	float e = (*O)->a;
	*O = (*O)->next;
	free(f), f = NULL;
	return e;
}
//��ȡջ��Ԫ��
float GetTop(OPND** O)
{
	if (!*O)
	{
		printf("ջΪ��");
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
	int scale;  //result�����ϲ��ַ����֣�scale������¼С����ģ
	float a, b;  //a,b������������ͳ�������Ϊ�����ͳ���Ҫ���Ⱥ�˳��
	while ((ch = *str++) != '\0')
	{
		if((ch >= '0' && ch <= '9')||ch=='.')   //��ȡ�����ַ������ֻ���С����������
		{
			while (ch >= '0' && ch <= '9')    //����������ַ������result
			{
				result = result * 10 + ch - '0';
				ch = *str++;
			}
			if (ch == '.')   //��ȡ�������ַ���С���㣬�������䣬���û��С������ֱ�ӵõ�ƴ�ӵ�����
			{   //����С��
				scale = 1;
				while ((ch = *str++) != ' ')
				{
					result = result * 10 + ch - '0';    //�Ȱ��ַ�ȫ��ת��Ϊ�������ٳ���С���Ĺ�ģ���õ�С��
					scale = scale * 10;
				}
				result = result / scale;
			}
			Push(&O, result);    //���õ��Ľ���浽ջ��
			result = 0;
		}
		else   //��������Ĳ������ֻ���С���㣬������������߿ո������else
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
//���Դ���
int main()
{
	char str[1024];
	gets_s(str, 1024);
	CalPoland(str);
	return 0;
}


//5.������I��O�ֱ��ʾ��ջ�ͳ�ջ������ջ�ĳ�̬����̬��Ϊ�գ���ջ�ͳ�ջ�Ĳ������пɱ�ʾΪ����I��O��ɵ�����
//  �ƿ��Բ���������Ϊ�Ϸ����У������Ϊ�Ƿ�����
//д��һ���㷨���ж������Ĳ��������Ƿ�Ϸ������Ϸ�������true�����򷵻�false�����ٶ����ж��Ĳ��������Ѵ���һά�����У�
int Islegal(char* str)
{
	//��ջ�ͳ�ջ�Ĵ�����ͬ������������ı�����ջ�Ĵ�����������ջ�Ĵ���
	int i = 0;
	int j = 0;  //i��j�ֱ��¼��ջ�ͳ�ջ�Ĵ���
	char ch;
	while ((ch = *str++) != '\0')
	{
		if (ch == 'I')   
			i++;
		if (ch == 'O')
			j++;
		if (j > i)   //��ջ�Ĵ������ܴ�����ջ�Ĵ���������Ƿ�
			return 0;
	}
	if (i == j)   //��Ŀ�涨ջ�ĳ�̬����̬Ϊ�գ�������ջ�ͳ�ջ�Ĵ���Ҫ���
		return 1;
	else
		return 0;
}
//int main()
//{
//	char str[10] = "IOIIOIOO";
//	int ret=Islegal(str);
//	if (ret)
//		printf("�Ϸ�����\n");
//	else
//		printf("�Ƿ�����\n");
//	return 0;
//}