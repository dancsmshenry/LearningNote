#include <iostream>

using namespace std;

typedef struct
{
    int key;
} ElemType;

typedef struct
{
    ElemType *R;
    int length;
} SSTable;
SSTable ST;

int Search_Seq(SSTable ST, int key)
{//挡length过大的时候，能够极大的节约时间
    ST.R[0].key = key;//设置监视哨的顺序查找
    for (i = ST.length; ST.R[i].key != key; --i)
        ;
    return i;
}

//非递归版本
int Search_Bin(SSTable ST, int key){
    int low = 1, high = ST.length;//置区间初值
    while (low <= high){
        int mid = low + high >> 1;
        if (ST.R[mid].key == key) return mid;//找到待查元素
        else if (key < ST.R[mid].key) high = mid - 1;//缩小区间，继续前半区查找
        else low = mid + 1;//继续在后半区查找
    }
    return 0;//不存在这个元素
}