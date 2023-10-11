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
		printf("���ݳɹ���\n");
#endif
	}
}
void Load(SqList* pL)
{
	Exp_Coe tmp = { 0 };
	FILE* pfread = fopen("����ʽ��¼��.txt", "rb");
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
void DeletList(SqList* pL)  //�������Ա�
{
	free(pL->data), pL->data = NULL;
}
void ClearList(SqList* pL)  //������Ա�
{
	char c;
	int ret;
	while (c = getchar() != '\n')
	{
		;
	}
	printf("��ȷ��Ҫ������Ա���(y/n):");
	again:
	ret=scanf("%c", &c);
	while (ret != 1)
	{
		while (getchar() != '\n'); //������������ĸ���߱����ŵ��ַ�����ô������ջ�������������
		{
			//_flushall();  //Ҳ����ʹ��_flushall����������������ܻ���Σ�գ�����
			printf("��������ȷ�ķ��ţ�");
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
		printf("����������������룺\n");
		goto again;
	}
	printf("��ճɹ���\n");
}
void GetElem(const SqList* pL) //��ȡ���Ա��е�num��Ԫ��
{ 
	if (pL->len == 0)
	{
		printf("û�ж���ʽ!\n");
	}
	else
	{
		printf("������Ҫ����Ԫ�ص���ţ�");
		int num = check_num(pL);
		printf("e:%f c:%f \n", pL->data[num - 1].e, pL->data[num - 1].c);
	}
}
void Add(SqList* pL)
{
	int ret;
	check_size(pL);
	printf("���������ʽ��ָ����ϵ��\n");
	ret=scanf("%f%f", &(pL->data[pL->len].e), &(pL->data[pL->len].c)); //scanf���ص��ǳɹ��������ݵĸ��������Ƶģ�printf���ص�������ɹ��ĸ���
	while (ret != 2)  //�˴�scanf�����������ݣ��������ɹ��򷵻�2��������ɹ�ret�Ͳ�����2������ѭ��
	{
		while (getchar() != '\n'); //������������ĸ���߱����ŵ��ַ�����ô������ջ�������������
		printf("���������֣�");
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
	printf("�����ɣ�\n");
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
		printf("û�ж���ʽ��Ҫɾ��\n");
	else
	{
		printf("������Ҫɾ��Ԫ�ص���ţ�");
		int num = check_num(pL);
		for (int j = num; j < pL->len; j++)
		{
			pL->data[j - 1] = pL->data[j];
		}
		pL->len--;
		printf("ɾ���ɹ���\n");
	}
}
void Modify(SqList* pL)
{
	if (pL->len == 0)
	{
		printf("û�ж���ʽ!\n");
	}
	else
	{
		printf("������Ҫ�޸�Ԫ�ص���ţ�");
		int num = check_num(pL);
		printf("�������޸ĺ�����ָ����ϵ����");
		scanf("%f%f", &(pL->data[num - 1].e), &(pL->data[num - 1].c));
		printf("�޸���ɣ�\n");
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
		while (getchar() != '\n'); //������������ĸ���߱����ŵ��ַ�����ô������ջ�������������
		{
			printf("���������֣�");
			ret = scanf("%d", &num);
		}
	}
	if (num < 1)
	{
		printf("��������ȷ����ţ�\n");
		goto again;
	}
	if (num > pL->len)
	{
		printf("û����ô������������룺\n");
		goto again;
	}
	return num;
}
void save(SqList* pL)
{
	FILE* pfwrite=fopen("����ʽ��¼��.txt", "wb+");
	if (!pfwrite)
	{
		perror("Write  Fail");
		return;
	}
	fwrite(pL->data, sizeof(Exp_Coe), pL->len, pfwrite);
	fclose(pfwrite), pfwrite = NULL;
	printf("����ɹ�!\n");
}
int cmp(const void* x, const void* y)
{
	if (((Exp_Coe*)x)->e >((Exp_Coe*)y)->e)
		return 1;
	else if (((Exp_Coe*)x)->e == ((Exp_Coe*)y)->e)    //��������int�ͣ����ֱ�ӷ�����������Ľ����float�ͻᱻǿ��ת��Ϊint�ͣ����ܻᶪʧ����
		return 0;
	else
		return -1;
}
void sort(SqList* pL)
{
	if (pL->len == 0)
		printf("û�ж���ʽҪ����\n");
	else
	{
		qsort(pL->data, pL->len, sizeof(pL->data[0]), cmp);
		printf("����ɹ���\n");
	}
}