#include <iostream>

using namespace std;

class Person{
    public:
        Person(int a){
            this->m_A = a;
        }

        int m_A;
};

class Person2{
    public:
        Person2(char *name){
            this->pName = new char[strlen(name) + 1];
            strcpy(this->pName, name);
        }

        //重载 = 赋值运算符
        void operator= (Person2 & p){

        }

        ~Person2(){
            if (this->name != NULL){
                delete[] this->pName;
                this->pName = NULL;
            }
        }

        char *pName;
};

void test01(){
    Person p1(10);

    Person p2(1);
}

int main(){
    
}