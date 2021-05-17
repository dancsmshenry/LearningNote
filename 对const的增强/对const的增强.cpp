#include <iostream>

using namespace std;
//const int a = 100;
//这里出现的问题是无法通过指针修改全局的const变量


void test_01()
{
    const int a = 100;
    int *p = (int *)&a;
    *p = 200;
    cout << "*p的值是：" << *p << endl;
    cout << "a的值是：" << a << endl;
    cout << "p的地址是：" << p << endl;
    cout << "a的地址是：" << &a << endl;
}
/**
 * 对此现象的解释：
 * 在c++中，const是不会给后面的变量提供内存的，而是存入一个符号表当中，即key和value当中
 * 在key中存入a变量，在value中存放100值，即调用的时候都是键-值对调用的
 * 而对下列代码的解释：int *p = (int *)&a; *p = 200;
 * 实际上是int tmp = a; int *p = (int *) &tmp;（相当于创建的指针指向的是临时生成的那一块区域，就导致没能根本的修改变量）
 * 但是令人惊讶的是在以c结尾的文件中也是用这种标准来运行代码，看来是我的.vscode部分出现了问题
**/

int main()
{
    test_01();
    //这段代码在clion就可以运行，在vscode中就会报错，然而发现是vscode无法正确分清c/c++的编辑器
    //导致本来是c的代码变为是c++的标准来运行（所以clion能够正确执行c的标准，而vscode不能正确执行）
    //return 0;
}