#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
typedef struct Lnode
{
	int data;
	struct Lnode* next;
}Lnode, * LinkList;
//创建有序链表
Lnode* Creat_Sq()
{
	int n, ret;
	char str[1001];
	printf("输入要创建结点个数：");
again:
	ret = scanf("%d", &n);
	if (!ret)
	{
		while (gets_s(str, 1000))
		{
			printf("请输入正确的数字:");
			goto again;
		}
	}
	LinkList L = (Lnode*)malloc(sizeof(Lnode));
	L->next = NULL;
	for (int i = 0; i < n; i++)
	{
		Lnode* p = (Lnode*)malloc(sizeof(Lnode));
		printf("请输入该结点的数据：");
		scanf("%d", &(p->data));
		//按data由小到大的顺序排结点
		Lnode* pre = L;       //因为我们要给所创建的链表排序，要比较两个结点的指数大小，所以可能存在插入的操作
		//链表的插入操作需要用到一前一后两个指针，所以我们要创建一个q指针和q的前驱指针pre
		Lnode* q = pre->next;   //q用来遍历链表，比较新创建的结点指数和旧结点的指数
		//因为我们要用q来找到是否存在一个结点的指数大于新结点的指数，所以q就要从头到尾遍历，直到找到一个结点的指数大于新结点的指数或者一直找到链表的尾部都没有
		while (q && q->data <= p->data)
		{
			pre = q;
			q = q->next;
		}
		p->next = q;
		pre->next = p;
	}
	return L;
}
//创建无序链表
Lnode* Creat()
{
	int n, ret;
	char str[1001];
	printf("输入要创建的多项式项数：");
again:
	ret = scanf("%d", &n);
	if (!ret)
	{
		while (gets_s(str, 1000))
		{
			printf("请输入正确的数字:");
			goto again;
		}
	}
	LinkList L = (Lnode*)malloc(sizeof(Lnode));
	L->next = NULL;
	Lnode* r = L;
	for (int i = 0; i < n; i++)
	{
		Lnode* p = (Lnode*)malloc(sizeof(Lnode));
		printf("请输入该结点的数据：");
		scanf("%d", &(p->data));
		p->next = r->next;               //用尾插法插入链表
		r->next = p;
		r = p;
	}
	return L;
}
//算法设计题
//6.设计一个算法，通过一趟遍历确定长度为n的单链表中值最大的结点
Lnode* Max(LinkList L)
{
	if (L->next == NULL)
		return NULL;
	int n;
	Lnode* p = L->next;
	Lnode* max = L->next;   //用max来指向链表中值最大的结点，最开始指向首元结点，当出现大于max的结点时，max重新赋值
	n = p->data;
	p = p->next;
	while (p)
	{
		if (p->data > n)
		{
			max = p;
			n = p->data;
		}
		p = p->next;
	}
	return max;
}

//7.设计一个算法，将链表中所有结点的连接方向“原地”逆转，即要求仅利用原表的存储空间，换句话说，要求算法空间复杂度为O(1)
void Reverse(LinkList* L)
{
	Lnode* p = (*L)->next;
	(*L)->next = NULL;
	while (p)
	{
		Lnode* hp = p;
		p = p->next;
		hp->next = (*L)->next;   //用头插法实现倒序
		(*L)->next = hp;  
	}
}

//8.设计一个算法，删除递增有序链表中值大于mink且小于maxk的所有元素，（mink和maxk是给定的两个参数，其值可以和表中元素相同，也可以不同）
void delete(LinkList* L, int mink, int maxk)
{
	Lnode* p = (*L)->next;
	Lnode* pre = *L;
	while (p)
	{
		if (p->data > mink && p->data < maxk)
		{
			Lnode* f = p;
			pre->next = p->next;
			p = p->next;
			free(f), f = NULL;
		}
		else
		{
			pre = p;
			p = p->next;
		}
	}
}

