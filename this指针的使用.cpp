#include <iostream>

using namespace std;

/**
 * thisָ�룺
 * ָ��ָ��ǰ����
 * ���������ͻ
 * *this���ص�ǰ��ı���
 * �Ǿ�̬��Ա��������thisָ��
 **/ 

class Person{
    public:
        int m_Age;

        //this���Խ��������ͻ
        Person(int m_Age){
            //�����������age����age = m_Age�ǿ���ִ�е�
            //���������m_Age�Ļ����Ͳ����ж�m_Age�ĸ����ĸ��ˣ�����Ҫthisָ������æ
            this->m_Age = m_Age;
        }

        void getAge(){
            cout << m_Age << endl;
        }

        //�Ա�����
        void compareAge(Person &p){
            if (this->m_Age == p.m_Age){
                cout << "�����������" << endl;
            } else{
                cout << "�������䲻��" << endl;
            }
        }

        //��������
        //����ע�⣺���û��&���Ǿ���ֵ���أ�����ͻ���ÿ������죬��*this���ص��൱����һ���µĶ���
        //���������ֵ���أ��ͻ�����ڵ�һ�ε������ǶԱ�����в����������ŷ��ص���һ���µĶ���һ������
        //�������ʽ��̵Ļ���һֱ�����ľ���һ����һ�����¶��󣬾Ͳ�����ԭ���Ķ����ϲ�������
        Person& PlusAge(int age){
            this->m_Age += age;
            return *this;//*this���ص��Ǳ���
        }
};

void test01(){
    Person p1(10);
    //p1.getAge();

    Person p2(11);
    p2.compareAge(p1);
}

void test02(){
    Person p3(10);
    p3.PlusAge(10).PlusAge(10);//��Ϊ�����PlusAge���ص���һ�������壬���ԾͿ���һֱ���ϵ������������
    //��ʽ���
    p3.getAge();
    Person p4(p3.PlusAge(10));//����ͱ���PlusAge���ص���һ������ʵ�壬���Կ�������
    p4.getAge();
}

int main(){
    //test01();
    test02(); 
}