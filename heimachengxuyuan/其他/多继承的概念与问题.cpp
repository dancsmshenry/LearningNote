#include <iostream>

using namespace std;

class Base1{
    public:
        Base1(){
            cout << "����Base1�Ĺ���" << endl;
            m_A = 100;
        }

        int m_A;
};

class Base2{
    public:
        Base2(){
            cout << "����Base2�Ĺ���" << endl;
        }

        int m_A;
        int m_B;
};

class Son :public Base1, public Base2{//��̳е�д��
    public:
        Son(){
            cout << "����Son�Ĺ���" << endl;
        }

        int m_C;
        int m_D;  
};

void test01(){
    //cout << sizeof(Son) << endl;//16 = 4 * 4
     Son son1;
     //cout << son1.m_A << endl;//��ʱ��ͻ���ֶ����ԣ�����������֪������ʵ�����һ��
     cout << son1.Base1::m_A << endl;
}

int main(){
    test01();
}