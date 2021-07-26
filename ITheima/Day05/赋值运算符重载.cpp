#include <iostream>
#include <cstring>

using namespace std;

/**
 * 一个类会默认创建 默认构造，析构，拷贝构造和重载=运算符
 * 默认的重载=运算符只是简单的值传递
 * 
 * 系统默认给类提供 赋值运算符写法 是简单的值拷贝
 * 导致如果类中有指向堆区的指针，就可能出现深浅拷贝的问题
 * 所以才会重载运算符
 * 想要链式编程的就return *this
 **/
  
class Person{
    public:
        Person(int a){
            this->m_A = a;
        }

        int m_A;
};

class Person2{
    public:
        Person2(char *name){
            this->pName = new char[strlen(name) + 1];
            strcpy(this->pName, name);
        }

        //重载 = 赋值运算符
        //一开始返回的是void的，但是会出现p1=p2=p3的情况，所以返回引用了
        Person2& operator= (const Person2 & p){
            //判断如果原来已经堆区有内容，先释放
            if (this->pName != NULL){
                delete[] this->pName;
                this->pName = NULL;
            }

            this->pName = new char[strlen(p.pName) + 1];
            strcpy(this->pName, p.pName);

            return *this;
        }

        ~Person2(){
            if (this->pName != NULL){
                delete[] this->pName;
                this->pName = NULL;
            }
        }

        char *pName;
};

void test01(){
    Person p1(10);

    Person p2(1);

    p2 = p1;

    cout << "p2.m_Age = " << p2.m_A << endl;
}

void test02(){
    //https://blog.csdn.net/VVVLeHr/article/details/86697346
    Person2 p1((char*)"henry");

    Person2 p2((char*)"hang");

    Person2 p3((char*)"dong");

    p3 = p2 = p1;

    cout << "p3.pName = " << p3.pName << endl;
}

int main(){
    // test01();   

    test02();
}