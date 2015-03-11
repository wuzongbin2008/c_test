#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#include "test.h"

int main(int argc,char *argv[])
{
    printf("hello world: %d\n", sizeof(uint32_t));

    pthread_key_create_demo();

    return EXIT_SUCCESS;
}
