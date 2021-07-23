#include <iostream>

using namespace std;

class Person{
    public:
        Person():m_A(10),m_B(20),m_C(30){}

        /**
        //带参数值初始化
        Person(int a, int b, int c){
            m_A = a; 
            m_B = b; 
            m_C = c;
        }
        **/

        //利用初始化列表，初始化属性
        //构造函数后面+：属性（值参数），属性（值参数）
        Person(int a, int b, int c):m_A(a),m_B(b),m_C(c){

        }

        int m_A;
        int m_B;
        int m_C;
};

void test01(){
    //Person p1(10, 20, 30);
    Person p1;
    cout << p1.m_A << endl;
    cout << p1.m_B << endl;
    cout << p1.m_C << endl;
}

int main(){
    test01();
}