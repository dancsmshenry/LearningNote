#include <iostream>

using namespace std;

class Phone{
    public:
        Phone(){
            cout << "Phone�Ĺ��캯��" << endl;
        }

        Phone(string phoneName){
            name = phoneName;
            cout << "Phone���вι��캯��" << endl;
        }

        ~Phone(){
            cout << "Phone����������" << endl;
        }

        string name;
};

class Game{
    public:
        Game(){
            cout << "Game�Ĺ��캯��" << endl;
        }

        Game(string gameName){
            name = gameName;
            cout << "Game���вι��캯��" << endl;
        }

        ~Game(){
            cout << "Game����������" << endl;
        }

        string name;
};

class Person{
    public:
        Person(){
            cout << "Person�Ĺ��캯��" << endl;
        }

        Person(string name, string phoneName, string gameName):m_Name(name), m_Phone(phoneName), m_Game(gameName){
            cout << "Person���вι��캯��" << endl;
        }

        ~Person(){
            cout << "Person����������" << endl;
        }

        string m_Name;
        Phone m_Phone;//��Ĺ���˳��������������й�
        Game m_Game;
        
};

//�������Ϊ���Աʱ�򣬹���˳���Ƚ������һһ���죬Ȼ��������˳�����෴��
void test01(){
    //Person p1;
    Person p2("henry", "huawei", "lol");
    cout << "���������������p2.m_Game.name��" << p2.m_Game.name << endl;
}

int main(){
    test01();//����phone,����game������person
}