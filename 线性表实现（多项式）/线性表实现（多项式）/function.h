#pragma once
#include<stdio.h>
#include<stdlib.h>
#define INIT_CAP 3
#define DEBUG
typedef struct Exp_Coe  //存放指数与系数
{
	int e;
	int c;
} Exp_Coe;
typedef struct SqList  //创建一个线性表
{
	Exp_Coe* data;
	int len;
	int capacity;
}SqList;
enum choose
{
	EXIT,
	ADD,
	DEL,
	SEARCH,
	MODIFY,
	SHOW,
	SORT,
	CLEAR
};
int InitList(SqList* L);
void ClearList(SqList* pL);
void DeletList(SqList* pL);
void GetElem(const SqList* pL);
void Add(SqList* pL);
void show(const SqList* pL);
void Del(SqList* pL);
void Modify(SqList* pL);
int check_num(SqList* pL);
void save(SqList *pL);
void sort(SqList* pL);