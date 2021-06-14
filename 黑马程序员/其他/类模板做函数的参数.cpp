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
            cout << "姓名是：" << this->m_Name << " 年龄是：" << this->m_Age << endl;
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
    cout << typeid(T1).name() << endl;
    cout << typeid(T2).name() << endl;
}

void test02(){
    Person<string, int> p2("Jerry", 30);
    doWork2(p2);
}

//整体类型化
//相当于是把整个Person类当作了一个对象模板放入
template<class T>
void doWork3(T &p){
    p.show();
    cout << typeid(T).name() << endl;//查看类型
}

void test03(){
    Person<string, int> p3("Henry", 19);
    doWork3(p3);
}

int main(){
    // test01();
    test02();
    // test03();
}