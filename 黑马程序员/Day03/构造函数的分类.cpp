#include <iostream>

using namespace std;


/**分类：
 * 按照参数进行分类，无参构造函数（默认构造函数），有参构造函数
 * 按照类型分类，普通构造函数 拷贝构造函数
 * 构造和析构函数必须写在public下
 */

class Person{
    public:
        //这里的构造函数有多态，所以只会执行其中的一个
        Person(){
            cout << "这是无参构造函数" << endl; 
        }

        Person(int a){
            cout << "这是有参构造函数 " << a << endl;
        }

        //拷贝构造函数，顾名思义，是要将已有的对象拷贝到这个新的对象中，所以为了不改变原有的对象，用的是const
        Person(const Person& p){
            m_Age = p.m_Age;
            cout << "这是拷贝构造函数" << endl; 
        }

        ~Person(){
            cout << "这里是析造函数" << endl;
        }

        int m_Age;
};

void test01(){
    
    Person p1(1);//有参
    p1.m_Age = 10;
    Person p2(p1);//拷贝
    cout << p2.m_Age << endl;

    //Person p3();//如果这样写，编译器会默认为是一个函数的命名，而不是一个类的初始化
    Person p3;//这才是一个类的初始化

    //显示法调用
    Person p4 = Person(10);
    Person p5 = Person(p4);
    
    Person p6 = Person();//这种方法可以构造类

    Person(100);//匿名对象，匿名对象特定，如果编辑器发现了对象是匿名的，那么会在这行代码结束后就释放这个对象
    //所以这里也会有析构和构造
    //不能用拷贝构造函数，初始化匿名对象
    //Person(p5);//会被认为写的是Person(p5)的声明

    Person p7 = 100;//相当于调用了Person p7 = Person(100)，隐式类型转换
    Person p8 = p7;//相当于 Person p8 = person(p7);
}

int main(){
    test01();
}