#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//4.舞伴问题：
//舞伴配对问题，男队和女队的队头的人配对成舞伴。将男士和女士分为两队，队头元素配对，直到一个队为空为止。
//如果某队仍有等待配对者，则输出此队列排在队头的等待着的姓名，此人将是下一轮舞曲开始第一个可获得舞伴的人

//此问题由于男女是人数固定的，不会增加或减少，故采用顺序队列来解决
#define PEOPLEMAX 8   //定义队列最大人数
typedef struct   //定义一个“人”的类型
{
	char name[20];
	char sex;   //F代表女性，M代表男性
}Person;
typedef struct Queue  //定义顺序队列
{
	Person* base;
	int front;
	int rear;
}SqQueue;
//初始化队列
void InitQueue(SqQueue* Q)
{
	Q->base = (Person*)malloc(sizeof(Person)*PEOPLEMAX);
	if (!Q->base)
	{
		perror("malloc error");
		return;
	}
	Q->front = Q->rear = 0;
}
//入队
void EnQueue(SqQueue* Q,Person per)
{
	if ((Q->rear + 1) % PEOPLEMAX == Q->front)
	{
		printf("队满\n");
		return;
	}
	Q->base[Q->rear] = per;
	Q->rear = (Q->rear + 1) % PEOPLEMAX;
}
//出队
Person  DelQueue(SqQueue* Q)
{
	if (Q->front == Q->rear)
	{
		printf("队空\n");
		return;
	}
	Person p = Q->base[Q->front];
	Q->front = (Q->front + 1) % PEOPLEMAX;
	return p;
}
//判断队是否为空
int IsEmpty(SqQueue* Q)
{
	if (Q->front == Q->rear)
		return 1;
	else
		return 0;
}
//获取队头元素
Person GetTop(SqQueue* Q)
{
	if (Q->front == Q->rear)
	{
		printf("队空\n");
		return;
	}
	Person peo = Q->base[Q->front];
	return peo;
}
//将舞会的人分成男女两队
void DancerPatner(Person dancers[], int num)
{
	SqQueue Mdancers, Fdancers;
	InitQueue(&Mdancers);
	InitQueue(&Fdancers);
	//让舞者分别入男女两队
	for (int i = 0; i < num; i++)
	{
		if (dancers[i].sex == 'M')
			EnQueue(&Mdancers, dancers[i]);
		else
			EnQueue(&Fdancers, dancers[i]);
	}
	printf("互为舞伴的两人：\n");
	while (!IsEmpty(&Mdancers) && !IsEmpty(&Fdancers))  //男队女队都没空的话
	{
		Person man = DelQueue(&Mdancers);  //队头的男士出队与队头的女士匹配
		Person lady = DelQueue(&Fdancers);  //队头女士出队
		printf("男：%s\t女：%s\n", man.name, lady.name);
	}
	if (!IsEmpty(&Mdancers)) //如果女队空了
	{
		Person peo = GetTop(&Mdancers);  //获取在队头的男士
		printf("下一轮舞曲最先获得舞伴的男士是：%s\n", peo.name);
	}
	else           //如果男队空了
	{
		Person peo = GetTop(&Fdancers);  //获取在队头的女士
		printf("下一轮舞曲最先获得舞伴的女士是：%s\n", peo.name);
	}

}
int main()
{
	int num = 10;    //参加舞会的人数
	Person dancers[10] = { 
		{"张三",'M'},{"王五",'M'},{"李四",'M'},{"赵二",'M'},{"杨一",'M'},{"梁六",'M'},
		{"赵丽颖",'F'},{"马冬梅",'F'},{"陈琪琪",'F'},{"林莉莉",'F'}};
	DancerPatner(dancers, num);
	return 0;
}
