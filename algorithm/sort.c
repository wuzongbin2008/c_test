#include <stdio.h>
#include "sort.h"

int n = 10;
int k[] = {2,3,1,5,0,4,9,8,7,6};
int a[] = {3,5,8};
int b[] = {4,7,9,10};
int c[7];
int d[3] = {1,6,2};
int t[10];
int cnt1 = 0,cnt2 = 0;

void sort_test()
{

    int i;

    iteration_merge_sort(k, n);
    printf("\nsort result:\n");
    for( i=0; i < n; i++)
    {
        printf("%d\t", k[i]);
    }
    printf("\n");
}

//merge sort
void iteration_merge_sort(int k[], int n)
{
    int i, left_min, left_max, right_min, right_max,next, j, m;
    int *tmp = (int *)malloc(n * sizeof(int));

    for(i = 1; i < n; i *= 2)
    {
        for(left_min = 0; left_min < n - i; left_min = right_max)
        {
            right_min = left_max = left_min + i;
            right_max = left_max + i;

            if(right_max > n) right_max = n;

            next = 0;
            int tmp2;
            while(left_min < left_max && right_min < right_max)
            {
                if(k[left_min] < k[right_min])
                {
                    tmp2 = k[left_min++];
                    tmp[next++] = tmp2;
                }
                else
                {
                    tmp2 = k[right_min++];
                    tmp[next++] = tmp2;
                }
            }

            while(left_min < left_max)
            {
                printf("left_min: %d\tleft_max: %d\nright_min: %d\tright_max: %d\n\n", left_min, left_max, right_min, right_max);
                k[--right_min] = k[--left_max];
            }

            //print_k(tmp, next);
            while(next > 0)
            {
                m = tmp[--next];
                k[--right_min] = m;
            }

            printf("\ni= %d:\t", i);
            for( j = 0; j < 10; j++)
            {
                printf("%d\t", k[j]);
            }
            printf("\n");
        }
    }
}
void recursion_merge_sort(int k[],int n)
{
    if (n > 1)
    {
        int *list1 = k;
        int list1_size = n/2;
        int *list2 = k + n/2;
        int list2_size = n - list1_size;

        recursion_merge_sort(list1, list1_size);
        recursion_merge_sort(list2, list2_size);

        merging(list1, list1_size, list2, list2_size);

    }
}
void merging(int *list1, int size1, int *list2, int size2)
{
    int i,j,k,m,temp[n];
    i = j = k = 0;

    while(i < size1 && j < size2)
    {
        if(list1[i] < list2[j])
        {
            temp[k++] = list1[i++];
        }
        else
        {
            temp[k++] = list2[j++];
        }
    }
    while(i < size1)
    {
        temp[k++] = list1[i++];
    }
    while(j < size2)
    {
        temp[k++] = list2[j++];
    }
    for(m = 0; m < (size1 + size2); m++)
    {
        list1[m] = temp[m];
    }
}
void mergeAB(int c[],int a[],int n,int b[],int m)
{
    int i,j,k;
    for(i=0,j=0,k=0; k < n+m ; k++)
    {
        if(i == n )
        {
            c[k] = b[j++];
            continue;
        }
        if(j == m )
        {
            c[k] = a[i++];
            continue;
        }
        c[k] = (less(a[i],b[j])) ? a[i++] : b[j++];
    }
}
int less(int a,int b)
{
    if(a < b)
    {
        //printf("less\n");
        return 1;
    }
    else
    {
        return 0;
    }
}

