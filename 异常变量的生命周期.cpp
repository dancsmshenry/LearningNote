#include <iostream>

using namespace std;

class MyException{
    public:
    MyException(){
        cout << "����MyException��Ĭ�Ϲ���" << endl;
    }
    MyException(const MyException& e){
        cout << "����MyException�Ŀ�������" << endl;
    }

    void func(){
        cout << "����func()����" << endl;
    }

    ~MyException(){
        cout << "����MyException����������" << endl;
    }
};

void doWork(){
    //throw MyException();
    //throw new MyException();//���������ľ��ڶ������ˣ�����Ҫ�Լ�ȥ���������
    throw &MyException();
}

void test01(){
    try{
        doWork();
    }
    catch(MyException *e){//MyException e ������һ���������죬Ҳ���ж���Ŀ���
    //MyException &e������Ϳ��Լ��ٿ���
    //MyException *e������ᵼ��e�ڵ���catch֮ǰ����Ϊջ���������ͷŵ�
        //e->func();//�����﷨���û�б�������ʵ�����ڴ�����֮ǰ���Ѿ����ͷŵ��ˣ������޷����ã��ᱨ��
        cout << "�����쳣MyException" << endl;
        //delete e;
    }
}

int main(){
    test01();
}