#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//算法设计题
//1、写出折半查找的递归算法
int Search_Bin(int arr[],int lenth, int e,int left,int right)
{
	if (left > right)
		return 0;
	int mid = (left + right) / 2;
	if (arr[mid] == e)
		return mid;
	else if (arr[mid] < e)
		return Search_Bin(arr, lenth, e, mid + 1, right);
	else
		return Search_Bin(arr, lenth, e, left, mid - 1);
}
//int main()
//{
//	int arr[6] = { 1,2,3,4,5,6 };
//	int ret=Search_Bin(arr, sizeof(arr) / sizeof(arr[0]),7, 0, sizeof(arr) / sizeof(arr[0]) - 1);
//	if (!ret)
//		printf("没找到\n");
//	else
//		printf("找到了，下标为%d", ret);
//	return 0;
//}

//2、试写一个判别给定二叉树是否为二叉排序树的算法
typedef struct BTnode   //定义一个二叉树类型
{
	int a;   //关键字a
	struct BTnode* lchild, * rchild;
}BTnode, *BTree;
typedef struct Stacknode
{
	BTnode *t;
	struct Stacknode* next;
}Stacknode,*LinkStack;
void InitStack(LinkStack* S)
{
	*S = NULL;
}
void Push(LinkStack* S,BTnode* e)
{
	Stacknode* p = (Stacknode*)malloc(sizeof(Stacknode));
	p->t = e;
	p->next = *S;
	*S = p;
}
BTnode* Pop(LinkStack* S)
{
	if (!S)
		return NULL;
	BTnode* e = (*S)->t;
	Stacknode* p = *S;
	*S = (*S)->next;
	free(p), p = NULL;
	return e;
}
int IsEmpty(LinkStack* S)
{
	if (*S == NULL)
		return 1;
	return 0;
}
void InsertBST(BTree* BST, int e)
{
	if (!(*BST))   //插入的结点都是叶子结点
	{
		BTnode* p = (BTnode*)malloc(sizeof(BTnode));
		p->a = e;
		p->lchild = p->rchild = NULL;
		*BST = p;
	}
	else if ((*BST)->a < e)
		InsertBST(&(*BST)->rchild, e);
	else if ((*BST)->a > e)
		InsertBST(&(*BST)->lchild, e);

}
int IsBST(BTree BT)
{
	if (!BT)
		return 0;
	BTnode* p = BT;
	LinkStack S;
	InitStack(&S);   //用链栈实现
	while (p->lchild || !IsEmpty(&S))  
	{
		if (p->lchild)
		{
			Push(&S, p);
			p = p->lchild;  //先找到二叉树的最左子树，并将路径上的根结点入栈
		}
		else
		{
			BTnode* q = Pop(&S);  //接着出栈根结点，比较左根右子树结点的大小
			if (q->lchild->a < q->a && q->a < q->rchild->a)
				p = q->rchild;   //如果满足有序排列，则开始遍历根结点的右子树
			else
				return 0;   //不满足则返回0
		}
	}
	return 1;  //如果栈空了，并且p的左子树为空（即p为叶子结点），并且没有在while循环中返回，说明该树为二叉排序树
}
//先序创建二叉树
void CreatBT(BTree* BT)
{
	int a;
	scanf("%d", &a);
	if (a == -1)
		*BT = NULL;
	else
	{
		*BT = (BTnode*)malloc(sizeof(BTnode));
		(*BT)->a = a;
		CreatBT(&(*BT)->lchild);
		CreatBT(&(*BT)->rchild);
	}
}
//int main()
//{
//	int arr[] = { 20,11,10,14,13,15,25,26 };
//	BTree BT=NULL;
//	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
//	{
//		InsertBST(&BT, arr[i]);
//	}
//	BTree BT2;
//	CreatBT(&BT2);
//	int ret = IsBST(BT2);
//	if (ret == 1)
//		printf("yes");
//	else
//		printf("no");
//	return 0;
//}

