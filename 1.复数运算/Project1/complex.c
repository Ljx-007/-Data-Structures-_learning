#include"test.h"
void Creat(Complex* c, double a, double b)
{
	c->realpart = a;
	c->imagpart = b;
}
void Multiply(Complex c1, Complex c2, Complex* c3)
{
	c3->realpart = c1.realpart * c2.realpart - c1.imagpart * c2.imagpart;
	c3->imagpart = c1.realpart * c2.imagpart + c1.imagpart * c2.realpart;
}
void Add(Complex c1, Complex c2, Complex* c3)
{
	c3->realpart = c1.realpart + c2.realpart;
	c3->imagpart = c1.imagpart + c2.imagpart;
}
void Div(Complex c1, Complex c2, Complex* c3)
{
	c3->realpart = (c1.realpart * c2.realpart + c1.imagpart * c2.imagpart) / (pow(c2.realpart, 2) + pow(c2.imagpart, 2));
	c3->imagpart=(c1.imagpart*c2.realpart-c1.realpart*c2.imagpart)/ (pow(c2.realpart, 2) + pow(c2.imagpart, 2));
}
void print(Complex c)
{
	printf("¸´Êýz1 = % lf + % lfi\n", c.realpart, c.imagpart);
}