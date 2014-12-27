#include <stdio.h>
#include <stdint.h>
#include<sys/file.h>
#include <errno.h>

#include "file_test.h"

char * get_path()
{
    char *str;
    str = alloca(PATH_MAX);
    getcwd(str, PATH_MAX);
    printf("pwd: %s\n", str);

    return str;
}

void create_file(char *filename){
        int fd = open(filename, O_RDWR, 0777);
        if (fd == -1){
                printf("open error = %d,str = %s",errno);
        }else{
                printf("open ok");
        }
}
