#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define MVNum 100
//最小生成树--邻接表法
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
//创建无向网
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
	printf("输入无向网的顶点数和边数：");
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
		printf("输入边依附的两个顶点和权值:");
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
	int adjvex;   //在U中的顶点
	int weight;    //V-U中顶点到U中顶点的边的权值
}Edge;
int Min(Edge closedge[],int n)  //寻找最小权值边
{
	int min = INT_MAX;
	int pos = 0; 
	int i;
	for ( i = 0; i < n; i++)
	{
		if (closedge[i].weight != 0 && closedge[i].weight < min)
		{
			min=closedge[i].weight;
			pos = i;
		}
	}
	return pos;   //这里的pos一定会返回一个值的，因为如果closedge[i].weight全是INT_MAX的话，就代表这个点与其他所有顶点都不相连，那么这就不是一个连通图了
	             //而创建的时候我们创建的又是连通图，所以这里pos一定会在for循环中返回出一个值
}
void AMLPrim(AMLGraph* G,char v)
{
	int k = Located(v, G);  
	Edge closedge[MVNum];   //创建一个closedge数组来存储V-U中的各个顶点到U中顶点的最小权值边
	for (int i = 0; i < G->vexnum; i++)
	{
			closedge[i].adjvex = k;     //起初先把V-U中各个顶点的closedge的邻接顶点初始化为起始顶点，后续随着更多的顶点加入U，会更新
			closedge[i].weight = INT_MAX;  //因为邻接表中不相关的两个顶点间没有权值，所以初始化的时候权值全部初始化为最大值
	}
	closedge[k].weight = 0;
	Arcnode* p = G->Vlist[k].first;   //邻接矩阵与邻接表的不同之处在于邻接表用的是边表存储边信息
	//用p来指向起始顶点的边表地址，不断向后遍历，即可知道顶点k的邻接顶点及其边的权值，以此来更新权值全为INT_MAX的closedge数组的权值信息
	while (p)
	{
		closedge[p->adjvex].weight = p->w;
		p = p->next;
	}
	for (int i = 0; i < G->vexnum - 1; i++)   //开始选择余下的n-1个顶点和n-1个边
	{
		int min = Min(closedge, G->vexnum);
		int v0 = closedge[min].adjvex;   //最小边起点
		int u0 = min;   //最小边终点
		printf("%c-->%c\n", G->Vlist[v0].v, G->Vlist[u0].v);
		closedge[u0].weight = 0;   //将最小权值边的终点顶点也并入U
		p = G->Vlist[u0].first;   //仿照上一次更新closedge数组的权值，用p来指向最小边终点顶点的边表，继续遍历
		while (p)
		{
			if (p->w<closedge[p->adjvex].weight)  //如果新加的顶点的在某个便有最小边权值，且最小边权值小于之前顶点边在这个点的最小边权值
			{                                  //那么就用小的那个最小边权值代替掉原来的最小边权值
				closedge[p->adjvex].adjvex = u0;
				closedge[p->adjvex].weight = p->w;
			}
			p = p->next;
		}
	}
}
int main()
{
	AMLGraph G;
	CreatWXW(&G);
	AMLPrim(&G, '1');
	return 0;
}