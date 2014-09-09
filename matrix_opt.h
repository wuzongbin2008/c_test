#ifndef MATRIX_OPT_H_INCLUDED
#define MATRIX_OPT_H_INCLUDED

#define K 10
#define M 3
#define N 10

void ec_double_test();
void van_double_matrix_encode(int k,int m,double *matrix,char **data,char **coding,int blocksize);
void double_matrix_multiply_string( char *r1, double l2,char *r3,int nbytes);
void ec_int_test();
void van_int_matrix_encode(int k,int m,int *matrix,char **data,char **coding,int blocksize);
void erasure_int_matrix_dotprod(int col, int row, int *matrix_row,int *src_ids, int dest_id,char **data_ptrs, char **coding_ptrs, int blocksize);
void int_matrix_multiply_string( char *r1, int l2,char *r3,int nbytes);
void int_matrix_multiply();
void print_multiply();
void tcmul(double *ar,double *br,int m,int n,int k,double *cr);

#endif // MATRIX_OPT_H_INCLUDED
