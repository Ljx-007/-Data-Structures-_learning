#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define MVNum 100
#define MAXW 32767
//���·����Dijkstra��--�ڽӱ�
typedef struct Vnode
{
	char v;
	struct Arcnode* first;
}Vnode;
typedef struct Arcnode
{
	int adjvex;
	int w;
	struct Arcnode* next;
}Arcnode;
typedef struct
{
	Vnode Vlist[MVNum];
	int vexnum, arcnum;
}AMLGraph;
//����������
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
	printf("�����������Ķ������ͱ�����");
	scanf("%d%d", &G->vexnum, &G->arcnum);
	for (int i = 0; i < G->vexnum; i++)
	{
		while ((c = getchar()) != '\n') { ; }
		printf("���붥����Ϣ��");
		scanf("%c", &G->Vlist[i].v);
		G->Vlist[i].first = NULL;
	}
	for (int i = 0; i < G->arcnum; i++)
	{
		char v1, v2;
		int w;
		while ((c = getchar()) != '\n') { ; }
		printf("������˳����������������������Ȩֵ:");
		scanf("%c %c %d", &v1, &v2, &w);
		int j = Located(v1, G);
		int k = Located(v2, G);
		Arcnode* p = (Arcnode*)malloc(sizeof(Arcnode));
		p->next = G->Vlist[j].first;
		G->Vlist[j].first = p;
		p->adjvex = k, p->w = w;
	}
}
void ShortestPath_DIJ(AMLGraph* G, char v, int* S, int* D, int* Path)
{
	int k = Located(v, G);
	Arcnode* p = G->Vlist[k].first;
	for (int i = 0; i < G->vexnum; i++)    //��ʼ������S��D��Path
	{
		S[i] = 0;
		D[i] = MAXW;
		Path[i] = -1;
	}
	while (p)        //pָ��Դ��ı߱���D��Path�������ʼֵ
	{
		int j = p->adjvex;
		D[j] = p->w;
		Path[j] = k;
		p = p->next;
	}
	D[k] = 0, S[k] = 1;   //��Դ����붥�㼯��Դ�㵽����û�����·������ʼ��Ϊ0
	int u;
	for (int i = 1; i < G->vexnum; i++)   //��ѡʣ��n-1������
	{
		int min = MAXW;
		for (int j = 0; j < G->vexnum; j++)  //��ѡʣ�¶����е�Դ������·��
		{
			if (S[j] == 0 && D[j] < min)
			{
				min = D[j];   //min��¼���·��
				u = j;    //���·�����㸳��u
			}
		}
		S[u] = 1;   //���Ѿ��ҵ������·������u���붥�㼯
		p = G->Vlist[u].first;   //�����붥��u�����ӵĶ���
		while (p)   //����u��Ϊ��תվ
		{
			int j = p->adjvex;
			if (S[j] == 0 && (D[u] + p->w < D[j]))   //������붥��u��Ϊ��תʹ�ö���j�������·������ô���޸Ķ���j�����·����ǰ������
			{
				D[j] = D[u] + p->w;   //�������·��
				Path[j] = u;
			}
			p = p->next;
		}
	}
}
int main()
{
	AMLGraph G;
	CreatYXW(&G);
	char v, u;
	int* D = malloc(sizeof(int) * G.vexnum);
	int* S = malloc(sizeof(int) * G.vexnum);
	int* Path = malloc(sizeof(int) * G.vexnum);
	printf("������Դ����յ�:");
	while ((v = getchar()) != '\n') { ; }
	scanf("%c %c", &v, &u);
	ShortestPath_DIJ(&G, v, S, D, Path);
	int v0 = Located(v, &G);
	int u0 = Located(u, &G);
	int* stack = malloc(sizeof(int) * G.vexnum);
	int base = 0;
	int top = 0;
	while (u0 != v0)
	{
		stack[top++] = u0;
		u0 = Path[u0];
	}
	int i = v0;
	while (top != base)
	{
		int j = stack[--top];
		printf("%c-->%c\n", G.Vlist[i].v, G.Vlist[j].v);
		i = j;
	}
	return 0;
}