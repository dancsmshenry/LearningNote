//
// Created by HP on 2021/07/26.
//

#ifndef MYSTRING_MYSTRING_H
#define MYSTRING_MYSTRING_H

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class MyString{
    friend ostream& operator<<(ostream& cout, MyString& str);
    friend istream& operator>>(istream& cin, MyString& str);
public:
    MyString(const char* str);
    MyString(const MyString& str);

    //重载=运算符
    MyString& operator=(const char* str);
    MyString& operator=(const MyString& str);

    //重载[]运算符
    char& operator[](int index);

    //重载+运算符
    MyString operator+(const char* str);
    MyString operator+(const MyString& str);

    //重载==运算符
    bool operator==(const MyString& str);
    bool operator==(const char* str);

    ~MyString();

private:
    char *pString;//执行堆区的指针
    int m_Size;//字符串大小
};

#endif //MYSTRING_MYSTRING_H
