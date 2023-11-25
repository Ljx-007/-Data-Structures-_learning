#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//查找
//查找表是由同一类型的数据元素（或记录）构成的集合
//关键字--关键字是数据元素（或记录）中某个数据项的值，用它可以标识一个数据元素（或记录）
//  主关键字--主关键字可以唯一的标识一个记录（类似于准考证号，学号等）
//  次关键字可以表示若干记录（例如成绩，姓名等）
//平均查找长度ASL：
//  ASL= P1C1 + P2C2 + P3C3 +.....+ PiCi
//  Pi为查找表中第i个记录的概率（通常认为等概率P=1/n）
//  Ci为找到第i个记录所需的比较次数
//  n为记录的个数

//顺序查找
//顺序查找一般适用线性表的顺序存储结构和链式存储结构
//定义一个学生类型
typedef struct Student
{
	int age;       //年龄
	char name[10];   //姓名
	char id[10];   //学号
	char sex[5];   //性别
}Stu;
// 定义一个线性表
typedef struct
{
	Stu* S; 
	int len;  //表长
}SSTable;
//线性表的0号位置闲置，从1号位置开始存放，这样做的原因后面会解释
int Search_Seq(SSTable ST, char id[])
{
	for (int i = ST.len; i >= 1; i--)   //从后往前找，原因后面也会解释
	{
		if (strcmp(ST.S[i].id, id) == 0)  //如果有关键字（学号）与要查找的关键字（学号）相等，则返回该关键字所在的位置
			return i;
	}
	return 0;  //找不到返回0
}
//这样的查找过程每一次都需要比较两次，一次比较i是否>=1,一次比较关键字是否相等，可否改进呢？
//改进的办法为设置一个监视哨，即把要找的关键字存放在ST.S[0]的位置
// 然后从后往前一直找，如果都没找到要找的关键字，那么在0号位置就会找到刚才赋值的关键字，故返回下标0，返回下标0则代表没找到
//  这样，0号位置闲置，从后往前查找的原因都能解释清楚了
// 
//改进后的设置监视哨的查找算法
int Search_Seq2(SSTable ST, char id[])
{
	int i;
	//这里不能用ST.S[0].id= id ，因为ST.S[0].id是一个数组名，id是一个字符串，赋值不能用=，	//因为数组名或字符串是常量指针，无法直接赋值。
	strcmp(ST.S[0].id, id); //将要查找的id关键字放在线性表的0号位置
	// 从后往前查找线性表，如果线性表中有id与要查找的id相同，那么strcmp(ST.S[i].id, id)值为0
	//  条件值为0跳出循环，那么当下i所处的值就是要查找的id的位置，如果查到表头ST.S[0].id才查找到，说明原表中没有要查找的关键字，此时i=0
	for (i = ST.len; strcmp(ST.S[i].id, id); i--);  
	return i;   //若i=0说明没找到
}
//设置监视哨后的改进算法只需要比较一次，即表中关键字是否等于要查找的关键字，省去比较i>=0的步骤，因为查找到0位置时循环一定会停下来
// 实践证明，这个改进当ST.len>=1000时，一次查找的平均时间能减少一半
//ASL=(n+1)/2  时间复杂度为：O(n)

//二分查找
//二分查找要求线性表必须使用顺序存储结构，并且表中元素按关键字有序排列
int Search_Bin(SSTable ST, int a)
{
	int left = 1;
	int right = ST.len;
	int mid = (left + right) / 2;
	while (left <= right)
	{
		if (ST.S[mid].age == a)
			return mid;
		else if (ST.S[mid].age < a)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return 0;
}
//二分查找递归算法
int Search_BinRe(SSTable ST, int a, int left, int right)
{
	if (left > right)
		return 0;
	int mid = (left + right) / 2;
	if (ST.S[mid].age == a)
		return mid;
	else if (ST.S[mid].age < a)
		Search_BinRe(ST, a, mid + 1, right);
	else
		Search_BinRe(ST, a, left, mid - 1);
}
//二分查找的过程可以用二叉树来描述，把线性表的中间位置作为根，左子表和右子表作为左子树和右子树，这样的二叉树称为判定树
// 分别得出线性表中每个元素需要比较的次数，把这个次数放入二叉树中可以看出，查找的次数与 结点所在的层数 或者 与到根结点的路径上的结点数 相同
//若查找成功，比较次数最大不超过树的深度，树的深度为(log2 n) +1	，查找不成功比较次数也不超过树的深度(log2 n) +1
//所以平均查找长度为：
// ASL=log2(n+1)-1 ,时间复杂度为O(log2 n)
//优点：查找效率高   缺点：只适用有序表的顺序存储结构

//分块查找--索引顺序查找
//先建立一个索引表，把一个线性表分成几块，把每一块的第一个元素的指针和每一块中最大的元素放入索引表中
// 查找时先确定元素在哪一块，再采用顺序查找或二分查找在块的内部进行查找
//分块查找的时间复杂度比二分查找大，比顺序查找小，更接近于二分查找