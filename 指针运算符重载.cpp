#include <iostream>

using namespace std;

class Person{
    public:
        Person(int age){
            this->m_Age = age;
        }

        void showAge(){
            cout << "Age: " <<  m_Age << endl;
        }

        ~Person(){
            cout << "������������" << endl;
        }

        int m_Age;
};

//����ָ�룬�����й��Զ������͵Ķ����ö�������Զ����ͷ�
class smartPointer{
    public:
        smartPointer(Person * person){
            this->person = person;
        }

    private:
        Person *person;
};

void test01(){
    //Person p1(10);//��Ϊ������ջ�ϴ����Ķ������Ի��Զ�������������
    
    Person * p2 = new Person(10);//��Ϊ�ǿ����ڶ��ϵĶ������Բ����Զ�������������
    delete p2;//���Ե��ֶ���������ʱ���Ҫ������ָ������æ��

    smartPointer sp(new Person(10));//ע�⣺sp�ǿ��ٵ���ջ�ϵģ�����sp���Զ�����
    //��Ȼ���Զ������������������������person
}

int main(){
    test01();
}