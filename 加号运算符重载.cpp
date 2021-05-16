#include <iostream>

using namespace std;

class Person{
    public:
        Person(){}

        Person(int a, int b):m_A(a),m_B(b) {

        }
        
        /*
        //+号运算符重载 成员函数
        Person operator+(Person &p){
            Person tmp;
            tmp.m_A = this->m_A + p.m_A;
            tmp.m_B = this->m_B + p.m_B;
            return tmp;
        }
        */

        int m_A;
        int m_B;
};

//利用全局函数 进行+号运算符的重载
Person operator+(Person &p1, Person &p2){
    Person tmp;
    tmp.m_A = p1.m_A + p2.m_A;
    tmp.m_B = p1.m_B + p2.m_B;
    return tmp;
}

void test01(){
    Person p1(10, 10);
    Person p2(20, 20);

    Person p3 = p1 + p2;//从p1.operator+(p2) 到 operator+(p1, p2);

    cout << "p3的m_A是：" <<p3.m_A << "m_B:" << p3.m_B << endl;
}

int main(){
    test01();
}