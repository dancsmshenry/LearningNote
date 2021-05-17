#include <iostream>

using namespace std;

class Person{
    public:
        Person(int age){
            this->m_Age = age;
        }

        void showAge(){
            cout << "Age: " <<  m_Age << endl;
        }

        ~Person(){
            cout << "调用析构函数" << endl;
        }

        int m_Age;
};

//智能指针，用来托管自定义类型的对象，让对象进行自动的释放
class smartPointer{
    public:
        smartPointer(Person * person){
            this->person = person;
        }

    private:
        Person *person;
};

void test01(){
    //Person p1(10);//因为这是在栈上创建的对象，所以会自动调用析构函数
    
    Person * p2 = new Person(10);//因为是开辟在堆上的对象，所以不会自动调用析构函数
    delete p2;//所以得手动析构，这时候就要用智能指针来帮忙了

    smartPointer sp(new Person(10));//注意：sp是开辟到了栈上的，所以sp会自动析构
    //既然会自动析构，就在这个析构中析构person
}

int main(){
    test01();
}