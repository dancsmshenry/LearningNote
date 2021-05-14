#include <iostream>

using namespace std;

class MyString{
    public:
        MyString(const char* str){

        }

        explicit MyString(int a){
             age = a;
        }

        int age;
};

void test01(){
    MyString m1 = "abc";
    //MyString m2 = 20;
    //等价于MyString m2 = MyString(20);，即是一种隐式转换
    //但是这种方法很不明确，会有歧义发生
    //所以为了防止隐式转换，最好在前面加上一个explicit
    //而加了explicit，这样写就会报错，应该像下面一样写才不会报错
    //即explicit的作用是防止隐式类型转换
    MyString m3(20);
    //cout << m2.age << endl;
    cout << m3.age << endl;
}

int main(){
    test01();
}