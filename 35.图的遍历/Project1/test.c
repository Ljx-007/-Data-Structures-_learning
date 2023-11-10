#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//�����������--Depth First Search--DFS
//���������������˵������ĳһ��·һֱ�ߣ�ֱ���߲�ͨΪֹ�������ߣ�ֱ����·��,���������������
//�ڽӾ����ʾ������ͼ�����������
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
void ArrCreatWXT(AMGraph* G)        //��������ͼ
{
	printf("�����붥������ͱ߸�����");
	scanf("%d%d", &G->vexnum, &G->arcnum);
	for (int i = 0; i < G->vexnum; i++)
	{
		printf("�����붥����Ϣ:");
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
		printf("������ñ����������������㣺");
		scanf("%c%c", &v1, &v2);
		int p = LocatedWXT(v1, G);
		int q = LocatedWXT(v2, G);
		G->arcs[p][q] = 1;
	}
}
int visited[MVNum] = { 0 };   //��һ��visited��������¼�����Ƿ񱻷��ʹ���0����δ�����ʣ�1��������
void DFS(AMGraph G, int v)  //����Ϊһ������ͼ���ʼ���ʵĶ���
{
	printf("%c ", G.Vlist[v]);
	visited[v] = 1;  //����v�����ʣ���¼������visited��
	for (int i = 0; i < G.vexnum; i++)        //������ά�����ж���v���ڵ����е�ֵ
	{
		if (G.arcs[v][i] != 0 && visited[i] == 0)   //���������ֵ��Ϊ0��˵���ö���v��i�д���Ķ���i֮���бߣ����Ҷ���iû�б����ʹ�
			DFS(G, i);   //�������ʶ���i
	}
}
//�ڽӱ��ʾ��ͼ�������������
typedef struct Vnode
{
	char v;
	struct Arcnode* first;
}Vnode;
typedef struct Arcnode
{
	int v;
	//�����Ȩֵ�����Ȩֵ
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
	printf("�����붥������ͱ�����");
	scanf("%d%d", &G->vexnum, &G->arcnum);
	for (int i = 0; i < G->vexnum; i++)
	{
		printf("�����붥����Ϣ��");
		scanf("%c", &G->Vlist[i].v);
		G->Vlist[i].first = NULL;
	}
	for (int i = 0; i < G->arcnum; i++)
	{
		char v1, v2;
		printf("�������������������������Ϣ��");
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
	printf("%c ", G.Vlist[v].v);  //���ʶ���
	visitedAL[v] = 1;   //��¼�ö���ķ���״̬
	Arcnode* p = G.Vlist[v].first;    //��pָ�򶥵���еı߱�ָ����
	while (p)   //���ָ��Ϊ�գ�˵����ö��������Ķ����Ѿ���������
	{
		int j = p->v;    //��j���ڱ߽���еĶ����±�
		if (visitedAL[j] == 0)  //�������jδ�����ʹ�����ݹ����
			DFS_AL(G, j);
		p = p->next;   //�߱�ָ��ָ����һ��v������ڽӶ���
	}
}
//�ڽӱ�ı�����Ȼ��2e���߽�㣬���Ǳ�����ֻ��Ҫɨ��e����㼴�ɣ��ټ���n��ͷ���ķ��ʣ�ʱ�临�Ӷ�ΪO��n+e��
//�ڽӾ���ı���ʱ�临�Ӷ�ΪO��n^2��
//���ϵ��������������������ͨͼ�����ڷ���ͨͼ�����������������������ʾ
//void DFSTraverse(Graph G) //Graph GΪ����ͨͼ���˴�Graph����δ����
//{
//	for (int i = 0; i < G.vexnum; i++)
//	{
//		visited[i] = 0;  //��ʼ����־����
//	}
//	for (int i = 0; i < G.vexnum; i++)
//	{
//		if (visited[i] == 0)    //�������iδ�����ʣ���Զ���i���ڵ���ͨ�������б�����������iΪ���
//			DFS(G, i);         //������i���ڵ���ͨ�������������ˣ�forѭ���б���visited���飬������ж���δ��������˵���ö��������������ͨ����
//		                //��Ըö������ڵ���ͨ�������б����������Ըö���Ϊ���
//	}
//}

//�����������--Breadth First Search--BFS
//��������������̣�
//�ȴ�ĳ������v����������v���㣬Ȼ�����η���v�ĸ���δ�����ʹ����ڽӵ㣬�ٷֱ���ڽӵ���������ڽӵ���ڽӵ㣬ѭ��������ֱ��ͼ��û�ж���ɷ���
//������������������Ĳ�α��������Թ������������Ҫ�õ�����
//�ڽӱ�Ĺ����������
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
		printf("����\n");
		return;
	}
	Q->que[Q->rear] = v;
	Q->rear = (Q->rear + 1) % MAXSIZE;
}
int OutQueue(SqQueue* Q)
{
	if (Q->front == Q->rear)
	{
		printf("�ӿ�\n");
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
	InitQueue(&Q);   //��ʼ��һ������
	printf("%c ", G->Vlist[v].v);   //��ӡ��һ�����������
	visitedBFS_AL[v] = 1;   //��¼�����ѱ�����
	EnQueue(&Q, v);   //����һ���������
	while (!QueueEmpty(&Q))   
	{
		int e=OutQueue(&Q);    //��e���ճ��Ӷ���
		Arcnode* p = G->Vlist[e].first;   //��p���ճ��Ӷ���ı߱�ָ����
		while (p)   //��ʼ�����߱����������Ӷ�����ڽӶ���
		{
			int i = p->v;   //��i�������ڽӶ�����±�
			if(visitedBFS_AL[i]==0)    //����ڽӶ���û�б����ʹ�������if���
			{
				printf("%c ", &G->Vlist[i].v);
				EnQueue(&Q, i);   //�����ڽӶ��㲢��ӣ���¼������Ϣ
				visitedBFS_AL[i] = 1;
			}
			p = p->next;  //pָ����һ�����Ӷ�����ڽӶ���
		}
	}//ѭ������ʱ����������еĶ����ѱ�������
}

//�ڽӾ���Ĺ����������
int visitedBFS[MVNum] = { 0 };
void BFS(AMGraph* G,int v)
{
	SqQueue Q;
	InitQueue(&Q);
	printf("%c ", G->Vlist[v]);  //�ȷ��ʵ�һ�����㲢��Ӽ�¼������Ϣ
	EnQueue(&Q, v);
	visitedBFS[v] = 1;
	int out;
	while(!QueueEmpty(&Q))   
	{
		out = OutQueue(&Q);   //��out���ճ��Ӷ���
		for(int i=0;i<G->vexnum;i++)
		{   //�����ö����±��Ӧ�ľ������
			if (G->arcs[out][i] != 0 && visitedBFS[i] == 0)   //�����������Ϊ0��ֵ����ô��Ӧ������i��Ϊ�ö�����ڽӶ����±�
			{      //������ڽӶ���iû�б����ʣ�����ʸö��㲢��Ӽ�¼������Ϣ
				printf("%c ", G->Vlist[i]);   
				EnQueue(&Q, i);
				visitedBFS[i] = 1;
			}
		}	
	} //�������whileѭ��˵�������Ѿ�Ϊ�գ����еĶ��㶼����������
}
//�ڽӾ����BFS�㷨ʱ�临�Ӷ�ΪO��n^2��
//�ڽӱ��BFS�㷨ʱ�临�Ӷ�ΪO��n+e��	
//DFS��BFS�ռ临�Ӷ���ͬ���������˶�ջ�Ͷ��У�ʱ�临�Ӷ�ֻ��洢�ṹ�йأ��ڽӾ�����ڽӱ��йأ�������·���޹