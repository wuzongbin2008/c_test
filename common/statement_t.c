#include "statement_t.h"

void switch_test()
{
    char ch;
    ch = ';';

    switch(ch){
    case ';':
    case 'a':
        printf("a\n");
        break;
    case 'b':
        printf("b\n");
        break;
    default:
        printf("default: %c\n",ch);
    }
}
