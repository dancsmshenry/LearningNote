#include <iostream>

using namespace std;

class Base{
    public:
        Base(){
            cout << "Base�Ĺ��캯������" << endl;
        }

        ~Base(){
            cout << "Base�����캯������" << endl;
        }
};


/**
 * �����̳и���ĳ�Ա���ԣ���Ա����
 * ���ǲ���̳и���Ĺ��캯�������캯��
 * ֻ�и���֪����ι���������Լ������ԣ������಻֪��
 **/ 
class Son1 :public Base
{
    public:
        Son1(){
            cout << "Son1�Ĺ��캯������" << endl;
        }

        ~Son1(){
            cout << "Son1�����캯������" << endl;
        }
};

void test01(){
    //Base base1;

    //Son1 son1;
    // Base�Ĺ��캯������
    // Son1�Ĺ��캯������
    // Son1�����캯������
    // Base�����캯������

    //Son1 *son1 = new Son1();
}

class Base2{
    public:
        Base2(int a){
            this->m_A = a;
            cout << "Base���вι��캯������" << endl;
        }

        int m_A;
};

class Son2 :public Base2{
    public:
        //Son2() :Base2(10)
        Son2(int a) :Base2(a)
        {
            //�������ֱ��д����Son2�Ļ��ͻᱨ����Ϊ���ĸ�����û���޲ι����
            //����취�����ó�ʼ���б�ʽ ��ʾ�����вι���
            //д��һ��Son2():Base2(10)
            //д������Son2(int a):Base(a)

        }
};
//���䣺���������û�к���Ĭ�Ϲ��죬��ô����������ó�ʼ���б�ķ�ʽ��ʾ�ĵ��ø������������

int main(){
    test01();
}