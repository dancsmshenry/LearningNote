#include <iostream>
#include <string>

using namespace std;

//设计一个学生类，属性有姓名和学号，可以给姓名和学号赋值，可以显示学生的姓名和学号
class Student{
    public:
        //设置姓名
        void setName(string name){
            this->m_Name = name;
        }

        //设置学号
        void setId(int id){
            this->m_Id = id;
        }

        //获取姓名
        string getName() const{
            return this->m_Name;
        }

        //获取id
        int getId() const{
            return this->m_Id;
        }

        void showInfo(){
            cout << "Name: " << this->m_Name << endl;
            cout << "Id: " << this->m_Id << endl;
        }

        string m_Name;//姓名
        int m_Id;//学号
};

void test01(){
    //创建一个学生实例，通过类创建对象的过程
    Student st;
    st.setName("henry");
    st.setId(123);
    
    cout << "Student's name is " << st.getName() << endl;
    cout << "Student's id is " << st.getId() << endl;
}

void test02(){
    Student st;
    st.setName("henry"); 
    st.setId(125);

    st.showInfo();
}

int main(){
    // test01();
    test02();
}