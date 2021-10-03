#include <iostream>

using namespace std;

#define Success 1
#define Fail 0

class L{
    public:
        int length;
        int a[1000];
};

//构建一个空的线性表L
L InitList();

//销毁线性表L
int DestroyList(L &l);

//将线性表L重置为空表
int ClearList(L &l);

//若线性表L为空表，则返回True,否则返回False
int ListEmpty(L &l);

//返回线性表L中的数据元素个数
int ListLength(L &l);

//用e返回线性表L中的第i个数据元素的值
int GetElem(L &l,int i,int &e);

//返回L中第1个与e满足compare()的数据元素的次序，若这样的数据元素不存在则返回值为0
int LocateElem(L &l, int e);

//若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱，否则操作失败；pre_e无意义
int PriorElem(L &l, int cur_e, int &pre_e);

//若cur_e是L的数据元素，且不是最后一个，则用pre_e返回它的后驱，否则操作失败；pre_e无意义
void NextElem(L &l, int cur_e, int &next_e);

//删除L的第i个数据元素，并用e返回其值，L的长度减一
int ListDelete(L &l, int i, int &e);

//依次对线性表中每个元素调用visited()，visited()函数就是对元素的具体操作
int ListTraverse(L &l);