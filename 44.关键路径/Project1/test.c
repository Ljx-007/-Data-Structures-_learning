#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define MVNum 100
//�ؼ�·��
//AOE����ʾ�Ա߱�ʾ��������ʾ��Ŀ�ʼ���߽�����
//AOE��ͨ���ڹ��̼ƻ��;�Ӫ�������й㷺Ӧ�ã�ͨ����Ҫ����������⣺
//1��������������������Ҫ����ʱ�䣿
//2���ж���Щ���Ӱ�칤�̽��ȵĹؼ�
//��Ϊ����ֻ��һ����ʼ���һ����ɵ㣬��ʼ�����Ϊ0����ΪԴ�㣬��ɵ����Ϊ0����Ϊ��㡣
//Ҫ�����������ɵ����ʱ�䣬����Ҫ��һ����Դ�㵽���Ĵ�Ȩ·���������·������Ϊ�ؼ�·����
//�ؼ�·���ϵĻ��Ϊ�ؼ������Щ�����ǰ�����ӽ�ʹ����������ǰ������

//�ai�����翪ʼʱ��-����ʼʱ��=ʱ������
//���һ���û��ʱ����������ô�������ǹؼ��
// 
//�¼�vi�����翪ʼʱ��ve��i����
//  �¼�viǰ��ÿһ���������˲��ܿ�ʼvi�¼�������Ҫ�ң�vi�¼�ǰ���¼������緢��ʱ��+���¼�vi�Ļ���Ȩֵ�������ֵ������vi�¼������翪ʼʱ��
//    ve��i��= Max{ ve(k) + wk,i}    --vkΪvi�¼�ǰ���¼���ve��k��Ϊvk�¼������緢��ʱ�䣬wk,iΪ�vk-vi�ĳ���ʱ��
//�¼�vi��������ʱ��vl��i����
//  ����������ʱ����Ҫ�ӻ����ǰ���ƣ�����������������Ҫ��ʮ����ɣ�vi�¼�����3���ֱ���Ҫ3��5��7������ɣ���vi�¼�����������ʱ��Ӧ��
//    10-7��10-5��10-3�е���Сֵ����10-7=3������vi�¼�����������ʱ��ӦΪ�����졣
//  �Դ����ƣ��ӻ��һֱ��ǰ�ƣ�һֱ�Ƶ��������ڼ�����¼�vi�����Թ�ʽΪ��
//    vl(i) = Min{vl(k) - wi,k}

//�ai=<vj,vk>
//�ai�����翪ʼʱ��e(i)��
//  ֻ���¼�vj�����ˣ��ai���ܿ�ʼ������ai�����翪ʼʱ��e(i)=ve(j)
//�ai������ʼʱ��l(i):
//  �ai�Ŀ�ʼʱ���豣֤�������¼�vk��������ʱ�䣬����ai������ʼʱ��l(i)=vl(k)-wj,k

