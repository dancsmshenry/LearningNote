#include <iostream>
#pragma pack(1)//加上了这条语句便不用补回之前缺的了，即是12而不是16

using namespace std;

/**
 * 类对象的成员变量和函数是分开存储的，即函数是单独存放在一个地方的
 **/

class Person{
    public:
        int m_Age;//非静态成员变量，属于对象身上
        void func(){}//非静态成员函数，不属于对象身上
        static int m_B;//静态成员变量也不属于对象身上
        static void func2(){}//静态成员函数也不属于对象身上
        double m_C;//这里有一个问题，就是double是8个字节，int是4个字节，但是要补回int缺失的，所以占用的是16个字节
};

void test01(){
    //前提是Person为空类
    cout << "size of Person = " <<sizeof(Person) << endl;
    //空类的大小为1，每个实例的对象都有独一无二的地址，char维护这个地址，所以大小就为1
    Person p[10];
    cout << "size of p = " <<sizeof(p) << endl;//同理

    //而当Person有一个变量的时候，就变为了属性的大小，却没有记录函数的大小
}

void test02(){
    //this指针指向被调用的成员函数所属的对象

    Person p1;
    p1.func();//编译器会在函数的传参中默认加上this指针，即Person *this
    //而这里也会默认传入一个自己的指针进去

    Person p2;
    p2.func();
}

int main(){
    test01();
}