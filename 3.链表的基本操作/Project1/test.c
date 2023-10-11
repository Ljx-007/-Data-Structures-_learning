#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//链表的实现由结构体完成，链表由n个任意存储单元的数据结点组成，结点分为两个域，数据域和指针域。
//数据域用来存储数据，指针与用来存储下一个数据的地址
//链表一般增加一个头结点，存储第一个元素的结点叫首元结点，头结点不是首元结点。
//头结点存储首元结点的地址，头结点的数据域可以为空，也可以存储链表长度，头结点不算入链表长度

//设计一个存储学生学号，姓名，成绩的链表
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
}Lnode,*LinkList;   //这里的LinkList可不是创建一个struct Lnode的指针变量，而是将struct Lnode*改名为LinkList
                   //通常创建链表时用LinkList，创建结点地址时用struct Lnode*，好区分链表与结点。

void InitList(LinkList L)  //创建一个空表
{
	L=(LinkList)malloc(sizeof(Lnode)); //创建链表（创建头结点）
	L->next = NULL;//将头结点指针域置空
}
//单链表的销毁
void DestroyList(Lnode* L)
{
	//销毁链表需要用到两个指针，链表的销毁需要逐个销毁，需要多创建一个临时的指针变量p
	//因为如果不多用一个指针p，那么直接把L销毁了，只是把其中一个结点销毁了而已，剩下的结点并没有销毁
	//所以我们要用p来知道下一个结点的位置，然后让L指向下一个节点的位置，再把p指向的结点销毁掉，再把L赋给p
	//以此类推，逐个销毁结点,直到L为空指针，循环结束
	Lnode* p;
	while (L)
	{
		p = L;
		L = L->next; //注意，最后一个结点是会被销毁的，因为L先指向最后一个结点的地址后，倒数第二个结点才会被销毁，此时L并不是空值
		//于是进入下一次循环，下一次循环L赋值给p，p也指向最后一个结点的地址，此时L指向最后一个结点的指针域，最后一个结点的指针域是空指针
		//L指向空指针后，p，也就是最后一个结点的地址被销毁了，L已经是NULL，于是跳出循环
		free(p),p = NULL;
	}
}

//单链表的清空(保留头结点，头指针)--  除了头结点外都销毁掉
//因为只是清空链表，还要保留头结点，头指针，所以需要有一个指针变量来一直存储头结点的地址
//所以头结点指针 L 不能动，那谁来清空呢？所以需要一个变量p来指向首元结点，那么销毁链表至少需要两个指针，只有一个变量p是不够的
//所以要在创建一个变量q，p和q相互配合，才能做到销毁结点
void ClearList(LinkList L)
{
	Lnode *p, *q;
	p = L->next;
	while (p)  //p负责销毁，q负责寻找下一个结点
	{
		q = p->next;  //q指向下一个结点
		free(p);   
		p = q;   //销毁p指向的结点后，p再指向下一个结点
	}
	L->next = NULL;  //循环结束后，除头结点外所有结点都清空了，那么头结点的指针域就要置为空置
}

//计算链表长度
int LengthList(LinkList L)
{
	int count=0;
	Lnode* p;
	p = L->next;//如果链表为空，那么头结点L的指针域就为空，所以p=NULL，不进入循环，count不++是0，符合逻辑
	while(p)   
	{
		count++;
		p = p->next;
	}
	return count;
}
int main()
{
	LinkList L = { 0 };
	InitList(L); //L的类型本来就是一个指针，是一个结点类型的指针，所以传参的时候不用再&L
	DestroyList(L);
	return 0;
}