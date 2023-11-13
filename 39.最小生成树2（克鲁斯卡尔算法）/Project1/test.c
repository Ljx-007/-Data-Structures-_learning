#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define MVNum 100
//��С������(Kruskal)--�ڽӱ�
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
void CreatWXW(AMLGraph* G)
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
		printf("��������������������Ȩֵ:");
		scanf("%c %c %d", &v1, &v2, &w);
		int j = Located(v1, G);
		int k = Located(v2, G);
		Arcnode* p = (Arcnode*)malloc(sizeof(Arcnode));
		p->next = G->Vlist[j].first;
		G->Vlist[j].first = p;
		p->adjvex = k, p->w = w;
		Arcnode* q = (Arcnode*)malloc(sizeof(Arcnode));
		q->next = G->Vlist[k].first;
		G->Vlist[k].first = q;
		q->adjvex = j, q->w = w;
	}
}
typedef struct Edge
{
	int v0, u0;
	int weight;
}Edge;
void InitEdge(Edge* Arredge, AMLGraph* G)
{   
	for (int i = 0; i < G->vexnum; i++)
	{
		Arcnode* p = G->Vlist[i].first;
		while (p)
		{//���������ڽӱ�洢��������ͬ�ı���Ϣ��������ֻ��Ҫһ�鲻�ظ��ı���Ϣ����Ϊÿһ���߶��ڶ���ı߱��д洢�����Σ���������±��д�С֮��
			//��������ֻ��ѡȡ�����±����/С�ڱ߱����±�ıߣ��Ϳ�������ѡȡ���ظ��ı���
			//����v1��v5����һ���ߣ���ô���ڽӱ��У������0��v1���±꣩�ı߱����4��v5���±꣩�������4��v5���±꣩�ı߱����0��v1���±꣩
			// ֻ��Ҫ���ѡȡһ������ı߼��ɣ�Ϊ�˱�֤��ѡ���ظ��ıߣ����ǹ涨ֻѡȡһ�����򣬼������±�С�ڱ߱����±�ķ���
			//  �ڴ����о���ѡȡ���������0��v1���±꣩�ı߱����4��v5���±꣩������һ����
			if(i<p->adjvex)   //i���Ƕ����Ķ����±꣬p->adjvex���Ǳ߱�����±�
			{
				Arredge->v0 = i;
				Arredge->u0 = p->adjvex;
				Arredge->weight = p->w;
				Arredge++;
			}
			p = p->next;
		}
	}
}
int cmp(const void* e1, const void* e2)
{
	return ((Edge*)e1)->weight - ((Edge*)e2)->weight;
}
void Kruskal_AML(AMLGraph* G)
{
	Edge* Arredge = (Edge*)malloc(sizeof(Edge)*G->arcnum);
	InitEdge(Arredge, G);  //��ʼ������Arredge���ѱ���Ϣ���浽Arredge������
	qsort(Arredge, G->arcnum, sizeof(Edge), cmp);
	int* Vexset = malloc(sizeof(int) * G->vexnum);  //��������Vexset����¼ÿ�������Ƿ���ͨ
	for (int i = 0; i < G->vexnum; i++)
	{
		Vexset[i] = i;
	}
	for (int i = 0; i < G->arcnum; i++)
	{
		int v0 = Arredge[i].v0;
		int u0 = Arredge[i].u0;
		int vs0 = Vexset[v0];
		int us0 = Vexset[u0];
		if (vs0 != us0)
		{
			printf("%c-->%c\n", G->Vlist[v0].v, G->Vlist[u0].v);
			for (int j = 0; j < G->arcnum; j++)
				if (Vexset[j] == us0)
					Vexset[j] = vs0;
		}
	}
}
int main()
{
	AMLGraph G;
	CreatWXW(&G);
	Kruskal_AML(&G);
	return 0;
}