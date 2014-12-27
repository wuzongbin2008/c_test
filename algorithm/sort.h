#include <stdio.h>

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
