#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
//图的存储结构
//由于图可以有多个前驱和后继，所以图无法用顺序存储结构来表示
//  但是可以借助二维数组来表示元素之间的关系，称为邻接矩阵表示法
//另外，有多个前驱和后继，用链式存储来表示是很自然的事，但到底需要几个指针域来表示前驱和后继？
//  图的链式存储有多种，有邻接表，十字链表和多重链表

//邻接矩阵表示法
//先建立一个顶点表，记录n个顶点的信息；再建立一个二维数组Arcs[n][n]，来表示各个顶点之间的关系
//  如果两个顶点有关系，则二维数组相应表示为1，如果没有，则表示为0
//  顶点表： 0  1  2  3  4  
//          v1 v2 v3 v4 v5
// 无向图：
// 
//   二维数组Arcs[n][n]:
//           0(v1)   1(v2)   2(v3)   3(v4)   4(v5)
//    0(v1)  0       1       0       1		  0   
//   
//    1(v2)  1       0		 1       0		  1
// 
//    2(v3)  0       1       0       1        1             //通过观察可知，对角线上的元素都为0，因为是顶点自身和自身的关系，无连接关系则为0
//                                                        //该矩阵是一个对称矩阵，无向图的邻接对称矩阵都为对称矩阵
//    3(v4)  1       0       1       0        0       //判断无向图顶点的度，则看某顶点所在的那行/那列的1的个数，或那行/那列所有元素之和
// 
//    4(v5)  0       1       1       0        0

//有向图：
//		顶点表： v1  v2  v3  v4
//		二维数组Arcs[4][4]：
//			0(v1)	1(v2)	2(v3)	3(v4)
//	0(v1)   0       1		1		0
// 
//	1(v2)	0		0		0		0          有向图的邻接矩阵一共有多少个1就代表了有向图有多少条边
//											   第i行元素之和表示vi结点的出度，第i列元素之和表示vi结点的入度边
//	2(v3)	0		0		0		1
// 
//	3(v4)	1		0		0		0

//网的存储结构
//网即带权的图，存储方法与图几乎相同，只不过在邻接矩阵中两点的关系值由1改为权值，两点无关则值改为无穷
//  由于计算机无法表示无穷，则采取一个极大的数来代替无穷。权值相当于两点间的距离，无穷则代表通过一点永远无法达到另一点，即两点无关
#define MVNum 100      //定义最大顶点数
#define MAXINT 32767
typedef struct
{
	char vexs[MVNum];    //建立顶点表  假设顶点类型为char
	int arcs[MVNum][MVNum];   //邻接矩阵   假设权值类型为int
	int vexnum, arcnum;       //图当前的顶点数和边数
}AMGraph;

//采用邻接矩阵创建无向网（UDN）
int Locatedvex(char v,AMGraph* G)
{
	for (int i = 0; i < G->vexnum; i++)
	{
		if (v == G->vexs[i])
			return i;
	}
	printf("不存在该顶点");
	return -1;  
}
void CreatUDN(AMGraph* G)
{
	printf("输入无向网的总顶点数和总边数：");
	scanf("%d%d", &G->vexnum, &G->arcnum);
	for (int i = 0; i < G->vexnum; i++)     //建立顶点表
	{
		printf("输入顶点信息：");
		scanf("%c", &G->vexs[i]);
	}
	for (int i = 0; i < G->vexnum; i++)   //初始化邻接矩阵
	{
		for (int j = 0; j < G->vexnum; j++)
		{
			G->arcs[i][j] = MAXINT;
		}
	}
	for (int i =0; i < G->arcnum; i++)
	{
		char e1, e2;
		int w;
		printf("请输入两个顶点及与其关联的边的权值：");
		scanf("%c%c%d", &e1, &e2, &w);
		int p = Locatedvex(e1, G);
		int q = Locatedvex(e2, G);  //确定输入两个顶点的在顶点表的下标
		G->arcs[p][q] = w;
		G->arcs[q][p] = w;   //因为无向图/无向网的邻接矩阵是对称的，有向网则不需要这一步
	}
}
//邻接矩阵法的优点
//1.便于判断两个顶点是否有边
//2.便于计算各个顶点的度。对于无向图，邻接矩阵第i行元素之和就是顶点i的度；对于有向图，第i行元素之和就是顶点i的出度，第i列元素之和就是顶点的入度

