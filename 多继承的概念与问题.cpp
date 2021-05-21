#include <iostream>

using namespace std;

class Base1{
    public:
        Base1(){
            cout << "调用Base1的构造" << endl;
            m_A = 100;
        }

        int m_A;
};

class Base2{
    public:
        Base2(){
            cout << "调用Base2的构造" << endl;
        }

        int m_A;
        int m_B;
};

class Son :public Base1, public Base2{//多继承的写法
    public:
        Son(){
            cout << "调用Son的构造" << endl;
        }

        int m_C;
        int m_D;  
};

void test01(){
    //cout << sizeof(Son) << endl;//16 = 4 * 4
     Son son1;
     //cout << son1.m_A << endl;//这时候就会出现二义性，即编译器比知道你访问的是哪一个
     cout << son1.Base1::m_A << endl;
}

int main(){
    test01();
}