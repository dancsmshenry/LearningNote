#include <iostream>
#include <string>

using namespace std;

//建议将所有成员属性设置为私有
//自己提供公共的对外接口进行set或get方法访问
class Person{
    public:
        //设置年龄
        void setAge(int age){
            if (age < 0 || age > 100){
                this->m_Age = 0;
                cout << "Are you kidding me?" << endl;
                return ;
            }
            this->m_Age = age;
        }

        //获取年龄
        int getAge(){
            return this->m_Age;
        }

        //读姓名
        string getName(){
            return this->m_Name;
        }

        //写姓名
        void setName(string name){
            this->m_Name = name;
        }

        //写爱人
        void setLover(string lover){
            m_lover = lover;
        }

    private://类外不可访问，类内可以访问
        int m_Age;//年龄
        string m_Name;//姓名
        string m_lover;//情人
};

void test01(){
    Person p1;
    
    p1.setName("henry");

    cout << "Person's name is " << p1.getName() << endl;

    p1.setAge(-10);

    cout << "Person's age is " << p1.getAge() << endl;
}

int main(){
    test01();
}