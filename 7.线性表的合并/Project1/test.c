#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//�ϲ��������Ա�

//�����ĺϲ�--˳���ʵ��
//typedef struct SqList  //�ȶ���һ��˳���
//{
//	int *elem;
//	int len;
//}SqList;
//
////�ϲ�����˳���
//void MergeList(SqList La, SqList Lb, SqList* Lc)
//{
//	int* pa = La.elem;  //�ѱ�a����Ԫ�ص�ַ����ָ��pa
//	int* pb = Lb.elem;  //�ѱ�b����Ԫ�ص�ַ����ָ��pb
//	Lc->len = 0;
//	Lc->elem = (int*)malloc(sizeof(int)* (La.len+Lb.len));  //Ϊ��c���Ԫ�ص�λ�ÿ���һ�鳤��Ϊ��a��b֮�͵Ŀռ䣬��Ϊ����Ϊ a��bԪ�ز��ظ�����cԪ��Ϊa��b֮��
//	int* pc = Lc->elem; //�ѱ�c����Ԫ�ص�ַ����ָ��pc
//	//Ϊ�����жϱ�a��bʲôʱ��ȫ�������꣬��Ҫ����βָ��ָ����������һ��Ԫ��
//	int* pa_past = La.elem + La.len - 1;  
//	int* pb_past = Lb.elem + Lb.len - 1;
//	while (pa <= pa_past && pb <= pb_past)  //������δ�����β
//	{
//		//�Ƚ���������Ԫ�ؽ�С���Ǹ��������c
//		if (*pa < *pb)  
//			*pc++ = *pa++,Lc->len++;
//		//�������ϲ��ظ���Ԫ�أ���ô���ٶ��һ�������ж�
//		else if (*pb == *pa)
//		{
//			*pc++ = *pa++;  //�������ֵ��ͬ������ѡ�����е�һ��ֵ�����c
//			*pb++;   //����һ�����ָ��ҲҪ����
//			Lc->len++;
//		}
//		else
//			*pc++ = *pb++,Lc->len++;
//	}
//	//�������һ������β�ˣ���ô��һ�����Ԫ�ؾ�ȫ�Ž���c��
//	while (pa <= pa_past)  //Lb����β
//		*pc++ = *pa++, Lc->len++;
//	while (pb <= pb_past) //La����β
//		*pc++ = *pb++, Lc->len++;
//}
////���㷨ʱ�临�Ӷ�ΪO(La.len+Lb.len)   ������������a��bû��Ԫ���ظ����㷨���ִ�д���ΪLa.len+Lb.len��
////�ռ临�Ӷ�ΪO(La.len+Lb.len)
//
//int main()
//{
//	SqList La,Lb,Lc;
//	La.len = 0,Lb.len=0;
//	La.elem = (int*)malloc(sizeof(int) * 3);
//	for (int i = 0; i < 3; i++)
//	{
//		La.elem[i] = i+1;
//		La.len++;
//	}
//	Lb.elem = (int*)malloc(sizeof(int) * 5);
//	for (int i = 0; i < 5; i++)
//	{
//		Lb.elem[i] = i+2;
//		Lb.len++;
//	}
//	MergeList(La, Lb, &Lc);
//	for (int i = 0; i < Lc.len; i++)
//	{
//		printf("%d ", Lc.elem[i]);
//	}
//	return 0;
//}


//���������ĺϲ�
typedef struct Lnode
{
	int data;
	struct Lnode* next;
}Lnode, * LinkList;

//��ʼ������
Lnode* InitList()
{
	int n,ret;
	char str[1001];
	printf("Ҫ�����Ԫ�ظ�����");
	again:
	ret=scanf("%d", &n);
	if (ret != 1)
	{
		while (gets_s(str, 1000))
		{
			printf("���������֣�");
			goto again;
		}
	}
	//�ȴ���һ��ͷ���
	LinkList L = (Lnode*)malloc(sizeof(Lnode));
	L->next = NULL;
	Lnode* r = L;
	for (int i = 0; i < n; i++)
	{
		Lnode* p = (Lnode*)malloc(sizeof(Lnode));
		if (!p)
		{
			perror("creat Lnode error");
			return  - 1;
		}
		printf("�������������е����ݣ�int�ͣ���");
		again2:
		ret = scanf("%d", &(p->data));
		if (ret != 1)
		{
			while(gets_s(str,1000))  //��ȡ���������ַ�
			{
				printf("�밴Ҫ������:");
				goto again2;
			}		
		}
		p->next = NULL;
		r->next = p;
		r = p;
	}
	return L;
}

