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

        ~Person(){
            cout << "Ĭ�����캯��" << endl;
        }
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
    delete p3;
    //�޷��ͷŵ�p3
}

int main(){
    //test01();
    test02();
}