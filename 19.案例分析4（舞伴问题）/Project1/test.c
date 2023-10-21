#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//4.������⣺
//���������⣬�жӺ�Ů�ӵĶ�ͷ������Գ���顣����ʿ��Ůʿ��Ϊ���ӣ���ͷԪ����ԣ�ֱ��һ����Ϊ��Ϊֹ��
//���ĳ�����еȴ�����ߣ�������˶������ڶ�ͷ�ĵȴ��ŵ����������˽�����һ��������ʼ��һ���ɻ��������

//������������Ů�������̶��ģ��������ӻ���٣��ʲ���˳����������
#define PEOPLEMAX 8   //��������������
typedef struct   //����һ�����ˡ�������
{
	char name[20];
	char sex;   //F����Ů�ԣ�M��������
}Person;
typedef struct Queue  //����˳�����
{
	Person* base;
	int front;
	int rear;
}SqQueue;
//��ʼ������
void InitQueue(SqQueue* Q)
{
	Q->base = (Person*)malloc(sizeof(Person)*PEOPLEMAX);
	if (!Q->base)
	{
		perror("malloc error");
		return;
	}
	Q->front = Q->rear = 0;
}
//���
void EnQueue(SqQueue* Q,Person per)
{
	if ((Q->rear + 1) % PEOPLEMAX == Q->front)
	{
		printf("����\n");
		return;
	}
	Q->base[Q->rear] = per;
	Q->rear = (Q->rear + 1) % PEOPLEMAX;
}
//����
Person  DelQueue(SqQueue* Q)
{
	if (Q->front == Q->rear)
	{
		printf("�ӿ�\n");
		return;
	}
	Person p = Q->base[Q->front];
	Q->front = (Q->front + 1) % PEOPLEMAX;
	return p;
}
//�ж϶��Ƿ�Ϊ��
int IsEmpty(SqQueue* Q)
{
	if (Q->front == Q->rear)
		return 1;
	else
		return 0;
}
//��ȡ��ͷԪ��
Person GetTop(SqQueue* Q)
{
	if (Q->front == Q->rear)
	{
		printf("�ӿ�\n");
		return;
	}
	Person peo = Q->base[Q->front];
	return peo;
}
//�������˷ֳ���Ů����
void DancerPatner(Person dancers[], int num)
{
	SqQueue Mdancers, Fdancers;
	InitQueue(&Mdancers);
	InitQueue(&Fdancers);
	//�����߷ֱ�����Ů����
	for (int i = 0; i < num; i++)
	{
		if (dancers[i].sex == 'M')
			EnQueue(&Mdancers, dancers[i]);
		else
			EnQueue(&Fdancers, dancers[i]);
	}
	printf("��Ϊ�������ˣ�\n");
	while (!IsEmpty(&Mdancers) && !IsEmpty(&Fdancers))  //�ж�Ů�Ӷ�û�յĻ�
	{
		Person man = DelQueue(&Mdancers);  //��ͷ����ʿ�������ͷ��Ůʿƥ��
		Person lady = DelQueue(&Fdancers);  //��ͷŮʿ����
		printf("�У�%s\tŮ��%s\n", man.name, lady.name);
	}
	if (!IsEmpty(&Mdancers)) //���Ů�ӿ���
	{
		Person peo = GetTop(&Mdancers);  //��ȡ�ڶ�ͷ����ʿ
		printf("��һ���������Ȼ��������ʿ�ǣ�%s\n", peo.name);
	}
	else           //����жӿ���
	{
		Person peo = GetTop(&Fdancers);  //��ȡ�ڶ�ͷ��Ůʿ
		printf("��һ���������Ȼ������Ůʿ�ǣ�%s\n", peo.name);
	}

}
int main()
{
	int num = 10;    //�μ���������
	Person dancers[10] = { 
		{"����",'M'},{"����",'M'},{"����",'M'},{"�Զ�",'M'},{"��һ",'M'},{"����",'M'},
		{"����ӱ",'F'},{"��÷",'F'},{"������",'F'},{"������",'F'}};
	DancerPatner(dancers, num);
	return 0;
}
