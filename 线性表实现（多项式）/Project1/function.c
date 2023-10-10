#define _CRT_SECURE_NO_WARNINGS 1
#include"function.h"
int InitList(SqList* pL)
{
	pL->data = (Exp_Coe*)malloc(sizeof(Exp_Coe) * 10);
	if (!(pL->data))
	{
		perror("creat data fail");
		return -1;
	}
	pL->len = 0;
	return 0;
}
void DeletList(SqList* pL)  //销毁线性表
{
	free(pL->data), pL->data = NULL;
}
void ClearList(SqList* pL)  //清空线性表
{
	pL->len = 0;
}
void GetElem(const SqList* pL,int num) //获取线性表中第num个元素
{
	printf("e:%d c:%d ", pL->data[num-1].e, pL->data[num-1].c);
}
void Add(SqList* pL)
{
	printf("请输入多项式的指数和系数\n");
	scanf("%d%d", &(pL->data[pL->len].e), &(pL->data[pL->len].c));
	printf("输入完成！\n");
	pL->len++;
}
void show(SqList* pL)
{
	Exp_Coe* tmp = pL->data;
	for (int i = 0; i < pL->len+1; i++)
	{
		printf("%d  ", i);
	}
	printf("\n");
	printf("e: ");
	for (int i = 0; i < pL->len; i++)
	{
		printf("%-2d ", tmp->e);
		tmp++;
	}
	tmp = pL->data;
	printf("\n");
	printf("c: ");
	for (int i = 0; i < pL->len; i++)
	{ 
		printf("%-2d ", tmp->c);
		tmp++;
	}
	printf("\n");
}