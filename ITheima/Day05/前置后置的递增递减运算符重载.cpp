#include <iostream>

using namespace std;

class MyInterger{
    friend ostream& operator<<(ostream& cout, MyInterger& myInt);
    public:
        MyInterger(){
        }

        //前置++重载
        MyInterger& operator++(){
            this->m_Num++;
            return *this;
        }

        //后置++重载
        MyInterger operator++(int){
            //先保存当前的数据
            MyInterger tmp = *this;
            m_Num ++ ;
            return tmp;
        }

    private:
        int m_Num = 0;
};

ostream& operator<<(ostream& cout, MyInterger& myInt){
    cout << myInt.m_Num;
    return cout;
} 

void test01(){
     MyInterger myInt;
     ++ myInt;//前置++
    //  myInt ++;//后置++
     cout << myInt << endl;
     cout << "++myInt = " << ++ myInt << endl;
}

void test02(){
    MyInterger myInt;
    myInt ++;
    cout << "myInt = " << myInt << endl;
}

int main(){
    // test01();

    test02();
}