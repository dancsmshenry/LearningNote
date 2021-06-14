#include <iostream>

using namespace std;

class Phone{
    public:
        Phone(){
            cout << "Phone的构造函数" << endl;
        }

        Phone(string phoneName){
            name = phoneName;
            cout << "Phone的有参构造函数" << endl;
        }

        ~Phone(){
            cout << "Phone的析构函数" << endl;
        }

        string name;
};

class Game{
    public:
        Game(){
            cout << "Game的构造函数" << endl;
        }

        Game(string gameName){
            name = gameName;
            cout << "Game的有参构造函数" << endl;
        }

        ~Game(){
            cout << "Game的析构函数" << endl;
        }

        string name;
};

class Person{
    public:
        Person(){
            cout << "Person的构造函数" << endl;
        }

        Person(string name, string phoneName, string gameName):m_Name(name), m_Phone(phoneName), m_Game(gameName){
            cout << "Person的有参构造函数" << endl;
        }

        ~Person(){
            cout << "Person的析构函数" << endl;
        }

        string m_Name;
        Phone m_Phone;//类的构造顺序与这里的排序有关
        Game m_Game;
        
};

//类对象作为类成员时候，构造顺序先将类对象一一构造，然后析构的顺序是相反的
void test01(){
    //Person p1;
    Person p2("henry", "huawei", "lol");
    cout << "这里调用类对象，输出p2.m_Game.name：" << p2.m_Game.name << endl;
}

int main(){
    test01();//先有phone,再有game，再有person
}