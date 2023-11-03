#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//������������
//˳��洢�ṹ
typedef struct    //����������
{
	int weight;   //���Ȩ��ֵ
	int parent, lchild, rchild;   //����˫�ף����ӣ��Һ��ӵ��±�
}HTNode,*HuffmanTree;
//���ڲ����������洢����������㣬�������������1��ʼ������Ϊ��ʵ�ַ��㣬����0�ŵ�Ԫ��ʹ�ã���1�ŵ�Ԫ��ʼʹ��
// ��������һ����2n-1����㣬������������˵Ӧ��������Ĵ�СΪ2n-1��������Ҫ��1��ʼ�洢������Ӧ��������Ĵ�СΪ2n
//  ������Զ�̬����
//����Ԫ�ؾ��ǹ���������㣬һ��������Ȩ�أ�˫�ף������Һ���
void Select(HuffmanTree HT, int len, int* s1, int* s2)
{
	int min1;   //����min1ΪȨֵ��Сֵ��pos1ΪȨֵ��Сֵ��Ӧ���±꣬�ʼ��min1��������ĵ�һ��Ȩֵ
	int min2;     //min2Ϊ������Ȩֵ�Ĵ�Сֵ
	int pos1;     //min1Ϊ����ĵ�һ��Ȩֵ��pos1��ӦΪ1
	int pos2;   //pos2ΪȨֵ��Сֵ��Ӧ��С��
	for (int i = 1; i <= len; i++)
	{   //����forѭ���ҵ���һ��parentΪ0��λ�ã�����Ȩֵ����min1������λ��
		if (HT[i].parent == 0)
		{
			min1 = HT[i].weight;
			pos1 = i;
			break;
		}
	}
	//����forѭ���ҵ��ڶ���parentΪ0��λ�ã�����Ȩֵ����min2������λ��
	for (int i = 1; i <= len; i++)
	{
		if (HT[i].parent == 0 && i != pos1)
		{
			min2 = HT[i].weight;
			pos2 = i;
			break;
		}
	}
	for (int i = 1; i <= len; i++)   //��������
	{
		if (HT[i].parent == 0)    //��������㻹�Ǹ���㣨û��˫�ף����������������Ȩֵ��min1�Ƚ�
		{
			if (min1 > HT[i].weight)    //����������������ȨֵС��min1��ֵ
			{
				min1 = HT[i].weight;   //�����СȨֵ��Ϊ�ý���Ȩֵ����Ӧ���±�pos1Ҳ��
				pos1 = i;
			}
		}
	}
	if (pos2 == pos1)     //�����һ���޸ĺ��min1ֵ���ڵ�λ�øպ���min2����λ�ã���min2����һ���µ�parentΪ0��λ��
	{
		for (int i = pos2 + 1; i <= len; i++)   //i��pos2+1��ʼ����
		{
			if (HT[i].parent == 0 ) 
			{
				min2 = HT[i].weight;
				pos2 = i;
				break;
			}
		}
	}
	//�ҵ�pos2�����󣬿�ʼѰ�Ҵ�Сֵ
	for (int i = 1; i <= len; i++)    //�����ѭ���Ҵ�Сֵ
	{
		if (i == pos1)   //�������������Сֵ����λ�ã�����
			continue;
		if (HT[i].parent == 0)     //�Ƚ���min1ͬ��
		{
			if (min2 > HT[i].weight)
			{
				min2 = HT[i].weight;
				pos2 = i;
			}
		}
	}
	*s1 = pos1, * s2 = pos2;   //����Сֵmin1�ʹ�Сֵmin2��λ�ø���s1��s2
}
//Ѱ����С�ʹ�СȨֵ�ĸ�����취
void Select2(HuffmanTree HT, int len, int* s1, int* s2)
{
	int min1, min2;
	min1 = min2 = INT_MAX;   //��Ȩֵ��Ϊ�������ֵ
	int pos1, pos2;
	pos1 = pos2 = 0;
	for (int i = 1; i < len + 1; ++i) {
		if (HT[i].parent == 0) 
		{
			if (HT[i].weight < min1)    //���Ȩֵ1���ڱ����Ľ���Ȩֵ
			{
				min2 = min1;   //min2=min1�������ǣ�min1ʼ��С��min2����Ϊmin1����Сֵ��min2�Ǵ�Сֵ
				              //���ҵ�һ��Ȩֵ��min1��ҪС����ôԭ����min1��Сֵ����˴�Сֵ�����ԾͰ�min1��ֵ����min2
				pos2 = pos1;  //��min1���������С��Ȩֵ
				min1 = HT[i].weight;   //���������Ľ�С�Ľ��Ȩֵ����min1
				pos1 = i;
			}
			else if (HT[i].weight < min2)    //����������Ľ��ȨֵС��min2
			{
				min2 = HT[i].weight;   //���丳��min2
				pos2 = i;
			}
		}
	}
	*s1 = pos1;
	*s2 = pos2;
}
void CreatHuffmanTree(HuffmanTree* HT, int n)    //nΪȨֵ����
{
	//�ȴ��������鲢��ʼ�� 
	if (n <= 1)
		return;
	int m = 2 * n - 1;     //������һ��2n-1��Ԫ��
	*HT = (HuffmanTree)malloc(sizeof(HTNode) * (m+1));    //���������СΪ2n
	for (int i = 1; i <= m; i++)
	{
		(*HT)[i].lchild = 0;   //�Ƚ����еĽ������Ӻ��Һ��Ӻ�˫�׶���ʼ��Ϊ0
		(*HT)[i].rchild = 0;
		(*HT)[i].parent = 0;   
	}
	for (int i = 1; i <= n; i++)
	{
		printf("������Ȩֵ��");
		scanf("%d", &(*HT)[i].weight);
	}
	//�ٿ�ʼ�����������
	for (int i = n + 1; i <= m; i++)
	{
		int s1, s2;
		//������HT[k](1<=k<=i-1)�����Ѿ������Ȩֵ��˫�ף����Һ��ӵ���������ѡ����Ȩֵ��С������˫����Ϊ0�Ľ�㣬�������������е����
		Select(*HT, i - 1, &s1, &s2); 
		//��ѡ������Ȩֵ��С�Ľ��󣬿�ʼ��������������Ȱ�����Ȩֵ��С�Ľ���˫�׸�Ϊi
		(*HT)[s1].parent = i, (*HT)[s2].parent = i;  //��Ϊ��������㹹�������˫�׾�Ҫ���������±�Ϊi�е�λ����
		(*HT)[i].lchild = s1, (*HT)[i].rchild = s2;      //�ѹ��������˫�׽������Ӻ��Һ��ӷֱ�Ϊ��ѡ���������������±�
		(*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;    //���������˫�׵�ȨֵΪ���Һ���Ȩֵ֮��
	}
}
int main()
{
	HuffmanTree T;
	CreatHuffmanTree(&T,8);
	return 0;
}