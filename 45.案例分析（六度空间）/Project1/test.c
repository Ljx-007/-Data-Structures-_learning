#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define MVNum 100
//���ȿռ�����--�������������������ֻ��Ҫͨ�������˾Ϳ�����ʶ
//���԰��˼ʹ�ϵ����ͼ����һ��������Ȩͼ���������һ���ˣ������Ƿ���ʶ���ñ�����
//�������ȿռ�����ۣ���������������·�����Ȳ�����7��Ҫ��֤�����ۿ����ù�������㷨
// ��������㷨��ͼ����7�����������7������󺭸ǵ��ѷ��ʶ�����ռ�ܶ������Ķ��١�
//  ����7�����������6������Ϊ��ʼ�������һ�㣬ͨ���������˲������Լ�����

//����һ������
typedef struct Queuenode
{
	int v;
	struct Queuenode* next;
}Queuenode,*QueuePtr;
typedef struct
{
	QueuePtr front;
	QueuePtr rear;
}QueueLink;
void InitQueue(QueueLink* Q)
{
	//����һ��ͷ���
	Q->front = (Queuenode*)malloc(sizeof(Queuenode));
	Q->front->next = NULL;
	Q->rear = Q->front;
}
void EnQueue(QueueLink* Q,int v)
{
	Queuenode* p = (Queuenode*)malloc(sizeof(Queuenode));
	p->v = v;
	p->next = Q->rear->next;
	Q->rear->next = p;
	Q->rear = p;
}
int OutQueue(QueueLink* Q)
{
	if (Q->front == Q->rear)
		return -1;
	Queuenode* p = Q->front->next;
	int e = p->v;
	Q->front->next = p->next;
	if (Q->rear == p)
		Q->rear = Q->front;
	free(p), p = NULL;
	return e;
}
int IsEmpty(QueueLink* Q)
{
	if (Q->front == Q->rear)
		return 1;
	return 0;
}
//ʹ���ڽӱ�����Ϊ������Ȩͼ�Ĵ洢�ṹ
typedef struct Vnode
{
	char v;
	struct Arcnode* first;
}Vnode;
typedef struct Arcnode
{
	int adjvex;
	struct Arcnode* next;
}Arcnode;
typedef struct
{
	Vnode Vlist[MVNum];
	int vexnum, arcnum;
}AMLGraph;
int Located(char v, AMLGraph* G)
{
	for (int i = 0; i < G->vexnum; i++)
	{
		if (v == G->Vlist[i].v)
			return i;
	}
	return -1;
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
		printf("�������������㣺");
		while ((c = getchar()) != '\n') { ; }
		scanf("%c %c", &v1, &v2);
		int m = Located(v1, G);
		int n = Located(v2, G);
		Arcnode* p = malloc(sizeof(Arcnode));
		p->adjvex = n;
		p->next = G->Vlist[m].first;
		G->Vlist[m].first = p;
		Arcnode* q = malloc(sizeof(Arcnode));
		q->adjvex = m;
		q->next = G->Vlist[n].first;
		G->Vlist[n].first = q;
	}
}
void SixDegree_BFS(AMLGraph* G,char v)  //ͨ����������㷨����֤���ȿռ����ۣ�vΪָ����һ�����
{
	int start = Located(v, G);
	int visit_num = 0; //��visit_num����¼7����������˶��ٶ���
	int* visited = (int*)calloc(sizeof(int) , G->vexnum);  //����visit����¼�����Ƿ񱻷���
	visited[start] = 1;
	QueueLink Q;
	InitQueue(&Q);
	EnQueue(&Q, start);  //��ӵ�һ��Ķ��㣬����ʼ����
	int level[7] = { 0 };  //������len����¼ÿһ������Ķ��������ֻ�����7��
	level[0] = 1;   //��һ������Ķ������Ϊ1
	for (int len = 1; len <= 6 && !IsEmpty(&Q); len++)  //����ѭ�����Σ��ǿ�ĳ���ˣ���ʼ���㣩ͨ�������˺�����ʶ������
	{
		for (int i = 0; i < level[len - 1]; i++)   //���forѭ���ǰ�ĳһ��Ķ���ȫ�����ӱ�����Ȼ�������һ��Ķ���
		{  //�����ÿһ��ѭ����ʵ�����ڱ���ǰһ�����һ���ˣ�����len=1ʱ������0��Ķ�����ӣ�Ѱ�ҵ�1��Ķ�����ӣ����Ե�0��Ķ����������level[len-1]
			//len=2ʱ����ҪѰ�ҵڶ���Ķ��������len-1=1����Ҫ�ѵ�һ��Ķ��㶼���ӣ�Ѱ�ҵڶ���Ķ������
			//��len=6ʱ��Ҫ�ѵ�5��Ķ��㶼���ӣ�Ѱ�ҵ�6��Ķ�����ӣ���������Բ���Ҫ���ӣ���Ϊ����ֻ��Ҫ���㺭�ǵĶ������visit_num
			//�����ʱ���Ǿ��Ѿ������˶������visit_num���������һ��������Ӷ�����ν
			int e=OutQueue(&Q);  //������һ�������ӣ���e����
			Arcnode* p = G->Vlist[e].first; 
			while (p)
			{  //Ѱ�Ҷ���e���ڽӶ��㣬��Ѱ����һ��
				if (visited[p->adjvex] == 0)   //�������δ�����ʹ����򽫸��ڽӶ������
				{
					visited[p->adjvex] = 1;   //������״̬��Ϊ1
					visit_num++;   //�����Ѿ�����Ķ������
					level[len]++;   //������һ��Ķ������
					EnQueue(&Q, p->adjvex);   //���
				}
			}
		}
	}
	printf("�ٷֱ�Ϊ��%d", 100 * visit_num / G->vexnum);
}