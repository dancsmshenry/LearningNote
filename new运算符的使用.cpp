#include <iostream>

using namespace std;

/**
 * ��ͳ�ķ����ڴ��ȱ�㣺
 * ����ȷ������ĳ��ȣ���ÿռ�����ǿ��ת����
 * malloc����ռ����ʧ�ܣ���������ж���ȷ���ռ����óɹ�
 * ʹ�ö���ǰ���������г�ʼ��
 **/

class Person{
    public:
        Person(){
            cout << "Ĭ�Ϲ��캯��" << endl;
        }

        Person(int a){
            cout << "�вι��캯��" << endl;
        }

        ~Person(){
            cout << "Ĭ�����캯��" << endl;
        }

        int m_A;
};

void test01(){
    //Person p1;//��ջ�Ͽ��ٿռ�

    Person *p2 = new Person;//�ڶ����Ͽ��ٿռ�
    //����new�����Ķ��󶼻᷵�ظ����͵�ָ��
    //malloc���ص���void*ָ�룬��Ҫǿת
    //new��һ�������������ù��캯��
    //�ͷ� �����ռ�
    //deleteҲ������������newһ���ã���malloc���free��

    delete p2;
}

void test02(){
    void *p3 = new Person;
    //����void* ����new������ָ���ʱ�򣬻�����ͷŵ�����
    //delete p3;
    //�޷��ͷŵ�p3
}

void test03(){
    //ͨ��new�������飬һ�������Ĭ�Ϲ�����ú����������ṩ�вι����ʱ��ҲҪ�ṩĬ�Ϲ��죩
    Person *pArray = new Person[10];//�������ٿռ�
    //Person pArray2[2] = {Person(1), Person(2)};//��ջ�Ͽ������飬����ָ���вι���

    //delete pArray;//�������޷��ͷ������
    delete [] pArray;//��������ȷ��
    //���ͣ���ʹ��delete��ʱ�򣬱�����delete֪���ڴ�ռ����Ƿ����һ����¼�����С����
    //���Ե�ʱdelete[]��ʱ��delete��֪����һ���������飬��֪��Ҫdelete����
    //�������飺��ǰ����һ�����������������������
    //�������[]����delete�ͻ�ֱ���ͷ���ǰ����Ǹ����󣬶����ܺ���Ķ���
}

int main(){
    //test01();
    //test02();
    test03();
}