#include <iostream>

using namespace std;

class Person{
    public:
        Person(){
            cout << "默认构造函数调用" << endl;
        }

        Person(int a){
            cout << "有参构造函数的调用" << endl;
        }

        Person(const Person& A){//不加&就是值传递，那就是又创建了一个类，那又要创建调用一个构造函数，就进入死循环了
            m_Age = A.m_Age;
            cout << "拷贝构造函数调用" << endl;
        }

        ~Person(){
            cout << "析构函数调用" << endl;
        }

        int m_Age;
};

//拷贝构造调用的时机
//用已经创建好的对象来初始化新的对象
//比较常用
void test_01(){
    Person p1;
    p1.m_Age = 10;
    Person p2(p1);
    cout << p2.m_Age << endl;
}

//以值传递的方式给函数参数传值
void doWork(Person p1){
    //相当于Person p1 = Person(p)
    //所以这里就是析造函数了
    //这里有一个疑问，就是那这样的话，正常的传参也是新建一个变量吗？？

}

//以值传递的方法给函数参数传值
void test_02(){
    Person p;
    p.m_Age = 10;
    
    doWork(p);
}

Person doWork2(){
    Person p1;
    return p1;//也就是说在这里的返回会不会是拷贝取决于编辑器的，与语法干系不大
}
//Relase下会出现优化
/**
 * 这里有些乱，先写着先，晚点补坑
 * Person p;//不调用默认构造
 * doWork2(p);
 * void doWoek2(Person & p){
 *  Person p1;//调用默认构造
 * }
 **/

//以值方式返回局部对象
void test_03(){
    Person p = doWork2();

}

int main(){
    test_01();
    //test_02();
    //test_03();//这里会不会出现拷贝取决于编辑器的优化结果
}