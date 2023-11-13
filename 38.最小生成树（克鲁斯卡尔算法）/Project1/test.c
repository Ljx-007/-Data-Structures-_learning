#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define MVNum 100
//克鲁斯卡尔算法(Kruskal)
//Prim算法是一个一个顶点的并入集合U，而Kruskal算法是一下子将所有的顶点全部包含进U，然后一条一条边来选择
//简单来说，Prim算法是选择顶点，Kruskal算法是选择边
//Kruskal算法过程：
// 将一个无向图去掉所有的边，只留下顶点，然后选择权值最小的边，连接其依附的两个顶点，接着再选择权值次小的边，连接其依附的两个顶点，以此类推。
//  连接过程中不能形成回路，如果选择的最小边连接后会形成回路，则舍弃此边选择下一条权值最小的边。直到形成最小生成树为止
//   注意：如果选择最小边时，可能有多条同样权值的边可以选，则任选其一。Kruskal算法的最小生成树不唯一
typedef struct AMGraph
{
	char Vlist[MVNum];
	int arcs[MVNum][MVNum];
	int arcnum, vexnum;
}AMGraph;
int Located(char v, AMGraph* G)
{
	for (int i = 0; i < G->vexnum; i++)
	{
		if (G->Vlist[i] == v)
			return i;
	}
	return -1;
}
void CreatGraph(AMGraph* G)   //创建无向网
{
	printf("输入网的顶点个数和边数：");
	scanf("%d%d", &G->vexnum, &G->arcnum);
	for (int i = 0; i < G->vexnum; i++)
	{
		char c;
		while ((c = getchar()) != '\n') { ; }
		printf("输入顶点信息：");
		scanf("%c", &G->Vlist[i]);
	}
	for (int i = 0; i < G->vexnum; i++)
	{
		for (int j = 0; j < G->vexnum; j++)
			G->arcs[i][j] = INT_MAX;
	}
	for (int i = 0; i < G->arcnum; i++)
	{
		char v1, v2;
		int w;
		while ((v1 = getchar()) != '\n') { ; }
		printf("输入边依附的两个顶点及其权值：");
		scanf("%c %c %d", &v1, &v2, &w);
		int p = Located(v1, G);
		int q = Located(v2, G);
		G->arcs[p][q] = w;
		G->arcs[q][p] = w;
	}
}
//算法的实现要引入一个辅助数组存储边的信息，包括边的两个顶点和权值
typedef struct Edge
{
	int v0,u0;
	int weight;
}Edge;
void InitEdge(Edge* Arredge,AMGraph* G)
{
	for (int i = 0; i < G->vexnum; i++)   //因为无向网存储为邻接矩阵形式时，邻接矩阵是一个对称矩阵，所以只需要遍历一半的矩阵即可
	{                              //即上三角矩阵或者下三角矩阵，因为我们只要记录边的信息就可以，邻接矩阵因为对称，有重复的边的信息，所以只遍历一半
		for (int j = i; j < G->vexnum; j++)  //令j==i，循环执行时就成功遍历上三角矩阵了
		{
			if (G->arcs[i][j] != INT_MAX)
			{
				Arredge->v0 = i, Arredge->u0 = j;
				Arredge->weight = G->arcs[i][j];
				Arredge++;
			}
		}
	}
}
int cmp(const void* e1, const void* e2)
{
	return ((Edge*)e1)->weight - ((Edge*)e2)->weight;
}
void Kruskal_AM(AMGraph* G)
{
	Edge* Arredge = (Edge*)malloc(sizeof(Edge) * G->arcnum);
	InitEdge(Arredge,G);
	qsort(Arredge, G->arcnum, sizeof(Edge), cmp);   //用qsort函数对Edge数组里的权值从低到高进行排序
	//还要引入一个辅助数组Vexsex来标识各个顶点所属的连通分量，即辨别是否有回路产生
	//假设v1和v2在同一个连通分量里，那么其数组元素应相同，即vs1=vs2
	//最开始每一个顶点都自己为一个连通分量，如果后续遇到相同连通分量的顶点，则代表添加这条边就会构成回路
	int* Vexset = (int*)malloc(sizeof(int) * G->vexnum);
	for (int i = 0; i < G->vexnum; i++)
	{
		Vexset[i] = i;    //初始化数组Vexset，每一个顶点的元素都不相同，代表各自为一个连通分量
	}
	for (int i = 0; i < G->arcnum; i++)
	{
		int v0 = Arredge[i].v0;   //获取最小权值边的两个顶点
		int u0 = Arredge[i].u0;
		int vs0 = Vexset[v0];    //获取这两个顶点的连通分量
		int us0 = Vexset[u0];
		if (vs0 != us0)   //如果这两个顶点不是属于同一个连通分量，那么说明连接这两个顶点不会产生回路
		{
			printf("%c-->%c\n", G->Vlist[v0], G->Vlist[u0]);    //打印出连通的信息
			for (int j = 0; j < G->arcnum; j++)    //更新Vexset数组
			{
				if (Vexset[j] == us0)   //因为连通分量为us0的顶点已经被纳入另一个连通分量了，说明一整个us0代表的连通分量都被纳入到vs0了
					                   //vs0代表的是另外一个连通分量
					Vexset[j] = vs0; //所以凡是连通分量为us0的顶点，都要改为vs0
			}
		}
	}
}
//Kruskal的时间复杂度为O(elog2 e),适合求稀疏网的最小生成树
//Prim的时间复杂度为O(n^2)，适合求稠密网的最小生成树
int main()
{
	AMGraph G;
	CreatGraph(&G);
	Kruskal_AM(&G);
	return 0;
}