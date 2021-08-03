#include <iostream>

using namespace std;

//函数的默认参数，参数后面 = ..
//如果没有写默认参数，那么在传入变量的时候必须填写没有默认参数的那一项
//注意事项：如果有一个位置有了默认参数，那么从这个位置开始，从左往右都必须有默认参数
//传入参数，如果有参数，就用传入的参数，没有参数就用默认值
void func(int c, int a = 20, int b = 10){
    cout << "a + b = " << a + b << endl;
}

void test01(){
    func(1,2, 3);
}

//函数 占位参数
//如果有了占位参数，函数调用时候必须要提供这个参数，但是用不到这个参数
//并没有什么用，只有在后面重载++符号才有一点点用
//占位参数可以有默认值
void func2(int a, int = 1){

}

void test02(){
    func(10, 2);
}

//如果函数声明里面有了默认参数，那么在实现的时候就不能够再写默认参数了
void Func(int a = 10, int b = 20);
void Func(int a, int b){
    cout << a;
}

int main(){
    // test01();
    Func();
}