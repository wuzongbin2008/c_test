#include <stdio.h>

#include "matrix_opt.h"

int main()
{
    FILE *fp, *fp2;
    int i,j,n,m;
    char *fname = "./decode_data";
    char  **data,**d_data;
    char  **coding,**coding2;
    int blocksize = 80;
    double van_encode_matrix[3][10]=
    {
        { 1,1,1,1,1,1,1,1,1,1},
        { 1,2,3,4,5,6,7,8,9,10},
        { 1,4,9,16,25,36,49,64,81,100}
    };
    double van_decode_matrix[10][10] =
    {
        { 1.0 , 2.0 , 3.0 , 4.0 , 5.0 , 6.0 , 7.0 , 8.0 , 2.0 ,-1.0 },
        {-2.0 ,-3.0 ,-4.0 ,-5.0 ,-6.0 ,-7.0 ,-8.0 ,-9.0 ,-1.0 , 1.0 },
        { 1.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 },
        { 0.0 , 1.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 },
        { 0.0 , 0.0 , 1.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 },
        { 0.0 , 0.0 , 0.0 , 1.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 },
        { 0.0 , 0.0 , 0.0 , 0.0 , 1.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 },
        { 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 1.0 , 0.0 , 0.0 , 0.0 , 0.0 },
        { 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 1.0 , 0.0 , 0.0 , 0.0 },
        { 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 1.0 , 0.0 , 0.0 },
    };
    /* Allocate data and coding */
    data = ( char  **)malloc(sizeof( char *)*K);
    d_data = ( char  **)malloc(sizeof( char *)*K);
    coding = ( char  **)malloc(sizeof( char *)*M);
    for (i = 0; i < M; i++)
    {
        coding[i] = ( char  *)calloc(blocksize,sizeof( char ));
    }
    for(i=0; i<K; i++)
    {
        data[i] = ( char  *)calloc(blocksize,sizeof( char ));
        d_data[i] = ( char  *)calloc(blocksize,sizeof( char ));
        if(i==0)
        {
            data[i] = "abcdefghij";
        }
//        if(i==1){
//            data[i] = "klmnopqrst";
//        }
       // printf("%d = %s\nlen = %d\n\n",i,data[i],strlen(data[i]));
    }

    //rinv_test();

    //encode
    van_matrix_encode(10,3,van_encode_matrix,data,coding,blocksize);
    printf("\ncoding[%d] = %s\n",0,coding[0],strlen(coding[0]));
    printf("coding[%d] = %s\n",1,coding[1],strlen(coding[1]));
    printf("coding[%d] = %s\n\n\n",2,coding[2],strlen(coding[2]));

    //decode
    data[0] = coding[0];
    data[1] = coding[1];
    van_matrix_encode(10,10,van_decode_matrix,data,d_data,blocksize);
    for (i=0; i<K; i++)
    {
        printf("decoding[%d] = %s\n",i,d_data[i]);
    }
    printf("\n");

    return 0;
}

