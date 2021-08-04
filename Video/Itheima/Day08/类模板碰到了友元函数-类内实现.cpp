#include <iostream>
#include <string>

using namespace std;

template<class T1, class T2>
class Person{
    //友元函数类内实现(友元函数可以访问得到类的私有属性)
    friend void PrintPerson(Person<T1, T2> &p){
        cout << "Name : " << p.m_Name << endl;
        cout << "Age : " << p.m_Age << endl;
    }

    public:
        Person(T1 name, T2 age){
            this->m_Name = name;
            this->m_Age = age;
        }

    private:
        T1 m_Name;
        T2 m_Age;
};

void test01(){
    Person<string, int> p("Tom", 14);
    PrintPerson(p);
}

int main(){
    test01();
}