#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//2.����ƥ��ļ���
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
//�ж�ջ�Ƿ�Ϊ��
int IsEmpty(StackLink* S)
{
	if (*S == NULL)
		return 1;
	else
		return 0;
}
//��ȡջ��Ԫ�� 
char GetTop(StackLink* S)
{
	if (*S)  //���ջ����Ϊ�գ��򷵻�ջ��Ԫ��
	{
		return (*S)->c;
	}
	else
	{
		printf("ջΪ��\n");
		return '-1';
	}
}
//��ջ
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
//��ջ
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
		printf("ջΪ��");
		return '-1';
	}
}
void check(StackLink* S)
{
	char str[1024];
	printf("�������ż����Ƿ�ƥ�䣺\n");
	scanf("%s", str);
	char* ptr = str;
	//����һ��flag���������ж��Ƿ�ƥ��ɹ�,1����ƥ��ɹ���0����ƥ��ʧ��
	int flag = 1;
	char ch;
	//����ѭ��������������һ���������ַ���û��ĩβ��һ��������flag=1����ǰ������Ŷ�ƥ��ɹ���
	while ((ch=*ptr++) != '\0' && flag)   //һ��һ����ȡ���ţ�һֱ����ĩβ���˳�ѭ��
	{
		switch (ch)
		{
		case '(':
		case '[':   //����'(','[','{'��ֱ����ջ
		case '{':
			Push(S, ch);
			break;
		case ')':
			if (!IsEmpty(S) && GetTop(S) == '(')   //���ջ��Ϊ�գ���ջ��Ԫ��Ϊ(�����ջ
				Pop(S);
			else
				flag = 0;  //���ջΪ�ջ���ջ��Ԫ�ز�Ϊ(����ƥ��ʧ��
			break;
		case ']':
			if (!IsEmpty(S) && GetTop(S) == '[')      //�� ( ͬ��
				Pop(S);
			else 
				flag = 0;
			break;
		case '}':
			if (!IsEmpty(S) && GetTop(S) == '{')   //�� ( ͬ��
				Pop(S);
			else
				flag = 0;
			break;
		default:
			break;
		}
	}
	if (flag == 1)
		printf("ƥ��ɹ�!\n");
	else
		printf("ƥ��ʧ��!\n");
}
int main()
{
 	StackLink S = InitStack();
	check(&S);
	return 0;
}