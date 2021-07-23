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
            cout << "�����ǣ�" << this->m_Name << " �����ǣ�" << this->m_Age << endl;
        }

        NameType m_Name;
        AgeType m_Age;
};

//1��ָ����������
void doWork(Person<string, int> &p){
    p.show();
}

void test01(){
    Person<string, int> p1("Tom", 20);
    doWork(p1);
}

//2������ģ�廯
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

//�������ͻ�
//�൱���ǰ�����Person�൱����һ������ģ�����
template<class T>
void doWork3(T &p){
    p.show();
    cout << typeid(T).name() << endl;//�鿴����
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