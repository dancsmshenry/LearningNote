#include <iostream>

using namespace std;

//静态转换
void test01(){
    char a = 'a';

    double d = static_cast<double>(a);

    cout << "d = " << d << endl;//d = 97
}

//父子类型转换
class Base{};//父类，基类
class Child:public Base{};//子类
class Other{};

//static_cast使用 static_cast<要转换为的目标类型>（原始对象）
void test02(){
    Base *base = NULL;
    Child *child = NULL;

    //将base转为Child*类型 向下 不安全
    Child *child2 = static_cast<Child*>(base);

    //将child转为Base* 向上 安全
    Base *base2 = static_cast<Base*>(child);

    //转other类型 转换无效
    //Other *other = static_cast<Other*>(base);
}

/**
 * 静态转换：
 * 父与子类型转换
 * 可以进行基础数据类型转换
 * 没有父子关系的自定义类型不能互相转换
 **/ 



void test03(){
    //基础类型不可以动态转换，因为动态转换中不可以出现精度的丢失
    //即失去精度或者不安全的都不可以转换
    char c = 'a';

    // double b = dynamic_cast<double>(c);
}

//动态转换
class Base2{
    virtual void func(){}
};
class Child2:public Base2{
    virtual void func(){}
};
class Other2{};

void test04(){
    Base2 *base = NULL;
    Child2 *child = NULL;

    //child转Base2安全
    Base2 *base2 = dynamic_cast<Base2*>(child);

    //Base2转child2 *不安全
    // Child2 * child2 = dynamic_cast<Child2*>(base);
    //没有多态的时候就会报错
    //dymatic_cast 如果发生了多态，那么可以让基类转为派生类，向下转换

    //发生了多态的情况
    Base2 *base3 = new Child2;//想一下多态的定义
    Child2 *child3 = dynamic_cast<Child2*>(base3);
}

/**
 * 动态转换
 * 不可以转换基础数据类型
 * 父子之间可以转换
 * 父转子 不可以
 * 子转父 可以
 * 发生了多态（虚函数） 都可以
 **/ 



//常量转换
void test05(){
    const int *p = NULL;
    //去除const
    int *newp = const_cast<int*>(p);

    int *p2 = NULL;
    //加上const
    const int *newp2 = const_cast<const int*>(p2);

    //不能对非指针非引用的变量进行转换
    const int a = 10;
    //int b = const_cast<int>(a);

    int c = 10;
    int & c1 = c;
    const int &newc1 = static_cast<const int&>(c1);
    const int &newc2 = const_cast<const int&>(c1);//可以的
}

//重新解释转换（reinterpet_cast）
void test06(){
    int a = 10;
    int *newa = reinterpret_cast<int *>(a);

    Base *base = NULL;
    Other *other = reinterpret_cast<Other*>(base);
    //最不安全，也是最不推荐
}

int main(){
    // test01();

    // test02();

    // test04();

    // test05();
}