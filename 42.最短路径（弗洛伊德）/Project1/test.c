#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include<stdlib.h>
#define MVNum 100
#define MAXW 32767
//最短路径--每一对顶点间的最短路径
//计算每一对顶点间的最短路径有两种方法：
// 1.对每一个顶点都使用Dijkstra算法
// 2.弗洛伊德(Floyd)算法
//两者的时间复杂度都为O(n^3)，但后者形式上更简单
// 
//弗洛伊德算法要用邻接矩阵实现而不用邻接表是因为需要O(1)时间查询任意两个顶点的边权值，最后才能使时间复杂度达到O（n^3）
//弗洛伊德算法（Floyd）
//算法思想：
//1.引入二维数组Path[i][j]来记录从顶点vi到vj的最短路径上顶点vj的前一顶点的序号
//2.引入二维数组D[i][j]来记录顶点vi和vj之间的最短路径长度
//3.先将各个顶点两两之间的权值记录下来，采用邻接矩阵的方式，顶点与自己的距离为0
//4.接下来试着在原路径（矩阵）中增加中间顶点，若增加中间顶点后路径变短，则修改矩阵的权值，否则维持原来的值，直到所有的顶点都增加为中间顶点，则结束
typedef struct 
{
	char Vlist[MVNum];
	int arcs[MVNum][MVNum];
	int vexnum, arcnum;
}AMGraph;
int Located(char v,AMGraph* G)
{
	for (int i = 0; i < G->vexnum; i++)
	{
		if (v == G->Vlist[i])
			return i;
	}
	return -1;
}
void CreatYXW(AMGraph* G)
{
	printf("输入顶点数和边数：");
	scanf("%d%d", &G->vexnum, &G->arcnum);
	char c;
	for (int i = 0; i < G->vexnum; i++)
	{
		while ((c = getchar()) != '\n') { ; }
		printf("输入顶点信息:");
		scanf("%c", &G->Vlist[i]);
	}
	for (int i = 0; i < G->vexnum; i++)
	{
		for (int j = 0; j < G->vexnum; j++)
		{
			if (i == j)
				G->arcs[i][j] = 0;
			else
				G->arcs[i][j] = MAXW;
		}
	}
	for (int i = 0; i < G->arcnum; i++)
	{
		char v1, v2;
		int w;
		printf("以有向顺序输入两个顶点及其边权值：");
		while ((c = getchar()) != '\n') { ; }
		scanf("%c %c %d", &v1, &v2, &w);
		int m = Located(v1, G);
		int n = Located(v2, G);
		G->arcs[m][n] = w;
	}
}
void ShortestPath_Floyd(AMGraph* G,int** D,int** Path)
{
	for (int i = 0; i < G->vexnum; i++)  
	{
		for (int j = 0; j < G->vexnum; j++)   //初始化二维数组D和Path
		{
			D[i][j] = G->arcs[i][j];   //最开始vi到vj的最短路径为两顶点间的直接路径，即弧权值
			if (D[i][j] < MAXW && i != j)  //如果顶点vi和vj间有弧，即权值不为无穷，并且vi和vj不是同一个顶点
				Path[i][j] = i;     //则将vi到vj的最短路径上vj的前驱顶点修改为vi顶点
			else
				Path[i][j] = -1;   //如果vi和vj之间没弧，则vj前驱改为-1
		}
	}
	for (int i = 0; i < G->vexnum; i++)
	{
		for (int j = 0; j < G->vexnum; j++)   //前两个循环是为了遍历二维数组D和Path
		{
			for (int k = 0; k < G->vexnum; k++)   //第三个循环是一个一个增加中间顶点
			{
				if ((D[i][k] + D[k][j]) < D[i][j])       //如果增加了顶点vk作为中间顶点，且加入后vi到vj之间通过vk顶点比原来的路径更短
				{
					D[i][j] = D[i][k] + D[k][j];   //则用更短的路径代替原路径
					Path[i][j] = Path[k][j];  //并将原来的顶点i到j的前驱顶点改为顶点k到j的前驱顶点
				}
			}
		}
	}
}
int main()
{
	AMGraph G;
	CreatYXW(&G);
	int** D = malloc(sizeof(int*) * G.vexnum);
	int** Path = malloc(sizeof(int*) * G.vexnum);
	for (int i = 0; i < G.vexnum; i++)
	{
		D[i] = malloc(sizeof(int) * G.vexnum);
		Path[i] = malloc(sizeof(int) * G.vexnum);
	}
	ShortestPath_Floyd(&G, D, Path);
	char v, u;
	printf("输入源点与终点顶点信息：");
	while ((v = getchar()) != '\n') { ; }
	scanf("%c %c", &v, &u);
	int v0= Located(v, &G);
	int u0 = Located(u, &G);
	int* stack = malloc(sizeof(int) * G.vexnum);
	int top, base;
	top = base = 0;
	while (u0 != v0)
	{
		stack[top++] = u0;
		u0 = Path[v0][u0];
	}
	int i=v0;
	int j;
	while (base != top)
	{
		j= stack[--top];
		printf("%c-->%c\n", G.Vlist[i], G.Vlist[j]);
		i = j;
	}
	return 0;
}