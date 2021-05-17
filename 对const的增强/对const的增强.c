#include <stdio.h>

//const int a = 100;
//这里出现的问题是无法通过指针修改全局的const变量


void test_01()
{
    const int a = 100;
    int *p = (int *)&a;
    *p = 200;
    printf("*p的值是：%d\n", *p);
    printf("a的值是：%d\n", a);
    printf("p的地址是：%d\n", p);
    printf("a的地址是：%d\n", &a);
}


int main()
{
    test_01();
    //这段代码在clion就可以运行，在vscode中就会报错，然而发现是vscode无法正确分清c/c++的编辑器
    //导致本来是c的代码变为是c++的标准来运行（所以clion能够正确执行c的标准，而vscode不能正确执行）
    //return 0;
}