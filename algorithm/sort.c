#include <stdio.h>
#include "sort.h"

int n = 10;
int k[] = {2,3,1,5,0,4,9,8,7,6};
int cnt1 = 0,cnt2 = 0;

void sort_test(){

    int i;

    insert_sort();

    for(i=0;i<n;i++){
        printf("%d",k[i]);
    }
    printf("\n");
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

void bubble_sort(int k[],int n)
{
    int i,j,tmp;
    cnt1 = 0;
    cnt2 = 0;

    for(i = 0;i<n-1;i++){
        for(j = i+1;j<n; j++){
            cnt1++;
            if(k[j]>k[i]){
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

    for(i = 0; i < n-1; i++){
        for(j = n-1; j > i; j--){
            cnt1++;
            if(k[j-1] > k[j]){
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

    for(i = 0; i < n-1 && flag; i++){
        for(j = n-1; j > i; j--){
            flag = 0;
            cnt1++;
            if(k[j-1] > k[j]){
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

void select_sort()
{
    int i,j,min,tmp;
    cnt1 = 0;
    cnt2 = 0;

    for(i=0; i<n-1; i++)
    {
        min = i;
        for(j=i+1;j<n;j++)
        {
            cnt1++;
            if(k[j] < k[min]){
                min = j;
            }
        }

        if(min != i){
            cnt2++;
            tmp = k[min];
            k[min] = k[i];
            k[i] = tmp;
        }
    }
    printf("compare count: %d,\tmove count: %d\n",cnt1,cnt2);
}
