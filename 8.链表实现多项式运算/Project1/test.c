#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
typedef struct Pnode
{
	float coef;  //系数
	int exp;  //指数
	struct Pnode* next;
}Pnode,*LinkPoly;
Pnode* CreatPoly()
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
	LinkPoly L = (Pnode*)malloc(sizeof(Pnode));
	L->next = NULL;
	for(int i=0;i<n;i++)
	{
		Pnode* p = (Pnode*)malloc(sizeof(Pnode));
		printf("请输入该项的指数和系数：");
		scanf("%d%f", &(p->exp), &(p->coef));
		//按指数由小到大的顺序排结点
		Pnode* pre = L;       //因为我们要给所创建的链表排序，要比较两个结点的指数大小，所以可能存在插入的操作
		                     //链表的插入操作需要用到一前一后两个指针，所以我们要创建一个q指针和q的前驱指针pre
		Pnode* q =pre->next;   //q用来遍历链表，比较新创建的结点指数和旧结点的指数
		//因为我们要用q来找到是否存在一个结点的指数大于新结点的指数，所以q就要从头到尾遍历，直到找到一个结点的指数大于新结点的指数或者一直找到链表的尾部都没有
		while (q&&q->exp<p->exp) 
		{
			//q和p的指数比较，若指数没有大于q的，就往后找
			pre = q; //pre是q的前驱指针，始终指向p的前一个结点
			q = q->next; //p一个一个的往后移
		}
		//出了循环有两种可能：
		//1.存在一个结点的指数大于新结点
		//2.循环遍历完了，q为NULL退出循环，即不存在一个结点的指数大于新结点	，不大于就有可能等于或者小于，所以还要再分情况
		if (q&&q->exp == p->exp)
		{
			q->coef = q->coef + p->coef;  //如果指数相等，那么把他们的系数相加赋回给p结点的系数，并把新结点的内存释放
			if (q->coef == 0)
			{      //如果系数相加为0，那么把该结点从链表中删除
				pre->next = q->next;  //把前驱和后继连在一起，q直接删掉
				free(q), q = NULL;
			}
			free(p), p = NULL;
		}
		else
		{
			p->next = q;   //如果是第一种情况，那么新结点的后继指针应该指向指数大于它的结点q，q的前一个结点pre的后继指针指向p
			pre->next = p;  //如果是第二种情况，此时q是最后一个结点的指针域。p应该在最后一个结点位置，那么p的指针域应该为空，所以p的指针域指向了q
		}                //q的前驱结点pre此时也指向了原来的最后一个结点，最后一个结点（新结点）就应该在原来的最后一个结点的后面，故pre->=p             
	}
	return L;
}

//把两个多项式相加（链表相加）
Pnode* Add(LinkPoly La,LinkPoly Lb)
{
	Pnode* pa = La->next;  //创建pa，pb来遍历链表a，b
	Pnode* pb = Lb->next;
	LinkPoly Lc = La; //创建链表Lc指向La，并把两个链表相加的结果放在链表Lc中
	Pnode* pc = Lc;
	while (pa && pb)
	{
		if (pa->exp < pb->exp)  //如果表a中的结点的指数小于表b中的结点的指数
		{
			pc->next = pa; //把表a结点的内容存放到表c中
			pa = pa->next; //同时表a和表c都往后访问一结点
			pc = pc->next;
		}
		else if (pa->exp > pb->exp)  //相反同理
		{
			pc->next = pb;
			pb = pb->next;
			pc = pc->next;
		}
		else  //当两结点指数相等时
		{   //先把两结点的系数相加放在表a的结点中
			pa->coef = pa->coef + pb->coef;  
			if (pa->coef == 0)  //如果系数为0，表a，b同时向后访问结点
			{                 //并把原来结点的空间释放
				Pnode* fa = pa;
				Pnode* fb = pb;
				pa = pa->next, pb = pb->next;
				free(fa), fa = NULL;
				free(fb), fb = NULL;
			}
			else
			{  //如果不为0
				pc->next = pa;  //把刚才放在表a的数据放在表c中
				Pnode* fb = pb;  //同时表b结点的数据已经加到表a去了，所以这个b结点没用了，要释放空间
				pb = pb->next;  //存放好数据后，表a，b，c同时向后访问一个结点
				pa = pa->next;
				pc = pc->next;
				free(fb), fb = NULL;
			}
		}
	}
	pc->next = pa ? pa : pb;  //如果表a，b其中一个遍历为空，那么另外一表剩下的结点接在表c后
	return Lc;
}
#define PRINTF(X) printf("创建多项式"#X"\n")
int main()
{
	PRINTF(A);
	LinkPoly La = CreatPoly();
	PRINTF(B);
	LinkPoly Lb = CreatPoly();
	LinkPoly Lc = Add(La, Lb);
	Pnode* pc = Lc->next;
	while (pc)
	{
		printf("系数：%f  指数：%d\n", pc->coef, pc->exp);
		pc = pc->next;
	}
	return 0;
}