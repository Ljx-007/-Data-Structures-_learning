#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//实现哈夫曼编码，先构造哈夫曼树
typedef struct HuffmanNode
{
	int weight;
	int parent, lchild, rchild;
}HuffmanNode,*HuffmanTree;
void Select(HuffmanTree HT, int len,int* s1, int* s2)
{
	int min1, min2, pos1, pos2;
	//先让min1和min2找到最前面的两个根结点
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
	//再寻找权值最小和次小的结点，我们规定，min1为权值最小，miin2为次小
	for (int i = 1; i <= len; i++)
	{
		if (HT[i].parent == 0)
		{
			if(min1>HT[i].weight)   //如果结点权值小于min1，则min1不是最小
			{
				min2 = min1;   //先把min1原来代表的最小值赋给min2，min2此时为次小权值
				pos2 = pos1;
				min1 = HT[i].weight;   //再让min1等于最小权值
				pos1 = i;
			}
			//如果出现结点权值大于最小，小于次小的情况，那么就让次小值min2等于该结点权值
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
		printf("请输入结点权重:");
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
//因为我们要将最后的哈夫曼编码存放到一个数组中，哈夫曼编码用字符串来表示，而字符串是一个地址，所以这个存放哈夫曼编码的数组是一个二级指针
//该数组的元素是字符串，也就是一级指针，所以数组名为二级指针,该数组要传参进CreatHuffmanCode函数中，将得到的哈夫曼编码放进数组
//所以传入的参数又是一个三级指针，为避免高次指针，我们将字符的二级指针，也就是存放哈夫曼编码字符串的数组定义为HuffmanCode
typedef char** HuffmanCode;
//创建哈夫曼编码
void CreatHuffmanCode(HuffmanTree HT,HuffmanCode* Code,int n)
{
	*Code = (HuffmanCode)malloc(sizeof(char*) * (n + 1));  //因为哈夫曼树从序号1开始，所以为了与其匹配，存放编码字符串的数组也从序号1开始
	for (int i = 1; i <= n; i++)
	{
		char* cd = (char*)malloc(sizeof(char) * n);    //cd数组用来存放字符0或1
		//有n个叶结点的哈夫曼树最多有n-1层，也就是说叶结点的哈夫曼编码最多有n-1个字符
		//这里创建n个字符是因为有一个字符要放'\0'
		cd[n - 1] = '\0';   //最后一个字符放'\0'作为结束
		//因为叶结点的哈夫曼编码是从根结点到叶结点之间的左右孩子代表的0和1组成的，而我们只能从已知的叶结点来寻找双亲
		// 而叶结点又是哈夫曼树的最底层，所以得到的0或1是由下往上的。我们需要的哈夫曼编码是由上往下的，所以我们得到的0或1要倒着存在cd数组中
		int start = n - 1;   //于是start=n-1
		int c = i;   //c用来向上寻找双亲
		//从叶结点一直往上找直到找到根结点，因为不知道要找几次，所以用while循环，因为根结点没有双亲，所以根结点的parent=0
		int pa = HT[i].parent;
		while (pa != 0)   //结束条件为双亲为0，即已经找到根结点位置
		{
			if (HT[pa].lchild == c)  //双亲的左孩子如果是此结点
				cd[--start] = '0';   //那么编码为1，反之如果是右孩子，编码为0
			else
				cd[--start] = '1';
			c = pa, pa = HT[pa].parent;   //如果不创建一个变量c来代替i，那么这里改变了i值，外层的for循环就会被破坏
			//将检索的结点变为此结点的双亲结点，pa等于此结点双亲的双亲
		}
		//*Code为二级指针，他是一个指针数组，数组元素为一级指针，指向编码字符串的首元素地址
		  //长度为n-start，cd长度为n，cd数组不一定被存满，某个叶结点的编码长度就为n-start（包括'\0')
		(*Code)[i] = (char*)malloc(sizeof(char) * (n - start)); 
		strcpy((*Code)[i], &cd[start]); //将cd数组里的字符，从start位置开始往后的字符串，复制到存放哈夫曼编码的数组中
		free(cd),cd = NULL;;   //把cd的空间释放出来
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