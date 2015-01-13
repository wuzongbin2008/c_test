// c1.h (程序名)
#include<string.h>
#include<ctype.h>
#include<malloc.h> // malloc()等
#include<limits.h> // INT_MAX等
#include<stdio.h> // EOF(=^Z或F6),NULL
#include<stdlib.h> // atoi()
//#include<io.h> // eof()
#include<math.h> // floor(),ceil(),abs()
// #include<process.h> // exit()
//#include<iostream.h> // cout,cin

// 函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
// c10-3.h 基数排序的数据类型
#define MAX_NUM_OF_KEY 8 // 关键字项数的最大值
#define RADIX 10 // 关键字基数，此时是十进制整数的基数
#define MAX_SPACE 1000
 // c9.h 对两个数值型关键字的比较约定为如下的宏定义
 #define EQ(a,b) ((a)==(b))
 #define LT(a,b) ((a)<(b))
 #define LQ(a,b) ((a)<=(b))
// #define OVERFLOW -2 因为在math.h中已定义OVERFLOW的值为3,故去掉此行

typedef int Status; // Status是函数的类型,其值是函数结果状态代码，如OK等
typedef int Boolean; // Boolean是布尔类型,其值是TRUE或FALSE
// alg10-11.cpp 链式基数排序
typedef int InfoType; // 定义其它数据项的类型
typedef int KeyType; // 定义RedType类型的关键字为整型
typedef char KeysType; // 定义关键字类型为字符型
// c10-1.h 待排记录的数据类型
#define MAXSIZE 20 // 一个用作示例的小顺序表的最大长度
typedef int KeyType; // 定义关键字类型为整型

typedef struct  // 记录类型
{
    KeyType key; // 关键字项
    InfoType otherinfo; // 其它数据项，具体类型在主程中定义
} RedType;

typedef struct  // 顺序表类型
{
    RedType r[MAXSIZE+1]; // r[0]闲置或用作哨兵单元
    int length; // 顺序表长度
} SqList;

typedef struct  // 静态链表的结点类型
{
    KeysType keys[MAX_NUM_OF_KEY]; // 关键字
    InfoType otheritems; // 其它数据项
    int next;
} SLCell;

typedef struct  // 静态链表类型
{
    SLCell r[MAX_SPACE]; // 静态链表的可利用空间，r[0]为头结点
    int keynum; // 记录的当前关键字个数
    int recnum; //  静态链表的当前长度
} SLList;
typedef int ArrType[RADIX]; // 指针数组类型


void radix_sort();
void InitList(SLList *L,RedType D[],int n);
int ord(char c);
void Distribute(SLCell r[],int i,ArrType f,ArrType e);
int succ(int i);
void Collect(SLCell r[],ArrType f,ArrType e);
void printl(SLList *L);
void RadixSort(SLList *L);
void print(SLList *L);
void Sort(SLList *L,int adr[]); // 改此句(类型)
void Rearrange(SLList *L,int adr[]);

void recursion_merge_sort(int k[], int n);
void iteration_merge_sort(int k[], int n);
void merging(int *list1, int size1, int *list2, int size2);
void mergeAB(int c[],int a[],int n,int b[],int m);
int less(int a,int b);

void simple_select_sort();

void straight_insert_sort();
void binary_insert_sort();
void shell_sort();

void quick_sort(int k[],int n);
void qk_sort(int k[],int low ,int high);
int partition(int k[],int low, int high);
void swap(int k[],int low,int high);
void bubble_sort(int a[],int n);
void bubble_sort2(int a[],int n);
void bubble_sort3(int a[],int n);

void sort_test();
void print_k(int k[], int n);
