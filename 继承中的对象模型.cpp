#include <iostream>

using namespace std;

//继承会继承所有的属性和函数，但是编译器就会把它们都隐藏了

class Base{
    public:
        int m_A;
    protected:
        int m_B;
    private:
        int m_C;
};

class Son1 :public Base{
    public:
        int m_D;
};

class Son2 :protected Base{
    public:
        int m_D;
};

class Son3 :private Base{
    public:
        int m_D;
};

void test01(){
    Son1 son1;
    cout << sizeof(son1) << endl;//16,这里是公共继承，虽然名义上没有继承到m_C但是系统内部还是有继承到的

    Son2 son2;
    cout << sizeof(son2) << endl;//16，理由同上

    Son3 son3;
    cout << sizeof(son3) << endl;//16，理由同上
}

int main(){
    test01();
}