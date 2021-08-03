#include <iostream>

using namespace std;

void test01(){
    // int &ref = 10;//引用了不合法的内存，不可以
    const int &ref = 10;
    //加入const之后，编译器为此生成一个临时变量：int tmp = 10;const int &ref = tmp;

    // ref = 1000;//这里会报错，因为const是不能被修改的

    int *p = (int *) &ref;
    //注意：这里的&的作用，用在左边表示为引用类型，用在右边表示为取地址
    *p = 1000;
    
    cout << "ref = " << ref << endl;
}

//常量引用使用场景 用来修饰形参
void showValue(const int &val){
    // val += 10000;//如果只是想要显示内容，而不修改内容，那么就用const修饰这个形参
    //即形参加const以后就不能够在函数内部被修改了

    //这里多说一句，其实是可以通过二级指针再对该变量进行修改的
    // int *p = (int *)&val;
    // *p = 11000;
    
    cout << "value = " << val << endl;
}

void test02(){
    int a = 10;
    showValue(a);
}

int main(){
    // test01();
    test02();
}
//引用不产生新的变量，减少形参与实参传递时的开销
//由于引用可能导致实参随形参改变而改变，将其定义为常量引用可以消除这种副作用