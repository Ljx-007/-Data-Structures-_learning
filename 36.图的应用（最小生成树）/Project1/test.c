#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define MVNum 100
//��С������
//����ķ�㷨
//��һ����ͨ���У�UΪ��ѡ�ж���ļ��ϣ�VΪ���ж���ļ��ϣ���V-UΪδѡ�ж���ļ��ϣ�TEΪ��ͨ������С�������бߵļ���
//�����U����һ����ʼ���㣬Ѱ����ʼ�����Ȩֵ��С�ıߣ��ѱ߲��뼯��TE��������������һ�����㲢�뼯��U��
//  ��Ѱ��U�ж����Ȩֵ��С�ıߣ��ٽ�ѡ�е�Ȩֵ��С�ı߲���U
//���磺
//   ��һ��ͼ�У�һ����n�����㡣
//   ��ʼ����Ϊv1���ҵ�һ��������v1��Ȩֵ��С�ıߣ�ͬʱҲ������v3����v3����U���������߲���TE����Ѱ�Ҽ���U�ж��㣨v1��v3������������Ȩֵ��С�ı�
//  ���������ٲ���TE���ҵ��ñ���������һ�����㣬�ٽ��䲢��U���Դ����ƣ�ֱ��U�а������ж��㣬��ʱTE�б���n-1����
//���ѡ����С��ʱ�����ڶ���ͬ��Ȩֵ�ıߣ���ѡ��һ���ɡ�ȫ��ѡ�����U��TE���ɵ�ͼ������С������
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
		scanf("%c %c%d", &v1, &v2, &w);
		int p = Located(v1, G);
		int q = Located(v2, G);
		G->arcs[p][q] = w;
		G->arcs[q][p] = w;
	}
}
struct edge //��������closedge�����ڼ�¼��U��V-U������СȨֵ�ı�
{   //����ÿһ����V-U�����еĶ��㣬���洢����С���ϵ�Ȩֵ������С����U�е��Ǹ�����
	int adjvex;   //��С����U�е��Ǹ�����
	int lowweight;   //��С���ϵ�Ȩֵ
}closedge[MVNum];
int Min(AMGraph* G,struct edge closedge[])
{
	int min = INT_MAX;    //min����Ѱ����Сֵ����min��ʼ��Ϊ���Ȩֵ���������
	int pos = 0;
	for (int i = 0; i < G->vexnum; i++)
	{
		if (closedge[i].lowweight != 0 && closedge[i].lowweight < min)  //������ֲ��ڼ���U�еĶ��㣬����ȨֵС��min
		{ //ȨֵΪ0�����õ��ڼ���U��
			min = closedge[i].lowweight; //�������СȨֵmin������pos��¼�ö����λ��
			pos = i;
		}
	}
	return pos;
}
void MiniSpanTree_Prim(AMGraph *G, char v)  //vΪ������С����������ʼ����
{
	int k = Located(v, G);  //�ҵ�����v���±�k
	for (int i = 0; i < G->vexnum; i++)   //��ʼ������closedge
	{
		if (i != k)
		{
			closedge[i].adjvex=k;   //���������㶼�Ƕ���v���ڽӶ��㣬ֻ����Ȩֵ��һ�����ˣ�ȨֵΪINT_MAX�����ڽӶ���
			closedge[i].lowweight = G->arcs[k][i];   //������v�����������ȨֵҲ��¼����
		}
		closedge[k].lowweight = 0;   //�Լ����Լ�û��Ȩֵ������Ȩֵ��Ϊ0
	}
	for (int i = 1; i < G->vexnum; i++)   //ѡ������n-1�����㣬����ѭ��n-1��
	{
		int min = Min(G,closedge);  //Ѱ���ڽӶ�����Ȩֵ��С�ıߣ����ڽӶ��㣨�ڼ���V-U�У����±긳ֵ��min
		int v0 = closedge[min].adjvex;   //��С�ߵ����
		int u0 =min;   //��С�ߵ��յ�
		printf("%c-->%c\n", G->Vlist[v0], G->Vlist[u0]);
		closedge[u0].lowweight = 0;   //�ö��㲢�뼯��U
		//�����ȨֵΪ0���뼯��U�����ͣ�
		// ����ķ�㷨����С�����ڼ���U�е����ж������ҵģ����缯��U����1��3��5�������㣬��ô����С������1��3��5���������㷢������СȨֵ��
		//  ��closedge�����Ǵ����V-U�����еĶ���ģ�Ҫ����Щ���㵽1��3��5�ıߵ���СȨֵ�ߣ������ڶ���1��3��5��˵�������Ѿ���ѡ����С��������
		//���Բ���Ҫ����ΪV-U�����еĶ�����Ѱ����СȨֵ���ˣ����԰�������closedge���������Ķ����Ȩֵ��Ϊ0
		// Ȼ������Min�������һ�����������������Ķ���ȨֵΪ0���������ö���Ѱ����С��
		for (int j = 0; j < G->vexnum; j++)      //����closedge����
		{
			if (G->arcs[u0][j] < closedge[j].lowweight)   //����U�ж��˶���u0�����V-U�еĶ��㵽u0����С�ߵ�Ȩֵ�ȵ�v��Ȩֵ��С
			{                                           //��ô�ͽ�Ȩֵ���£�ȨֵӦ�ǵ�U�ж���ıߵ���СȨֵ
				closedge[j].adjvex = u0;    
				closedge[j].lowweight = G->arcs[u0][j];
			}
		}
	}
}
int main()
{
	AMGraph G;
	CreatGraph(&G);
	MiniSpanTree_Prim(&G, '1');
	return 0;
}