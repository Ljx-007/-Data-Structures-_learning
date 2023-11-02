#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//�����������������������
typedef struct Binode
{
	char c;
	struct Binode* lchild, * rchild;
}Binode,*Bitree;
//�ݹ��㷨
void ReCreatBiTree(Bitree* T)
{
	char ch;
	printf("���������ַ�:");
	scanf("%c", &ch);
	//һ�����п��Բ������ֶ�������Ϊ��ȷ��Ψһ�Ķ����������ǽ��������Ŀս��Ҳ���ϣ���'#'������ȫ�˿ս��Ķ���������Ψһ�Ķ�����
	if (ch == '#')    //��#������ս��
	{
		while ((ch = getchar()) != '\n') { ; }   //��ȡ���������Ļ��з�
		*T = NULL;
	}
	else
	{
		*T = (Binode*)malloc(sizeof(Binode));
		if (!*T)
		{
			printf("malloc error\n");
			return;
		}
		(*T)->c = ch;   //��������ַ����������
		while ((ch = getchar()) != '\n') { ; }
		ReCreatBiTree(&(*T)->lchild);    //�ݹ鴴����������������
		ReCreatBiTree(&(*T)->rchild);
	}
}
//���ƶ�����
void Copy(Bitree* T, Bitree* copyT)
{
	if (!T)    //����ǿ�������ô���Ƶ���Ҳ�ǿյ�
	{
		copyT = NULL;
		return;
	}
	else
	{
		*copyT = (Bitree)malloc(sizeof(Binode));    //������ǿ������ȸ�����������һ��ռ�
		(*T)->c = (*copyT)->c;           //����������copy����������
		Copy(&(*T)->lchild, &(*copyT)->lchild);   //�ٵݹ鸴������������������Ҫ�������ַ�ĵ�ַ
		Copy(&(*T)->rchild, &(*copyT)->rchild);
	}
}
//��������������
int Depth(Bitree* T)
{
	if (!*T)
		return 0;
	else
	{
		int m = 1 + Depth(&(*T)->lchild);   // ����+1��Ϊ�˼��ϸ���㱾������
		int n = 1 + Depth(&(*T)->rchild);
		return m > n ? m : n;
	}
}
//����������Ľ�����
int Nodecount(Bitree* T)
{
	if (!*T)
	{
		return 0;
	}
	else
	{
		int m = Nodecount(&(*T)->lchild); 
		int n = Nodecount(&(*T)->rchild);
		return m + n + 1;       //����+1��Ϊ�����ϸ���㱾���������������������������������������
	}
}
//��Ҷ�ӽ����
int Leafcount(Bitree* T)
{
	if (!*T)
		return 0;    //��������0
	if ((*T)->lchild == NULL && (*T)->rchild == NULL)
	{
		return 1;    //�������������������Ϊ�գ�˵������һ��Ҷ��㣬����1
	}
	else
	{
		int m = Leafcount(&(*T)->lchild);    //������������Ҷ�����
		int n = Leafcount(&(*T)->rchild);
		return m + n;   //��ӵö�����Ҷ���������Ϊ����㱾������������������Ҷ���
	}
}
//���Դ���
//int main()
//{
//	Bitree T;
//	ReCreatBiTree(&T);
//	printf("%d ", Depth(&T));
//	printf("%d ",Nodecount(&T));
//	return 0;
//}

//����������
//������������Ϊ�洢�ṹʱ��ֻ�ܵõ�������Һ��ӵ���Ϣ������ֱ�ӵõ���������������е�ǰ���ͺ����Ϣ
// ���磬����������У�ĳ�������ķ�������ΪEGFCBADHI,��֪G����ǰ����E�������F������Щ��Ϣֻ���ڱ��������в��ܵõ�
//  Ϊ�����������ֽ��������
//   1�����±���һ��    ��ʱ��̫����
//   2����������ָ������ǰ���ͺ�̵���Ϣ  ���ռ�̫��
//   3.���ö��������еĿ�ָ����    ����ð취��

//��������n����㣬һ����2n��ָ������������n-1�����ӣ��������û��˫�ף����Ǻ��ӣ���������n-1��ָ����ָ���ӣ�ʣ�µľ��ǿ�ָ����
// 
//���Կ�ָ����ĸ���Ϊ��2n-��n-1��=n+1
// 
//���ĳ����������Ϊ�գ���ô��ָ�����Ϊָ����ǰ��
// 
//���ĳ�������Һ���Ϊ�գ���ô��ָ�����Ϊָ������
// 
//Ϊ����������ָ����ָ���ӵĻ���ǰ����̵ģ�������Ҫ����������־ltag��rtag
// 
//��ָ����ʱ��tag=0��ָ��ǰ��/���ʱ��tag=1

//���û��ǰ������û�к�̵Ľ�����ǵ�ָ�����ָ�������أ�Ϊ�˲������ǿ��ţ�������һ��ͷ��㣬ͷ���һ��������ָ��������������ұ�־

//ͷ������ָ����ָ�����ĸ���㣬ltag=0����ָ����ָ�����������һ����㣬rtag=1��

//���������еĵ�һ��������ָ��������һ��������ָ����ԭ����Ӧ������ָ����������ָ��ͷ���

typedef struct BiThrNode
{
	char data;
	struct BiThrNode* lchild, * rchild;
	int ltag, rtag;
}*BiThrTree;
//�������������ô���
// ��������ı������Ӽ��