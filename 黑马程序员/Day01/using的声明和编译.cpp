#include <iostream>

using namespace std;

namespace A
{
    int id = 20;
}

namespace B
{
    int id = 500;
}

void test_01()
{
    //int id = 200;
    //这里会有二义性，即会产生矛盾

    //强调声明的是A空间的id
    using A::id;

    cout << id << endl; //cout << A::id << endl;也可的，这也很好的解释了为什么会有二义性
}

void test_02()
{
    //int id = 30;
    using namespace A;
    //这里体现的是就近原则，即这里引用了A这个空间，但是用不用A空间里的变量其实是不一定的，所以引用的还是这里声明了的变量
    //但是如果打开了两个房间的话，而这个变量没有指定的话，就必须要指定输出
    using namespace B;

    cout << B::id << " " << endl;
}

int main()
{
    test_01();
    test_02();
}