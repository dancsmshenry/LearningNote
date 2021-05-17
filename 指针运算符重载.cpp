#include <iostream>

using namespace std;

/**
 * Person����showAge��Ա����
 * �����new�����Ķ�������Ҫ�յ�������
 * ����������ָ�����й�Person����
 * Ϊ��������ָ���ԭ����ָ��һģһ��ʹ�ã����Ծ�Ҫ������
 **/ 

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
        
        //����->��������ָ�������Person *pһ��ȥʹ��
        Person* operator->(){
            return this->person;//���ﷵ�ص���һ��ָ��
        }

        //����*��ʹ�ú�*ָ�루�õ�������һ����һ��ȥʹ��
        Person& operator*(){
            return *this->person;
        }

        //��������smartPointer��������person
        ~smartPointer(){
            cout << "����ָ��������personָ��" << endl;
            if (this->person != NULL){
                delete this->person;
                this->person = NULL;
            }
        }

    private:
        Person *person;
};

void test01(){
    //Person p1(10);//��Ϊ������ջ�ϴ����Ķ������Ի��Զ�������������
    
    // Person * p2 = new Person(10);//��Ϊ�ǿ����ڶ��ϵĶ������Բ����Զ�������������
    // delete p2;//���Ե��ֶ���������ʱ���Ҫ������ָ������æ��

    smartPointer sp(new Person(10));//ע�⣺sp�ǿ��ٵ���ջ�ϵģ�����sp���Զ�����
    //��Ȼ���Զ������������������������person

    sp->showAge();//���û��->�����أ�����ᱨ��
    //ע�⣺����->���ص���һ��ָ�룬����༭���������Ż��ģ�������Ӧ����sp->->showAge()��

    (*sp).showAge();//���ﲻ���صĻ�������ͬ����
}

int main(){
    test01();
}