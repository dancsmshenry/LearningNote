#include <iostream>

using namespace std;

class MyClass{
    public:
        // MyClass(){
        //     cout << "Ĭ�Ϲ��캯��" << endl;
        // }

        MyClass(int a){
            cout << "�вι��캯��" << endl;
        }
        //ϵͳĬ���ṩ��һ����3��������Ĭ�Ϲ���(�޲Σ�������Ϊ��)���������죬���캯��(�޲Σ�������Ϊ��)

        //���ṩ���вεĹ��캯����ϵͳ�Ͳ����ṩĬ�ϵĹ��캯���ˣ���һ��д�ˣ��͵�ȫ��д���𣬷���ͻᱨ��
        //1�����ṩ���вΣ��Ͳ����ṩĬ�ϣ����ǻ��ṩĬ�ϵĿ�����

        //2�����ṩ�˿������죬ϵͳ�Ͳ����ṩ�����Ĺ�����

        int m_A;
};

class Person{
    public:
        Person(const Person& a){}

        int m_A;
};

void test01(){
    MyClass c1(1);
    c1.m_A = 100;
    MyClass c2(c1);
    cout << c2.m_A << endl;
}

void test02(){
    //Person p1;//����ͻᱨ��
}

int main(){
    //test01();
    test02();
    return 0;
}