#define _CRT_SECURE_NO_WARNINGS 1
#include<string.h>
#include<stdio.h>
//�������ַ���
 //����˳��洢����
#define MAXSIZE 255  //�����ַ����ܴ�ŵ��������
typedef struct      
{
	char ch[MAXSIZE + 1];  //���һ���ֽڿռ�������'\0'
	int len;   //�ַ�������
}SString;
//���Ķ�ʽ˳��洢�ṹ
typedef struct
{
	char* ch;  //��̬�����ڴ棬�ڶ������٣����ַ����Ĵ洢�������
	int len;
}HString;

//������ʽ�洢
//��������һ�����ֻ���һ���ַ�����ôһ�����Ĵ洢�ܶȾ�̫С�ˣ����Բ���һ������Ŷ���ַ��İ취
//��������ʽ�ṹ��Ϊ������һ��һ����ַ��������������������洢�ܶȾʹ�������
#define CHUNKSIZE 80   //��Ĵ�С�����ж���
typedef struct Chunk    //��������
{
	char ch[CHUNKSIZE];
	struct Chunk* next;
}Chunk;
//�ٶ���һ���ṹ�����ʹ�Ŵ���ͷָ��βָ�루���贴�����ͳ���
typedef struct
{
	Chunk* head, * tail;   //����ͷָ��βָ��
	int len;         //���ĳ���
}LString;           //�ַ����Ŀ����ṹ

//����һ��ʹ��˳��洢�ṹ����ַ�����ʽ�洢��Ȼ����ĳЩ������һ���ļ��֮�������ܵ���˵����˳��洢�ṹ��
