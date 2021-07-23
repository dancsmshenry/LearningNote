#include <iostream>

using namespace std;

//�쳣����
//ϵͳ�ڵĺܶ��쳣�����ö�̬��д��
class BassException{
    public:
        virtual void printError(){

        }
};

class NullPointerException : public BassException{
    public:
        virtual void printError(){
            cout << "��ָ���쳣" << endl;
        }
};

class OutOfRangeException : public BassException{
    public:
        virtual void printError(){
            cout << "Խ���쳣" << endl;
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

//�����쳣��ʵ�� printErrorͬһ�ӿڵ��ã����׳���ͬ�Ĵ������