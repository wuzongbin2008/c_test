#include <stdio.h>
#include"c1.h"
#include"c10-3.h"

// alg10-11.cpp 链式基数排序
typedef int InfoType; // 定义其它数据项的类型
typedef int KeyType; // 定义RedType类型的关键字为整型
struct RedType // 记录类型(同c10-1.h)
{
    KeyType key; // 关键字项
    InfoType otherinfo; // 其它数据项
};
typedef char KeysType; // 定义关键字类型为字符型

void radix_sort();
void InitList(SLList &L,RedType D[],int n);
int ord(char c);
void Distribute(SLCell r[],int i,ArrType f,ArrType e);
int succ(int i);
void Collect(SLCell r[],ArrType f,ArrType e);
void printl(SLList L);
void RadixSort(SLList &L);
void print(SLList L);
void Sort(SLList L,int adr[]); // 改此句(类型)
void Rearrange(SLList &L,int adr[]);

void recursion_merge_sort(int k[], int n);
void iteration_merge_sort(int k[], int n);
void merging(int *list1, int size1, int *list2, int size2);
void mergeAB(int c[],int a[],int n,int b[],int m);
int less(int a,int b);

void simple_select_sort();

void insert_sort();
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
