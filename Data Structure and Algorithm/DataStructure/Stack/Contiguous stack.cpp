#include <iostream>

using namespace std;

//顺序栈的表示
typedef struct
{
    int *base;     //栈底指针
    int *top;      //栈顶指针
    int stacksize; //栈可用最大容量
} SqStack;

//初始化操作，构造一个空栈S
int InitStack(SqStack &S)
{
    S.base = new int[10000];
    if (!S.base)
        return -1;  //内存分配失败
    S.top = S.base; //栈顶指针等于栈底指针
    S.stacksize = 10000;
    return 1;
}

//销毁栈操作
void DestroyStack(SqStack &S)
{
    if (S.base)
    {
        delete S.base;
        S.stacksize = 0;
        S.base = S.top = NULL;
    }
}

//判断是否为空栈
int StackEmpty(SqStack S)
{
    if (S.top == S.base)
        return 1;
    else
        return 0;
}

//求栈的长度
int StackLength(SqStack S)
{
    return S.top - S.base;
}

//取栈顶元素
void GetTop()
{
}

//栈置空操作，清空顺序栈
int ClearStack(SqStack S)
{
    if (S.base)
        S.top = S.base;
    return 1;
}

//入栈操作
int Push(SqStack &S, int e)
{
    if (S.top - S.base == S.stacksize)
    {
        return -1;
    }           //先判断栈是否满了，如果满了就返回-1
    *S.top = e; //实际上
    S.top++;
    return 1;
}

//出栈操作
int Pop(SqStack &S, int &e)
{
    if (S.top == S.base)
        return -1; //表示此时栈是空的
    --S.top;
    e = *S.top;
    return 1;
}