#include <iostream>

using namespace std;

/**
 * 在一个类中，将一个成员变量声明为static，即静态成员变量
 * 无论创建多少个变量，只有一个静态数据的拷贝
 * 是在编译阶段就分配空间，对象还没有创建，就已经分配了空间
 * 必须在类中声明，在类外定义
 * 不属于某个对象，在为对象分配空间时不包括静态成员所占空间
 * 可以通过类名或者对象名来引用
 **/

class Person{
    public:
        Person(){
            //m_Age = 100;
        }

        static int m_Age;//会共享数据
        //在类内声明，在类外初始化

        int m_Sex;

        //不可以访问成员变量
        static void func(){
            cout << "静态函数的调用" << endl;
            //m_Sex = 100;//会发生报错
            //静态函数是单独于每一个类之外的，如果让它修改某个类对象的成员变量，是无法区分的
            //（因为有很多的对象都指向了它）
            //即每一个新建的类是用一个指针指向这个静态函数
            m_other = 100;//但是可以访问静态成员变量，道理同上
        }

        //普通函数可以调用静态变量和静态函数
        void fun(){
            func();
            cout << m_Age;
        }
    
    private:
        static int m_other;//私有权限，类外无法访问，但是在类外是可以初始化的

        static void func1(){
            cout << "私有静态函数的调用" << endl;
        }
};

int Person::m_other = 10;//虽然私有不能访问，但是还是可以初始化的，编译器会认为还是类内

int Person::m_Age = 222;//类外的初始化

void test01(){
    //通过对象访问静态成员变量
    Person p1;
    p1.m_Age = 100;
    Person p2;
    p2.m_Age = 200;
    cout << "通过对象访问属性" << p1.m_Age << "和" << p2.m_Age <<endl;//共享数据

    //通过类名访问属性
    cout << "通过类名访问属性" <<Person::m_Age << endl;
    //不在类里面定义静态成员变量的原因：如果是用类名访问属性，那么这种方法就无法修改值了
}

void test02(){
    //cout << Person::m_other << endl;
    //这里显示是不可访问的
}

void test03(){
    //静态函数的调用
    Person p1;//也可以用创建对象来调用
    p1.func();
    Person::func();//可以通过类的调用来使用
}

void test04(){
    //Person::func1();//私有函数无法访问
    
    Person p1;
    p1.fun();
}

int main(){
    //test01();
    //test02();
    //test03();
    test04();
}
