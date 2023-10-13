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

//链表的删除
void DeleteList(LinkList L, int i)
{
	Lnode* p = L;
	Lnode* q;
	int j = 0;
	//找到第i-1个元素
	//while(p&&i-1>j)
	//p->next为空说明p已经是最后一个结点了
	while (p->next && i - 1 > j)  //这里的p要改为p->next，因为如果不修改像注释一样的话，当输入的i大于链表长度时，p就会一直遍历直到p==NULL
	{                           //如果语句都不修改为p->next，那么，当p遍历到p==NULL，也会进入if语句判断后打印没有此元素，看起来修补修改都并没有关系
		                        //那为什么要改为p->next呢,因为不改的话，如果i=链表长+1，那么当j=链表长时，p指向最后一个结点，此时i-1==j,跳出循环
		                   //而p也没有指向空指针，没有进入if语句，开始执行删除代码，此时p->next->next时无意义的，因为p指向最后一个结点，其指针域为空
		                 //空指针没有指针域next了，所以执行到p->next->next时就会报错
		p = p->next;
		j++;
	}
	//if(!p||j>i-1)
	if (!(p->next) || j > i - 1)
	{
		printf("没有此元素！\n");
		return;
	}
	//要把第i个元素删除，就要让第i-1个结点的指针域指向第i+1个结点的地址
	//p是第i-1个结点的地址，p->next是第i个结点的地址，p->next->next是第i+1个结点的地址
	q = p->next; //删除第i个结点还要把第i个结点的内存给释放了，用q来存第i个结点的地址，以免下一行代码更改p后找不到第i个结点的地址了
	p->next = p->next->next;
	free(q), q = NULL;
}

//链表的查找
Lnode* Located(LinkList L, Stu e)
{
	Lnode* p = L;
	while (p && strcmp(p->data.name,e.name)!=0&&strcmp(p->data.num,e.num)!=0&&p->data.score!=e.score) 
		//这里p->data 和e 都是结构体，结构体不能简单的用==或者!=号来判断其是否相等或者不相等
		                //因为结构体中含有成员变量，想要判断两结构体是否相等只能判断其成员是否各自相等
		//此处while循环判断当结构体内三个成员变量都不相等时，才进入循环
	{
		p = p->next;
	}
	return p;
}

//创建链表，头插法
//将已有的结点从后到前一个一个插入链表的头部（头结点之后）来创建链表
void CreatList(LinkList L)  //要插入n个元素
{
	int n,ret;
	char arr[100] = { 0 };
	printf("要插入的元素个数:");
	again:
	ret=scanf("%d", &n);
	while (ret != 1)
	{
		while (gets_s(arr,100) != (char*)'\n')  //如果输入的不是数字，读取缓冲区输入的字符，并重新输入
		{
			printf("请输入数字：");
			goto again;
		}
	}
	L = (LinkList)malloc(sizeof(Lnode)); //创建一个头结点
	L->next = NULL;  //头结点的指针域置空，以便第一个插入的元素的指针域为空，成为最后一个元素
	for (int i = 0; i < n; i++)
	{
		Lnode* p = (Lnode*)malloc(sizeof(Lnode));
		//给创建的p赋值，往链表里输入内容
		//...
		printf("姓名：");
		scanf("%s", p->data.name);
		printf("学号：");
		scanf("%s", p->data.num);
		printf("成绩：");
		scanf("%d", &(p->data.score));
		p->next = L->next;   //因为是头插法，所以p要插入到头结点后的第一个位置中，所以p的指针域要指向原本L后的元素，让原本L后的元素在p后
		L->next = p;  //p后接了元素后，前面要接上L，所以L的指针域要改为p
	}
}

//链表的创建，尾插法
void CreatList2(LinkList L)
{
	int n, ret;
	char arr[100] = { 0 };
	printf("要插入的元素个数:");
again:
	ret = scanf("%d", &n);
	while (ret != 1)
	{
		while (gets_s(arr, 100) != (char*)'\n')  //如果输入的不是数字，读取缓冲区输入的字符，并重新输入
		{
			printf("请输入数字：");
			goto again;
		}
	}
	L = (LinkList)malloc(sizeof(Lnode)); //创建一个头结点
	L->next = NULL;
	Lnode* r = L; //创建一个尾指针,一直指向最后一个结点
	for (int i = 0; i < n; i++)
	{
		Lnode* p = (Lnode*)malloc(sizeof(Lnode));
		//输入数据
		//...
		p->next = NULL;  //因为创建的p是从链表的尾部接上，p是最后一个结点，所以p的指针域要先置空，
		p = r->next;  //p成了尾结点，r就变成了p前面一个结点，把这两个结点连接起来，所以r的指针域要指向p
		r = p;  //p结点连接上了后，尾指针r就要变成尾结点了，所以让r=p，因为p也是尾结点
	}
}

//循环链表
//循环链表就是把单链表里的尾结点的指针域由NULL改为头指针
//循环链表一般设立尾指针不设立头指针，尾指针处理起链表来更快捷
int main()
{
	LinkList L = { 0 };
	CreatList(L);
	return 0;
}