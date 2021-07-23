#include <iostream>

using namespace std;

class MyInterger{
    public:
        MyInterger(){
        }

        int m_Num = 0;

        //前置++重载
        void operator++(){
            this->m_Num++;
        }

        //后置++重载
        void operator++(int a){

        }
};

void test01(){
     MyInterger myInt;
     ++ myInt;
     ++ myInt;
     cout << myInt.m_Num << endl;
}

int main(){
    test01();
}