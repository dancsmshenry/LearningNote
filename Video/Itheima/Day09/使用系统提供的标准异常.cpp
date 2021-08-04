#include <iostream>
#include <stdexcept>//必要的头文件
#include <string>

using namespace std;

class Person{
    public:
        Person(string name, int age){
            this->m_Name = name;

            if (age < 0 || age > 200){
                throw out_of_range("年龄越界了！");
            }

            throw length_error("长度越界！");
        }

        string m_Name;
        int m_Age;
};

void test01(){
    try{
        Person("张三", 100);
    }
    catch(out_of_range &e){
        cout << "Error: " << e.what() << endl;//what输出的是抛出异常时给出的解释
    }
    catch(length_error &e){
        cout << "Error: " << e.what() << endl;
    }
}

int main(){
    test01();
}