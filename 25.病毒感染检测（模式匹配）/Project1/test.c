#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct SString
{
	char ch[1024];
	int len;
}SString;
//病毒感染检测
//根据患者的DNA序列，检测其中是否出现了病毒DNA序列，如果出现了，则此患者感染过该病毒
//注意，病毒的DNA是环状的，例如病毒DNA序列为 aab ，则患者DNA序列中出现aab,aba,baa都认为患者感染过该病毒
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
		if (ch== '\n' || ch == ' '||ch==EOF)  //当读取到的字符为换行符或者空格或者文件末尾时，就停止读取
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
	char cpy[1024] = { 0 };    //这里要创建一个模式串T->ch的副本，因为如果不创建副本，用指针tmp指向模式串，指针修改会让模式串也跟着修改
	for (int i = 0; i < T->len + 1; i++)
	{
		cpy[i] = T->ch[i];          //将模式串的值复制到副本中
	}
	//设置tmp指针指向副本，后续操作利用指针在副本中操作
	char* tmp = cpy;   //这里为什么要设置一个指针，因为我们要让指针不断向前移一个字符，类型得是char*，所以必须要用一个指针
	for (int k = 0; k < T->len; k++)
	{
		int i = 1, j = 1;
		int len_tmp=Getlen(tmp);   //tmp其实可看成一个模式串，这里计算模式串的长度
		Get_nextval(tmp,len_tmp, nextval);   //因为我们用副本代替了模式串，所以nextval函数中不能用T->len来计算模式串长度了，所以我们要多传一个值
		while (i <= S->len && j <= T->len)
		{
			if (j == 0 || S->ch[i] == tmp[j])
				i++, j++;
			else
				j = nextval[j];
		}
		if (j > T->len)
			return 1;
		tmp++, tmp[0] = 0;    //这里则是令DNA循环的关键部分，tmp指针向前移动，把0位置的字符改为0
		tmp[T->len] = T->ch[k+1];  //把最后一位的字符改为原来模式串的第一位，放入循环中就达成了循环DNA的效果
	}
	return 0;
}
int main()
{
	//读取病毒检测记录
	FILE* pf = fopen("record.txt", "r+");
	if (!pf)
	{
		printf("文件打开失败\n");
		return -1;
	}
	while(!feof(pf))   //feof返回0则pf指向文件末尾,没有指向文件末尾返回1
	{
		SString S = { 0 }, T = { 0 };   //这里要把主串和模式串的初始化放在循环里，不然读取主串和字串的时候只是覆盖了值
		                             //如果只是覆盖值，当字符串从长变短，例如从abcde变成acc就会出现accde这样只覆盖了前三个值，后三个值没覆盖的情况
		Read(&S, &T, pf);
		int ret = KMP(&S, &T);
		if (ret == 1)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}