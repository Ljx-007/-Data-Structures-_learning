#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define MVNum 100
//关键路径
//AOE网表示以边表示活动，顶点表示活动的开始或者结束。
//AOE网通常在工程计划和经营管理中有广泛应用，通常需要解决两个问题：
//1、估算完成整项工程至少需要多少时间？
//2、判断哪些活动是影响工程进度的关键
//因为工程只有一个开始点和一个完成点，开始点入度为0，称为源点，完成点出度为0，称为汇点。
//要估算整项工程完成的最短时间，就是要找一条从源点到汇点的带权路径长度最长的路径，称为关键路径。
//关键路径上的活动称为关键活动，这些活动的提前或拖延将使整个工程提前或拖延

//活动ai的最早开始时间-最晚开始时间=时间余量
//如果一个活动没有时间余量，那么这个活动就是关键活动
// 
//事件vi的最早开始时间ve（i）：
//  事件vi前的每一项活动都结束了才能开始vi事件，所以要找（vi事件前的事件的最早发生时间+到事件vi的弧的权值）的最大值，就是vi事件的最早开始时间
//    ve（i）= Max{ ve(k) + wk,i}    --vk为vi事件前的事件，ve（k）为vk事件的最早发生时间，wk,i为活动vk-vi的持续时间
//事件vi的最晚发生时间vl（i）：
//  计算最晚发生时间需要从汇点往前递推，例如整个工程最晚要第十天完成，vi事件后有3项活动分别需要3，5，7天来完成，则vi事件发生的最晚时间应是
//    10-7，10-5，10-3中的最小值，即10-7=3，所以vi事件发生的最晚时间应为第三天。
//  以此类推，从汇点一直往前推，一直推到我们正在计算的事件vi，所以公式为：
//    vl(i) = Min{vl(k) - wi,k}

//活动ai=<vj,vk>
//活动ai的最早开始时间e(i)：
//  只有事件vj发生了，活动ai才能开始，所以ai的最早开始时间e(i)=ve(j)
//活动ai的最晚开始时间l(i):
//  活动ai的开始时间需保证不延误事件vk的最晚发生时间，所以ai的最晚开始时间l(i)=vl(k)-wj,k

