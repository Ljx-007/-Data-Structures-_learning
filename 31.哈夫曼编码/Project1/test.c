#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//ʵ�ֹ��������룬�ȹ����������
typedef struct HuffmanNode
{
	int weight;
	int parent, lchild, rchild;
}HuffmanNode,*HuffmanTree;
void Select(HuffmanTree HT, int len,int* s1, int* s2)
{
	int min1, min2, pos1, pos2;
	//����min1��min2�ҵ���ǰ������������
	for (int i = 1; i <= len; i++)
	{
		if (HT[i].parent == 0)   
		{
			min1 = HT[i].weight;
			pos1 = i;
			break;
		}
	}
	for (int i = 1; i <= len; i++)
	{
		if (HT[i].parent == 0&&i!=pos1)
		{
			min2 = HT[i].weight;
			pos2 = i;
			break;
		}
	}
	//��Ѱ��Ȩֵ��С�ʹ�С�Ľ�㣬���ǹ涨��min1ΪȨֵ��С��miin2Ϊ��С
	for (int i = 1; i <= len; i++)
	{
		if (HT[i].parent == 0)
		{
			if(min1>HT[i].weight)   //������ȨֵС��min1����min1������С
			{
				min2 = min1;   //�Ȱ�min1ԭ���������Сֵ����min2��min2��ʱΪ��СȨֵ
				pos2 = pos1;
				min1 = HT[i].weight;   //����min1������СȨֵ
				pos1 = i;
			}
			//������ֽ��Ȩֵ������С��С�ڴ�С���������ô���ô�Сֵmin2���ڸý��Ȩֵ
			else if (min2 > HT[i].weight && min1 < HT[i].weight)
			{
				min2 = HT[i].weight;
				pos2 = i;
			}
		}
	}
	*s1 = pos1, * s2 = pos2;
}
void CreatHuffmanTree(HuffmanTree* HT,int n)
{
	int m = 2 * n - 1;
	*HT = (HuffmanTree)malloc(sizeof(HuffmanNode) * (m + 1));
	for (int i = 1; i <= m; i++)
	{
		(*HT)[i].parent = (*HT)[i].lchild = (*HT)[i].rchild = 0;
	}
	for (int i = 1; i <= n; i++)
	{
		printf("��������Ȩ��:");
		scanf("%d", &(*HT)[i].weight);
	}
	for (int i = n + 1; i <= m; i++)
	{
		int s1, s2;
		Select(*HT, i-1, &s1, &s2);
		(*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
		(*HT)[s1].parent = (*HT)[s2].parent = i;
		(*HT)[i].lchild = s1, (*HT)[i].rchild = s2;
	}
}
//��Ϊ����Ҫ�����Ĺ����������ŵ�һ�������У��������������ַ�������ʾ�����ַ�����һ����ַ�����������Ź����������������һ������ָ��
//�������Ԫ�����ַ�����Ҳ����һ��ָ�룬����������Ϊ����ָ��,������Ҫ���ν�CreatHuffmanCode�����У����õ��Ĺ���������Ž�����
//���Դ���Ĳ�������һ������ָ�룬Ϊ����ߴ�ָ�룬���ǽ��ַ��Ķ���ָ�룬Ҳ���Ǵ�Ź����������ַ��������鶨��ΪHuffmanCode
typedef char** HuffmanCode;
//��������������
void CreatHuffmanCode(HuffmanTree HT,HuffmanCode* Code,int n)
{
	*Code = (HuffmanCode)malloc(sizeof(char*) * (n + 1));  //��Ϊ�������������1��ʼ������Ϊ������ƥ�䣬��ű����ַ���������Ҳ�����1��ʼ
	for (int i = 1; i <= n; i++)
	{
		char* cd = (char*)malloc(sizeof(char) * n);    //cd������������ַ�0��1
		//��n��Ҷ���Ĺ������������n-1�㣬Ҳ����˵Ҷ���Ĺ��������������n-1���ַ�
		//���ﴴ��n���ַ�����Ϊ��һ���ַ�Ҫ��'\0'
		cd[n - 1] = '\0';   //���һ���ַ���'\0'��Ϊ����
		//��ΪҶ���Ĺ����������ǴӸ���㵽Ҷ���֮������Һ��Ӵ����0��1��ɵģ�������ֻ�ܴ���֪��Ҷ�����Ѱ��˫��
		// ��Ҷ������ǹ�����������ײ㣬���Եõ���0��1���������ϵġ�������Ҫ�Ĺ������������������µģ��������ǵõ���0��1Ҫ���Ŵ���cd������
		int start = n - 1;   //����start=n-1
		int c = i;   //c��������Ѱ��˫��
		//��Ҷ���һֱ������ֱ���ҵ�����㣬��Ϊ��֪��Ҫ�Ҽ��Σ�������whileѭ������Ϊ�����û��˫�ף����Ը�����parent=0
		int pa = HT[i].parent;
		while (pa != 0)   //��������Ϊ˫��Ϊ0�����Ѿ��ҵ������λ��
		{
			if (HT[pa].lchild == c)  //˫�׵���������Ǵ˽��
				cd[--start] = '0';   //��ô����Ϊ1����֮������Һ��ӣ�����Ϊ0
			else
				cd[--start] = '1';
			c = pa, pa = HT[pa].parent;   //���������һ������c������i����ô����ı���iֵ������forѭ���ͻᱻ�ƻ�
			//�������Ľ���Ϊ�˽���˫�׽�㣬pa���ڴ˽��˫�׵�˫��
		}
		//*CodeΪ����ָ�룬����һ��ָ�����飬����Ԫ��Ϊһ��ָ�룬ָ������ַ�������Ԫ�ص�ַ
		  //����Ϊn-start��cd����Ϊn��cd���鲻һ����������ĳ��Ҷ���ı��볤�Ⱦ�Ϊn-start������'\0')
		(*Code)[i] = (char*)malloc(sizeof(char) * (n - start)); 
		strcpy((*Code)[i], &cd[start]); //��cd��������ַ�����startλ�ÿ�ʼ������ַ��������Ƶ���Ź����������������
		free(cd),cd = NULL;;   //��cd�Ŀռ��ͷų���
	}
}
int main()
{
	HuffmanTree HT;
	HuffmanCode Code;
	CreatHuffmanTree(&HT,8);
	CreatHuffmanCode(HT, &Code, 8);
	for(int i=1;i<=8;i++)
	{
		printf("%s\n", Code[i]);
	}
	return 0;
}