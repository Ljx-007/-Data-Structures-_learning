#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//二叉树先序遍历创建二叉树
typedef struct Binode
{
	char c;
	struct Binode* lchild, * rchild;
}Binode,*Bitree;
//递归算法
void ReCreatBiTree(Bitree* T)
{
	char ch;
	printf("请输入结点字符:");
	scanf("%c", &ch);
	//一个序列可以产生多种二叉树，为了确定唯一的二叉树，我们将二叉树的空结点也补上，用'#'代表，补全了空结点的二叉树就是唯一的二叉树
	if (ch == '#')    //用#来代表空结点
	{
		while ((ch = getchar()) != '\n') { ; }   //读取掉缓冲区的换行符
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
		(*T)->c = ch;   //将输入的字符填入二叉树
		while ((ch = getchar()) != '\n') { ; }
		ReCreatBiTree(&(*T)->lchild);    //递归创建左子树和右子树
		ReCreatBiTree(&(*T)->rchild);
	}
}
//复制二叉树
void Copy(Bitree* T, Bitree* copyT)
{
	if (!T)    //如果是空树，那么复制的树也是空的
	{
		copyT = NULL;
		return;
	}
	else
	{
		*copyT = (Bitree)malloc(sizeof(Binode));    //如果不是空树，先给复制树创建一块空间
		(*T)->c = (*copyT)->c;           //把树的内容copy到复制树中
		Copy(&(*T)->lchild, &(*copyT)->lchild);   //再递归复制左子树和右子树，要传入结点地址的地址
		Copy(&(*T)->rchild, &(*copyT)->rchild);
	}
}
//计算二叉树的深度
int Depth(Bitree* T)
{
	if (!*T)
		return 0;
	else
	{
		int m = 1 + Depth(&(*T)->lchild);   // 这里+1是为了加上根结点本层的深度
		int n = 1 + Depth(&(*T)->rchild);
		return m > n ? m : n;
	}
}
//计算二叉树的结点个数
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
		return m + n + 1;       //这里+1是为了算上根结点本身，本身结点加上左子树结点个数加上右子树结点个数
	}
}
//求叶子结点数
int Leafcount(Bitree* T)
{
	if (!*T)
		return 0;    //空树返回0
	if ((*T)->lchild == NULL && (*T)->rchild == NULL)
	{
		return 1;    //如果左子树和右子树都为空，说明这是一个叶结点，返回1
	}
	else
	{
		int m = Leafcount(&(*T)->lchild);    //返回左右子树叶结点数
		int n = Leafcount(&(*T)->rchild);
		return m + n;   //相加得二叉树叶结点数，因为根结点本身有左右子树，不算叶结点
	}
}
//测试代码
//int main()
//{
//	Bitree T;
//	ReCreatBiTree(&T);
//	printf("%d ", Depth(&T));
//	printf("%d ",Nodecount(&T));
//	return 0;
//}

//线索二叉树
//当二叉链表作为存储结构时，只能得到结点左右孩子的信息，不能直接得到结点在任意序列中的前驱和后继信息
// 例如，在中序遍历中，某二叉树的访问序列为EGFCBADHI,可知G结点的前驱是E，后继是F，但这些信息只能在遍历过程中才能得到
//  为此有以下三种解决方案，
//   1、重新遍历一次    （时间太长）
//   2、增加两个指针域存放前驱和后继的信息  （空间太大）
//   3.利用二叉链表中的空指针域    （最好办法）

//二叉树中n个结点，一共有2n个指针域，其中又有n-1个孩子，（根结点没有双亲，不是孩子），所以有n-1个指针域指向孩子，剩下的就是空指针域
// 
//所以空指针域的个数为：2n-（n-1）=n+1
// 
//如果某个结点的左孩子为空，那么左指针域改为指向其前驱
// 
//如果某个结点的右孩子为空，那么右指针域改为指向其后继
// 
//为了区别左右指针是指向孩子的还是前驱后继的，我们需要另设两个标志ltag和rtag
// 
//当指向孩子时，tag=0，指向前驱/后继时，tag=1

//如果没有前驱或者没有后继的结点他们的指针域该指向哪里呢？为了不让他们空着，再设置一个头结点，头结点一样有左右指针域，数据域和左右标志

//头结点的左指针域指向树的根结点，ltag=0，右指针域指向序列中最后一个结点，rtag=1；

//遍历序列中的第一个结点的左指针域和最后一个结点的右指针域原本都应该无所指向，现在令其指向头结点

typedef struct BiThrNode
{
	char data;
	struct BiThrNode* lchild, * rchild;
	int ltag, rtag;
}*BiThrTree;
//线索二叉树的用处：
// 令二叉树的遍历更加简便