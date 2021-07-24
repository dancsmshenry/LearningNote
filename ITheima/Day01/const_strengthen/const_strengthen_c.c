#include <stdio.h>

//const int a = 100;
//全局变量有保护，不可以随便修改


void test_01()
{
    const int a = 100;
    //a是一个伪常量，编译器是会为其分配内存的
    int *p = (int *)&a;
    *p = 200;
    printf("*p的值是：%d\n", *p);
    printf("a的值是：%d\n", a);
    printf("p的地址是：%d\n", p);
    printf("a的地址是：%d\n", &a);

    int a1[a];//视频说a不可以作为数组的大小，但是这里是可以的
}


int main()
{
    test_01();
    //这里证明在c语言里面是可以通过指针的方式来修改变量的
}