#include <iostream>

using namespace std;

template<class T>
T myPlus1(T a, T b){
    return a + b;
}

int myPlus2(int a, int b){
    return a + b;
}

void test01(){
    int a = 10, b = 20;

    char c = 'a';

    cout << myPlus1(a, b) << endl;//类型推导不出来

    cout << myPlus2(a, c) << endl;
    //这里的普通函数可以自动推导变量的类型
    //即可以进行隐式类型转换
}

template<class T>
void myPrint(T a, T b){
    cout << "模板调用的myPrint" <<endl;
}

void myPrint(string a, string b){
    cout << "常规函数string调用myPrint" << endl;
}

void myPrint(int a, int b){
    cout << "常规函数调用的myPrint" << endl;
}

void test02(){
    int a = 10, b = 100;
    //myPrint(a, b);//这里调用的不是模板的函数，是常规函数调用的
    //规则：如果出现重载，优先使用普通函数调用，如果没有实现就会报错

    //如果想要强制使用模板，可以使用空参数列表
    //myPrint<>(a, b);

    //函数模板也可以被函数模板重载

    //如果有更好的匹配目标，就会调用函数模板,比如下面调用的就是函数模板
    myPrint("a", "a");
}

int main(){
    //test01();
    test02();
}

//编译过程：预处理，编译，汇编，链接
/**
 * 函数模板通过具体类型产生不同的函数 
 * 编译器会对函数进行二次编译，在声明的地方对模板代码进行编译，在任何调用的地方对参数替换后的代码再进行编译
 * 解释：第一次是语法上的编译，就看看函数是否有错误，第二次是类型上的编译，即把T改为应对的类型来检查（即已经调用了具体类型了）
 * ps:通过模板产生的函数就是模板函数
 * 编译器并不是把函数模板处理成能够处理任何类型的函数（有点晕？？）
 * 
 * 总结：
 * 模板不是万能的，不能通用所有的数据类型
 * 模板不能直接调用，生成后的模板函数才可以调用
 * 二次编译，第一次对模板进行编译，第二次对替换T类型后的代码进行编译
 **/ 