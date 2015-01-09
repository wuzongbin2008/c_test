#include <stdio.h>
#include <stdint.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <errno.h>
#include <limits.h>

#include "file_test.h"

void file_size()
{
    struct stat f_st;
    off_t size;
    int fd, rt;
    char *filename = "/project/c/c_test/file/data/nginx.conf";

    fd = open(filename, O_RDONLY, 0);
    rt = fstat(fd, &f_st);
    rt = stat(filename, &f_st);
    size = f_st.st_size;

    printf("rt: %d\nsize: %d\n", rt, size);

}

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
