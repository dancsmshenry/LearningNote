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

    ~MyException(){
        cout << "这是MyException的析构函数" << endl;
    }
};

void doWork(){
    //throw MyException();
    //throw new MyException();//这样创建的就在堆上面了，就需要自己去把他清除掉
    throw &MyException();
}

void test01(){
    try{
        doWork();
    }
    catch(MyException *e){//MyException e 这里有一个拷贝构造，也会有多余的开销
    //MyException &e用这个就可以减少开销
    //MyException *e用这个会导致e在到达catch之前就因为栈解旋而被释放掉
        //e->func();//这里语法插件没有报错，但是实际上在传进来之前就已经被释放掉了，所以无法调用，会报错
        cout << "捕获异常MyException" << endl;
        //delete e;
    }
}

int main(){
    test01();
}