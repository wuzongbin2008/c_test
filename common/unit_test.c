#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/statfs.h>
#include <string.h>
#include <fcntl.h>

#include "unit_test.h"
#include "queue.h"
#define PAGE_SIZE 4096

int add_entry(nf_key_t *key, nf_pos_t *pos)
{
	int new;
	nf_pos_t *ptr;
	struct hash_entry *entry;
	struct hash_entry **next = NULL;

	/* bug: WHEN LIST IS NULL */
	entry = _find_entry(key, &next);
	if (entry == NULL) {
		entry = _new_entry(key);
		if (entry == NULL) {
			return NF_E_NEWENTRY;
		}
		//SLIST_INSERT_AFTER(last, entry, field);
		*next = entry;
		new = 1;
	}

	ptr = get_pos(entry, key);

	return 0;
}
struct hash_entry * _find_entry(nf_key_t *key, struct hash_entry ***next)
{
	int hv;
	unsigned int len = 0;
	struct list_head *head;
	struct hash_entry *entry, *target = NULL;

	hv = hash(key);
	head = nf_hash_table + hv;

	if (unlikely(next)) {
		*next = &SLIST_FIRST(head);
		SLIST_FOREACH(entry, head, field) {
			len++;
			*next = &SLIST_NEXT(entry, field);
			if (compare(key, entry) == 0) {
				target = entry;
				break;
			}
		}
	} else {
		SLIST_FOREACH(entry, head, field) {
			len++;
			if (compare(key, entry) == 0) {
				target = entry;
				break;
			}
		}
	}
#ifdef DEBUG
	printf("earch len = %d\n", len);
	printf("lengest_chain = %d\n", longest_chain);
#endif
	if (len > longest_chain) longest_chain = len;
	return target;
}

struct hash_entry * _new_entry(nf_key_t *key)
{
	struct hash_entry *new;

	//new = calloc(1, sizeof(struct hash_entry));
	new = block_pool_alloc(&pic_idx_mem_pool, sizeof(struct hash_entry));
	if (new) {
		memset(new, 0, sizeof(struct hash_entry));
		memcpy(new->key, key->key+PIC_KEY_PREFIX, PIC_KEY_SIZE);
	}

	return new;
}
void * block_pool_alloc(nf_pool_t *pool, size_t count)
{
	int ret;
	void *ptr;
	size_t len;

	len = nf_align(size_t, count, 8);
	if (len > NF_PAGE_SIZE) return NULL;

	if (len > (NF_PAGE_SIZE - pool->off)) {
		ret = expand_block_pool(pool);
		if (ret == -1) return NULL;
	}

	ptr = pool->ptr + pool->off;
	pool->off += len;
	pool->objs ++;

	return ptr;
}
void get_param(int argc,char *argv[])
{
    int result;
    char *conf_file = "./t.conf";

    opterr = 0;  //使getopt不行stderr输出错误信息

    while( (result = getopt(argc, argv, "hf::c")) != -1 )
    {
        switch(result)
        {
        case 'h':
            printf("option=h, optopt=%c, optarg=%s\n", optopt, optarg);
            break;
        case 'f':
            printf("option=f, optopt=%c, optarg=%s\n", optopt, optarg);
            break;
        case 'c':
            printf("option=c, optopt=%c, optarg=%s\n", optopt, optarg);
            break;
        case '?':
            printf("result=?, optopt=%c, optarg=%s\n", optopt, optarg);
            break;
        default:
            printf("default, result=%c\n",result);
            break;
        }
        printf("argv[%d]=%s\n", optind, argv[optind]);
    }

    printf("result=-1, optind=%d\n", optind);   //看看最后optind的位置

    for(result = optind; result < argc; result++)
        printf("-----argv[%d]=%s\n", result, argv[result]);

    //看看最后的命令行参数，看顺序是否改变了哈。
    for(result = 1; result < argc; result++)
        printf("\nat the end-----argv[%d]=%s\n", result, argv[result]);
}

void print_file_Statfs()
{
    struct statfs diskInfo;

    statfs("/home/", &diskInfo);
    unsigned long long blocksize = diskInfo.f_bsize;    //每个block里包含的字节数
    unsigned long long totalsize = blocksize * diskInfo.f_blocks;   //总的字节数，f_blocks为block的数目
    printf("Total_size = %llu B = %llu KB = %llu MB = %llu GB\n",
           totalsize, totalsize>>10, totalsize>>20, totalsize>>30);

    unsigned long long freeDisk = diskInfo.f_bfree * blocksize; //剩余空间的大小
    unsigned long long availableDisk = diskInfo.f_bavail * blocksize;   //可用空间大小
    printf("Disk_free = %llu MB = %llu GB\nDisk_available = %llu MB = %llu GB\n",
           freeDisk>>20, freeDisk>>30, availableDisk>>20, availableDisk>>30);
}

off_t get_file_offset()
{
    int fd;
    off_t off;
    char *file = "./t.txt";
    fd = open(file,O_RDONLY);
    off = lseek(fd,0,SEEK_END);

    return off;
}

int nf_hash()
{
    int PIC_STO_HASH_SHIFT = 24;
    int PIC_KEY_PREFIX = 8,i;
    char *str = "88bbb9eb5cb5a98ac9b5cd535c42ee24000455ac.bmi";
    static char map_table[128];
    int hv = 0;
    char c = 0;

    for (i='0'; i<='9'; i++)
    {
        map_table[i] = c++;
    }
    for (i='a'; i<='z'; i++)
    {
        map_table[i] = c++;
    }

    for (i=0; i<PIC_KEY_PREFIX; i++)
    {
        c = str[i];
        hv |= map_table[c];
        hv = hv << 4;
    }
    hv = hv >> 4;

    i = (1 << PIC_STO_HASH_SHIFT) - 1;

    return hv & i;
}

void unlikely_test()
{
    buff_t *bf = NULL;
    if(unlikely(bf)){
        printf("bf is not null\n");
    }else{
        printf("bf is null\n");
    }
}
