#include <iostream>

using namespace std;

template<class T>
class Base{
    public:
        T m_A;
};

//类的继承出现的问题，如果这里不指明具体的类型的话，例如：
//child在继承的时候会先创建对象Base并分配空间，但是这里不知道T的类型的话就会导致无法初始化
//child继承与base必须告诉base中的T的类型 否则T无法分配内存
class Child :public Base<int>{

};

//child2也是模板类
template<class T1, class T2>
class Child2 :public Base<T2>{
    public:
        T1 m_B;

        Child2(){
            cout << typeid(T1).name() << endl;
            cout << typeid(T2).name() << endl;
        }
};

void test01(){
    Child2<int, double> child;
}

int main(){
    test01();
}
//当模板碰到继承，基类如果是模板类，必须让子类告诉编译器，基类中的T到底是什么
//如果不告诉，就无法分配内存，编译不了