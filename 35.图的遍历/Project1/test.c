#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//深度优先搜索--Depth First Search--DFS
//深度优先搜索简单来说是沿着某一条路一直走，直到走不通为止就往回走，直到有路走,类似树的先序遍历
//邻接矩阵表示的无向图深度优先搜索
#define MVNum 100
typedef struct
{
	char Vlist[MVNum];
	int arcs[MVNum][MVNum];
	int vexnum, arcnum;
}AMGraph;
int LocatedWXT(char v, AMGraph* G)
{
	for (int i = 0; i < G->vexnum; i++)
	{
		if (v == G->Vlist[i])
			return i;
	}
	return -1;
}
void ArrCreatWXT(AMGraph* G)        //创建无向图
{
	printf("请输入顶点个数和边个数：");
	scanf("%d%d", &G->vexnum, &G->arcnum);
	for (int i = 0; i < G->vexnum; i++)
	{
		printf("请输入顶点信息:");
		scanf("%c", &G->Vlist[i]);
	}
	for (int i = 0; i < G->vexnum; i++)
	{
		for (int j = 0; j < G->vexnum; j++)
		{
			G->arcs[i][j] = 0;
		}
	}
	for (int i = 0; i < G->arcnum; i++)
	{
		char v1, v2;
		printf("请输入该边所依附的两个顶点：");
		scanf("%c%c", &v1, &v2);
		int p = LocatedWXT(v1, G);
		int q = LocatedWXT(v2, G);
		G->arcs[p][q] = 1;
	}
}
int visited[MVNum] = { 0 };   //用一个visited数组来记录顶点是否被访问过，0代表未被访问，1代表被访问
void DFS(AMGraph G, int v)  //参数为一个无向图和最开始访问的顶点
{
	printf("%c ", G.Vlist[v]);
	visited[v] = 1;  //顶点v被访问，记录到数组visited中
	for (int i = 0; i < G.vexnum; i++)        //遍历二维数组中顶点v所在的那行的值
	{
		if (G.arcs[v][i] != 0 && visited[i] == 0)   //如果该行有值不为0，说明该顶点v与i列代表的顶点i之间有边，并且顶点i没有被访问过
			DFS(G, i);   //继续访问顶点i
	}
}
//邻接表表示的图的深度优先搜索
typedef struct Vnode
{
	char v;
	struct Arcnode* first;
}Vnode;
typedef struct Arcnode
{
	int v;
	//如果有权值则添加权值
	struct Arcnode* next;
}Arcnode;
typedef struct
{
	Vnode Vlist[MVNum];
	int vexnum, arcnum;
}AMLGraph;
int LocatedWXTLink(char v, AMLGraph* G)
{
	for (int i = 0; i < G->vexnum; i++)
	{
		if (G->Vlist[i].v == v)
			return i;
	}
	return -1;
}
void LinkCreatWXT(AMLGraph* G)
{
	printf("请输入顶点个数和边数：");
	scanf("%d%d", &G->vexnum, &G->arcnum);
	for (int i = 0; i < G->vexnum; i++)
	{
		printf("请输入顶点信息：");
		scanf("%c", &G->Vlist[i].v);
		G->Vlist[i].first = NULL;
	}
	for (int i = 0; i < G->arcnum; i++)
	{
		char v1, v2;
		printf("请输入边所依附的两个顶点信息：");
		scanf("%c%c", &v1, &v2);
		int j = LocatedWXTLink(v1, G);
		int k = LocatedWXTLink(v2, G);
		Arcnode* p = (Arcnode*)malloc(sizeof(Arcnode));
		p->v = k;
		p->next = G->Vlist[j].first;
		G->Vlist[j].first = p;
		Arcnode* q = (Arcnode*)malloc(sizeof(Arcnode));
		q->v = j;
		q->next = G->Vlist[k].first;
		G->Vlist[k].first = p;
	}
}
int visitedAL[MVNum] = { 0 };
void DFS_AL(AMLGraph G, int v)
{
	printf("%c ", G.Vlist[v].v);  //访问顶点
	visitedAL[v] = 1;   //记录该顶点的访问状态
	Arcnode* p = G.Vlist[v].first;    //用p指向顶点表中的边表指针域
	while (p)   //如果指针为空，说明与该顶点相连的顶点已经遍历完了
	{
		int j = p->v;    //令j等于边结点中的顶点下标
		if (visitedAL[j] == 0)  //如果顶点j未被访问过，则递归访问
			DFS_AL(G, j);
		p = p->next;   //边表指针指向下一个v顶点的邻接顶点
	}
}
//邻接表的遍历虽然有2e个边结点，但是遍历完只需要扫描e个结点即可，再加上n个头结点的访问，时间复杂度为O（n+e）
//邻接矩阵的遍历时间复杂度为O（n^2）
//以上的深度优先搜索适用于连通图，对于非连通图的深度优先搜索，则如下所示
//void DFSTraverse(Graph G) //Graph G为非连通图，此处Graph类型未定义
//{
//	for (int i = 0; i < G.vexnum; i++)
//	{
//		visited[i] = 0;  //初始化标志数组
//	}
//	for (int i = 0; i < G.vexnum; i++)
//	{
//		if (visited[i] == 0)    //如果顶点i未被访问，则对顶点i所在的连通分量进行遍历，并且以i为起点
//			DFS(G, i);         //当顶点i所在的连通分量被遍历完了，for循环中遍历visited数组，如果还有顶点未被遍历，说明该顶点属于另外的连通分量
//		                //则对该顶点所在的连通分量进行遍历，并且以该顶点为起点
//	}
//}

