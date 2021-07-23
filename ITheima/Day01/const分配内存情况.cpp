#include <iostream>
#include <string>

using namespace std;

//const分配内存，取地址会分配临时内存
//extern编译器也会给const变量分配内存
void test01(){
    const int m_A = 10;
    int *p = (int *) & m_A;//会临时分配内存
}

//用普通变量初始化const变量
void test02(){
    int a = 10;
    const int b = a;//为b分配内存

    int *p = (int *) &b;
    *p = 1010;
    
    cout << b << endl;
}

//自定义数据类型，用const也会分配内存
struct Person{
    string m_Name;
    int m_Age;
};

void test03(){
    const Person p1;

    Person *p = (Person *) &p1;
    p->m_Name = "henry";
    (*p).m_Age = 19;

    cout << p1.m_Name << endl;
    cout << p1.m_Age << endl;
}

int main(){
    // test02();
    test03();
}