//求关键路径的步骤：
//1.求ve(i).vl(i)
//2.求e(i),l(i)
//3.计算l(i)-e(i)
//源点和汇点的最早开始时间和最晚开始时间是一样的
//计算关键路径要引入以下辅助结构：
//1.一维数组ve[i]：记录事件vi的最早发生时间
//2.一维数组vl[i]：记录事件vi的最迟发生时间
//3.一维数组topo[i]：记录拓扑序列的顶点序号
typedef struct Vnode
{
	char v;
	struct Arcnode* first;
}Vnode;
typedef struct Arcnode
{
	int adjvex;
	int weight;
	struct Arcnode* next;
}Arcnode;
typedef struct
{
	Vnode Vlist[MVNum];
	int vexnum, arcnum;
}AMLGraph;
//定义顺序栈
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
		printf("栈满\n");
		return;
	}
	*S->top = e;
	S->top++;
}
int Pop(Stack* S)
{
	if (S->top == S->base)
	{
		printf("栈空\n");
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
	printf("输入顶点数和边数：");
	scanf("%d%d", &G->vexnum, &G->arcnum);
	for (int i = 0; i < G->vexnum; i++)
	{
		printf("输入顶点信息：");
		while ((c = getchar()) != '\n') { ; }
		scanf("%c", &G->Vlist[i].v);
		G->Vlist[i].first = NULL;
	}
	for (int i = 0; i < G->arcnum; i++)
	{
		char v1, v2;
		int w;
		printf("请以有向顺序输入两个顶点及边权值：");
		while ((c = getchar()) != '\n') { ; }
		scanf("%c %c %d", &v1, &v2,&w);
		int m = Located(v1, G);
		int n = Located(v2, G);
		Arcnode* p = malloc(sizeof(Arcnode));
		p->adjvex = n;
		p->weight = w;
		p->next = G->Vlist[m].first;
		G->Vlist[m].first = p;
	}
}
void Findindegree(AMLGraph* G, int* indegree)
{
	for (int i = 0; i < G->vexnum; i++)
	{
		int count = 0;
		for (int j = 0; j < G->vexnum; j++)
		{
			Arcnode* p = G->Vlist[j].first;
			while (p)
			{
				if (p->adjvex == i)
					count++;
				p = p->next;
			}
		}
		indegree[i] = count;
	}
}
int TopoSort(AMLGraph* G,int* indegree,int* topo)
{
	Findindegree(G, indegree);
	Stack S;
	InitStack(&S);
	for (int i = 0; i < G->vexnum; i++)
	{
		if (indegree[i] == 0)
			Push(&S, i);
	}
	int m = 0;
	while (!IsEmpty(&S))
	{
		int e = Pop(&S);
		topo[m++] = e;
		Arcnode* p = G->Vlist[e].first;
		while (p)
		{
			indegree[p->adjvex]--;
			if (indegree[p->adjvex] == 0)
				Push(&S, p->adjvex);
			p = p->next;
		}
	}
	if (m < G->vexnum)
		return 0;
	return 1;
}
void CriticalPath(AMLGraph G, int* ve, int* vl,int* indegree,int* topo)
{
	if (!TopoSort(&G, indegree, topo))
		return;
	//初始化每个事件的最早发生时间
	for (int i = 0; i < G.vexnum; i++)
		ve[i] = 0;
	//求每个事件的最早发生时间
	for (int i = 0; i < G.vexnum; i++)
	{//按拓扑序列求每个事件的最早发生时间
		int k = topo[i];
		Arcnode* p = G.Vlist[k].first;
		while (p)
		{//如果事件p->adjvex的前一个事件k的最早发生时间+两事件间的活动时间>原来的事件p->adjvex的最早发生时间，那么就更新事件p->adjvex的最早发生时间
			//这里就是再找Max{ve(k)+ wi,k},i其实就是p->adjvex
			if (ve[p->adjvex] < ve[k] + p->weight)    
				ve[p->adjvex] = ve[k] + p->weight;
			p = p->next;
		}
	}
	//初始化每个事件的最晚发生时间
	for (int i = 0; i < G.vexnum; i++)
	{
		vl[i] = ve[G.vexnum - 1];  //将每个事件的最晚发生时间初始化为汇点的最早发生时间，即整个工程要求完成的时间
	}
	//求每个事件的最晚发生时间
	for (int i = G.vexnum-1; i >=0; i--)
	{//因为最晚发生时间要从汇点从后往前递推，所以要按逆拓扑序列求事件的最晚发生时间
		int k = topo[i];
		Arcnode* p = G.Vlist[k].first;
		while (p)
		{//如果事件k后一个事件p->adjvex-两事件之间的活动时间<原来事件k的最晚发生时间，那么就更新事件k的最晚发生时间
			//这里就是再找Min{ vl(j)- wi,j} , j就是p->adjvex
			if (vl[p->adjvex] - p->weight < vl[k])
				vl[k] = vl[p->adjvex] - p->weight;
			p = p->next;
		}
	}
	for (int i = 0; i < G.vexnum; i++)
	{  //每次循环针对以vi为活动开始点，以vi的邻接顶点为活动结束点的活动
		Arcnode* p = G.Vlist[i].first;
		while (p)  //用p遍历边表找邻接顶点
		{
			int e = ve[i];  //活动的最早开始时间=前一个事件的最早开始时间
			int l = vl[p->adjvex] - p->weight;  //活动的最晚开始时间=后一个活动的最晚开始时间-活动的持续时间
			if (l == e )
			{//打印关键路径
				printf("%c-->%c，weight=%d\n", G.Vlist[i].v, G.Vlist[p->adjvex].v,p->weight);
			}
			p = p->next;
		}
	}
}
int main()
{
	AMLGraph G;
	CreatYXW(&G);
	int* indegree = (int*)malloc(sizeof(int) * G.vexnum);
	int* topo = (int*)malloc(sizeof(int) * G.vexnum);
	int* ve = (int*)malloc(sizeof(int) * G.vexnum);
	int* vl = (int*)malloc(sizeof(int) * G.vexnum);
	CriticalPath(G, ve, vl, indegree, topo);
	return 0;
}