#define _CRT_SECURE_NO_WARNINGS 1
#include"test.h"
int main()
{
	Complex z1, z2, z3, z4, z;  
	Creat(&z1, 8.0, 6.0);  //��������
	Creat(&z2, 4.0, 3.0);
	print(z1);
	print(z2);
	Multiply(z1, z2, &z3);  //�����ĳ˷�
	printf("z1*z2=%lf+%lfi\n", z3.realpart, z3.imagpart);
	Add(z1, z2, &z4); //�����ļӷ�
	printf("z1+z2=%lf+%lfi\n", z4.realpart, z4.imagpart);
	Div(z3, z4, &z);  //�����ĳ���
	printf("z1*z2/(z1+z2)=%lf+%lfi", z.realpart, z.imagpart);
	return 0;
}