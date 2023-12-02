#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//树表的查找
//线性表的查找适用于静态查找表，如果删除插入操作频繁时，则需用到树表

//二叉排序树(Binary Sort Tree)
//二叉排序树定义：
//1.若左子树不为空，则左子树上所有结点的值均小于它的根结点的值
//2.若右子树不为空，则右子树上所有结点的值均大于等于它的根结点的值
//3.它的左、右子树也分别为二叉排序树
//对一个非空的二叉排序树进行中序遍历，得到的遍历序列为一个按关键字排列的递增有序序列
//因为二叉树中序遍历为左根右，正好符合二叉排序树从左到右变大的顺序

//二叉排序树存储结构
typedef struct   //定义一个人的复杂类型
{
	char name[10];
	int age;
	char sex[5];
}People;
typedef struct BSTnode   //定义二叉排序树
{
	People peo;
	struct BSTnode* lchild, * rchild;
}BSTnode,*BSTree;
//二叉排序树的查找(递归算法）
BSTree SearchBST(BSTree T, int age)
{
	if ((!T) || T->peo.age == age)  //如果为空或者找到了，那么就返回当前结点指针
		return T;
	else if (T->peo.age < age)    //与关键字age比较，如果小于，就去左子树找
		return SearchBST(T->lchild, age);
	else
		return SearchBST(T->rchild, age);  //如果大于，就去右子树找
}
//分析二叉排序树的平均查找长度ASL和时间复杂度O(n)与二叉排序树的形态有关
// 从二叉排序树中我们可以找到规律，每个结点的比较次数与结点所在的层次数（深度）相等
//如果二叉排序树的形态是均衡的，即最好情况，那么平均查找长度为log2 (n+1) -1  时间复杂度为O(log2 n)
//如果二叉排序树的形态不均衡，为单支树，即最坏情况，那么ASL=（n+1)/2,时间复杂度为O(n)
//可知形态不均衡的二叉树查找效率不如形态均衡的二叉树，所以我们要对形态不均衡的二叉树做“平衡化”处理，平衡化后的二叉排序树称为平衡二叉树

//二叉排序树的插入
//与二叉树的查找类似，同样是将要插入的结点的关键字与二叉树中的结点的关键字进行比较
// 若二叉排序树为空，则将该结点作为根结点插入到空树中
//  否则继续在左右子树上查找，如果已经有了该关键字，则不再插入。
//    如果没有，则查找至某个叶结点的左子树或右子树为空为止，并将该结点插入至该叶结点的左孩子或者右孩子
//注：插入的结点为叶子结点
void InsertBST(BSTree* T, People e)
{    //若二叉排序树中不存在关键字等于e.age的结点
	if (!(*T))
	{
		BSTnode* S = malloc(sizeof(BSTnode));
		S->peo = e;
		S->lchild = S->rchild = NULL;
		*T = S;
	}
	else if ((*T)->peo.age < e.age)
		InsertBST(&(*T)->lchild, e);
	else if((*T)->peo.age>e.age)
		InsertBST(&(*T)->rchild, e);
}
//二叉树的生成
void CreatBST(BSTree* T)
{
	*T = NULL;
	char c;
	printf("将年龄输入0可退出\n");
	printf("请输入结点数据（姓名，年龄，性别）:");
	People e;
	scanf("%s %d %s",e.name, &e.age, e.sex);
	while (e.age != 0)    //如果不想在继续输入结点，那么年龄输入为0时则可以退出
	{
		InsertBST(T, e);  //将输入好的数据插入到二叉树中
		while ((c = getchar()) != '\n');
		printf("请输入结点数据（姓名，年龄，性别）:");
		scanf("%s %d %s", e.name, &e.age, e.sex);
	}
}
//不同的输入序列会造成二叉排序树的不同形态，也许会出现单支树的情况
//二叉排序树的删除 -- 删除后要保持中序遍历序列依然是有序序列
//1.删除的结点为叶结点，没有左右子树：
//  直接删除该结点，修改双亲指针即可
//2.删除的结点只有左子树或者只有右子树：
//  直接将该结点删除，并把双亲与其子树相连
//3.删除的结点左右子树都有
//  方法（1）：
//   用二叉排序树中序遍历后的有序序列的前驱代替该结点，前驱则是该结点左子树中的最大值，代替后将前驱结点删除，删除办法参照上述三种情况删除即可
//  方法（2）：
//  用二叉树中序遍历后的有序序列的后继代替该结点，后继则是该结点右子树的最小值，代替后将后继结点删除，删除办法也参照上述三种情况删除即可。
void DeleteBST(BSTree* T, People e)
{
	BSTnode* p = *T;   //p指向根结点
	BSTnode* f = NULL;
	while (p)  
	{   //遍历二叉树
		if (p->peo.age == e.age)    //如果二叉排序树中有要删除的结点，则跳出循环
			break;
		//如果这一次循环没有找到要删除的结点，那则按照关键字与结点关键字的大小比较来决定遍历左子树还是右子树
		f = p;  //f为p的双亲结点
		if (p->peo.age < e.age)
			p = p->lchild;
		else
			p = p->rchild;
	}
	if (!p)   //如果遍历到最后都没找到，则p为空，p为空直接返回，说明二叉树中没有要删除的元素
		return;
	BSTnode* q = p;  
	//被删出的结点p左右子树均不为空
	if ((p->lchild) && (p->rchild))
	{   //s为我们要寻找的p结点的直接前驱
		BSTnode* s = p->lchild;   //直接前驱在p的左子树中寻找，所以s=p->lchild
		while (s->rchild)
		{  //p的直接前驱是p左子树中最大的值，而右子树比左子树和根结点都要大，所以一直往右子树找，直到右子树为空，找到的值即为最大值
			q = s;   //q为s结点的双亲
			s = s->rchild;
		}
		//s是找到p的左子树中的最大值，是p的直接前驱，s右子树必为空
		p->peo = s->peo;  //用s的值代替p的值
		//代替后把s结点删除
		if (q == p)    //如果q=p，说明p的左孩子就是左子树中的最大值，所以双亲q直接连接s的左子树，这样s就被删除了
			q->lchild = s->lchild;
		else    //如果q!=p，说明p的左孩子不是左子树中的最大值，而另有s结点，此时s结点一定是双亲的右孩子，如果他是双亲的左孩子，那么s结点就不是最大值
			//所以要删除s结点，则把s的左子树连接到双亲的右孩子。
			q->rchild = s->lchild;
		//最后删除s结点即可
		free(s), s = NULL;
		return;
	}
	//如果要删除结点p没有左子树
	else if (!p->lchild)
		q = p->rchild;  //q指向p的右子树
	//删除结点p没有右子树
	else if (!p->rchild)
		q = p->lchild;  //q指向p的左子树
	if (!f)  //如果被删除的结点是根结点，根结点没有双亲，所以f=NULL
		T = q;  //让根结点T直接为q结点即可，这是根结点只有左子树或者右子树的情况，根结点左右子树都有的情况上面已经讨论过了
	else if (p == f->lchild)   //如果删除结点p是双亲的左孩子
		f->lchild = q;  //那么就将双亲的左孩子与q连接，q指向p的唯一的一棵子树
	else if (p == f->rchild)// 同理，当要删除的结点p为双亲的右孩子
		f->rchild = q; // 则将双亲的右孩子与q连接，
	free(p), p = NULL;   //这里还包含了一种情况，即删除的结点p为叶结点，如果结点p为叶结点，那么直接删掉就好了，不需要其他操作
}
int main()
{
	BSTree T;
	CreatBST(&T);
	return 0;
}