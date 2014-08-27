#include <stdio.h>
#include <malloc.h>

#include "matrix_opt.h"

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
    int van_decode_matrix[10][10] =
    {
        //{0,0,1,0,0,0,0,0,0,0,},
        {0,0,0,1,0,0,0,0,0,0,},
        {0,0,0,0,1,0,0,0,0,0,},
        {0,0,0,0,0,1,0,0,0,0,},
        {0,0,0,0,0,0,1,0,0,0,},
        {0,0,0,0,0,0,0,1,0,0,},
        {0,0,0,0,0,0,0,0,1,0,},
        {0,0,0,0,0,0,0,0,0,1,},
        { 1,1,1,1,1,1,1,1,1,1},
        { 1,2,3,4,5,6,7,8,9,10},
        { 1,4,9,16,25,36,49,64,81,100}
    };
    int *c;

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
        if(i==1){
            //data[i] = "klmnopqrst";
        }
    }

    van_matrix_encode(van_encode_matrix,data,coding,blocksize);

//    printf("\ncoding[%d] = %s\n\n\n",0,coding[0]);
//    printf("coding[%d] = %s\n\n\n",1,coding[1]);
//    printf("coding[%d] = %s\n\n\n",2,coding[2]);
    n = m = 10;
    int demo[3][3] =
    {
        {1,2,3},
        {0,1,4},
        {0,0,1}
    };
    c = MatrixOpp(van_decode_matrix,n,m);
    for(i=0; i<n*m; i++)
    {
        printf("%d ",c[i]);
        if(!((i+1)%n))
            printf("\n");
    }

    return 0;
}

