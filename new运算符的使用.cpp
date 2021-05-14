#include <iostream>

using namespace std;

/**
 * 传统的分配内存的缺点：
 * 必须确定对象的长度，获得空间后必须强制转换，
 * malloc申请空间可能失败，必须添加判断来确保空间配置成功
 * 使用对象前必须对其进行初始化
 **/

class Person{
    public:
        Person(){
            cout << "默认构造函数" << endl;
        }

        ~Person(){
            cout << "默认析造函数" << endl;
        }
};

void test01(){
    //Person p1;//在栈上开辟空间

    Person *p2 = new Person;//在堆区上开辟空间
    //所有new出来的对象都会返回该类型的指针
    //malloc返回的是void*指针，还要强转
    //new是一个运算符，会调用构造函数
    //释放 堆区空间
    //delete也是运算符，配合new一起用；而malloc配合free用

    delete p2;
}

void test02(){
    void *p3 = new Person;
    //当用void* 接受new出来的指针的时候，会出现释放的问题
    delete p3;
    //无法释放的p3
}

int main(){
    //test01();
    test02();
}