//9.已知p指向双向循环链表中的一个结点，其结点结构为data，prior，next三个域，写出算法change(p)，交换p所指向的结点及其前驱结点的顺序
typedef struct LoopNode  //定义双向循环链表的结点
{
	int data;
	struct LoopNode* prior;
	struct LoopNode* next;
}LoopNode,*LoopList;
//创建双向循环链表
LoopList Creat_Loop()
{
	int n, ret;
	char str[1001];
	printf("输入要创建的结点个数：");
again:
	ret = scanf("%d", &n);
	if (!ret)
	{
		while (gets_s(str, 1000))
		{
			printf("请输入正确的数字:");
			goto again;
		}
	}
	LoopList L = (LoopNode*)malloc(sizeof(LoopNode));
	L->next = NULL;
	LoopNode* r = L;  //创建指针r一直指向尾结点
	for (int i = 0; i < n; i++)
	{
		LoopNode* p = (LoopNode*)malloc(sizeof(LoopNode));
		printf("请输入该结点的数据：");
		scanf("%d", &(p->data));
		p->next = r->next;               //用尾插法插入链表
		r->next = p;
		p->prior = r;
		r = p;
	}
	//双向链表创建完后。此时r为尾结点，把尾结点与头结点连接起来
	L->prior = r;
	r->next = L;
	return L;
}
//交换双向循环链表中结点p及其前驱结点的顺序
void change(LoopNode* p)
{
	LoopNode* pre = p->prior;  //pre是p的前驱结点
	pre->next = p->next;   
	p->next->prior = pre;  
	p->next = pre;
	p->prior = pre->prior;
	pre->prior->next = p;
	pre->prior = p;
}

//10.已知长度为n的线性表A采用顺序存储结构，请写一个时间复杂度为O(n)、空间复杂度为O(1)的算法，该算法可删除线性表中所有为item的数据元素
typedef struct SqList
{
	int* data;
	int len;
}SqList;
void Creat_SqList(SqList* L)
{
	L->len = 0;
	int n, ret,elem;
	char str[1001];
	printf("输入要创建的元素个数：");
again:
	ret = scanf("%d", &n);
	if (!ret)
	{
		while (gets_s(str, 1000))
		{
			printf("请输入正确的数字:");
			goto again;
		}
	}
	L->data = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
	{
		printf("请输入数据：");
		scanf("%d", &elem);
		L->data[i] = elem;
		L->len++;
	}
}

void Delete_item(SqList* L,int item)
{
	int left = 0;         //题目只是说删除掉与item相等的元素，并没有说不能调换位置
	int right = L->len- 1;               //设置一个头指针和尾指针，头指针向右遍历，尾指针向左遍历
	L->len = 0;              //把表长度置0，重新计算删除元素后表的长度             
	while (left <= right)        //当头指针大于尾指针时循环结束
	{
		if (L->data[left] == item)            //如果头指针的数等于item，则尾指针向左遍历
		{
			while (L->data[right] == item&&left<=right)      //尾指针的数如果也等于item，则跳过，继续向左遍历，前提为不能小于头指针
			{
				right--;
			}
			if (left > right)      //如果头指针大于尾指针，则循环结束
				break;
			L->data[left] = L->data[right];     //如果没大于，说明尾指针当前指的数不等于item，则交换头指针和尾指针的数
			right--;  //交换完后尾指针继续向左遍历
		}
		left++;     //交换了或者不交换都说明左指针此时指向的值都不等于item，于是左指针向右遍历
		L->len++;    //随着左指针遍历而增加表长
	}
}
 //时间复杂度为O(n)，因为表长为n，左指针和右指针同时向中间遍历，一共就遍历了n个元素
//空间复杂度为O(1)，交换操作在表上进行，没有使用额外的辅助空间
int main()
{
	//LoopList L = Creat_Loop();
	//change(L->next->next->next);
	//Lnode* p = Max(L);
	//Reverse(&L);
	//delete(&L, 0, 10);
	/*Lnode* p = L->next;
	while(p)
	{
		printf("%d ", p->data);
		p = p->next;
	}*/
	SqList L;
	Creat_SqList(&L);
	for (int i = 0; i < L.len; i++)
	{
		printf("%d ", L.data[i]);
	}
	printf("\n");
	Delete_item(&L, 4);
	for (int i = 0; i < L.len; i++)
	{
		printf("%d ", L.data[i]);
	}
	return 0;
}