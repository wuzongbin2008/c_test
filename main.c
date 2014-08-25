#include <stdio.h>
#include <malloc.h>

#include "matrix_opt.h"

#define N 10

//double A[N][N]= {{1,3,2,13},{7,2,1,-2},{9,15,3,-2},{-2,-2,11,5}};
inline void swap(double a,double b)
{
    double c=a;
    a=b;
    b=c;
}

int DinV(double A[N][N],int n)
{
    int i,j,k;
    double d;
    int JS[N],IS[N];
    for (k=0; k<n; k++)
    {
        d=0;
        for (i=k; i<n; i++)
            for (j=k; j<n; j++)
            {
                if (fabs(A[i][j])>d)
                {
                    d=fabs(A[i][j]);
                    IS[k]=i;
                    JS[k]=j;
                }
            }
        if (d+1.0==1.0) return 0;
        if (IS[k]!=k)
            for (j=0; j<n; j++)
                swap(A[k][j],A[IS[k]][j]);
        if (JS[k]!=k)
            for (i=0; i<n; i++)
                swap(A[i][k],A[i][JS[k]]);
        A[k][k]=1/A[k][k];
        for (j=0; j<n; j++)
            if (j!=k) A[k][j]=A[k][j]*A[k][k];
        for (i=0; i<n; i++)
            if (i!=k)
                for (j=0; j<n; j++)
                    if (j!=k) A[i][j]=A[i][j]-A[i][k]*A[k][j];
        for (i=0; i<n; i++)
            if (i!=k) A[i][k]=-A[i][k]*A[k][k];
    }
    for (k=n-1; k>=0; k--)
    {
        for (j=0; j<n; j++)
            if (JS[k]!=k) swap(A[k][j],A[JS[k]][j]);
        for (i=0; i<n; i++)
            if (IS[k]!=k) swap(A[i][k],A[i][IS[k]]);
    }
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
            printf("  %1.4f",A[i][j]);
        puts("");
    }
}

int main()
{
    int i,j,n,m;
    char  **data;
    char  **coding;
    int blocksize = 32;
    int van_encode_matrix[M][K]=
    {
        { 1,1,1,1,1,1,1,1,1,1},
        { 1,2,3,4,5,6,7,8,9,10},
        { 1,4,9,16,25,36,49,64,81,100}
    };
    double van_decode_matrix[10][10] =
    {
        {0,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,0,1,0,0,0,0},
        {0,0,0,0,0,0,1,0,0,0},
        {0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,0,1,0},
        {0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1},
        {1,2,3,4,5,6,7,8,9,10},
        {1,4,9,16,25,36,49,64,81,100}
    };
    int *c;

    n = m = 10;
    double demo[3][3] =
    {
        {1,2,3},
        {0,1,4},
        {0,0,1}
    };

    rinv_test();
    DinV(van_decode_matrix,N);
    c = MatrixOpp(van_decode_matrix,n,m);
    for(i=0; i<n*m; i++)
    {
        printf("%d ",c[i]);
        if(!((i+1)%n))
            printf("\n");
    }

    /* Allocate data and coding */
    data = ( char  **)malloc(sizeof( char *)*K);
    coding = ( char  **)malloc(sizeof( char *)*M);
    for (i = 0; i < M; i++)
    {
        coding[i] = ( char  *)calloc(blocksize,sizeof( char ));
    }
    for(i=0; i<K; i++)
    {
        data[i] = ( char  *)calloc(blocksize,sizeof( char ));
        if(i==0)
        {
            data[i] = "abcdefghij";
        }
        if(i==1)
        {
            //data[i] = "klmnopqrst";
        }
    }

    van_matrix_encode(van_encode_matrix,data,coding,blocksize);

//    printf("\ncoding[%d] = %s\n\n\n",0,coding[0]);
//    printf("coding[%d] = %s\n\n\n",1,coding[1]);
//    printf("coding[%d] = %s\n\n\n",2,coding[2]);


    return 0;
}

