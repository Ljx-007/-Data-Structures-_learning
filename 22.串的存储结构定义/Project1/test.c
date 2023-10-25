#define _CRT_SECURE_NO_WARNINGS 1
#include<string.h>
#include<stdio.h>
//串就是字符串
 //串的顺序存储定义
#define MAXSIZE 255  //定义字符串能存放的最大容量
typedef struct      
{
	char ch[MAXSIZE + 1];  //多加一个字节空间拿来放'\0'
	int len;   //字符串长度
}SString;
//串的堆式顺序存储结构
typedef struct
{
	char* ch;  //动态开辟内存，在堆区开辟，让字符串的存储更加灵活
	int len;
}HString;

//串的链式存储
//如果链表的一个结点只存放一个字符，那么一个结点的存储密度就太小了，所以采用一个结点存放多个字符的办法
//这样的链式结构称为块链，一块一块的字符串再链接起来，这样存储密度就大大提高了
#define CHUNKSIZE 80   //块的大小可自行定义
typedef struct Chunk    //块链定义
{
	char ch[CHUNKSIZE];
	struct Chunk* next;
}Chunk;
//再定义一个结构体类型存放串的头指针尾指针（按需创建）和长度
typedef struct
{
	Chunk* head, * tail;   //串的头指针尾指针
	int len;         //串的长度
}LString;           //字符串的块链结构

//我们一般使用顺序存储结构存放字符，链式存储虽然对于某些操作有一定的简便之处，但总的来说不如顺序存储结构灵活。
