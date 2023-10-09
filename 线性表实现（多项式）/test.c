#define _CRT_SECURE_NO_WARNINGS 1
#include"function.h"
int main()
{
	SqList L;
	char c;
	InitList(&L); //初始化线性表L
	//将y=10+3x^2-5x^5+x^6+4x^9 存放到线性表中
	//按照我们的定义只需存放指数和系数即可
	Add(&L);
	while (1)
	{
		printf("还要添加多项式吗？（y/n）：");
		while ((c = getchar()) != '\n') { ; }
		c = getchar();
		if (c == 'y')
		{
			Add(&L);
			continue;
		}
		else if (c == 'n')
			break;
		else
			printf("输入错误，请重新输入：");
	}
	show(&L);
	GetElem(&L, 2);
	return 0;
}