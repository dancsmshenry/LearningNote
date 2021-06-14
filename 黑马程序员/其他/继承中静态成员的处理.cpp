#include <iostream>

using namespace std;

class Base{
    public:
        static void func(){
            cout << "调用func函数（Base）" << endl;
        }

        static int m_A;
};

int Base::m_A = 10;

class Son1 :public Base{
    public:
        static int m_A;

        static void func(){
            cout << "调用Son1的func函数" << endl;
        }        
};

int Son1::m_A = 100;

void test01(){
    cout << Son1::m_A << endl;//可以访问类继承的静态变量
    //但是如果Son1中也有m_A的话，就会出问题（没加public的情况下）
}

void test02(){
    // Base base1;
    // Base::func();//这样必须调用静态的函数

    //Son1::func();//这里也可以继承父类的静态函数
    //但是注意，这里的子类如果也有同名的函数，那就会调用子类的函数
    Son1::Base::func();//有同名的话就用这种方式调用Base的函数
}

int main(){
    //test01();
    test02();
}