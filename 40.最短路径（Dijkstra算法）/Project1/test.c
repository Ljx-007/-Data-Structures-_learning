#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define MVNum 100
//最短路径
//在带权有向网中，习惯上称路径的第一个顶点为源点，最后一个顶点为终点
//最短路径有两个常见问题：
//1.从某个源点到其余各顶点的最短路径 ---迪杰斯特拉算法（Dijkstra）
//2.所有顶点两两之间的最短路径   --- 弗洛伊德算法（Floyd）
//先来解决第一个问题：从某个源点到其余各顶点的最短路径
//Dijkstra算法思想为
//1.设有一个顶点集S[i]，包含已求出的最短路径的终点集合（初始时只包含源点v0），如果顶点vi已求出最短路径，则S[i]=1。
// 
//2.设立一个数组Path[i]，用来记录源点v0到终点vi的当前最短路径上vi的直接前驱顶点（初始值为：如果v0到vi有弧，则Path[i]=v0，否则为-1）
// 
// 意思就是说，如果一条路径不止源点与终点，那么这个数组Path就是用来记录最短路径中离终点最近的那个顶点，如果只有源点与终点，那么离终点最近的顶点自然为源点
// 
//3.设立一个数组D[i],用来记录源点v0到各个顶点的最短路径长度（初始时为v0到各个顶点的弧长度，如果v0到某个顶点没有弧，就认为路径权值为无穷大）
// 
//4.先求出源点v0到各个顶点的直接路径，如果没有路径能直接到达，则认为其路径权值为无穷大，将这些数值存入数组D[i]中
// 
//5.再从数组中找出一个最短的路径，并将顶点加入顶点集，表示由源点到该顶点已找到最短路径
//   例如从源点v0到v2的直接路径最短，则把顶点v2加入顶点集S，然后记录其权值
//
//6.新的顶点加入顶点集后，对V-S中的顶点来说，从源点到终点不只有直达的弧可以选择，还可以通过新加入的顶点作为中转站，以此寻找是否有更短的路径达到终点
// 如果通过中转站找到了一条更短的路径，那么就用该路径来代替之前达到终点的最短路径，然后再将D[i]数组中具有最短路径的顶点加入顶点集S
//
//7.依次类推，直到所有顶点都加入了最短路径的顶点集S，至此源点v0到各顶点的最短路径全部找到

//邻接矩阵型
#define MAXW 32767
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
void CreatGraph(AMGraph* G)   //创建有向网
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
			G->arcs[i][j] = MAXW;
	}
	for (int i = 0; i < G->arcnum; i++)
	{
		char v1, v2;
		int w;
		while ((v1 = getchar()) != '\n') { ; }
		printf("以有向顺序输入边依附的两个顶点及其权值：");
		scanf("%c %c %d", &v1, &v2, &w);
		int p = Located(v1, G);
		int q = Located(v2, G);
		G->arcs[p][q] = w;
	}
}
void ShortestPath_DIJ(AMGraph* G, char v,int* S,int* D,int *Path)   //顶点v为源点
{
	int v0 = Located(v, G);  //令源点v的下标为v0
	//初始化三个数组
	for (int i = 0; i < G->vexnum; i++)   
	{
		S[i] = 0;    //所有顶点都还未加入顶点集S
		D[i] = G->arcs[v0][i];    //所有顶点到源点的直接路径存入数组D[i]，如果没有直接路径，则为无穷大（在创建有向网时就已确定）
		if (D[i] < MAXW)   //如果有顶点到源点有弧，那么该顶点在最短路径中的前驱顶点初始化为源点
			Path[i] = v0;
		else
			Path[i] = -1;  //否则初始化为-1，代表源点v0暂时没有路径能够到达顶点vi
	}
	S[v0] = 1, D[v0] = 0;   //将源点v加入顶点集S，源点到源点的路径长度初始化为0
	int u;
	for (int i = 1; i < G->vexnum; i++)   //依次添加剩下的n-1个顶点
	{
		int min = MAXW;   //用min来代表最小路径长度，最开始将最小路径长度初始化为权值无穷大
		for (int j = 0; j < G->vexnum; j++)   //遍历各个顶点，找出没有被加入顶点集并且到源点路径最短的顶点
		{
			if (S[j] == 0 && D[j] < min)   //选择一条当前的最短路径，终点为u
			{
				min = D[j];   //更新最小值
				u = j;  //用u来标记遍历出的最小路径长度的顶点
			}
		}
		S[u] = 1;  //将该顶点加入顶点集S
		for (int j = 0; j < G->vexnum; j++)  //因为有中转站顶点u的加入，所以要更新从源点出发到各个顶点的最短路径长度
		{
			//对于已经找到最短路径的顶点（即已经加入顶点集S的顶点），无需再更新它的最短路径长度，因为已经找到了，所以要更新的顶点为没有加入顶点集的顶点
			//对于没有加入顶点集的顶点，有了中转站顶点u的加入，要判断有了中转站后，最短路径有没有更短，如果更短则要更新最短路径长
			if (S[j] == 0 && (D[u] + G->arcs[u][j]) < D[j])
			{
				//如果加了中转站后对于顶点j来说路径更短了，那么顶点j到源点的最短路径就是中转站顶点u到源点的最短路径加上顶点j到中转站顶点u的路径
				D[j] = D[u] + G->arcs[u][j];
				Path[j] = u;    //并将顶点j的前驱改为u，因为源点是经过顶点u后才到达顶点j
			}
		}
	}
}
//至此邻接矩阵型的Dijstra算法结束
//若想查询源点到某点的最短路径，则查询数组Path[i]即可
int main()
{
	AMGraph G;
	CreatGraph(&G);
	//创建三个数组分别记录
	int* S = malloc(sizeof(int) * G.vexnum);   //已求出最短路径的顶点的顶点集
	int* D = malloc(sizeof(int) * G.vexnum);   //各个顶点的最短路径长度
	int* Path = malloc(sizeof(int) * G.vexnum);  //各个终点在各自最短路径中的前驱顶点，也就是在路径中离终点最近的顶点
	char v0, u0;
	printf("输入源点与终点求最短路径：");
	while ((v0 = getchar()) != '\n');
	scanf("%c %c", &v0, &u0);
	ShortestPath_DIJ(&G, v0, S, D, Path);   //用迪杰斯特拉算法找出各顶点到源点的最短路径后打印路径
	int v = Located(v0, &G);   //获取源点和终点的下标   
	int u = Located(u0, &G);
	int* arr = malloc(sizeof(int) * G.vexnum);   //因为最短路径是从终点寻回源点的，路径为倒序，所以要用到栈来正确打印路径
	int front = 0;
	int rear = 0;
	while (u != v)
	{
		arr[rear] = u;   //先将终点放入栈底，再一个个将路径上的点倒着存进栈，栈顶为源点，这样弹出栈顶元素后就是正确的顺序了
		rear++;
		u = Path[u];
	}
	arr[rear++] = u;   //出循环后栈顶元素还为入栈，将栈顶元素入栈
	int i,j;  
	i = arr[--rear];
	while (rear != front)  //当栈空时结束循环
	{
		j = arr[--rear];  //令i，j为路径顶点下标，i下标的路径顶点在j下标的路径顶点前
		printf("%c-->%c\n",G.Vlist[i],G.Vlist[j]);   //打印路径
		i = j;   //这行代码是让路径的打印呈现衔接效果，i等于j原来代表的顶点，j为路径下一个顶点
	}
	free(Path), Path = NULL;
	free(S), S = NULL;
	free(D), D = NULL;
	return 0;
}