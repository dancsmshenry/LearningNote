#include <iostream>

using namespace std;

class Base{
    public:
        static void func(){
            cout << "����func������Base��" << endl;
        }

        static int m_A;
};

int Base::m_A = 10;

class Son1 :public Base{
    public:
        static int m_A;

        static void func(){
            cout << "����Son1��func����" << endl;
        }        
};

int Son1::m_A = 100;

void test01(){
    cout << Son1::m_A << endl;//���Է�����̳еľ�̬����
    //�������Son1��Ҳ��m_A�Ļ����ͻ�����⣨û��public������£�
}

void test02(){
    // Base base1;
    // Base::func();//����������þ�̬�ĺ���

    //Son1::func();//����Ҳ���Լ̳и���ľ�̬����
    //����ע�⣬������������Ҳ��ͬ���ĺ������Ǿͻ��������ĺ���
    Son1::Base::func();//��ͬ���Ļ��������ַ�ʽ����Base�ĺ���
}

int main(){
    //test01();
    test02();
}