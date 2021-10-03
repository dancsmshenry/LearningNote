#include <iostream>

using namespace std;

int a, b;

int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

int main()
{
    cin >> a >> b;
    if (a < b) swap(a, b);

    cout << gcd(a, b) << endl;

    return 0;
}