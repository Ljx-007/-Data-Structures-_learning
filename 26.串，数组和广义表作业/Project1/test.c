#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//1.дһ���㷨ͳ���������ַ����и�����ͬ�ַ����ֵ�Ƶ�Ȳ�����������ļ����ַ����еĺϷ��ַ�ΪA-Z��26����ĸ��0-9��10������
//��������ĸ������һ����36��Ԫ�أ����Խ����Ǳ��һ������int arr[36],��ĸ������ACRII��ֵ������,���ǵ�ֵ����������±�
void Count(char* str)
{
	int arr[36] = { 0 };
	char ch;
	while (ch=*str++)
	{
		if ('0' <= ch && ch <= '9')
		{
			int i = ch - '0';
			arr[i]++;
		}
		if (ch >= 'A' && ch <= 'Z')
		{
			int i = ch - 'A' + 10;
			arr[i]++;
		}
	}
	FILE* pf = fopen("record.txt", "w");
	if (pf)
	{
		for (int i = 0; i < 10; i++)
			fprintf(pf, "%c���ֵĴ���:%d\n", i + '0', arr[i]);
		for (int i = 10; i <= 35; i++)
			fprintf(pf, "%c���ֵĴ���:%d\n", i + 'A' - 10, arr[i]);
	}
	else
		printf("open file error");
}
//int main()
//{
//	char ch[] = "0123456789ABCDEFG";
//	Count(ch);
//	return 0;
//}

//2.дһ���ݹ��㷨��ʵ���ַ�������洢��Ҫ�����贮�洢�ռ䡣
void reverse(char* str)
{
	static int i = 0;    //���þ�̬������ʵ���ַ����Ӻ���ǰ�洢
	char ch;
	scanf("%c", &ch);
	if (ch != '\n')
	{
		reverse(str);
		str[i++] = ch;
	}
	str[i] = 0;
}
//int main()
//{
//	char str[1024];
//	reverse(str);
//	printf("%s", str);
//	return 0;
//}

//3.��д�㷨��ʵ�����溯���Ĺ��ܣ�����void insert(char* s,char* t,int pos)���ַ���t���뵽�ַ���s�У�����λ��pos��
// ���������ַ���s�Ŀռ��㹻���ַ���t���롣��˵��������ʹ���κο⺯����
int my_strlen(char* s)
{
	int count = 0;
	while (*s++)
		count++;
	return count;
}
void insert(char* s, char* t, int pos)
{
	int slen = my_strlen(s);
	int tlen = my_strlen(t);
	char ch[1024] = { 0 };
	for (int i = pos, j = 0; i < slen; i++,j++)   //����ch�����s����posλ�ú���ַ������ȥ
		ch[j] = s[i];
	if (pos<0 || pos>slen)
		printf("����Ƿ�\n");
	else
	{
		
		for (int i = pos,j=0; i < slen; i++,j++)
		{
			s[i + tlen] = ch[j];    //s����pos����Ӵ������ƶ�tlen�����ȣ�����t���ĳ�������t��
		}
		for (int j = 0; j < tlen; j++)
		{
			s[pos++]=t[j];       //�������Ŀռ��ڲ���t��
		}
	}
}
//int main()
//{
//	char s[1024] = "abcdejksjldkjfklsjdflk";
//	char t[] = "1212354";
//	insert(s, t, 7);
//	printf("%s", s);
//	return 0;
//}

//4.��֪�ַ���S1�д��һ��Ӣ�ģ�д���㷨format(s1,s2,s3,n)�����䰴�����ĳ���n��ʽ�������˶�����ַ���S2��������Ϊn����β�ַ�����Ϊ�ո��ַ���
  //��������ַ���S3
void format(char* s1, char* s2, char* s3, int n)
{
	int i,j=0;
	char* p1 = s1;
	while (*p1 == ' ')   //s1��ͷ�пո�����±���ֱ��û�пո�Ϊֹ
		p1++;
	if (!*p1)
		printf("s1Ϊ�մ�\n");
	else
	{
		for (i = 0; i <= n; i++)
		{  
			s2[i] = *p1++;           //��s2��ֵ
			if (!*p1)
			{
				printf("S1��û�г���Ϊn�Ķ����ַ���\n");
				return;
			}
		}
		while (*p1 == ' ') { p1++; }
		if(s2[i-1] == ' ' && *p1 != 0)   //���s2��ĩβ�ǿո���p1�������ֱ�����ǿո�
		{
			s2[i] = *p1++, s2[i +1] = '\0';
		}
		if (!*p1)
		{
			printf("S1��û�г���Ϊn�Ķ����ַ���\n");
			return;
		}
		while (*p1)   //ʣ����S3
		{
			s3[j++] = *p1++;
		}
	}
}
//int main()
//{
//	char* s1 = "hello, my name is ljx ";
//	char s2[1024] = { 0 };
//	char s3[1024] = { 0 };
//	format(s1, s2, s3, 22);
//	printf("%s\n%s\n%s", s1, s2, s3);
//	return 0;
//}

//5.��һ����ά����a[1...m,1...n]����m*n������
//��1��дһ���㷨�ж�a������Ԫ���Ƿ񻥲���ͬ����������Ϣ(yes/no)
//��2���Է����㷨��ʱ�临�Ӷ�
#define M 3
#define N 3
void IsDifferent(int arr[][N])
{
	for (int i = 0; i < M; i++)
	{
		for(int j=0;j<N;j++)
		{
			for (int k = j + 1; k < N; k++)  //��ͬһ��Ԫ�رȽ�
			{
				if (arr[i][j] == arr[i][k])
				{
					printf("no\n");
					return 0;
				}
			}
			for (int p = i + 1; p < M; p++)   //����һ��Ԫ�رȽ�
			{
				for (int m = 0; m < N; m++)
				{
					if (arr[i][j] == arr[p][m])
					{
						printf("no\n");
						return 0;
					}
				}
			}
		}
	}
}
//����һ��m*n��Ԫ�أ���һ��Ԫ��Ҫ�Ƚ�m*n-1�Σ��ڶ���Ԫ��Ҫ�Ƚ�m*n-2�Σ�....����m*n-1��Ԫ��Ҫ�Ƚ�1��
//�ܹ��Ƚϴ�����(m*n-1)+(m*n-2)+.....+2+1=(m*n-1+1)*(m*n-1)/2,����������
//����ʱ�临�Ӷ�ΪO(n)=(m*n)^2

//6.������n���������������A[1..n]�У��Ա�д�㷨�������������������и���ǰ�棨Ҫ���㷨ʱ�临�Ӷ�ΪO(n))
void sort(int arr[],int len)
{
	int* left = arr;
	int* right = arr + len - 1;
	while (left<=right)
	{
		while (*left > 0)
		{
			left++;
		}
		while (*right < 0)
			right--;
		if (left <= right)
		{
			int tmp = *left;
			*left = *right;
			*right = tmp;
		}
	}
}
int main()
{
	int arr[10] = { 1,-2,3,-4,5,-6,7,-8,9,-10 };
	sort(arr, 10);
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", arr[i]);
	}
	return 0;
}