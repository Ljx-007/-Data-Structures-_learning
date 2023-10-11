#define _CRT_SECURE_NO_WARNINGS 1
#include"test.h"
int main()
{
	Complex z1, z2, z3, z4, z;  
	Creat(&z1, 8.0, 6.0);  //创建复数
	Creat(&z2, 4.0, 3.0);
	print(z1);
	print(z2);
	Multiply(z1, z2, &z3);  //复数的乘法
	printf("z1*z2=%lf+%lfi\n", z3.realpart, z3.imagpart);
	Add(z1, z2, &z4); //复数的加法
	printf("z1+z2=%lf+%lfi\n", z4.realpart, z4.imagpart);
	Div(z3, z4, &z);  //复数的除法
	printf("z1*z2/(z1+z2)=%lf+%lfi", z.realpart, z.imagpart);
	return 0;
}