#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
typedef struct Lnode
{
	int data;
	struct Lnode* next;
}Lnode,*LinkList;
Lnode* Creat()
{
	int n, ret;
	char str[1001];
	printf("����Ҫ�����Ķ���ʽ������");
again:
	ret = scanf("%d", &n);
	if (!ret)
	{
		while (gets_s(str, 1000))
		{
			printf("��������ȷ������:");
			goto again;
		}
	}
	LinkList L = (Lnode*)malloc(sizeof(Lnode));
	L->next = NULL;
	for (int i = 0; i < n; i++)
	{
		Lnode* p = (Lnode*)malloc(sizeof(Lnode));
		printf("������ý������ݣ�");
		scanf("%d", &(p->data));
		//��data��С�����˳���Ž��
		Lnode* pre = L;       //��Ϊ����Ҫ������������������Ҫ�Ƚ���������ָ����С�����Կ��ܴ��ڲ���Ĳ���
		//����Ĳ��������Ҫ�õ�һǰһ������ָ�룬��������Ҫ����һ��qָ���q��ǰ��ָ��pre
		Lnode* q = pre->next;   //q�������������Ƚ��´����Ľ��ָ���;ɽ���ָ��
		//��Ϊ����Ҫ��q���ҵ��Ƿ����һ������ָ�������½���ָ��������q��Ҫ��ͷ��β������ֱ���ҵ�һ������ָ�������½���ָ������һֱ�ҵ������β����û��
		while (q && q->data <= p->data)
		{
			pre = q;
			q = q->next;
		}
		p->next = q;
		pre->next = p;
	}
	return L;
}
//�㷨�����
//1.��������������������ϲ�Ϊһ����������������Ҫ����������ʹ��ԭ����������Ĵ洢�ռ䣬������ռ�������Ĵ洢�ռ䡣���в��������ظ�������
LinkList MergeList1(LinkList La, LinkList Lb)
{
	LinkList Lc = La;
	Lnode* pa = La->next;
	Lnode* pb = Lb->next;
	Lnode* pc = Lc;
	while (pa && pb)
	{
		if (pa->data < pb->data)
		{
			pc->next = pa;
			pa = pa->next;
			pc = pc->next;
		}
		else if (pa->data == pb->data)
		{
			pc->next = pa;
			Lnode* fb = pb;
			pa = pa->next;
			pb = pb->next;
			pc = pc->next;
			free(fb), fb = NULL;
		}
		else
		{
			pc->next = pb;
			pc = pc->next; 
			pb = pb->next;
		}
	}
	pc->next = pa ? pa : pb;
	free(Lb), Lb = NULL;
	return Lc;
}

//2.�������ǵݼ�����������ϲ�Ϊһ���ǵ�������������Ҫ����������ʹ��ԭ����������Ĵ洢�ռ䣬������ռ�������Ĵ洢�ռ䡣�����������ظ�������
LinkList MergeList2(LinkList La, LinkList Lb)
{
	LinkList Lc = La;
	Lnode* pa = La->next;
	Lnode* pb = Lb->next;
	Lnode* pc = Lc;
	Lnode* q;
	Lc->next = NULL;
	while (pa || pb)  //����a��b���ǿձ��˲��˳�ѭ��
	{
		//qΪ���Ǵӱ�a���߱�b��ժȡҪ�����c��Ԫ��
		if (!pa)  //�����a�ǿձ���ô�Ͱѱ�b��Ԫ�ط����c
		{
			q = pb;
			pb = pb->next;
		}
		else if (!pb)  //�����b�ǿձ���ô�Ͱѱ�aʣ�µĵ�Ԫ�ط����c
		{
			q = pa;
			pa = pa->next;
		}
		else if (pa->data < pb->data)  //�����a��Ԫ�ش��ڱ�b��Ԫ�أ���ôժȡ��a��Ԫ�أ������b��ͬʱ��a������
		{
			q = pa;
			pa = pa->next;
		}
		else   //�����b��Ԫ�ش��ڵ��ڱ�a��Ԫ�أ���ôժȡ��b��Ԫ�أ������a��ͬʱ��b������
		{
			q = pb;
			pb = pb->next;
		}
		q->next = Lc->next;  //����ͷ�巨��������Ԫ��˳���ǵ����������÷���Ԫ�شӴ�С�Ĺ涨
		Lc->next = q;
		free(Lb), Lb = NULL;
	}
	return Lc;
}

