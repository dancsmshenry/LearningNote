#include <iostream>

using namespace std;

/**
 * 不要随意乱用符号重载
 * 内置数据类型的运算符不可以重载
 * <<需要写到全局函数当中
 * 如果重载的时候需要访问p1的私有成员，需要把该操作符作为对象的友元函数
 **/ 

class Person{
    friend ostream& operator<<(ostream& cout, Person& p);//用友元来访问对象的私人属性
    public:
        Person(){}

        Person(int a, int b):m_A(a), m_B(b){}

    private:
        int m_A;
        int m_B;
};

ostream& operator<<(ostream &cout, Person& p){
    cout << "Person's m_A is " << p.m_A << endl;
    cout << "Person's m_B is " << p.m_B;

    return cout;
    /**
     * 解释：用ostream做返回值的原因：因为你后面还是会继续输入数值的，不能只输入一个就不输出了吧
     * 所以要用cout的ostream做返回值
     * 重载的左移运算符也最后不要写到类对象里面，因为如果此时要调用该运算符的话
     * 是这样的：Person p1(10, 10); p1 << ...; 
     * 和往常不太一样
     **/ 
}

void test01(){
    Person p1(10, 10);

    cout << p1 << endl;
}

int main(){
    test01();
}