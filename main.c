#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#include "test.h"

int main(int argc, char *argv[])
{
    int size = 100;
    printf("hello world: %d\n\n", sizeof(uint32_t));

    //TSRM_ERROR((TSRM_ERROR_LEVEL_CORE, "Obtaining a new resource id, %d bytes", size));
    sort_test();

    return EXIT_SUCCESS;
}
