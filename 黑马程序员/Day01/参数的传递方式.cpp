#include <iostream>

using namespace std;

//通过引用来交换数值
void Swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

//通过指针来交换数值
void Swap01(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}//注意：这里传进来的应该是变量的地址

void test01(){
    int a = 100;
    int b = 10;
    Swap(a, b);
    //传过去的是一个值对象，但是swap是以一个引用的方式接收的
    //而引用又相当于一个指针，就可以直接操控具体的对象来改变数值了

    //如果是以值接收的话，那最后也不会改变原来对象的值的

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
}

/**
 * 引用的注意事项
 * 引用必须引一块合法的内存空间
 * 不要返回局部变量的引用
 **/ 

// int& doWork(){
//     int a = 10;
//     return a;
// }

void test02(){
    // int &a = 1;//引用必须引一块合法的内存空间

    // int &ret = doWork();//a是一个局部变量，跳出函数后就消失了，所以不能返回局部变量的引用
    //不报错是编译器做了优化,报错的话则是编译器没有优化
}

int& doWork2(){
    static int a = 10;
    return a;
}

void test03(){
    int &ret  = doWork2();
    cout << "ret = " << ret << endl;
    //如果函数的返回值是引用，那么函数的调用就可以作为左值来调用
    doWork2() = 100;
    cout << doWork2() << endl;
}

/**
 * 引用的本质是在c++内部实现一个指针常量
 * c++编译器在编译过程中使用常指针作为引用的内部实现，因此引用所占用的空间大小与指针相同
 **/ 

void test04(){
    int a = 10;
    int &aref = a;//内部转换为int* const aref = &a;说明了为什么引用必须初始化
    aref = 30;//转化为*aref = 30;
}

int main(){
    // test01();
    test03();
}