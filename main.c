#include <stdio.h>
#include <malloc.h>

#include "matrix_opt.h"



int main()
{
    int m,n,i,j;
    m = 3;
    n = 3;
    double *c;
    double a[10] = {1,2,3,0,1,4,0,0,1};

    //printf("%lf\n",Surplus(a,m,n));           //输出行列式
    //print_multiply();
    //printf("\n");
    c = MatrixOpp(a, m,n);
    for(i=0; i<m*n; i++)
    {
        printf("%.5f ",c[i]);
        if(!((i+1)%m))
            printf("\n");
    }

    return 0;
}

