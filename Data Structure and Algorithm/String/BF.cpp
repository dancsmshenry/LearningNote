#include <iostream>
#include <string.h>

using namespace std;

const int N = 1e4 + 10, M = 1e5 + 10;

int n, m;
char p[N], s[M]; //s是源字符串，p是模式字符串

int bf(char *p, int p1, char *s, int s1)
{
    int i = 0, j = 0;
    while (i < p1 && j < s1)
    {
        if (p[i] == s[j])
        {
            ++i;
            ++j;
        }
        else
        {
            ++j;
            i = 0;
        }
    }
    if (i >= p1)
        return j - p1;
    else
        return -1;
}

int main()
{
    cin >> p >> s;

    cout << bf(p, strlen(p), s, strlen(s)) << endl;

    return 0;
}