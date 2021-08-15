#include <iostream>
#include <cstring>

using namespace std;

class Animal{
    public:
        virtual void speak(){
            cout << "Animal::speak()" << endl;
        }

        //普通析构 是不会调用子类的析构的，所以可能会导致空间释放不干净
        //利用虚析构来解决这个问题
        //如果这里不是虚函数的话，就会导致下面delete那里不能释放完全
        //备注：下面使用父类的指针创建的子类，这里不是虚函数会导致最后析构调用的是父类的函数，不是它本身Cat的
        // virtual ~Animal(){
        //     cout << "Animal的析构调用" << endl;
        // }

        //纯虚析构
        //特性：需要声明，还需要实现 类内声明，类外实现
        virtual ~Animal() = 0; //这里相当于一个声明
        //特性：如果函数中出现了 纯虚析构函数 那么这个类会变为抽象类
        // 抽象类 不可实例化对象
};

Animal::~Animal(){
    //纯虚析构函数的实现
    cout << "Animal::~Animal()" << endl;
}

class Cat:public Animal{
    public:
        Cat(const char * name){
            this->m_Name = new char[strlen(name) + 1];
            strcpy(this->m_Name, name);
        }

        virtual void speak(){//这里的virutal可以不写，但是为了表明是继承父类的虚函数，最好还是写上
            cout << "Cat::speak()" << endl;
        }

        ~Cat(){
            cout << "Cat::~Cat()" << endl;
            if (this->m_Name != NULL){
                delete[] this->m_Name;
                this->m_Name = NULL;
            }
        }

        char *m_Name;
};

void test01(){
    Animal * animal = new Cat("Tom");//纯虚函数的不可实例化是指不可实例化Animal，但是还是可以实例化cat
    animal->speak();

    delete animal;
    //这里还是会调用父类的析构函数是因为最开始是先构造父类的对象，然后子类再继承的
    //先构造父类，然后再析构的时候先析构子类，再析构父类
}

int main(){
    test01();
}

/**
 * 虚析构：
 * 解决问题：通过父类指针指向子类对象被释放时不干净导致的问题
 * 虚析构写法：virtual ~类名(){}
 * 虚析构可以实例化原对象，但是纯虚析构不可以实例化
 **/ 