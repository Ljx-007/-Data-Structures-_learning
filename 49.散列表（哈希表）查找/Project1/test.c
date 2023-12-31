#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//散列表（哈希表）
// 通过在元素的存储位置与数据关键字之间建立了某种联系，那么在进行查找时，只需要对其关键字进行运算，直接求出该元素所在地址，进而找到该元素
//散列函数：在记录的存储位置p和其关键字key之间建立一个确定的对应关系H，使p=H(key)，这个对应关系H称为散列函数，p为散列地址
//冲突和同义词：如果对于不同的关键词key能够得到相同的地址p，这种现象称为冲突，这两个key对该散列函数来说称为同义词

//构造哈希函数的方法有很多，最常用的就是除留余数法
//除留余数法：假设哈希表表长m。选择一个不大于m的数p，用p除去关键字，除后所得余数为哈希地址。 H（key）=key%p
//            一般情况下，p可选为小于表长的最大质数（p<=m）
//好的哈希函数可以减少冲突，但很难完全避免，创建哈希表和查找哈希表都会遇到冲突，两种情况下处理冲突的方法应一致

//处理冲突的方法有两种：开放地址法、链地址法
//开放地址法：
// 当有冲突时，采取合适的方法计算得到另一个地址，如果仍冲突，则继续计算得到下一个地址，直到没有冲突为止，这个寻找空位的过程称为“探测”
//  Hi=(H(key)+di)%m   i=,1,2,...,k(k<=m-1)
//H（key）为哈希函数，m为哈希表长，根据di取值不同可以分为三种探测方法
//1.线性探测法：
//di=1，2，3，...，m-1
//通过加一个增量序列，再用m对其结果取模，这样往后遍历的哈希表可以看成是循环的，一直从探测到表尾后没有空位则回到表头继续查找
//2.二次探测法：
//di=1^2,-(1^2),2^2,-(2^2),....,+k^2,-(k^2)  (k<=m/2)
//3.伪随机探测法： di=伪随机序列

//链地址法：
//把具有相同哈希地址的关键字（同义词）放在同一个单链表中，称为同义词链表。其形态类似于邻接表，用一个数组存放各个链表的头指针，有m个哈希地址就有m个单链表
//哈希地址相同的关键字放到一个单链表中，以此类推得到链地址
//优点：1.不会出现聚集现象（聚集：即多个同义词争夺同一个地址）
//      2.可以动态增加，对于表长不固定时适用

//哈希表的查找
typedef struct
{
	char id[11];
	char name[10];
	int age;
}People,*HashTable;
void InsertHash(HashTable hashT[], People* peo)
{
	//散列函数计算时，取模的数字可以时小于表长的最大质数
//方便起见，这里以年龄作为关键字，如果以id或者名字这样的字符串为关键字，则可以将字符串中每一个字符的ACRII码值相加，得到一个整数，再取模
	int hash = peo->age % 97;
	if (hashT[hash] == NULL)
	{
		hashT[hash] = peo;
		return;
	}
	else
	{
		for (int i = 0; i < 101; i++)  //如果循环结束，说明整个哈希表都没有能插入的空位了
		{
			hash = (hash + 1) % 101;  //线性探测法，如果取模后空位被占据，则向前探测空位
			//这里对101取模而不对97取模是因为如果对97取模，那么在哈希表中只能遍历97个位置，表中剩余的101-97=4个位置就没有可能遍历到，就浪费了。
			if(hashT[hash]==NULL)
			{
				hashT[hash] = peo;
				return;
			}
		}
	}
	printf("无空位");
}
int SearchHash(HashTable hashT[],People peo)
{
	int hash = peo.age % 97;
	if (hashT[hash]==NULL)
		return -1;
	else if (hashT[hash]->age == peo.age)
		return hash;
	else
	{
		for (int i = 0; i < 101; i++)
		{
			hash = (hash + 1) % 101;
			if (hashT[hash]->age == peo.age)
				return hash;
			else if (hashT[hash] == NULL)   //如果找到空位都没有匹配的值，说明该表没有要查找的值
				return -1;
		}
		return -1;  //如果查遍了哈希表都没有要找的值，也返回-1
	}
}
int main()
{
	//假如一个公司有80个员工，要查找这80个员工的信息，那么构造哈希表，表长至少要80，那么可以去一个表长为101
	HashTable hashT[101] = { 0 }; 
	People e[3] = { {"12345678910","林嘉曦",20},{"9876543210","克萨斯",57},{"65478213541","强森",77} };
	for (int i = 0; i < 3; i++)
	{
		InsertHash(hashT, &e[i]);
		//e++会报错是因为e是数组指针，代表的是一个数组，只有在传参的时候它才代表数组的首元素地址
	}
	People p = { "9876543210","克萨斯",57 };
	int ret=SearchHash(hashT, p);
	if (ret == -1)
		printf("表中无此值\n");
	else
		printf("找到了，下标为%d", ret);
	return 0;
}