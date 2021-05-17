#include <iostream>

using namespace std;

class MyInterger{
    friend ostream& operator<<(ostream& cout, MyInterger& myInt);

    public:
        MyInterger(){
            m_Num = 0;
        }

        //前置重载++，这里必须返回的是一个引用
        //这里模仿的是++（++a）的写法，即如果是值返回，就会导致返回的不是原来的哪个东西了，就会操作失误
        MyInterger& operator++(){
            this->m_Num ++;
            return *this;
        }

        //后置重载++，加上int表示后置
        //这里返回的是一个临时数据，如果返回的是一个引用的话，临时数据木有了，那返回啥呢？？？
        MyInterger operator++(int){
            //先保存当前的数据
            MyInterger tmp = *this;
            this->m_Num ++ ;
            return tmp;
        }

        int m_Num;
};

ostream& operator<<(ostream& cout, MyInterger& myInt){
    cout << myInt.m_Num;
    return cout;
}
// ostream& operator<<(ostream& cout, MyInterger myInt){
//     cout << myInt.m_Num;
//     return cout;
// }

void test01(){
    MyInterger myInt;
    //cout << "m_Num = " << myInt << endl;
    //cout << "m_Num = " << (++myInt) << endl;
    //cout << "m_Num = " << myInt ++ << endl;//这里出现报错，不明原因，挖坑

    //注意,如果上面的前置重载是值返回（本来是值引用），就会导致这里出现问题
    //即++myInt返回的是一个值，而不是原来的那个myInt，导致后续的++对的是一个新的值进行操作，而不是原来的myInt
    //cout << "++(++m_Num) " << ++(++myInt) << endl;
    //cout << myInt.m_Num;
}

int main(){
    test01();
}