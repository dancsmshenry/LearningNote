#include <iostream>
#include <string>

using namespace std;

//д����ģ�����������࣬
//�뺯��ģ������𣬿�����Ĭ�����Ͳ���
//����ģ������Զ��Ƶ�������ģ����Ҫָ������
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
    // ��ģ�岻֧���Զ������Ƶ�
    // Person p1("Tome", 20);

    //��Ҫ��ʾָ������
    Person<string, int> p("Tom", 20);
    p.show();
}

class Person1{
    public:
        void showPerson1(){
            cout << "Person1�ĵ���" << endl;
        }
};

class Person2{
    public:
        void showPerson2(){
            cout << "Person2�ĵ���" << endl;
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
//��Ա���� һ��ʼ���ᴴ�������ģ�����������ʱ��ȥ����!!!

void test02(){
    MyClass<Person1> m;

    m.func1();
}

int main(){
    //test01();

    test02();
}