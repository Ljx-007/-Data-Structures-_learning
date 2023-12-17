#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 20
typedef struct
{
	int key;
	char other;
}RedType;
typedef struct
{
	RedType r[MAXSIZE + 1];
	int len;
}SqList;
//归并排序，将两个不同的有序序列合并成一个有序的序列
//归并相邻两个有序子序列的归并
void Merge(RedType R[], RedType T[], int left, int right, int mid)
{
	//有序表R[left,...,mid],和R[mid+1,...,right]相邻，归并为有序表T[left,...right]
	int i = left;
	int j = mid + 1;
	int k = left;
	while (i <= mid || j <= right)
	{
		if (R[i].key <= R[j].key)
			T[k++] = R[i++];
		else
			T[k++] = R[j++];
	}
	while (i <= mid)
	{
		T[k++] = R[i++];
	}
	while (j <= right)
		T[k++]=R[j++];
}
//时间复杂度O（nlog2 n) ,空间复杂度O（n）
//是稳定排序

//基数排序
//基数排序利用链表存储，又称为桶排序，实现分配和收集
//若关键字是整数，可以认为关键字是由0-9这十个数字组成的，分别在不同的位。如果关键字是字符串，那么则认为关键字由a-z这26个字母组成的。
//根据关键字的组成不同，需要设置不同数量的桶。以关键字为整数为例，我们需要设置10个桶，分别代表数字0-9
//然后将所有关键字从个位开始，个位数字与桶代表的数字相同的则放入桶内，全部放入后再按照顺序取出，第一次分配和收集就完成了
//此时的关键字个位数已经从小到大排好了，接下来是十位，百位，.....直到全部排完后，序列已经成为有序序列

//基数排序的时间复杂度O(k*(n+m)),k为关键字个数，n为数据元素个数（数据元素中有k个关键字），m为关键字的取值范围，有m个值
//空间复杂度（n+m），有m个桶，要存放n个元素
//基数排序是稳定排序