#include <stdio.h>
#include <stdlib.h>

#include "getopt_test.h"

int main(int argc,char *argv[])
{
    char *s;

    //getopt_long_test(argc,argv);
    getopt_test(argc,argv);

    exit(EXIT_SUCCESS);
}
