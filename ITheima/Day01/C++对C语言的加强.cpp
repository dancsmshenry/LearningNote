#include <iostream>

using namespace std;

//1、全局变量检测的增强，这里是无法运行的（在c语言中是可以通过的）
/*
int a;
int a = 10;//这里是重新定义了 
*/

//2、函数检测增强，参数类型增强，返回检测增强（返回值），函数调用参数检测增强
//参数一定要写明类型（但是c里面可以不写）
//在不是void的情况下，返回值一定是要有的（但是c里面可以不写）
//传参数目一定要和函数里面一样（但是c里面可以传多个参数，而只用前面规定的几个）
/*
int getRectS(w, h){

}//这个在c中是可以运行的，但是在c++中不可以
*/

//3、类型转换检测的增强
void test_01(){
    //char *p = malloc(sizeof(8));//正常的返回的是void指针，但是这在c中是可以运行的，c++中是不可以的
    //malloc返回的是void*
    //即在c中是不需要强转的，但是c++一定要强转
}

//4、struct的增强
struct Person{
    int sex;
    int name;
    int age;
    void PlusAge();//c语言中struct不能加函数
};
void test_02(){
    struct Person a;//c语言中一定要加struct才能成立
    Person b;//c++中不需要
}

//5、bool的增强
void test_03(){
    bool flag;//这个在c中是没有的，只有真假之分，只有0才是0，其他的数字都是1
    //_bool才是c中有的
    flag = -100;
    cout << sizeof(bool) << endl;
    cout << flag << endl;
}

//6、三目运算符的增强
//在c++中a > b ? a : b返回的是a或b的变量本身
//但是在c中返回的直接是某个具体的值
//说白了就是可以作为左值
void test_04(){
    int a = 10, b = 20;
    a > b ? a : b = 30;//这里b的值就变为30
    cout << "b = " << b << endl;
}

int main(){
    // test_03();
    test_04();
}