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

        void func(){
            cout << "调用Son1中的func()函数"  << endl;
        }
    
    public:
        int m_A;
};

void test01(){
    Son1 son1;
    //cout << son1.m_A << endl;//就近原则，访问的是Son1的m_A
    //cout << son1.Base::m_A << endl;//通过作用域访问Base的m_A

    //son1.func();
    //son1.Base::func();//同理

    son1.Base::func(10);//这里好像一定要加空间才行吧
}
//结论：子类不会覆盖父类的同名属性和方法，所以要找到父类的属性和方法只要换命名空间即可

int main(){
    test01();
}