//�ϲ�����
void MergeList(LinkList La, LinkList Lb, LinkList Lc)   //�ϲ�����a��b�������ϲ������ݴ�ŵ���c��
{
	Lnode* pa = La->next;  //��paָ���a����Ԫ���
	Lnode* pb = Lb->next;	//pbָ���b����Ԫ���
	Lc = La;  //�ñ�c�Ĵӱ�a��ͷ��㿪ʼ��Ҳ����˵�ϲ��������ֱ�ӷ��ڱ�a�У���a���Ǳ�c
	Lnode* pc = Lc;   //pcָ���c��ͷ���
	while (pa && pb)   
	{
		if (pa->data > pb->data)
		{   //�����a�Ľ������ݴ��ڱ�b�Ľ�������
			pc->next = pb;  //��ôpcָ��Ľ�����һ��������pbָ��Ľ��
			pb = pb->next;  //pb�����һ�����
			pc = pc->next;  //pcҲ�����һ�����
		}
		//�ϲ������У�pcʼ��ָ���c�����һ�����
		else if (pa->data == pb->data)  //�������ϲ��ظ���Ԫ�أ��Ͷ��һ���ж�
		{
			pc->next = pb;  //��a,b��������ͬ��ѡ���a��b����һ�����ݷ����c���ɣ�����ѡ���b
			Lnode* px = pa; //���������c��pa��pb��Ҫָ����һ����㣬Ȼ������Ҫ��px����¼һ�±�a�����b��ͬ���ݵ��Ǹ����
			//��Ϊ�������¼��pa�ͻ����������㣬��ô��������������Ŀռ��û�б��ͷţ����ܻ�����ڴ�й©
			pb = pb->next;
			pa = pa->next;  //������ͬ����¼�ú�pa��pb��pc��Ҫָ����һ�����
			pc = pc->next;
			free(px), px = NULL;  //�ͷŵ���a�Ǹ��������Ľ���ڴ�
		}
		else
		{
			pc->next = pa;  //�����b�����ݴ��ڱ�a�����a�����ݴ�ŵ���c��
			pa = pa->next;
			pc = pc->next;  //pa��pc��ָ����һ�����
		}
	}
	//����ѭ����������pa����pbΪ��ֵ��Ҳ����˵��a���b�Ѿ�������β��
	//����һ��������ˣ���ô�Ͱ���һ����ʣ�µĽ�㶼���ڱ�c��
	pc->next = pa ? pa : pb;  	//�˴��ж�pa���Ϊ�գ���ô�Ͱѱ�bʣ�µĽ�����pc�󣬷�֮�ѱ�a�Ľ�����pc��
	free(Lb), Lb = NULL;
}
#define PRINTF(x) printf("���ʼ������"#x"\n")
int main()
{
	PRINTF(a);
	LinkList La = InitList();
	PRINTF(b);
	LinkList Lb = InitList();
	LinkList Lc = (Lnode*)malloc(sizeof(Lnode));
	//����MergeList�Ĵ����е�����
	//���ﺯ��MergeList����Lcʱ������Lc���ָ�뱾���ڶ�̬�����ڴ�ʱ��Lcָ�������ǿ��ٵ��ǿ��ڴ�ĵ�ַ
	
	// ���ε�MergeList����ʱ����ʵ������Lc��һ����������MergeList�����У����ǰ��������Lcָ���λ���޸�Ϊ������La��λ��
	
	// Ȼ���ں������޸ĵ�Lc��ʵһֱ���Ǹ���Lc�����������Ǵ������Ǹ�Lc�������ڳ���MergeList�����󣬻ᷢ��Lcָ�������ʲô��û��
	
	// ��Ϊ���Ǹ���û���޸�ʵ�ʵ�Lcָ������ݣ�����һֱ���޸ĸ���Lcָ������ݣ���ֻ���޸���Lcָ�����������ݣ���û���޸�Lc
	
	//�������ʵ�ʵ�Lc��ָ�����ı䣬��Ӧ�ô�Lc�ĵ�ַ�������������ں����ڲ��޸�Lc��ʱ��ͬʱ�޸�Lc��ָ��ĵ�ַ
	
	//����ζ�ſ����ں����ڲ�����һ���������� Lc ָ��ָ�������⽫Ӱ�쵽 Lc �ں����ⲿ��ֵ��
	MergeList(La, Lb, Lc);
	//������봫��Lc�ĵ�ַ�Ļ�������һ���޸ķ�ʽΪ��
	// ����a��b��MergeList�����кϲ��󣬰Ѻϲ��������ĵ�ַ���س�����Lc����
	//LinkList Lc = MergeList(La, Lb);  
	Lnode* pa = La->next;
	while (pa)
	{
		printf("%d ", pa->data);
		pa = pa->next;
	}
	return 0;
}