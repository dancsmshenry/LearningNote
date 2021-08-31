#include <iostream>

using namespace std;

class A{
    public:
        A(){
            cout << "A()" << endl;
        }

        ~A(){
            cout << "~A()" << endl;
        }
};

class C{
    public:
        C(){
            cout << "C()" << endl;
        }

        ~C(){
            cout << "~C()" << endl;
        }
};

class B : public A{
    public:
        B(){
            cout << "B()" << endl;
        }

        ~B(){
            cout << "~B()" << endl;
        }

        C c;
};

void func(){
    static int i = 10;
}

int main(){
    // B b;

    // cout << i << endl;
}