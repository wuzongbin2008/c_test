#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#define a

//#include "pthread/pthread_test.h"
//#include "algorithm/sort.h"
//#include "libevent/libevent_server.h"
//#include "string/str_test.h"
//#include "common/getopt_test.h"
//#include "process/fork_t.h"
//#include "memory/mem_t.h"
//#include "common/limit_t.h"
//#include "file/file_test.h"
#include "macro/macro_t.h"

int main(int argc,char *argv[])
{
    printf("hello world: %d\n", sizeof(uint32_t));

    printf("gap: %d", 10/3+1);
    macro_null_t();

    return EXIT_SUCCESS;
}
