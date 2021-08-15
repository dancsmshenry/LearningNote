#include <iostream>

using namespace std;

//内置数据类型的运算符是不能被改变的
//运算符重载可以提供多个版本
//函数名 operator+(){}
//在成员函数或者全员函数里重写一个+运算符的函数

class Person{
    public:
        Person(){}

        Person(int a, int b):m_A(a),m_B(b) {

        }
        
        
        //+号运算符重载 成员函数
        Person operator+(Person &p){
            Person tmp;
            tmp.m_A = this->m_A + p.m_A;
            tmp.m_B = this->m_B + p.m_B;
            return tmp;
        }
        

        int m_A;
        int m_B;
};

//利用全局函数 进行+号运算符的重载
// Person operator+(Person &p1, Person &p2){
//     Person tmp;
//     tmp.m_A = p1.m_A + p2.m_A;
//     tmp.m_B = p1.m_B + p2.m_B;
//     return tmp;
// }

void test01(){
    Person p1(10, 10);
    Person p2(20, 20);

    Person p3 = p1 + p2;//从p1.operator+(p2) 到 operator+(p1, p2);

    cout << "p3's m_A is " <<p3.m_A  << " and " << "m_B is " << p3.m_B << endl;
}

int main(){
    test01();
}