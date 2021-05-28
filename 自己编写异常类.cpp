#include <iostream>
#include <string>

using namespace std;

class MyOutOfRangeException : public exception {//����ϵͳ�ṩ���쳣�࣬����ֱ�Ӽ̳�
    public:
        MyOutOfRangeException(string errorfile){
            this->m_ErrorInfo = errorfile;
        };

        virtual ~MyOutOfRangeException(){};

        //���������Ϻ����һ��
        virtual const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW{
            //���ش�����Ϣ,����Ҫstringתchar
            return this->m_ErrorInfo.c_str();
        };

        string m_ErrorInfo;
};

class Person{
    public:
        Person(string name, int age){
            this->m_Name = name;

            if (age < 0 || age > 200){
                throw MyOutOfRangeException(string("����Խ����"));
            }            
        }

        string m_Name;
        int m_Age;
};

void test01(){
    try{
        Person("����", 300);
    }
    catch(MyOutOfRangeException &e){
        cout << "Error:" << e.what() << endl;
    }
    
}

int main(){
    test01();
}
/**
 * �Լ������쳣�࣬��Ҫ�̳�exception
 * ��Ҫ��д��������what()
 * �ڲ�ά��������Ϣ���ַ���
 * ����ڹ����ʱ���������Ϣ���ַ�����what���ش���ԭ��
 **/ 