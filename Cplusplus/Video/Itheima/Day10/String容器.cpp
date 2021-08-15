#include <iostream>
#include <string>//字符串的头文件
#include <stdexcept>//异常的头文件

using namespace std;

/**
 * char*是一个指针，而string是一个类，封装了char*，管理这个字符串
 **/ 

//字符串的构造
void test01(){
    //默认构造（以对象构造（类）的思想来理解string的构造）
    string str;
    
    //使用一个string对象初始化另一个stirng对象，拷贝构造
    string str1(str);

    //使用已知字符串初始化对象，因为是拷贝构造
    string str2 = str;
    string str3 = "abc";
    
    //使用n个字符串c初始化对象
    string str4(10, 'n');
    
    cout << str3 << endl;
    cout << str4 << endl;

    //基本赋值
    str = "Hello";
    str1 = str3;

    //string& assign(const char *s, int n);，把字符串s的前n个字符赋给当前的字符串
    str2.assign("abcdef", 3);
    cout << str2 << endl;

    //string& assign(const string &s, int start, int n);，将s从start开始n个字符赋值给字符串
    string str6;
    str6.assign("abcdefg", 1, 3);//bcd
    cout << str6 << endl;

    //string& assign(int n, char c);，将n个字符c赋给当前字符串
    string str7;
    str7.assign(10, 'a');
    cout << str7 << endl;

    //string& assign(const string &s);，把字符串s赋给当前字符串
    //string& assign(const char *s);，把字符s赋给当前字符串
    string str8;
    str8.assign(str7);
    cout << str8 << endl;
}


/**
 * string访问字符操作
 * char& operator[](int n){};//通过[]来获取字符
 * char& at(int n)//通过at方法获取字符
 **/ 
void test02(){
    string s = "Hello world!";
    
    for (int i = 0; i < s.size(); i ++){
        // cout << s[i] << endl;
        // cout << s.at(i) << endl;
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
        cout << "throw exception" << endl;
    }catch(...){
        cout << "catch other exception" << endl;
    }
}

//string的拼接、查找和替换
void test03(){
    //拼接
    string s1 = "I";
    string s2 = " love you!";

    //string+string
    s1 += s2;

    //string+char
    s1 += '!';

    //string+char
    const char *a = "!!!";
    //注意：这里的"!!!"是指const char，是一个常量，现在如果让一个char指针指向const char，编译器就会报错优化
    //所以，就要改为const
    s1 += a;

    s1.append("!!!!");

    cout << s1 << endl;


    //查找
    
    //如果找不到的话就返回-1
    //int find(const string& s, int pos = 0) const;//查找str第一次出现的位置，从pos开始查找
    //int find(const char* s, int pos = 0) const;//查找s第一次出现的位置，从pos开始查找
    //int find(char c, int pos = 0) const;//查找c第一次出现的位置，从pos开始查找
    //int find(const char* s, int pos = 0, int n) const;//从pos位置查找s的前n个字符第一次位置

    //rfind是从后往前找的
    //int rfind(const stirng& str, int pos = npos) const;//查找str最后一次出现的位置，从pos开始查找
    //int rfind(const char* s, int pos = npos) const;//查找s最后一次出现的位置，从pos开始查找
    //int rfind(const stirng& str, int pos, int n) const;//从pos查找s的前n个字符最后一次位置
    //int rfind(const char c, int pos = 0) const;//查找字符c最后一次出现的位置


    string s11 = "abcdef";
    int pos = s11.find("dc");
    cout << pos << endl;

    //替换
    //string& replace(int pos, int n, const string& str);//替换从pos开始n个字符为字符串str
    //string& replace(int pos, int n, const char* str);//替换从pos开始的n个字符为字符str

    string s111 = "hello";
    s111.replace(1, 3, "1111111");
    //理解本质：是把s111的三个字符换位我想要换成的字符
    cout << s111 << endl;
}

//string的比较操作
void test04(){
    //int compare(const string& s) const;//与字符串s进行比较
    //int compare(const char* s) const;//与字符串s进行比较
    /**
     * compare函数在>时返回1，<时返回-1，==时返回0
     * 比较区分大小写，比较时参考字典顺序，排越前面的越小
     * 大写的A小于小写的a
     * 比大小与长度没有关系，就是单纯的比较字母的字典序
     **/ 

    string s1 = "hell";
    string s2 = "hello";

    if (s1.compare(s2) == 0){
        cout << "s1 == s2" << endl;
    }else if (s1.compare(s2) == -1){
        cout << "s1 < s2" << endl;
    }else{
        cout << "s1 > s2" << endl;
    }
}

//string子串
//string substr(int pos = 0, int n = npos) const;//返回由pos开始的n个字符组成的字符串
void test05(){
    string s1 = "hello world!!";
    string s2;
    s2 = s1.substr(0, 5);
    cout << s2 << endl;

    //需求，查找一个右键的用户名
    string email = "zhangtao@sina.com";

    int pos = email.find("@");
    cout << "pos = " << pos << endl;

    cout << "username:" << email.substr(0, pos) << endl;
}

//string的插入和删除
/**
 * string& insert(int pos, const char* s&)//插入字符串
 * string& insert(int pos, const string& str)//插入字符串
 * string& insert(int pos, int n, char c)//在指定位置插入n个字符c
 * 
 * string& erase(int pos, int n = npos)//删除从pos开始的n个字符
 **/ 
void test06(){
    string s1 = "hello";
    s1.insert(1, "111");
    cout << "s1 = " << s1 << endl;

    //删除111
    s1.erase(1, 3);
    cout << "s1 = " << s1 << endl;
}

void func(string s){
    cout << s << endl;
}

void func2(char *s){
    cout << s << endl;
}

void test07(){
    string s = "abc";

    //string 转 char
    const char *p = s.c_str();

    func(p);//隐式转换，const char隐式转换为string

    //char 转 stirng
    string s2(p);

    // func2(s2);//这里不能够由string隐式转换为char
}

void test08(){
    //记住一条，当字符串被重新赋值重新分配内存的时候，地址就会发生改变
    //那么改变之前原来的地址就不会改变现在s的值了
    //可问题是我这里的地址没有发生改变啊？？？？(改变了，可能是原来的大小够，就没有重新分配空间)
    string s = "abcdef";
    char& a = s[1];
    char& b = s[2];
    a = '2';
    b = '1';
    cout << s << endl;//a21def
    cout << (int*)s.c_str() << endl;

    s = "sdflkjaslkdsfslkfdsdf";
    a = '2';
    b = '1';
    cout << s << endl;
    cout << (int*)s.c_str() << endl;
}

//写一个函数，函数内部将string字符串中的所有小写字母都变为大写字母
void test09(string &s){
    for (int i = 0; i < s.size(); i ++){
        //全变为大写
        s[i] = toupper(s[i]);

        //全变为小写
        // s[i] = tolower(s[i]);
    }

    cout << s << endl;
}

int main(){
    // test01();

    // test02();

    // test03();

    // test04();

    // test05();

    // test06();

    // test07();

    // test08();

    string s1 = "lskdfjslkfjslkdf";
    test09(s1);
}