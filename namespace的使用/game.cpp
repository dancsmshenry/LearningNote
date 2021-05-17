#include "game_01.cpp"
#include <iostream> //#include "game_01.h"所以这里为什么不可以写这一条呢？？？

using namespace std;

//namespace命名空间主要用于解决命名冲突的问题
//命名空间下可以放变量，函数，结构体，类
namespace A
{
    int m_a = 666;
    void func();
    struct Game
    {
        int c;
        int d;
    };
    class Animals
    {
    };
    namespace B
    {
        int m_a = 999;
    }
}
//命名空间必须定义在全局作用域下

//可以相互嵌套

//命名空间是开放的，即后续创建相同的命名空间不会覆盖原来的命名空间

//无名/匿名空间，相当于写了static int m_C, static int m_D;，即是静态变量
namespace
{
    int m_c = 9;
    int m_d = 6;
}

//可以给namespace起别名
void test()
{
    namespace Aa = A;
    cout << "作用域A下的(是别名):" << Aa::m_a << endl;
}

int main()
{
    FirstSpace::attack();
    cout << "作用域A下的B下的m_a变量：" << A::B::m_a << endl;
    cout << "作用域A下的m_a变量：" << A::m_a << endl;
    test();
    return 0;
}