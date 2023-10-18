#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//ջ�Ķ��壺
//ջ��stack�����޶����ڱ�β���в����ɾ�����������Ա����к���ȳ����ص�
//Ӧ�ó�����
//���Ƶ�ת�������ŵ�ƥ����飬���ʽ��ֵ������
//�洢�ṹ��
// ˳��ջ����ջ


//˳��ջ�ı�ʾ
//˳��ջ�Ĵ洢��ʽ��˳�����ͬ������һ�������Ĵ洢��Ԫ�ṹ���δ�Ŵ�ջ�׵�ջ��������Ԫ�أ�ջ��һ���ڵ͵�ַ�ˡ�
//ͬʱջ��Ҫ����topָ�룬ָ��ջ��λ�ã�������baseָ�룬ָ��ջ��λ��
//Ϊ�˲������㣬ͨ��top��ָ��Ϊջ��Ԫ��֮�ϵ��±�λ��
//���⣬��stacksize��ʾ˳��ջ��ʹ�õ��������

//����һ��ջ
#define MAXSIZE 20   //����˳��ջ���������
typedef struct Sqstack
{
	int* top;    //��������ջԪ������Ϊint������topָ��ָ��ջ����baseָ��ջ��
	int* base;
	int stacksize;
}Sqstack;

//ջ�ĳ�ʼ��
void InitStack(Sqstack* S)
{
	S->base = (int*)malloc(sizeof(int) * MAXSIZE);  //����һ���ַ�����Ŀռ�
	if (!S->base)
	{
		perror("creat stack error");
		return;
	}
	S->top = S->base;   //top=base�������ʼ����ջΪ��ջ
	S->stacksize = MAXSIZE;
}

//�ж�ջ�Ƿ�Ϊ��
int StackEmpty(Sqstack S)
{
	if (S.base == S.top)
		return 1;
	else
		return 0;
}

//��˳��ջ����
int LenStack(Sqstack S)
{
	return S.top - S.base;
}
//���˳��ջ
void Clear(Sqstack* S)
{
	if (S->base)
		S->top = S->base;  //��topָ��ָ��ջ�ף����ù�ջ֮ǰ����ʲô���´洢�����ֻḲ�ǵ�֮ǰ�����ݣ����Կ���ֱ�ӵ��ɿ�ջ
	else
		printf("ջ������\n");
}

//����˳��ջ
void Destroy(Sqstack* S)
{
	free(S->base), S->base = NULL;
	S->top = NULL;  //��top��base���ÿ�
	S->stacksize = 0;  //ջ������Ϊ0
}

//˳��ջ����ջ
void Push(Sqstack* S)
{
	int ret, n;
	char str[1001];
	printf("�������ջ��Ԫ�ظ�����");
again:
	ret = scanf("%d", &n);
	if (!ret)
	{
		while (gets_s(str, 1000))
		{
			printf("��������ȷ�����֣�");
			goto again;
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (S->top - S->base == S->stacksize)   //�ж�ջ�Ƿ�����
		{
			printf("ջ����\n");
			break;
		}
		printf("�������ջ������(int��)��");
	again2:
		ret = scanf("%d", S->top++);   //������԰Ѹ�S->topָ��Ŀռ丳ֵ��topָ�������ϲ���һ��д��û������
		if (!ret)
		{
			while (gets_s(str, 1000))
			{
				printf("��������ȷ�����֣�");
				goto again2;
			}
		}
		//S->top++;
	}
}

//˳��ջ�ĳ�ջ--��ջ��Ԫ��ɾ��
int Pop(Sqstack* S)   //���س�ջɾ�����Ǹ�Ԫ��
{
	if (S->top == S->base)
	{
		printf("ջ�ǿյ�\n");
		return -1;
	}
	S->top--;
	int e = *(S->top);
	//�������д���ɸ�Ϊ
	//int e=*--S->top; 
	return e;
}

//˳��ջȡջ��Ԫ��
int GetTop(Sqstack S)
{
	if (S.top != S.base)   //���ջ���ǿյ�
		return *(S.top - 1);  //topָ�벻��
	else
	{
		printf("ջ�ǿյ�\n");
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