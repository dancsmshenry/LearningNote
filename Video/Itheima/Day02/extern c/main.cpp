#include<iostream>
using namespace std;
#include "test.h"

//cpp中想要调用c语言的方法
//extern "C" void show();//show方法 按照c语言方式做连接
//解决的问题就是 在cpp中调用c语言的函数

/**
 * 这里之前出现问题主要是在cmakelist中没有加上test.c文件，才导致bug的
 */

int main(){

    //在cpp中函数是可以发生重载的，编译器会把这个函数名称偷偷改变 _showc void

    show();
}