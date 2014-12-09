#include <stdio.h>
#include <string.h>
#include "str_test.h"

void str_test()
{
    make_no();
}

void strerror_t()
{
    char *s;

    s = strerror(3);
    printf("%s\n",s);
}

void make_no()
{
    char *name;
    char no[3];
    int a = 100,len;

    sprintf(no,"%03d",1);
    len = strlen(no)+6;
    name = malloc(sizeof(char)*len);
    sprintf(name,"conn_%03d",2);

    printf("\tname = %s\n\tlen = %d\n",name,strlen(name));
}
