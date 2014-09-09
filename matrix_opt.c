#include <stdio.h>
#include <stdlib.h>

#include "matrix_opt.h"

void ec_double_test()
{
    FILE *fp, *fp2;
    int i,j,n=0,m;
    char *fname;
    char  **data,**decoding,*curdir;
    char  **coding,**coding2;
    int blocksize = 320;
    double van_encode_matrix[3][10]=
    {
        { 1,1,1,1,1,1,1,1,1,1},
        { 1,2,3,4,5,6,7,8,9,10},
        { 1,4,9,16,25,36,49,64,81,100}
    };
    double van_decode_matrix[10][10] =
    {
        {-1.0	 ,-3.0	 ,-6.0	 ,-10.0	 ,-15.0	 ,-21.0	 ,-28.0	 , 3.0	 ,-2.5	 , 0.5	 },
        { 3.0	 , 8.0	 ,15.0	 ,24.0	 ,35.0	 ,48.0	 ,63.0	 ,-3.0	 , 4.0	 ,-1.0	 },
        {-3.0	 ,-6.0	 ,-10.0	 ,-15.0	 ,-21.0	 ,-28.0	 ,-36.0	 , 1.0	 ,-1.5	 , 0.5	 },
        { 1.0	 , 0.0	 , 0.0	 , 0.0	 , 0.0	 , 0.0	 ,-0.0	 , 0.0	 , 0.0	 , 0.0	 },
        { 0.0	 , 1.0	 , 0.0	 , 0.0	 , 0.0	 , 0.0	 , 0.0	 ,-0.0	 , 0.0	 ,-0.0	 },
        { 0.0	 , 0.0	 , 1.0	 , 0.0	 , 0.0	 , 0.0	 ,-0.0	 , 0.0	 , 0.0	 , 0.0	 },
        { 0.0	 , 0.0	 , 0.0	 , 1.0	 , 0.0	 , 0.0	 ,-0.0	 , 0.0	 , 0.0	 , 0.0	 },
        { 0.0	 , 0.0	 , 0.0	 , 0.0	 , 1.0	 , 0.0	 ,-0.0	 , 0.0	 , 0.0	 , 0.0	 },
        { 0.0	 , 0.0	 , 0.0	 , 0.0	 , 0.0	 , 1.0	 ,-0.0	 , 0.0	 , 0.0	 , 0.0	 },
        { 0.0	 , 0.0	 , 0.0	 , 0.0	 , 0.0	 , 0.0	 , 1.0	 , 0.0	 , 0.0	 , 0.0	 },

    };

    /* Allocate data and coding */
    data = ( char  **)malloc(sizeof( char *)*K);
    decoding = ( char  **)malloc(sizeof( char *)*K);
    coding = ( char  **)malloc(sizeof( char *)*M);
    for (i = 0; i < M; i++)
    {
        coding[i] = ( char  *)calloc(blocksize,sizeof( char ));
    }
    for(i=0; i<K; i++)
    {
        data[i] = ( char  *)calloc(blocksize,sizeof( char ));
        decoding[i] = ( char  *)calloc(blocksize,sizeof( char ));
        if(i==0)
        {
            data[i] = "abcdefghij";
        }
        if(i==1)
        {
            data[i] = "klmnopqrst";
        }
        // printf("%d = %s\nlen = %d\n\n",i,data[i],strlen(data[i]));
    }
    curdir = (char*)malloc(sizeof(char)*1000);
    fname = (char*)malloc(sizeof(char)*200);
    getcwd(curdir, 1000);

    //encode
    van_double_matrix_encode(10,3,van_encode_matrix,data,coding,blocksize);
    for(i=0; i<3; i++)
    {
        printf("\ncoding[%d] =%d=%s",i,strlen(coding[i]),coding[i]);
        sprintf(fname, "%s/m%d", curdir, i);
        save_coding(fname,coding[i],blocksize);
    }
    printf("\n\n");

    //decode
    data[0]=( char  *)calloc(blocksize,sizeof( char ));
    data[1]=( char  *)calloc(blocksize,sizeof( char ));
    data[8] = coding[0];
    data[9] = coding[1];
//    for(i=0;i<10;i++){
//        printf("%d=%s\n",i,data[i]);
//    }
    van_double_matrix_encode(10,10,van_decode_matrix,data,decoding,blocksize);
    for (i=0; i<K; i++)
    {
        printf("decoding[%d] = %s\n",i,decoding[i]);
    }
    printf("\n");
}

void van_double_matrix_encode(int col,int row,double *matrix,char **data_ptrs,char **coding_ptrs,int blocksize)
{
    int i, j;
    char *t;

    for(i=0; i < row; i++)
    {
        erasure_double_matrix_dotprod(col,row, matrix+(i*col), NULL, col+i, data_ptrs, coding_ptrs, blocksize);
        t = coding_ptrs[i];
    }

}

void erasure_double_matrix_dotprod(int col, int row, double *matrix_row,int *src_ids, int dest_id,char **data_ptrs, char **coding_ptrs, int blocksize)
{
    char *dptr, *sptr,*t;
    int i,j;
    dptr = coding_ptrs[dest_id-col];

    for( j=0; j < col; j++)
    {
        sptr = data_ptrs[j];
        double_matrix_multiply_string(sptr,matrix_row[j],dptr,blocksize);
        t = *dptr;
        //printf("l3 = %f\ncoding[i]=\n\n",*l3,i,coding[i]);
    }
    //printf("coding[%d] = %s\n\n\n",i,coding[i]);
}

