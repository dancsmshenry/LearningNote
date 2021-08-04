#include <iostream>
#include <string>

using namespace std;

//写法：模板后面紧跟着类，
//与函数模板的区别，可以有默认类型参数
//函数模板可以自动推导(即不用特地指明类型，模板自动推导出类型)，而类模板需要指定类型
template<class NameType, class AgeType = int>
class Person{
    public:
        Person(NameType name, AgeType age){
            this->m_Name = name;
            this->m_Age = age;
        }

        void show(){
            cout << this->m_Name << " " << this->m_Age << endl;
        }

        NameType m_Name;
        AgeType m_Age;
};

void test01(){
    // 类模板不支持自动类型推导
    // Person p1("Tome", 20);

    //需要显示指定类型
    Person<string, int> p("Tom", 20);
    //Person<string> p("Tom", 20);也是一样的，因为有默认类型参数
    p.show();
}

class Person1{
    public:
        void showPerson1(){
            cout << "Person1::showPerson1()" << endl;
        }
};

class Person2{
    public:
        void showPerson2(){
            cout << "Person2::showPerson2()" << endl;
        }
};

template<class T>
class MyClass{
    public:
        T obj;
        void func1(){
            obj.showPerson1();
        }

        void func2(){
            obj.showPerson2();
        }
};
//成员函数 一开始不会创建出来的，而是在运行时才去创建!!!

void test02(){
    MyClass<Person1> m;

    m.func1();
}

int main(){
    //test01();

    test02();
}