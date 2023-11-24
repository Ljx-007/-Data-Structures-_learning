#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define MVNum 100
#define MAXINT 32767
//�㷨�����
//1.�ֱ����ڽӾ�����ڽӱ���Ϊ�洢�ṹ��ʵ������ͼ�Ļ���������
// ��1������һ���¶��㣬InsertVex(G,v)
// ��2��ɾ������v������صıߣ�DeleteVex(G,v)
// ��3������һ����<v,w>,InsertArc(G,v,w)
// ��4��ɾ��һ����<v,w>,DeleteArc(G,v,w)
typedef struct Vnode
{
	char v;
	struct Arcnode* first;
}Vnode;
typedef struct Arcnode
{
	int adjvex;
	int weight;
	struct Arcnode* next;
}Arcnode;
typedef struct
{
	Vnode Vlist[MVNum];
	int vexnum, arcnum;
}AMLGraph;
typedef struct AMGraph
{
	char Vlist[MVNum];
	int arcs[MVNum][MVNum];
	int vexnum, arcnum;
}AMGraph;
int AM_Located(AMGraph* G, char v)
{
	for (int i = 0; i < G->vexnum; i++)
	{
		if (G->Vlist[i] == v)
			return i;
	}
	return -1;
}
int AML_Located(AMLGraph* G, char v)
{
	for (int i = 0; i < G->vexnum; i++)
	{
		if (G->Vlist[i].v == v)
			return i;
	}
	return -1;
}
//(1)
// �ڽӾ���
void InsertVex_AM(AMGraph* G, char v)
{
	if (G->vexnum + 1 > MVNum)
		return;
	G->Vlist[G->vexnum + 1] = v;
	G->vexnum++;
}
//�ڽӱ�
void InsertVex_AML(AMLGraph* G, char v)
{
	if (G->vexnum + 1 > MVNum)
		return;
	G->Vlist[G->vexnum ].v = v;
	G->Vlist[G->vexnum ].first = NULL;
	G->vexnum++;
}
//(2)
// �ڽӾ���
void AM_DeleteVex(AMGraph* G, char v)
{
	int k = AM_Located(G, v);
	if (G->vexnum == 0||k==-1)
		return;
	//����k������ֱ�Ӻ����һ�����㽻��λ�ã�������ú����������ǰ��Ķ���Ļ�����ܸ���
	G->Vlist[k] = G->Vlist[G->vexnum-1];
	for (int i = 0; i < G->vexnum; i++)
	{
		G->arcs[k][i] = G->arcs[G->vexnum - 1][i];   //�ߵĹ�ϵҲ�������һ�������
	}
	G->vexnum--;
}
// �ڽӱ�
void AML_DeleteVex(AMLGraph* G, char v)
{
	int k = AML_Located(G, v);
	if (G->vexnum == 0 || k == -1)
		return;
	G->Vlist[k].v = G->Vlist[G->vexnum - 1].v;
	G->Vlist[k].first = G->Vlist[G->vexnum-1].first;
	G->vexnum--;
}
//(3)
// �ڽӾ���
void AM_InsertArc(AMGraph* G, char v, char w)
{
	int v0 = AM_Located(G, v);
	int w0 = AM_Located(G, w);
	if (v0 == -1 || w0 == -1||v0==w0)
		return;
	if (G->arcs[v0][w0] != 0)
	{
		printf("���Ѵ���");
		return;
	}
	else
	{
		G->arcs[v0][w0] = 1;
		G->arcnum++;
	}
}
// �ڽӱ�
void AML_InsertArc(AMLGraph* G, char v, char w)
{
	int v0 = AML_Located(G, v);
	int w0 = AML_Located(G, w);
	if (v0 == -1 || w0 == -1 || v0 == w0)
		return;
	Arcnode* p = (Arcnode*)malloc(sizeof(Arcnode));
	p->adjvex = w0, p->next = NULL;
	Arcnode* h = G->Vlist[v0].first;
	while (h)      //��������v�ı߱��������v�Ͷ���w����ڱߣ���ô��ֱ�ӷ��أ������ھͰ���������Ϣ���ڱ߱��
	{
		if (h->adjvex = w0)
		{
			printf("���Ѵ���");
			return;
		}
		h=h->next;
	}
	h = p;
	G->arcnum++;
}
//��4��
// �ڽӾ���
void AM_DeleteArc(AMGraph* G, char v, char w)
{
	int v0 = AM_Located(G, v);
	int w0 = AM_Located(G, w);
	if (v0 == -1 || w0 == -1 || v0 == w0)
		return;
	if (G->arcs[v0][w0] == 0)
	{
		printf("�ñ߲�����");
		return;
	}
	else
	{
		G->arcs[v0][w0] = 0;
		G->arcnum--;
	}
}
// �ڽӱ�
void AML_DeleteArc(AMLGraph* G, char v, char w)
{
	int v0 = AML_Located(G, v);
	int w0 = AML_Located(G, w);
	if (v0 == -1 || w0 == -1 || v0 == w0)
		return;
	Arcnode* p = G->Vlist[v0].first;
	Arcnode* q = p->next;
	if (p->adjvex == w0)   //�߱��һ��Ԫ�ؾ���Ҫɾ���ı�
	{
		Arcnode* f = p;
		p = p->next;
		free(f), f = NULL;
		return;
	}
	while (q)  //��һ��Ԫ�ز���Ҫɾ���ı�
	{
		if (q->adjvex == w0)
		{
			Arcnode* f = q;
			p->next = q->next;
			p = p->next, q = q->next;
			free(f), f = NULL;
			return;
		}
		else
			p = p->next, q = q->next;
	}
	//�������ѭ����˵���ڱ߱���û���ҵ������ߣ��������߲�����
	printf("�ñ߲�����"); 
}
//2.һ����ͨͼ�����ڽӱ���Ϊ�洢�ṹ�����һ���㷨��ʵ�ִӶ���v������������ȱ����ķǵݹ����
typedef struct Stack
{
	int* base;
	int* top;
	int sizemax;
}Stack;
void InitStack(Stack* S,int n)
{
	S->base = (int*)malloc(sizeof(int) * n);
	S->top = S->base;
	S->sizemax = n;
}
void Push(Stack* S, int v)
{
	if ((S->top - S->base) == S->sizemax)
	{
		printf("ջ��");
		return;
	}
	*S->top++ = v;
}
int Pop(Stack* S)
{
	if (S->top == S->base)
	{
		printf("ջ��");
		return -1;
	}
	int e = *--S->top;
	return e;
}
int IsEmpty(Stack* S)
{
	if (S->top == S->base)
		return 1;
	return 0;
}
void CreatWXT(AMLGraph* G)
{
	char c;
	printf("���붥�����ͱ�����");
	scanf("%d%d", &G->vexnum, &G->arcnum);
	for (int i = 0; i < G->vexnum; i++)
	{
		printf("���붥����Ϣ��");
		while ((c = getchar()) != '\n') { ; }
		scanf("%c", &G->Vlist[i].v);
		G->Vlist[i].first = NULL;
	}
	for (int i = 0; i < G->arcnum; i++)
	{
		char v1, v2;
		//int w;
		printf("�������������㣺");
		while ((c = getchar()) != '\n') { ; }
		scanf("%c %c", &v1, &v2);
		int m = AML_Located(G, v1);
		int n = AML_Located(G,v2);
		Arcnode* p = malloc(sizeof(Arcnode));
		p->adjvex = n;
		//p->weight = w;
		p->next = G->Vlist[m].first;
		G->Vlist[m].first = p;
		Arcnode* q = malloc(sizeof(Arcnode));
		q->adjvex = m;
		//q->weight = w;
		q->next = G->Vlist[n].first;
		G->Vlist[n].first = q;
	}
}
void DFS_notre(AMLGraph* G, char v)
{
	Stack S;
	InitStack(&S,G->vexnum);
	int v0 = AML_Located(G, v);
	int* visited = (int*)calloc(sizeof(int),G->vexnum);
	if (v0 == -1)
		return;
	Arcnode* p = G->Vlist[v0].first;
	printf("%c ", G->Vlist[v0].v);
	Push(&S, v0);
	visited[v0] = 1;
	while (p)
	{
		if (visited[p->adjvex] == 0)
		{
			printf("%c ", G->Vlist[p->adjvex].v);
			Push(&S, p->adjvex);
			visited[p->adjvex] = 1;
			p = G->Vlist[p->adjvex].first;
		}
		else
		{
			p = p->next;
			if (!p&&!IsEmpty(&S))
			{
				int e = Pop(&S);
				p = G->Vlist[e].first;
			}
		}
	}
}
//3.���һ���㷨����ͼG�о��붥��v�����·����������һ�����㡣��v�ɴ������������
int LongestPath(AMLGraph* G, char v)
{  //��Dijkstra�㷨�����·��
	int v0 = AML_Located(G, v);
	if (v0 == -1)
		return -1;
	int* S = (int*)malloc(sizeof(int) * G->vexnum);
	int* D = (int*)malloc(sizeof(int) * G->vexnum);
	int* Path = (int*)malloc(sizeof(int) * G->vexnum);
	for (int i = 0; i < G->vexnum; i++)
	{
		S[i] = 0;
		D[i] = MAXINT;
		Path[i] = -1;
	}
	S[v0] = 1, D[v0] = 0;
	Arcnode* p = G->Vlist[v0].first;
	while (p)
	{
		D[p->adjvex] = p->weight;
		Path[p->adjvex] = v0;
		p = p->next;
	}
	//Ѱ�Ҿ���v0�����·���Ķ���
	for(int j=1;j<G->vexnum;j++)  //��ʣ��n-1��������м���
	{
		int min = MAXINT;
		int pos;
		for (int i = 0; i < G->vexnum; i++)
		{
			if (S[i] == 0 && D[i] < min)
			{
				min = D[i];
				pos = i;
			}
		}
		S[pos] = 1;
		p = G->Vlist[pos].first;
		while (p)
		{
			if (S[p->adjvex] == 0 && D[p->adjvex] > D[pos] + p->weight)
			{
				D[p->adjvex] = D[pos] + p->weight;
				Path[p->adjvex] = pos;
			}
			p = p->next;
		}
	}
	//����������·��Ѱ������������ֵ
	int max = 0;
	int pos2;
	for (int i = 1; i < G->vexnum; i++)
	{
		if (D[i] > max&&D[i]!=MAXINT)
		{
			max = D[i];
			pos2 = i;
		}
	}
	printf("���·���������Ķ���Ϊ��%c ,����Ϊ%d", G->Vlist[pos2].v,D[pos2]);
	return pos2;
}
//4.�Ի���ͼ�����������������дһ�㷨���б����ڽӱ�ʽ�洢������ͼ���Ƿ���ڶ���vi������vj��·����i!=j��
int IsPath_DFS(AMLGraph* G, char v, char u,int* visited)
{
	int v0 = AML_Located(G, v);
	int u0 = AML_Located(G, u);
	if (u0 == -1 || v0 == -1 || u0 == v0)
		return -1;
	visited[v0] = 1;
	static int ret = 0;   //���þ�̬������¼�Ƿ������˶���u0�������������u0��ret=1������һֱΪ0��
	Arcnode* p = G->Vlist[v0].first;
	while (p)
	{
		if (visited[p->adjvex] == 0)
		{
			visited[p->adjvex] = 1;
			if (p->adjvex == u0)
				ret = 1;
			IsPath_DFS(G, G->Vlist[p->adjvex].v, u, visited);
		}
		p = p->next;
	}
	return ret;
}
//��5�������ڽӱ�洢�ṹ����дһ���㷨���б�����ͼ�������������������֮���Ƿ����һ������Ϊk�ļ�·��
int IsPath(AMLGraph* G, char v,char u,int k,int* visited)
{
	int v0 = AML_Located(G, v);
	int u0 = AML_Located(G, u);
	if (u0 == -1 || v0 == -1||k<0)
		return -1;
	if (v0 == u0 && k == 0)   //�������������������һ�����㣬������֮�䳤��Ϊ0�����������������1
		return 1;
	Arcnode* p = G->Vlist[v0].first;
	visited[v0] = 1;
	static int ret = 0;   //�þ�̬����ret��¼�Ƿ��ҵ���Ϊk�ļ�·��
	while (p)
	{
		if (visited[p->adjvex] == 0)  //���ö�����ڽӶ���û�����ʹ�
		{
			//��Ϊÿ�εݹ鶼�Ƕ�Ŀ�궥��ĸ���һ��������·������kҲ��-1
			//�����һ�εݹ鵽Ŀ�궥��ʱ��k=1������k=0����Ϊ�ж��Ƿ�ΪĿ�궥��u0������ڵݹ����ǰ�����Ե��ݹ鵽Ŀ�궥��ʱ��k=1
			if (p->adjvex == u0 && k == 1)   //���ö�����ڽӶ������Ŀ�궥��u0������k==1������������
				ret = 1;
			visited[p->adjvex] = 1;   //�����ڽӶ����Ϊ���ʹ���������DFS�㷨�����ݹ����
			IsPath(G, G->Vlist[p->adjvex].v, u, k - 1,visited);
			visited[p->adjvex] = 0;  //Ҳ��Ŀ�궥�㲻�ڸղŵݹ��·������ô�ͻ��ˣ��Ѹղż�Ϊ���ʹ��Ķ������±�Ϊδ����״̬
		}       //�����ñ߱�p�����������ڽӶ��㣬��������·�����еݹ飬���Ƿ����Ŀ�궥��u0
		p = p->next;
	}
	return ret;
}
int main()
{
	AMLGraph G;
	CreatWXT(&G);
	//DFS_notre(&G, '1');
	/*LongestPath(&G, '0');*/
	/*int* visited = (int*)calloc(sizeof(int), G.vexnum);*/
	/*int ret = IsPath_DFS(&G, '1', '0');*/
	int* visited = (int*)calloc(sizeof(int), G.vexnum);
	int ret = IsPath(&G, '1', '3', 4,visited);
	if (ret == 1)
		printf("����·��\n");
	else
		printf("������·��\n");
	return 0;
}