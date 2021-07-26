#include <iostream>

using namespace std;

/**
 * this指针：
 * 指针指向当前对象
 * 解决命名冲突
 * *this返回当前类的本体
 * 非静态成员函数才有this指针
 **/ 

class Person{
    public:
        int m_Age;

        //this可以解决命名冲突
        Person(int m_Age){
            //如果传来的是age，那age = m_Age是可以执行的
            //但是如果是m_Age的话，就不能判断m_Age哪个是哪个了，就需要this指针来帮忙
            this->m_Age = m_Age;
        }

        void getAge(){
            cout << m_Age << endl;
        }

        //对比年龄
        void compareAge(Person &p){
            if (this->m_Age == p.m_Age){
                cout << "两人年龄相等" << endl;
            } else{
                cout << "两人年龄不等" << endl;
            }
        }

        //年龄增长
        //这里注意：如果没有&，那就是值返回，这里就会调用拷贝构造，而*this返回的相当于是一个新的对象
        //所以如果是值返回，就会造成在第一次调用中是对本体进行操作，但接着返回的是一个新的对象，一次类推
        //下面的链式编程的话，一直操作的就是一个又一个的新对象，就不是在原来的对象上操作的了
        //如果是以值的方式返回，就会调用拷贝构造
        Person& PlusAge(int age){
            this->m_Age += age;
            return *this;//*this返回的是本体
        }
};

void test01(){
    Person p1(10);
    //p1.getAge();

    Person p2(11);
    p2.compareAge(p1);
}

void test02(){
    Person p3(10);
    p3.PlusAge(10).PlusAge(10);//因为这里的PlusAge返回的是一个对象本体，所以就可以一直不断的引用这个对象
    //链式编程
    p3.getAge();
    Person p4(p3.PlusAge(10));//这里就表明PlusAge返回的是一个对象实体，可以拷贝构造
    p4.getAge();
}

int main(){
    //test01();
    test02(); 
}