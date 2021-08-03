#include <iostream>

using namespace std;

/**
 * 常函数void func() cosnt {}
 * 常函数修饰的是this指针
 * 常对象在对象前加const
 * 常对象不可调用普通的成员函数
**/

class Person{
    public:
    Person(){
        //构造中修改属性
        //this 永远执行本体
        //Person *const this
        
        this->m_A = 0;
        this->m_B = 0;
    }

    void showInfo() const //常函数 不允许修改指针指向的值（这里一定要换行）
    {
        //this->m_A = 1;//这里会报错

        this->m_C = 0;
        //const Person *const this;
        cout << "m_A" << this->m_A << endl;
        cout << "m_B" << this->m_B << endl;
    }

    int m_A;
    int m_B;

    mutable int m_C;//就算是常函数，还是要执意在其中修改值
};

void test01(){
    Person p1;
    p1.m_A = 10;

    //常对象，不允许修改属性
    const Person p2;
    //p2.m_A = 10;//函数这里就会报错

    /**
     * 注意：常对象的初衷就是不能修改成员变量，而也存在通过函数修改成员变量的情况
     * 所以常对象无法调用普通成员函数
     * 但常对象可以调用常函数
    **/
}

int main(){
    test01();
}