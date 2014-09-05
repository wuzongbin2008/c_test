#ifndef MATRIX_OPT_H_INCLUDED
#define MATRIX_OPT_H_INCLUDED

#define K 10
#define M 3
#define N 10

void ec_test();
void van_matrix_encode(int k,int m,int *matrix,char **data,char **coding,int blocksize);
void int_matrix_multiply();
void int_matrix_multiply2(int a[][5],int b[][3],int m,int n,int k,int c[][3]);
int *MatrixInver(int   A[],int   m,int   n);
int Surplus(int   A[],int   m,int   n);
int *MatrixOpp(int   A[],int   m,int   n);
void print_multiply();
void tcmul(double *ar,double *br,int m,int n,int k,double *cr);

#endif // MATRIX_OPT_H_INCLUDED
