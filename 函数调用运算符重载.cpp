#include <iostream>

using namespace std;

/**
 * 不要重载&&和||
 * 无法实现内置操作符的完整语义
 * 因为其内置版本的特殊之处在于它是首先计算左边，如果左边的结果能够决定表达式，那右边的值就不用算了
 **/ 

class MyPrint{
    public:
        void operator()(string txt){
            cout << txt << endl;
        }

};

class MyAdd{
    public:
        int operator()(int v1, int v2){
            return v1 + v2;
        }
};

void test01(){
    MyPrint print;
    //仿函数调用一
    print("hello world!");//仿函数
}

void test02(){
    //仿函数调用二
    cout << MyAdd()(1, 2) << endl;//匿名对象
}

int main(){
    //test01();
    test02();
}