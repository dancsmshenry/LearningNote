#include <iostream>

using namespace std;

class Animal{
    public:
        virtual void doSpeak(){//父类需要写virtual
            cout << "动物在说话" << endl;
        }

        virtual void doEat(){
            cout << "动物在吃东西" << endl;
        }
};

class Cat :public Animal {//子类可以不写
    public:
        void doSpeak(){
            cout << "小猫在说话" << endl;
        }

        void doEat(){
            cout << "小猫在吃东西" << endl;
        }
};

/**
 * 调用doSpeak,speak函数的地址早绑定好了，早绑定，静态联编，编译阶段就确定好了地址
 * 如果想要调用猫的speak，不能提前绑定好函数的地址，所以需要在运行时候再去确定函数地址
 * 动态联编，写法是 将animal的dospeak声明为虚函数，发生了多态
 * 多态的定义：父类的引用或者指针 执行 子类对象
 * 说白了，就是让代码在具体运行的时候去判断调用哪个函数
 * 静态多态 函数重载
 * 动态多态 虚函数 继承关系 
 * 静态联编：地址早绑定 编译阶段绑定好地址
 * 动态联编：地址晚绑定 运行时候绑定好地址
 **/ 
void Speak(Animal &animal){
    //编译阶段已经确定了函数的内容了
    animal.doSpeak();
}

void test01(){
    Cat cat1;
    Speak(cat1);//如果调用的函数里面是animal的doSpeak，那就调用的是animal的doSpeak
}

void test02(){
    cout << sizeof(Animal) << endl;//挖坑，我的编译器输出的时8，但是老师给的时4
}

void test03(){
    //父类指针指向子类对象，多态
    Animal *animal = new Cat;

    animal->doSpeak();//实例的对象还是cat，所以最终还是输出小猫在说话
    //挖坑，这里要求证animal是如何调用的
}

int main(){
    //test01();
    //test02();
    test03();
}
/**
 * 多态原理的解析：
 * 当父类的某个函数变为虚函数（在前面用virtual来修饰的）了以后：
 * 在父类的结构中就会有有一个虚函数指针（virtual function pointer 即vfptr）
 * 在其内部指向这个函数
 * 而当有子类继承了该父类的时候，在其子类也会有一个虚函数表，
 * //科普重写的概念：子类写父类的同名函数，且返回值，参数个数，类型，顺序都相同//
 * //对象创建的时候，调用构造函数，将所有的虚函数表指针都指向自己的虚函数表//
 * 这个子类的虚函数指针就会指向这个重写的函数，而不是父类的同名的函数
 * ps:有重写的同名函数就是这个函数，没有的话就直接继承父类的同名函数
 **/

/**
 * 多态原理的解析：
 * 当父类中有了虚函数后，内部结构就发生了改变
 * 内部多了vfptr
 *  virtual function pointer 虚函数表指针
 *  指向vftable虚函数表
 * 父类结构中的vfptr &Animal::doSpeak
 * 子类中 进行继承 会继承 vfptr vftable
 * 构造函数中 会将虚函数表指针 指向自己的虚函数表中
 * 如果发生了重写 会替换掉虚函数表中原有的dospeak，改为&Cat::speak
 * 深入内部看看是如何调用的 
 **/ 