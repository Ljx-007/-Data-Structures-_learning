#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//合并两个线性表

//有序表的合并--顺序表实现
//typedef struct SqList  //先定义一个顺序表
//{
//	int *elem;
//	int len;
//}SqList;
//
////合并两个顺序表
//void MergeList(SqList La, SqList Lb, SqList* Lc)
//{
//	int* pa = La.elem;  //把表a的首元素地址赋给指针pa
//	int* pb = Lb.elem;  //把表b的首元素地址赋给指针pb
//	Lc->len = 0;
//	Lc->elem = (int*)malloc(sizeof(int)* (La.len+Lb.len));  //为表c存放元素的位置开辟一块长度为表a，b之和的空间，因为最坏情况为 a，b元素不重复，表c元素为a，b之和
//	int* pc = Lc->elem; //把表c的首元素地址赋给指针pc
//	//为了能判断表a，b什么时候全部遍历完，还要创建尾指针指向两表的最后一个元素
//	int* pa_past = La.elem + La.len - 1;  
//	int* pb_past = Lb.elem + Lb.len - 1;
//	while (pa <= pa_past && pb <= pb_past)  //两个表都未到达表尾
//	{
//		//比较两个表中元素较小的那个，放入表c
//		if (*pa < *pb)  
//			*pc++ = *pa++,Lc->len++;
//		//如果不想合并重复的元素，那么就再多加一个条件判断
//		else if (*pb == *pa)
//		{
//			*pc++ = *pa++;  //，如果两值相同，随意选择其中的一个值放入表c
//			*pb++;   //另外一个表的指针也要增加
//			Lc->len++;
//		}
//		else
//			*pc++ = *pb++,Lc->len++;
//	}
//	//如果其中一个表到表尾了，那么另一个表的元素就全放进表c中
//	while (pa <= pa_past)  //Lb到表尾
//		*pc++ = *pa++, Lc->len++;
//	while (pb <= pb_past) //La到表尾
//		*pc++ = *pb++, Lc->len++;
//}
////该算法时间复杂度为O(La.len+Lb.len)   按照最坏情况，表a，b没有元素重复，算法最多执行次数为La.len+Lb.len次
////空间复杂度为O(La.len+Lb.len)
//
//int main()
//{
//	SqList La,Lb,Lc;
//	La.len = 0,Lb.len=0;
//	La.elem = (int*)malloc(sizeof(int) * 3);
//	for (int i = 0; i < 3; i++)
//	{
//		La.elem[i] = i+1;
//		La.len++;
//	}
//	Lb.elem = (int*)malloc(sizeof(int) * 5);
//	for (int i = 0; i < 5; i++)
//	{
//		Lb.elem[i] = i+2;
//		Lb.len++;
//	}
//	MergeList(La, Lb, &Lc);
//	for (int i = 0; i < Lc.len; i++)
//	{
//		printf("%d ", Lc.elem[i]);
//	}
//	return 0;
//}


//链表有序表的合并
typedef struct Lnode
{
	int data;
	struct Lnode* next;
}Lnode, * LinkList;

//初始化链表
Lnode* InitList()
{
	int n,ret;
	char str[1001];
	printf("要输入的元素个数：");
	again:
	ret=scanf("%d", &n);
	if (ret != 1)
	{
		while (gets_s(str, 1000))
		{
			printf("请输入数字：");
			goto again;
		}
	}
	//先创建一个头结点
	LinkList L = (Lnode*)malloc(sizeof(Lnode));
	L->next = NULL;
	Lnode* r = L;
	for (int i = 0; i < n; i++)
	{
		Lnode* p = (Lnode*)malloc(sizeof(Lnode));
		if (!p)
		{
			perror("creat Lnode error");
			return  - 1;
		}
		printf("请输入数据域中的数据（int型）：");
		again2:
		ret = scanf("%d", &(p->data));
		if (ret != 1)
		{
			while(gets_s(str,1000))  //读取缓冲区的字符
			{
				printf("请按要求输入:");
				goto again2;
			}		
		}
		p->next = NULL;
		r->next = p;
		r = p;
	}
	return L;
}

