#ifndef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include <getopt.h>
#include <sys/stat.h>

#include "getopt_test.h"

FILE *fp;

int vfpf_t()
{
    int inumber = 30, m;
    float fnumber = 90.0;
    char string[4] = "abc";
    struct stat buf;

    fp = tmpfile();
    if (fp == NULL)
    {
        perror("tmpfile() call");
        exit(1);
    }
    fstat(fp, &buf);
    printf("mode: %d\n", buf.st_size);

    vfpf("%d %f %s", inumber, fnumber, string);
    rewind(fp);
    fscanf(fp, "%d %f %s", &inumber, &fnumber, string);
    printf("%d %f %s\n", inumber, fnumber, string);
    fclose(fp);

    return 0;
}

int vfpf(char* fmt, ...)
{
    va_list argptr;
    int cnt = 0;

    va_start(argptr, fmt);
    cnt = vfprintf(fp, fmt, argptr);
    va_end(argptr);

    return 0;
}

//static char *ecnotfs_config_file = "./ec_notfs.conf";
void argv_t(int argc, char *argv[])
{
    int i;
    char *p;
    printf("argc: %d\n", argc);
    for (i = 1; i < argc; i++)
    {

        p = (char *) argv[i];
        printf("p: %s\n", p);
        printf("*p: %c\n", *p);
        //printf("*p++: %c\n", *p);

        if (*p++ != '-')
        {
            printf("invalid option: \"%s\"", argv[i]);
            return -1;
        }

        while (*p)
        {
            switch(*p++){
            case 'h':
                printf("1: %c\n", *(p-1));
                break;
            case 'v':
                printf("2: %c\n", *(p-1));
                break;
            }
        }
    }
}

void usage()
{
    printf("Rozofs export daemon - %s\n", "1");
    printf("Usage: exportd [OPTIONS]\n\n");
    printf("\t-h, --help\tprint this message.\n");
    printf("\t-c, --config\tconfiguration file to use (default: %s).\n","./config.conf");
};

/*
* ./test -a 100 -b 200 -c admin -d
*/
void getopt_test(int argc,char *argv[])
{
    int opt;
    char *optstring = "a:b:c:d";

    printf("func name: %s\n", program_invocation_name);
    printf("func short name: %s\n", program_invocation_short_name);
    while ((opt = getopt(argc, argv, optstring)) != -1)
    {
        printf("opt = %c\n", opt);
        printf("optopt = %c\n", optopt);
        printf("opterr = %d\n", opterr);
        printf("optarg = %s\n", optarg);
        printf("optind = %d\n", optind);
        printf("argv[optind - 1] = %s\n\n",  argv[optind - 1]);
    }
}

/*
* ./test -a 100 --reqarg 100 --nonarg
*/
void getopt_long_test(int argc, char *argv[])
{
    int opt;
    //int digit_optind = 0;
    int option_index = 0;
    char *optstring = "a:b:c:d";
    static struct option long_options[] =
    {
        {"reqarg", required_argument, NULL, 9},
        {"noarg",  no_argument,       NULL, 5},
        {"optarg", optional_argument, NULL, 'o'},
        {0, 0, 0, 0}
    };

    while ( (opt = getopt_long(argc, argv, optstring, long_options, &option_index)) != -1)
    {
        printf("opt = %d\n", opt);
        printf("optarg = %s\n", optarg);
        printf("optind = %d\n", optind);
        printf("argv[optind - 1] = %s\n",  argv[optind - 1]);
        printf("option_index = %d\n\n", option_index);
    }
}
#endif // _GNU_SOURCE
