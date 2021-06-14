#include <iostream>
#include <string>
#include <stdexcept>//异常的头文件

using namespace std;

void test01(){
    string str;//默认构造（以对象构造（类）的思想来理解string的构造）
    //创建一个空的字符串
    
    string str1(str);//拷贝构造
    //使用一个string对象初始化另一个stirng对象

    string str2 = str;//也是拷贝构造
    string str3 = "abc";
    //使用已知字符串初始化对象
    
    string str4(10, 'n');
    //使用n个字符串c初始化对象

    cout << str3 << endl;
    cout << str4 << endl;

    //基本赋值
    str = "Hello";
    str1 = str3;

    //string& assign(const char *s, int n);，把字符串“”的前n个字符赋给当前的字符串
    str2.assign("abcdef", 6);
    cout << str2 << endl;

    //string& assign(const string &s, int start, int n);，将s从start开始n个字符赋值给字符串
    string str6;
    str6.assign(str2, 0, 3);//注意是从start开始的n位
    cout << str6 << endl;

}

/**
 * string存放字符操作
 * char& operator[](int n){};//通过[]来获取字符
 * char& at(int n)//通过at方法获取字符
 **/ 
void test02(){
    string s = "Hello world!";
    
    for (int i = 0; i < s.size(); i ++){
        // cout << s[i] << endl;
        //cout << s.at(i) << endl;//道理相同
        /**
         * []访问到越界的地方会直接挂掉
         * at访问到越界的地方会抛出异常
         **/ 
    }

    try{
        //cout << s[1000] << endl;
        cout << s.at(1000) << endl;
    }catch(out_of_range &e){
        cout << e.what() << endl;//使用标准库和异常库来抛出异常
    }
    catch(...){
        cout << "抛出越界异常"  << endl;
    }
}

int main(){
    // test01();
    test02();
}
//因为本章都是关于strign的api的使用，所以就暂不了解了