//3.��֪��������A��B�ֱ��ʾ�������ϣ���Ԫ�ص������С������һ���㷨���������A��B�Ľ������������A������
Lnode* Jiao(LinkList La, LinkList Lb)
{
	LinkList Lc = La;
	Lnode* pa = La->next;
	Lnode* pb = Lb->next;
	Lnode* pc = Lc;
	while (pa && pb)
	{
		if (pa->data == pb->data)
		{  //���������ȣ����ŵ���a�У�pa��pb������һ�����
			pc->next = pa;
			pa = pa->next;
			pc = pc->next;
			pb = pb->next;
		}
		else if (pa->data < pb->data)    //��Ϊ�����ǵ����ģ������������������һ�����Ԫ��С����һ�����Ԫ�أ���Ҫ��С�ڵı������ʽ��
			                             //��Ϊ������ʵ�ֵԽ��Խ���п��ܻ������ȵ����
		{
			Lnode* fa = pa;
			pa = pa->next;
			free(fa), fa = NULL;
		}
		else
		{
			Lnode* fb = pb;
			pb = pb->next;
			free(fb), fb = NULL;
		}
	}
	//���꽻�����ͷŵ�ʣ�µĽ��Ŀռ�
	while (pa)
	{
		Lnode* fa = pa;
		pa = pa->next;
		free(pa), pa = NULL;
	}
	while (pb)
	{
		Lnode* fb = pb;
		pb = pb->next;
		free(pb), pb = NULL;
	}
	pc->next = NULL;  //�ѽ��������β���ÿգ���������
	free(Lb), Lb = NULL;
	return Lc;
}

//4.��֪����A,B��Ԫ�ص������У�������㷨�����������A,B�Ĳ����������A�г��ֶ�����B�г��ֵ�Ԫ�������ɵļ��ϣ�������ͬ������ʽ�洢
//  ͬʱ�Ƿ��ظü��ϵ�Ԫ�ظ���
int AdelB(LinkList* La, LinkList Lb)
{
	int n = 0;
	Lnode* pre = *La;
	Lnode* pa = (*La)->next;
	Lnode* pb = Lb->next;
	while (pa && pb)
	{
		if (pa->data == pb->data)
		{
			Lnode* fa = pa;
			pre->next = pa->next;
			pa = pa->next;
			free(fa), fa = NULL;
		}
		else if(pa->data>pb->data)
		{
			Lnode* fb = pb;
			pb = pb->next;
			free(fb), fb = NULL;
		}
		else
		{
			pre = pa;
			pa = pa->next;
			n++;
		}
	}
	//��b���˺�Ҫ�ѱ�aʣ�µ�Ԫ��Ҳ����
	while (pa)
	{
		pa = pa->next;
		n++;
	}
	//��b���Ԫ��ɾ��
	while (pb)
	{
		Lnode* fb = pb;
		pb = pb->next;
		free(fb), fb = NULL;
	}
	return n;
}

//5.����㷨��һ����ͷ���ĵ�����A�ֽ�Ϊ����������ͬ�ṹ������B��C������B��Ľ��ΪA����ֵС����Ľ�㣬��C��Ľ��ΪA����ֵ������Ľ��
// ������A�е�Ԫ��Ϊ����������Ҫ��B,C������A��Ľ�㣩
void DisCompose(LinkList* A,  LinkList* C)
{
	Lnode* pa = (*A)->next;
	Lnode* pre = *A;
	(*C)->next = NULL;
	Lnode* pc = *C;
	while (pa)
	{
		if (pa->data > 0)
		{
			Lnode* ha = pa;
			pre->next = pa->next;
			pa = pa->next;
			ha->next = pc->next;
			pc->next = ha;
			pc = pc->next;
		}
		else
		{
			pa = pa->next;
			pre = pre->next;
		}
	}
}
int main()
{
	LinkList La = Creat();
	//LinkList Lb = Creat();
	//LinkList Lc = MergeList2(La, Lb);
	//LinkList Lc = Jiao(La, Lb);
	//int n=AdelB(&La, Lb);
	LinkList C = (Lnode*)malloc(sizeof(Lnode));
	DisCompose(&La, &C);
	Lnode* pc = C->next;
	Lnode* pa = La->next;
	while (pa)
	{
		printf("%d ", pa->data);
		pa = pa->next;
	}
	printf("\n");
	while (pc)
	{
		printf("%d ", pc->data);
		pc = pc->next;
	}
	//printf("\n%d", n);
	return 0;
}