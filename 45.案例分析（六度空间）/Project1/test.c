#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define MVNum 100
//六度空间理论--世界上任意两个人最多只需要通过六个人就可以认识
//可以把人际关系网络图看成一个无向无权图，顶点代表一个人，两人是否相识则用边连接
//按照六度空间的理论，任意两个顶点间的路径长度不超过7，要验证此理论可以用广度优先算法
// 广度优先算法对图进行7层遍历，看看7层遍历后涵盖的已访问顶点数占总顶点数的多少。
//  进行7层遍历而不是6层是因为起始顶点算第一层，通过的六个人不包括自己本身

//定义一个队列
typedef struct Queuenode
{
	int v;
	struct Queuenode* next;
}Queuenode,*QueuePtr;
typedef struct
{
	QueuePtr front;
	QueuePtr rear;
}QueueLink;
void InitQueue(QueueLink* Q)
{
	//创建一个头结点
	Q->front = (Queuenode*)malloc(sizeof(Queuenode));
	Q->front->next = NULL;
	Q->rear = Q->front;
}
void EnQueue(QueueLink* Q,int v)
{
	Queuenode* p = (Queuenode*)malloc(sizeof(Queuenode));
	p->v = v;
	p->next = Q->rear->next;
	Q->rear->next = p;
	Q->rear = p;
}
int OutQueue(QueueLink* Q)
{
	if (Q->front == Q->rear)
		return -1;
	Queuenode* p = Q->front->next;
	int e = p->v;
	Q->front->next = p->next;
	if (Q->rear == p)
		Q->rear = Q->front;
	free(p), p = NULL;
	return e;
}
int IsEmpty(QueueLink* Q)
{
	if (Q->front == Q->rear)
		return 1;
	return 0;
}
//使用邻接表来作为无向无权图的存储结构
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
int Located(char v, AMLGraph* G)
{
	for (int i = 0; i < G->vexnum; i++)
	{
		if (v == G->Vlist[i].v)
			return i;
	}
	return -1;
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
		printf("请输入两个顶点：");
		while ((c = getchar()) != '\n') { ; }
		scanf("%c %c", &v1, &v2);
		int m = Located(v1, G);
		int n = Located(v2, G);
		Arcnode* p = malloc(sizeof(Arcnode));
		p->adjvex = n;
		p->next = G->Vlist[m].first;
		G->Vlist[m].first = p;
		Arcnode* q = malloc(sizeof(Arcnode));
		q->adjvex = m;
		q->next = G->Vlist[n].first;
		G->Vlist[n].first = q;
	}
}
void SixDegree_BFS(AMLGraph* G,char v)  //通过广度优先算法来验证六度空间理论，v为指定的一个起点
{
	int start = Located(v, G);
	int visit_num = 0; //用visit_num来记录7层遍历涵盖了多少顶点
	int* visited = (int*)calloc(sizeof(int) , G->vexnum);  //数组visit来记录顶点是否被访问
	visited[start] = 1;
	QueueLink Q;
	InitQueue(&Q);
	EnQueue(&Q, start);  //入队第一层的顶点，即起始顶点
	int level[7] = { 0 };  //用数组len来记录每一层遍历的顶点个数，只需遍历7层
	level[0] = 1;   //第一层遍历的顶点个数为1
	for (int len = 1; len <= 6 && !IsEmpty(&Q); len++)  //这里循环六次，是看某个人（起始顶点）通过六个人后能认识多少人
	{
		for (int i = 0; i < level[len - 1]; i++)   //这个for循环是把某一层的顶点全部出队遍历，然后入队下一层的顶点
		{  //这里的每一次循环其实就是在遍历前一层的下一层了，比如len=1时，将第0层的顶点出队，寻找第1层的顶点入队，所以第0层的顶点个数就是level[len-1]
			//len=2时，即要寻找第二层的顶点个数，len-1=1，故要把第一层的顶点都出队，寻找第二层的顶点入队
			//当len=6时，要把第5层的顶点都出队，寻找第6层的顶点入队，入队完后可以不需要出队，因为我们只需要计算涵盖的顶点个数visit_num
			//在入队时我们就已经记下了顶点个数visit_num，所以最后一层出不出队都无所谓
			int e=OutQueue(&Q);  //将顶点一个个出队，用e接收
			Arcnode* p = G->Vlist[e].first; 
			while (p)
			{  //寻找顶点e的邻接顶点，即寻找下一层
				if (visited[p->adjvex] == 0)   //如果顶点未被访问果，则将该邻接顶点计入
				{
					visited[p->adjvex] = 1;   //将访问状态改为1
					visit_num++;   //计入已经计算的顶点个数
					level[len]++;   //计入下一层的顶点个数
					EnQueue(&Q, p->adjvex);   //入队
				}
			}
		}
	}
	printf("百分比为：%d", 100 * visit_num / G->vexnum);
}