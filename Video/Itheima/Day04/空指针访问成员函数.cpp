#include <iostream>

using namespace std;

//如果成员函数没有用到this指针，那么空指针可以直接访问
//如果成员函数用的this指针，就要注意空指针是不能访问的，要加上if语句特判
class Person{
    public:
        void show(){
            cout << "Person show()" << endl;
        }

        void showAge(){
            if (this == NULL){
                cout << "Your this point is NULL" << endl;
            }

            cout << m_Age << endl;   
        }

        int m_Age = 65345;
};

void test01(){
    Person *p = NULL;
    //在类的每个成员函数中都会有this指针在里面，但是如果当前初始化的是一个空指针
    //就会导致说当访问该成员变量的时候，出现this->m_Age的情况，但this又是一个空指针，无法访问，会报错

    p->show();
    // p->showAge();
    // int a = p->m_Age;
    // cout << a << endl;
}

int main(){
    test01();
}