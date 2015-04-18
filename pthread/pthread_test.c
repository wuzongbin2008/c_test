#include <errno.h>
#include <string.h>
#include <stdio.h>
#include "pthread_test.h"

thread_attr *attr;
pthread_key_t key;
test_struct *key_p;

void *child1 (void *arg)
{
    test_struct struct_data;
    struct_data.i = 10;
    struct_data.k = 3.1415;
    pthread_setspecific (key, &struct_data);
    printf ("结构体struct_data的地址为 0x%p\n\n", &(struct_data));
    key_p = (struct test_struct *)pthread_getspecific(key);
    printf ("child1 中 pthread_getspecific(key)返回的指针为:0x%p\n", key_p);
    printf ("利用 pthread_getspecific(key)打印 child1 线程中与key关联的结构体中成员值:\nstruct_data.i:%d\nstruct_data.k: %f\n", key_p->i, key_p->k);
    printf ("------------------------------------------------------\n\n");
}

void *child2 (void *arg)
{
    int temp = 20, *tmp_p;
    sleep (2);
    printf ("child2 中变量 temp 的地址为 0x%p\n",  &temp);
    pthread_setspecific (key, &temp);
    tmp_p = (int *)pthread_getspecific(key);
    printf ("child2 中 pthread_getspecific(key)返回的指针为:0x%p\n", tmp_p);
    printf ("利用 pthread_getspecific(key)打印 child2 线程中与key关联的整型变量temp 值:%d\n", *(tmp_p));
}

int pthread_key_create_demo ()
{
    pthread_t tid1, tid2;
    pthread_key_create (&key, NULL);
    pthread_create (&tid1, NULL, (void *)child1, NULL);
    pthread_create (&tid2, NULL, (void *)child2, NULL);
    pthread_join (tid1, NULL);
    pthread_join (tid2, NULL);
    pthread_key_delete (key);
    return 0;

}

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
