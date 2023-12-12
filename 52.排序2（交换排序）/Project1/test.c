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
	int lenth;
}SqList;
//交换排序
//冒泡排序
void BubbleSort(SqList* L)
{
	for (int i = 1; i < L->lenth; i++)  //趟数 i
	{
		int flag = 1;										//趟数+比较次数=元素个数----i+L->lenth-i=L->lenth
		for (int j = 1; j < L->lenth - i+1; j++)  //比较次数：L->lenth-i
		{
			if (L->r[j].key > L->r[j + 1].key)
			{
				RedType tmp = L->r[j];
				L->r[j] = L->r[j + 1];
				L->r[j + 1] = tmp;
				flag = 0;
			}
		}
		if (flag == 1)
			break;
	}
}
//冒泡排序时间复杂度为O(n^2),空间复杂度为O(1)
//可用于链式存储结构
//算法平均时间性能比直接插入排序差，n较大时不宜使用

//快速排序
//基本思想：任取一个元素为中心（如第一个元素），所有比它小的元素往前放，比它大的往后放，形成左右两个子表
// 对各子表重新选择中心元素并按先前规则调整，直到子表元素剩下一个。这是一种递归思想
int Partition(SqList* L, int left, int right)   //对表内进行排序
{
	L->r[0] = L->r[left];   //left一般指向表中第一个元素，所以最开始将第一个元素放在哨兵位置
	while (left < right)  //这里是left<right而不是left<=right是因为排序到最后left和right应一同指向一个空位置
	{               //如果是left<=right，那么出while循环时，不知道是left指向空位置还是right指向空位置，无法将哨兵重新放回空位置，所以不能是left<=right
		while (L->r[right].key >= L->r[0].key && left < right)  //从表的右端往左遍历，直到找到一个元素小于中间元素（哨兵），同时要保证left不能>=right
			right--;
		L->r[left] = L->r[right];  //找到后把小于哨兵的元素放在左端left指向的空位置
		while (L->r[left].key <= L->r[0].key && left < right)  //从表的左端往右遍历，直到找到一个元素大于中间元素（哨兵），同时要保证left不能>=right
			left++;
		L->r[right] = L->r[left];  //找到后把大于哨兵的元素放在右端right指向的空位置
	}
	L->r[left] = L->r[0];   //最后排序完将哨兵放回最后的空位置，此时right和left都指向空位置
	return left;   //把中心位置返回
}
void Qsort(SqList* L, int left, int right)
{
	if (left < right)  //保证子表长度大于1
	{
		int privot = Partition(L,left,right);   //找到中心位置privot
		Qsort(L, left, privot - 1);  //递归排序左子表
		Qsort(L, privot + 1, right);  //递归排序右子表
	}
}
//Qsort函数的平均时间复杂度为 O(log2 n),Partition函数的平均时间复杂度为O(n)
//快速排序算法的平均时间复杂度为O(nlog2 n)，空间复杂度平均情况下为O(log2 n),最坏情况为O(n)
//就平均计算时间而言，快速排序是我们所讨论的所有内排序方法中最好的一个 ,是一种不稳定排序
//快速排序不适用于原本有序或基本有序的记录序列进行排序
//快速排序是不自然排序，自然排序是序列越有序，排的越快。
