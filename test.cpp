#include <iostream>

using namespace std;

class A{
    public:
        static int a;
};

int A::a = 10;

int main(){
    int a = 10;
    int *b1 = &a;
    int &b = a;
    cout << A::a << endl;
    cout << sizeof(a) << endl;
    cout << sizeof(b1) << endl;
}