#include <iostream>

using namespace std;

/**
 * 多态分类：
 * 静态多态 函数重载
 * 动态多态 虚函数 继承关系 
 * 
 * 静态联编：地址早绑定 编译阶段绑定好地址
 * 动态联编：地址晚绑定 运行时候绑定好地址
 **/ 
class Animal{
    public:
        virtual void doSpeak(){
            cout << "Animal::doSpeak()" << endl;
        }

        virtual void doEat(){
            cout << "Animal::doEat()" << endl;
        }
};

class Cat :public Animal {
    public:
        virtual void doSpeak(){
            cout << "Cat::doSpeak()" << endl;
        }

        virtual void doEat(){
            cout << "Cat::doEat()" << endl;
        }
};

/**
 * 调用doSpeak,dospeak函数的地址早绑定好了，早绑定，静态联编，编译阶段就确定好了地址
 * 如果想要调用猫的speak，不能提前绑定好函数的地址，所以需要在运行时候再去确定函数地址
 * 动态联编，写法是将animal的dospeak声明为虚函数，在父类上声明虚函数，发生了多态
 * 
 * 多态的定义：父类的引用或者指针 指向 子类对象
 * 说白了，就是让代码在具体运行的时候去判断调用哪个函数
 **/ 
void Speak(Animal &animal){//Animal& animal = cat;
    animal.doSpeak();
}

//如果发生了继承的关系，编译器允许进行类型的转换
void test01(){
    Cat cat1;

    //如果调用的函数里面是animal的doSpeak，那就调用的是animal的doSpeak
    Speak(cat1);
}

void test02(){
    // cout << sizeof(Animal) << endl;

    //父类指针指向子类对象，多态
    Animal *animal = new Cat;

    animal->doSpeak();
    //*(int*)*(int*)animal//函数地址
    //((void(*)()) (*(int*)*(int*)animal))();
}

int main(){
    // test01();

    test02();
}

/**
 * 多态原理的解析：
 * 当父类的某个函数变为虚函数（在前面用virtual来修饰的）以后：
 * 在父类的结构中就会有一个虚函数指针（virtual function pointer 即vfptr），在其内部指向虚函数表
 * 而当有子类继承了该父类的时候，在其子类也会有一个虚函数表，
 * 
 * 重写：子类写父类的同名函数，且返回值，参数个数，类型，顺序都相同
 * 对象创建的时候，调用构造函数，将所有的vfptr都指向自己的vftable
 * 而这个操作我们是看不到的
 * 
 * 如果子类又重写父类的同名函数，就指向这个重写的函数
 * 这个子类的虚函数指针就会指向这个重写的函数，而不是父类的同名的函数
 **/ 