//��ؼ�·���Ĳ��裺
//1.��ve(i).vl(i)
//2.��e(i),l(i)
//3.����l(i)-e(i)
//Դ��ͻ������翪ʼʱ�������ʼʱ����һ����
//����ؼ�·��Ҫ�������¸����ṹ��
//1.һά����ve[i]����¼�¼�vi�����緢��ʱ��
//2.һά����vl[i]����¼�¼�vi����ٷ���ʱ��
//3.һά����topo[i]����¼�������еĶ������
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
//����˳��ջ
typedef struct Stack
{
	int* base;
	int* top;
	int sizemax;
}Stack;
void InitStack(Stack* S)
{
	S->base = malloc(sizeof(int) * MVNum);
	S->top = S->base;
	S->sizemax = MVNum;
}
void Push(Stack* S, int  e)
{
	if ((S->top - S->base) == S->sizemax)
	{
		printf("ջ��\n");
		return;
	}
	*S->top = e;
	S->top++;
}
int Pop(Stack* S)
{
	if (S->top == S->base)
	{
		printf("ջ��\n");
		return -1;
	}
	int e = *--S->top;
	return e;
}
int IsEmpty(Stack* S)
{
	if (S->top == S->base)
		return 1;
	else
		return 0;
}
int Located(char v, AMLGraph* G)
{
	for (int i = 0; i < G->vexnum; i++)
	{
		if (v == G->Vlist[i].v)
			return i;
	}
	return -1;
}
void CreatYXW(AMLGraph* G)
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
		int w;
		printf("��������˳�������������㼰��Ȩֵ��");
		while ((c = getchar()) != '\n') { ; }
		scanf("%c %c %d", &v1, &v2,&w);
		int m = Located(v1, G);
		int n = Located(v2, G);
		Arcnode* p = malloc(sizeof(Arcnode));
		p->adjvex = n;
		p->weight = w;
		p->next = G->Vlist[m].first;
		G->Vlist[m].first = p;
	}
}
void Findindegree(AMLGraph* G, int* indegree)
{
	for (int i = 0; i < G->vexnum; i++)
	{
		int count = 0;
		for (int j = 0; j < G->vexnum; j++)
		{
			Arcnode* p = G->Vlist[j].first;
			while (p)
			{
				if (p->adjvex == i)
					count++;
				p = p->next;
			}
		}
		indegree[i] = count;
	}
}
int TopoSort(AMLGraph* G,int* indegree,int* topo)
{
	Findindegree(G, indegree);
	Stack S;
	InitStack(&S);
	for (int i = 0; i < G->vexnum; i++)
	{
		if (indegree[i] == 0)
			Push(&S, i);
	}
	int m = 0;
	while (!IsEmpty(&S))
	{
		int e = Pop(&S);
		topo[m++] = e;
		Arcnode* p = G->Vlist[e].first;
		while (p)
		{
			indegree[p->adjvex]--;
			if (indegree[p->adjvex] == 0)
				Push(&S, p->adjvex);
			p = p->next;
		}
	}
	if (m < G->vexnum)
		return 0;
	return 1;
}
void CriticalPath(AMLGraph G, int* ve, int* vl,int* indegree,int* topo)
{
	if (!TopoSort(&G, indegree, topo))
		return;
	//��ʼ��ÿ���¼������緢��ʱ��
	for (int i = 0; i < G.vexnum; i++)
		ve[i] = 0;
	//��ÿ���¼������緢��ʱ��
	for (int i = 0; i < G.vexnum; i++)
	{//������������ÿ���¼������緢��ʱ��
		int k = topo[i];
		Arcnode* p = G.Vlist[k].first;
		while (p)
		{//����¼�p->adjvex��ǰһ���¼�k�����緢��ʱ��+���¼���Ļʱ��>ԭ�����¼�p->adjvex�����緢��ʱ�䣬��ô�͸����¼�p->adjvex�����緢��ʱ��
			//�����������Max{ve(k)+ wi,k},i��ʵ����p->adjvex
			if (ve[p->adjvex] < ve[k] + p->weight)    
				ve[p->adjvex] = ve[k] + p->weight;
			p = p->next;
		}
	}
	//��ʼ��ÿ���¼���������ʱ��
	for (int i = 0; i < G.vexnum; i++)
	{
		vl[i] = ve[G.vexnum - 1];  //��ÿ���¼���������ʱ���ʼ��Ϊ�������緢��ʱ�䣬����������Ҫ����ɵ�ʱ��
	}
	//��ÿ���¼���������ʱ��
	for (int i = G.vexnum-1; i >=0; i--)
	{//��Ϊ������ʱ��Ҫ�ӻ��Ӻ���ǰ���ƣ�����Ҫ���������������¼���������ʱ��
		int k = topo[i];
		Arcnode* p = G.Vlist[k].first;
		while (p)
		{//����¼�k��һ���¼�p->adjvex-���¼�֮��Ļʱ��<ԭ���¼�k��������ʱ�䣬��ô�͸����¼�k��������ʱ��
			//�����������Min{ vl(j)- wi,j} , j����p->adjvex
			if (vl[p->adjvex] - p->weight < vl[k])
				vl[k] = vl[p->adjvex] - p->weight;
			p = p->next;
		}
	}
	for (int i = 0; i < G.vexnum; i++)
	{  //ÿ��ѭ�������viΪ���ʼ�㣬��vi���ڽӶ���Ϊ�������Ļ
		Arcnode* p = G.Vlist[i].first;
		while (p)  //��p�����߱����ڽӶ���
		{
			int e = ve[i];  //������翪ʼʱ��=ǰһ���¼������翪ʼʱ��
			int l = vl[p->adjvex] - p->weight;  //�������ʼʱ��=��һ���������ʼʱ��-��ĳ���ʱ��
			if (l == e )
			{//��ӡ�ؼ�·��
				printf("%c-->%c��weight=%d\n", G.Vlist[i].v, G.Vlist[p->adjvex].v,p->weight);
			}
			p = p->next;
		}
	}
}
int main()
{
	AMLGraph G;
	CreatYXW(&G);
	int* indegree = (int*)malloc(sizeof(int) * G.vexnum);
	int* topo = (int*)malloc(sizeof(int) * G.vexnum);
	int* ve = (int*)malloc(sizeof(int) * G.vexnum);
	int* vl = (int*)malloc(sizeof(int) * G.vexnum);
	CriticalPath(G, ve, vl, indegree, topo);
	return 0;
}