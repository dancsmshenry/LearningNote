#include <iostream>

using namespace std;

//异常基类
//系统内的很多异常就是用多态来写的
class BassException{
    public:
        virtual void printError(){

        }
};

class NullPointerException : public BassException{
    public:
        virtual void printError(){
            cout << "空指针异常" << endl;
        }
};

class OutOfRangeException : public BassException{
    public:
        virtual void printError(){
            cout << "越界异常" << endl;
        }
};

void doWork(){
    // throw NullPointerException();

    throw OutOfRangeException();
}

void test01(){
    try{
        doWork();
    }
    catch(BassException &e){
        e.printError();
    }
}

int main(){
    test01();
}

//利用异常来实现 printError同一接口调用，来抛出不同的错误对象