#include <iostream>

using namespace std;

class Person{
    public:
        Person(string m_Name, int m_Age){
            this->m_Name = m_Name;
            this->m_Age = m_Age;
        }

        bool operator==(Person &p1){
            if (this->m_Name == p1.m_Name && this->m_Age == p1.m_Age){
                return true;
            }

            return false;
        }

        bool operator!=(Person &p1){
            if (this->m_Name == p1.m_Name && this->m_Age == p1.m_Age){
                return false;
            }

            return true;
        }

    public:
        string m_Name;
        int m_Age;
};

void test01(){
    Person p1("henry", 10);
    Person p2("dancy", 15);

    if (p1 == p2){
        cout << "p1 == p2"<< endl;
    }
    else {
        cout << "p1 != p2" << endl;
    }

    if (p1 != p2){
        cout << "p1 != p2"<< endl;
    }
    else {
        cout << "p1 == p2" << endl;
    }
}

int main(){
    test01();
}