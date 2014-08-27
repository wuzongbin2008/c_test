#include <stdio.h>
#include <malloc.h>

#include "matrix_opt.h"

int main()
{
    int i,j;
    char  **data;
    char  **coding;
    int blocksize = 32;
    int van_encode_matrix[M][K]=
    {
        { 1,1,1,1,1,1,1,1,1,1},
        { 1,2,3,4,5,6,7,8,9,10},
        { 1,4,9,16,25,36,49,64,81,100}
    };

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
            data[i] = "klmnopqrst";
        }
    }

    van_matrix_encode(van_encode_matrix,data,coding,blocksize);

    printf("coding[%d] = %s\n\n\n",0,coding[0]);
    printf("coding[%d] = %s\n\n\n",1,coding[1]);
    printf("coding[%d] = %s\n\n\n",2,coding[2]);

//    c = MatrixOpp(a, m,n);
//    for(i=0; i<m*n; i++)
//    {
//        printf("%.5f ",c[i]);
//        if(!((i+1)%m))
//            printf("\n");
//    }

    return 0;
}

