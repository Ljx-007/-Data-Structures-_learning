#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include<stdlib.h>
#define MVNum 100
#define MAXW 32767
//���·��--ÿһ�Զ��������·��
//����ÿһ�Զ��������·�������ַ�����
// 1.��ÿһ�����㶼ʹ��Dijkstra�㷨
// 2.��������(Floyd)�㷨
//���ߵ�ʱ�临�Ӷȶ�ΪO(n^3)����������ʽ�ϸ���
// 
//���������㷨Ҫ���ڽӾ���ʵ�ֶ������ڽӱ�����Ϊ��ҪO(1)ʱ���ѯ������������ı�Ȩֵ��������ʹʱ�临�ӶȴﵽO��n^3��
//���������㷨��Floyd��
//�㷨˼�룺
//1.�����ά����Path[i][j]����¼�Ӷ���vi��vj�����·���϶���vj��ǰһ��������
//2.�����ά����D[i][j]����¼����vi��vj֮������·������
//3.�Ƚ�������������֮���Ȩֵ��¼�����������ڽӾ���ķ�ʽ���������Լ��ľ���Ϊ0
//4.������������ԭ·���������������м䶥�㣬�������м䶥���·����̣����޸ľ����Ȩֵ������ά��ԭ����ֵ��ֱ�����еĶ��㶼����Ϊ�м䶥�㣬�����
typedef struct 
{
	char Vlist[MVNum];
	int arcs[MVNum][MVNum];
	int vexnum, arcnum;
}AMGraph;
int Located(char v,AMGraph* G)
{
	for (int i = 0; i < G->vexnum; i++)
	{
		if (v == G->Vlist[i])
			return i;
	}
	return -1;
}
void CreatYXW(AMGraph* G)
{
	printf("���붥�����ͱ�����");
	scanf("%d%d", &G->vexnum, &G->arcnum);
	char c;
	for (int i = 0; i < G->vexnum; i++)
	{
		while ((c = getchar()) != '\n') { ; }
		printf("���붥����Ϣ:");
		scanf("%c", &G->Vlist[i]);
	}
	for (int i = 0; i < G->vexnum; i++)
	{
		for (int j = 0; j < G->vexnum; j++)
		{
			if (i == j)
				G->arcs[i][j] = 0;
			else
				G->arcs[i][j] = MAXW;
		}
	}
	for (int i = 0; i < G->arcnum; i++)
	{
		char v1, v2;
		int w;
		printf("������˳�������������㼰���Ȩֵ��");
		while ((c = getchar()) != '\n') { ; }
		scanf("%c %c %d", &v1, &v2, &w);
		int m = Located(v1, G);
		int n = Located(v2, G);
		G->arcs[m][n] = w;
	}
}
void ShortestPath_Floyd(AMGraph* G,int** D,int** Path)
{
	for (int i = 0; i < G->vexnum; i++)  
	{
		for (int j = 0; j < G->vexnum; j++)   //��ʼ����ά����D��Path
		{
			D[i][j] = G->arcs[i][j];   //�ʼvi��vj�����·��Ϊ��������ֱ��·��������Ȩֵ
			if (D[i][j] < MAXW && i != j)  //�������vi��vj���л�����Ȩֵ��Ϊ�������vi��vj����ͬһ������
				Path[i][j] = i;     //��vi��vj�����·����vj��ǰ�������޸�Ϊvi����
			else
				Path[i][j] = -1;   //���vi��vj֮��û������vjǰ����Ϊ-1
		}
	}
	for (int i = 0; i < G->vexnum; i++)
	{
		for (int j = 0; j < G->vexnum; j++)   //ǰ����ѭ����Ϊ�˱�����ά����D��Path
		{
			for (int k = 0; k < G->vexnum; k++)   //������ѭ����һ��һ�������м䶥��
			{
				if ((D[i][k] + D[k][j]) < D[i][j])       //��������˶���vk��Ϊ�м䶥�㣬�Ҽ����vi��vj֮��ͨ��vk�����ԭ����·������
				{
					D[i][j] = D[i][k] + D[k][j];   //���ø��̵�·������ԭ·��
					Path[i][j] = Path[k][j];  //����ԭ���Ķ���i��j��ǰ�������Ϊ����k��j��ǰ������
				}
			}
		}
	}
}
int main()
{
	AMGraph G;
	CreatYXW(&G);
	int** D = malloc(sizeof(int*) * G.vexnum);
	int** Path = malloc(sizeof(int*) * G.vexnum);
	for (int i = 0; i < G.vexnum; i++)
	{
		D[i] = malloc(sizeof(int) * G.vexnum);
		Path[i] = malloc(sizeof(int) * G.vexnum);
	}
	ShortestPath_Floyd(&G, D, Path);
	char v, u;
	printf("����Դ�����յ㶥����Ϣ��");
	while ((v = getchar()) != '\n') { ; }
	scanf("%c %c", &v, &u);
	int v0= Located(v, &G);
	int u0 = Located(u, &G);
	int* stack = malloc(sizeof(int) * G.vexnum);
	int top, base;
	top = base = 0;
	while (u0 != v0)
	{
		stack[top++] = u0;
		u0 = Path[v0][u0];
	}
	int i=v0;
	int j;
	while (base != top)
	{
		j= stack[--top];
		printf("%c-->%c\n", G.Vlist[i], G.Vlist[j]);
		i = j;
	}
	return 0;
}