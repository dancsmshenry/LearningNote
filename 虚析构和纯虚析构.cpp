#include <iostream>

using namespace std;

class Animal{
    public:
        virtual void speak(){
            cout << "������˵��" << endl;
        }

        //��ͨ���� �ǲ����������������ģ����Կ��ܻᵼ�¿ռ��ͷŲ��ɾ�
        //����������������������,��Ҫ���������
        //������ﲻ���麯���Ļ����ͻᵼ������delete���ﲻ���ͷ���ȫ
        //��ע������ʹ�ø����ָ�봴�������࣬���ﲻ���麯���ᵼ������������õ��Ǹ���ĺ���������������Cat��
        // virtual ~Animal(){
        //     cout << "Animal����������" << endl;
        // }

        //��������
        //���ԣ���Ҫ����������Ҫʵ�� ��������������ʵ��
        virtual ~Animal() = 0; //�����൱��һ������
        //���ԣ���������г����� ������������ ��ô�������Ϊ������
        // ������ ָ����ʵ��������
};

Animal::~Animal(){
    //��������������ʵ��
    cout << "���������ĺ�������ʵ��" << endl;
}

class Cat:public Animal{
    public:
        Cat(const char * name){
            this->m_Name = new char[strlen(name) + 1];
            strcpy(this->m_Name, name);
        }

        virtual void speak(){//�����virutal���Բ�д������Ϊ�˱����Ǽ̳и�����麯������û���д��
            cout << "Сè��˵��" << endl;
        }

        ~Cat(){
            cout << "Cat����������" << endl;
            if (this->m_Name != NULL){
                delete[] this->m_Name;
                this->m_Name = NULL;
            }
        }

        char *m_Name;
};

void test01(){
    Animal * animal = new Cat("Tom");//���麯���Ĳ���ʵ������ָ����ʵ����Animal�����ǻ��ǿ���ʵ����cat
    animal->speak();

    delete animal;
    //���ﻹ�ǻ���ø����������������Ϊ�ʼ���ȹ��츸��Ķ���Ȼ�������ټ̳е�
    //�ȹ��츸�࣬Ȼ����������ʱ�����������࣬����������
}

void test02(){
    //Animal * animal = new Animal();//����ᱨ��һ���������ǲ�����ʵ���������
}

int main(){
    test01();
}

/**
 * ������⣺ͨ������ָ��ָ����������ͷ�ʱ���ɾ����µ�����
 * ������д����virtual ~
 * ����������ʵ����ԭ���󣬵��Ǵ�������������ʵ����
 **/ 