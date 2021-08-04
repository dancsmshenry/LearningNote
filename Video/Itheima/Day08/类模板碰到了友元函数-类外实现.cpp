#include <iostream>

using namespace std;

//而下面的Person编译器又不知道是什么，所以也要在类外声明类
template<class T1, class T2> class Person;

//因为原来的友元函数是在类内声明的，编译器是看不到的，所以要让编译器看到，要在类外再声明
template<class T1, class T2> void PrintPerson(Person<T1, T2> &p);

template<class T1, class T2>
class Person{
    //利用空函数列表 告诉编译器 模板函数的声明
    friend void PrintPerson<>(Person<T1, T2> &p);//注意这里有一个<>

    public:
        Person(T1 name, T2 age){
            this->m_Name = name;
            this->m_Age = age;
        }

    private:
        T1 m_Name;
        T2 m_Age;
};

//类外实现
template<class T1, class T2>
void PrintPerson(Person<T1, T2> &p){
    cout << "Name ：" << p.m_Name << endl;
    cout << "Age ：" << p.m_Age << endl; 
}

void test01(){
    Person<string, int> p("Tom", 10);
    PrintPerson(p);
}

int main(){
    test01();
}