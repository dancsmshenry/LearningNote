#include <iostream>

using namespace std;

typedef struct Qnode
{
    int data;
    struct Qnode *next;
} Qnode, *QuenePtr;

typedef struct
{
    QuenePtr front;
    QuenePtr rear;
} LinkQueue;

//链表初始化
int InitQueue(LinkQueue &Q)
{
    Q.front = Q.rear = (QuenePtr)malloc(sizeof(Qnode));
    if (!Q.front)
        return -1;
    Q->next = NULL;
    return 1;
}

//销毁链表
int DestoryQueue(LinkQueue &Q)
{
    //从头结点开始，依次释放所有结点
    while (Q.front)
    {
        QuenePtr p = Q.front->next;
        free(Q.front);
        Q.front = p;
    }
}

//将元素e入队
int EnQueue(LinkQueue &Q, int e){
    QuenePtr  p;
    if (!p) return -1;
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return 1;
}

//出队
int DeQueue(LinkQueue &Q, int &e){
    if (Q.front == Q.rear) return -1;
    QuenePtr p = Q.front->next;
    e = p->data;
    Q.front ->next = p->next;
    if (Q.rear == p) Q.rear = Q.front;
    delete p;
    return 1;
}

//求链队列的队头元素
int GetHead(LinkQueue Q, int &e){
    if (Q.front == Q.rear) return -1;
    e = Q->front->next->data;
    return 1;
}