#include <iostream>

using namespace std;

int test01(int a, int b){
    return a > b ? a : b;
}

int test02(int a, int b, int(*p)(int, int)){
    return p(a, b);
}

int main(){
    int (*p)(int, int);
    p = test01;

    cout << test02(10, 9, p);
}