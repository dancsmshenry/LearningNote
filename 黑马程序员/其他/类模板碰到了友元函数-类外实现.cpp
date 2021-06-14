#include <iostream>

using namespace std;

//但是如果是只让编译器看到的话，那也要让编译器看到Person的声明（否则下面的语句就会报错）
template<class T1, class T2> class Person;
//如果直接是在类里面进行声明的话，会造成编译器无法看到这个声明（在类内却是看不到啊）
//所以要在类外声明让编译器看到
template<class T1, class T2> void PrintPerson(Person<T1, T2> &p);

template<class T1, class T2>
class Person{
    //友元函数类内实现(友元函数可以访问得到类的私有属性)
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
    cout << "姓名：" << p.m_Name << " 年龄：" << p.m_Age << endl; 
}

void test01(){
    Person<string, int> p("Tom", 10);
    PrintPerson(p);
}

int main(){
    test01();
}
/**
 * 友元函数类内实现
 * friend void printPerson(Person<T1, T2> &p)
 **/ 