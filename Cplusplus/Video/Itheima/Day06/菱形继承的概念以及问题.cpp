#include <iostream>

using namespace std;

//这里解释虚继承的过程（内部原理）出现了问题，挖坑，日后解决

class Animal{
    public:
        int m_Age;
};

//虚基类
class Sheep :virtual public Animal{

};

//虚基类
class Tuo :virtual public Animal{

};

class SheepTuo :public Sheep, public Tuo{
    /**
     * vbptr 虚基类指针
     * 指向一张虚基类表
     * 通过表找到偏移量
     * 找到共有数据
     **/ 
};

void test01(){
    SheepTuo st;
    st.Sheep::m_Age = 200;
    st.Tuo::m_Age = 100;

    /**
     * 菱形继承出现的问题，两者都是继承Animal的，但是实际结果却是m_Age为两个类独自拥有
     * 为了解决这种情况，用虚继承来处理，使得二者共用的继承的是同一个属性，操作的是共享的一份数据
     * 所以可以这样访问的了
    **/

    cout << st.Sheep::m_Age << endl;
    cout << st.Tuo::m_Age << endl;
    cout << st.m_Age << endl;
}

void test02(){
    SheepTuo st;
    st.m_Age = 100;

    //找出Sheep的偏移量
    // cout << *(int*)((int*)*(int*)&st + 1) << endl;
    /**
     * 第一层int是指把它从类里面取出来
     * 第二层int是取出它在序列表中的位置
     * +1是指它的在列表中的步长，即加多少才到实际的位置
     * 最后一层是更具这个位置输出当前的数字位置（即偏移量）
     **/ 

    //找出Tuo的偏移量
    //cout << *((int*)((int*)*((int*)&st + 1) + 1)) << endl;
}

int main(){
    test01();

    // test02();
}