#include <iostream>

using namespace std;

/**
 * Person类有showAge成员函数
 * 如果是new出来的对象是需要收到析构的
 * 所以用智能指针来托管Person对象
 * 为了让智能指针和原来的指针一模一样使用，所以就要重载它
 **/ 

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
        
        //重载->，让智能指针对象像Person *p一样去使用
        Person* operator->(){
            return this->person;//这里返回的是一个指针
        }

        //重载*，使得和*指针（得到对象本体一样）一样去使用
        Person& operator*(){
            return *this->person;
        }

        //这里是先smartPointer，再析构person
        ~smartPointer(){
            cout << "智能指针析构了person指针" << endl;
            if (this->person != NULL){
                delete this->person;
                this->person = NULL;
            }
        }

    private:
        Person *person;
};

void test01(){
    //Person p1(10);//因为这是在栈上创建的对象，所以会自动调用析构函数
    
    // Person * p2 = new Person(10);//因为是开辟在堆上的对象，所以不会自动调用析构函数
    // delete p2;//所以得手动析构，这时候就要用智能指针来帮忙了

    smartPointer sp(new Person(10));//注意：sp是开辟到了栈上的，所以sp会自动析构
    //既然会自动析构，就在这个析构中析构person

    sp->showAge();//如果没有->的重载，这里会报错
    //注意：这里->返回的是一个指针，这里编辑器是做了优化的（即本来应该是sp->->showAge()）

    (*sp).showAge();//这里不重载的话和上面同理报错
}

int main(){
    test01();
}