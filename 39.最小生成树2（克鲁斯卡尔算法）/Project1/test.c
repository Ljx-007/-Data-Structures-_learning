#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define MVNum 100
//最小生成树(Kruskal)--邻接表法
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
	int v0, u0;
	int weight;
}Edge;
void InitEdge(Edge* Arredge, AMLGraph* G)
{   
	for (int i = 0; i < G->vexnum; i++)
	{
		Arcnode* p = G->Vlist[i].first;
		while (p)
		{//无向网的邻接表存储了两次相同的边信息，但我们只需要一组不重复的边信息，因为每一条边都在顶点的边表中存储了两次，而顶点的下标有大小之分
			//所以我们只用选取顶点下标大于/小于边表顶点下标的边，就可以做到选取不重复的边了
			//例如v1与v5间有一条边，那么在邻接表中，顶点表0（v1的下标）的边表存有4（v5的下标），顶点表4（v5的下标）的边表存有0（v1的下标）
			// 只需要随便选取一个方向的边即可，为了保证不选到重复的边，我们规定只选取一个方向，即顶点下标小于边表顶点下标的方向
			//  在此例中就是选取——顶点表0（v1的下标）的边表存有4（v5的下标）——这一条边
			if(i<p->adjvex)   //i就是顶点表的顶点下标，p->adjvex就是边表顶点的下标
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
	InitEdge(Arredge, G);  //初始化数组Arredge，把边信息都存到Arredge数组中
	qsort(Arredge, G->arcnum, sizeof(Edge), cmp);
	int* Vexset = malloc(sizeof(int) * G->vexnum);  //创建数组Vexset来记录每个顶点是否连通
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