#ifndef PREPROCESS_T_H_INCLUDED
#define PREPROCESS_T_H_INCLUDED

#include <stdio.h>
#include <sys/stat.h>
//#define T 0

#define TSRM_ERROR_LEVEL_CORE	2
#define TSRM_ERROR(args) tsrm_error args

int tsrm_error(int level, const char *format, ...);
static FILE *tsrm_error_file;

int tsrm_error(int level, const char *format, ...);

#if defined(T)
void def_test();
#else
#define def_test()
#endif // defined

#endif // PREPROCESS_T_H_INCLUDED
