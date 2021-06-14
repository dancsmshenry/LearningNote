#include <iostream>

using namespace std;

/**
 * 如果成员函数没有用到this，那么空指针可以直接访问
 * 否则，就要注意代码中是否引用了空指针
 **/ 

class Person{
    public:
        void show(){
            cout << "调用show（）函数" << endl;
        }

        void showAge(){
            if (this == NULL) cout << "这是一个空指针" << endl;
            cout << "年龄是" << this->m_Age << endl;
        }

        int m_Age = 65345;
};

void test01(){
    Person *p1 = NULL;
    p1->show();//空指针可以调用show()函数，因为它没有调用this指针
    p1->showAge();//这里报错是因为输出m_Age的时候需要this指针有确定指向的对象（而此时指向的是null）
    //不懂就问，为什么这里怎样都不会报错的啊？？？？
    int a = p1->m_Age;
    cout << a << endl;
}

int main(){
    test01();
}