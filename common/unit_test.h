#ifndef UNIT_TEST_H_INCLUDED
#define UNIT_TEST_H_INCLUDED

#include "queue.h"

#define likely(x)	__builtin_expect(!!(x), 1)
#define unlikely(x)	__builtin_expect(!!(x), 0)
#define nf_align(type, size, align) (((size)+(align)-1) & ((type)~((align)-1)))
typedef STAILQ_HEAD(block_frame_head, block_frame) bf_head;
typedef struct buffer_pool {
	int							used;
	int							total;
	bf_head						free_buff;
	bf_head						free_frame;

	int							bf_len;
	int							bf_off;
	void 						**bf_page;
} bp_t;

/*********************** Chained buffer ************************/
typedef struct buffer {
	int							len;
	int							off;
	char						*last;
	bp_t						*pool;
	STAILQ_HEAD(, block_frame)	head;
} buff_t;

void get_param(int argc,char *argv[]);
void print_file_Statfs();
off_t get_file_offset();
int notfs_hash();
void unlikely_test();
#endif // UNIT_TEST_H_INCLUDED
