#include <iostream>

using namespace std;

class myException{//�Զ����쳣�࣬�����׳��Զ���Ķ���
    public:
        void printError(){
            cout << "�׳��Զ�����쳣" << endl;
        }
};

class Person{
    //�����дpublic�Ļ����ǹ��캯�������캯������Ϊ��˽�ܵ��ˣ���������������
    public:
    Person(){
        cout << "������person�Ĺ��캯��" << endl;
    }

    void print(){
        cout << "������print����" << endl;
    }

    ~Person(){
        cout << "������person����������" << endl;
    }
};

class Person1{
    //�����дpublic�Ļ����ǹ��캯�������캯������Ϊ��˽�ܵ��ˣ���������������
    public:
    Person1(){
        cout << "������person1�Ĺ��캯��" << endl;
    }

    void print(){
        cout << "������print����" << endl;
    }

    ~Person1(){
        cout << "������person1����������" << endl;
    }
};

int myDevide(int a, int b){
    if (b == 0){
        //���b���쳣 �׳��쳣
        // return -1;

        //throw -1;//�׳�int���쳣

        //throw 3.14;//�׳�double���쳣

        //throw 'a';

        //�쳣���뱻��������ϵͳ��ֱ�ӹҵ�

        //�׳������쳣

        Person p1;//ջ����
        Person1 p2;
        //��try��throw�׳��쳣֮ǰ ����ջ�ϵĶ��󶼻ᱻ�ͷ�
        //�����������ȱ�test01��try���ã�Ȼ��ֱ���׳��쳣֮ǰ�����е�ջ�ϵ�Ԫ�ض��ᱻ���
        //��try��ʼ����throw�׳��쳣֮ǰ������ջ�ϵĶ��󶼻ᱻ�ͷ� ������̳�Ϊջ����
        //ջ�ϵĶ���Ĺ���˳��������˳���෴�����ȹ���ĺ������������������������ջ�����ʣ�

        //p1.print();
        

        throw myException();//�׳���������
    }

    return a/b;
}

void test01(){
    int a = 10;
    int b = 0;

    //int ret = myDevide(a, b);//������ôд������ص���-1�Ļ������޷��ж��ǲ��Ƿ����쳣��

    try{//��һ��
        myDevide(a, b);
    }
    catch(int){//�����쳣
        cout << "int�����쳣����" << endl;
    }
    catch(double){//����double�쳣
        //������������ﱨ������쳣�Ļ�����ֱ��throw���double�쳣����һ��
        throw;
        //cout << "double�����쳣����" << endl;
    }
    catch(myException e){
        e.printError();
    }
    catch(...){//���������쳣����
        cout << "���������쳣����" << endl;
    }
}

int main(){
    try{
        test01();
    }
    catch(double){//���û���κ��쳣��Ҫ������Ļ�����ô�ͻ���ó�Ա����terminate���� ʹ�����ж�
        cout << "main�����е�double�����쳣" << endl;
    }
    catch(...){
        cout << "main�����е��������͵��쳣����" << endl;
    }
}