#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
typedef struct Pnode
{
	float coef;  //ϵ��
	int exp;  //ָ��
	struct Pnode* next;
}Pnode,*LinkPoly;
Pnode* CreatPoly()
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
	LinkPoly L = (Pnode*)malloc(sizeof(Pnode));
	L->next = NULL;
	for(int i=0;i<n;i++)
	{
		Pnode* p = (Pnode*)malloc(sizeof(Pnode));
		printf("����������ָ����ϵ����");
		scanf("%d%f", &(p->exp), &(p->coef));
		//��ָ����С�����˳���Ž��
		Pnode* pre = L;       //��Ϊ����Ҫ������������������Ҫ�Ƚ���������ָ����С�����Կ��ܴ��ڲ���Ĳ���
		                     //����Ĳ��������Ҫ�õ�һǰһ������ָ�룬��������Ҫ����һ��qָ���q��ǰ��ָ��pre
		Pnode* q =pre->next;   //q�������������Ƚ��´����Ľ��ָ���;ɽ���ָ��
		//��Ϊ����Ҫ��q���ҵ��Ƿ����һ������ָ�������½���ָ��������q��Ҫ��ͷ��β������ֱ���ҵ�һ������ָ�������½���ָ������һֱ�ҵ������β����û��
		while (q&&q->exp<p->exp) 
		{
			//q��p��ָ���Ƚϣ���ָ��û�д���q�ģ���������
			pre = q; //pre��q��ǰ��ָ�룬ʼ��ָ��p��ǰһ�����
			q = q->next; //pһ��һ����������
		}
		//����ѭ�������ֿ��ܣ�
		//1.����һ������ָ�������½��
		//2.ѭ���������ˣ�qΪNULL�˳�ѭ������������һ������ָ�������½��	�������ھ��п��ܵ��ڻ���С�ڣ����Ի�Ҫ�ٷ����
		if (q&&q->exp == p->exp)
		{
			q->coef = q->coef + p->coef;  //���ָ����ȣ���ô�����ǵ�ϵ����Ӹ��ظ�p����ϵ���������½����ڴ��ͷ�
			if (q->coef == 0)
			{      //���ϵ�����Ϊ0����ô�Ѹý���������ɾ��
				pre->next = q->next;  //��ǰ���ͺ������һ��qֱ��ɾ��
				free(q), q = NULL;
			}
			free(p), p = NULL;
		}
		else
		{
			p->next = q;   //����ǵ�һ���������ô�½��ĺ��ָ��Ӧ��ָ��ָ���������Ľ��q��q��ǰһ�����pre�ĺ��ָ��ָ��p
			pre->next = p;  //����ǵڶ����������ʱq�����һ������ָ����pӦ�������һ�����λ�ã���ôp��ָ����Ӧ��Ϊ�գ�����p��ָ����ָ����q
		}                //q��ǰ�����pre��ʱҲָ����ԭ�������һ����㣬���һ����㣨�½�㣩��Ӧ����ԭ�������һ�����ĺ��棬��pre->=p             
	}
	return L;
}

//����������ʽ��ӣ�������ӣ�
Pnode* Add(LinkPoly La,LinkPoly Lb)
{
	Pnode* pa = La->next;  //����pa��pb����������a��b
	Pnode* pb = Lb->next;
	LinkPoly Lc = La; //��������Lcָ��La����������������ӵĽ����������Lc��
	Pnode* pc = Lc;
	while (pa && pb)
	{
		if (pa->exp < pb->exp)  //�����a�еĽ���ָ��С�ڱ�b�еĽ���ָ��
		{
			pc->next = pa; //�ѱ�a�������ݴ�ŵ���c��
			pa = pa->next; //ͬʱ��a�ͱ�c���������һ���
			pc = pc->next;
		}
		else if (pa->exp > pb->exp)  //�෴ͬ��
		{
			pc->next = pb;
			pb = pb->next;
			pc = pc->next;
		}
		else  //�������ָ�����ʱ
		{   //�Ȱ�������ϵ����ӷ��ڱ�a�Ľ����
			pa->coef = pa->coef + pb->coef;  
			if (pa->coef == 0)  //���ϵ��Ϊ0����a��bͬʱ�����ʽ��
			{                 //����ԭ�����Ŀռ��ͷ�
				Pnode* fa = pa;
				Pnode* fb = pb;
				pa = pa->next, pb = pb->next;
				free(fa), fa = NULL;
				free(fb), fb = NULL;
			}
			else
			{  //�����Ϊ0
				pc->next = pa;  //�Ѹղŷ��ڱ�a�����ݷ��ڱ�c��
				Pnode* fb = pb;  //ͬʱ��b���������Ѿ��ӵ���aȥ�ˣ��������b���û���ˣ�Ҫ�ͷſռ�
				pb = pb->next;  //��ź����ݺ󣬱�a��b��cͬʱ������һ�����
				pa = pa->next;
				pc = pc->next;
				free(fb), fb = NULL;
			}
		}
	}
	pc->next = pa ? pa : pb;  //�����a��b����һ������Ϊ�գ���ô����һ��ʣ�µĽ����ڱ�c��
	return Lc;
}
#define PRINTF(X) printf("��������ʽ"#X"\n")
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
		printf("ϵ����%f  ָ����%d\n", pc->coef, pc->exp);
		pc = pc->next;
	}
	return 0;
}