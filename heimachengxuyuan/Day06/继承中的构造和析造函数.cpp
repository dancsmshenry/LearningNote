#include <iostream>

using namespace std;

class Base{
    public:
        Base(){
            cout << "Base的构造函数调用" << endl;
        }

        ~Base(){
            cout << "Base的析造函数调用" << endl;
        }
};


/**
 * 子类会继承父类的成员属性，成员函数
 * 但是不会继承父类的构造函数和析造函数
 * 只有父类知道如何构造和析造自己的属性，而子类不知道
 **/ 
class Son1 :public Base
{
    public:
        Son1(){
            cout << "Son1的构造函数调用" << endl;
        }

        ~Son1(){
            cout << "Son1的析造函数调用" << endl;
        }
};

void test01(){
    //Base base1;

    //Son1 son1;
    // Base的构造函数调用
    // Son1的构造函数调用
    // Son1的析造函数调用
    // Base的析造函数调用

    //Son1 *son1 = new Son1();
}

class Base2{
    public:
        Base2(int a){
            this->m_A = a;
            cout << "Base的有参构造函数调用" << endl;
        }

        int m_A;
};

class Son2 :public Base2{
    public:
        //Son2() :Base2(10)
        Son2(int a) :Base2(a)
        {
            //这里如果直接写的是Son2的话就会报错，因为它的父类是没有无参构造的
            //解决办法就是用初始化列表方式 显示调用有参构造
            //写法一：Son2():Base2(10)
            //写法二：Son2(int a):Base(a)

        }
};
//补充：如果父类中没有合适默认构造，那么子类可以利用初始化列表的方式显示的调用父类的其他构造

int main(){
    test01();
}