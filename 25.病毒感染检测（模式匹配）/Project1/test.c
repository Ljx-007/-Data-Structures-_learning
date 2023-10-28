#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct SString
{
	char ch[1024];
	int len;
}SString;
//������Ⱦ���
//���ݻ��ߵ�DNA���У���������Ƿ�����˲���DNA���У���������ˣ���˻��߸�Ⱦ���ò���
//ע�⣬������DNA�ǻ�״�ģ����粡��DNA����Ϊ aab ������DNA�����г���aab,aba,baa����Ϊ���߸�Ⱦ���ò���
int Getlen(char* str)
{
	int i = 1,count=0;
	while (str[i] != '\0')
		i++, count++;
	return count;
}
void Read(SString* S,SString* T,FILE* pf)
{
	int i = 1, j = 1;
	while(1)
	{
		char ch = fgetc(pf);
		if (ch== '\n' || ch == ' '||ch==EOF)  //����ȡ�����ַ�Ϊ���з����߿ո�����ļ�ĩβʱ����ֹͣ��ȡ
		{
			break;
		}
		T->ch[i] = ch, i++;
	}
	T->len = Getlen(T->ch);
	while (1)
	{
		char ch = fgetc(pf);
		if (ch == '\n'||ch == ' '||ch==EOF)  
		{
			break;
		}
		S->ch[j] = ch, j++;
	}
	S->len = Getlen(S->ch);
}
void Get_nextval(char* str,int len,int nextval[])
{
	int i = 1, j = 0;
	nextval[1] = 0;
	while (i <len)
	{
		if (j == 0 || str[i] == str[j])
		{
			i++, j++;
			if (str[i]!= str[j])
				nextval[i] = j;
			else
				nextval[i] = nextval[j];
		}
		else
			j = nextval[j];
	}
}
int KMP(SString* S, SString* T)
{
	int* nextval = (int*)malloc(sizeof(int) * 1024);
	char cpy[1024] = { 0 };    //����Ҫ����һ��ģʽ��T->ch�ĸ�������Ϊ�����������������ָ��tmpָ��ģʽ����ָ���޸Ļ���ģʽ��Ҳ�����޸�
	for (int i = 0; i < T->len + 1; i++)
	{
		cpy[i] = T->ch[i];          //��ģʽ����ֵ���Ƶ�������
	}
	//����tmpָ��ָ�򸱱���������������ָ���ڸ����в���
	char* tmp = cpy;   //����ΪʲôҪ����һ��ָ�룬��Ϊ����Ҫ��ָ�벻����ǰ��һ���ַ������͵���char*�����Ա���Ҫ��һ��ָ��
	for (int k = 0; k < T->len; k++)
	{
		int i = 1, j = 1;
		int len_tmp=Getlen(tmp);   //tmp��ʵ�ɿ���һ��ģʽ�����������ģʽ���ĳ���
		Get_nextval(tmp,len_tmp, nextval);   //��Ϊ�����ø���������ģʽ��������nextval�����в�����T->len������ģʽ�������ˣ���������Ҫ�ഫһ��ֵ
		while (i <= S->len && j <= T->len)
		{
			if (j == 0 || S->ch[i] == tmp[j])
				i++, j++;
			else
				j = nextval[j];
		}
		if (j > T->len)
			return 1;
		tmp++, tmp[0] = 0;    //����������DNAѭ���Ĺؼ����֣�tmpָ����ǰ�ƶ�����0λ�õ��ַ���Ϊ0
		tmp[T->len] = T->ch[k+1];  //�����һλ���ַ���Ϊԭ��ģʽ���ĵ�һλ������ѭ���оʹ����ѭ��DNA��Ч��
	}
	return 0;
}
int main()
{
	//��ȡ��������¼
	FILE* pf = fopen("record.txt", "r+");
	if (!pf)
	{
		printf("�ļ���ʧ��\n");
		return -1;
	}
	while(!feof(pf))   //feof����0��pfָ���ļ�ĩβ,û��ָ���ļ�ĩβ����1
	{
		SString S = { 0 }, T = { 0 };   //����Ҫ��������ģʽ���ĳ�ʼ������ѭ�����Ȼ��ȡ�������ִ���ʱ��ֻ�Ǹ�����ֵ
		                             //���ֻ�Ǹ���ֵ�����ַ����ӳ���̣������abcde���acc�ͻ����accde����ֻ������ǰ����ֵ��������ֵû���ǵ����
		Read(&S, &T, pf);
		int ret = KMP(&S, &T);
		if (ret == 1)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}