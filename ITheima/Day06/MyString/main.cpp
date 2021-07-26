#include <iostream>
#include "MyString.h"

void test01(){
    MyString s1 = "abc";

    cout << "Show you the old s1: " << s1 << endl;

    cout << "please write new mystring:" << endl;

    cin >> s1;

    cout << "Show you the new s1: " << s1 << endl;
}

void test02(){
    MyString s1 = "aaaa";
    cout << "s1 = " << s1 << endl;

    cout << "s1[0] = " << s1[0] << endl;
}

void test03(){
    MyString s1 = "abcd";

    s1 = s1 + "efg";

//    cout << "s1 + efg = " << (s1 + s1) << endl;
//    个人认为这里报错是因为重载+过后生产的是一个临时对象，用完就销毁，所以会报错
}

void test04(){
    MyString s1 = "abc";
    MyString s2 = "abc";

    if (s1 == s2){
        cout << "s1 == s2" << endl;
    }else{
        cout << "s1 != s2" << endl;
    }
}

/**
 * cout 输入 自定义字符串
 * cin 让用户输入字符串内容
 * 重载 = 运算符
 * 重载 + [] ==运算符
 * @return
 */

int main() {
//    std::cout << "Hello, World!" << std::endl;

//    test01();

//    test02();

//    test03();

    test04();

    return 0;
}