//合并链表
void MergeList(LinkList La, LinkList Lb, LinkList Lc)   //合并链表a，b，并将合并的数据存放到表c中
{
	Lnode* pa = La->next;  //令pa指向表a的首元结点
	Lnode* pb = Lb->next;	//pb指向表b的首元结点
	Lc = La;  //让表c的从表a的头结点开始，也就是说合并后的数据直接放在表a中，表a就是表c
	Lnode* pc = Lc;   //pc指向表c的头结点
	while (pa && pb)   
	{
		if (pa->data > pb->data)
		{   //如果表a的结点的数据大于表b的结点的数据
			pc->next = pb;  //那么pc指向的结点的下一个结点就是pb指向的结点
			pb = pb->next;  //pb向后移一个结点
			pc = pc->next;  //pc也向后移一个结点
		}
		//合并过程中，pc始终指向表c的最后一个结点
		else if (pa->data == pb->data)  //如果不想合并重复的元素，就多加一个判断
		{
			pc->next = pb;  //表a,b的数据相同，选择表a，b其中一个数据放入表c即可，这里选择表b
			Lnode* px = pa; //数据填入表c后，pa和pb都要指向下一个结点，然而这里要用px来记录一下表a中与表b相同数据的那个结点
			//因为如果不记录，pa就会跳过这个结点，那么被跳过的这个结点的空间就没有被释放，可能会造成内存泄漏
			pb = pb->next;
			pa = pa->next;  //数据相同，记录好后pa，pb，pc都要指向下一个结点
			pc = pc->next;
			free(px), px = NULL;  //释放掉表a那个被跳过的结点内存
		}
		else
		{
			pc->next = pa;  //如果表b的数据大于表a，则把a的数据存放到表c中
			pa = pa->next;
			pc = pc->next;  //pa，pc都指向下一个结点
		}
	}
	//跳出循环的条件：pa或者pb为空值，也就是说表a或表b已经读到结尾了
	//其中一个表结束了，那么就把另一个表剩下的结点都接在表c后
	pc->next = pa ? pa : pb;  	//此处判断pa如果为空，那么就把表b剩下的结点接在pc后，反之把表a的结点接在pc后
	free(Lb), Lb = NULL;
}
#define PRINTF(x) printf("请初始化链表"#x"\n")
int main()
{
	PRINTF(a);
	LinkList La = InitList();
	PRINTF(b);
	LinkList Lb = InitList();
	LinkList Lc = (Lnode*)malloc(sizeof(Lnode));
	//这里MergeList的传参有点问题
	//这里函数MergeList传参Lc时传的是Lc这个指针本身，在动态开辟内存时，Lc指向了我们开辟的那块内存的地址
	
	// 传参到MergeList函数时，其实传的是Lc的一个副本，在MergeList函数中，我们把这个副本Lc指向的位置修改为了链表La的位置
	
	// 然后在函数里修改的Lc其实一直都是副本Lc，并不是我们创建的那个Lc。所以在出了MergeList函数后，会发现Lc指向的内容什么都没有
	
	// 因为我们根本没有修改实际的Lc指向的内容，我们一直在修改副本Lc指向的内容，即只是修改了Lc指向的链表的内容，并没有修改Lc
	
	//如果想让实际的Lc的指向发生改变，则应该传Lc的地址，这允许我们在函数内部修改Lc的时候，同时修改Lc所指向的地址
	
	//这意味着可以在函数内部创建一个新链表并将 Lc 指针指向它，这将影响到 Lc 在函数外部的值。
	MergeList(La, Lb, Lc);
	//如果不想传入Lc的地址的话，另外一种修改方式为：
	// 将表a，b在MergeList函数中合并后，把合并后的链表的地址返回出来用Lc接收
	//LinkList Lc = MergeList(La, Lb);  
	Lnode* pa = La->next;
	while (pa)
	{
		printf("%d ", pa->data);
		pa = pa->next;
	}
	return 0;
}