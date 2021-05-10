#include <iostream>

using namespace std;

//全局变量检测的增强，这里是无法运行的
/*
int a;
int a = 10;
*/

//函数检测增强，参数类型增强，返回检测增强，这里是无法运行的
//即参数一定要写明类型（但是c里面可以不写）
//即返回一定是要有的（在不是void的情况下），但是c里面可以不写
//传参数目一定要和函数里面一样（但是c里面可以传多个参数，而只用前面规定的几个）


//三目运算符的增强
//在c++中a > b ? a : b返回的是a或b的变量本身
//但是在c中返回的直接是某个具体的值
void test_01(){
    int a = 10, b = 20;
    a > b ? a : b = 30;//这里b的值就变为30
}

//struct的增强
struct Person{
    int sex;
    int name;
};
void test_02(){
    struct Person a;//c语言中一定要加struct才能成立
    Person b;//c++中不需要
}

//bool的增强
void test_03(){
    bool flag;//这个在c中是没有的
    //_bool才是c中有的
}

//类型转换检测的增强
void test_04(){
    //char *p = malloc(sizeof(8));//正常的返回的是void指针，但是这在c中是可以运行的，c++中是不可以的
    //即在c中是不需要强转的，但是c++一定要强转
}
int main(){
    return 0;
}