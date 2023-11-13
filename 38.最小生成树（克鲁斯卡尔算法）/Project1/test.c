#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define MVNum 100
//��³˹�����㷨(Kruskal)
//Prim�㷨��һ��һ������Ĳ��뼯��U����Kruskal�㷨��һ���ӽ����еĶ���ȫ��������U��Ȼ��һ��һ������ѡ��
//����˵��Prim�㷨��ѡ�񶥵㣬Kruskal�㷨��ѡ���
//Kruskal�㷨���̣�
// ��һ������ͼȥ�����еıߣ�ֻ���¶��㣬Ȼ��ѡ��Ȩֵ��С�ıߣ��������������������㣬������ѡ��Ȩֵ��С�ıߣ��������������������㣬�Դ����ơ�
//  ���ӹ����в����γɻ�·�����ѡ�����С�����Ӻ���γɻ�·���������˱�ѡ����һ��Ȩֵ��С�ıߡ�ֱ���γ���С������Ϊֹ
//   ע�⣺���ѡ����С��ʱ�������ж���ͬ��Ȩֵ�ı߿���ѡ������ѡ��һ��Kruskal�㷨����С��������Ψһ
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
void CreatGraph(AMGraph* G)   //����������
{
	printf("�������Ķ�������ͱ�����");
	scanf("%d%d", &G->vexnum, &G->arcnum);
	for (int i = 0; i < G->vexnum; i++)
	{
		char c;
		while ((c = getchar()) != '\n') { ; }
		printf("���붥����Ϣ��");
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
		printf("������������������㼰��Ȩֵ��");
		scanf("%c %c %d", &v1, &v2, &w);
		int p = Located(v1, G);
		int q = Located(v2, G);
		G->arcs[p][q] = w;
		G->arcs[q][p] = w;
	}
}
//�㷨��ʵ��Ҫ����һ����������洢�ߵ���Ϣ�������ߵ����������Ȩֵ
typedef struct Edge
{
	int v0,u0;
	int weight;
}Edge;
void InitEdge(Edge* Arredge,AMGraph* G)
{
	for (int i = 0; i < G->vexnum; i++)   //��Ϊ�������洢Ϊ�ڽӾ�����ʽʱ���ڽӾ�����һ���Գƾ�������ֻ��Ҫ����һ��ľ��󼴿�
	{                              //�������Ǿ�����������Ǿ�����Ϊ����ֻҪ��¼�ߵ���Ϣ�Ϳ��ԣ��ڽӾ�����Ϊ�Գƣ����ظ��ıߵ���Ϣ������ֻ����һ��
		for (int j = i; j < G->vexnum; j++)  //��j==i��ѭ��ִ��ʱ�ͳɹ����������Ǿ�����
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
	qsort(Arredge, G->arcnum, sizeof(Edge), cmp);   //��qsort������Edge�������Ȩֵ�ӵ͵��߽�������
	//��Ҫ����һ����������Vexsex����ʶ����������������ͨ������������Ƿ��л�·����
	//����v1��v2��ͬһ����ͨ�������ô������Ԫ��Ӧ��ͬ����vs1=vs2
	//�ʼÿһ�����㶼�Լ�Ϊһ����ͨ�������������������ͬ��ͨ�����Ķ��㣬�������������߾ͻṹ�ɻ�·
	int* Vexset = (int*)malloc(sizeof(int) * G->vexnum);
	for (int i = 0; i < G->vexnum; i++)
	{
		Vexset[i] = i;    //��ʼ������Vexset��ÿһ�������Ԫ�ض�����ͬ���������Ϊһ����ͨ����
	}
	for (int i = 0; i < G->arcnum; i++)
	{
		int v0 = Arredge[i].v0;   //��ȡ��СȨֵ�ߵ���������
		int u0 = Arredge[i].u0;
		int vs0 = Vexset[v0];    //��ȡ�������������ͨ����
		int us0 = Vexset[u0];
		if (vs0 != us0)   //������������㲻������ͬһ����ͨ��������ô˵���������������㲻�������·
		{
			printf("%c-->%c\n", G->Vlist[v0], G->Vlist[u0]);    //��ӡ����ͨ����Ϣ
			for (int j = 0; j < G->arcnum; j++)    //����Vexset����
			{
				if (Vexset[j] == us0)   //��Ϊ��ͨ����Ϊus0�Ķ����Ѿ���������һ����ͨ�����ˣ�˵��һ����us0�������ͨ�����������뵽vs0��
					                   //vs0�����������һ����ͨ����
					Vexset[j] = vs0; //���Է�����ͨ����Ϊus0�Ķ��㣬��Ҫ��Ϊvs0
			}
		}
	}
}
//Kruskal��ʱ�临�Ӷ�ΪO(elog2 e),�ʺ���ϡ��������С������
//Prim��ʱ�临�Ӷ�ΪO(n^2)���ʺ������������С������
int main()
{
	AMGraph G;
	CreatGraph(&G);
	Kruskal_AM(&G);
	return 0;
}