#define _CRT_SECURE_NO_WARNINGS 1
#include"function.h"
void check_size(SqList* pL)
{
	if (pL->len == pL->capacity)
	{
		Exp_Coe* ptr = (Exp_Coe*)realloc(pL->data, (pL->capacity + 3) * sizeof(Exp_Coe));
		if (!ptr)
		{
			perror("realloc fail");
			return;
		}
		pL->data = ptr;
		pL->capacity += 3;
#ifdef DEBUG
		printf("扩容成功！\n");
#endif
	}
}
void Load(SqList* pL)
{
	Exp_Coe tmp = { 0 };
	FILE* pfread = fopen("多项式记录表.txt", "rb");
	if (!pfread)
	{
		perror("Load fail ");
		return;
	}
	while (fread(&tmp, sizeof(Exp_Coe), 1, pfread))
	{
		check_size(pL);
		pL->data[pL->len] = tmp;
		pL->len++;
	}
}
int InitList(SqList* pL)
{
	pL->data = (Exp_Coe*)malloc(sizeof(Exp_Coe) * 3);
	if (!(pL->data))
	{
		perror("creat data fail");
		return -1;
	}
	pL->len = 0;
	pL->capacity = INIT_CAP;
	Load(pL);
	return 0;
}
void DeletList(SqList* pL)  //销毁线性表
{
	free(pL->data), pL->data = NULL;
}
void ClearList(SqList* pL)  //清空线性表
{
	char c;
	int ret;
	while (c = getchar() != '\n')
	{
		;
	}
	printf("你确定要清空线性表吗？(y/n):");
	again:
	ret=scanf("%c", &c);
	while (ret != 1)
	{
		while (getchar() != '\n'); //如果输入的是字母或者标点符号等字符，那么就先清空缓存区，再输入
		{
			//_flushall();  //也可以使用_flushall清除缓冲区，但可能会有危险，慎用
			printf("请输入正确的符号：");
			ret = scanf("%c", &c);
		}
	}
	if (c == 'y')
		pL->len = 0;
	else if (c == 'n')
		return;
	else
	{
		while (getchar() != '\n')
		{
			;
		}
		printf("输入错误！请重新输入：\n");
		goto again;
	}
	printf("清空成功！\n");
}
void GetElem(const SqList* pL) //获取线性表中第num个元素
{ 
	if (pL->len == 0)
	{
		printf("没有多项式!\n");
	}
	else
	{
		printf("请输入要查找元素的序号：");
		int num = check_num(pL);
		printf("e:%f c:%f \n", pL->data[num - 1].e, pL->data[num - 1].c);
	}
}
void Add(SqList* pL)
{
	int ret;
	check_size(pL);
	printf("请输入多项式的指数和系数\n");
	ret=scanf("%f%f", &(pL->data[pL->len].e), &(pL->data[pL->len].c)); //scanf返回的是成功输入数据的个数，类似的，printf返回的是输出成功的个数
	while (ret != 2)  //此处scanf输入两个数据，如果输入成功则返回2，如果不成功ret就不等于2，进入循环
	{
		while (getchar() != '\n'); //如果输入的是字母或者标点符号等字符，那么就先清空缓存区，再输入
		printf("请输入数字：");
		ret = scanf("%f%f", &(pL->data[pL->len].e), &(pL->data[pL->len].c)); 

	}
	pL->len++;
	for (int i = 0; i < pL->len - 1; i++)
	{
		if (pL->data[pL->len-1].e == pL->data[i].e)
		{
			pL->data[i].c = pL->data[pL->len-1].c + pL->data[i].c;
			pL->len--;
			if (pL->data[i].c == 0)
			{
				for (int j = i; j < pL->len; j++)
				{
					pL->data[j] = pL->data[j+1];
				}
				pL->len--;
			}
		}
	}
	printf("添加完成！\n");
}
void show(const SqList* pL)
{
	Exp_Coe* tmp = pL->data;
	for (int i = 0; i < pL->len+1; i++)
	{
		printf("%d	", i);
	}
	printf("\n");
	printf("e:	");
	for (int i = 0; i < pL->len; i++)
	{
		printf("%-.2f	", tmp->e);
		tmp++;
	}
	tmp = pL->data;
	printf("\n");
	printf("c:	");
	for (int i = 0; i < pL->len; i++)
	{ 
		printf("%-.2f	", tmp->c);
		tmp++;
	}
	printf("\n");
}
void Del(SqList* pL)
{
	if (pL->len == 0)
		printf("没有多项式需要删除\n");
	else
	{
		printf("请输入要删除元素的序号：");
		int num = check_num(pL);
		for (int j = num; j < pL->len; j++)
		{
			pL->data[j - 1] = pL->data[j];
		}
		pL->len--;
		printf("删除成功！\n");
	}
}
void Modify(SqList* pL)
{
	if (pL->len == 0)
	{
		printf("没有多项式!\n");
	}
	else
	{
		printf("请输入要修改元素的序号：");
		int num = check_num(pL);
		printf("请输入修改后的项的指数和系数：");
		scanf("%f%f", &(pL->data[num - 1].e), &(pL->data[num - 1].c));
		printf("修改完成！\n");
		for (int i = 0; i < pL->len; i++)
		{
			if (i == num - 1)
				continue;
			else
			{
				if (pL->data[num - 1].e == pL->data[i].e)
				{
					pL->data[MIN(num - 1, i)].c = pL->data[num - 1].c + pL->data[i].c;
					for (int j = MAX(num - 1, i); j < pL->len; j++)
					{
						pL->data[j] = pL->data[j + 1];
					}
					pL->len--;
					if (pL->data[MIN(num - 1, i)].c == 0)
					{
						for (int j = MIN(num - 1, i); j < pL->len; j++)
						{
							pL->data[j] = pL->data[j + 1];
						}
						pL->len--;
					}
				}
			}
		}
	}
}
int check_num(SqList* pL)
{
	int num,ret;
again:
	ret=scanf("%d", &num);
	while (ret != 1)
	{
		while (getchar() != '\n'); //如果输入的是字母或者标点符号等字符，那么就先清空缓存区，再输入
		{
			printf("请输入数字：");
			ret = scanf("%d", &num);
		}
	}
	if (num < 1)
	{
		printf("请输入正确的序号：\n");
		goto again;
	}
	if (num > pL->len)
	{
		printf("没有这么多项！请重新输入：\n");
		goto again;
	}
	return num;
}
void save(SqList* pL)
{
	FILE* pfwrite=fopen("多项式记录表.txt", "wb+");
	if (!pfwrite)
	{
		perror("Write  Fail");
		return;
	}
	fwrite(pL->data, sizeof(Exp_Coe), pL->len, pfwrite);
	fclose(pfwrite), pfwrite = NULL;
	printf("保存成功!\n");
}
int cmp(const void* x, const void* y)
{
	if (((Exp_Coe*)x)->e >((Exp_Coe*)y)->e)
		return 1;
	else if (((Exp_Coe*)x)->e == ((Exp_Coe*)y)->e)    //函数返回int型，如果直接返回两数相减的结果，float型会被强制转换为int型，可能会丢失数据
		return 0;
	else
		return -1;
}
void sort(SqList* pL)
{
	if (pL->len == 0)
		printf("没有多项式要排序\n");
	else
	{
		qsort(pL->data, pL->len, sizeof(pL->data[0]), cmp);
		printf("排序成功！\n");
	}
}