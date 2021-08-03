#include <iostream>

using namespace std;

//引用的基本语法，type &别名 = 原名
void test01(){
    int a = 10;
    int &b = a;
    //&用在左边表示引用类型，用在右边表示取地址符

    b = 20;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
}

//引用必须初始化
void test02(){
    // int &a;//必须初始化
    int a = 10;
    int &b = a;//初始化了以后就不可以修改了，即b绑定了为a的话就不能绑定另一个了
    int c = 20;

    b = c;//赋值
}

//对数组建立引用
void test03(){
    int arr[10];
    for (int i = 0; i < 10; i ++ ){
        arr[i] = i; 
    }

    //给数组起别名
    int (&pArr)[10] = arr;
    for (int i:pArr){
        cout << i << " ";
    }

    //第二种方式
    typedef int(arrayref) [10];//一个具有10个元素的int类型的数组
    arrayref & arr2 = arr;
    
}

int main(){
    // test01();
    test03();
}