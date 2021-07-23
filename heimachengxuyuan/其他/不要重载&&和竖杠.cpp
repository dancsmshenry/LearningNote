#include <iostream>

using namespace std;

class Complex{
    public:
        Complex(int flag){
            this->flag = flag;
        }

        Complex& operator+=(Complex& complex){
            this->flag = this->flag + complex.flag;
            return *this;
        }

        bool operator&&(Complex& complex){
            return this->flag && complex.flag;
        }

    public:
        int flag;
};

int main(){
    Complex complex1(0);
    Complex complex2(1);
    if (complex1 && (complex1 += complex2)){
        cout << "真" << endl;
    }
    else{
        cout << "假" << endl;
    }
}