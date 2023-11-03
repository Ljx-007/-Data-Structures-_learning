#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>
//树的存储结构
// 
//一、双亲表示法
//用一组连续的存储单元存储树的结点，每个结点除了数据以外，还有一个双亲域指向该结点的双亲。所以这样的连续存储单元应是一个结构数组
//例：
// 数组下标: 0 1 2 3 4 5 6 7 8 9 
//     数据: R A B C D E F G H K    （按结点的编号进行排列）
//    双亲: -1 0 0 0 1 1 3 6 6 6    (-1代表结点R没有双亲，A，B，C的双亲域都为0，说明他们的双亲是下标为0的数据R，以此类推。。）
typedef struct PTNode
{
	char data;   //假设数据类型为char
	int parent;     //双亲域
}PTNode;
#define SIZE 10  //定义数组的最大个数,即结点个数
typedef struct Tree
{
	PTNode tree[SIZE];
	int r, n;   //根结点的位置（下标r）和根结点个数
}Tree;
//双亲表示法：找双亲容易，找孩子难

//二、孩子表示法
// 将每一个结点按照编号排列存放到一个数组中，然后将每一个结点的第一个孩子（从左到右）的编号用链表存储
//  为了让结点和其孩子在数组里产生联系，该数组应为一个结构数组，存放结点数据的同时，还要有一个指针域来存放结点孩子的链表
//   该链表中存储的不是数据本身，而是孩子结点在数组中的结点编号
//例：
//数组下标    数据    指针域    
//   0         A        [ ]-> 3 -> 5 -> NULL    （A的孩子为D,E)
//   1         B        NULL
//   2         C        [ ]-> 6 -> NULL
//   3         D        NULL
//   4         R        [ ]-> 0 -> 1 -> 2 -> NULL      R为根结点，其位置可以自己决定，不一定下标为4，可以自己决定在哪里
//   5         E        NULL
//   6         F        [ ]-> 7 -> 8 -> 9 -> NULL
//   7         G        NULL
//   8         H        NULL
//   9         I        NULL
//定义孩子链表
typedef struct CTNode   
{
	int child;   //孩子的编号
	struct CTNode* next;
}CTNode;
//定义结构数组的结构类型
typedef struct TreeNode
{
	char data;    //结点数据
	CTNode* firstchild;    //结点的孩子链表
}TreeNode;
//定义结构数组
typedef struct Tree
{
	TreeNode arr[SIZE];    
	int r, n;    //r为根结点位置
};
//孩子表示法：找孩子容易，找双亲难
//为了让找双亲也变得容易，结合前面双亲表示法的办法，可以再在结构数组的结构类型中增加一个双亲域指向结点的双亲
typedef struct TreeNode2
{
	int parent;   //增加一个双亲域
	char data;
	CTNode* firstchild;
}TreeNode2;


//三、孩子兄弟表示法
//用二叉链表作为树的存储结构，但不同的是，二叉树的链表左右指针域分别指向左右孩子；树的二叉链表左指针指向第一个孩子结点，右指针指向下一个兄弟结点
typedef struct CSnode
{
	char data;  //结点本身的数据
	struct CSnode* firstchild, * nextsibling;    //两个指针域，一个指向第一个孩子，另一个指向下一个兄弟
}CSnode,*CSTree;
//孩子兄弟表示法：找孩子和兄弟容易，找双亲难
// 为了解决找双亲难的问题，还可以再加上一个双亲指针域，令其指向该结点的双亲