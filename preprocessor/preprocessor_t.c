#include <stdarg.h>
#include "preprocessor_t.h"

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

#if defined(T)
void def_test()
{
    printf("def_test\n");
}
#endif // defined
