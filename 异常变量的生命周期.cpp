#include <iostream>

using namespace std;

class MyException{
    public:
    MyException(){
        cout << "这是MyException的默认构造" << endl;
    }
    MyException(const MyException& e){
        cout << "这是MyException的拷贝构造" << endl;
    }

    void func(){
        cout << "调用func()函数" << endl;
    }

    void PringError(){
        cout << "error" << endl;
    }

    ~MyException(){
        cout << "这是MyException的析构函数" << endl;
    }
};

void doWork(){//这里都是直接抛出一个异常
    //throw MyException();//传入的是一个异常

    throw new MyException();//这样创建的就在堆上面了，就需要自己去把他清除掉

    throw &MyException();//传入的是一个异常的地址（所以会立马析构掉）
    //感觉是编辑器的原因，导致了报错
    //通过知乎的查询，发现这里是msvc对其的拓展导致代码可以允许
}

void test01(){
    try{
        doWork();
    }
    catch(MyException *e){
        //MyException e//接收一个异常
        //解释：前面是一个默认构造，后面这里是一个拷贝构造（所以要构造析构两次）
        //缺点：会有多余的开销（主要是下面也会拷贝构造一次）

        //MyException &e//接收一个异常 推荐使用这个
        //解释：上面有多余的开销，所以用引用就可以减少开销

        //MyException *e//接收一个异常的地址
        //解释：这样的话，上面就要传入一个地址，但是因为是地址，所以在上面就会立马构造立马析构掉，
        //用这个会导致e在到达catch之前就因为栈解旋而被释放掉
        //所以这里传进来的就不是真正的实体了，就无法调用该类的函数了
        //例如：
        //e->func();//这里语法插件没有报错，但是实际上在传进来之前就已经被释放掉了，所以无法调用，会报错

        e->PringError();

        cout << "捕获异常MyException" << endl;

        delete e;//如果是new出来的异常对象，这里就要自己手动把它给释放了
    }
}

int main(){
    test01();
}