#include <iostream>

using namespace std;

//定义链表L，LinkList L;
//定义结点指针p，LNode *p;等价于LinkList p;
typedef struct Lnode
{                       //声明结点的类型和指向结点的指针类型
    int data;           //结点的数据域
    struct Lnode *next; //结点的指针域
} Lnode, *LinkList;     //LinkList为指向结构体Lnode的指针类型，以后写就不用加*,Lnode *l等价于Linklist l
                        //即*LinkList也可以认为是指向该类型结点的一个指针

/*统一定义
typedef Struct{
    char num[8];
    char name[8];
    int scort;
}ElemType;

typedef struct Lnode{
    ElemType data;
    struct Lnode *next;
}Lnode, *LinkList;
*/

//单链表的初始化
int InitList_L(LinkList &L)
{
    L = new Lnode;  //生成新结点作头结点，用头指针L指向头结点
    L->next = NULL; //将头结点的指针域置空
    return 1;
}

//判断链表是否为空
int ListEmpty(LinkList L)
{
    if (L->next)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

//单链表的销毁
int DestroyList_L(LinkList L)
{             //从头指针开始，依次销毁所有的结点
    Lnode *p; //LinkList p;
    while (L)
    {
        p = L;
        L = L->next;
        delete p;
    }
}

//清空链表
int ClearList(LinkList &L)
{
    Lnode *p, *q;
    p = L->next;
    while (p)
    { //如果没到表尾
        q = p->next;
        delete p;
        p = q;
    }
    L->next = NULL; //头结点指针域为空
    return 1;
}

//求单链表的长度
int ListLength_L(LinkList L)
{
    LinkList p;
    p = L->next; //p指向第一个结点
    int i = 0;
    while (p)
    { //遍历链表，统计结点个数
        ++i;
        p = p->next;
    }
    return i;
}

//获取线性表L中的某个数据元素的内容，通过变量e返回
int GetElem_L(LinkList L, int i, int &e)
{
    LinkList p = L->next;
    int j = 1;         //初始化
    while (p && j < i) //注意，一般是从1开始计数的
    {
        p = p->next; //向后扫描，直到p指向第i个元素或p为空
        ++j;
    }
    if (!p || j > i)
        return 0; //第i个元素不存在
    e = p->data;  //取第i个元素
    return 1;
}

//按值查找-根据指定数据获取该数据的位置序号
int LocateElem_L(LinkList L, int e)
{
    LinkList p = L->next;
    int j = 1; //初始化
    while (p && p->data != e)
    {
        p = p->next;
        ++j;
    }
    if (p)
        return j;
    else
        return 0;
}

//在L中第i个元素之前插入数据元素e
int ListInsert_L(LinkList &L, int i, int e)
{
    int j = 0;
    LinkList p = L;
    while (p && j < i - 1) //寻找第i-1个结点，p指向i-1个结点
    {
        p = p->next;
        ++j;
    }
    if (!p || j > i - 1) //i大于表长+1或者小于1，插入位置非法
        return 0;
    LinkList s = new Lnode;
    s->data = e;       //生成新结点，将结点s的数据域设为e
    s->next = p->next; //将结点s插入L中
    p->next = s;
    return 1;
}

//将线性表L中第i个数据元素删除
int ListDelte_L(LinkList &L, int i, int &e)
{
    LinkList p = L;
    int j = 0;
    while (p->next && j < i - 1)
    {
        p = p->next;
        ++j;
    } //寻找第i个结点，并令p指向其前驱
    if (!(p->next) || j < i - 1)
        return 0;         //删除位置不合理
    LinkList q = p->next; //临时保存被删结点的地址
    e = q->data;          //保存被删结点的数据域
    p->next = q->next;    //是该点前面的点的地址变为该点后面的点的地址
    delete q;             //释放删除节点的空间
    return 1;
}

//头插法建立链表
void CreateList_H(LinkList &L, int n)
{
    LinkList L = new Lnode;
    L->next = NULL; //先建立一个带头结点的单链表
    for (int i = n; i > 0; --i)
    {
        LinkList p = new Lnode; //创建一个新结点
        cin >> p->data;         //输入新结点的数据
        p->next = L->next;
        L->next = p; //这一步和上一步都是插入到表头
    }
}

//尾插法建立链表
void CreateList_R(LinkList &L, int n) //n表示链表的长度
{
    LinkList L = new Lnode;
    L->next = NULL;
    LinkList r = L; //尾指针r指向头结点
    for (int i = 0; i < n; ++i)
    {
        LinkList p = new Lnode;
        cin >> p->data; //生成新节点，输入元素值
        p->next = NULL;
        r->next = p; //插入到表尾
        r = p;       //r指向新的尾节点
    }
}

//针对带尾指针的循环链表的合并
LinkList Connect(LinkList Ta, LinkList Tb)
{
    LinkList p = Ta->next;
    Ta->next = Tb->next->next;
    delete Tb->next;
    Tb->next = p;
    return Tb;
}