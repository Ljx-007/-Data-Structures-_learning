#define _CRT_SECURE_NO_WARNINGS 1
#include"function.h"
int main()
{
	SqList L;
	char c;
	InitList(&L); //��ʼ�����Ա�L
	//��y=10+3x^2-5x^5+x^6+4x^9 ��ŵ����Ա���
	//�������ǵĶ���ֻ����ָ����ϵ������
	Add(&L);
	while (1)
	{
		printf("��Ҫ��Ӷ���ʽ�𣿣�y/n����");
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
			printf("����������������룺");
	}
	show(&L);
	GetElem(&L, 2);
	return 0;
}