#include <iostream>
#include "game1.h"
#include "game2.h"

// namespace命名空间
// 用途:是用来解决命名冲突的问题

//命名空间还可以放函数，结构体，类，变量等等
//命名空间必须定义在全局作用域下
//命名空间可以嵌套命名空间
namespace A{
    void func();
    int m_A = 10;
    struct Person{
        Person(){}
    };
    class Animal{};
    namespace B{
        int m_A = 20;
    }
}

void test01(){
    std::cout << A::B::m_A << std::endl;
    std::cout << A::m_A << std::endl;
}

//命名空间是开放的，可以随时往原来的命名空间添加内容
namespace A{
    //此命名空间会和上面的命名空间A进行合并
    int m_B = 1000;
}

void test02(){
    std::cout << "A :: m_A = " << A::m_A << " and A :: m_B = " << A::m_B << std::endl;
}

//无名，匿名空间
namespace {
    int m_C = 0;
    int m_D = 0;
    //当写了无名命名空间，相当于写了static int m_C = 0, static int m_D = 0
    //静态变量，只能在当前文件内使用
}

//命名空间可以起别名
namespace veryLongName{
    int m_A = 777;
}

void test03(){
    namespace veryShortName = veryLongName;//起别名
    std::cout << veryShortName::m_A << std::endl;
}

int main() {
    LOL::goAtk();
    WangZhe::goAtk();
    std::cout << std::endl;

//    test01();
//    test02();
    test03();

    return 0;
}
