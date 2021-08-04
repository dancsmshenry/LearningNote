#include <iostream>

using namespace std;

void swapDouble(double &a, double &b){
    double temp = a;
    a = b;
    b = temp;
}

void swapInt(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

//类型，逻辑都非常的相似
//类型参数化，泛型编程 模板技术
template <class T>//告诉编译器 下面如果出现T不要报错 T是一个通用的类型
//换一种写法 template <typename T>
void mySwap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

void test01(){
    int a = 10;
    int b = 1;

    mySwap(a, b);//这里不要重载swap，c++标准库自带swap
    //自动类型推导，必须有参数类型才可以推导

    mySwap<int>(a, b);//或者显示指定类型

    //模板必须要指定出T才可以使用
    // mySwap();//所以这里报错了

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
}

void test02() {
    double a = 3.14;
    double b = 1.14;

    mySwap(a, b);

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
}

template<typename T>
void mySwap2(){
}

void test03(){
    int a = 3;
    char b = 'a';
    // mySwap(a, b);//这里模板就无法推导出正确的那个类型了，会报错

    //模板必须要推导出类才能使用
    // mySwap2();//会报错，因为没有推导出类型
    mySwap2<int>();//有类型传入就ok
}

int main(){
    // test01();
    test02();
}