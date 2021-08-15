#include <iostream>
#pragma pack(1)//加上了这条语句便不用补回之前缺的了，即是12而不是16

using namespace std;

/**
 * 类对象的成员变量和函数是分开存储的，即函数是单独存放在一个地方的
 * 成员属性和成员方法是分开存储的
 **/

class Person{
    public:
        int m_Age;//非静态成员变量，属于对象身上
        void func(){}//非静态成员函数，不属于对象身上
        static int m_B;//静态成员变量也不属于对象身上
        static void func2(){}//静态成员函数也不属于对象身上
        double m_C;//这里有一个问题，就是double是8个字节，int是4个字节，但是要补回int缺失的，所以占用的是16个字节
};

/**
 * 结论：
 * 只有非静态成员变量才是对象身上的
 * 成员变量和成员属性是分开存储的
 * 空类的大小为1
 **/

void test01(){
    //当Person为空类
    //空类的大小为1，每个实例的对象都有独一无二的地址，char维护这个地址，所以大小就为1
    cout << "size of Person = " <<sizeof(Person) << endl;
    
    Person p[10];
    cout << "size of p = " <<sizeof(p) << endl;//同理

    //而当Person有一个变量的时候，就变为了属性的大小，却没有记录函数的大小
}

void test02(){
    /**
     * this指针指向被调用的成员函数所属的对象
     * this指针是隐含在每个类的非静态成员函数中
     * 当一个对象被创建以后，它的每一个成员函数都含有一个系统自动生成的隐含指针this，用以保存这个对象的地址
     * 
     * 静态成员函数内部没有this指针
     **/

    Person p1;
    p1.func();//编译器会在函数的传参中默认加上this指针，即Person *this
    

    Person p2;
    p2.func();
}

int main(){
    test01();

    // test02();
}