#include <iostream>

using namespace std;

class Person{
    public:
        Person(){
            cout << "Ĭ�Ϲ��캯������" << endl;
        }

        Person(int a){
            cout << "�вι��캯���ĵ���" << endl;
        }

        Person(const Person& A){//����&����ֵ���ݣ��Ǿ����ִ�����һ���࣬����Ҫ��������һ�����캯�����ͽ�����ѭ����
            m_Age = A.m_Age;
            cout << "�������캯������" << endl;
        }

        ~Person(){
            cout << "������������" << endl;
        }

        int m_Age;
};

//����������õ�ʱ��
//���Ѿ������õĶ�������ʼ���µĶ���
//�Ƚϳ���
void test_01(){
    Person p1;
    p1.m_Age = 10;
    Person p2(p1);
    cout << p2.m_Age << endl;
}

//��ֵ���ݵķ�ʽ������������ֵ
void doWork(Person p1){
    //�൱��Person p1 = Person(p)
    //��������������캯����
    //������һ�����ʣ������������Ļ��������Ĵ���Ҳ���½�һ�������𣿣�

}

//��ֵ���ݵķ���������������ֵ
void test_02(){
    Person p;
    p.m_Age = 10;
    
    doWork(p);
}

Person doWork2(){
    Person p1;
    return p1;//Ҳ����˵������ķ��ػ᲻���ǿ���ȡ���ڱ༭���ģ����﷨��ϵ����
}
//Relase�»�����Ż�
/**
 * ������Щ�ң���д���ȣ���㲹��
 * Person p;//������Ĭ�Ϲ���
 * doWork2(p);
 * void doWoek2(Person & p){
 *  Person p1;//����Ĭ�Ϲ���
 * }
 **/

//��ֵ��ʽ���ؾֲ�����
void test_03(){
    Person p = doWork2();

}

int main(){
    //test_01();
    //test_02();
    //test_03();//����᲻����ֿ���ȡ���ڱ༭�����Ż����
}