#define _CRT_SECURE_NO_WARNINGS 1	
//十字链表---有向图的另一种链式存储
//邻接表表示法不便于判断顶点之间是否有边，且不容易判断入度边，于是引入十字链表
//十字链表可以看成将邻接表和逆邻接表结合起来得到的一种链表。在十字链表中，对于有向图的每一条弧和每一个顶点都有一个结点表示
//在十字链表中，弧结点弧头相同连接成的链表为出度边表，弧尾相同连接成的链表为入度边表
#define MVNum 100
typedef struct Vexnode    //定义顶点表结点
{
	char v;    //顶点信息
	struct Arcnode* firstin;    //入度边表
	struct Arcnode* firstout;   //出度边表
}Vexnode;
typedef struct Arcnode        //定义弧结点
{
	int headvex;   //弧的头顶点
	int tailvex;      //弧的尾顶点
	struct Arcnode* hlink;    //弧头相同的边表，即出度边表
	struct Arcnode* tlink;    //弧尾相同的边表，即入度边表
	int w;       //权值
}Arcnode;
typedef struct
{    //定义有向图
	Vexnode Vlist[MVNum];
	int vexnum, arcnum;
}OLGraph;

//邻接多重表---无向图的另一种链式存储
//由于无向图的邻接表每一条边都要访问两次，增加了空间复杂度，所以，邻接多重表让无向图的每条边只用访问一次
//与邻接表类似，邻接多重表的顶点表不变，依旧是顶点信息和边表指针域
//变化的是边表结点的内容，边表结点包含该条边所依附的两个顶点的信息，以及依附于其中一个顶点的边结点指针和依附于另一个顶点的边结点指针
// 此外还可以添加权值，和标记。标记则用来判断该边是否被访问过
typedef struct Vexnode    //定义顶点表
{
	char v;    //顶点信息
	struct Arcnode* firstedge;   //依附顶点的第一条边的结点指针
}Vexnode;
typedef struct Arcnode         //定义边表结点
{
	int mark;    //访问标志
	int ivex;    //该边依附于两个顶点的信息
	int jvex;
	struct Arcnode* ilink, * jlink;     //依附于该边依附于两个顶点的其他的边的结点指针
	int w;  //权值
}Arcnode;
typedef struct       //定义无向图
{
	Vexnode Vlist[MVNum];   //建立顶点表
	int vexnum, arcnum;     //顶点数和边数
}AMLGraph;