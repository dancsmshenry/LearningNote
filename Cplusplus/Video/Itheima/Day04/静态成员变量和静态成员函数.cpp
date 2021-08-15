#include <iostream>

using namespace std;

/**
 * 在一个类中，将一个成员变量声明为static，即静态成员变量
 * 
 * 无论创建多少个对象，只有一个静态数据的拷贝，静态成员变量，属于某个类，所有对象共享
 * 
 * 静态变量，是在编译阶段就分配空间，对象还没有创建，就已经分配了空间
 * 
 * 特点：
 * 必须在类中声明，在类外定义
 * 不属于某个对象，在为对象分配空间时不包括静态成员所占空间
 * 可以通过类名或者对象名来引用
 **/

class Person{
    public:
        Person(){
            //m_Age = 100;
        }

        //所有这个对象会共享这个数据
        //必须在类内声明，在类外初始化
        static int m_Age;

        int m_Sex;

        //静态成员函数
        static void func(){
            cout << "static void func()" << endl;

            // m_Sex = 10;//不可以访问成员变量
            m_other = 100;//可以访问静态成员变量

            // 静态函数是单独于每一个类之外的，如果让它修改某个类对象的成员变量，
            // 它是无法区分的到底要修改的是哪个对象的成员变量的
            // 即每一个新建的类是用一个指针指向这个静态函数

        }

        //普通函数可以调用静态变量和静态函数
        void fun(){
            func();
            func1();
            cout << m_Age;
        }
    
    private:
        //私有权限，类外无法访问，但是要在类外初始化
        static int m_other;

        //静态私有函数只允许本类的成员函数内部或者友元函数来调用
        static void func1(){
            cout << "private static void func1()" << endl;
        }
};

//虽然私有不能访问，但是还是可以初始化的，编译器会认为还是类内
int Person::m_other = 10;

//类外的初始化实现 
int Person::m_Age = 222;

void test01(){
    //通过对象访问静态成员变量
    Person p1;
    p1.m_Age = 100;

    Person p2;
    p2.m_Age = 200;

    //共享数据
    cout << "p1.m_Age = " << p1.m_Age << endl;
    cout << "p2.m_Age = " << p2.m_Age << endl;

    //通过类名访问属性
    cout << "Person::m_Age = " << Person::m_Age << endl;

    //不在类里面定义静态成员变量的原因：
    //如果是像这样用类名访问属性，在类内构造函数或拷贝构造等函数方法就无法修改值

    //私有权限在类外是无法访问的
    // cout << "Person::m_other" << Person::m_other << endl;
}

void test02(){
    //静态函数的调用

    //可以用创建对象来调用
    Person p1;
    p1.func();

    //也可以通过类的调用来使用
    Person::func();
}

void test03(){
    // Person::func1();//静态私有函数无法通过类名无法访问
    
    Person p1;
    p1.fun();
    // p1.func1();//静态私有成员函数不能类外访问
}

int main(){
    // test01();

    // test02();

    // test03();

}
