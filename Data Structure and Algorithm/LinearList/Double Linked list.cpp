#include <iostream>

using namespace std;

typedef struct DuLNode
{
    int data;                     //数据域
    struct DuLNode *prior, *next; //指向前一个数的指针，指向后一个数的指针
} DuLNode, *DuLinkList;

DuLinkList GetElemP_DuL(DuLinkList L, int i)
{
    int j = 0;
    DuLinkList p = L;
    while (p && j < i) //寻找第i个结点，p指向i个结点
    {
        p = p->next;
        ++j;
    }
    return p;
}

//双向链表的插入
int ListInsert_DuL(DuLinkList &L, int i, int e)
{
    //在带头结点的双向链表L中第i个位置之前插入e元素
    DuLinkList p;
    if (!(p = GetElemP_DuL(L, i))) //获取第i个位置结点的信息并赋值给p
        return 0;
    DuLinkList s;
    s->data = e;         //创建一个结点，并给该结点赋值
    s->prior = p->prior; //该节点的前驱指针应该等于原来在这个位置结点的前驱指针
    p->prior->next = s;  //第i-1位置结点的后继指针应该等于当前这个新结点的地址
    s->next = p;         //该结点的后继指针指向原来第i个位置的数的地址
    p->prior = s;        //原来第i个位置的数的前驱指针指向这个新结点
    return 1;
}

//双向链表的删除
int ListDelete_DuL(DuLinkList &L, int i, int &e)
{
    //删除带头结点的双向循环链表L的第i个元素，并用e返回
    DuLinkList p;
    if (!(p = GetElemP_DuL(L, i))) //获取第i个位置结点的信息并赋值给p
        return 0;
    e = p->data;
    p->prior->next = p->next;
    p->next->prior = p->prior;
    free(p);
    return 1;
}