#pragma once
#include<stdio.h>
#include<stdlib.h>
typedef struct Exp_Coe  //存放指数与系数
{
	int e;
	int c;
} Exp_Coe;
typedef struct SqList  //创建一个线性表
{
	Exp_Coe* data;
	int len;
}SqList;
int InitList(SqList* L);
void ClearList(SqList* pL);
void DeletList(SqList* pL);
void GetElem(const SqList* pL, int num);
void Add(SqList* pL);
void show(SqList* pL);