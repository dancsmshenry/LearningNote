#include <iostream>

using namespace std;

/**
 * 不要随便乱用符号重载
 * 内置数据类型的运算符不可重载
 * cout<<直接对Person自定义数据类型 进行输出
 * 将<<重载函数写到全局函数当中
 * 如果重载的时候想要访问p1的私有变量，那全局函数就要做类的友元函数
 **/ 

class Person{
    //这里因为是私有变量，所以要把全局函数变为友元函数来访问类内的属性
    friend ostream& operator<<(ostream& cout, Person& p1);
    public:
        Person(){

        }

        Person(int m_A, int m_B){
            this->m_A = m_A;
            this->m_B = m_B;
        }
    private:
        int m_A; 
        int m_B;
};

//这里如果是void的话，下面的cout << p1 << endl;就会报错，因为<<的右边是void而左边是endl（有点牵强）
ostream& operator<<(ostream& cout, Person& p1){
    cout << "m_A = " << p1.m_A << endl;
    cout << "m_B = " << p1.m_B << endl;
    return cout;

    /**
     * 解释：用ostream做返回值的原因：因为你后面还是会继续输入数值的，不能只输入一个就不输出了吧
     * 所以要用cout的ostream做返回值
     * 重载的左移运算符也最后不要写到类对象里面，因为如果此时要调用该运算符的话
     * 是这样的：Person p1(10, 10); p1 << ...; 
     * 和往常不太一样
     **/
}

void test01(){
    Person p1(10, 10);

    cout << p1 << endl;
}

int main(){
    test01();
}