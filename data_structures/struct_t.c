#include "struct_t.h"

void struct_init_t()
{
    str_t s;
    user_t u;

    memset(&u, 0, sizeof(user_t));

    u.buf = &s;
}
