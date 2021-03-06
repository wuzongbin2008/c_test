#include <stdio.h>
#include "sort.h"

#define N 10
int n = 10;
//int k[] = {2,3,1,5,0,4,9,8,7,6};
int k[] = {2,3,1,5,0,4,9,8,7,6};
int a[] = {3,5,8};
int b[] = {4,7,9,10};
int c[7];
int d[3] = {1,6,2};
int t[10];
int cnt1 = 0,cnt2 = 0;

void sort_test()
{

    int i;

    //iteration_merge_sort(k, n);
    straight_insert_sort2();

    printf("\nsort result:\n");
    for( i=0; i < n; i++)
    {
        printf("%d\t", k[i]);
    }
    printf("\n");
}

/*
* 有1,2,....一直到n的无序数组,求排序算法,并且要求时间复杂度为O(n),
* 空间复杂度O(1),使用交换,而且一次只能交换两个数
*/
void sort_on_and_o1()
{
    int temp, i, n = 0;
    int a[] = {10, 2, 9, 5, 1, 8, 4, 7, 6, 3};
    int len = sizeof(a) / sizeof(int);
    printf("len: %d\n", len);
    //exit(EXIT_SUCCESS);
    for(i = 0; i < len; )
    {
        n++;
        //printf("n: %d\n", n);

        if (a[i] == i + 1)
        {
            i++;
        }
        else
        {
            temp = a[a[i] - 1];
            a[a[i] - 1] = a[i];
            a[i] = temp;
        }
    }
    printf("n: %d\n", n);
    printf("i: %d\n", i);
    print_k(a, len);
}
void ReverseArray()
{
    int arr[] = { 1, 23, 2, 34, 21, 45, 26, 22, 41, 66, 74, 91, 17, 64 };
    int len = sizeof(arr) / sizeof(arr[0]);
    int i;

    if (arr == NULL || len <= 0)
        printf("数组中无元素，变换毛线啊。");
    else
    {
        int begin = 0;
        int end = len - 1;
        while (begin < end)
        {
            printf("begin: %d\n", begin);
            printf("end: %d\n", end);
            while (arr[begin] % 2 == 1 && end>begin)
                begin++;
            while (arr[end] % 2 == 0 && end > begin)
                end--;
            Swap(arr[begin], arr[end]);
        }
    }

    printf("经过变换后的数组为：");
    for (i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
void Swap(int *a, int *b)
{
    int temp = a;
    a = b;
    b = temp;
}


//radix sort
void radix_sort()
{
    RedType d[N]= {{278,1},{109,2},{63,3},{930,4},{589,5},{184,6},{505,7},{269,8},{8,9},{83,10}};
    SLList l;
    int *adr;
    InitList(&l,d,N);
    printf("排序前(next域还没赋值):\n");
    print(&l);
    RadixSort(&l);
    printf("排序后(静态链表):\n");
    print(&l);
    adr=(int*)malloc((l.recnum)*sizeof(int));
    Sort(&l,adr);
    Rearrange(&l,adr);
    printf("排序后(重排记录):\n");
    print(&l);
}
void InitList(SLList *L,RedType D[],int n)
{
    // 初始化静态链表L（把数组D中的数据存于L中）
    char c[MAX_NUM_OF_KEY],c1[MAX_NUM_OF_KEY];
    int i,j,max=D[0].key; // max为关键字的最大值
    for(i=1; i<n; i++)
        if(max<D[i].key)
            max=D[i].key;
    L->keynum= (int)ceil(log10(max));
    L->recnum=n;
    for(i=1; i<=n; i++)
    {
        L->r[i].otheritems=D[i-1].otherinfo;
        sprintf(c, "%d", D[i-1].key); // 将10进制整型转化为字符型,存入c
        for(j=strlen(c); j<L->keynum; j++) // 若c的长度<max的位数,在c前补'0'
        {
            strcpy(c1,"0");
            strcat(c1,c);
            strcpy(c,c1);
        }
        for(j=0; j<L->keynum; j++)
            L->r[i].keys[j]=c[L->keynum-1-j];
    }
}
void RadixSort(SLList *L)
{
    // L是采用静态链表表示的顺序表。对L作基数排序，使得L成为按关键字
    // 自小到大的有序静态链表，L.r[0]为头结点。算法10.17
    int i;
    ArrType f,e;
    for(i=0; i<L->recnum; ++i)
        L->r[i].next=i+1;
    L->r[L->recnum].next=0; // 将L改造为静态链表
    for(i=0; i<L->keynum; ++i)
    {
        // 按最低位优先依次对各关键字进行分配和收集
        Distribute(L->r,i,f,e); // 第i趟分配
        Collect(L->r,f,e); // 第i趟收集
        printf("第%d趟收集后:\n",i+1);
        printl(L);
        printf("\n");
    }
}
void Distribute(SLCell r[],int i,ArrType f,ArrType e) // 算法10.15
{
    // 静态键表L的r域中记录已按(keys[0],…,keys[i-1])有序。本算法按
    // 第i个关键字keys[i]建立RADIX个子表,使同一子表中记录的keys[i]相同。
    // f[0..RADIX-1]和e[0..RADIX-1]分别指向各子表中第一个和最后一个记录
    int j,p;
    for(j=0; j<RADIX; ++j)
        f[j]=0; // 各子表初始化为空表
    for(p=r[0].next; p; p=r[p].next)
    {
        j=ord(r[p].keys[i]); // ord将记录中第i个关键字映射到[0..RADIX-1]
        if(!f[j])
            f[j]=p;
        else
            r[e[j]].next=p;
        e[j]=p; // 将p所指的结点插入第j个子表中
    }
}
void Collect(SLCell r[],ArrType f,ArrType e)
{
    // 本算法按keys[i]自小至大地将f[0..RADIX-1]所指各子表依次链接成
    // 一个链表，e[0..RADIX-1]为各子表的尾指针。算法10.16
    int j,t;
    for(j=0; !f[j]; j=succ(j)); // 找第一个非空子表，succ为求后继函数
    r[0].next=f[j];
    t=e[j]; // r[0].next指向第一个非空子表中第一个结点
    while(j<RADIX-1)
    {
        for(j=succ(j); j<RADIX-1&&!f[j]; j=succ(j)); // 找下一个非空子表
        if(f[j])
        {
            // 链接两个非空子表
            r[t].next=f[j];
            t=e[j];
        }
    }
    r[t].next=0; // t指向最后一个非空子表中的最后一个结点
}
int ord(char c)
{
    // 返回k的映射(个位整数)
    return c-'0';
}
int succ(int i)
{
    // 求后继函数
    return ++i;
}
void printl(SLList *L)
{
    // 按链表输出静态链表
    int i=L->r[0].next,j;
    while(i)
    {
        for(j=L->keynum-1; j>=0; j--)
            printf("%c",L->r[i].keys[j]);
        printf(" ");
        i=L->r[i].next;
    }
}
void print(SLList *L)
{
    // 按数组序号输出静态链表
    int i,j;
    printf("keynum=%d recnum=%d\n",L->keynum,L->recnum);
    for(i=1; i<=L->recnum; i++)
    {
        printf("keys=");
        for(j=L->keynum-1; j>=0; j--)
            printf("%c",L->r[i].keys[j]);
        printf(" otheritems=%d next=%d\n",L->r[i].otheritems,L->r[i].next);
    }
}
void Sort(SLList *L,int adr[]) // 改此句(类型)
{
    // 求得adr[1..L.length]，adr[i]为静态链表L的第i个最小记录的序号
    int i=1,p=L->r[0].next;
    while(p)
    {
        adr[i++]=p;
        p=L->r[p].next;
    }
}
void Rearrange(SLList *L,int adr[]) // 改此句(类型)
{
    // adr给出静态链表L的有序次序，即L.r[adr[i]]是第i小的记录。
    // 本算法按adr重排L.r，使其有序。算法10.18(L的类型有变)
    int i,j,k;
    for(i=1; i<L->recnum; ++i) // 改此句(类型)
        if(adr[i]!=i)
        {
            j=i;
            L->r[0]=L->r[i]; // 暂存记录L.r[i]
            while(adr[j]!=i)
            {
                // 调整L.r[adr[j]]的记录到位直到adr[j]=i为止
                k=adr[j];
                L->r[j]=L->r[k];
                adr[j]=j;
                j=k; // 记录按序到位
            }
            L->r[j]=L->r[0];
            adr[j]=j;
        }
}


//merge sort
void iteration_merge_sort(int k[], int n)
{
    int i, left_min, left_max, right_min, right_max,next, j, m;
    int *tmp = (int *)malloc(n * sizeof(int));

    for(i = 1; i < n; i *= 2)
    {
        for(left_min = 0; left_min < n - i; left_min = right_max)
        {
            right_min = left_max = left_min + i;
            right_max = left_max + i;

            if(right_max > n) right_max = n;

            next = 0;
            int tmp2;
            while(left_min < left_max && right_min < right_max)
            {
                if(k[left_min] < k[right_min])
                {
                    tmp2 = k[left_min++];
                    tmp[next++] = tmp2;
                }
                else
                {
                    tmp2 = k[right_min++];
                    tmp[next++] = tmp2;
                }
            }

            while(left_min < left_max)
            {
                printf("left_min: %d\tleft_max: %d\nright_min: %d\tright_max: %d\n\n", left_min, left_max, right_min, right_max);
                k[--right_min] = k[--left_max];
            }

            //print_k(tmp, next);
            while(next > 0)
            {
                m = tmp[--next];
                k[--right_min] = m;
            }

            printf("\ni= %d:\t", i);
            for( j = 0; j < 10; j++)
            {
                printf("%d\t", k[j]);
            }
            printf("\n");
        }
    }
}
void recursion_merge_sort(int k[],int n)
{
    if (n > 1)
    {
        int *list1 = k;
        int list1_size = n/2;
        int *list2 = k + n/2;
        int list2_size = n - list1_size;

        recursion_merge_sort(list1, list1_size);
        recursion_merge_sort(list2, list2_size);

        merging(list1, list1_size, list2, list2_size);

    }
}
void merging(int *list1, int size1, int *list2, int size2)
{
    int i,j,k,m,temp[n];
    i = j = k = 0;

    while(i < size1 && j < size2)
    {
        if(list1[i] < list2[j])
        {
            temp[k++] = list1[i++];
        }
        else
        {
            temp[k++] = list2[j++];
        }
    }
    while(i < size1)
    {
        temp[k++] = list1[i++];
    }
    while(j < size2)
    {
        temp[k++] = list2[j++];
    }
    for(m = 0; m < (size1 + size2); m++)
    {
        list1[m] = temp[m];
    }
}
void mergeAB()
{
    int i,j,k;
    int n = 3, m=4;
    for(i=0,j=0,k=0; k < n+m ; k++)
    {
        if(i == n )
        {
            c[k] = b[j++];
            continue;
        }
        if(j == m )
        {
            c[k] = a[i++];
            continue;
        }
        c[k] = (less(a[i],b[j])) ? a[i++] : b[j++];
    }

    for(i=0; i<7; i++)
        printf("%d\t", c[i]);
}
int less(int a,int b)
{
    if(a < b)
    {
        //printf("less\n");
        return 1;
    }
    else
    {
        return 0;
    }
}


//insert sort
void straight_insert_sort()
{
    // 直接插入排序
    int i,j,tmp;

    for(i=1; i<n; i++)
    {
        tmp = k[i]; //sentry
        printf("i=%d\tk[i]=%d\tk[i-1]=%d\ttmp = %d\n",i,k[i],k[i-1],tmp);
        if(k[i] < k[i-1])
        {
            printf("\ni=%d\ttmp = %d\n",i,tmp);

            for(j=i-1; k[j]>tmp; j--)
            {
                printf("i=%d\tj=%d\tk[j]:%d\tk[j+1]: %d\n",i,j,k[j],k[j+1]);
                k[j+1] = k[j];
            }
            printf("j=%d\tk[j]=%d\n",j,k[j]);
            k[j+1] = tmp;
            printf("\n");
        }
    }

    //顺序表插入排序的函数(3个)
    //void InsertSort(SqList *L)
    //{
    //    // 对顺序表L作直接插入排序。算法10.1
    //    int i,j;
    //    for(i=2; i<=L.length; ++i)
    //        if LT(L.r[i].key,L.r[i-1].key) // "<",需将L.r[i]插入有序子表
    //        {
    //            L.r[0]=L.r[i]; // 复制为哨兵
    //            for(j=i-1; LT(L.r[0].key,L.r[j].key); --j)
    //                L.r[j+1]=L.r[j]; // 记录后移
    //            L.r[j+1]=L.r[0]; // 插入到正确位置
    //        }
    //}
}
void straight_insert_sort2()
{
    int i, j, tmp;

    for( i = 1; i < n; i++ )
    {
        for( j = i - 1; j > 0; j--)
        {
            if(k[j-1] > k[j])
            {
                tmp = k[j];
                k[j] = k[j-1];
                k[j-1] = tmp;
            }
        }
    }
}
void binary_insert_sort()
{
    // 折半插入排序。算法10.2
    int i, j, m, low, high, tmp, v;
    for (i=2; i<=n; ++i)
    {
        tmp = k[i];
        low = 1;
        high = i-1;
        while (low <= high)
        {
            // 在r[low..high]中折半查找有序插入的位置
            m = (low+high) / 2; // 折半
            v = k[m];
            if (tmp < v)
                high = m-1; // 插入点在低半区
            else
                low = m+1; // 插入点在高半区
        }
        for (j=i-1; j>=high+1; --j)
            k[j+1] = k[j]; // 记录后移
        k[high+1] = tmp; // 插入

    }
}
void P2_InsertSort()
{
    // 2_路插入排序
    int i, j, first, final, v, first_v, final_v;
    //RedType *d;
    //d = (RedType*)malloc(N * sizeof(RedType)); // 生成L.length个记录的临时空间
    RedType d[N]= {{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8},{55,9},{4,10}};

    //init
    SqList L;
    int dt[3]= {5,3,1}; // 增量序列数组
    for(i=0; i<N; i++)
        L.r[i+1]=d[i];
    L.length=N;

    print_RedType(d);
    memset(d, 0, sizeof(d));
    printf("RedType d[N] memset :\n");
    print_RedType(d);
    printf("l排序前:\n");
    print_SqList(L);

    //sort
    d[0] = L.r[1]; // 设L的第1个记录为d中排好序的记录(在位置[0])
    first = final = 0; // first、final分别指示d中排好序的记录的第1个和最后1个记录的位置
    for(i=2; i<=L.length; ++i)
    {
        // 依次将L的第2个～最后1个记录插入d中
        v = L.r[i].key;
        first_v = d[first].key;
        final_v = d[final].key;
        if(L.r[i].key < d[first].key)
        {
            // 待插记录小于d中最小值，插到d[first]之前(不需移动d数组的元素)
            first = (first - 1 + L.length) % L.length; // 设d为循环向量
            d[first] = L.r[i];
        }
        else if(L.r[i].key > d[final].key)
        {
            // 待插记录大于d中最大值，插到d[final]之后(不需移动d数组的元素)
            final = final+1;
            d[final] = L.r[i];
        }
        else
        {
            // 待插记录大于d中最小值，小于d中最大值，插到d的中间(需要移动d数组的元素)
            j = final++; // 移动d的尾部元素以便按序插入记录
            while(L.r[i].key < d[j].key)
            {
                d[(j + 1) % L.length] = d[j];
                j=(j - 1 + L.length) % L.length;
            }
            d[j+1] = L.r[i];
        }
    }

    for(i=1; i <= L.length; i++) // 把d赋给L.r
        L.r[i] = d[(i + first - 1) % L.length]; // 线性关系

    printf("l排序后:\n");
    print_SqList(L);
}
void shell_sort()
{
    //希尔排序
    int i,j,tmp;
    int gap = n;

    do
    {
        gap = gap/6+1;
        for(i=gap; i<n; i++)
        {
            //printf("i=%d\tk[i]=%d\tk[i-1]=%d\ttmp = %d\n",i,k[i],k[i-1],tmp);
            if(k[i] < k[i-gap])
            {
                tmp = k[i];
                //printf("\ni=%d\ttmp = %d\n",i,tmp);

                for(j=i-gap; k[j]>tmp; j-=gap)
                {
                    //printf("i=%d\tj=%d\tk[j]:%d\tk[j+1]: %d\n",i,j,k[j],k[j+1]);
                    k[j+gap] = k[j];
                }
                //printf("j=%d\tk[j]=%d\n",j,k[j]);
                k[j+gap] = tmp;
                //printf("\n");
            }
        }
    }
    while(gap > 1);
}
void shell_sort2()
{
    int i, j, tmp;
    int dk = 3;

    for(i=dk+1; i<n; i++)
    {
        if(k[i] < k[i-dk])
        {
            tmp = k[i];
            for(j=i-dk; j>0 && tmp<k[j]; j-=dk)
            {
                k[j+dk] = k[j];
            }
            k[j+dk] = tmp;
        }
    }
}
void print_SqList(SqList L)
{
    int i;
    for(i=1; i<=L.length; i++)
        printf("%d ",L.r[i].key);
    printf("\n");
}
void print_RedType(RedType *arr)
{
    int i, n;
    //n = sizeof(arr)/sizeof(RedType);
    //printf("arr len: %d\n", n);
    for (i = 0; i < N; i++)
    {
        printf("%d\t", arr[i].key);
    }
    printf("\n");
}


//select sort
void select_sort()
{
    int i,j,min,tmp;
    cnt1 = 0;
    cnt2 = 0;

    for(i=0; i<n-1; i++)
    {
        min = i;
        for(j=i+1; j<n; j++)
        {
            cnt1++;
            if(k[j] < k[min])
            {
                min = j;
            }
        }

        if(min != i)
        {
            cnt2++;
            tmp = k[min];
            k[min] = k[i];
            k[i] = tmp;
        }
    }
    printf("compare count: %d,\tmove count: %d\n",cnt1,cnt2);
}
#define N 8
void HeapSort_test()
{
    RedType d[N]= {{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
    HeapType h;
    int i;

    for(i=0; i<N; i++)
        h.r[i+1]=d[i];
    h.length=N;

    printf("排序前:\n");
    print_heapsort(h);

    HeapSort(&h);

    printf("排序后:\n");
    print_heapsort(h);
}
void HeapAdjust(HeapType *H, int s, int m) // 算法10.10
{
    HeapType ht;
    //RedType d[N]= {{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
    // 已知H->r[s..m]中记录的关键字除H->r[s].key之外均满足堆的定义，本函数
    // 调整H->r[s]的关键字,使H->r[s..m]成为一个大顶堆(对其中记录的关键字而言)
    RedType rc;
    int j, t, t2, t3;
    rc = H->r[s];
    for(j=2*s; j<=m; j*=2)
    {
        t = H->r[j].key;
        t2 = H->r[j+1].key;
        // 沿key较大的孩子结点向下筛选
        if(j<m && LT(H->r[j].key, H->r[j+1].key))
            ++j; // j为key较大的记录的下标

        if(!LT(rc.key, H->r[j].key))
            break; // rc应插入在位置s上

        H->r[s] = H->r[j];
        s = j;
    }
    H->r[s] = rc; // 插入

    //debug
    ht = *H;
    t3 = H->r[s].key;
}
void HeapSort(HeapType *H)
{
    // 对顺序表H进行堆排序。算法10.11
    RedType t;
    HeapType ht;
    int i;

    for(i=H->length/2; i>0; --i) // 把H->r[1..H.length]建成大顶堆
    {
        HeapAdjust(H,i,H->length);
        ht = *H;
    }

    for(i=H->length; i>1; --i)
    {
        // 将堆顶记录和当前未经排序子序列H->r[1..i]中最后一个记录相互交换
        t=H->r[1];
        H->r[1]=H->r[i];
        H->r[i]=t;
        HeapAdjust(H,1,i-1); // 将H->r[1..i-1]重新调整为大顶堆
    }
}
void print_heapsort(HeapType H)
{
    int i;
    for(i=1; i<=H.length; i++)
        printf("(%d,%d)",H.r[i].key,H.r[i].otherinfo);
    printf("\n");
}


//quick sort
void quick_sort()
{
    qk_sort(k,0,n-1);
}
void qk_sort(int k[], int low , int high)
{
    int point;
    if(low < high)
    {
        point = partition(k, low, high);
        printf("point: %d\n", point);
        qk_sort(k, low, point-1);
        qk_sort(k, point+1, high);
    }
}
int partition(int k[],int low, int high)
{
    int point;
    point = k[low];

    while(low < high)
    {
        while(low < high && k[high] >= point)
        {
            high--;
        }
        swap(k,low,high);
        while(low < high && k[low] <= point)
        {
            low++;
        }
        swap(k,low,high);
    }

    return low;
}
void swap(int k[],int low,int high)
{
    int temp;

    temp = k[low];
    k[low] = k[high];
    k[high] = temp;
}


//swap sort
void bubble_sort(int k[],int n)
{
    int i,j,tmp;
    cnt1 = 0;
    cnt2 = 0;

    for(i = 0; i<n-1; i++)
    {
        for(j = i+1; j<n; j++)
        {
            cnt1++;
            if(k[i] > k[j])
            {
                cnt2++;
                tmp = k[i];
                k[i] = k[j];
                k[j] = tmp;
            }
        }
    }
    printf("compare count: %d,\tmove count: %d\n",cnt1,cnt2);
}
void bubble_sort2(int k[],int n)
{
    int i,j,tmp;
    cnt1 = 0;
    cnt2 = 0;

    for(i = 0; i < n-1; i++)
    {
        for(j = n-1; j > i; j--)
        {
            cnt1++;
            if(k[j-1] > k[j])
            {
                cnt2++;
                tmp = k[j-1];
                k[j-1] = k[j];
                k[j] = tmp;
            }
        }
    }
    printf("compare count: %d,\tmove count: %d\n",cnt1,cnt2);
}
void bubble_sort3(int k[],int n)
{
    int i,j,tmp,flag;

    flag = 1;
    cnt1 = 0;
    cnt2 = 0;

    for(i = 0; i < n-1 && flag; i++)
    {
        for(j = n-1; j > i; j--)
        {
            flag = 0;
            cnt1++;
            if(k[j-1] > k[j])
            {
                cnt2++;
                tmp = k[j-1];
                k[j-1] = k[j];
                k[j] = tmp;
                flag = 1;
            }
        }
    }
    printf("compare count: %d,\tmove count: %d\n",cnt1,cnt2);
}

void print_k(int a[], int n)
{
    int i;

    for( i=0; i < n; i++)
    {
        printf("%d\t", a[i]);
    }
    printf("\n");
}
