#include <stdio.h>
#include <malloc.h>

#include "matrix_opt.h"



int main()
{
    int m,n,i,j;
    m = 3;
    n = 3;
    double *c;
    long *a = (long *)malloc(sizeof(long));
    *a =  7523094288207667809;
    int van_matrix[10][3]={
        { 1,1,1,1,1,1,1,1,1,1},
        { 1,2,3,4,5,6,7,8,9,10},
        { 1,4,9,16,25,36,49,64,81,100}
    };

    char *s = (char *) a;
    //printf("%s\n",s);
    van_matrix_multiply();

//    c = MatrixOpp(a, m,n);
//    for(i=0; i<m*n; i++)
//    {
//        printf("%.5f ",c[i]);
//        if(!((i+1)%m))
//            printf("\n");
//    }

    return 0;
}

