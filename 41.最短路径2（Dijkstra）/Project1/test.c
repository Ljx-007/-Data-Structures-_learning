#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define MVNum 100
#define MAXW 32767
//最短路径（Dijkstra）--邻接表法
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
//创建有向网
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
	printf("输入有向网的顶点数和边数：");
	scanf("%d%d", &G->vexnum, &G->arcnum);
	for (int i = 0; i < G->vexnum; i++)
	{
		while ((c = getchar()) != '\n') { ; }
		printf("输入顶点信息：");
		scanf("%c", &G->Vlist[i].v);
		G->Vlist[i].first = NULL;
	}
	for (int i = 0; i < G->arcnum; i++)
	{
		char v1, v2;
		int w;
		while ((c = getchar()) != '\n') { ; }
		printf("按有向顺序输入边依附的两个顶点和权值:");
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
	for (int i = 0; i < G->vexnum; i++)    //初始化数组S，D，Path
	{
		S[i] = 0;
		D[i] = MAXW;
		Path[i] = -1;
	}
	while (p)        //p指向源点的边表，给D，Path数组设初始值
	{
		int j = p->adjvex;
		D[j] = p->w;
		Path[j] = k;
		p = p->next;
	}
	D[k] = 0, S[k] = 1;   //将源点加入顶点集，源点到自身没有最短路径，初始化为0
	int u;
	for (int i = 1; i < G->vexnum; i++)   //挑选剩下n-1个顶点
	{
		int min = MAXW;
		for (int j = 0; j < G->vexnum; j++)  //挑选剩下顶点中到源点的最短路径
		{
			if (S[j] == 0 && D[j] < min)
			{
				min = D[j];   //min记录最短路径
				u = j;    //最短路径顶点赋给u
			}
		}
		S[u] = 1;   //将已经找到的最短路径顶点u加入顶点集
		p = G->Vlist[u].first;   //遍历与顶点u相连接的顶点
		while (p)   //顶点u作为中转站
		{
			int j = p->adjvex;
			if (S[j] == 0 && (D[u] + p->w < D[j]))   //如果加入顶点u作为中转使得顶点j具有最短路径，那么就修改顶点j的最短路径和前驱顶点
			{
				D[j] = D[u] + p->w;   //更新最短路径
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
	printf("请输入源点和终点:");
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