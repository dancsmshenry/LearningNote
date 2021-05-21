#include <iostream>

using namespace std;

class Base{
    public:
        Base(){
            m_A = 100;
        }

        void func(){
            cout << "调用Base中的func()函数"  << endl;
        }

        void func(int a){
            cout << "调用Base中的func(int a)函数" << endl;
        }

    public:
        int m_A;
};

class Son1 :public Base{
    public:
        Son1(){
            m_A = 200;
        }

        // void func()
        //     cout << "调用Son1中的func()函数"  << endl;
        // 
    
    public:
        int m_A;
};

void test01(){
    Son1 son1;
    //cout << son1.m_A << endl;//就近原则，访问的是Son1的m_A
    //cout << son1.Base::m_A << endl;//通过作用域访问Base的m_A

    // son1.func();//如果子类没有func的话，这条语句就直接调用父类的
    // son1.Base::func();//同理

    // son1.Base::func(10);//这里好像一定要加空间才行吧

    son1.func(10);
}
//结论：子类不会覆盖父类的同名属性和方法，所以要找到父类的属性和方法只要换命名空间即可
//但如果子类和父类的成员函数名称相同，子类会把父类的所有同名函数的所有版本都隐藏起来
//这时如果想要调用父类的函数，就必须添加作用域

/**
 * 成员属性 直接调用 先调用子类 如果想要调用父类 需要作用域
 * 成员函数 直接调用 先调用子类，父类的所有版本都会被隐藏，除非显示用作用域运算符操作
 **/ 

int main(){
    test01();
}