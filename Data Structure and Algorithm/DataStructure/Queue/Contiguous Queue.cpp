#include <iostream>

using namespace std;

typedef struct
{
    int *base; //初始化的动态分配存储空间
    int front; //头指针，若队列不空，指向队列头元素
    int rear;  //尾指针，若队列不空，指向队列尾元素的下一个位置
} SqQueue;

//队列初始化
int InitQueue(SqQueue &Q){
    Q.base = new int[10000];
    if (!Q.base) return -1;
    Q.front = Q.rear = 0;
    return 1;
}

//求队列的长度
int QueueLength(SqQueue Q){
    return (Q.rear - Q.front + 10000) % 10000;
}

//循环队列出队
int EnQueue(SqQueue &Q, int e){
    if ((Q.rear + 1) % 10000 == Q.front) return -1;
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear + 1) % 10000;
    return 1;
}

//取队头元素
int GetHead(SqQueue Q){
    if(Q.front!= Q.rear){
        return Q.base[Q.front];
    }
}