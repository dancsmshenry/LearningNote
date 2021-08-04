#include <iostream>

using namespace std;

//1、普通函数和函数模板的区别
template<class T>
T myPlus1(T a, T b){
    return a + b;
}

int myPlus2(int a, int b){
    return a + b;
}

void test01(){
    int a = 10, b = 20;

    char c = 'c';

    cout << myPlus1(a, b) << endl;

    // cout << myPlus1(a, c) << endl;//类型推导不出来,函数模板不能进行隐式的类型转换

    cout << myPlus2(a, c) << endl;
    //这里的普通函数可以自动推导变量的类型
    //即可以进行隐式类型转换
}

//2、普通函数和函数模板的调用规则
template<class T>
void myPrint(T a, T b){
    cout << "template<class T> void myPrint" <<endl;
}

void myPrint(string a, string b){
    cout << "void myPrint(string)" << endl;
}

void myPrint(int a, int b){
    cout << "void myPrint(int)" << endl;
}

template<class T>
void myPrint(T a, T b, T c){
    cout << "template<class T> void myPrint(TTT)" <<endl;
}

void test02(){
    int a = 10, b = 100;

    //如果出现重载，优先使用普通函数调用，如果没有实现(即函数只有声明没实现的话)就会报错
    myPrint(a, b);//这里调用的不是模板函数，是常规函数

    //如果想要强制使用模板，可以使用空参数列表
    myPrint<>(a, b);

    //函数模板也可以被函数模板重载
    int c = 1000;
    myPrint(a, b, c);

    //如果有更好的匹配目标，就会调用函数模板,比如下面调用的就是函数模板
    myPrint("a", "a");
}

int main(){
    test01();

    // test02();
}

//编译过程：预处理，编译，汇编，链接
/**
 * 编译器并不是把函数模板处理成能够处理任何类型的函数
 * 函数模板通过具体类型产生不同的函数 
 * 编译器会对函数进行二次编译，在声明的地方对模板代码进行编译，在任何调用的地方对参数替换后的代码再进行编译
 * 
 * 解释：第一次是语法上的编译，就看看函数是否有错误，第二次是类型上的编译，即把T改为应对的类型来检查（即已经调用了具体类型了）
 * ps:通过模板产生的函数就是模板函数
 * 编译器并不是把函数模板处理成能够处理任何类型的函数（有点晕？？）
 * 
 * 总结：
 * 模板不是万能的，不能通用所有的数据类型
 * 模板不能直接调用，生成后的模板函数才可以调用
 * 二次编译，第一次对模板进行编译，第二次对替换T类型后的代码进行编译 
 **/ 