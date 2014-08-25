#include <stdio.h>
#include <malloc.h>

#include "matrix_opt.h"

double *C,a[10] = {1,2,3,0,1,4,0,0,1};
double   *MatrixInver(double   A[],int   m,int   n)             //矩阵转置
{
    int   i,j;
    double   *B=NULL;
    B=(double   *)malloc(m*n*sizeof(double));

    for(i=0; i <n; i++)
        for(j=0; j <m; j++)
            B[i*m+j]=A[j*n+i];
    return   B;
}

double   Surplus(double   A[],int   m,int   n)                   //求矩阵行列式
{
    int   i,j,k,p,r;
    double   X,temp=1,temp1=1,s=0,s1=0;
    if(n==2)
    {
        for(i=0; i <m; i++)
            for(j=0; j <n; j++)
                if((i+j)%2)   temp1*=A[i*n+j];
                else   temp*=A[i*n+j];
        X=temp-temp1;
    }
    else
    {
        for(k=0; k <n; k++)
        {
            for(i=0,j=k; i <m,j <n; i++,j++)
                temp*=A[i*n+j];
            if(m-i)
            {
                for(p=m-i,r=m-1; p> 0; p--,r--)
                    temp*=A[r*n+p-1];
            }
            s+=temp;
            temp=1;
        }
        for(k=n-1; k>=0; k--)
        {
            for(i=0,j=k; i<m,j>=0; i++,j--)
                temp1*=A[i*n+j];
            if(m-i)
            {
                for(p=m-1,r=i; r <m; p--,r++)
                    temp1*=A[r*n+p];
            }
            s1+=temp1;
            temp1=1;
        }
        X=s-s1;
    }
    return   X;
}

double   *MatrixOpp(double   A[],int   m,int   n)               //矩阵求逆
{
    int   i,j,x,y,k;
    double   *SP=NULL,*AB=NULL,*B=NULL,X;                  //*C;
    SP=(double   *)malloc(m*n*sizeof(double));
    AB=(double   *)malloc(m*n*sizeof(double));
    B=(double   *)malloc(m*n*sizeof(double));
    X=Surplus(A,m,n);
    X=1/X;
    for(i=0; i<m; i++)                             //求矩阵伴随矩阵
        for(j=0; j<n; j++)
        {
            for(k=0; k<m*n; k++)
                B[k]=A[k];                                 //B[]变成A[];
            {
                for(x=0; x<n; x++)
                    B[i*n+x]=0;
                for(y=0; y<m; y++)
                    B[m*y+j]=0;
                B[i*n+j]=1;
                SP[i*n+j]=Surplus(B,m,n);
                AB[i*n+j]=X*SP[i*n+j];
            }
        }
    C=MatrixInver(AB,m,n);                         //MatrixInver  求倒置
    return   C;
}

int main()
{
    int m,n,i,j;
    m = 3;
    n = 3;

    //printf("%lf\n",Surplus(a,m,n));           //输出行列式
    print_multiply();
    printf("\n");
    MatrixOpp(a, m,n);
    for(i=0; i<m*n; i++)
    {
        printf("%.5f ",C[i]);
        if(!((i+1)%m))
            printf("\n");
    }

    return 0;
}

