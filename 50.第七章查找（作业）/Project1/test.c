#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//�㷨�����
//1��д���۰���ҵĵݹ��㷨
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
//		printf("û�ҵ�\n");
//	else
//		printf("�ҵ��ˣ��±�Ϊ%d", ret);
//	return 0;
//}

//2����дһ���б�����������Ƿ�Ϊ�������������㷨
typedef struct BTnode   //����һ������������
{
	int a;   //�ؼ���a
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
	if (!(*BST))   //����Ľ�㶼��Ҷ�ӽ��
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
	InitStack(&S);   //����ջʵ��
	while (p->lchild || !IsEmpty(&S))  
	{
		if (p->lchild)
		{
			Push(&S, p);
			p = p->lchild;  //���ҵ�����������������������·���ϵĸ������ջ
		}
		else
		{
			BTnode* q = Pop(&S);  //���ų�ջ����㣬�Ƚ�������������Ĵ�С
			if (q->lchild->a < q->a && q->a < q->rchild->a)
				p = q->rchild;   //��������������У���ʼ����������������
			else
				return 0;   //�������򷵻�0
		}
	}
	return 1;  //���ջ���ˣ�����p��������Ϊ�գ���pΪҶ�ӽ�㣩������û����whileѭ���з��أ�˵������Ϊ����������
}
//���򴴽�������
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

//3.��֪�������������ö�������洢�ṹ��������ָ��ΪT�������ĽṹΪ��lchild��data��rchild��������lchild��rchild�ֱ�ָ��ý�����Һ��ӵ�ָ�룬
// data���Ž������ݡ���д���ݹ��㷨����С������������������е���������ֵ>=x�Ľ�������
//Ҫ�����ҵ���һ�����������Ľ�������������������������Ľ��
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
		printf("�Ѵ��ڸ�Ԫ��\n");
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

//4.��֪������T�Ľ����ʽΪ��llink��data��count��rlink)�������в���ֵΪX�Ľ�㣬���ҵ����������count����1��
// ������Ϊһ���½��������У��������Ϊ������������д����ǵݹ��㷨��
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
		f->llink = s;   //���ﲻ��ֱ����p=s����Ϊs��һ�������ָ��ָ������Ŀռ䣬���p=s����ôpҲָ�����ռ�ȥ�ˣ���û�и���������������
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

//5.����һ��ƽ���������ÿ����㶼������ƽ������b�������һ���㷨����ƽ��������ĸ߶�
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

//6.�ֱ�д����ɢ�б��в����ɾ���ؼ���ΪK��һ����¼���㷨����ɢ�к���ΪH�������ͻ�ķ���Ϊ����ַ����
#define DEFAULTSIZE 50
typedef struct HashNode
{
	int key;
	struct HashNode* next;
}Hashnode,*HashTable[DEFAULTSIZE];   //HashTable��һ���ṹ��ָ���������ͣ������Ԫ���ǽṹ��ָ��
void InsertHash(HashTable HT, int k)   
{
	int hash = k % 47;  //����ɢ�к���HΪk%47
	Hashnode* p = HT[hash];
	while (p->next)
	{
		if (p->next->key == k)
		{
			printf("���д˹ؼ���\n");
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