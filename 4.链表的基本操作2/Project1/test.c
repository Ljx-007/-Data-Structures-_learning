#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct Student  //先创建一个学生类型
{
	char num[10];
	char name[8];
	int score;
}Stu;
typedef struct Lnode  //再创建一个链表结点类型
{
	Stu data;
	struct Lnode* next; //下一个结点的地址
}Lnode, * LinkList;

//链表的取值

//自己写的
//Stu GetElem_L(LinkList L, int num)   //num为要获取的链表中的第num个元素
//{
//	int count = 0;
//	Lnode* p = L;
//	if (num < 0)
//	{
//		printf("请使用正确的序号：");
//		return;
//	}
//	while (p)
//	{
//		p = p->next;
//		count++;
//		if (count == num)
//			return p->data;
//	}
//	if (num > count)
//	{
//		printf("没有这个元素\n");
//		return;
//	}
//}

//书上写的
void GetElem_L(LinkList L, int i, Stu* e)  //用来接收取到的值
{
	Lnode* p = L->next;  //先让p直接指向首元结点地址
	int j = 1;
	while (p && j < i)  //如果p为空值或者输入的i不合法，例如0，-1，就无法进入循环
	{
		p = p->next, j++;
	}
	//跳出循环有三种可能
	//1.p为空值，即链表遍历到最后一个结点后跳出
	//2.输入的i为不合法，例如第0个元素或者第-1个元素等
	//3.遍历到了第i个元素，j==i了
	if (!p || j > i)  //进入if语句的条件：1.p为空值，!p就为非零，进入循环，意为如果遍历完最后一个元素，都没有输出，代表要寻找的元素序号大于现有的元素个数
		             //                   2.j是不可能大于i的，因为遍历时j==i时就跳出循环了，所以如果j>i,说明i不合法，是一个小于1的值
	{
		printf("序号不合法，没有此元素\n");
		return;
	}
	*e = p->data;  //执行到这里说明j==i，找到了元素，所以赋值
}

//链表的插入
void InsertList(LinkList L,int i, Lnode* e)  //e为要插入的结点地址
{
	Lnode* p = L;  //考虑到插入的结点可能会插入到第一个位置成为首元结点，所以p从头结点开始
	int j = 0;    
	//要插入第i个位置，所以要先找到第i-1个元素
	while (p && i-1 > j)  
	{
		p = p->next, j++;
	}
	if (!p && j > i-1)  
	{
		printf("没有这个元素!\n");
		return;
	}
	e->next = p->next;  //把这个新结点的指针域指向原来结点的下一个结点地址，这个地址存在原来结点的指针域中
	p->next = e;      //插入一个新结点后，原来结点的指针域也要更换内容，更换为新结点的地址，即e
}
int main()
{
	LinkList L;

	return 0;
}