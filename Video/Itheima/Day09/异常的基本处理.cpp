#include <iostream>

using namespace std;

class myException{//自定义异常类，可以抛出自定义的对象
    public:
        void printError(){
            cout << "抛出自定义的异常" << endl;
        }
};

class Person{
    //如果不写public的话，那构造函数和析造函数都变为了私密的了？？好像是这样的
    public:
    Person(){
        cout << "这里是person的构造函数" << endl;
    }

    void print(){
        cout << "调用了print函数" << endl;
    }

    ~Person(){
        cout << "这里是person的析构函数" << endl;
    }
};

class Person1{
    //如果不写public的话，那构造函数和析造函数都变为了私密的了？？好像是这样的
    public:
    Person1(){
        cout << "这里是person1的构造函数" << endl;
    }

    void print(){
        cout << "调用了print函数" << endl;
    }

    ~Person1(){
        cout << "这里是person1的析构函数" << endl;
    }
};

int myDevide(int a, int b){
    if (b == 0){
        //如果b是异常 抛出异常
        // return -1;

        //throw -1;//抛出int型异常

        //throw 3.14;//抛出double型异常

        //throw 'a';

        //异常必须被处理，否则系统会直接挂掉

        //抛出自制异常

        Person p1;//栈解旋
        Person1 p2;
        //从try到throw抛出异常之前 所有栈上的对象都会被释放
        //所以这里是先被test01中try调用，然后直到抛出异常之前，所有的栈上的元素都会被清空
        //从try开始，到throw抛出异常之前，所有栈上的对象都会被释放 这个过程称为栈解旋
        //栈上的对象的构造顺序与析构顺序相反，即先构造的后析构，后构造的先析构（联想栈的性质）

        //p1.print();
        

        throw myException();//抛出匿名对象
    }

    return a/b;
}

void test01(){
    int a = 10;
    int b = 0;

    //int ret = myDevide(a, b);//早期这么写如果返回的是-1的话，就无法判断是不是发生异常了

    try{//试一试
        myDevide(a, b);
    }
    catch(int){//捕获异常
        cout << "int类型异常捕获" << endl;
    }
    catch(double){//捕获double异常
        //如果不想在这里报错这个异常的话，就直接throw这个double异常给上一级
        throw;
        //cout << "double类型异常捕获" << endl;
    }
    catch(myException e){
        e.printError();
    }
    catch(...){//其他类型异常捕获
        cout << "其他类型异常捕获" << endl;
    }
}

int main(){
    try{
        test01();
    }
    catch(double){//如果没有任何异常需要被处理的话，那么就会调用成员函数terminate函数 使程序中断
        cout << "main函数中的double类型异常" << endl;
    }
    catch(...){
        cout << "main函数中的其他类型的异常处理" << endl;
    }
}