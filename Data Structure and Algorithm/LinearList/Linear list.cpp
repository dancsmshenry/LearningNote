#include <iostream>

using namespace std;

struct
{
    int length;
    int a[1000];
} L;

//构建一个空的线性表L
void InitList(&l)
{
}

//销毁线性表L
void DestroyList(&l)
{
}

//将线性表L重置为空表
void ClearList(&L)
{
}

//若线性表L为空表，则返回True,否则返回False
int ListEmpty(L)
{
    return 0;
}

//返回线性表L中的数据元素个数
int ListLength(L)
{
    return 1;
}

//用e返回线性表L中的第i个数据元素的值
void GetElem(L, i, &e)
{
}

//返回L中第1个与e满足compare()的数据元素的次序，若这样的数据元素不存在则返回值为0
int LocateElem(L, e, compare())
{
    return 0;
}

//若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱，否则操作失败；pre_e无意义
void PriorElem(L, cur_e, &pre_e)
{
}

//若cur_e是L的数据元素，且不是最后一个，则用pre_e返回它的后驱，否则操作失败；pre_e无意义
void NextElem(L, cur_e, &next_e)
{
}

//删除L的第i个数据元素，并用e返回其值，L的长度减一
void ListDelete(&L, i, &e)
{
}

//依次对线性表中每个元素调用visited()，visited()函数就是对元素的具体操作
void ListTraverse(&L, visited())
{
}