#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define MVNum 100
#define MAXINT 32767
//算法设计题
//1.分别以邻接矩阵和邻接表作为存储结构，实现以下图的基本操作：
// （1）增加一个新顶点，InsertVex(G,v)
// （2）删除顶点v及其相关的边，DeleteVex(G,v)
// （3）增加一条边<v,w>,InsertArc(G,v,w)
// （4）删除一条边<v,w>,DeleteArc(G,v,w)
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
typedef struct AMGraph
{
	char Vlist[MVNum];
	int arcs[MVNum][MVNum];
	int vexnum, arcnum;
}AMGraph;
int AM_Located(AMGraph* G, char v)
{
	for (int i = 0; i < G->vexnum; i++)
	{
		if (G->Vlist[i] == v)
			return i;
	}
	return -1;
}
int AML_Located(AMLGraph* G, char v)
{
	for (int i = 0; i < G->vexnum; i++)
	{
		if (G->Vlist[i].v == v)
			return i;
	}
	return -1;
}
//(1)
// 邻接矩阵
void InsertVex_AM(AMGraph* G, char v)
{
	if (G->vexnum + 1 > MVNum)
		return;
	G->Vlist[G->vexnum + 1] = v;
	G->vexnum++;
}
//邻接表
void InsertVex_AML(AMLGraph* G, char v)
{
	if (G->vexnum + 1 > MVNum)
		return;
	G->Vlist[G->vexnum ].v = v;
	G->Vlist[G->vexnum ].first = NULL;
	G->vexnum++;
}
//(2)
// 邻接矩阵
void AM_DeleteVex(AMGraph* G, char v)
{
	int k = AM_Located(G, v);
	if (G->vexnum == 0||k==-1)
		return;
	//将第k个顶点直接和最后一个顶点交换位置，如果是用后续顶点代替前面的顶点的话，会很复杂
	G->Vlist[k] = G->Vlist[G->vexnum-1];
	for (int i = 0; i < G->vexnum; i++)
	{
		G->arcs[k][i] = G->arcs[G->vexnum - 1][i];   //边的关系也换成最后一个顶点的
	}
	G->vexnum--;
}
// 邻接表
void AML_DeleteVex(AMLGraph* G, char v)
{
	int k = AML_Located(G, v);
	if (G->vexnum == 0 || k == -1)
		return;
	G->Vlist[k].v = G->Vlist[G->vexnum - 1].v;
	G->Vlist[k].first = G->Vlist[G->vexnum-1].first;
	G->vexnum--;
}
//(3)
// 邻接矩阵
void AM_InsertArc(AMGraph* G, char v, char w)
{
	int v0 = AM_Located(G, v);
	int w0 = AM_Located(G, w);
	if (v0 == -1 || w0 == -1||v0==w0)
		return;
	if (G->arcs[v0][w0] != 0)
	{
		printf("边已存在");
		return;
	}
	else
	{
		G->arcs[v0][w0] = 1;
		G->arcnum++;
	}
}
// 邻接表
void AML_InsertArc(AMLGraph* G, char v, char w)
{
	int v0 = AML_Located(G, v);
	int w0 = AML_Located(G, w);
	if (v0 == -1 || w0 == -1 || v0 == w0)
		return;
	Arcnode* p = (Arcnode*)malloc(sizeof(Arcnode));
	p->adjvex = w0, p->next = NULL;
	Arcnode* h = G->Vlist[v0].first;
	while (h)      //遍历顶点v的边表，如果顶点v和顶点w间存在边，那么就直接返回，不存在就把这条边信息加在边表后
	{
		if (h->adjvex = w0)
		{
			printf("边已存在");
			return;
		}
		h=h->next;
	}
	h = p;
	G->arcnum++;
}
//（4）
// 邻接矩阵
void AM_DeleteArc(AMGraph* G, char v, char w)
{
	int v0 = AM_Located(G, v);
	int w0 = AM_Located(G, w);
	if (v0 == -1 || w0 == -1 || v0 == w0)
		return;
	if (G->arcs[v0][w0] == 0)
	{
		printf("该边不存在");
		return;
	}
	else
	{
		G->arcs[v0][w0] = 0;
		G->arcnum--;
	}
}
// 邻接表
void AML_DeleteArc(AMLGraph* G, char v, char w)
{
	int v0 = AML_Located(G, v);
	int w0 = AML_Located(G, w);
	if (v0 == -1 || w0 == -1 || v0 == w0)
		return;
	Arcnode* p = G->Vlist[v0].first;
	Arcnode* q = p->next;
	if (p->adjvex == w0)   //边表第一个元素就是要删掉的边
	{
		Arcnode* f = p;
		p = p->next;
		free(f), f = NULL;
		return;
	}
	while (q)  //第一个元素不是要删掉的边
	{
		if (q->adjvex == w0)
		{
			Arcnode* f = q;
			p->next = q->next;
			p = p->next, q = q->next;
			free(f), f = NULL;
			return;
		}
		else
			p = p->next, q = q->next;
	}
	//如果出了循环，说明在边表中没有找到这条边，则这条边不存在
	printf("该边不存在"); 
}
//2.一个连通图采用邻接表作为存储结构，设计一个算法，实现从顶点v出发点深度优先遍历的非递归过程
typedef struct Stack
{
	int* base;
	int* top;
	int sizemax;
}Stack;
void InitStack(Stack* S,int n)
{
	S->base = (int*)malloc(sizeof(int) * n);
	S->top = S->base;
	S->sizemax = n;
}
void Push(Stack* S, int v)
{
	if ((S->top - S->base) == S->sizemax)
	{
		printf("栈满");
		return;
	}
	*S->top++ = v;
}
int Pop(Stack* S)
{
	if (S->top == S->base)
	{
		printf("栈空");
		return -1;
	}
	int e = *--S->top;
	return e;
}
int IsEmpty(Stack* S)
{
	if (S->top == S->base)
		return 1;
	return 0;
}
void CreatWXT(AMLGraph* G)
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
		//int w;
		printf("请输入两个顶点：");
		while ((c = getchar()) != '\n') { ; }
		scanf("%c %c", &v1, &v2);
		int m = AML_Located(G, v1);
		int n = AML_Located(G,v2);
		Arcnode* p = malloc(sizeof(Arcnode));
		p->adjvex = n;
		//p->weight = w;
		p->next = G->Vlist[m].first;
		G->Vlist[m].first = p;
		Arcnode* q = malloc(sizeof(Arcnode));
		q->adjvex = m;
		//q->weight = w;
		q->next = G->Vlist[n].first;
		G->Vlist[n].first = q;
	}
}
void DFS_notre(AMLGraph* G, char v)
{
	Stack S;
	InitStack(&S,G->vexnum);
	int v0 = AML_Located(G, v);
	int* visited = (int*)calloc(sizeof(int),G->vexnum);
	if (v0 == -1)
		return;
	Arcnode* p = G->Vlist[v0].first;
	printf("%c ", G->Vlist[v0].v);
	Push(&S, v0);
	visited[v0] = 1;
	while (p)
	{
		if (visited[p->adjvex] == 0)
		{
			printf("%c ", G->Vlist[p->adjvex].v);
			Push(&S, p->adjvex);
			visited[p->adjvex] = 1;
			p = G->Vlist[p->adjvex].first;
		}
		else
		{
			p = p->next;
			if (!p&&!IsEmpty(&S))
			{
				int e = Pop(&S);
				p = G->Vlist[e].first;
			}
		}
	}
}
//3.设计一个算法，求图G中距离顶点v的最短路径长度最大的一个顶点。设v可达其余各个顶点
int LongestPath(AMLGraph* G, char v)
{  //用Dijkstra算法求最短路径
	int v0 = AML_Located(G, v);
	if (v0 == -1)
		return -1;
	int* S = (int*)malloc(sizeof(int) * G->vexnum);
	int* D = (int*)malloc(sizeof(int) * G->vexnum);
	int* Path = (int*)malloc(sizeof(int) * G->vexnum);
	for (int i = 0; i < G->vexnum; i++)
	{
		S[i] = 0;
		D[i] = MAXINT;
		Path[i] = -1;
	}
	S[v0] = 1, D[v0] = 0;
	Arcnode* p = G->Vlist[v0].first;
	while (p)
	{
		D[p->adjvex] = p->weight;
		Path[p->adjvex] = v0;
		p = p->next;
	}
	//寻找距离v0的最短路径的顶点
	for(int j=1;j<G->vexnum;j++)  //对剩下n-1个顶点进行计算
	{
		int min = MAXINT;
		int pos;
		for (int i = 0; i < G->vexnum; i++)
		{
			if (S[i] == 0 && D[i] < min)
			{
				min = D[i];
				pos = i;
			}
		}
		S[pos] = 1;
		p = G->Vlist[pos].first;
		while (p)
		{
			if (S[p->adjvex] == 0 && D[p->adjvex] > D[pos] + p->weight)
			{
				D[p->adjvex] = D[pos] + p->weight;
				Path[p->adjvex] = pos;
			}
			p = p->next;
		}
	}
	//各顶点的最短路径寻找完后来找最大值
	int max = 0;
	int pos2;
	for (int i = 1; i < G->vexnum; i++)
	{
		if (D[i] > max&&D[i]!=MAXINT)
		{
			max = D[i];
			pos2 = i;
		}
	}
	printf("最短路径长度最大的顶点为：%c ,长度为%d", G->Vlist[pos2].v,D[pos2]);
	return pos2;
}
//4.试基于图的深度优先搜索策略写一算法，判别以邻接表方式存储的有向图中是否存在顶点vi到顶点vj的路径（i!=j）
int IsPath_DFS(AMLGraph* G, char v, char u,int* visited)
{
	int v0 = AML_Located(G, v);
	int u0 = AML_Located(G, u);
	if (u0 == -1 || v0 == -1 || u0 == v0)
		return -1;
	visited[v0] = 1;
	static int ret = 0;   //采用静态变量记录是否遇到了顶点u0，如果遇到顶点u0，ret=1，否则一直为0；
	Arcnode* p = G->Vlist[v0].first;
	while (p)
	{
		if (visited[p->adjvex] == 0)
		{
			visited[p->adjvex] = 1;
			if (p->adjvex == u0)
				ret = 1;
			IsPath_DFS(G, G->Vlist[p->adjvex].v, u, visited);
		}
		p = p->next;
	}
	return ret;
}
//（5）采用邻接表存储结构，编写一个算法，判别无向图中任意给定的两个顶点之间是否存在一条长度为k的简单路径
int IsPath(AMLGraph* G, char v,char u,int k,int* visited)
{
	int v0 = AML_Located(G, v);
	int u0 = AML_Located(G, u);
	if (u0 == -1 || v0 == -1||k<0)
		return -1;
	if (v0 == u0 && k == 0)   //如果给定的两个顶点是一个顶点，且他们之间长度为0，则符合条件，返回1
		return 1;
	Arcnode* p = G->Vlist[v0].first;
	visited[v0] = 1;
	static int ret = 0;   //用静态变量ret记录是否找到长为k的简单路径
	while (p)
	{
		if (visited[p->adjvex] == 0)  //若该顶点的邻接顶点没被访问过
		{
			//因为每次递归都是对目标顶点的更进一步，所以路径长度k也逐渐-1
			//当最后一次递归到目标顶点时，k=1而不是k=0，因为判断是否为目标顶点u0的语句在递归语句前，所以当递归到目标顶点时，k=1
			if (p->adjvex == u0 && k == 1)   //若该顶点的邻接顶点就是目标顶点u0，并且k==1，即符合条件
				ret = 1;
			visited[p->adjvex] = 1;   //将该邻接顶点记为访问过，并类似DFS算法继续递归访问
			IsPath(G, G->Vlist[p->adjvex].v, u, k - 1,visited);
			visited[p->adjvex] = 0;  //也许目标顶点不在刚才递归的路径，那么就回退，把刚才记为访问过的顶点重新标为未访问状态
		}       //继续让边表p遍历其他的邻接顶点，走其他的路径进行递归，看是否存在目标顶点u0
		p = p->next;
	}
	return ret;
}
int main()
{
	AMLGraph G;
	CreatWXT(&G);
	//DFS_notre(&G, '1');
	/*LongestPath(&G, '0');*/
	/*int* visited = (int*)calloc(sizeof(int), G.vexnum);*/
	/*int ret = IsPath_DFS(&G, '1', '0');*/
	int* visited = (int*)calloc(sizeof(int), G.vexnum);
	int ret = IsPath(&G, '1', '3', 4,visited);
	if (ret == 1)
		printf("存在路径\n");
	else
		printf("不存在路径\n");
	return 0;
}