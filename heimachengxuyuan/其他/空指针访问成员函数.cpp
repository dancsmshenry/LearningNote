#include <iostream>

using namespace std;

/**
 * �����Ա����û���õ�this����ô��ָ�����ֱ�ӷ���
 * ���򣬾�Ҫע��������Ƿ������˿�ָ��
 **/ 

class Person{
    public:
        void show(){
            cout << "����show��������" << endl;
        }

        void showAge(){
            if (this == NULL) cout << "����һ����ָ��" << endl;
            cout << "������" << this->m_Age << endl;
        }

        int m_Age = 65345;
};

void test01(){
    Person *p1 = NULL;
    p1->show();//��ָ����Ե���show()��������Ϊ��û�е���thisָ��
    p1->showAge();//���ﱨ������Ϊ���m_Age��ʱ����Ҫthisָ����ȷ��ָ��Ķ��󣨶���ʱָ�����null��
    //�������ʣ�Ϊʲô�������������ᱨ��İ���������
    int a = p1->m_Age;
    cout << a << endl;
}

int main(){
    test01();
}