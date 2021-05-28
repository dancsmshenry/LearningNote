#include <iostream>
#include <stdexcept>//��Ҫ��ͷ�ļ�
#include <string>

using namespace std;

class Person{
    public:
        Person(string name, int age){
            this->m_Name = name;

            if (age < 0 || age > 200){
                throw out_of_range("����Խ���ˣ�");
            }

            throw length_error("����Խ�磡");
        }

        string m_Name;
        int m_Age;
};

void test01(){
    try{
        Person("����", 100);
    }
    catch(out_of_range &e){
        cout << "Error: " << e.what() << endl;//what��������׳��쳣ʱ�����Ľ���
    }
    catch(length_error &e){
        cout << "Error: " << e.what() << endl;
    }
}

int main(){
    test01();
}