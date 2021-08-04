#include <iostream>
#include <string>

using namespace std;

class MyOutOfRangeException : public exception {//这是系统提供的异常类，可以直接继承
    public:
        MyOutOfRangeException(string errorfile){
            this->m_ErrorInfo = errorfile;
        };

        virtual ~MyOutOfRangeException(){};

        //这里必须加上后面的一串
        virtual const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW{
            //返回错误信息,这里要string转char
            return this->m_ErrorInfo.c_str();
        };

        string m_ErrorInfo;
};

class Person{
    public:
        Person(string name, int age){
            this->m_Name = name;

            if (age < 0 || age > 200){
                throw MyOutOfRangeException(string("年龄越界了"));
            }            
        }

        string m_Name;
        int m_Age;
};

void test01(){
    try{
        Person("张三", 300);
    }
    catch(MyOutOfRangeException &e){
        cout << "Error:" << e.what() << endl;
    }
    
}

int main(){
    test01();
}
/**
 * 自己构建异常类，需要继承exception
 * 需要重写虚析构和what()
 * 内部维护错误信息，字符串
 * 最好在构造的时候传入错误信息和字符串，what返回错误原因
 **/ 