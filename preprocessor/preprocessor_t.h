#ifndef PREPROCESS_T_H_INCLUDED
#define PREPROCESS_T_H_INCLUDED

//#define T 0

void preprocessor_t();

#if defined(T)
void def_test();
#else
#define def_test()
#endif // defined

#endif // PREPROCESS_T_H_INCLUDED
