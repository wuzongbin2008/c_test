#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static char *ecnotfs_config_file = "./ec_notfs.conf";

static void usage()
{
    printf("Rozofs export daemon - %s\n", 1);
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

    while ((opt = getopt(argc, argv, optstring)) != -1)
    {
        printf("opt = %c\n", opt);
        printf("optopt = %c\n", optopt);
        printf("opterr = %c\n", opterr);
        printf("optarg = %s\n", optarg);
        printf("optind = %d\n", optind);
        printf("argv[optind - 1] = %s\n\n",  argv[optind - 1]);
    }
}

/*
* ./test -a 100 --reqarg 100 --nonarg
*/
void getopt_long_test(int argc,char *argv[])
{
    int opt;
    int digit_optind = 0;
    int option_index = 0;
    char *optstring = "a:b:c:d";
    static struct option long_options[] =
    {
        {"reqarg", required_argument, NULL, 'r'},
        {"noarg",  no_argument,       NULL, 'n'},
        {"optarg", optional_argument, NULL, 'o'},
        {0, 0, 0, 0}
    };

    while ( (opt = getopt_long(argc, argv, optstring, long_options, &option_index)) != -1)
    {
        printf("opt = %c\n", opt);
        printf("optarg = %s\n", optarg);
        printf("optind = %d\n", optind);
        printf("argv[optind - 1] = %s\n",  argv[optind - 1]);
        printf("option_index = %d\n\n", option_index);
    }
}
