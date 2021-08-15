#include <iostream>

using namespace std;

typedef struct StackNode
{
    int data;
    struct StackNode *next;
} StackNode, *LinkStack;

//链栈的初始化
int InitStack(LinkStack &S)
{
    S = NULL;
    return 1;
}

//判断链表是否为空
int StackEmpty(LinkStack S)
{
    if (S == NULL)
        return 1;
    else
        return -1;
}

//入栈
int Push(LinkStack &S, int e)
{
    LinkStack p;
    p = new StackNode;
    p->data = e;
    p->next = S;
    S = p;
    return 1;
}

//出栈
int Pop(LinkStack &S, int &e)
{
    if (S == NULL)
        return -1;
    e = S->data;
    LinkStack p = S;
    S = S->next;
    delete p;
    return 1;
}

//取栈顶元素
int GetTop(LinkStack S){
    if (S != NULL) return S->data;
}