#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//哈夫曼树构造
//顺序存储结构
typedef struct    //定义结点类型
{
	int weight;   //结点权重值
	int parent, lchild, rchild;   //结点的双亲，左孩子，右孩子的下标
}HTNode,*HuffmanTree;
//由于采用数组来存储哈夫曼树结点，而结点编号又是由1开始，所以为了实现方便，数组0号单元不使用，从1号单元开始使用
// 哈夫曼树一共有2n-1个结点，所以理论上来说应创建数组的大小为2n-1，但数组要从1开始存储，所以应创建数组的大小为2n
//  数组可以动态开辟
//数组元素就是哈夫曼树结点，一个结点包含权重，双亲，左孩子右孩子
void Select(HuffmanTree HT, int len, int* s1, int* s2)
{
	int min1;   //设置min1为权值最小值，pos1为权值最小值对应的下标，最开始令min1等于数组的第一个权值
	int min2;     //min2为数组结点权值的次小值
	int pos1;     //min1为数组的第一个权值，pos1对应为1
	int pos2;   //pos2为权值次小值对应的小标
	for (int i = 1; i <= len; i++)
	{   //先用for循环找到第一个parent为0的位置，将其权值赋给min1并记下位置
		if (HT[i].parent == 0)
		{
			min1 = HT[i].weight;
			pos1 = i;
			break;
		}
	}
	//再用for循环找到第二个parent为0的位置，将其权值赋给min2并记下位置
	for (int i = 1; i <= len; i++)
	{
		if (HT[i].parent == 0 && i != pos1)
		{
			min2 = HT[i].weight;
			pos2 = i;
			break;
		}
	}
	for (int i = 1; i <= len; i++)   //遍历数组
	{
		if (HT[i].parent == 0)    //如果数组结点还是根结点（没有双亲），则让这个根结点的权值与min1比较
		{
			if (min1 > HT[i].weight)    //如果遍历的数组结点的权值小于min1的值
			{
				min1 = HT[i].weight;   //则把最小权值改为该结点的权值，对应的下标pos1也改
				pos1 = i;
			}
		}
	}
	if (pos2 == pos1)     //如果第一次修改后的min1值所在的位置刚好是min2所在位置，则min2再找一个新的parent为0的位置
	{
		for (int i = pos2 + 1; i <= len; i++)   //i从pos2+1开始遍历
		{
			if (HT[i].parent == 0 ) 
			{
				min2 = HT[i].weight;
				pos2 = i;
				break;
			}
		}
	}
	//找到pos2新起点后，开始寻找次小值
	for (int i = 1; i <= len; i++)    //进入该循环找次小值
	{
		if (i == pos1)   //如果遍历到了最小值所在位置，跳过
			continue;
		if (HT[i].parent == 0)     //比较与min1同理
		{
			if (min2 > HT[i].weight)
			{
				min2 = HT[i].weight;
				pos2 = i;
			}
		}
	}
	*s1 = pos1, * s2 = pos2;   //将最小值min1和次小值min2的位置赋给s1和s2
}
//寻找最小和次小权值的更精简办法
void Select2(HuffmanTree HT, int len, int* s1, int* s2)
{
	int min1, min2;
	min1 = min2 = INT_MAX;   //将权值赋为整型最大值
	int pos1, pos2;
	pos1 = pos2 = 0;
	for (int i = 1; i < len + 1; ++i) {
		if (HT[i].parent == 0) 
		{
			if (HT[i].weight < min1)    //如果权值1大于遍历的结点的权值
			{
				min2 = min1;   //min2=min1的理由是：min1始终小于min2，因为min1是最小值，min2是次小值
				              //当找到一个权值比min1还要小，那么原来的min1最小值变成了次小值，所以就把min1的值赋给min2
				pos2 = pos1;  //而min1等于这个更小的权值
				min1 = HT[i].weight;   //将遍历到的较小的结点权值赋给min1
				pos1 = i;
			}
			else if (HT[i].weight < min2)    //如果遍历到的结点权值小于min2
			{
				min2 = HT[i].weight;   //则将其赋给min2
				pos2 = i;
			}
		}
	}
	*s1 = pos1;
	*s2 = pos2;
}
void CreatHuffmanTree(HuffmanTree* HT, int n)    //n为权值个数
{
	//先创建好数组并初始化 
	if (n <= 1)
		return;
	int m = 2 * n - 1;     //数组内一共2n-1个元素
	*HT = (HuffmanTree)malloc(sizeof(HTNode) * (m+1));    //创建数组大小为2n
	for (int i = 1; i <= m; i++)
	{
		(*HT)[i].lchild = 0;   //先将所有的结点的左孩子和右孩子和双亲都初始化为0
		(*HT)[i].rchild = 0;
		(*HT)[i].parent = 0;   
	}
	for (int i = 1; i <= n; i++)
	{
		printf("输入结点权值：");
		scanf("%d", &(*HT)[i].weight);
	}
	//再开始构造哈夫曼树
	for (int i = n + 1; i <= m; i++)
	{
		int s1, s2;
		//从数组HT[k](1<=k<=i-1)，即已经构造好权值，双亲，左右孩子的数组中挑选两个权值最小的且其双亲域为0的结点，返回其在数组中的序号
		Select(*HT, i - 1, &s1, &s2); 
		//挑选好两个权值最小的结点后，开始构造哈夫曼树，先把两个权值最小的结点的双亲改为i
		(*HT)[s1].parent = i, (*HT)[s2].parent = i;  //因为这两个结点构造出来的双亲就要放在数组下标为i中的位置上
		(*HT)[i].lchild = s1, (*HT)[i].rchild = s2;      //把构造出来的双亲结点的左孩子和右孩子分别赋为挑选出来的两个结点的下标
		(*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;    //构造出来的双亲的权值为左右孩子权值之和
	}
}
int main()
{
	HuffmanTree T;
	CreatHuffmanTree(&T,8);
	return 0;
}