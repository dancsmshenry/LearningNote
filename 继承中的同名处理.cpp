#include <iostream>

using namespace std;

class Base{
    public:
        Base(){
            m_A = 100;
        }

        void func(){
            cout << "����Base�е�func()����"  << endl;
        }

        void func(int a){
            cout << "����Base�е�func(int a)����" << endl;
        }

    public:
        int m_A;
};

class Son1 :public Base{
    public:
        Son1(){
            m_A = 200;
        }

        void func(){
            cout << "����Son1�е�func()����"  << endl;
        }
    
    public:
        int m_A;
};

void test01(){
    Son1 son1;
    //cout << son1.m_A << endl;//�ͽ�ԭ�򣬷��ʵ���Son1��m_A
    //cout << son1.Base::m_A << endl;//ͨ�����������Base��m_A

    //son1.func();
    //son1.Base::func();//ͬ��

    son1.Base::func(10);//�������һ��Ҫ�ӿռ���а�
}
//���ۣ����಻�Ḳ�Ǹ����ͬ�����Ժͷ���������Ҫ�ҵ���������Ժͷ���ֻҪ�������ռ伴��

int main(){
    test01();
}