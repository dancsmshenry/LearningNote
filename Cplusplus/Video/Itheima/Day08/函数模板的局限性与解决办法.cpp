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

/**
 * 通过具体化自定义数据类型，解决上述问题
 * 就可以不用重载==
 * 如果具体化能够优先匹配，那么就选择具体化
 * 语法：template<> 返回值类型 函数名<具体类型>(参数)
 * 参数名和类型和函数名都不能修改
**/
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