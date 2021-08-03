//
// Created by HP on 2021/07/26.
//

#include "MyString.h"

MyString::MyString(const char *str) {
    this->pString = new char[strlen(str) + 1];
    strcpy(this->pString, str);
    this->m_Size = strlen(str);
    cout << "MyString::MyString(const char *str)" << endl;
}

MyString::MyString(const MyString &str) {
    this->pString = new char[strlen(str.pString) + 1];
    strcpy(this->pString, str.pString);
    this->m_Size = str.m_Size;
    cout << "MyString::MyString(const MyString &str)" << endl;
}

MyString::~MyString() {
    if (this->pString != NULL){
        delete[] this->pString;
        this->pString = NULL;
    }
    cout << "MyString::~MyString()" << endl;
}

//左移运算符重载
ostream& operator<<(ostream& cout, MyString& str){
    cout << str.pString << endl;
    return cout;
}

//右移运算符重载
istream& operator>>(istream& cin, MyString& str){
    //先判断 原始是否有内容 如果有，就清空
    if (str.pString != NULL){
        delete[] str.pString;
        str.pString = NULL;
    }

    //让用户输入内容
    char buf[1024];
    cin >> buf;

    //把用户输入的字符串 赋值给 str
    str.pString = new char[strlen(buf) + 1];
    strcpy(str.pString, buf);
    str.m_Size = strlen(buf);

    return cin;
}

//=运算符重载
MyString& MyString::operator=(const char *str) {
    if (this->pString != NULL){
        delete[] this->pString;
        this->pString = NULL;
    }

    this->pString = new char[strlen(str) + 1];
    strcpy(this->pString, str);

    return *this;
}

//=运算符重载
MyString& MyString::operator=(const MyString &str) {
    if (this->pString != NULL){
        delete[] this->pString;
        this->pString = NULL;
    }

    this->pString = new char[strlen(str.pString) + 1];
    strcpy(this->pString, str.pString);

    return *this;
}

//[]运算符重载
char& MyString::operator[](int index) {
    return this->pString[index];
}

//+运算符重载
MyString MyString::operator+(const char *str) {
    //先计算返回的字符串开辟的大小
    int newSize = this->m_Size + strlen(str) + 1;

    char *tmp = new char[newSize];

    memset(tmp, 0, newSize);

    //拼接字符串
    strcat(tmp, this->pString);
    strcat(tmp, str);

    MyString newStr(tmp);
    delete[] tmp;
    return newStr;
}

MyString MyString::operator+(const MyString &str) {
    //先计算返回的字符串开辟的大小
    int newSize = this->m_Size + strlen(str.pString) + 1;

    char *tmp = new char[newSize];

    memset(tmp, 0, newSize);

    //拼接字符串
    strcat(tmp, this->pString);
    strcat(tmp, str.pString);

    MyString newStr(tmp);
    delete[] tmp;
    return newStr;
}

//重载==运算符
bool MyString::operator==(const MyString &str) {
    if (strcmp(this->pString, str.pString) == 0 && this->m_Size == str.m_Size){
        return true;
    }

    return false;
}

bool MyString::operator==(const char *str) {
    if (strcmp(this->pString, str) == 0 && this->m_Size == strlen(str)){
        return true;
    }

    return false;
}