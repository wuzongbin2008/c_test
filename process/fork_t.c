#include <stdio.h>
#include "fork_t.h"

void fork_test()
{
    pid_t pid;

    printf("main pid: %d\n",getpid());
    pid = fork();
    switch (pid) {
    case -1:
        printf("fork() failed");
        return -1;

    case 0:
        printf("child process: 0");
        break;

    default:
        printf("child pid: %d\n",pid);

        exit(0);  //父进程退出
    }
}
