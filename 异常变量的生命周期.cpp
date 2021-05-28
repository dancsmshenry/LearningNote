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

    void PringError(){
        cout << "error" << endl;
    }

    ~MyException(){
        cout << "����MyException����������" << endl;
    }
};

void doWork(){//���ﶼ��ֱ���׳�һ���쳣
    //throw MyException();//�������һ���쳣

    throw new MyException();//���������ľ��ڶ������ˣ�����Ҫ�Լ�ȥ���������

    throw &MyException();//�������һ���쳣�ĵ�ַ�����Ի�������������
    //�о��Ǳ༭����ԭ�򣬵����˱���
    //ͨ��֪���Ĳ�ѯ������������msvc�������չ���´����������
}

void test01(){
    try{
        doWork();
    }
    catch(MyException *e){
        //MyException e//����һ���쳣
        //���ͣ�ǰ����һ��Ĭ�Ϲ��죬����������һ���������죨����Ҫ�����������Σ�
        //ȱ�㣺���ж���Ŀ�������Ҫ������Ҳ�´������һ�Σ�

        //MyException &e//����һ���쳣 �Ƽ�ʹ�����
        //���ͣ������ж���Ŀ��������������þͿ��Լ��ٿ���

        //MyException *e//����һ���쳣�ĵ�ַ
        //���ͣ������Ļ��������Ҫ����һ����ַ��������Ϊ�ǵ�ַ������������ͻ�������������������
        //������ᵼ��e�ڵ���catch֮ǰ����Ϊջ���������ͷŵ�
        //�������ﴫ�����ľͲ���������ʵ���ˣ����޷����ø���ĺ�����
        //���磺
        //e->func();//�����﷨���û�б�������ʵ�����ڴ�����֮ǰ���Ѿ����ͷŵ��ˣ������޷����ã��ᱨ��

        e->PringError();

        cout << "�����쳣MyException" << endl;

        delete e;//�����new�������쳣���������Ҫ�Լ��ֶ��������ͷ���
    }
}

int main(){
    test01();
}