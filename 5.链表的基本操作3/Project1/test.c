#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct Student  //�ȴ���һ��ѧ������
{
	char num[10];
	char name[8];
	int score;
}Stu;
typedef struct Lnode  //�ٴ���һ������������
{
	Stu data;
	struct Lnode* next; //��һ�����ĵ�ַ
}Lnode, * LinkList;

//�����ɾ��
void DeleteList(LinkList L, int i)
{
	Lnode* p = L;
	Lnode* q;
	int j = 0;
	//�ҵ���i-1��Ԫ��
	//while(p&&i-1>j)
	//p->nextΪ��˵��p�Ѿ������һ�������
	while (p->next && i - 1 > j)  //�����pҪ��Ϊp->next����Ϊ������޸���ע��һ���Ļ����������i����������ʱ��p�ͻ�һֱ����ֱ��p==NULL
	{                           //�����䶼���޸�Ϊp->next����ô����p������p==NULL��Ҳ�����if����жϺ��ӡû�д�Ԫ�أ��������޲��޸Ķ���û�й�ϵ
		                        //��ΪʲôҪ��Ϊp->next��,��Ϊ���ĵĻ������i=����+1����ô��j=����ʱ��pָ�����һ����㣬��ʱi-1==j,����ѭ��
		                   //��pҲû��ָ���ָ�룬û�н���if��䣬��ʼִ��ɾ�����룬��ʱp->next->nextʱ������ģ���Ϊpָ�����һ����㣬��ָ����Ϊ��
		                 //��ָ��û��ָ����next�ˣ�����ִ�е�p->next->nextʱ�ͻᱨ��
		p = p->next;
		j++;
	}
	//if(!p||j>i-1)
	if (!(p->next) || j > i - 1)
	{
		printf("û�д�Ԫ�أ�\n");
		return;
	}
	//Ҫ�ѵ�i��Ԫ��ɾ������Ҫ�õ�i-1������ָ����ָ���i+1�����ĵ�ַ
	//p�ǵ�i-1�����ĵ�ַ��p->next�ǵ�i�����ĵ�ַ��p->next->next�ǵ�i+1�����ĵ�ַ
	q = p->next; //ɾ����i����㻹Ҫ�ѵ�i�������ڴ���ͷ��ˣ���q�����i�����ĵ�ַ��������һ�д������p���Ҳ�����i�����ĵ�ַ��
	p->next = p->next->next;
	free(q), q = NULL;
}

//����Ĳ���
Lnode* Located(LinkList L, Stu e)
{
	Lnode* p = L;
	while (p && strcmp(p->data.name,e.name)!=0&&strcmp(p->data.num,e.num)!=0&&p->data.score!=e.score) 
		//����p->data ��e ���ǽṹ�壬�ṹ�岻�ܼ򵥵���==����!=�����ж����Ƿ���Ȼ��߲����
		                //��Ϊ�ṹ���к��г�Ա��������Ҫ�ж����ṹ���Ƿ����ֻ���ж����Ա�Ƿ�������
		//�˴�whileѭ���жϵ��ṹ����������Ա�����������ʱ���Ž���ѭ��
	{
		p = p->next;
	}
	return p;
}

//��������ͷ�巨
//�����еĽ��Ӻ�ǰһ��һ�����������ͷ����ͷ���֮������������
void CreatList(LinkList L)  //Ҫ����n��Ԫ��
{
	int n,ret;
	char arr[100] = { 0 };
	printf("Ҫ�����Ԫ�ظ���:");
	again:
	ret=scanf("%d", &n);
	while (ret != 1)
	{
		while (gets_s(arr,100) != (char*)'\n')  //�������Ĳ������֣���ȡ������������ַ�������������
		{
			printf("���������֣�");
			goto again;
		}
	}
	L = (LinkList)malloc(sizeof(Lnode)); //����һ��ͷ���
	L->next = NULL;  //ͷ����ָ�����ÿգ��Ա��һ�������Ԫ�ص�ָ����Ϊ�գ���Ϊ���һ��Ԫ��
	for (int i = 0; i < n; i++)
	{
		Lnode* p = (Lnode*)malloc(sizeof(Lnode));
		//��������p��ֵ������������������
		//...
		printf("������");
		scanf("%s", p->data.name);
		printf("ѧ�ţ�");
		scanf("%s", p->data.num);
		printf("�ɼ���");
		scanf("%d", &(p->data.score));
		p->next = L->next;   //��Ϊ��ͷ�巨������pҪ���뵽ͷ����ĵ�һ��λ���У�����p��ָ����Ҫָ��ԭ��L���Ԫ�أ���ԭ��L���Ԫ����p��
		L->next = p;  //p�����Ԫ�غ�ǰ��Ҫ����L������L��ָ����Ҫ��Ϊp
	}
}

//����Ĵ�����β�巨
void CreatList2(LinkList L)
{
	int n, ret;
	char arr[100] = { 0 };
	printf("Ҫ�����Ԫ�ظ���:");
again:
	ret = scanf("%d", &n);
	while (ret != 1)
	{
		while (gets_s(arr, 100) != (char*)'\n')  //�������Ĳ������֣���ȡ������������ַ�������������
		{
			printf("���������֣�");
			goto again;
		}
	}
	L = (LinkList)malloc(sizeof(Lnode)); //����һ��ͷ���
	L->next = NULL;
	Lnode* r = L; //����һ��βָ��,һֱָ�����һ�����
	for (int i = 0; i < n; i++)
	{
		Lnode* p = (Lnode*)malloc(sizeof(Lnode));
		//��������
		//...
		p->next = NULL;  //��Ϊ������p�Ǵ������β�����ϣ�p�����һ����㣬����p��ָ����Ҫ���ÿգ�
		p = r->next;  //p����β��㣬r�ͱ����pǰ��һ����㣬�������������������������r��ָ����Ҫָ��p
		r = p;  //p����������˺�βָ��r��Ҫ���β����ˣ�������r=p����ΪpҲ��β���
	}
}

//ѭ������
//ѭ��������ǰѵ��������β����ָ������NULL��Ϊͷָ��
//ѭ������һ������βָ�벻����ͷָ�룬βָ�봦���������������
int main()
{
	LinkList L = { 0 };
	CreatList(L);
	return 0;
}