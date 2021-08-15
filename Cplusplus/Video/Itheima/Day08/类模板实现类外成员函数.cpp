#include <iostream>

using namespace std;

template<class T1, class T2>
class Person{
    public:
        Person(T1 name, T2 age);
        // {
        //     this->m_Name = name;
        //     this->m_Age = age;
        // }

        T1 m_Name;
        T2 m_Age;

        void showPerson();
        // {
        //     cout << "Name : " << this->m_Name <<endl;
        //     cout << "Age : "  << this->m_Age << endl;
        // }
};

//类外实现成员函数
template<class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age){
    this->m_Name = name;
    this->m_Age = age;
}

template<class T1, class T2>
void Person<T1, T2>::showPerson(){
    cout << "Name : " << this->m_Name <<endl;
    cout << "Age : "  << this->m_Age << endl;
}

void test01(){
    Person<string, int> p1("henry", 20);
    p1.showPerson();
}

int main(){
    test01();
}