#include <iostream>

using namespace std;

#define Success 1
#define Fail 0

typedef struct DuLNode
{
    int data;                     //数据域
    struct DuLNode *prior, *next; //指向前一个数的指针，指向后一个数的指针
} DuLNode, *DuLinkList;

//双向链表的查找特定位置的结点
DuLinkList GetElemP_DuL(DuLinkList L, int i)
{
    DuLinkList p = L;

    //寻找第i个结点，p指向i个结点
    while (p && i > 0) {
        p = p->next;
        -- i;
    }
    return p;
}

//双向链表的插入，在带头结点的双向链表L中第i个位置之前插入e元素
int ListInsert_DuL(DuLinkList &L, int i, int e)
{
    DuLinkList p;

    //获取第i个位置结点的信息并赋值给p
    if (!(p = GetElemP_DuL(L, i))) {
        return Fail;
    }
    DuLinkList s;
    s->data = e;         //创建一个结点，并给该结点赋值
    s->prior = p->prior; //该节点的前驱指针应该等于原来在这个位置结点的前驱指针
    p->prior->next = s;  //第i-1位置结点的后继指针应该等于当前这个新结点的地址
    s->next = p;         //该结点的后继指针指向原来第i个位置的数的地址
    p->prior = s;        //原来第i个位置的数的前驱指针指向这个新结点

    return Success;
}

//双向链表的删除,删除带头结点的双向循环链表L的第i个元素，并用e返回
int ListDelete_DuL(DuLinkList &L, int i, int &e)
{
    DuLinkList p;

    //获取第i个位置结点的信息并赋值给p
    if (!(p = GetElemP_DuL(L, i))) {
        return Fail;
    }
    e = p->data;
    p->prior->next = p->next;
    p->next->prior = p->prior;
    free(p);
    return Success;
}