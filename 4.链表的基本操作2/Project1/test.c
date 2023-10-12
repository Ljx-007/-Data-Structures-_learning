#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct Student  //�ȴ���һ��ѧ������
{
	char num[10];
	char name[8];
	int score;
}Stu;
typedef struct Lnode  //�ٴ���һ������������
{
	Stu data;
	struct Lnode* next; //��һ�����ĵ�ַ
}Lnode, * LinkList;

//�����ȡֵ

//�Լ�д��
//Stu GetElem_L(LinkList L, int num)   //numΪҪ��ȡ�������еĵ�num��Ԫ��
//{
//	int count = 0;
//	Lnode* p = L;
//	if (num < 0)
//	{
//		printf("��ʹ����ȷ����ţ�");
//		return;
//	}
//	while (p)
//	{
//		p = p->next;
//		count++;
//		if (count == num)
//			return p->data;
//	}
//	if (num > count)
//	{
//		printf("û�����Ԫ��\n");
//		return;
//	}
//}

//����д��
void GetElem_L(LinkList L, int i, Stu* e)  //��������ȡ����ֵ
{
	Lnode* p = L->next;  //����pֱ��ָ����Ԫ����ַ
	int j = 1;
	while (p && j < i)  //���pΪ��ֵ���������i���Ϸ�������0��-1�����޷�����ѭ��
	{
		p = p->next, j++;
	}
	//����ѭ�������ֿ���
	//1.pΪ��ֵ����������������һ����������
	//2.�����iΪ���Ϸ��������0��Ԫ�ػ��ߵ�-1��Ԫ�ص�
	//3.�������˵�i��Ԫ�أ�j==i��
	if (!p || j > i)  //����if����������1.pΪ��ֵ��!p��Ϊ���㣬����ѭ������Ϊ������������һ��Ԫ�أ���û�����������ҪѰ�ҵ�Ԫ����Ŵ������е�Ԫ�ظ���
		             //                   2.j�ǲ����ܴ���i�ģ���Ϊ����ʱj==iʱ������ѭ���ˣ��������j>i,˵��i���Ϸ�����һ��С��1��ֵ
	{
		printf("��Ų��Ϸ���û�д�Ԫ��\n");
		return;
	}
	*e = p->data;  //ִ�е�����˵��j==i���ҵ���Ԫ�أ����Ը�ֵ
}

//����Ĳ���
void InsertList(LinkList L,int i, Lnode* e)  //eΪҪ����Ľ���ַ
{
	Lnode* p = L;  //���ǵ�����Ľ����ܻ���뵽��һ��λ�ó�Ϊ��Ԫ��㣬����p��ͷ��㿪ʼ
	int j = 0;    
	//Ҫ�����i��λ�ã�����Ҫ���ҵ���i-1��Ԫ��
	while (p && i-1 > j)  
	{
		p = p->next, j++;
	}
	if (!p && j > i-1)  
	{
		printf("û�����Ԫ��!\n");
		return;
	}
	e->next = p->next;  //������½���ָ����ָ��ԭ��������һ������ַ�������ַ����ԭ������ָ������
	p->next = e;      //����һ���½���ԭ������ָ����ҲҪ�������ݣ�����Ϊ�½��ĵ�ַ����e
}
int main()
{
	LinkList L;

	return 0;
}