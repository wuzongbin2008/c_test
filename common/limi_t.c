#include <sys/resource.h>

void limit_t()
{
    struct rlimit  rlmt;
    int max;

    if (getrlimit(RLIMIT_NOFILE, &rlmt) == -1) {
        printf("limit err");
    }

    max = (int) rlmt.rlim_cur;
    printf("max: %d\n",max);
}
