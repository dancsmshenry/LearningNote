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

        Person(int a){
            cout << "有参构造函数" << endl;
        }

        ~Person(){
            cout << "默认析造函数" << endl;
        }

        int m_A;
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
    //delete p3;
    //无法释放的p3
}

void test03(){
    //通过new创建数组，一定会调用默认构造调用函数（所以提供有参构造的时候也要提供默认构造）
    Person *pArray = new Person[10];//堆区开辟空间
    //Person pArray2[2] = {Person(1), Person(2)};//在栈上开辟数组，可以指定有参构造

    //delete pArray;//这样是无法释放数组的
    delete [] pArray;//这样是正确的
    //解释：当使用delete的时候，必须让delete知道内存空间中是否存在一个记录数组大小的数
    //所以当时delete[]的时候，delete就知道是一个对象数组，就知道要delete几次
    //对象数组：最前面有一个数是用来储存数组个数的
    //如果不加[]，那delete就会直接释放最前面的那个对象，而不管后面的对象
}

int main(){
    //test01();
    //test02();
    test03();
}