#include <iostream>

using namespace std;

template<class T1, class T2>
class Person{
    public:
        Person(T1 name, T2 age);
        // {
        //     this->m_Name = name;
        //     this->m_Age = age;
        // }

        T1 m_Name;
        T2 m_Age;

        void showPerson();
        // {
        //     cout << "姓名是：" << this->m_Name << "年龄是"  << this->m_Age << endl;
        // }
};

//类外实现成员函数
template<class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age){
    this->m_Name = name;
    this->m_Age = age;
}

template<class T1, class T2>
void Person<T1, T2>::showPerson(){
    cout << "姓名是：" << this->m_Name << "  年龄是："  << this->m_Age << endl;
}

void test01(){
    Person<string, int> p1("henry", 20);//类模板必须显示类型
    p1.showPerson();
}

int main(){
    test01();
}
/**
 * 写法：template<class T1, class T2>
 * 然后先写 
 * 函数的返回类型（void int） 
 * 类的名称和T1T2的制定类型（Person<T1, T2>）
 * 接着是作用域符号，然后是函数名(参数列表)
 **/ 