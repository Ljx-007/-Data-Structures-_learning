#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define MVNum 100
//��С������--�ڽӱ�
typedef struct Vnode
{
	char v;
	struct Arcnode* first;
}Vnode;
typedef struct Arcnode
{
	int adjvex;
	int w;
	struct Arcnode* next;
}Arcnode;
typedef struct
{
	Vnode Vlist[MVNum];
	int vexnum, arcnum;
}AMLGraph;
//����������
int Located(char v, AMLGraph* G)
{
	for (int i = 0; i < G->vexnum; i++)
	{
		if (v == G->Vlist[i].v)
			return i;
	}
	return -1;
}
void CreatWXW(AMLGraph* G)
{
	char c;
	printf("�����������Ķ������ͱ�����");
	scanf("%d%d", &G->vexnum, &G->arcnum);
	for (int i = 0; i < G->vexnum; i++)
	{
		while ((c = getchar()) != '\n') { ; }
		printf("���붥����Ϣ��");
		scanf("%c", &G->Vlist[i].v);
		G->Vlist[i].first = NULL;
	}
	for (int i = 0; i < G->arcnum; i++)
	{
		char v1, v2;
		int w;
		while ((c = getchar()) != '\n') { ; }
		printf("��������������������Ȩֵ:");
		scanf("%c %c %d", &v1, &v2, &w);
		int j = Located(v1, G);
		int k = Located(v2, G);
		Arcnode* p = (Arcnode*)malloc(sizeof(Arcnode));
		p->next = G->Vlist[j].first;
		G->Vlist[j].first = p;
		p->adjvex = k, p->w = w;
		Arcnode* q = (Arcnode*)malloc(sizeof(Arcnode));
		q->next = G->Vlist[k].first;
		G->Vlist[k].first = q;
		q->adjvex = j, q->w = w;
	}
}
typedef struct Edge
{
	int adjvex;   //��U�еĶ���
	int weight;    //V-U�ж��㵽U�ж���ıߵ�Ȩֵ
}Edge;
int Min(Edge closedge[],int n)  //Ѱ����СȨֵ��
{
	int min = INT_MAX;
	int pos = 0; 
	int i;
	for ( i = 0; i < n; i++)
	{
		if (closedge[i].weight != 0 && closedge[i].weight < min)
		{
			min=closedge[i].weight;
			pos = i;
		}
	}
	return pos;   //�����posһ���᷵��һ��ֵ�ģ���Ϊ���closedge[i].weightȫ��INT_MAX�Ļ����ʹ�����������������ж��㶼����������ô��Ͳ���һ����ͨͼ��
	             //��������ʱ�����Ǵ�����������ͨͼ����������posһ������forѭ���з��س�һ��ֵ
}
void AMLPrim(AMLGraph* G,char v)
{
	int k = Located(v, G);  
	Edge closedge[MVNum];   //����һ��closedge�������洢V-U�еĸ������㵽U�ж������СȨֵ��
	for (int i = 0; i < G->vexnum; i++)
	{
			closedge[i].adjvex = k;     //����Ȱ�V-U�и��������closedge���ڽӶ����ʼ��Ϊ��ʼ���㣬�������Ÿ���Ķ������U�������
			closedge[i].weight = INT_MAX;  //��Ϊ�ڽӱ��в���ص����������û��Ȩֵ�����Գ�ʼ����ʱ��Ȩֵȫ����ʼ��Ϊ���ֵ
	}
	closedge[k].weight = 0;
	Arcnode* p = G->Vlist[k].first;   //�ڽӾ������ڽӱ�Ĳ�֮ͬ�������ڽӱ��õ��Ǳ߱�洢����Ϣ
	//��p��ָ����ʼ����ı߱��ַ������������������֪������k���ڽӶ��㼰��ߵ�Ȩֵ���Դ�������ȨֵȫΪINT_MAX��closedge�����Ȩֵ��Ϣ
	while (p)
	{
		closedge[p->adjvex].weight = p->w;
		p = p->next;
	}
	for (int i = 0; i < G->vexnum - 1; i++)   //��ʼѡ�����µ�n-1�������n-1����
	{
		int min = Min(closedge, G->vexnum);
		int v0 = closedge[min].adjvex;   //��С�����
		int u0 = min;   //��С���յ�
		printf("%c-->%c\n", G->Vlist[v0].v, G->Vlist[u0].v);
		closedge[u0].weight = 0;   //����СȨֵ�ߵ��յ㶥��Ҳ����U
		p = G->Vlist[u0].first;   //������һ�θ���closedge�����Ȩֵ����p��ָ����С���յ㶥��ı߱���������
		while (p)
		{
			if (p->w<closedge[p->adjvex].weight)  //����¼ӵĶ������ĳ��������С��Ȩֵ������С��ȨֵС��֮ǰ���������������С��Ȩֵ
			{                                  //��ô����С���Ǹ���С��Ȩֵ�����ԭ������С��Ȩֵ
				closedge[p->adjvex].adjvex = u0;
				closedge[p->adjvex].weight = p->w;
			}
			p = p->next;
		}
	}
}
int main()
{
	AMLGraph G;
	CreatWXW(&G);
	AMLPrim(&G, '1');
	return 0;
}