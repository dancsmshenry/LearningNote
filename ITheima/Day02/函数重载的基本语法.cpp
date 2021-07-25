#include <iostream>

using namespace std;

//函数的重载
//函数名称可以重复
//必须在同一个作用域，函数名称相同
//函数的参数 个数不同 或者类型不同 或者顺序不同
//返回值不同不可以作为函数重载的条件
//因为如果可以，那就会面临很多奇怪的情况，如有int和double的重载，现在用int来接受，那int的也可以，double强转后也可以
//就会很麻烦
//总结：同一个作用域下，参数个数不同，参数类型不同，参数顺序不同

void func(){
    cout << "this is void func()" << endl; 
}

void func(int a){
    cout << "this is void func(int a)" << endl;
}

void func(double a){
    cout << "this is void func(double a)" << endl;
}

void func(double a, int b){
    cout << "this is void func(double a, int b)" << endl;
}

void func(int b, double a){
    cout << "this is void func(int b, double a)" << endl;
}

void test01(){
    // func(1);
    func(1.1, 3);
    func(1, 3.1);
}

//注意，要避免函数的二义性
void func2(int a, int b = 10){

}

void func2(int a){

}

void test02(){
    // func2(10);//这里调用的是哪一个呢？
}

//引用的重载版本
void func3(int &a){//引用必须要引合法的内存空间
    cout << "this is void func3(int &a)" << endl;
}

void func3(const int &a){//const也可以作为重载的条件
    //int tmp = 10; const int &a = tmp;
    cout << "this is void func3(const int &a)" << endl;
}

void test03(){
    int a = 10;
    func3(190);
    func3(a);
}

/**
 * 函数重载的实现原理：
 * 就 编译器 对 相同名字的函数重载 在其内部中 实际的名字是不一样的
 * 比如void func() 在内部是_Z4funcv
 * 而void func(int a) 在内部是_Z4funci
 **/ 

int main(){
    // test01();
    
    // test02();

    test03();
}