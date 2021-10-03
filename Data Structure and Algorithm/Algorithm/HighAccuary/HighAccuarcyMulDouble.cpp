#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 1e6 + 10;

char a1[N], b1[N];
int a[N] = {0}, b[N] = {0}, c[N] = {0}; 

int main()
{
    cin >> a1 >> b1;
    int lena = strlen(a1), lenb = strlen(b1);
    for (int i = 0; i < lena; i ++ ) a[lena - i] = a1[i] - '0';
    for (int i = 0; i < lenb; i ++ ) b[lenb - i] = b1[i] - '0';

    for (int i = 1; i <= lena; i ++ )
    {
        int x = 0;
        for (int j = 1; j <= lenb; j ++ )
        {
            c[i + j - 1] = a[i] * b[j] + c[i + j - 1] + x;
            x = c[i + j - 1] / 10;
            c[i + j - 1] %= 10;
        }
        c[i + lenb] = x;
    }

    int len = lena + lenb;
    while (!c[len] && len > 1) len--;
    for (int i = len; i > 0; i -- ) cout << c[i];

    return 0;
}