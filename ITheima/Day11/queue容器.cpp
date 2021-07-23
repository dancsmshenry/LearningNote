#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

void test01(){
    queue<int> q;
    q.push(1);//向队尾添加元素
    q.pop();//从队头移除第一个元素
    int a1 = q.back();//返回最后一个元素（队尾处）
    int a2 = q.front();//返回第一个元素
    int a3 = q.size();//返回队列的大小
    bool a4 = q.empty();//判断队列是否为空
}

void test02(){
    queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);
    
    while (!q.empty()){
        cout << "队头元素为：" << q.front() << endl;
        cout << "队尾元素为：" << q.back() << endl;
        q.pop(); 
        cout << endl;
    }
}

int main(){
    test02();
}
/**
 * 没有迭代器
 * 先进后出
 * 队头 front 队尾 back
 * 入队 push
 * 弹出队头 pop
 * 大小 size
 **/ 