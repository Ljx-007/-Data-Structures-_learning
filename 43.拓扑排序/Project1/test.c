#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define MVNum 100
//AOV����Active On Vertex��--�Զ����ʾ�������ʾ�֮���������Լ��ϵ����������ͼ��Ϊ�������ʾ�������
// AOV���У���Ӧ�ó������򻷣���Ϊ���ڻ���������ζ��ĳ��Ӧ���Լ�Ϊ�Ⱦ�����������Ȼ�ǻ����ġ�
//AOE����Active On Edge�� --�Ի���ʾ����Զ����ʾ��Ŀ�ʼ������¼�����������ͼ��Ϊ���߱�ʾ�������
//��������
//����������ǽ�AOV-�������ж����ų�һ���������У����������㣺����AOV-�����ɶ���vi������vj��һ��·�������ڸ����������еĶ���vi�ض��ڶ���vj֮ǰ��
//��������Ĺ��̣�
//1.������ͼ��ѡ��һ����ǰ���Ķ��㲢�����
//2.��ͼ��ɾ���ö������������Ϊβ�Ļ����������Ļ�����
//3.�ظ��������裬ֱ��������û��ǰ���ĵ�
//4.���������ͼӦΪ�����޻�ͼ���������Ķ�����С������ͼ�Ķ���������˵������ͼ�д��ڻ�����������Ķ�������Ϊ��������

//ʵ����������Ĺ��̣��ɲ����ڽӱ���Ϊ����ͼ�Ĵ洢�ṹ
//�㷨��ʵ��Ҫ���룺
//һά����indegree[i]����Ÿ�������ȣ�û��ǰ���Ķ���������Ϊ0�Ķ��㣬ɾ�����Ϊ0�Ķ���ʱ����ȵĻ�����Ӧ�Ķ�������-1
//ջS������������Ϊ0�Ķ��㣬�����ɱ����ظ�ɨ������indegree������Ϊ0�Ķ���
//һά����topo[i]����¼�������еĶ������
typedef struct Vnode
{
	char v;
	struct Arcnode* first;
}Vnode;
typedef struct Arcnode
{
	int adjvex;
	struct Arcnode* next;
}Arcnode;
typedef struct
{
	Vnode Vlist[MVNum];
	int vexnum, arcnum;
}AMLGraph;
//����˳��ջ
typedef struct Stack
{
	int* base;
	int* top;
	int sizemax;
}Stack;
void InitStack(Stack* S)
{
	S->base = malloc(sizeof(int) * MVNum);
	S->top = S->base;
	S->sizemax = MVNum;
}
void Push(Stack* S, int  e)
{
	if ((S->top - S->base) == S->sizemax)
	{
		printf("ջ��\n");
		return;
	}
	*S->top = e;
	S->top++;
}
int Pop(Stack* S)
{
	if (S->top == S->base)
	{
		printf("ջ��\n");
		return -1;
	}
	int e = *--S->top;
	return e;
}
int IsEmpty(Stack* S)
{
	if (S->top == S->base)
		return 1;
	else
		return 0;
}
int Located(char v, AMLGraph* G)
{
	for (int i = 0; i < G->vexnum; i++)
	{
		if (v == G->Vlist[i].v)
			return i;
	}
	return -1;
}
void CreatYXW(AMLGraph* G)
{
	char c;
	printf("���붥�����ͱ�����");
	scanf("%d%d", &G->vexnum, &G->arcnum);
	for (int i = 0; i < G->vexnum; i++)
	{
		printf("���붥����Ϣ��");
		while ((c = getchar()) != '\n') { ; }
		scanf("%c", &G->Vlist[i].v);
		G->Vlist[i].first = NULL;
	}
	for (int i = 0; i < G->arcnum; i++)
	{
		char v1, v2;
		printf("��������˳�������������㣺");
		while ((c = getchar()) != '\n') { ; }
		scanf("%c %c", &v1, &v2);
		int m = Located(v1, G);
		int n = Located(v2, G);
		Arcnode* p = malloc(sizeof(Arcnode));
		p->adjvex = n;
		p->next = G->Vlist[m].first;
		G->Vlist[m].first = p;
	}
}
//��������ͼ��ÿ����������
void Findindegree(AMLGraph* G, int* indegree)
{
	for(int i=0;i<G->vexnum;i++)   //���ѭ����������������indegree��
	{
		int count = 0;   //count��������ÿ����������
		for (int j = 0; j < G->vexnum; j++)   //���ѭ�������������ж���ı߱������������
		{
			Arcnode* p = G->Vlist[j].first;   //�ӵ�һ������ı߱�ʼ����
			while (p)
			{
				if (p->adjvex == i)   //������ȵĶ���Ϊi��˵������i����ȣ���count+1
					count++;
				p = p->next;
			}
		}//forѭ��������������ж���ĳ��ȶ��������ˣ�������i����Ȳ�����ϣ������Ϊcount
		indegree[i] = count;  //�����������indegree��
	}
}
//��������
int TopologicalSort(AMLGraph* G, int *top,int* indegree)
{
	Findindegree(G, indegree);  //���������ж������Ȳ������indegree������
	Stack S;    //����һ��ջ����ʱ������Ϊ0�Ķ���
	InitStack(&S);
	for (int i = 0; i < G->vexnum; i++)
	{
		if (indegree[i] == 0)    //��������indegree������������Ϊ0�Ķ���,�ͽ�ջ
			Push(&S, i);
	}
	int m = 0;  //��ʼ��һ��m������ɾ�����Ķ������
	while (!IsEmpty(&S))   //ջ�ղ��˳�ѭ��
	{
		int e = Pop(&S);   //��ջһ�����㣬��e����
		//ע�⣺m�Ĵ�Сʼ��Ϊɾ��������+1
		top[m++] = e;    //��ջ�����e���������Ϊ0�Ķ��㣬��������ʱ����ǰ�棬m++����
		Arcnode* p = G->Vlist[e].first;   //����pѰ�Ҷ���e�ĳ���
		while (p)
		{
			indegree[p->adjvex]--;    //����e�ĳ��Ⱦ��������������ȣ�����eҪ��ɾ���ˣ���Ӧ�ĳ���ҲҪ��ɾ������������������ҲҪ-1
			if (indegree[p->adjvex] == 0)    //�����ɾ������e�Ĺ�����������������Ϊ0�ˣ��򽫸ö�����ջ
				Push(&S, p->adjvex);
			p = p->next;   //p������������e�ı߱�
		}
	}
	//�������ͼ�д��ڻ�����ôm�ǲ������G->vexnum�ģ���Ϊ�γɻ�����Ҫ�������㣬������������������С����ɾ�����Ķ�����ӦΪG->vexnum-2
	//��m�Ĵ�С��ԶΪɾ�����Ķ�����+1������m=G->vexnum-1����С��G->vexnum�ģ�����������ڻ���m�ǲ����ܻ����G->vexnum��
	if (m < G->vexnum)   //���m < G->vexnum����˵��ͼ�д��ڻ���û����������
		return 0;  
	else         //��������������
		return 1;
}
int main()
{
	AMLGraph G;
	CreatYXW(&G);
	int* top = (int*)malloc(sizeof(int) * G.vexnum);
	int* indegree = (int*)malloc(sizeof(int) * G.vexnum);
	int ret=TopologicalSort(&G, top, indegree);
	if (ret == 1)
	{
		printf("��������Ϊ��");
		for (int i = 0; i < G.vexnum; i++)
		{
			printf("%c ", G.Vlist[top[i]].v);
		}
	}
	else
		printf("û����������");
	return 0;
}