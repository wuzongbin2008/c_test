#ifndef MATRIX_OPT_H_INCLUDED
#define MATRIX_OPT_H_INCLUDED

void int_matrix_multiply();
void double_matrix_multiply(double a[][5],double b[][3],int m,int n,int k,double c[][3]);
double *MatrixInver(double   A[],int   m,int   n);
double Surplus(double   A[],int   m,int   n);
double *MatrixOpp(double   A[],int   m,int   n);
void print_multiply();
#endif // MATRIX_OPT_H_INCLUDED
