#include <iostream>

using namespace std;

template<class NameType, class AgeType = int>
class Person{
    public:
        Person(NameType name, AgeType age){
            this->m_Name = name;
            this->m_Age = age;
        }

        void show(){
            cout << "Name: " << this->m_Name << endl;
            cout << "Age: " << this->m_Age << endl;
        }

        NameType m_Name;
        AgeType m_Age;
};

//1、指定传入类型
void doWork(Person<string, int> &p){
    p.show();
}

void test01(){
    Person<string, int> p1("Tom", 20);
    doWork(p1);
}


//2、参数模板化
template<class T1, class T2>
void doWork2(Person<T1, T2> &p){
    p.show();

    //如何查看类型
    cout << typeid(T1).name() << endl;
    cout << typeid(T2).name() << endl;
}

void test02(){
    Person<string, int> p2("Jerry", 30);
    doWork2(p2);
}


//整个类型化
template<class T>
void doWork3(T &p){
    // p.show();

    cout << typeid(T).name() << endl;
}

void test03(){
    Person<string, int> p3("Henry", 19);
    doWork3(p3);
}

int main(){
    // test01();

    // test02();
    
    test03();
}

/**
 * 类模板做函数的参数类型的三种方法
 * 1、显示指定类型（指定类型）
 * 2、参数模板化（对对象的参数模板化）
 * 3、整体模板化（将传入的对象作为模板）
 **/ 