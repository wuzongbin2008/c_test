#ifndef STRUCT_T_H_INCLUDED
#define STRUCT_T_H_INCLUDED

struct str{
    int len;
    char *data;
};
typedef struct str str_t;

struct user{
    str_t *buf;
    char *name;
};
typedef struct user user_t;

void struct_init_t();
#endif // STRUCT_T_H_INCLUDED
