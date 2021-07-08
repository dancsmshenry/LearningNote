#include <iostream>

using namespace std;

/**
 * public是公共的变量，是可以访问的
 * protected是保护变量，只能类内访问，可以被继承
 * private是私有变量，只能是类内访问，和protect的区别与继承有关（private不可被继承）
 **/ 

class Base1{
    public:
        int m_A;
    protected:
        int m_B;
    private:
        int m_C;
};

//公有继承
/**
 * 父类的私有无法继承，其他的原封不动的继承
 **/ 
class Son1 :public Base1{
     public:
        void func(){
            cout << m_A << endl;//基类内的公有属性，可继承，还是public
            cout << m_B << endl;//基类内的保护属性，可继承，还是protected 
            //cout << m_C << endl;//基类内的私有属性，不能被继承
        }
};

class Base2{
    public:
        int m_A;
    protected:
        int m_B;
    private:
        int m_C;
};

//保护继承
/**
 * 父类的私有无法继承，其他的全部继承为保护变量
 **/ 
class Son2 :protected Base2{
    public:
        void func(){
            cout << m_A << endl;//基类内的公有属性，可继承，变为protected
            cout << m_B << endl;//基类内的保护属性，可继承 还是protected 
            //cout << m_C << endl;//基类内的私有属性，不能被继承
        }
};

class Base3{
    public:
        int m_A;
    protected:
        int m_B;
    private:
        int m_C;
};

//私有继承
/**
 * 父类的私有无法继承，其他的全部继承为私有变量
 **/ 
class Son3 :private Base3{
    public:
        void func(){
            cout << m_A << endl;//基类中的公有属性，可继承，变为private
            cout << m_B << endl;//基类中的保护属性，可继承，变为private
            //cout << m_C << endl;//基类内的私有属性，不能被继承
        }
};

class GrandSon3 :public Son3{
    public:
        void Func(){
            //cout << m_A << endl;//孙子类中，访问不到m_A,因为m_A在Son3中变为了私有属性了
        }
};

int main(){

}