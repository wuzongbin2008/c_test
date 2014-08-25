#include <stdio.h>
#include <stdlib.h>

#include "matrix_opt.h"

void matrix_multiply()
{
     int a[2][2]={{ 1, 1},{ 2, 0}};
    int b[2][3]={{ 0, 2, 3},{ 1, 1, 2}};
    // int i, j, k, s[2][3];
    //问题出现在这里，s[2][3]没有赋初值，看得出来吗。
    //而你在下面的循坏里面，就直接用了 ==>s[i][j]=s[i][j]+a[i][k]*b[k][j];
    //将代码改成下面的，就得到你要的结果了
    //其他地方没有出现什么错误。修改过后，就是你要的答案了
    int i, j, k, s[2][3]={0};
    for(i=0; i<2; i++)
    {
        for( j=0; j<3; j++)
        {
            for( k=0; k<2; k++)
            {
                s[i][j]=s[i][j]+a[i][k]*b[k][j];
            }
        }
    }
    for(i=0;i<2;i++)
    for(j=0;j<3;j++)
    {
        printf("%d\t",s[i][j]);
        if(j==2)
        printf("\n");
    }

}

void trmul(double a[][5],double b[][3],int m,int n,int k,double c[][3])
{
    int i,j,l,u;
    double at,bt,ct;
    //m=4 k=3 n=5
    for (i=0; i<m; i++)
    {
        for (j=0; j<k; j++)
        {
            ct = c[i][j] = 0.0;
            for (l=0; l<n; l++){
                at = a[i][l];
                bt = b[l][j];

                ct=ct+at*bt;
            }
            printf("%e\t",ct);
        }
        printf("\n");
    }
}

void print_multiply(){
    int i,j;
    double a[4][5]= {
        {1.0,3.0,-2.0,0.0,4.0},
        {-2.0,-1.0,5.0,-7.0,2.0},
        {0.0,8.0,4.0,1.0,-5.0},
        {3.0,-3.0,2.0,-4.0,1.0}
    };
    double b[5][3]= {
        {4.0,5.0,-1.0},
        {2.0,-2.0,6.0},
        {7.0,8.0,1.0},
        {0.0,3.0,-5.0},
        {9.0,8.0,-6.0}
    };
    double c[4][3];

    trmul(a,b,4,5,3,c);
}
