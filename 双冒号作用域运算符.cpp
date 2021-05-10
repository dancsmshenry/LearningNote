#include <iostream>

using namespace std;

int atk = 200;

void test_01(){
    int atk = 100;
    cout << "局部变量：" << atk <<endl;
    //双冒号，作用域运算符，::全局作用域
    cout << "全局变量：" << ::atk <<endl;
}

int main(){
    test_01();
    return 0;
}