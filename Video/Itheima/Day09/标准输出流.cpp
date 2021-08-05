#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

/**
 * cout.put()//向缓冲区写字符
 * cout.write()//从buffer中写num个字节到当前输出流中
 **/ 

void test01(){
    // cout.put('a').put('b');

    char buf[1024] = "helloworld!";
    cout.write(buf, strlen(buf));
}

void test02(){
    //通过流成员函数

    int number = 99;

    cout.width(20);//从右往左数20个空
    cout.fill('*');//往这20个空里面填满*
    cout.setf(ios::left);//设置格式 输入内容做对齐
    cout.unsetf(ios::dec);//卸载十进制
    cout.setf(ios::hex);//设置进制为16进制
    cout.setf(ios::showbase);//显示是多少进制的，比如加上0x（强制输出整数基数）
    cout.unsetf(ios::hex);//卸载16进制
    cout.setf(ios::oct);//设置为8进制

    cout << number << endl;
}

void test03(){
    int a = 90;

    cout << setw(20)
        << setfill('*')
        << setiosflags(ios::showbase)//基数
        << setiosflags(ios::left)//左对齐
        << hex//十六进制
        << a
        << endl;
}

int main(){
    // test01();

    // test02();

    test03();
}