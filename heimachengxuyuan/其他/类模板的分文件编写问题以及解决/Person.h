#include <iostream>

using namespace std;

template <class T1, class T2>
class Person{
    public:
        Person();

        void showPerson();

        T1 m_Name;
        T2 m_Age;
}