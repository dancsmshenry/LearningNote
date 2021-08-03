#include <iostream>

using namespace std;

const double pi = 3.14;

//设计一个类，求圆的周长
//周长公式：2*pi*r
class Circle{//class代表一个类，后面紧跟的是类的名称
    public:
        //在类里面写成员函数
        double CalculateZC(){
            return 2 * pi * m_R;
        }

        void setR(int r){
            this->m_R = r;
        }

        int getR(){
            return this->m_R;
        }

    private:
        int m_R;//半径，成员属性
};

void test01(){
    Circle c1;
    c1.setR(10);
    cout << "the zhouchang of a circle is " << c1.CalculateZC() << endl;
}

int main(){
    test01();
}