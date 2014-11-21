#ifndef PTHREAD_TEST_H_INCLUDED
#define PTHREAD_TEST_H_INCLUDED

#include <pthread.h>

typedef struct thread_create_param{
    int id;
    char *name;
    pthread_t tid;
    pthread_attr_t attr;
} thread_attr;

void thread_worker(void *attr);
void thread_create_test();
#endif // PTHREAD_TEST_H_INCLUDED
