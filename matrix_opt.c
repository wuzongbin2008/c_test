#include <stdio.h>
#include <stdlib.h>

#include "matrix_opt.h"
void galois_region_xor( char *r1, int l2,char *r3,int nbytes)
{
    long *l1;
    //double *l2;
    long *l3;
    long *ltop;
    char *ctop;

    ctop = r1 + nbytes;
    ltop = (long *) ctop;
    l1 = (long *) r1;
    //l2 = (double *) r2;
    l3 = (long *) r3;

    while (l1 < ltop)
    {
        //*l3 = (*l3) + ((*l1)  * (*l2));
        *l3 = (*l3) + (*l1)  * l2;
        l1++;
        l3++;
    }
}

void erasure_matrix_dotprod(int col, int row, int *matrix_row,int *src_ids, int dest_id,char **data_ptrs, char **coding_ptrs, int blocksize)
{
    char *dptr, *sptr,*t;
    int i,j;
    dptr = coding_ptrs[dest_id-col];

    for( j=0; j < col; j++)
    {
        sptr = data_ptrs[j];
//            ctop = r1 + blocksize;
//            ltop = (double *) ctop;
//            l1 = (double *) r1;
//            l3 = (long *) r3;
//            while (l1 < ltop)
//            {
//                tmp = matrix_row[j];
//                (*l3) = (*l3) +  tmp * (*l1);
//                t = coding[i];
//                l1++;
//                l3++;
//            } =
        galois_region_xor(sptr,matrix_row[j],dptr,blocksize);
        t = *dptr;
        //printf("l3 = %f\ncoding[i]=\n\n",*l3,i,coding[i]);
    }
    //printf("coding[%d] = %s\n\n\n",i,coding[i]);
}

void van_matrix_encode(int col,int row,int *matrix,char **data_ptrs,char **coding_ptrs,int blocksize)
{
    int i, j;
    char *t;

    for(i=0; i < row; i++)
    {
        erasure_matrix_dotprod(col,row, matrix+(i*col), NULL, col+i, data_ptrs, coding_ptrs, blocksize);
        t = coding_ptrs[i];
    }

}

void save_coding(char *fname,char *content,int blocksize){
    FILE *fp, *fp2;
    fp2 = fopen(fname, "wb");
    fwrite(content, sizeof(char), blocksize, fp2);
    fclose(fp2);
}

int rinv(double a[],int n)
{
    int *is,*js,i,j,k,l,u,v;
    double d,p;
    is=malloc(n*sizeof(int));
    js=malloc(n*sizeof(int));

    for (k=0; k<=n-1; k++)
    {
        d=0.0;
        for (i=k; i<=n-1; i++)
        {
            for (j=k; j<=n-1; j++)
            {
                l=i*n+j;
                p=fabs(a[l]);
                if (p>d)
                {
                    d=p;
                    is[k]=i;
                    js[k]=j;
                }
            }
        }

        if (d+1.0==1.0)
        {
            free(is);
            free(js);
            printf("err**not inv\n");
            return(0);
        }

        if (is[k]!=k)
        {
            for (j=0; j<=n-1; j++)
            {
                u=k*n+j;
                v=is[k]*n+j;
                p=a[u];
                a[u]=a[v];
                a[v]=p;
            }
        }

        if (js[k]!=k)
        {
            for (i=0; i<=n-1; i++)
            {
                u=i*n+k;
                v=i*n+js[k];
                p=a[u];
                a[u]=a[v];
                a[v]=p;
            }
        }

        l=k*n+k;
        a[l]=1.0/a[l];
        for (j=0; j<=n-1; j++)
        {
            if (j!=k)
            {
                u=k*n+j;
                a[u]=a[u]*a[l];
            }
        }

        for (i=0; i<=n-1; i++)
        {
            if (i!=k)
            {
                for (j=0; j<=n-1; j++)
                {
                    if (j!=k)
                    {
                        u=i*n+j;
                        a[u]=a[u]-a[i*n+k]*a[k*n+j];
                    }
                }
            }
        }

        for (i=0; i<=n-1; i++)
        {
            if (i!=k)
            {
                u=i*n+k;
                a[u]=-a[u]*a[l];
            }
        }
    }

    for (k=n-1; k>=0; k--)
    {
        if (js[k]!=k)
        {
            for (j=0; j<=n-1; j++)
            {
                u=k*n+j;
                v=js[k]*n+j;
                p=a[u];
                a[u]=a[v];
                a[v]=p;
            }
        }

        if (is[k]!=k)
        {
            for (i=0; i<=n-1; i++)
            {
                u=i*n+k;
                v=i*n+is[k];
                p=a[u];
                a[u]=a[v];
                a[v]=p;
            }
        }
    }

    free(is);
    free(js);

    return(1);
}

void trmul(double *a,double *b,int m,int n,int k,double *c)
{
    int i,j,l,u;
    for (i=0; i<=m-1; i++)
        for (j=0; j<K-1; j++)
        {
            u=i*k+j;
            c[u]=0.0;
            for (l=0; l<=n-1; l++)
                c[u]=c[u]+a[i*n+l]*b[l*k+j];
        }
    return;
}

void rinv_test()
{
    int i,j;
//    static double a[4][4]= { {0.2368,0.2471,0.2568,1.2671},
//        {1.1161,0.1254,0.1397,0.1490},
//        {0.1582,1.1675,0.1768,0.1871},
//        {0.1968,0.2071,1.2168,0.2271}
//    };
    double a[10][10] =
    {
        {0,0,1,0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,0,1,0,0,0,0},
        {0,0,0,0,0,0,1,0,0,0},
        {0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,0,1,0},
        {0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1},
        {1,2,3,4,5,6,7,8,9,10},
//        {1,4,9,16,25,36,49,64,81,100}
    };
//    double a[3][3] =
//    {
//        {1,2,3},
//        {0,1,4},
//        {0,0,1}
//    };
    double a_inverse[3][3] =
    {
        {1,  -2,   5},
        {0,  1,   -4},
        {0,  0,    1}
    };
    static double b[K][K],c[K][K];

    for (i=0; i<K; i++)
        for (j=0; j<K; j++)
            b[i][j]=a[i][j];

    //invertion
    i=rinv(a,K);

    if (i!=0)
    {
        printf("MAT A IS:\n");
        for (i=0; i<K; i++)
        {
            for (j=0; j<K; j++)
                printf("%3.0f ",b[i][j]);
            printf("\n");
        }
        printf("\n");

        printf("MAT A- IS:\n");
        for (i=0; i<K; i++)
        {
            printf("{");
            for (j=0; j<K; j++)
            {
                printf("%4.1f ",a[i][j]);
                if(j<9) printf(",");
            }
            printf("},\n");
        }
        printf("\n");

        printf("MAT AA- IS:\n");
        trmul(b,a,K,K,K,c);
        for (i=0; i<K; i++)
        {
            for (j=0; j<K; j++)
                printf("%3.0f ",c[i][j]);
            printf("\n");
        }
    }
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

void generate_decode_matrix()
{
    int i,j;
    int matrix[10][10];

    for(i=0; i<10; i++)
    {
        printf("{");
        for(j=0; j<10; j++)
        {
            if(i==j)
            {
                matrix[i][j] = 1;
            }
            else
            {
                matrix[i][j] = 0;
            }
            printf("%d",matrix[i][j]);
            if(j<9) printf(",");
        }
        printf("},\n");
    }
}

/************************ error demo *********************************/
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
