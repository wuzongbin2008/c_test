// c10-3.h �����������������
#define MAX_NUM_OF_KEY 8 // �ؼ������������ֵ
#define RADIX 10 // �ؼ��ֻ�������ʱ��ʮ���������Ļ���
#define MAX_SPACE 1000

// alg10-11.cpp ��ʽ��������
typedef int InfoType; // �������������������
typedef int KeyType; // ����RedType���͵Ĺؼ���Ϊ����
typedef char KeysType; // ����ؼ�������Ϊ�ַ���

typedef struct  // ��¼����(ͬc10-1.h)
{
    KeyType key; // �ؼ�����
    InfoType otherinfo; // ����������
} RedType;

typedef struct  // ��̬����Ľ������
{
    KeysType keys[MAX_NUM_OF_KEY]; // �ؼ���
    InfoType otheritems; // ����������
    int next;
} SLCell;

typedef struct  // ��̬��������
{
    SLCell r[MAX_SPACE]; // ��̬����Ŀ����ÿռ䣬r[0]Ϊͷ���
    int keynum; // ��¼�ĵ�ǰ�ؼ��ָ���
    int recnum; //  ��̬����ĵ�ǰ����
} SLList;

typedef int ArrType[RADIX]; // ָ����������
