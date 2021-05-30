#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

void test01(){
    stack<int> s;
    //插入元素
    s.push(10);
    s.push(20);
    s.push(30);

    while (s.size() != 0){
        cout << "栈顶为：" << s.top() << endl;//返回栈顶元素
        s.pop();//踢出栈顶元素
    }

    cout << s.size() << endl;
}

int main(){
    test01();
}
/**
 * 先进后出
 * 栈顶top
 * 压栈push
 * 弹出栈顶pop
 * 大小size
 * 是否为空empty
 **/ 