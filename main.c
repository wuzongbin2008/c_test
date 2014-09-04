#include <stdio.h>

#include "matrix_opt.h"

int main()
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
        if(i==1){
            data[i] = "klmnopqrst";
        }
       // printf("%d = %s\nlen = %d\n\n",i,data[i],strlen(data[i]));
    }
    curdir = (char*)malloc(sizeof(char)*1000);
    fname = (char*)malloc(sizeof(char)*200);
    getcwd(curdir, 1000);

    //求逆矩阵
    //rinv_test();

    //encode
    van_matrix_encode(10,3,van_encode_matrix,data,coding,blocksize);
    for(i=0;i<3;i++){
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
    van_matrix_encode(10,10,van_decode_matrix,data,decoding,blocksize);
    for (i=0; i<K; i++)
    {
        printf("decoding[%d] = %s\n",i,decoding[i]);
    }
    printf("\n");

    return 0;
}

