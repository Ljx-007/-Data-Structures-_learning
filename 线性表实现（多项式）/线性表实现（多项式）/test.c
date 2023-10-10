#define _CRT_SECURE_NO_WARNINGS 1
#include"function.h"
void menu()
{
	printf("********多项式线性表*********\n");
	printf("********1.增加一项***********\n");
	printf("********2.删除一项***********\n");
	printf("********3.查找一项***********\n");
	printf("********4.修改一项***********\n");
	printf("********5.显示    ***********\n");
	printf("********6.排序多项式*********\n");
	printf("********7.清空线性表*********\n");
	printf("********0.关闭    ***********\n");
	printf("*****************************\n");
}
int main()
{
	SqList L;
	int answer;
	InitList(&L); //初始化线性表L
	do
	{
		menu();
		printf("请选择：");
		scanf("%d", &answer);
		switch (answer)
		{
		case ADD:
			Add(&L);
			break;
		case DEL:
			Del(&L);
			break;
		case SEARCH:
			GetElem(&L);
			break;
		case MODIFY:
			Modify(&L);
			break;
		case SHOW:
			show(&L);
			break;
		case CLEAR:
			ClearList(&L);
			break;
		case SORT:
			sort(&L);
			break;
		case EXIT:
			save(&L);
			DeletList(&L);
			break;
		default:
			printf("输入错误，请重新输入：\n");
			break;
		}
	} while (answer);
	//将y=10+3x^2-5x^5+x^6+4x^9 存放到线性表中
	//按照我们的定义只需存放指数和系数即可
	return 0;
}