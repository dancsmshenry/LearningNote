#include <iostream>

using namespace std;
/**
 * 浅拷贝
 * 是指原来有一个对象，新建一个和原来一模一样的对象，但是这里的新建的对象是指
 * 新的对象的值的存储空间是套用原来的对象的存储空间，即新建的对象是用指针指向原来的对象的存储空间
 * 所以如果释放了原来的空间，那么新建的对象就会报错（因为指针没有了指向嘛）
 * 而类的拷贝构造函数就是浅拷贝
 **/

class Person{
    public:
        Person(){
            
        }
        //初始化属性
        Person(char *name, int age){
            m_Name = (char*)malloc(strlen(name)  +1);
            strcpy(m_Name, name);

            m_Age = age;
        }

        //自己提供拷贝构造，原因简单的浅拷贝会释放堆区空间两次，导致原来的对象释放掉后，新建的对象也会挂掉
        Person(const Person &p){
            m_Age = p.m_Age;
            m_Name = (char*)malloc(strlen(p.m_Name) + 1);
            strcpy(m_Name, p.m_Name);
        }

        ~Person(){
            cout << "析构函数调用" << endl;
            //释放m_Name的空间
            if (m_Name != NULL){
                free(m_Name);
            }
        }

        //姓名
        char * m_Name;
        //年龄
        int m_Age;
};


void test01(){
    //char m_Name[100] = "adifa";
    Person p1("difa", 10);//这里的报错只是说最好不要吧字符串常量传给变量罢了，无事
    //Person p2(p1);//调用拷贝构造这里是没有问题的，调用的是系统默认的拷贝构造是浅拷贝
    //但是这里调用析构函数的时候释放了m_Name的空间，所以会出现bug
    //即类的拷贝函数是浅拷贝，为了避免这种情况，要用深拷贝

    Person p2(p1);
}

int main(){
    test01();
}