#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define MVNum 100
//最小生成树
//普利姆算法
//在一个连通网中，U为已选中顶点的集合，V为所有顶点的集合，则V-U为未选中顶点的集合，TE为连通网上最小生成树中边的集合
//起初，U中有一个起始顶点，寻找起始顶点的权值最小的边，把边并入集合TE并将边依附的另一个顶点并入集合U。
//  再寻找U中顶点的权值最小的边，再将选中的权值最小的边并入U
//例如：
//   在一个图中，一共有n个顶点。
//   起始顶点为v1，找到一条依附于v1的权值最小的边，同时也依附于v3，则将v3并入U，将这条边并入TE，再寻找集合U中顶点（v1，v3）与其相连的权值最小的边
//  把这条边再并入TE，找到该边依附的另一个顶点，再将其并入U，以此类推，直到U中包含所有顶点，此时TE中必有n-1条边
//如果选择最小边时，存在多条同样权值的边，任选其一即可。全部选完后，由U和TE构成的图就是最小生成树
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
		scanf("%c %c%d", &v1, &v2, &w);
		int p = Located(v1, G);
		int q = Located(v2, G);
		G->arcs[p][q] = w;
		G->arcs[q][p] = w;
	}
}
struct edge //创建数组closedge，用于记录从U到V-U具有最小权值的边
{   //对于每一个在V-U集合中的顶点，都存储这最小边上的权值，和最小边在U中的那个顶点
	int adjvex;   //最小边在U中的那个顶点
	int lowweight;   //最小边上的权值
}closedge[MVNum];
int Min(AMGraph* G,struct edge closedge[])
{
	int min = INT_MAX;    //min用来寻找最小值，把min初始化为最大权值（看作无穷）
	int pos = 0;
	for (int i = 0; i < G->vexnum; i++)
	{
		if (closedge[i].lowweight != 0 && closedge[i].lowweight < min)  //如果出现不在集合U中的顶点，并且权值小于min
		{ //权值为0则代表该点在集合U中
			min = closedge[i].lowweight; //则更新最小权值min，并用pos记录该顶点的位置
			pos = i;
		}
	}
	return pos;
}
void MiniSpanTree_Prim(AMGraph *G, char v)  //v为创建最小生成树的起始顶点
{
	int k = Located(v, G);  //找到顶点v的下标k
	for (int i = 0; i < G->vexnum; i++)   //初始化数组closedge
	{
		if (i != k)
		{
			closedge[i].adjvex=k;   //设其他顶点都是顶点v的邻接顶点，只不过权值不一样罢了，权值为INT_MAX则不是邻接顶点
			closedge[i].lowweight = G->arcs[k][i];   //将顶点v到其他顶点的权值也记录下来
		}
		closedge[k].lowweight = 0;   //自己到自己没有权值，所以权值设为0
	}
	for (int i = 1; i < G->vexnum; i++)   //选择其余n-1个顶点，所以循环n-1次
	{
		int min = Min(G,closedge);  //寻找邻接顶点中权值最小的边，将邻接顶点（在集合V-U中）的下标赋值给min
		int v0 = closedge[min].adjvex;   //最小边的起点
		int u0 =min;   //最小边的终点
		printf("%c-->%c\n", G->Vlist[v0], G->Vlist[u0]);
		closedge[u0].lowweight = 0;   //该顶点并入集合U
		//这里对权值为0则并入集合U做解释：
		// 普利姆算法找最小边是在集合U中的所有顶点里找的，比如集合U中有1，3，5三个顶点，那么找最小边是找1，3，5这三个顶点发出的最小权值边
		//  而closedge数组是存放在V-U集合中的顶点的，要找这些顶点到1，3，5的边的最小权值边，而对于顶点1，3，5来说，他们已经被选入最小生成树了
		//所以不需要再作为V-U集合中的顶点来寻找最小权值边了，所以把他们在closedge数组里代表的顶点的权值置为0
		// 然后再在Min函数里加一个条件，如果所代表的顶点权值为0，则跳过该顶点寻找最小边
		for (int j = 0; j < G->vexnum; j++)      //更新closedge数组
		{
			if (G->arcs[u0][j] < closedge[j].lowweight)   //集合U中多了顶点u0，如果V-U中的顶点到u0的最小边的权值比到v的权值还小
			{                                           //那么就将权值更新，权值应是到U中顶点的边的最小权值
				closedge[j].adjvex = u0;    
				closedge[j].lowweight = G->arcs[u0][j];
			}
		}
	}
}
int main()
{
	AMGraph G;
	CreatGraph(&G);
	MiniSpanTree_Prim(&G, '1');
	return 0;
}