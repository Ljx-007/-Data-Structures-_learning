#pragma once
#include<stdio.h>
#include<stdlib.h>
typedef struct Exp_Coe  //���ָ����ϵ��
{
	int e;
	int c;
} Exp_Coe;
typedef struct SqList  //����һ�����Ա�
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