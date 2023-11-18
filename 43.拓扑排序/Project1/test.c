#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define MVNum 100
//AOV网（Active On Vertex）--以顶点表示活动，弧表示活动之间的优先制约关系，这种有向图称为“顶点表示活动的网”
// AOV网中，不应该出现有向环，因为存在环的条件意味着某项活动应以自己为先决条件，这显然是荒谬的。
//AOE网（Active On Edge） --以弧表示活动，以顶点表示活动的开始或结束事件，这种有向图称为“边表示活动的网”
//拓扑排序
//拓扑排序就是将AOV-网种所有顶点排成一个线性序列，该序列满足：若在AOV-网中由顶点vi道顶点vj有一条路径，则在该线性序列中的顶点vi必定在顶点vj之前。
//拓扑排序的过程：
//1.在有向图中选择一个无前驱的顶点并输出它
//2.从图中删除该顶点和所有以它为尾的弧（它发出的弧）。
//3.重复上述步骤，直到不存在没有前驱的点
//4.拓扑排序的图应为有向无环图，如果输出的顶点数小于有向图的顶点数，则说明有向图中存在环，否则输出的顶点序列为拓扑排序

//实现拓扑排序的过程，可采用邻接表作为有向图的存储结构
//算法的实现要引入：
//一维数组indegree[i]：存放个顶点入度，没有前驱的顶点就是入度为0的顶点，删除入度为0的顶点时其出度的弧所对应的顶点的入读-1
//栈S：存放所有入度为0的顶点，这样可避免重复扫描数组indegree检测入度为0的顶点
//一维数组topo[i]：记录拓扑序列的顶点序号
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
		printf("请以有向顺序输入两个顶点：");
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
//计算有向图中每个顶点的入度
void Findindegree(AMLGraph* G, int* indegree)
{
	for(int i=0;i<G->vexnum;i++)   //这个循环是用来遍历数组indegree的
	{
		int count = 0;   //count用来计算每个顶点的入度
		for (int j = 0; j < G->vexnum; j++)   //这个循环用来遍历所有顶点的边表，用来计算入度
		{
			Arcnode* p = G->Vlist[j].first;   //从第一个顶点的边表开始遍历
			while (p)
			{
				if (p->adjvex == i)   //如果出度的顶点为i，说明顶点i有入度，则count+1
					count++;
				p = p->next;
			}
		}//for循环结束则代表所有顶点的出度都遍历完了，即顶点i的入度查找完毕，入度数为count
		indegree[i] = count;  //把入度数放在indegree中
	}
}
//拓扑排序
int TopologicalSort(AMLGraph* G, int *top,int* indegree)
{
	Findindegree(G, indegree);  //计算完所有顶点的入度并存放在indegree数组中
	Stack S;    //设置一个栈，暂时存放入度为0的顶点
	InitStack(&S);
	for (int i = 0; i < G->vexnum; i++)
	{
		if (indegree[i] == 0)    //遍历数组indegree，如果存在入度为0的顶点,就进栈
			Push(&S, i);
	}
	int m = 0;  //初始化一个m来计算删除掉的顶点个数
	while (!IsEmpty(&S))   //栈空才退出循环
	{
		int e = Pop(&S);   //出栈一个顶点，用e接收
		//注意：m的大小始终为删除顶点数+1
		top[m++] = e;    //出栈的这个e顶点是入度为0的顶点，拓扑排序时它排前面，m++计数
		Arcnode* p = G->Vlist[e].first;   //利用p寻找顶点e的出度
		while (p)
		{
			indegree[p->adjvex]--;    //顶点e的出度就是其他顶点的入度，顶点e要被删除了，对应的出度也要被删除，则其他顶点的入度也要-1
			if (indegree[p->adjvex] == 0)    //如果在删除顶点e的过程中其他顶点的入度为0了，则将该顶点入栈
				Push(&S, p->adjvex);
			p = p->next;   //p继续遍历顶点e的边表
		}
	}
	//如果有向图中存在环，那么m是不会大于G->vexnum的，因为形成环至少要两个顶点，如果存在两个顶点的最小环，删除掉的顶点数应为G->vexnum-2
	//而m的大小永远为删除掉的顶点数+1，所以m=G->vexnum-1，是小于G->vexnum的，所以如果存在环，m是不可能会大于G->vexnum的
	if (m < G->vexnum)   //如果m < G->vexnum，则说明图中存在环，没有拓扑排序
		return 0;  
	else         //否则有拓扑排序
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
		printf("拓扑排序为：");
		for (int i = 0; i < G.vexnum; i++)
		{
			printf("%c ", G.Vlist[top[i]].v);
		}
	}
	else
		printf("没有拓扑排序");
	return 0;
}