#include <iostream>

using namespace std;

//�����������͵�������ǲ��ܱ��ı��
//��������ؿ����ṩ����汾
//������ operator+(){}
//�ڳ�Ա��������ȫԱ��������дһ��+������ĺ���

class Person{
    public:
        Person(){}

        Person(int a, int b):m_A(a),m_B(b) {

        }
        
        
        //+����������� ��Ա����
        Person operator+(Person &p){
            Person tmp;
            tmp.m_A = this->m_A + p.m_A;
            tmp.m_B = this->m_B + p.m_B;
            return tmp;
        }
        

        int m_A;
        int m_B;
};

//����ȫ�ֺ��� ����+�������������
// Person operator+(Person &p1, Person &p2){
//     Person tmp;
//     tmp.m_A = p1.m_A + p2.m_A;
//     tmp.m_B = p1.m_B + p2.m_B;
//     return tmp;
// }

void test01(){
    Person p1(10, 10);
    Person p2(20, 20);

    Person p3 = p1 + p2;//��p1.operator+(p2) �� operator+(p1, p2);

    cout << "p3's m_A is " <<p3.m_A  << " and " << "m_B is " << p3.m_B << endl;
}

int main(){
    test01();
}