#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stdarg.h>

#include "test.h"
#define TSRM_ERROR_LEVEL_CORE	2
#define TSRM_ERROR(args) tsrm_error args

int tsrm_error(int level, const char *format, ...);
static FILE *tsrm_error_file;

int main(int argc, char *argv[])
{
    int size = 100;
    printf("hello world: %d\n\n", sizeof(uint32_t));

    TSRM_ERROR((TSRM_ERROR_LEVEL_CORE, "Obtaining a new resource id, %d bytes", size));

    return EXIT_SUCCESS;
}

int tsrm_error(int level, const char *format, ...)
{
    int tsrm_error_level = 20;
    tsrm_error_file = stdout;
	if (level<=tsrm_error_level) {
		va_list args;
		int size;

		fprintf(tsrm_error_file, "TSRM:  ");
		va_start(args, format);
		size = vfprintf(tsrm_error_file, format, args);
		va_end(args);
		fprintf(tsrm_error_file, "\n");
		fflush(tsrm_error_file);
		return size;
	} else {
		return 0;
	}
}