//邻接矩阵法的缺点
//1.不便于增加和删除顶点
//2.不便于统计边的数目，需要扫描邻接矩阵所有元素才能统计完毕，时间复杂度为O(n^2)
//3.空间复杂度高。

//邻接表
//邻接表依旧需要一个顶点表，在这个顶点表中，对图中的每一个结点vi建立一个单链表，把与vi相邻接的顶点放在这个链表中
//而顶点表由一个一维数组组成，该数组的数组元素为复杂类型，元素内容包含顶点信息，以及与其邻接的顶点的链表地址，这个顶点表称为表头结点表
//表头结点包括数据域和链域，链域指向链表中的第一个结点（即与顶点vi相邻接的第一个邻接点）
//  连接表头结点的链表被称为边表，是存放邻接顶点以及与其关联的边的信息，边表包括邻接点域，链域，如果为无向/有向图的话，则还可以添加一个权值域存放权值

//  0  v1 -> 3 -> 1
//  1  v2 -> 4 -> 2 -> 0       vi为头结点，vi前的数字为头结点组成的一维数组下标，vi后即边表
//  2  v3 -> 4 -> 3 -> 1
//  3  v4 -> 2 -> 0 
//  4  v5 -> 2 -> 1 
//如果用邻接表存储有向图，那么与某条边相关的两个顶点就不需要存储两次边信息了，按照顶点间的方向存储边信息即可
// 有向图的邻接表存储时：顶点vi的出度边个数即边表的结点个数，入度边个数为边表结点的邻接点域值为i的结点个数
//  有向图的邻接表也可以存入度边：那么顶点vi的入度边个数即边表的结点个数，出度边个数为边表结点的邻接点域值为i的结点个数。这样的邻接表称为逆邻接表
typedef struct Arcnode
{
	int adjvex;  //邻接顶点在一维数组中所在的位置下标
	int w;     //边权值
	struct Arcnode* next;   //其他邻接顶点的位置信息
}Arcnode;
typedef struct Vnode   //定义顶点表的头结点类型
{
	char v;
	Arcnode* first;
}Vnode;
typedef struct     //定义图类型
{
	Vnode* VexList[MVNum];  //建立顶点表
	int vexnum, arcnum;  //顶点个数以及边数
}ALGraph;
int Locatedvex2(char v, ALGraph* G)
{
	for (int i = 0; i < G->vexnum; i++)
	{
		if (v == G->VexList[i]->v)
			return i;
	}
	return -1;
}
void CreatUDG(ALGraph* G)
{
	printf("输入无向图的顶点个数以及边个数：");
	scanf("%d%d", &G->vexnum, &G->arcnum);
	for (int i = 0; i < G->vexnum; i++)   //建立顶点表
	{
		printf("输入顶点信息：");
		scanf("%c", &G->VexList[i]->v);
		G->VexList[i]->first = NULL;
	}
	for (int i = 0; i < G->arcnum; i++)   //建立边表
	{
		char v1, v2;
		int w;
		printf("输入两个顶点及其边的权值：");
		scanf("%c%c%d", &v1, &v2, &w);
		int a = Locatedvex2(v1, G);
		int b = Locatedvex2(v2, G);
		Arcnode* p1 = (Arcnode*)malloc(sizeof(Arcnode));   //建立边表结点
		p1->next = G->VexList[a]->first;     //使用头插法插入
		G->VexList[a]->first = p1;
		p1->adjvex = b;
		p1->w = w;
		//无向网中一条边的信息需要两个顶点来存储，所以需要把边信息再存到另外一个顶点的边表
		// 如果是有向网，则无需这步
		Arcnode* p2 = (Arcnode*)malloc(sizeof(Arcnode));
		p2->next = G->VexList[b]->first;     //使用头插法插入
		G->VexList[b]->first = p2;
		p2->adjvex = a;
		p2->w = w;
	}
}