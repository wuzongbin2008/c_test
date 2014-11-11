#include <stdio.h>

int n = 10;
int a[] = {2,3,1,5,7,4,9,8,6,0};
int cnt1 = 0,cnt2 = 0;

void bubble_sort(int a[],int n)
{
    int i,j,tmp;
    cnt1 = 0;
    cnt2 = 0;

    for(i = 0;i<n-1;i++){
        for(j = i+1;j<n; j++){
            cnt1++;
            if(a[j]>a[i]){
                cnt2++;
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }
    printf("compare count: %d,\tmove count: %d\n",cnt1,cnt2);
}
void bubble_sort2(int a[],int n)
{
    int i,j,tmp;
    cnt1 = 0;
    cnt2 = 0;

    for(i = 0; i < n-1; i++){
        for(j = n-1; j > i; j--){
            cnt1++;
            if(a[j-1] > a[j]){
                cnt2++;
                tmp = a[j-1];
                a[j-1] = a[j];
                a[j] = tmp;
            }
        }
    }
    printf("compare count: %d,\tmove count: %d\n",cnt1,cnt2);
}
void bubble_sort3(int a[],int n)
{
    int i,j,tmp,flag;

    flag = 1;
    cnt1 = 0;
    cnt2 = 0;

    for(i = 0; i < n-1 && flag; i++){
        for(j = n-1; j > i; j--){
            flag = 0;
            cnt1++;
            if(a[j-1] > a[j]){
                cnt2++;
                tmp = a[j-1];
                a[j-1] = a[j];
                a[j] = tmp;
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
            if(a[j] < a[min]){
                min = j;
            }
        }

        if(min != i){
            cnt2++;
            tmp = a[min];
            a[min] = a[i];
            a[i] = tmp;
        }
    }
    printf("compare count: %d,\tmove count: %d\n",cnt1,cnt2);
}

void sort_test(){

    int i;

    //bubble_sort(a,10);
    //bubble_sort2(a,10);
    //bubble_sort3(a,10);

    select_sort();
    for(i=0;i<n;i++){
        printf("a[%d]: %d\n",i,a[i]);
    }
}
