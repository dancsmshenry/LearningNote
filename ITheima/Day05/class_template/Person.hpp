//
// Created by HP on 2021/07/26.
//

#ifndef CLASS_TEMPLATE_PERSON_HPP
#define CLASS_TEMPLATE_PERSON_HPP

#include <iostream>
#include <string>

using namespace std;

template<class T1, class T2>
class Person{
public:
        Person(T1 name, T2 age);

        void showPerson();

        T1 m_Name;
        T2 m_Age;
};

template<class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age) {
    this->m_Name = name;
    this->m_Age = age;
}

template<class T1, class T2>
void Person<T1, T2>::showPerson() {
    cout << "Your name is " << this->m_Name << endl;
    cout << "Your age is " << this->m_Age << endl;
}

#endif //CLASS_TEMPLATE_PERSON_HPP
