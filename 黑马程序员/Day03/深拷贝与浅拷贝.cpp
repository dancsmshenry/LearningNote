#include <iostream>

using namespace std;
/**
 * ǳ����
 * ��ָԭ����һ�������½�һ����ԭ��һģһ���Ķ��󣬵���������½��Ķ�����ָ
 * �µĶ����ֵ�Ĵ洢�ռ�������ԭ���Ķ���Ĵ洢�ռ䣬���½��Ķ�������ָ��ָ��ԭ���Ķ���Ĵ洢�ռ�
 * ��������ͷ���ԭ���Ŀռ䣬��ô�½��Ķ���ͻᱨ����Ϊָ��û����ָ���
 * ����Ŀ������캯������ǳ����
 **/

class Person{
    public:
        Person(){
            
        }
        //��ʼ������
        Person(char *name, int age){
            m_Name = (char*)malloc(strlen(name)  +1);
            strcpy(m_Name, name);

            m_Age = age;
        }

        //�Լ��ṩ�������죬ԭ��򵥵�ǳ�������ͷŶ����ռ����Σ�����ԭ���Ķ����ͷŵ����½��Ķ���Ҳ��ҵ�
        Person(const Person &p){
            m_Age = p.m_Age;
            m_Name = (char*)malloc(strlen(p.m_Name) + 1);
            strcpy(m_Name, p.m_Name);
        }

        ~Person(){
            cout << "������������" << endl;
            //�ͷ�m_Name�Ŀռ�
            if (m_Name != NULL){
                free(m_Name);
            }
        }

        //����
        char * m_Name;
        //����
        int m_Age;
};


void test01(){
    //char m_Name[100] = "adifa";
    Person p1("difa", 10);//����ı���ֻ��˵��ò�Ҫ���ַ������������������ˣ�����
    //Person p2(p1);//���ÿ�������������û������ģ����õ���ϵͳĬ�ϵĿ���������ǳ����
    //���������������������ʱ���ͷ���m_Name�Ŀռ䣬���Ի����bug
    //����Ŀ���������ǳ������Ϊ�˱������������Ҫ�����

    Person p2(p1);
}

int main(){
    test01();
}