//insert sort
void shell_sort()
{
    int i,j,tmp;
    int gap = n;

    do
    {
        gap = gap/3+1;
        for(i=gap; i<n; i++)
        {
            tmp = k[i];
            printf("i=%d\tk[i]=%d\tk[i-1]=%d\ttmp = %d\n",i,k[i],k[i-1],tmp);
            if(k[i] < k[i-gap])
            {
                printf("\ni=%d\ttmp = %d\n",i,tmp);

                for(j=i-gap; k[j]>tmp; j-=gap)
                {
                    printf("i=%d\tj=%d\tk[j]:%d\tk[j+1]: %d\n",i,j,k[j],k[j+1]);
                    k[j+gap] = k[j];
                }
                printf("j=%d\tk[j]=%d\n",j,k[j]);
                k[j+gap] = tmp;
                printf("\n");
            }
        }
    }
    while(gap > 1);
}
void insert_sort()
{
    int i,j,tmp;

    for(i=1; i<n; i++)
    {
        tmp = k[i];
        printf("i=%d\tk[i]=%d\tk[i-1]=%d\ttmp = %d\n",i,k[i],k[i-1],tmp);
        if(k[i] < k[i-1])
        {
            printf("\ni=%d\ttmp = %d\n",i,tmp);

            for(j=i-1; k[j]>tmp; j--)
            {
                printf("i=%d\tj=%d\tk[j]:%d\tk[j+1]: %d\n",i,j,k[j],k[j+1]);
                k[j+1] = k[j];
            }
            printf("j=%d\tk[j]=%d\n",j,k[j]);
            k[j+1] = tmp;
            printf("\n");
        }
    }
}

//select sort
void select_sort()
{
    int i,j,min,tmp;
    cnt1 = 0;
    cnt2 = 0;

    for(i=0; i<n-1; i++)
    {
        min = i;
        for(j=i+1; j<n; j++)
        {
            cnt1++;
            if(k[j] < k[min])
            {
                min = j;
            }
        }

        if(min != i)
        {
            cnt2++;
            tmp = k[min];
            k[min] = k[i];
            k[i] = tmp;
        }
    }
    printf("compare count: %d,\tmove count: %d\n",cnt1,cnt2);
}

//swap sort
void quick_sort(int k[],int n)
{
    qk_sort(k,0,n-1);
}
void qk_sort(int k[], int low , int high)
{
    int point;
    if(low < high)
    {
        point = partition(k, low, high);
        printf("point: %d\n", point);
        qk_sort(k, low, point-1);
        qk_sort(k, point+1, high);
    }
}
int partition(int k[],int low, int high)
{
    int point;
    point = k[low];

    while(low < high)
    {
        while(low < high && k[high] >= point)
        {
            high--;
        }
        swap(k,low,high);
        while(low < high && k[low] <= point)
        {
            low++;
        }
        swap(k,low,high);
    }

    return low;
}
void swap(int k[],int low,int high)
{
    int temp;

    temp = k[low];
    k[low] = k[high];
    k[high] = temp;
}
void bubble_sort(int k[],int n)
{
    int i,j,tmp;
    cnt1 = 0;
    cnt2 = 0;

    for(i = 0; i<n-1; i++)
    {
        for(j = i+1; j<n; j++)
        {
            cnt1++;
            if(k[i] > k[j])
            {
                cnt2++;
                tmp = k[i];
                k[i] = k[j];
                k[j] = tmp;
            }
        }
    }
    printf("compare count: %d,\tmove count: %d\n",cnt1,cnt2);
}
void bubble_sort2(int k[],int n)
{
    int i,j,tmp;
    cnt1 = 0;
    cnt2 = 0;

    for(i = 0; i < n-1; i++)
    {
        for(j = n-1; j > i; j--)
        {
            cnt1++;
            if(k[j-1] > k[j])
            {
                cnt2++;
                tmp = k[j-1];
                k[j-1] = k[j];
                k[j] = tmp;
            }
        }
    }
    printf("compare count: %d,\tmove count: %d\n",cnt1,cnt2);
}
void bubble_sort3(int k[],int n)
{
    int i,j,tmp,flag;

    flag = 1;
    cnt1 = 0;
    cnt2 = 0;

    for(i = 0; i < n-1 && flag; i++)
    {
        for(j = n-1; j > i; j--)
        {
            flag = 0;
            cnt1++;
            if(k[j-1] > k[j])
            {
                cnt2++;
                tmp = k[j-1];
                k[j-1] = k[j];
                k[j] = tmp;
                flag = 1;
            }
        }
    }
    printf("compare count: %d,\tmove count: %d\n",cnt1,cnt2);
}

void print_k(int a[], int n)
{
    int i;

    for( i=0; i < n; i++)
    {
        printf("%d\t", a[i]);
    }
    printf("\n");
}
