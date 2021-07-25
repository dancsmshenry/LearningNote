#include <iostream>

using namespace std;

class MyClass{
    public:
        // MyClass(){
        //     cout << "默认构造函数" << endl;
        // }

        MyClass(int a){
            cout << "有参构造函数" << endl;
        }
        //系统默认提供给一个类3个函数，默认构造(无参，函数体为空)，拷贝构造，析造函数(无参，函数体为空)

        //当提供了有参的构造函数，系统就不会提供默认的构造函数了，即一旦写了，就得全部写完吗，否则就会报错
        //1、即提供了有参，就不会提供默认（还是会提供默认的拷贝）

        //2、当提供了拷贝构造，系统就不会提供其他的构造了

        int m_A;
};

class Person{
    public:
        Person(const Person& a){}

        int m_A;
};

void test01(){
    MyClass c1(1);
    c1.m_A = 100;
    MyClass c2(c1);
    cout << c2.m_A << endl;
}

void test02(){
    //Person p1;//这里就会报错
}

int main(){
    //test01();
    test02();
    return 0;
}