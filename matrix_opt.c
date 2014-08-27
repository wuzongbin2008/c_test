#include <stdio.h>
#include <stdlib.h>

#include "matrix_opt.h"

void van_matrix_encode(int *matrix,char **data,char **coding,int blocksize)
{
    int i, j;
    char *r1,*r3;
    long *l1;
    long *l3;
    char *ctop;
    long *ltop;
    char *t;
    int *matrix_row;

    //do multiply
    long  *ld;
    long  *cd;
    for(i=0; i < M; i++)
    {
        matrix_row = matrix+(i*K);
        for( j=0; j < K; j++)
        {
            l3 = (  long  *)coding[i];
            r1 = data[j];
            ctop = r1 + blocksize;
            ltop = (long *) ctop;
            l1 = (long *) r1;

            while (l1 < ltop)
            {
                //printf("j=%d\ns_l1 = %s\nl1=%ld\n",j,l1,*l1);
                //printf("matrix_row[%d][%d] = %d\n",i,j,matrix_row[i][j] );
                (*l3) = (*l3) + matrix_row[j] * (*l1);
                //printf("l3 = %ld\ns_l3=%s\n\n",*l3,l3);
                l1++;
                l3++;
            }
            //if(j > 0) break;
            //printf("l3 = %ld\ncoding[i]=\n\n",*l3,i,coding[i]);
        }
        //printf("coding[%d] = %s\n\n\n",i,coding[i]);
        //break;
    }

}

void generate_decode_matrix(int *matrix)
{
//    for(i=2;i<10;i++){
//        printf("{");
//        for(j=0;j<10;j++){
//            if(i==j)
//            {
//                van_decode_matrix[i][j] = 1;
//            }else{
//                van_decode_matrix[i][j] = 0;
//            }
//            printf("%d,",van_decode_matrix[i][j]);
//        }
//        printf("},\n");
//    }
}

void int_matrix_multiply()
{
    int a[2][2]= {{ 1, 1},{ 2, 0}};
    int b[2][3]= {{ 0, 2, 3},{ 1, 1, 2}};
    // int i, j, k, s[2][3];
    //问题出现在这里，s[2][3]没有赋初值，看得出来吗。
    //而你在下面的循坏里面，就直接用了 ==>s[i][j]=s[i][j]+a[i][k]*b[k][j];
    //将代码改成下面的，就得到你要的结果了
    //其他地方没有出现什么错误。修改过后，就是你要的答案了
    int i, j, k, s[2][3]= {0};
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
    for(i=0; i<2; i++)
    {
        for(j=0; j<3; j++)
        {
            printf("%d\t",s[i][j]);
            if(j==2)
                printf("\n");
        }
    }

}

void int_matrix_multiply2(int a[][5],int b[][3],int m,int n,int k,int c[][3])
{
    int i,j,l,u;
    int at,bt,ct;
    //m=4 k=3 n=5
    for (i=0; i<m; i++)
    {
        for (j=0; j<k; j++)
        {
            ct = c[i][j] = 0.0;
            for (l=0; l<n; l++)
            {
                at = a[i][l];
                bt = b[l][j];

                ct=ct+at*bt;
            }
            printf("%e\t",ct);
        }
        printf("\n");
    }
}

int *MatrixInver(int   A[],int   m,int   n)             //矩阵转置
{
    int   i,j;
    int   *B=NULL;
    B=(int  *)malloc(m*n*sizeof(int));

    for(i=0; i <n; i++)
        for(j=0; j <m; j++)
            B[i*m+j]=A[j*n+i];
    return   B;
}

int Surplus(int   A[],int   m,int   n)                 //求矩阵行列式
{
    int   i,j,k,p,r;
    int   X,temp=1,temp1=1,s=0,s1=0;
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

int *MatrixOpp(int   A[],int   m,int   n)               //矩阵求逆
{
    int   i,j,x,y,k;
    int *C;
    int   *SP=NULL,*AB=NULL,*B=NULL,X;                  //*C;
    SP=(int   *)malloc(m*n*sizeof(int));
    AB=(int   *)malloc(m*n*sizeof(int));
    B=(int   *)malloc(m*n*sizeof(int));
    X=Surplus(A,m,n);
    X=1/X;
    for(i=0; i<m; i++)                            //求矩阵伴随矩阵
    {
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
    }
    C=MatrixInver(AB,m,n);                         //MatrixInver  求倒置
    return   C;
}

void print_multiply()
{
    int i,j;
    int a[4][5]=
    {
        {1.0,3.0,-2.0,0.0,4.0},
        {-2.0,-1.0,5.0,-7.0,2.0},
        {0.0,8.0,4.0,1.0,-5.0},
        {3.0,-3.0,2.0,-4.0,1.0}
    };
    int b[5][3]=
    {
        {4.0,5.0,-1.0},
        {2.0,-2.0,6.0},
        {7.0,8.0,1.0},
        {0.0,3.0,-5.0},
        {9.0,8.0,-6.0}
    };
    int c[4][3];

    int_matrix_multiply(a,b,4,5,3,c);
}
