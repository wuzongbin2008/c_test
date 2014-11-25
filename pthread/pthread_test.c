#include <errno.h>
#include <stdio.h>
#include "pthread_test.h"

thread_attr *attr;

void thread_worker(void *arg)
{
    thread_attr *a;
    a = (thread_attr *)arg;
    printf("thread_worker\nattr->id: %d\name: %s\n",a->id,a->name);
    a->id = 3;
    a->tid = pthread_self;
    printf("thread id: %d\n\n",pthread_self);

}

void thread_create_test()
{
    int ret;
    char *tname = "first_thread";
    pthread_t tidp,tid;
    pthread_attr_t t_attr;

    //pthread_attr_init(&t_attr);

    attr = (thread_attr *)calloc(1, sizeof(thread_attr));
    if(attr == NULL){
        printf("attr is null");
    }
    attr->id = 1;
    attr->name = strdup(tname);

    ret = pthread_create(&tidp,&t_attr,thread_worker,attr);
    pthread_join(tidp,NULL);

    if( ret == 0)
    {
        printf("main create success\nid: %d \nname: %s\nthread_id: %d \n\n",attr->id,attr->name,attr->tid);
    }else{
        perror("create pthread failed");
    }

    pthread_join(tidp,NULL);
}