void double_matrix_multiply_string( char *r1, double l2,char *r3,int nbytes)
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

void ec_int_test()
{
    FILE *fp, *fp2;
    int i,j,n=0,m;
    char *fname;
    char  **data,**decoding,*curdir;
    char  **coding,**coding2;
    int blocksize = 320;
    int van_encode_matrix[3][10]=
    {
        { 1,1,1,1,1,1,1,1,1,1},
        { 1,2,3,4,5,6,7,8,9,10},
        { 1,4,9,16,25,36,49,64,81,100}
    };
    int van_decode_matrix[10][10] =
    {
        { 1 , 2 , 3 , 4 , 5 , 6 , 7, 8 , 2 ,-1 },
        {-2 ,-3,-4 ,-5 ,-6,-7 ,-8 ,-9 ,-1 , 1 },
        { 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
        { 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
        { 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
        { 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 },
        { 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 },
        { 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 },
        { 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 },
        { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 },
    };

    /* Allocate data and coding */
    data = ( char  **)malloc(sizeof( char *)*K);
    decoding = ( char  **)malloc(sizeof( char *)*K);
    coding = ( char  **)malloc(sizeof( char *)*M);
    for (i = 0; i < M; i++)
    {
        coding[i] = ( char  *)calloc(blocksize,sizeof( char ));
    }
    for(i=0; i<K; i++)
    {
        data[i] = ( char  *)calloc(blocksize,sizeof( char ));
        decoding[i] = ( char  *)calloc(blocksize,sizeof( char ));
        if(i==0)
        {
            data[i] = "abcdefghij";
        }
        if(i==1)
        {
            data[i] = "klmnopqrst";
        }
        // printf("%d = %s\nlen = %d\n\n",i,data[i],strlen(data[i]));
    }
    curdir = (char*)malloc(sizeof(char)*1000);
    fname = (char*)malloc(sizeof(char)*200);
    getcwd(curdir, 1000);

    //encode
    van_int_matrix_encode(10,3,van_encode_matrix,data,coding,blocksize);
    for(i=0; i<3; i++)
    {
        printf("\ncoding[%d] =%d=%s",i,strlen(coding[i]),coding[i]);
        sprintf(fname, "%s/m%d", curdir, i);
        save_coding(fname,coding[i],blocksize);
    }
    printf("\n\n");

    //decode
    data[0]=( char  *)calloc(blocksize,sizeof( char ));
    data[1]=( char  *)calloc(blocksize,sizeof( char ));
    data[8] = coding[0];
    data[9] = coding[1];
//    for(i=0;i<10;i++){
//        printf("%d=%s\n",i,data[i]);
//    }
    van_int_matrix_encode(10,10,van_decode_matrix,data,decoding,blocksize);
    for (i=0; i<K; i++)
    {
        printf("decoding[%d] = %s\n",i,decoding[i]);
    }
    printf("\n");
}

void int_matrix_multiply_string( char *r1, int l2,char *r3,int nbytes)
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

void erasure_int_matrix_dotprod(int col, int row, int *matrix_row,int *src_ids, int dest_id,char **data_ptrs, char **coding_ptrs, int blocksize)
{
    char *dptr, *sptr,*t;
    int i,j;
    dptr = coding_ptrs[dest_id-col];

    for( j=0; j < col; j++)
    {
        sptr = data_ptrs[j];
        int_matrix_multiply_string(sptr,matrix_row[j],dptr,blocksize);
        t = *dptr;
        //printf("l3 = %f\ncoding[i]=\n\n",*l3,i,coding[i]);
    }
    //printf("coding[%d] = %s\n\n\n",i,coding[i]);
}

void van_int_matrix_encode(int col,int row,int *matrix,char **data_ptrs,char **coding_ptrs,int blocksize)
{
    int i, j;
    char *t;

    for(i=0; i < row; i++)
    {
        erasure_int_matrix_dotprod(col,row, matrix+(i*col), NULL, col+i, data_ptrs, coding_ptrs, blocksize);
        t = coding_ptrs[i];
    }

}

void save_coding(char *fname,char *content,int blocksize)
{
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
    double a[10][10] =
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

    double a_inverse[3][3] =
    {
        {1,  -2,   5},
        {0,  1,   -4},
        {0,  0,    1}
    };
    static double b[K][K],c[K][K];

    for (i=0; i<K; i++)
    {
        for (j=0; j<K; j++)
        {
            b[i][j]=a[i][j];
        }
    }

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
                printf("%4.1f\t ",a[i][j]);
                if(j<9) printf(",");
            }
            printf("},\n");
        }
        printf("\n");

//        printf("MAT AA- IS:\n");
//        trmul(b,a,K,K,K,c);
//        for (i=0; i<K; i++)
//        {
//            for (j=0; j<K; j++)
//                printf("%3.0f ",c[i][j]);
//            printf("\n");
//        }
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
