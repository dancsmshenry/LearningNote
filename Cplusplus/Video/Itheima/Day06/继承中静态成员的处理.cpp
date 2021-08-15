#include <iostream>

using namespace std;

class Base{
    public:
        static void func(){
            cout << "Base::func()" << endl;
        }

        static int m_A;
};

int Base::m_A = 10;

class Son1 :public Base{
    public:
        static int m_A;

        static void func(){
            cout << "Son1::func()" << endl;
        }        
};

int Son1::m_A = 100;

//静态成员属性 子类可以继承下来
void test01(){
    cout << Son1::m_A << endl;//可以访问类继承的静态变量
    
    cout << Base::m_A << endl;
}

void test02(){
    Base::func();//可以这样调用静态的函数

    Son1::func();//子类可以继承父类的静态函数
    //但是注意，这里的子类如果也有同名的函数，那就会调用子类的函数

    Son1::Base::func();//有同名的话就用这种方式调用Base的函数
}

int main(){
    // test01();

    test02();
}

/**
 * 总结：类似非静态成员函数的处理
 * 如果想要访问父类中的成员，加作用域
 **/ 