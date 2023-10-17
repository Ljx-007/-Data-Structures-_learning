#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
typedef struct Lnode
{
	int data;
	struct Lnode* next;
}Lnode, * LinkList;
//������������
Lnode* Creat_Sq()
{
	int n, ret;
	char str[1001];
	printf("����Ҫ������������");
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
//������������
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
	Lnode* r = L;
	for (int i = 0; i < n; i++)
	{
		Lnode* p = (Lnode*)malloc(sizeof(Lnode));
		printf("������ý������ݣ�");
		scanf("%d", &(p->data));
		p->next = r->next;               //��β�巨��������
		r->next = p;
		r = p;
	}
	return L;
}
//�㷨�����
//6.���һ���㷨��ͨ��һ�˱���ȷ������Ϊn�ĵ�������ֵ���Ľ��
Lnode* Max(LinkList L)
{
	if (L->next == NULL)
		return NULL;
	int n;
	Lnode* p = L->next;
	Lnode* max = L->next;   //��max��ָ��������ֵ���Ľ�㣬�ʼָ����Ԫ��㣬�����ִ���max�Ľ��ʱ��max���¸�ֵ
	n = p->data;
	p = p->next;
	while (p)
	{
		if (p->data > n)
		{
			max = p;
			n = p->data;
		}
		p = p->next;
	}
	return max;
}

//7.���һ���㷨�������������н������ӷ���ԭ�ء���ת����Ҫ�������ԭ��Ĵ洢�ռ䣬���仰˵��Ҫ���㷨�ռ临�Ӷ�ΪO(1)
void Reverse(LinkList* L)
{
	Lnode* p = (*L)->next;
	(*L)->next = NULL;
	while (p)
	{
		Lnode* hp = p;
		p = p->next;
		hp->next = (*L)->next;   //��ͷ�巨ʵ�ֵ���
		(*L)->next = hp;  
	}
}

//8.���һ���㷨��ɾ����������������ֵ����mink��С��maxk������Ԫ�أ���mink��maxk�Ǹ�����������������ֵ���Ժͱ���Ԫ����ͬ��Ҳ���Բ�ͬ��
void delete(LinkList* L, int mink, int maxk)
{
	Lnode* p = (*L)->next;
	Lnode* pre = *L;
	while (p)
	{
		if (p->data > mink && p->data < maxk)
		{
			Lnode* f = p;
			pre->next = p->next;
			p = p->next;
			free(f), f = NULL;
		}
		else
		{
			pre = p;
			p = p->next;
		}
	}
}

//9.��֪pָ��˫��ѭ�������е�һ����㣬����ṹΪdata��prior��next������д���㷨change(p)������p��ָ��Ľ�㼰��ǰ������˳��
typedef struct LoopNode  //����˫��ѭ������Ľ��
{
	int data;
	struct LoopNode* prior;
	struct LoopNode* next;
}LoopNode,*LoopList;
//����˫��ѭ������
LoopList Creat_Loop()
{
	int n, ret;
	char str[1001];
	printf("����Ҫ�����Ľ�������");
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
	LoopList L = (LoopNode*)malloc(sizeof(LoopNode));
	L->next = NULL;
	LoopNode* r = L;  //����ָ��rһֱָ��β���
	for (int i = 0; i < n; i++)
	{
		LoopNode* p = (LoopNode*)malloc(sizeof(LoopNode));
		printf("������ý������ݣ�");
		scanf("%d", &(p->data));
		p->next = r->next;               //��β�巨��������
		r->next = p;
		p->prior = r;
		r = p;
	}
	//˫����������󡣴�ʱrΪβ��㣬��β�����ͷ�����������
	L->prior = r;
	r->next = L;
	return L;
}
//����˫��ѭ�������н��p����ǰ������˳��
void change(LoopNode* p)
{
	LoopNode* pre = p->prior;  //pre��p��ǰ�����
	pre->next = p->next;   
	p->next->prior = pre;  
	p->next = pre;
	p->prior = pre->prior;
	pre->prior->next = p;
	pre->prior = p;
}

//10.��֪����Ϊn�����Ա�A����˳��洢�ṹ����дһ��ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(1)���㷨�����㷨��ɾ�����Ա�������Ϊitem������Ԫ��
typedef struct SqList
{
	int* data;
	int len;
}SqList;
void Creat_SqList(SqList* L)
{
	L->len = 0;
	int n, ret,elem;
	char str[1001];
	printf("����Ҫ������Ԫ�ظ�����");
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
	L->data = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
	{
		printf("���������ݣ�");
		scanf("%d", &elem);
		L->data[i] = elem;
		L->len++;
	}
}

void Delete_item(SqList* L,int item)
{
	int left = 0;         //��Ŀֻ��˵ɾ������item��ȵ�Ԫ�أ���û��˵���ܵ���λ��
	int right = L->len- 1;               //����һ��ͷָ���βָ�룬ͷָ�����ұ�����βָ���������
	L->len = 0;              //�ѱ�����0�����¼���ɾ��Ԫ�غ��ĳ���             
	while (left <= right)        //��ͷָ�����βָ��ʱѭ������
	{
		if (L->data[left] == item)            //���ͷָ���������item����βָ���������
		{
			while (L->data[right] == item&&left<=right)      //βָ��������Ҳ����item�����������������������ǰ��Ϊ����С��ͷָ��
			{
				right--;
			}
			if (left > right)      //���ͷָ�����βָ�룬��ѭ������
				break;
			L->data[left] = L->data[right];     //���û���ڣ�˵��βָ�뵱ǰָ����������item���򽻻�ͷָ���βָ�����
			right--;  //�������βָ������������
		}
		left++;     //�����˻��߲�������˵����ָ���ʱָ���ֵ��������item��������ָ�����ұ���
		L->len++;    //������ָ����������ӱ�
	}
}
 //ʱ�临�Ӷ�ΪO(n)����Ϊ��Ϊn����ָ�����ָ��ͬʱ���м������һ���ͱ�����n��Ԫ��
//�ռ临�Ӷ�ΪO(1)�����������ڱ��Ͻ��У�û��ʹ�ö���ĸ����ռ�
int main()
{
	//LoopList L = Creat_Loop();
	//change(L->next->next->next);
	//Lnode* p = Max(L);
	//Reverse(&L);
	//delete(&L, 0, 10);
	/*Lnode* p = L->next;
	while(p)
	{
		printf("%d ", p->data);
		p = p->next;
	}*/
	SqList L;
	Creat_SqList(&L);
	for (int i = 0; i < L.len; i++)
	{
		printf("%d ", L.data[i]);
	}
	printf("\n");
	Delete_item(&L, 4);
	for (int i = 0; i < L.len; i++)
	{
		printf("%d ", L.data[i]);
	}
	return 0;
}