//3.已知二叉排序树采用二叉链表存储结构，根结点的指针为T，链结点的结构为（lchild，data，rchild），其中lchild、rchild分别指向该结点左右孩子的指针，
// data域存放结点的数据。请写出递归算法，从小到大输出二叉排序树中的所有数据值>=x的结点的数据
//要求先找到第一个满足条件的结点后，再依次输出其他满足条件的结点
typedef struct BSTnode
{
	int data;
	struct BSTnode* lchild, * rchild;
}BSTnode,*BSTree;
void Insert_BST(BSTree* BST, int e)
{
	if (!*BST)
	{
		BSTnode* p = (BSTnode*)malloc(sizeof(BSTnode));
		p->data = e;
		p->lchild = p->rchild = NULL;
		*BST = p;
	}
	else if ((*BST)->data < e)
		Insert_BST(&(*BST)->rchild, e);
	else if ((*BST)->data > e)
		Insert_BST(&(*BST)->lchild, e);
	else
	{
		printf("已存在该元素\n");
		return;
	}
}
void Printx(BSTree BST,int x)
{
	if (!BST)
		return;
	Printx(BST->lchild,x);
	if (BST->data >= x)
		printf("%d ", BST->data);
	Printx(BST->rchild, x);
}
//int main()
//{
//	int arr[]= { 20,11,10,14,13,15,25,22,26 };
//	BSTree BST = NULL;
//	for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
//	{
//		Insert_BST(&BST, arr[i]);
//	}
//	Printx(BST, 17);
//	return 0;
//}

//4.已知二叉树T的结点形式为（llink，data，count，rlink)，在树中查找值为X的结点，若找到，则记数（count）加1；
// 否则作为一个新结点插入树中，插入后仍为二叉排序树，写出其非递归算法。
typedef struct BT_node
{
	struct BT_node* llink, * rlink;
	int data, count;
}BT_node,*BT_Tree;
void InsertX(BT_Tree* BT,int x)
{
	BT_node* s = (BT_node*)malloc(sizeof(BT_node));
	s->count = 0, s->data = x;
	s->llink = s->rlink = NULL;
	if (!(*BT))
	{
		*BT = s;
		return;
	}
	BT_node* p = *BT;
	BT_node* f=0;
	while (p)
	{
		if (p->data == x)
		{
			p->count++;
			return;
		}
		f = p;
		if (p->data < x)
			p = p->rlink;
		else if(p->data>x)
			p = p->llink;
	}
	if (f->data > x)
		f->llink = s;   //这里不能直接让p=s，因为s是一个另外的指针指向另外的空间，如果p=s，那么p也指向这块空间去了，而没有跟二叉树建立联接
	else
		f->rlink = s;
}
//int main()
//{
//	BT_Tree BT = NULL;
//	int arr[] = { 20,11,10,14,13,15,25,22,26 };
//	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
//	{
//		InsertX(&BT, arr[i]);
//	}
//	return 0;
//}

//5.假设一棵平衡二叉树的每个结点都表明了平衡因子b，试设计一个算法，求平衡二叉树的高度
typedef struct BSTnodeb
{
	int data;
	int b;
	struct BSTnodeb* lchild, *rchild;
}BSTnodeb,*BSTreeb;
int HeightBST(BSTreeb BST)
{
	if (!BST)
		return 0;
	BSTnodeb* p = BST;
	int count = 0;
	while (p)
	{
		if (p->b >= 0)
		{
			p = p->lchild;
			count++;
		}
		else
		{
			p = p->rchild;
			count++;
		}
	}
	return count;
}

//6.分别写出在散列表中插入和删除关键字为K的一个记录的算法，设散列函数为H，解决冲突的方法为链地址法。
#define DEFAULTSIZE 50
typedef struct HashNode
{
	int key;
	struct HashNode* next;
}Hashnode,*HashTable[DEFAULTSIZE];   //HashTable是一个结构体指针数组类型，数组的元素是结构体指针
void InsertHash(HashTable HT, int k)   
{
	int hash = k % 47;  //假设散列函数H为k%47
	Hashnode* p = HT[hash];
	while (p->next)
	{
		if (p->next->key == k)
		{
			printf("已有此关键字\n");
			return;
		}
		else
			p = p->next;
	}
	Hashnode* s = (Hashnode*)malloc(sizeof(Hashnode));
	s->key = k;
	s->next = p->next;
	p->next = s;
}
int DeleteHash(HashTable HT, int k)
{
	int hash = k % 47;
	Hashnode* p = HT[hash];
	while (p->next)
	{
		if (p->next->key == k)
		{
			Hashnode* s = p->next;
			p->next = s->next;
			free(s), s = NULL;
			return 1;
		}
		p = p->next;
	}
	return 0;
}