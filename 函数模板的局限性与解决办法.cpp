#include <iostream>

using namespace std;

class Person{
    public:
        int m_Age;
        string m_Name;

        Person(string name, int age){
            this->m_Name = name;
            this->m_Age = age;
        }
};

template<class T>
bool myCompare(T &a, T &b){
    if (a == b){
        return true;
    }

    return false;
}

//ͨ�����廯�Զ����������ͣ������������
//�Ϳ��Բ���������
//������廯�ܹ�����ƥ�䣬��ô��ѡ����廯
//�﷨��template<> ����ֵ���� ������<��������>(����)
//�����������ͺͺ������������޸�
template<> bool myCompare<Person>(Person& a, Person& b){
    if (a.m_Age == b.m_Age && a.m_Name == b.m_Name){
        return true;
    }

    return false;
}

void test01(){
    int a = 10;
    int b = 20;
    int ret1 = myCompare(a, b);

    cout << "ret1 = " << ret1 << endl;

    Person p1("Tom", 10);
    Person p2("Jerry", 20);
    int ret2 = myCompare(p1, p2);

    cout << "ret2 = " << ret2 << endl;
}

int main(){
    test01();
}