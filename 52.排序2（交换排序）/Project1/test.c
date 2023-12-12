#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 20
typedef struct
{
	int key;
	char other;
}RedType;
typedef struct
{
	RedType r[MAXSIZE + 1];
	int lenth;
}SqList;
//��������
//ð������
void BubbleSort(SqList* L)
{
	for (int i = 1; i < L->lenth; i++)  //���� i
	{
		int flag = 1;										//����+�Ƚϴ���=Ԫ�ظ���----i+L->lenth-i=L->lenth
		for (int j = 1; j < L->lenth - i+1; j++)  //�Ƚϴ�����L->lenth-i
		{
			if (L->r[j].key > L->r[j + 1].key)
			{
				RedType tmp = L->r[j];
				L->r[j] = L->r[j + 1];
				L->r[j + 1] = tmp;
				flag = 0;
			}
		}
		if (flag == 1)
			break;
	}
}
//ð������ʱ�临�Ӷ�ΪO(n^2),�ռ临�Ӷ�ΪO(1)
//��������ʽ�洢�ṹ
//�㷨ƽ��ʱ�����ܱ�ֱ�Ӳ�������n�ϴ�ʱ����ʹ��

//��������
//����˼�룺��ȡһ��Ԫ��Ϊ���ģ����һ��Ԫ�أ������б���С��Ԫ����ǰ�ţ������������ţ��γ����������ӱ�
// �Ը��ӱ�����ѡ������Ԫ�ز�����ǰ���������ֱ���ӱ�Ԫ��ʣ��һ��������һ�ֵݹ�˼��
int Partition(SqList* L, int left, int right)   //�Ա��ڽ�������
{
	L->r[0] = L->r[left];   //leftһ��ָ����е�һ��Ԫ�أ������ʼ����һ��Ԫ�ط����ڱ�λ��
	while (left < right)  //������left<right������left<=right����Ϊ�������left��rightӦһָͬ��һ����λ��
	{               //�����left<=right����ô��whileѭ��ʱ����֪����leftָ���λ�û���rightָ���λ�ã��޷����ڱ����·Żؿ�λ�ã����Բ�����left<=right
		while (L->r[right].key >= L->r[0].key && left < right)  //�ӱ���Ҷ����������ֱ���ҵ�һ��Ԫ��С���м�Ԫ�أ��ڱ�����ͬʱҪ��֤left����>=right
			right--;
		L->r[left] = L->r[right];  //�ҵ����С���ڱ���Ԫ�ط������leftָ��Ŀ�λ��
		while (L->r[left].key <= L->r[0].key && left < right)  //�ӱ��������ұ�����ֱ���ҵ�һ��Ԫ�ش����м�Ԫ�أ��ڱ�����ͬʱҪ��֤left����>=right
			left++;
		L->r[right] = L->r[left];  //�ҵ���Ѵ����ڱ���Ԫ�ط����Ҷ�rightָ��Ŀ�λ��
	}
	L->r[left] = L->r[0];   //��������꽫�ڱ��Ż����Ŀ�λ�ã���ʱright��left��ָ���λ��
	return left;   //������λ�÷���
}
void Qsort(SqList* L, int left, int right)
{
	if (left < right)  //��֤�ӱ��ȴ���1
	{
		int privot = Partition(L,left,right);   //�ҵ�����λ��privot
		Qsort(L, left, privot - 1);  //�ݹ��������ӱ�
		Qsort(L, privot + 1, right);  //�ݹ��������ӱ�
	}
}
//Qsort������ƽ��ʱ�临�Ӷ�Ϊ O(log2 n),Partition������ƽ��ʱ�临�Ӷ�ΪO(n)
//���������㷨��ƽ��ʱ�临�Ӷ�ΪO(nlog2 n)���ռ临�Ӷ�ƽ�������ΪO(log2 n),����ΪO(n)
//��ƽ������ʱ����ԣ��������������������۵����������򷽷�����õ�һ�� ,��һ�ֲ��ȶ�����
//��������������ԭ��������������ļ�¼���н�������
//���������ǲ���Ȼ������Ȼ����������Խ�����ŵ�Խ�졣
