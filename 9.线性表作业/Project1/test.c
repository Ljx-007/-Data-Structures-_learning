#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
typedef struct Lnode
{
	int data;
	struct Lnode* next;
}Lnode,*LinkList;
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
//算法设计题
//1.将两个递增的有序链表合并为一个递增的有序链表。要求结果链表仍使用原来两个链表的存储空间，不另外占用其他的存储空间。表中不允许有重复的数据
LinkList MergeList1(LinkList La, LinkList Lb)
{
	LinkList Lc = La;
	Lnode* pa = La->next;
	Lnode* pb = Lb->next;
	Lnode* pc = Lc;
	while (pa && pb)
	{
		if (pa->data < pb->data)
		{
			pc->next = pa;
			pa = pa->next;
			pc = pc->next;
		}
		else if (pa->data == pb->data)
		{
			pc->next = pa;
			Lnode* fb = pb;
			pa = pa->next;
			pb = pb->next;
			pc = pc->next;
			free(fb), fb = NULL;
		}
		else
		{
			pc->next = pb;
			pc = pc->next; 
			pb = pb->next;
		}
	}
	pc->next = pa ? pa : pb;
	free(Lb), Lb = NULL;
	return Lc;
}

//2.将两个非递减的有序链表合并为一个非递增的有序链表。要求结果链表仍使用原来两个链表的存储空间，不另外占用其他的存储空间。表中允许有重复的数据
LinkList MergeList2(LinkList La, LinkList Lb)
{
	LinkList Lc = La;
	Lnode* pa = La->next;
	Lnode* pb = Lb->next;
	Lnode* pc = Lc;
	Lnode* q;
	Lc->next = NULL;
	while (pa || pb)  //当表a表b都是空表了才退出循环
	{
		//q为我们从表a或者表b中摘取要放入表c的元素
		if (!pa)  //如果表a是空表，那么就把表b的元素放入表c
		{
			q = pb;
			pb = pb->next;
		}
		else if (!pb)  //如果表b是空表，那么就把表a剩下的的元素放入表c
		{
			q = pa;
			pa = pa->next;
		}
		else if (pa->data < pb->data)  //如果表a的元素大于表b的元素，那么摘取表a的元素，插入表b，同时表a向后遍历
		{
			q = pa;
			pa = pa->next;
		}
		else   //如果表b的元素大于等于表a的元素，那么摘取表b的元素，插入表a，同时表b向后遍历
		{
			q = pb;
			pb = pb->next;
		}
		q->next = Lc->next;  //采用头插法，则插入的元素顺序是倒序，所以正好符合元素从大到小的规定
		Lc->next = q;
		free(Lb), Lb = NULL;
	}
	return Lc;
}

//3.已知两个链表A和B分别表示两个集合，其元素递增排列。请设计一个算法，用于求出A与B的交集，并存放在A链表中
Lnode* Jiao(LinkList La, LinkList Lb)
{
	LinkList Lc = La;
	Lnode* pa = La->next;
	Lnode* pb = Lb->next;
	Lnode* pc = Lc;
	while (pa && pb)
	{
		if (pa->data == pb->data)
		{  //如果两数相等，则存放到表a中，pa，pb访问下一个结点
			pc->next = pa;
			pa = pa->next;
			pc = pc->next;
			pb = pb->next;
		}
		else if (pa->data < pb->data)    //因为两表都是递增的，所以如果出现了其中一个表的元素小于另一个表的元素，则要令小于的表向后访问结点
			                             //因为往后访问的值越来越大，有可能会出现相等的情况
		{
			Lnode* fa = pa;
			pa = pa->next;
			free(fa), fa = NULL;
		}
		else
		{
			Lnode* fb = pb;
			pb = pb->next;
			free(fb), fb = NULL;
		}
	}
	//找完交集后释放掉剩下的结点的空间
	while (pa)
	{
		Lnode* fa = pa;
		pa = pa->next;
		free(pa), pa = NULL;
	}
	while (pb)
	{
		Lnode* fb = pb;
		pb = pb->next;
		free(pb), pb = NULL;
	}
	pc->next = NULL;  //把交集链表的尾部置空，结束链表
	free(Lb), Lb = NULL;
	return Lc;
}

//4.已知链表A,B的元素递增排列，请设计算法求出两个集合A,B的差集（即仅由在A中出现而不在B中出现的元素所构成的集合），并以同样的形式存储
//  同时非返回该集合的元素个数
int AdelB(LinkList* La, LinkList Lb)
{
	int n = 0;
	Lnode* pre = *La;
	Lnode* pa = (*La)->next;
	Lnode* pb = Lb->next;
	while (pa && pb)
	{
		if (pa->data == pb->data)
		{
			Lnode* fa = pa;
			pre->next = pa->next;
			pa = pa->next;
			free(fa), fa = NULL;
		}
		else if(pa->data>pb->data)
		{
			Lnode* fb = pb;
			pb = pb->next;
			free(fb), fb = NULL;
		}
		else
		{
			pre = pa;
			pa = pa->next;
			n++;
		}
	}
	//表b空了后还要把表a剩下的元素也算上
	while (pa)
	{
		pa = pa->next;
		n++;
	}
	//把b多的元素删掉
	while (pb)
	{
		Lnode* fb = pb;
		pb = pb->next;
		free(fb), fb = NULL;
	}
	return n;
}

//5.设计算法将一个带头结点的单链表A分解为两个具有相同结构的链表B和C，其中B表的结点为A表中值小于零的结点，而C表的结点为A表中值大于零的结点
// （链表A中的元素为非零整数，要求B,C表利用A表的结点）
void DisCompose(LinkList* A,  LinkList* C)
{
	Lnode* pa = (*A)->next;
	Lnode* pre = *A;
	(*C)->next = NULL;
	Lnode* pc = *C;
	while (pa)
	{
		if (pa->data > 0)
		{
			Lnode* ha = pa;
			pre->next = pa->next;
			pa = pa->next;
			ha->next = pc->next;
			pc->next = ha;
			pc = pc->next;
		}
		else
		{
			pa = pa->next;
			pre = pre->next;
		}
	}
}
int main()
{
	LinkList La = Creat();
	//LinkList Lb = Creat();
	//LinkList Lc = MergeList2(La, Lb);
	//LinkList Lc = Jiao(La, Lb);
	//int n=AdelB(&La, Lb);
	LinkList C = (Lnode*)malloc(sizeof(Lnode));
	DisCompose(&La, &C);
	Lnode* pc = C->next;
	Lnode* pa = La->next;
	while (pa)
	{
		printf("%d ", pa->data);
		pa = pa->next;
	}
	printf("\n");
	while (pc)
	{
		printf("%d ", pc->data);
		pc = pc->next;
	}
	//printf("\n%d", n);
	return 0;
}