//广度优先搜索--Breadth First Search--BFS
//广度优先搜索过程：
//先从某个顶点v出发，访问v顶点，然后依次访问v的各个未曾访问过的邻接点，再分别从邻接点出发访问邻接点的邻接点，循环往复，直到图中没有顶点可访问
//广度优先搜索类似树的层次遍历，所以广度优先搜索需要用到队列
//邻接表的广度优先搜索
#define MAXSIZE 50
typedef struct SqQueue
{
	int* que;
	int front, rear;
}SqQueue;
void InitQueue(SqQueue* Q)
{
	Q->que = (int*)malloc(sizeof(int) * MAXSIZE);
	Q->front = Q->rear = 0;
}
void EnQueue(SqQueue* Q, int v)
{
	if ((Q->rear + 1) % MAXSIZE == Q->front)
	{
		printf("队满\n");
		return;
	}
	Q->que[Q->rear] = v;
	Q->rear = (Q->rear + 1) % MAXSIZE;
}
int OutQueue(SqQueue* Q)
{
	if (Q->front == Q->rear)
	{
		printf("队空\n");
		return;
	}
	int e = Q->que[Q->front];
	Q->front = (Q->front + 1) % MAXSIZE;
	return e;
}
int QueueEmpty(SqQueue* Q)
{
	if (Q->front == Q->rear)
		return 1;
	return 0;
}
int visitedBFS_AL[MVNum] = { 0 };
void BFS_AL(AMLGraph* G,int v)
{
	SqQueue Q;
	InitQueue(&Q);   //初始化一个队列
	printf("%c ", G->Vlist[v].v);   //打印第一个顶点的数据
	visitedBFS_AL[v] = 1;   //记录顶点已被访问
	EnQueue(&Q, v);   //将第一个顶点入队
	while (!QueueEmpty(&Q))   
	{
		int e=OutQueue(&Q);    //用e接收出队顶点
		Arcnode* p = G->Vlist[e].first;   //用p接收出队顶点的边表指针域
		while (p)   //开始遍历边表，即遍历出队顶点的邻接顶点
		{
			int i = p->v;   //用i来接收邻接顶点的下标
			if(visitedBFS_AL[i]==0)    //如果邻接顶点没有被访问过，进入if语句
			{
				printf("%c ", &G->Vlist[i].v);
				EnQueue(&Q, i);   //访问邻接顶点并入队，记录访问信息
				visitedBFS_AL[i] = 1;
			}
			p = p->next;  //p指向下一个出队顶点的邻接顶点
		}
	}//循环结束时，则代表所有的顶点已被遍历完
}

//邻接矩阵的广度优先搜索
int visitedBFS[MVNum] = { 0 };
void BFS(AMGraph* G,int v)
{
	SqQueue Q;
	InitQueue(&Q);
	printf("%c ", G->Vlist[v]);  //先访问第一个顶点并入队记录访问信息
	EnQueue(&Q, v);
	visitedBFS[v] = 1;
	int out;
	while(!QueueEmpty(&Q))   
	{
		out = OutQueue(&Q);   //用out接收出队顶点
		for(int i=0;i<G->vexnum;i++)
		{   //遍历该顶点下标对应的矩阵的行
			if (G->arcs[out][i] != 0 && visitedBFS[i] == 0)   //如果遍历到不为0的值，那么对应的列数i就为该顶点的邻接顶点下标
			{      //如果该邻接顶点i没有被访问，则访问该顶点并入队记录访问信息
				printf("%c ", G->Vlist[i]);   
				EnQueue(&Q, i);
				visitedBFS[i] = 1;
			}
		}	
	} //如果跳出while循环说明队列已经为空，所有的顶点都被遍历完了
}
//邻接矩阵的BFS算法时间复杂度为O（n^2）
//邻接表的BFS算法时间复杂度为O（n+e）	
//DFS和BFS空间复杂度相同，都借用了堆栈和队列，时间复杂度只与存储结构有关（邻接矩阵或邻接表）有关，与搜索路径无关