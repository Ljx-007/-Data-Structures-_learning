#pragma once
#include<stdio.h>
#include<math.h>
typedef struct
{
	double realpart;
	double imagpart;   //����һ�������ṹ��
}Complex;
void Creat(Complex* c, double a, double b);
void Multiply(Complex c1, Complex c2, Complex* c3);
void Add(Complex c1, Complex c2, Complex* c3);
void Div(Complex c1, Complex c2, Complex* c3);
void print(Complex c);