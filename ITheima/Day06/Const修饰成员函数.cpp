#include <iostream>

using namespace std;

//������void func() cosnt {}
//���������ε���thisָ��
//�������ڶ���ǰ��const
//�����󲻿ɵ�����ͨ�ĳ�Ա����

class Person{
    public:
    //�������޸�����
    //this ��Զִ�б���
    //Person *const this
    Person(){
        this->m_A = 0;
        this->m_B = 0;
    }

    void showInfo() const //������ �������޸�ָ��ָ���ֵ,��֣�����һ��Ҫ����..
    {
        //this->m_A = 1;//����ᱨ��

        this->m_C = 0;//OK
        //const Person *const this;
        cout << "m_A" << this->m_A << endl;
        cout << "m_B" << this->m_B << endl;
    }

    int m_A;
    int m_B;
    mutable int m_C;//�����ǳ�����������Ҫִ���������޸�ֵ
};

void test01(){
    Person p1;
    p1.m_A = 10;

    //�����󣬲������޸�����
    const Person p2;
    //p2.m_A = 10;//��������ͻᱨ��
    //ע�⣺������ĳ��Ծ��ǲ����޸ĳ�Ա��������Ҳ����ͨ�������޸ĳ�Ա���������
    //���Գ������޷�������ͨ��Ա����
    //����������Ե��ó�����
}

int main(){
    test01();
}