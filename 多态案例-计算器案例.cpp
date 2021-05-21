#include <iostream>

using namespace std;

class Calculator{
    public:
        void setv1(int v1){
            this->val1 = v1;
        }

        void setv2(int v2){
            this->val2 = v2;
        }

        int getResult(string oper){
            if (oper == "+"){
                return val1 + val2;
            }
            else if (oper == "-"){
                return val1 - val2;
            }

            return 0;
        }

    private:
        int val1;
        int val2;
};

//开发原则：对拓展开放，对修改关闭

//利用多态实现计算器
//这个类有了纯虚函数，通常又称为抽象类
class abstractCacluator{
    public:
        // virtual int getResult(){
        //     return 0;
        // }
        virtual int getResult() = 0;//纯虚函数
        //如果父类中有纯虚函数，子类继承父类，就必须实现纯虚函数

        void setv1(int v1){
            this->val1 = v1;
        }

        void setv2(int v2){
            this->val2 = v2;
        }

        int val1;
        int val2;
};

//加法计算器
class PlusCacluator :public abstractCacluator{
    public:
        virtual int getResult(){
            return val1 + val2;
        }
};

//减法计算器
class MinusCacluator :public abstractCacluator{
    public:
        virtual int getResult(){
            return val1 - val2;
        }
};

//乘法计算器
class MulCacluator :public abstractCacluator{
    public:
        virtual int getResult(){
            return val1 * val2;
        }
};

//除法计算器
class DivideCacluator :public abstractCacluator{
    public:
        virtual int getResult(){
            return val1 / val2;
        }
};

class A :public abstractCacluator{
    public:
        int getResult(){
            return 0;
        }
};

void test01(){
    Calculator cal;
    cal.setv1(10);
    cal.setv2(20);
    cout << cal.getResult("+") << endl;
}

void test02(){
    abstractCacluator * abc;
    abc = new PlusCacluator;
    abc->setv1(10);
    abc->setv2(20);

    cout <<  abc->getResult() << endl;

    delete abc;

    abc = new MinusCacluator;
    abc->setv1(10);
    abc->setv2(20);

    cout <<  abc->getResult() << endl;
}
/**
 * 早期方法：不利于拓展
 * 开发原则：开闭原则：对拓展开放，对修改关闭
 * 利用多态实现，利于后期拓展，结构性非常好，可读性高，效率稍微比较低，发生多态内部结构复杂
 **/ 

void test03(){
    A a;//这里因为没有继承getResult函数，所以报错
    //已经继承了，所以不会报错

    //abstractCacluator a1;
    //因为类中有了纯虚函数，所以这个类不能实例化对象了
    //如果父类中有了纯虚函数，不能实例化对象了
}

/**
 * 多态成立的条件：
 * 有继承
 * 子类重写父类虚函数
 *  返回值，函数名，函数参数，必须和父类完全一致，析构函数除外
 * 子类中virtual关键字可以不写
 * 如果子类继承的是父类的纯虚函数，那子类最好加上virtual
 **/ 

/**
 * 纯虚函数写法 virtual void func() = 0;
 * 抽象类型
 * 抽象类 不可实例化对象
 * 如果类 继承了抽象类 必须重写抽象类中的纯虚函数
 **/ 

int main(){
    //test01();
    test02();
}