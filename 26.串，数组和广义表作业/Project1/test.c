#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//1.写一个算法统计在输入字符串中各个不同字符出现的频度并将结果存入文件（字符串中的合法字符为A-Z这26个字母和0-9这10个数字
//分析：字母和数字一共有36个元素，可以将它们编成一个数组int arr[36],字母可以用ACRII码值来代替,它们的值就是数组的下标
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
			fprintf(pf, "%c出现的次数:%d\n", i + '0', arr[i]);
		for (int i = 10; i <= 35; i++)
			fprintf(pf, "%c出现的次数:%d\n", i + 'A' - 10, arr[i]);
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

//2.写一个递归算法来实现字符串逆序存储，要求不另设串存储空间。
void reverse(char* str)
{
	static int i = 0;    //利用静态变量来实现字符串从后向前存储
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

//3.编写算法，实现下面函数的功能，函数void insert(char* s,char* t,int pos)将字符串t插入到字符串s中，插入位置pos。
// 假设分配给字符串s的空间足够让字符串t插入。（说明：不得使用任何库函数）
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
	for (int i = pos, j = 0; i < slen; i++,j++)   //创建ch数组把s数组pos位置后的字符都存进去
		ch[j] = s[i];
	if (pos<0 || pos>slen)
		printf("坐标非法\n");
	else
	{
		
		for (int i = pos,j=0; i < slen; i++,j++)
		{
			s[i + tlen] = ch[j];    //s数组pos后的子串向右移动tlen个长度，留出t串的长度来放t串
		}
		for (int j = 0; j < tlen; j++)
		{
			s[pos++]=t[j];       //在留出的空间内补上t串
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

//4.已知字符串S1中存放一段英文，写出算法format(s1,s2,s3,n)，将其按给定的长度n格式化成两端对齐的字符串S2（即长度为n且首尾字符不得为空格字符）
  //将多余的字符送S3
void format(char* s1, char* s2, char* s3, int n)
{
	int i,j=0;
	char* p1 = s1;
	while (*p1 == ' ')   //s1开头有空格就往下遍历直到没有空格为止
		p1++;
	if (!*p1)
		printf("s1为空串\n");
	else
	{
		for (i = 0; i <= n; i++)
		{  
			s2[i] = *p1++;           //给s2赋值
			if (!*p1)
			{
				printf("S1中没有长度为n的对齐字符串\n");
				return;
			}
		}
		while (*p1 == ' ') { p1++; }
		if(s2[i-1] == ' ' && *p1 != 0)   //如果s2的末尾是空格，则p1往后遍历直到不是空格
		{
			s2[i] = *p1++, s2[i +1] = '\0';
		}
		if (!*p1)
		{
			printf("S1中没有长度为n的对齐字符串\n");
			return;
		}
		while (*p1)   //剩余送S3
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

//5.设一个二维数组a[1...m,1...n]含有m*n个整数
//（1）写一个算法判断a中所有元素是否互不相同？输出相关信息(yes/no)
//（2）试分析算法的时间复杂度
#define M 3
#define N 3
void IsDifferent(int arr[][N])
{
	for (int i = 0; i < M; i++)
	{
		for(int j=0;j<N;j++)
		{
			for (int k = j + 1; k < N; k++)  //与同一行元素比较
			{
				if (arr[i][j] == arr[i][k])
				{
					printf("no\n");
					return 0;
				}
			}
			for (int p = i + 1; p < M; p++)   //与下一行元素比较
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
//数组一共m*n个元素，第一个元素要比较m*n-1次，第二个元素要比较m*n-2次，....，第m*n-1个元素要比较1次
//总共比较次数：(m*n-1)+(m*n-2)+.....+2+1=(m*n-1+1)*(m*n-1)/2,这是最坏情况。
//所以时间复杂度为O(n)=(m*n)^2

//6.设任意n个整数存放于数组A[1..n]中，试编写算法，将所有正数排在所有负数前面（要求算法时间复杂度为O(n))
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