#ifndef JERASURE_TEST_H_INCLUDED
#define JERASURE_TEST_H_INCLUDED

#include <gf_rand.h>
#include "jerasure.h"

void usage(char *s);
static print_array(char **ptrs, int ndevices, int size, int packetsize, char *label);
int jerasure_test();

#endif // JERASURE_TEST_H_INCLUDED
