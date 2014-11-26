
/*该函数与stat()类似，用于得到文件的属性，将其存入到结构体struct stat中*/
static int hello_getattr(const char *path, struct stat *stbuf)
{
    int res = 0;

    memset(stbuf, 0, sizeof(struct stat));   //用于初始化结构体stat

    if (strcmp(path, "/") == 0)
    {
        stbuf->st_mode = S_IFDIR | 0755;     //S_IFDIR 用于说明/为目录，详见
        stbuf->st_nlink = 2;                 //文件链接数
    }
    else if (strcmp(path, hello_path) == 0)
    {
        stbuf->st_mode = S_IFREG | 0444;     //S_IFREG用于说明/hello为常规文件
        stbuf->st_nlink = 1;
        stbuf->st_size = strlen(hello_str);  //设置文件长度为hello_str的长度
    }
    else
        res = -ENOENT;                      //返回错误信息，没有该文件或目录

    return res;                              //执行成功返回 0
}

/*该函数用于读取/目录中的内容，并在/目录下增加了 . .. hello三个目录项*/
static int hello_readdir(const char *path, void *buf, fuse_fill_dir_t filler,off_t offset, struct fuse_file_info *fi)
{
    (void) offset;
    (void) fi;

    if(strcmp(path, "/") != 0)
        return -ENOENT;

    customlog(filename,path);

    filler(buf, ".", NULL, 0);               // 在/目录下增加. 这个目录项
    filler(buf, "..", NULL, 0);              // 增加.. 目录项
    filler(buf, hello_path + 1, NULL, 0);    // 增加hello目录项

    return 0;
}

/* fill的定义：
     typedef int (*fuse_fill_dir_t) (void *buf, const char *name, const struct stat *stbuf, off_t off);
     其作用是在readdir函数中增加一个目录项
 */

/*用于打开hello文件*/
static int hello_open(const char *path, struct fuse_file_info *fi)
{
    customlog(filename,"hello_open start");
    if(strcmp(path, hello_path) != 0)
        return -ENOENT;

    if((fi->flags & 3) != O_RDONLY)
        return -EACCES;
    customlog(filename,"hello_open end");
    return 0;
}

/*读取hello文件时的操作，它实际上读取的是字符串hello_str的内容*/
static int hello_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    size_t len;
    (void) fi;
    if(strcmp(path, hello_path) != 0)
        return -ENOENT;

    len = strlen(hello_str);
    if (offset < len)
    {
        if (offset + size > len)
            size = len - offset;
        memcpy(buf, hello_str + offset, size);
    }
    else
        size = 0;

    return size;
}

/*注册上面定义的函数*/
static struct fuse_operations hello_oper =
{
    .getattr = hello_getattr,
    .readdir = hello_readdir,
    .open    = hello_open,
    .read    = hello_read,
};

/*用户只需要调用fuse_main()，剩下的事就交给FUSE了*/
int main(int argc, char *argv[])
{
    return fuse_main(argc, argv, &hello_oper, NULL);
}

