#define _CRT_SECURE_NO_WARNINGS 1
#include"function.h"
void menu()
{
	printf("********����ʽ���Ա�*********\n");
	printf("********1.����һ��***********\n");
	printf("********2.ɾ��һ��***********\n");
	printf("********3.����һ��***********\n");
	printf("********4.�޸�һ��***********\n");
	printf("********5.��ʾ    ***********\n");
	printf("********6.�������ʽ*********\n");
	printf("********7.������Ա�*********\n");
	printf("********0.�ر�    ***********\n");
	printf("*****************************\n");
}
int main()
{
	SqList L;
	int answer;
	InitList(&L); //��ʼ�����Ա�L
	do
	{
		menu();
		printf("��ѡ��");
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
			printf("����������������룺\n");
			break;
		}
	} while (answer);
	//��y=10+3x^2-5x^5+x^6+4x^9 ��ŵ����Ա���
	//�������ǵĶ���ֻ����ָ����ϵ������
	return 0;
}