#define _CRT_SECURE_NO_WARNINGS 1	
//ʮ������---����ͼ����һ����ʽ�洢
//�ڽӱ��ʾ���������ж϶���֮���Ƿ��бߣ��Ҳ������ж���ȱߣ���������ʮ������
//ʮ��������Կ��ɽ��ڽӱ�����ڽӱ��������õ���һ��������ʮ�������У���������ͼ��ÿһ������ÿһ�����㶼��һ������ʾ
//��ʮ�������У�����㻡ͷ��ͬ���ӳɵ�����Ϊ���ȱ߱���β��ͬ���ӳɵ�����Ϊ��ȱ߱�
#define MVNum 100
typedef struct Vexnode    //���嶥�����
{
	char v;    //������Ϣ
	struct Arcnode* firstin;    //��ȱ߱�
	struct Arcnode* firstout;   //���ȱ߱�
}Vexnode;
typedef struct Arcnode        //���廡���
{
	int headvex;   //����ͷ����
	int tailvex;      //����β����
	struct Arcnode* hlink;    //��ͷ��ͬ�ı߱������ȱ߱�
	struct Arcnode* tlink;    //��β��ͬ�ı߱�����ȱ߱�
	int w;       //Ȩֵ
}Arcnode;
typedef struct
{    //��������ͼ
	Vexnode Vlist[MVNum];
	int vexnum, arcnum;
}OLGraph;

//�ڽӶ��ر�---����ͼ����һ����ʽ�洢
//��������ͼ���ڽӱ�ÿһ���߶�Ҫ�������Σ������˿ռ临�Ӷȣ����ԣ��ڽӶ��ر�������ͼ��ÿ����ֻ�÷���һ��
//���ڽӱ����ƣ��ڽӶ��ر�Ķ�����䣬�����Ƕ�����Ϣ�ͱ߱�ָ����
//�仯���Ǳ߱�������ݣ��߱�������������������������������Ϣ���Լ�����������һ������ı߽��ָ�����������һ������ı߽��ָ��
// ���⻹�������Ȩֵ���ͱ�ǡ�����������жϸñ��Ƿ񱻷��ʹ�
typedef struct Vexnode    //���嶥���
{
	char v;    //������Ϣ
	struct Arcnode* firstedge;   //��������ĵ�һ���ߵĽ��ָ��
}Vexnode;
typedef struct Arcnode         //����߱���
{
	int mark;    //���ʱ�־
	int ivex;    //�ñ������������������Ϣ
	int jvex;
	struct Arcnode* ilink, * jlink;     //�����ڸñ���������������������ıߵĽ��ָ��
	int w;  //Ȩֵ
}Arcnode;
typedef struct       //��������ͼ
{
	Vexnode Vlist[MVNum];   //���������
	int vexnum, arcnum;     //�������ͱ���
}AMLGraph;